// GET запрос к http://api.openweathermap.org
const String esp_id = "Boris012";

#include <ESP8266WiFi.h>
const String sensor_type = "RH_SENSOR"; // Какой датчик подключаем
const char* ssid     = "ssid";         // тут SSID и пароль к WIFI
const char* password = "pass";

const char* host = "chat-retriever.herokuapp.com";     // тут адрес сервера


void setup() {
  Serial.begin(115200);
  delay(10);


  // в сетапе как обычно подключаемся к сети

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Get("GET /delete/esp HTTP/1.1");
  delay(1000);
  Get("GET /deploy/esp/"+esp_id+"/VIRTUALHOST HTTP/1.1");        // при  включении выполняем функцию
}
int data = 0;
void loop() {
  delay(30000);
  Get("GET /delete/"+esp_id+" HTTP/1.1");
  delay(1000);
  Get("GET /deploy/"+esp_id+"/"+(String)data+"/"+sensor_type+" HTTP/1.1");
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
