//Pll con interrupcion
// #define courrent 35 //ADC7 COURRENT
// volatile double courrentEmu = 0;
// double id = 0;
// double id_ant = 0;
// double iq = 0;
// double iq_ant = 0;
// double i_coseno = 0;
// double i_coseno_ant = 0;
// int thetap_dac = 0;
// const int dacPin = 25; //DAC 1
// const int dacResolution = 8;
// double sin_ant = 0;
// double i_sin_ant = 0;
// double id_osci = 0;
// //Variables medicion de voltaje
// #define voltage 34 //ADC 6 VOLTAJE
// #define blink 2
// volatile double voltageEmu = 0;
// double pipll = 0;
// double pipll_ant = 0;
// double thetap_ant = 0;
// double thetap = 0;
// double w0 = 2*3.1416*60;
// double w0p = 0;//Probar 2*3.1416*60
// double w0p_ant = 0;
// double coseno = 0;
// double coseno_ant = 0;
// double vd = 0;
// double vd_ant = 0;
// double vq = 0;
// double vq_ant = 0;
// double p = 0;
// double s = 0;
// double q = 0;
// double fp = 0;
// //Constantes PLL  
// const double a1 = 0.10050*10;//0.963;
// const double a2 = 0.09950*10;//0.0963;
// //Configuracion del timer
// double Ts;
// int PRSC;
// hw_timer_t *Timer0_Cfg = NULL;


// //Interrupcion Calulo PLL
// void IRAM_ATTR Timer0_ISR() {                       //Actual coseno = coseno_ant*a1-a2*voltageEmu+sin_ant;
//       // digitalWrite(blink,HIGH);
//       voltageEmu = (analogRead(voltage)*(3.3/4095.0)-1.6); //Emulador probar sin emulacion
//       courrentEmu = (analogRead(courrent)*(3.3/4095.0)-1); //Emulador probar sin emulacion
//       coseno = coseno_ant*a1-a2*voltageEmu+sin_ant; // Revisar si es de la forma  coseno=cos_ant*0.9630-0.963*Vol_Carga+sin_ant; donde voltajeEmu = Vol_Carga
//       vd= voltageEmu*cos(thetap)+coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
//       vq = -voltageEmu*sin(thetap)+coseno*cos(thetap);

//       i_coseno = i_coseno_ant*a1-a2*courrentEmu+i_sin_ant;
//       id= courrentEmu*cos(thetap)+i_coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
//       iq = -courrentEmu*sin(thetap)+coseno*cos(thetap);
//       pipll=pipll_ant+a1*vd-vd_ant*a2;//salida Pipll en voltaje

//       w0p=pipll+w0;//entrada del integrador
      
//       thetap=w0p_ant*Ts+thetap_ant;//salida pll
//       w0p_ant = w0p;
//       if (thetap>=2*3.1416){
//         thetap= thetap-(2 * 3.1416);
//       }
//       pipll_ant = pipll;
//       vd_ant = vd;
//       vq_ant = vq;
//       id_ant = id;
//       iq_ant = iq;
//       thetap_ant = thetap;
//       coseno_ant = coseno;
//       sin_ant = voltageEmu;
//       i_sin_ant = courrentEmu;
//       thetap_dac = map(thetap, 0, 2 * 3.1416, 0, pow(2, dacResolution) - 1);
//       p = (vd*id)/2;
//       q = -vd*iq/2;
//       s = sqrt(p*p+q*q);
//       fp = p/s;
//       dacWrite(dacPin, thetap_dac); //Probarlo tambien en el loop principal quitarlo al finalizar
//       // digitalWrite(blink,LOW);
// }
// void setup() {
//   // Configura el pin GPIO como DAC
//   pinMode(dacPin, ANALOG);
//   // pinMode(VdacPin, ANALOG);
//   pinMode(blink, OUTPUT);
//   // Serial.begin(115200);

//   //Configuracion de la interrupcion
//   Ts = 99,206; //Tiempo de muestro en microSegundos (1.0/10080)segundos
//   PRSC = 80; //Reloj base del timer 80 MHz
//   Timer0_Cfg = timerBegin(0, PRSC, true); //Inicializar timer
//   timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
//   timerAlarmWrite(Timer0_Cfg, Ts, true);
//   timerAlarmEnable(Timer0_Cfg);
// }

// void loop() {
//   // voltageEmu = (analogRead(voltage)*(3.3/4095.0)-1.6); //Emulador probar sin emulacion
//   // courrentEmu = (analogRead(courrent)*(3.3/4095.0)-1); //Emulador probar sin emulacion
//   // delayMicroseconds(10);
//   // digitalWrite(blink,HIGH);
//   // Serial.println(p);
//   // digitalWrite(blink,LOW);
//   //delay(0.00007);
// }

//Pll Funcionaba
//Variables memdicion de corriente
// #define courrent 35 //ADC7 COURRENT
// double courrentEmu = 0;
// double id = 0;
// double id_ant = 0;
// double iq = 0;
// double iq_ant = 0;
// double pipll = 0;
// double pipll_ant = 0;
// double thetap_ant = 0;
// double thetap = 0;
// double w0 = 2*3.1416*60;
// double w0p = 0;
// double w0p_ant = 0;
// double coseno = 0;
// double coseno_ant = 0;
// double i_coseno = 0;
// double i_coseno_ant = 0;
// int thetap_dac = 0;
// const int dacPin = 25; //DAC 1
// const int dacResolution = 8;
// double sin_ant = 0;
// double i_sin_ant = 0;
// double id_osci = 0;
// //Variables medicion de voltaje
// #define voltage 34 //ADC 6 VOLTAJE
// #define blink 26
// double voltageEmu = 0;
// double vd = 0;
// double vd_ant = 0;
// double vq = 0;
// double vq_ant = 0;
// double p = 0;
// double s = 0;
// double q = 0;
// double fp = 0;
// //Constantes PLL  
// const double a1 = 0.963;
// const double a2 = 0.0963;
// const double Ts = 1.0/10080;
// unsigned long previousMillis = 0;
// unsigned long interval = Ts * 1000;
// String text = "";
// //FLAGS
// bool voltageMet = false;
// bool courrentMet = true;
// void setup() {
//   // Configura el pin GPIO como DAC
//   pinMode(dacPin, ANALOG);
//   // pinMode(VdacPin, ANALOG);
//   pinMode(blink, OUTPUT);
//   Serial.begin(115200);
// }

// void loop() {
//   unsigned long currentMillis = millis();
//     if(currentMillis-previousMillis >= interval){
//       voltageEmu = (analogRead(voltage)*(3.3/4095.0)-1.6); //Emulador
//       courrentEmu = (analogRead(courrent)*(3.3/4095.0)-1); //Emulador
//       coseno = coseno_ant*a1-a2*voltageEmu+sin_ant;
//       vd= voltageEmu*cos(thetap)+coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
//       vq = -voltageEmu*sin(thetap)+coseno*cos(thetap);

//       i_coseno = i_coseno_ant*a1-a2*courrentEmu+i_sin_ant;
//       id= courrentEmu*cos(thetap)+i_coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
//       iq = -courrentEmu*sin(thetap)+coseno*cos(thetap);
//       pipll=pipll_ant+a1*vd-vd_ant*a2;//salida PIpll

//       w0p=pipll+w0;//entrada del integrador
      
//       thetap=w0p_ant*Ts+thetap_ant;//salida pll
//       w0p_ant = w0p;
//       if (thetap>=2*3.1416)

//       {
//         thetap= thetap-(2 * 3.1416);
//       }
//       pipll_ant = pipll;
//       vd_ant = vd;
//       vq_ant = vq;
//       id_ant = id;
//       iq_ant = iq;
//       thetap_ant = thetap;
//       coseno_ant = coseno;
//       sin_ant = voltageEmu;
//       i_sin_ant = courrentEmu;
//       thetap_dac = map(thetap, 0, 2 * 3.1416, 0, pow(2, dacResolution) - 1);
//       //p = (vd*id)/2;
//         p = (vd*id)/2;
//         q = -vd*iq/2;
//         s = sqrt(p*p+q*q);
//         fp = p/s;
//       //text = "VD es: " + vd;
//       //Serial.print("VD es ");
//       Serial.println(vd);
//       //Serial.print("P es")
//       //Serial.println(p);
//       dacWrite(dacPin, thetap_dac);
//     previousMillis = currentMillis;
//   }
//   // digitalWrite(blink,HIGH);
//   // Serial.println(p);
//   // digitalWrite(blink,LOW);
//   //delay(0.00007);
// }


//Variables memdicion de corriente
// #define courrent 35 //ADC7 COURRENT
// float courrentEmu = 0;
// float id = 0;
// float id_ant = 0;
// float iq = 0;
// float iq_ant = 0;
// float pipll = 0;
// float pipll_ant = 0;
// float thetap_ant = 0;
// float thetap = 0;
// float w0 = 2*3.1416*60;
// float w0p = 0;
// float w0p_ant = 0;
// float coseno = 0;
// float coseno_ant = 0;
// float i_coseno = 0;
// float i_coseno_ant = 0;
// int thetap_dac = 0;
// const int dacPin = 25; //DAC 1
// const int dacResolution = 8;
// float sin_ant = 0;
// float i_sin_ant = 0;
// float id_osci = 0;
// //Variables medicion de voltaje
// #define voltage 34 //ADC 6 VOLTAJE
// #define blink 26
// float voltageEmu = 0;
// float vd = 0;
// float vd_ant = 0;
// float vq = 0;
// float vq_ant = 0;
// float p = 0;
// float s = 0;
// float q = 0;
// float fp = 0;
// //Constantes PLL  
// const float a1 = 0.963;
// const float a2 = 0.0963;
// const float Ts = 1.0/10080;
// unsigned long previousMillis = 0;
// unsigned long interval = Ts * 1000;
// String text = "";
// //FLAGS
// bool voltageMet = false;
// bool courrentMet = true;
// void setup() {
//   // Configura el pin GPIO como DAC
//   pinMode(dacPin, ANALOG);
//   // pinMode(VdacPin, ANALOG);
//   pinMode(blink, OUTPUT);
//   Serial.begin(115200);
// }

// void loop() {
//   unsigned long currentMillis = millis();
//     if(currentMillis-previousMillis >= interval){
//       voltageEmu = (analogRead(voltage)*(3.3/4095.0)-1.6); //Emulador
//       //courrentEmu = (analogRead(courrent)*(3.3/4095.0)-1); //Emulador
//       coseno = coseno_ant*a1-a2*voltageEmu+sin_ant;
//       vd= voltageEmu*cos(thetap)+coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
//       vq = -voltageEmu*sin(thetap)+coseno*cos(thetap);

//       //i_coseno = i_coseno_ant*a1-a2*courrentEmu+i_sin_ant;
//       //id= courrentEmu*cos(thetap)+i_coseno*sin(thetap);//señales en cuadratura- entrada del PIPLL COmponente en D
//       //iq = -courrentEmu*sin(thetap)+coseno*cos(thetap);
//       pipll=pipll_ant+a1*vd-vd_ant*a2;//salida PIpll

//       w0p=pipll+w0;//entrada del integrador
      
//       thetap=w0p_ant*Ts+thetap_ant;//salida pll
//       w0p_ant = w0p;
//       if (thetap>=2*3.1416)

//       {
//         thetap= thetap-(2 * 3.1416);
//       }
//       pipll_ant = pipll;
//       vd_ant = vd;
//       vq_ant = vq;
//       //id_ant = id;
//       //iq_ant = iq;
//       thetap_ant = thetap;
//       coseno_ant = coseno;
//       sin_ant = voltageEmu;
//       //i_sin_ant = courrentEmu;
//       thetap_dac = map(thetap, 0, 2 * 3.1416, 0, pow(2, dacResolution) - 1);
//       //p = (vd*id)/2;
//         // p = (vd*id)/2;
//         // q = -vd*iq/2;
//         // s = sqrt(p*p+q*q);
//         // fp = p/s;
//       //text = "VD es: " + vd;
//       //Serial.print("VD es ");
//       Serial.println(vd);
//       //Serial.print("P es")
//       //Serial.println(p);
//       dacWrite(dacPin, thetap_dac);
//     previousMillis = currentMillis;
//   }
//   // digitalWrite(blink,HIGH);
//   // Serial.println(p);
//   // digitalWrite(blink,LOW);
//   //delay(0.00007);
// }