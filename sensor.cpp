#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <DHT.h>
#include <NTPClient.h>
#include <WiFiUdp.h>  
 
//DHT instance
#define DHT11PIN 4
#define DHTTYPE DHT11
 
DHT dhtSensor(DHT11PIN, DHTTYPE);
 
// wifi credentials
#define WIFI_SSID "myRouter"
#define WIFI_PASSWORD "09112005"
 
 
// FIrebase credentials
#define API_KEY "AIzaSyDhZ0jNSrvphkJlCwOQXorBcvK-ZzPVkrY"
#define FIREBASE_PROJECT_ID "finalproject-c4d5d"
 
// user credentials
#define USER_EMAIL "p4dojefinho@gmail.com"
#define USER_PASSWORD "P4dojefinho123"
 
// Firebase data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
 
WiFiUDP ntpUDP;
NTPClient ntp(ntpUDP);
 
void setup() {
  Serial.begin(115200);
 
  dhtSensor.begin();
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to wifi...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  // firebase version
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
 
  // assign api key
  config.api_key = API_KEY;
 
  // user sign-in
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
 
  config.token_status_callback = tokenStatusCallback;
 
  Firebase.begin(&config, &auth);
 
  Firebase.reconnectWiFi(true);
 
  ntp.begin();
 
  //GMT em segundos
  // +1 = 3600
  // +8 = 28800
  // -1 = -3600
  // -3 = -10800 (BRASIL)
  ntp.setTimeOffset(-10800);
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
  String collectionPath = "/SensorData";
  String docId = String(millis());;
 
  FirebaseJson content;
  FirebaseJson fields;
 
  float temperature = dhtSensor.readTemperature();
  float humidity = dhtSensor.readHumidity();
 
  if (!isnan(temperature) && !isnan(humidity)) {
    // Add temperature field
    FirebaseJson tempField;
    tempField.set("stringValue", String(temperature, 2));
    fields.set("temp", tempField);
 
    // Add humidity field
    FirebaseJson hmdField;
    hmdField.set("stringValue", String(humidity, 2));
    fields.set("hmd", hmdField);
 
    String time = "";
    String date = "";
 
    if (ntp.update()){
      time = ntp.getFormattedTime();
      String formattedDateTime = ntp.getFormattedDate();
      date = formattedDateTime.substring(0, 10);
    } else {
      Serial.println("!Erro ao atualizar NTP!\n");
    }
    //char dateBuffer[11];
    //char timeBuffer[9];
    //strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", timeinfo);
    //strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", timeinfo);
 
    // Add date field
    FirebaseJson dateField;
    dateField.set("stringValue", date);
    fields.set("date", dateField);
    // Add time field
    FirebaseJson timeField;
    timeField.set("stringValue", time);
    fields.set("time", timeField);
    // Set the final content to the fields
    content.set("fields", fields);
 
    Serial.print("Update/Add DHT Data...");
 
    if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", collectionPath.c_str(), docId.c_str(), content.raw(), "")){
      Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
    } else {
      Serial.println(fbdo.errorReason());
    }
  } else {
    Serial.println("Failed to read DHT data.");
  }
 
  delay(3600000);
}
 