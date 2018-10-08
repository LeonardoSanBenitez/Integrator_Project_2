#include <Ultrasonic.h>     //Carrega a biblioteca do sensor ultrassonico
#include <LiquidCrystal.h>  //Carrega a biblioteca LiquidCrystal
#include <SPI.h>			//to ethernet
#include <Ethernet.h>
#include "pinout.h"


/** STATE DEFINITIONS **/
#define WAIT        0
#define MOVE_IN     1
#define READ_COLOR  2
#define READ_HEIGHT 3
#define MOVE_OUT    4


/** GENERAL DEFINITIONS **/
#define MOTOR_OFF 0
#define MOTOR_ON  150


/** GLOBAL VARIABLES **/
//Servo myservo;  // Create servo object to control a servo
char state = 0; // To the state machine
float cmMsec;

char team[]="Elvis";
char instaled[]="LTPA";
int volume= 50;
char color[] = "2";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };	// assign a MAC address for the ethernet controller.
char server[] = "pi2engenharia.000webhostapp.com";
IPAddress ip(145, 14, 145, 236);						// Set the static IP address to use if the DHCP fails to assign
IPAddress myDns(192, 168, 0, 1);


/** INITIALIZATIONS **/
Ultrasonic ultrasonic(pino_trigger, pino_echo); 		//Inicializa o sensor nos pinos definidos acima
LiquidCrystal lcd(42, 44, 46, 48, 50, 52);    			//Define os pinos que serão utilizados para ligação ao display
EthernetClient client;

/*---------------------------------------------------------------------
  SETUP
---------------------------------------------------------------------*/
void setup() {

  lcd.begin(16, 2);         //Define o número de colunas e linhas do LCD
  lcd.clear();              //Limpa a tela

  //myservo.attach(9);
  pinMode(INFRA_1, INPUT);
  pinMode(INFRA_2, INPUT);
  pinMode(INFRA_3, INPUT);
  pinMode(MOTOR_A, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  analogWrite(MOTOR_A, 0);

  Ethernet.init(10);  // Most Arduino shields
  Serial.begin(9600);
  while (!Serial) {;}

  /** START THE ETHERNET CONNECTION **/
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);
  
  /** WELCOME PRINT **/
  Serial.println("Welcome to PI-2!!!");
  Serial.println("waiting...");
  delay(100);
  lcd.begin(16, 2);
  lcd.clear();   // clear old screen data
  lcd.print ("PI-2 Elvis / Leo ");
}

/*---------------------------------------------------------------------
  LOOP
---------------------------------------------------------------------*/
void loop() {
  delay(20);
  switch (state) {
    /** State Wait: will do nothing until the infrared sensor 1 (positioned in the begin of the conveyor) detect the object*/
    case WAIT:
      if (analogRead(INFRA_1) < 200) {
        Serial.println("Object detected");
        lcd.setCursor(0, 1);         // (column 0) of the second line (line 1):
        lcd.clear();
        lcd.print ("motor ligado");
        sound_alert();
        analogWrite(MOTOR_A, MOTOR_ON);
        state = MOVE_IN;
      } else if (client.available()) {
		char c = client.read();
		Serial.write(c);
	  }
      break;
    
    /** State Move In: keep the DC motor running until the object reach the infrared sensor 2*/
    case MOVE_IN:
      if (analogRead(INFRA_2) < 200) {
        analogWrite(MOTOR_A, MOTOR_OFF);
        state = READ_COLOR;
      }
      break;
    
    /** State Read Color: just call the read_color() funcion*/
    case READ_COLOR:
      Serial.print("Color: ");
      Serial.println(read_color() == 1 ? "red" : "blue");
      state = READ_HEIGHT;
      break;
    
    /** State read height: just call the read_height() function. Does not calculates the volume, that is done in the server */
    case READ_HEIGHT:
      cmMsec = ultrasonic.distanceRead();
      lcd.setCursor(0, 1);                  // (column 0) of the second line (line 1):
      lcd.clear();
      lcd.print ("Dist: ");                 //print in LCD
      lcd.print (cmMsec);        
      Serial.print("Altura lida (em cm):"); //Print in serial
      Serial.println(cmMsec);
      delay(1000); 
      analogWrite(MOTOR_A, MOTOR_ON);
    state = MOVE_OUT;
      break;
    
    /** State move out: move the motor until the object reach infrared sensor 3*/
    case MOVE_OUT:
      if (analogRead(INFRA_3) < 200) {
        analogWrite(MOTOR_A, MOTOR_OFF);
        Serial.println("Process finished\n");
        lcd.setCursor(0, 1);         // (column 0) of the second line (line 1):
        lcd.clear();
        lcd.print ("Process finished");
        sound_alert();
		httpRequest();
        state = WAIT;
      }
  }
}

/*---------------------------------------------------------------------
  FUNCTION SOUND ALERT
  Double beet in a buzzer
  ---------------------------------------------------------------------*/
void sound_alert() {
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
}

/*---------------------------------------------------------------------
  FUNCTION READ COLOR
  Sensor used: TCS 230
  Return: 1=red, 2=blue, 3=green
  ---------------------------------------------------------------------*/
int read_color() {
  return 1;
}

/*---------------------------------------------------------------------
  FUNCTION READ HEIGHT
  Sensor used: HC-SR04
  ---------------------------------------------------------------------*/
//int read_height() {
//  {
//    //Le as informacoes do sensor ultrassonico, em cm e polvoid loop(
//    float cmMsec, inMsec;
//    long microsec = ultrasonic.timing();
//    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
//    inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
//    //Exibe informacoes no serial monitor
//    Serial.print("Distancia em cm: ");
//    Serial.print(cmMsec);
//    Serial.print(" - Distancia em polegadas: ");
//    Serial.println(inMsec);
//    delay(1000);
//  }
//  return analogRead(POT);
//}





void httpRequest() {
  // close any connection before send a new request. This will free the socket on the WiFi shield
  client.stop();

  if (client.connect(server, 80)) {   // connect method return true if successful connection 
    Serial.println("connecting...");
    client.print("GET /API_data_receive.php?");
    client.print("team=");
    client.print(team);
    client.print("&instaled=");
    client.print(instaled);
    client.print("&volume=");
    client.print(volume);
    client.print("ml");
    client.print("&color=");
    client.print(color);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
    volume+=10;
  } else {
    Serial.println("connection failed");
  }
}






