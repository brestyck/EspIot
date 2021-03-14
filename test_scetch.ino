#define CS_PIN 15
#define MOSI_PIN 13
#define MISO_PIN 12
#define CLOCK_PIN 14
#include <MCP3008.h>

const String esp_id = "ofBoris";

#include <ESP8266WiFi.h>
const String sensor_type = "Photoresistor"; // Какой датчик подключаем
const String sensor_type1 = "Thermoresistor"; // Какой датчик подключаем
const char* ssid     = "ssid";         // тут SSID и пароль к WIFI
const char* password = "pass";

const char* host = "chat-retriever.herokuapp.com";     // тут адрес сервера
MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

void setup() {
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
  Serial.begin(115200);
  delay(10);
  pinMode(16, OUTPUT);

  // в сетапе как обычно подключаемся к сети

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  digitalWrite(16, 0);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(16, 1);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Get("GET /delete/esp HTTP/1.1");
  delay(1000);
  Get("GET /deploy/esp/"+esp_id+"/VIRTUALHOST HTTP/1.1");        // при  включении выполняем функцию
}
int data = 0;
int data1 = 0;
void loop() {
  delay(20000);
  data = adc.readADC(0);
  delay(1000);
  data1 = adc.readADC(1);
  delay(1000);
  Get("GET /delete/"+esp_id+" HTTP/1.1");
  delay(1000);
  Get("GET /deploy/"+esp_id+"/"+(String)data+"/"+sensor_type+" HTTP/1.1");
  delay(1000);
  Get("GET /delete/VIRTUALHOST HTTP/1.1");
  delay(1000);
  Get("GET /deploy/VIRTUALHOST/"+(String)data1+"/"+sensor_type1+" HTTP/1.1");
}


void Get(String depl_url) {
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {      /// подключаемся к серверу
    Serial.println("connection failed");
    return;
  }
  /// если подключились, отправляем чего от сервера хотим
  // сам GET запрос с ID и ключем
  Serial.println("GET processing...");
  client.println(depl_url); // FORMAT!!! GET /link/ HTTP/1.1
  // говорим к какому хосту обращаемся (на сервере может быть несколько сайтов)
  Serial.println("Transmitting deploy query to the host");
  client.println("Host: chat-retriever.herokuapp.com");
  // говорим что закончили
  Serial.println("Asking server for connection:close...");
  client.println("Connection: close");
  client.println();
  delay(1000);  // ждем немного
  // читаем ответ и отправляем его в Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
}
