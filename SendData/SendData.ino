#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MANUEL_99";
const char* password = "Barbara1032502994";
const char* serverAddress = "http://192.168.1.15:8081/random-data";  // Puedes usar "localhost" en lugar de la dirección IP
const int serverPort = 8081;  // Ajusta el puerto para que coincida con el de tu servidor

void setup() {
  Serial.begin(115200);
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
  HTTPClient http;

  Serial.println("Conectando al servidor backend local...");

  if (http.begin(client, serverAddress)) {
    // Configura la cabecera y el contenido del mensaje POST
    http.addHeader("Content-Type", "application/json");

    // Crea un objeto JSON con el dato aleatorio
    String jsonPayload = "{\"number\": " + String(data) + "}";

    // Realiza la solicitud POST con el JSON como contenido
    int httpCode = http.POST(jsonPayload);

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Respuesta del servidor backend local: " + payload);
    } else {
      Serial.println("Error en la solicitud POST al servidor backend local");
    }

    // Libera recursos
    http.end();
  } else {
    Serial.println("Error al conectarse al servidor backend local");
  }
}

void connectToWiFi() {
  Serial.println("Conectando a WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando...");
  }

  Serial.println("Conectado a WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}