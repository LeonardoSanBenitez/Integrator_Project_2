//#include <Ultrasonic.h>     //Carrega a biblioteca do sensor ultrassonico
#include <LiquidCrystal.h>  //Carrega a biblioteca LiquidCrystal
#include <SPI.h>      //to ethernet
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

/** GLOBAL VARIABLES **/ //TODO: criar uma função main()
char state = 0; // To the state machine
char team[]="Elvis";
char instaled[]="LTPA";
int altura;
int color = 1;
int red, green, blue, clean;
int nr, ng, nb;//TODO: remove

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // assign a MAC address for the ethernet controller.
char server[] = "pi2engenharia.000webhostapp.com";
IPAddress ip(145, 14, 145, 236);            // Set the static IP address to use if the DHCP fails to assign
//IPAddress myDns(192, 168, 0, 1);

/** RESOURCE DECLARATIONS **/
EthernetClient client;
LiquidCrystal lcd(30, 32, 34, 36, 38, 40);          //Define os pinos que serão utilizados para ligação ao display

/*---------------------------------------------------------------------
  SETUP
---------------------------------------------------------------------*/
void setup() {
  pinMode(INFRA_1, INPUT);
  pinMode(INFRA_2, INPUT);
  pinMode(INFRA_3, INPUT);
  pinMode(MOTOR_A, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode (S0, OUTPUT);
  pinMode (S1, OUTPUT);
  pinMode (S2, OUTPUT);
  pinMode (S3, OUTPUT);
  pinMode (OUT, INPUT);

  digitalWrite (S0, LOW);
  digitalWrite (S1, HIGH);

  digitalWrite(TRIGGER_PIN, LOW);
  analogWrite(MOTOR_A, MOTOR_OFF);

  /** SERIAL INIT **/
  Serial.begin(9600);
  while (!Serial) {;}
  Serial.println("Serial initialized");
  delay(100);

  /** START THE ETHERNET CONNECTION **/
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);  // try to congifure using IP address instead of DHCP:
  }
  Serial.println("Ethernet initialized");
  delay(1000);    // give the Ethernet shield a second to initialize

  /** START THE LCD **/
  lcd.clear();              //Limpa a tela
  lcd.begin(16, 2);         //Define o número de colunas e linhas do LCD
  lcd.print ("PI-2 Elvis / Leo ");
  Serial.println("Welcome to PI-2!!!");
  analogWrite(MOTOR_A, MOTOR_OFF);
}

/*---------------------------------------------------------------------
  LOOP
---------------------------------------------------------------------*/
void loop() {
  /* Local variables */
  int red, green, blue, clean;
  int nr, ng, nb;
  
  delay(20);
  switch (state) {
    /** State Wait: will do nothing until the infrared sensor 1 (positioned in the begin of the conveyor) detect the object*/
    case WAIT:
      analogWrite(MOTOR_A, MOTOR_OFF);
      if (analogRead(INFRA_1) < 200) {
        Serial.println("Object detected");
        lcd.setCursor(0, 1);         // (column 0) of the second line (line 1):
        lcd.clear();
        lcd.print ("motor ligado");
        sound_alert();
        analogWrite(MOTOR_A, MOTOR_ON);
        state = MOVE_IN;
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
      read_color (&red, &green, &blue, &clean);
      nr = (int)255*1.23*(float)clean/red;
      ng = (int)255*1.18*(float)clean/green;
      nb = (int)255*1.4*(float)clean/blue;
      
      lcd.setCursor(0, 1);                  // (column 0) of the second line (line 1):
      lcd.clear();
      lcd.print ("Cor: ?");                 //print in LCD
      Serial.print ("COLOR: rgb("); 
      Serial.print (nr);
      Serial.print (", ");
      Serial.print (ng);
      Serial.print (", ");
      Serial.print (nb);
      Serial.println (")");
      Serial.println("");
      state = READ_HEIGHT;
      break;
    
    /** State read height: just call the read_height() function. Does not calculates the volume, that is done in the server */
    case READ_HEIGHT:
      digitalWrite(TRIGGER_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIGGER_PIN, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
      delayMicroseconds(1000);
      digitalWrite(TRIGGER_PIN, LOW);
      altura= 137 - pulseIn(ECHO_PIN, HIGH)*0.34/2;// Reads the echoPin (returns the sound wave travel time in microseconds). Calculate the distance.
      if (altura<0 || altura>500) altura = 0;
      lcd.setCursor(0, 2);                  // (column 0) of the second line (line 1):
      lcd.print ("altura: ");                 //print in LCD
      lcd.print (altura);        
      Serial.print("Altura lida (em mm):"); //Print in serial
      Serial.println(altura);
      delay(1000); 
      analogWrite(MOTOR_A, MOTOR_ON);
    state = MOVE_OUT;
      break;
    
    /** State move out: move the motor until the object reach infrared sensor 3*/
    case MOVE_OUT:
      if (analogRead(INFRA_3) < 200) {
        analogWrite(MOTOR_A, MOTOR_OFF);
        lcd.setCursor(0, 1);         // (column 0) of the second line (line 1):
        lcd.clear();
        lcd.print ("Process finished");
        sound_alert();
        httpRequest();
        Serial.println("Process finished\n");
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
  Return: Pulse in return an unsigned long with the length of the pulse (in microseconds). 
  ---------------------------------------------------------------------*/
void read_color(int* red, int* green, int* blue, int* clean){
  /* Red Filter */
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  *red = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);

  /* Green Filter */
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  *green = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);
  
  /* Blue Filter */
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  *blue = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);

  /* Clean Filter */
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  *clean = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);
}


/*---------------------------------------------------------------------
  FUNCTION HTTP REQUEST
  Method used: GET
  ---------------------------------------------------------------------*/
void httpRequest() {
  // close any connection before send a new request. This will free the socket on the WiFi shield
  client.stop();

  Serial.print("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected!");
    // Make a HTTP request:
    client.print("GET /API_data_receive.php?");
    client.print("team=");
    client.print(team);
    client.print("&instaled=");
    client.print(instaled);
    client.print("&altura=");
    client.print(altura);
    client.print("ml");
    client.print("&color=");
    client.print(color);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
    Serial.println("Dados enviados para o servidor");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}












