# Projeto DHT11 com ESP8266 e Firebase


Este projeto utiliza um **ESP8266** com o sensor **DHT11** para medir **temperatura** e **umidade**, sincroniza o horário com um servidor **NTP**, e envia os dados para o **Firebase Firestore** a cada hora. Teste de git.


<br>

## ⚙️ Tecnologias Utilizadas

- ESP8266
- Sensor DHT11
- Firebase Firestore
- NTP (Network Time Protocol)
- Arduino IDE
- Bibliotecas:
  - `ESP8266WiFi.h`
  - `Firebase_ESP_Client.h`
  - `DHT.h`
  - `NTPClient.h`

<br>

## 🧩 Funcionalidades

- Leitura de temperatura e umidade com o sensor DHT11
- Conexão Wi-Fi com ESP8266
- Autenticação de usuário no Firebase
- Envio dos dados para o Firestore (temperatura, umidade, data e hora)
- Sincronização com horário oficial via NTP
- Envio de dados a cada 1 hora

<br>

## ⚙️ Pré-requisitos

- Placa ESP8266 (NodeMCU ou similar)
- Sensor DHT11
- Conta no [Firebase](https://firebase.google.com/)
- Arduino IDE com bibliotecas instaladas

<br>

## 🔌 Montagem do Circuito

- **DHT11 VCC** → 3.3V do ESP8266  
- **DHT11 GND** → GND do ESP8266  
- **DHT11 Data** → GPIO 4 (D2 na NodeMCU)

<br>

## 🔐 Credenciais Necessárias

Você deve preencher no código:

```cpp
#define WIFI_SSID "SEU_WIFI"
#define WIFI_PASSWORD "SENHA_WIFI"

#define API_KEY "SUA_API_KEY"
#define FIREBASE_PROJECT_ID "ID_DO_PROJETO_FIREBASE"

#define USER_EMAIL "EMAIL_DO_USUARIO"
#define USER_PASSWORD "SENHA_DO_USUARIO"
```

<br>

## 🙋‍♂️ Autor

Desenvolvido por Bruno Silveira. Contato:  
• [LinkedIn](https://www.linkedin.com/in/bruno-silveira-dionisio/)  
• [GitHub](https://github.com/Brun0Silveir4)  
• bruno.silveira.dionisio@gmail.com