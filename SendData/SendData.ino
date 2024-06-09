#include <WiFi.h>
#include <WiFiClientSecure.h>
// //sudo chmod 666 /dev/ttyUSB0

//Variables memdicion de corriente
#define courrent 35 //ADC7 COURRENT
float courrentEmu = 0;
float id = 0;
float id_ant = 0;
float iq = 0;
float iq_ant = 0;
float pipll = 0;
float pipll_ant = 0;
float thetap_ant = 0;
float thetap = 0;
float w0 = 2*3.1416*60;
float w0p = 0;
float w0p_ant = 0;
float coseno = 0;
float coseno_ant = 0;
float i_coseno = 0;
float i_coseno_ant = 0;
int thetap_dac = 0;
const int dacPin = 25; //DAC 1
const int dacResolution = 8;
float sin_ant = 0;
float i_sin_ant = 0;
float id_osci = 0;
//Variables medicion de voltaje
#define voltage 34 //ADC 6 VOLTAJE
#define blink 26
float voltageEmu = 0;
float vd = 0;
float vd_ant = 0;
float vq = 0;
float vq_ant = 0;
float p = 0;
float s = 0;
float q = 0;
float fp = 0;
//Constantes PLL  
const float a1 = 0.963;
const float a2 = 0.0963;
const float Ts = 1.0/10080;
unsigned long previousMillis = 0;
unsigned long otherMillis = 0;
unsigned long interval = Ts * 1000;
String text = "";
//FLAGS
bool voltageMet = false;
bool courrentMet = true;
//iot
const char* ssid = "MANUEL_99";
const char* password = "Barbara1032502994";
const char* serverAddress = "lifae-iot.onrender.com";
const int serverPort = 443;  // Puerto para HTTPS

// AsyncWebServer server(80);
int cont = 0;
void setup() {
  Serial.begin(115200);
  Serial.println("HOlaaaa");
  pinMode(dacPin, ANALOG);
  connectToWiFi();
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long otherMillis = millis();
    if(currentMillis-previousMillis >= interval){
      // if(cont < 100000){
      //   cont = cont +1;
        voltageEmu = (analogRead(voltage)*(3.3/4095.0)-1.6); //Emulador
        courrentEmu = (analogRead(courrent)*(3.3/4095.0)-1); //Emulador
        coseno = coseno_ant*a1-a2*voltageEmu+sin_ant;
        vd= voltageEmu*cos(thetap)+coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
        vq = -voltageEmu*sin(thetap)+coseno*cos(thetap);

        i_coseno = i_coseno_ant*a1-a2*courrentEmu+i_sin_ant;
        id= courrentEmu*cos(thetap)+i_coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
        iq = -courrentEmu*sin(thetap)+coseno*cos(thetap);
        pipll=pipll_ant+a1*vd-vd_ant*a2;//salida PIpll

        w0p=pipll+w0;//entrada del integrador
        
        thetap=w0p_ant*Ts+thetap_ant;//salida pll
        w0p_ant = w0p;
        if (thetap>=2*3.1416)

        {
          thetap= thetap-(2 * 3.1416);
        }
        pipll_ant = pipll;
        vd_ant = vd;
        vq_ant = vq;
        id_ant = id;
        iq_ant = iq;
        thetap_ant = thetap;
        coseno_ant = coseno;
        sin_ant = voltageEmu;
        i_sin_ant = courrentEmu;
        thetap_dac = map(thetap, 0, 2 * 3.1416, 0, pow(2, dacResolution) - 1);
          p = (vd*id)/2;
          q = -vd*iq/2;
          s = sqrt(p*p+q*q);
          fp = p/s;
        dacWrite(dacPin, thetap_dac);
    // }else{
    //   cont = 0;
    //   sendToBackendAsync(p);
    // }
    previousMillis = currentMillis;
  }
  // if(otherMillis-previousMillis >= 1000){
  //   sendToBackendAsync(p);
  //   otherMillis = currentMillis;
  // }
  // digitalWrite(blink,HIGH);
  // Serial.println(p);
  // digitalWrite(blink,LOW);


  // float randomData = random(0, 100);
  // sendToBackendAsync(randomData);
  // delay(10000);  // Ejemplo de espera corta
}

void sendToBackendAsync(float data) {
  Serial.println("Conectando al servidor...");

  WiFiClientSecure client;
  client.setInsecure();

    if (client.connect(serverAddress, serverPort)) {
    Serial.println("Conectado al servidor");

    String jsonPayload = "{\"number\": " + String(data) + "}";
    String postRequest = "POST /random-data HTTP/1.1\r\nHost: " + String(serverAddress) + "\r\nContent-Type: application/json\r\nContent-Length: " + String(jsonPayload.length()) + "\r\n\r\n" + jsonPayload;

    client.print(postRequest);

    Serial.println("Datos enviados al servidor");
    delay(100);
    client.stop();
  } else {
    Serial.println("Error de conexión al servidor");
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
