#include <WiFi.h>
//sudo chmod 666 /dev/ttyUSB0
const char* ssid = "MANUEL_99";
const char* password = "Barbara1032502994";
const char* serverAddress = "192.168.1.15";  // Puedes usar "localhost" en lugar de la dirección IP
const int serverPort = 8081;  // Ajusta el puerto para que coincida con el de tu servidor

void setup() {
  connectToWiFi();
}

void loop() {
  float randomData = random(0, 100);  // Datos aleatorios

  // Realiza la solicitud HTTP POST al servidor backend local
  sendToBackend(randomData);

  delay(10000);  // Espera 10 segundos antes de enviar el próximo conjunto de datos
}

void sendToBackend(float data) {
  WiFiClient client;

  Serial.println("Conectando al servidor...");

  if (client.connect(serverAddress, serverPort)) {

    String jsonPayload = "{\"number\": " + String(data) + "}";

    client.println("POST /random-data HTTP/1.1");
    client.println("Host: " + String(serverAddress));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(jsonPayload.length()));
    client.println();
    client.print(jsonPayload);
    client.stop();
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

}