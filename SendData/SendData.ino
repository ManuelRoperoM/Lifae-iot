// #include <ESPAsyncWebServer.h>
// #include <WiFi.h>
// #include <AsyncTCP.h>
// //sudo chmod 666 /dev/ttyUSB0
// const char* ssid = "MANUEL_99";
// const char* password = "Barbara1032502994";
// const char* serverAddress = "192.168.1.15";
// const int serverPort = 8081;

// AsyncWebServer server(80);

// void setup() {
//   //Serial.begin(115200);
//   connectToWiFi();
//   server.on("/random-data", HTTP_POST, [](AsyncWebServerRequest *request){
//     String data;
//     if(request->hasParam("plain")) {
//       data = request->getParam("plain")->value();
//       //Serial.println("Datos recibidos (JSON): " + data);
//       request->send(200, "text/plain", "Datos recibidos correctamente");
//     } else {
//       request->send(400, "text/plain", "Cuerpo de solicitud faltante");
//     }
//   });
//   server.begin();
// }

// void loop() {
//   float randomData = random(0, 100);
//   sendToBackendAsync(randomData);
//   delay(10000);  // Espera 10 segundos antes de enviar el próximo conjunto de datos
// }

// void sendToBackendAsync(float data) {
//   AsyncClient* client = new AsyncClient();

//   client->onConnect([data](void* arg, AsyncClient* asyncClient){
//     //Serial.println("Conectado al servidor");
//     String jsonPayload = "{\"number\": " + String(data) + "}";
//     String postRequest = "POST /random-data HTTP/1.1\r\nHost: " + String(serverAddress) + "\r\nContent-Type: application/json\r\nContent-Length: " + String(jsonPayload.length()) + "\r\n\r\n" + jsonPayload;

//     asyncClient->write(postRequest.c_str(), postRequest.length());
//   }, NULL);

//   client->onDisconnect([](void* arg, AsyncClient* asyncClient){
//     //Serial.println("Desconectado del servidor");
//     delete asyncClient;
//   }, NULL);

//   client->connect(serverAddress, serverPort);
// }

// void connectToWiFi(){
//       WiFi.begin(ssid, password);
      
//       while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//       }
// }