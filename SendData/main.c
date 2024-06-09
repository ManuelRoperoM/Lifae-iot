// //###########################################################################
// // FILE:	SPWM
// // TITLE:	DSP28335; ePWM1A 24 kHz PWM signal sine wave output 60Hz via ePWM1A
// ////###########################################################################
// #include "DSP2833x_Device.h"
// #include "IQmathLib.h"
// #include "seno_signal.h"
// #include "math.h"
// //unsigned long f=100000;
// extern  float32 CapturaADC ( float32 *C_inductor, float32 *V_Capacitor, float32 *V_Carga); //Funci�n Captura ADC
// float32 Co_inductor; // Variable corriente
// float32 Vol_Capacitor; // Variable tensi�n
// float32 Vol_Sync; // Variable tensi�n
// float32 Vol_Carga; // Variable V Carga
// float32 Vol_referencia; // Variable Volt Referencia
// // external function prototypes
// extern void InitSysCtrl(void);
// extern void InitPieCtrl(void);
// extern void InitPieVectTable(void);
// extern void InitAdc (void);
// float32 seno=0;
// float32 seno2=0;
// int j= 0;
// int ena= 1;
// float32 theta=0;
// unsigned int CompA;
// unsigned int CompA2;
// // Prototype statements for functions found within this file.
// void Gpio_select(void);
// void Setup_ePWM1(void);
// void Config_ADC (void);
// interrupt void ePWM1A_compare_isr(void);
// //###########################################################################
// //Variables PLL
// //###########################################################################
// float32 coseno=0;
// float32 cos_ant=0;
// float32 sin_ant=0;
// float32 vd=0;
// float32 vq=0;
// float32 vd_ant=0;
// float32 vq_ant=0;
// float32 thetap=0;
// float32 thetap_ant=0;
// float32 pipll=0;
// float32 pipll_ant=0;
// float32 a1=0.10050*10;
// float32 a2=0.09950*10;
// float32 w0=2*3.1416*60;
// float32 w0p=2*3.1416*60;//variable de contador
// float32 Ts=0.000099206;//periodo de muestreo fportadora
// float32 w0p_ant=0;

// //###########################################################################

// //###########################################################################
// float32 ref_corr=0;
// float32 error_corr=0;
// float32 error_corr_ant=0;
// float32 Out_PI_corr=0;
// float32 Out_PI_corr_ant=0;
// float32 V_out=0;
// float32 m=0.8;
// float32 Ip=0;
// float32 b1=51.72/11.5;
// float32 b2=-51.68/11.5;

// //###########################################################################
// //Variables control tensi�n
// //###########################################################################
// float32 ref_ten=0;
// float32 Vm=0;
// float32 error_ten=0;
// float32 error_ten_ant=0;
// float32 Out_PI_ten=0;
// float32 Out_PI_ten_ant=0;
// float32 c1=5.188;
// float32 c2=-4.833;

// float32 Visualizacion[168];
// float32 Visualizacion1[168];
// float32 Visualizacion2[168];
// //###########################################################################
// //						main code
// //###########################################################################
// void main(void)
// {
//     //unsigned long i;

//    InitSysCtrl();	// Basic Core Init from DSP2833x_SysCtrl.c

// 	//EALLOW;
//    //	SysCtrlRegs.WDCR= 0x00AF;	// Re-enable the watchdog
//   // EDIS;			// 0x00AF  to NOT disable the Watchdog, Prescaler = 64

// 	DINT;				// Disable all interrupts

// 	Gpio_select();		// GPIO9, GPIO11, GPIO34 and GPIO49 as output
// 					    // to 4 LEDs at Peripheral Explorer Board
// 	Config_ADC ();
// 	Setup_ePWM1();		// init of ePWM1A

// 	InitPieCtrl();		// basic setup of PIE table; from DSP2833x_PieCtrl.c
// 	   IER = 0x0000;
// 	   IFR = 0x0000;

// 	InitPieVectTable();	// default ISR's in PIE

// 	EALLOW;
// 	PieVectTable.EPWM1_INT = &ePWM1A_compare_isr;
// 	EDIS;

// 	// Enable EPWM1A INT in the PIE: Group 3 interrupt 1
//    	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

// 	IER |=4;			// enable INT3 for ePWM1

// 	EINT;
// 	ERTM;
// 	 //GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
// 	// GpioDataRegs.GPBSET.bit.GPIO34 = 1;
// 	 while(1)
// 	     {
// 	         EALLOW;
// 	         SysCtrlRegs.WDKEY = 0x55;   // service WD #1
// 	         EDIS;
// 	 if (ena==0){
// 	                                EALLOW;
// 	                                EPwm1Regs.TZCLR.bit.OST = 1;            //Para desbloquear PWM1A y !B
// 	                                EPwm2Regs.TZCLR.bit.OST = 1;            //Para desbloquear PWM1A y !B
// 	                                EDIS;

// 	 }

// 	 else {

// 	                                    EALLOW;
// 	                                    EPwm1Regs.TZCLR.bit.OST = 0;            //Para bloquear PWM1A y !B
// 	                                    EPwm2Regs.TZCLR.bit.OST = 0;            //Para bloquear PWM1A y !B
// 	                                    EDIS;

// 	 }


// 	         //GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1; // toggle LD2
// 	         //   GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1; // toggle LD3
// 	         // for (i=0; i<f; i++); // time delay
// 	     }

// }

// void Gpio_select(void)
// {
// 	EALLOW;
// 	GpioCtrlRegs.GPAMUX1.all = 0;		// GPIO15 ... GPIO0 = General Puropse I/O
// 	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;	// ePWM1A active
// 	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1; // ePWM1B active
// 	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1; // ePWM1A active
// 	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1; // ePWM1B active
// 	GpioCtrlRegs.GPAMUX2.all = 0;		// GPIO31 ... GPIO16 = General Purpose I/O
// 	GpioCtrlRegs.GPBMUX1.all = 0;		// GPIO47 ... GPIO32 = General Purpose I/O
// 	GpioCtrlRegs.GPBMUX2.all = 0;		// GPIO63 ... GPIO48 = General Purpose I/O
// 	GpioCtrlRegs.GPCMUX1.all = 0;		// GPIO79 ... GPIO64 = General Purpose I/O
// 	GpioCtrlRegs.GPCMUX2.all = 0;		// GPIO87 ... GPIO80 = General Purpose I/O

// 	GpioCtrlRegs.GPADIR.all = 0;
// 	GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;	// peripheral explorer: LED LD1 at GPIO31
// 	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;	// peripheral explorer: LED LD2 at GPIO11


// 	GpioCtrlRegs.GPBDIR.all = 0;		// GPIO63-32 as inputs
// 	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;	// peripheral explorer: LED LD3 at GPIO34
// 	GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1; // peripheral explorer: LED LD4 at GPIO49
// 	GpioCtrlRegs.GPCDIR.all = 0;		// GPIO87-64 as inputs
// 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 	     GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;//resistencia Pull Up entrada Tz1
// 	     GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;//resistencia Pull Up entrada pin14
// 	    // GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;
// 	        //GpioCtrlRegs.GPADIR.bit.GPIO13 =0;

// 	        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;   //GPIO17 trabajar� como ==> TZ1 binario 11 decomal 3, ver diapositiva entrada salidas
// 	       // GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;   //GPIO17 trabajar� como ==> TZ2 binario 11 decomal 3, ver diapositiva entrada salidas
// 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 	EDIS;
// }

// void Setup_ePWM1(void)
// {
// 	EPwm1Regs.TBCTL.bit.CLKDIV =  0;	// CLKDIV = 1
// 	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;	// HSPCLKDIV = 1
// 	EPwm1Regs.TBCTL.bit.CTRMODE = 2;	// up - down mode

// 	EPwm1Regs.AQCTLA.all = 0x0060;		// set ePWM1A on CMPA up
// 										// clear ePWM1A on CMPA down
// 	EPwm1Regs.TBPRD = 7440; //3125;				// timer period for 24 KHz
// 										// TBPRD = 1/2 ( 150 MHz / 24 kHz)
// 	EPwm1Regs.CMPA.half.CMPA = EPwm1Regs.TBPRD / 2;	// 50% duty cycle first

// 	EPwm1Regs.ETSEL.all = 0;
// 	tEPwm1Regs.ETSEL.bit.INTEN = 1;		// interrupt enable for ePWM1
// 	EPwm1Regs.ETSEL.bit.INTSEL = 5;		// interrupt on CMPA down match
// 	EPwm1Regs.ETPS.bit.INTPRD = 1;		// interrupt on first even

// 	EPwm1Regs.DBCTL.bit.OUT_MODE = 3; // enable Dead-band module
// 	EPwm1Regs.DBCTL.bit.POLSEL = 2; // Active Hi complementary
// 	EPwm1Regs.DBCTL.bit.IN_MODE = 0;
// 	EPwm1Regs.DBFED = 300; // FED = 75 TBCLKs
// 	EPwm1Regs.DBRED = 300;
// 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 	    EALLOW;
// 	        EPwm1Regs.TZCTL.bit.TZA = 2;            //forza a bajo
// 	        EPwm1Regs.TZCTL.bit.TZB = 2;            //forza a bajo

// 	        EPwm1Regs.TZSEL.bit.OSHT1 = 1;          //Un solo disparo por TZ1
// 	       // EPwm1Regs.TZSEL.bit.OSHT2 = 1;
// 	    //  EPwm1Regs.TZSEL.bit.CBC6 = 1;           //Por ciclo al pulsar TZ6   OJO se genera una bandera que hay que limpiar (mirar la interrupci�n)
// 	    //  EPwm1Regs.TZEINT.bit.CBC = 1;           //habilita la interrupci�n por CBC para el trip zone y de la interrupci�n generada
// 	        EPwm1Regs.TZFRC.bit.OST = 1;            //Forzado por software por un solo evento (hasta que se limpie la bandera, en el main se limpiar�)

// 	        EDIS;
// 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// 	//Configuraci�n PWM2
// 	    EPwm2Regs.TBCTL.bit.CLKDIV = 0;         // CLKDIV =1
// 	    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;      // HSPCLKDIV =1
// 	    EPwm2Regs.TBCTL.bit.CTRMODE = 2;        // Contador Ascendente Descendente

// 	    EPwm2Regs.AQCTLA.all = 0x0060;       // set ePWM1A on CMPA up
// 	                                            // clear ePWM1A on CMPA down
// 	        EPwm2Regs.TBPRD = 7440;//3125;             // timer period for 24 KHz
// 	                                            // TBPRD = 1/2 ( 150 MHz / 24 kHz)
// 	        EPwm2Regs.CMPA.half.CMPA = EPwm1Regs.TBPRD / 2; // 50% duty cycle first

// 	        EPwm2Regs.DBCTL.bit.OUT_MODE = 3; // enable Dead-band module
// 	            EPwm2Regs.DBCTL.bit.POLSEL = 2; // Active Hi complementary
// 	            EPwm2Regs.DBCTL.bit.IN_MODE = 0;
// 	            EPwm2Regs.DBFED = 300; // FED = 300 TBCLKs
// 	            EPwm2Regs.DBRED = 300;
// 	            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 	            EALLOW;
// 	                                    EPwm2Regs.TZCTL.bit.TZA = 2;            //forza a bajo
// 	                                    EPwm2Regs.TZCTL.bit.TZB = 2;            //forza a bajo

// 	                                    EPwm2Regs.TZSEL.bit.OSHT1 = 1;          //Un solo disparo por TZ1
// 	                                   // EPwm1Regs.TZSEL.bit.OSHT2 = 1;
// 	                                //  EPwm1Regs.TZSEL.bit.CBC6 = 1;           //Por ciclo al pulsar TZ6   OJO se genera una bandera que hay que limpiar (mirar la interrupci�n)
// 	                                //  EPwm1Regs.TZEINT.bit.CBC = 1;           //habilita la interrupci�n por CBC para el trip zone y de la interrupci�n generada
// 	                                    EPwm2Regs.TZFRC.bit.OST = 1;            //Forzado por software por un solo evento (hasta que se limpie la bandera, en el main se limpiar�)
// 	                                    EDIS;
// 	            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// }

// interrupt void ePWM1A_compare_isr(void)
// // ISR runs every 41667 ns (PWM-frequency = 24 KHz)
// // and is triggered by ePWM1 compare event
// // run - time of ISR is 630 ns
// {


// 	//static  long delay=0;


//    	// Service watchdog every interrupt
//    //	EALLOW;
// 	//SysCtrlRegs.WDKEY = 0xAA;		// Service watchdog #2
// 	//EDIS;

// CapturaADC (&Co_inductor,&Vol_Capacitor,&Vol_Carga);//llama la funci�n

//   theta = j * 0.0374;
//   Vol_Sync =1*sin(theta); //remplazo del adc se�al tomada por el sensor
//  j++;         // use next element out of lookup table
//  if (j >167){ j = 0;}

//  // Vol_Capacitor =0;
//  //Co_inductor=0;
//  //Vol_Carga=Vol_Sync;

//  GpioDataRegs.GPADAT.bit.GPIO31 = GpioDataRegs.GPADAT.bit.GPIO14;
//   ena= GpioDataRegs.GPADAT.bit.GPIO14;
//   if (ena==0)
//                           {
//         coseno=cos_ant*0.9630-0.963*Vol_Carga+sin_ant;//generaci�n de se�ales en cuadratura
//         vd=Vol_Carga*cos(thetap)+coseno*sin(thetap);//se�ales en cuadratura- entrada del PIPLL
//         vq=-Vol_Carga*sin(thetap)+coseno*cos(thetap);//se�ales en cuadratura
//         pipll=pipll_ant+a1*vd-vd_ant*a2;//salida PIpll
//         w0p=pipll+w0;//entrada del integrador
//         thetap=w0p_ant*Ts+thetap_ant;//salida pll
//            if (thetap>=2*3.1416)
//                  {
//             thetap= thetap-(2 * 3.1416);
//                  }

//            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Pi tensi�n
//               ref_ten=Vm*sin(theta);
//               error_ten=ref_ten-Vol_Capacitor;
//               ref_corr==error_ten*c1+error_ten_ant*c2+Out_PI_ten_ant;

//               //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Pi corriente


//     //ref_corr=Ip*sin(thetap);
//        error_corr=ref_corr-Co_inductor;

//   Out_PI_corr=error_corr*b1+error_corr_ant*b2+0.94*Out_PI_corr_ant;

//   V_out=(Out_PI_corr+Vol_Capacitor)/15;


// 	//seno =V_out;
// 	//seno2=-V_out;

// 	seno =m*sin(thetap);
// 	seno2=-m*sin(thetap);

// 	CompA = (seno + 1) * EPwm1Regs.TBPRD / 2;
// 	CompA2 = (seno2 + 1) * EPwm2Regs.TBPRD / 2;
// 	EPwm1Regs.CMPA.half.CMPA = CompA;
//     EPwm2Regs.CMPA.half.CMPA = CompA2;



//                                                vd_ant=vd;
//                                                vq_ant=vq;
//                                                pipll_ant=pipll;
//                                                sin_ant=Vol_Carga;
//                                                cos_ant=coseno;
//                                                thetap_ant=thetap;
//                                                w0p_ant=w0p;
//                                     error_corr_ant=error_corr;
//                                     Out_PI_corr_ant=Out_PI_corr;
//                                     //%%%%%%%%%%%%%%%%% Memoria del Pi tension

//                                      error_ten_ant=error_ten;
//                                      Out_PI_ten_ant=ref_corr;
//                          }
//   else {

//       CompA = (0 + 1) * EPwm1Regs.TBPRD / 2;
//           CompA2 = (0 + 1) * EPwm2Regs.TBPRD / 2;
//           EPwm1Regs.CMPA.half.CMPA = CompA;
//           EPwm2Regs.CMPA.half.CMPA = CompA2;
//   }
//            Visualizacion[j]=error_corr;
//               Visualizacion1[j]=Co_inductor;
//               Visualizacion2[j]=Vol_Capacitor;
//     //Finally, we have to clear the interrupt flags of the event trigger module and the PIE-unit:

// 	EPwm1Regs.ETCLR.bit.INT = 1;		// Clear ePWM1 Interrupt flag

//    	// Acknowledge this interrupt to receive more interrupts from group 3
//    	PieCtrlRegs.PIEACK.all = 4;




// }

// void Config_ADC (void)
// {
//     InitAdc ();

//     AdcRegs.ADCTRL1.all = 0;                //limpia al iniciar
//     AdcRegs.ADCTRL1.bit.ACQ_PS = 7;         //Ventana de adquisici�n = (ACQ_PS+1)(1/ADCCLK)  7 = 8 x 1/ADCCLK
//     AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;       //En cascada 1 --> (SEQ1+SEQ2=SEQ)
//     AdcRegs.ADCTRL1.bit.CPS = 0;            //0: ADCCLK = FCLK/1. Divide entre 1
//     AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       //Modo carrera simple, es decir, lo corre una sola vez

//     AdcRegs.ADCTRL2.all = 0;                //limpia al iniciar
//     AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;   //Habilitar interrupci�n (SEQ1)
//     AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1; //Puede ser iniciada por el disparo del ePWM1 SOC a SEQ1
//     AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 =0;   //Interrupci�n despu�s de cada fin de secuencia
//     //AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ = 1;    //Habilita inicio de conversi�n de la secuencia 1 mediante PWM SOCB

//     AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;       //ADC CLOCK FCLK = HSPCLK /2 * ADCCLKPS 12.5 MHz
//     //AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;
//     AdcRegs.ADCMAXCONV.all = 3;             //N�mero m�x. de conversiones a hacer m�s una

//     AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;    //Canal ADCINA0   //para pr�ct potenci�m en PIN 57  //Para inversor: Sensor Tensi�n Capacitor
//     AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;    //Canal ADCINA1   //para pr�ct potenci�m en PIN 59  //Para inversor: Sensor Corriente Inductor Isesnseout
//     AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;  //Canal ADCINA2   //                              //Para inversor: Sensor Corriente entrada isenseIn

// }


// /// Interrupcion JuanPablo

// #define DAC1 25 //puerto GPIO usado
// //configuracion del controlador
//   double e[2]={0.0,0.0},u[2]={0.0,0.0};
//   double k=-5.3043;
//   double a=-0.7391;
//   double b=-0.9672;
//   int temp1=0;
// //prueba 1 muestreador retenedor ADC DAC
// //parte relacionada a la interrupcion
// hw_timer_t *Timer0_Cfg = NULL;
// int T, PRSC;//parametros para configurar timer
// //parte relacionada al ADC (12 bits de resolucion)
// const int ADC_Pin = 15;
// int ADC_Value = 0;
// //parte relacionada al DAC (8 bits de resolucion)
// int DAC_Value = 0;
// void IRAM_ATTR Timer0_ISR() {
//   ADC_Value = analogRead(ADC_Pin);//Lee ADC//DAC_Value = ADC_Value >> 4;//Asigna al DAC
//   //asignamos lectura del ADC
//   e[0]= 7.273*((3.3/4095)*double(ADC_Value)-1.65);
//   //calculamos u[k]
//   u[0]= k*e[0]+k*b*e[1]-a*u[1];//u[0]=k*e[0]-a*u[1];
//   //ajustamos a la cantidad de bits del DAC
//   temp1 = int((255/3.3)*(0.1375*u[0]+1.65));
//   if(temp1>=0 && temp1<=255){
//     DAC_Value=temp1;
//   }
//   //imprime voltaje
//   dacWrite(DAC1, DAC_Value);
//   //actualizamos variables
//   u[1]=u[0];
//   e[1]=e[0];
//   //Serial.println(DAC_Value);
//   //delay(100);
// }
// void setup() {
//   //configuracion de la interrupcion
//   T = 50;   //tiempo de muestreo en milisegundos
//   T = ((T)*1000);
//   PRSC = 80;//el reloj base del timer0 es de 80MHz
//   //inicializa el timer
//   Timer0_Cfg = timerBegin(0, PRSC, true);
//   //configura la interrupción
//   timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);  
//   timerAlarmWrite(Timer0_Cfg, T, true);
//   timerAlarmEnable(Timer0_Cfg);
    
// }

// void loop() {
    
// }

