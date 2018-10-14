#include <Ultrasonic.h> //Carrega a biblioteca do sensor ultrassonico


#include <LiquidCrystal.h> //Carrega a biblioteca LiquidCrystal
LiquidCrystal lcd(12, 11, 6, 4, 3, 2); //Define os pinos que serão utilizados para ligação ao display

//State definitions
#define WAIT        0
#define MOVE_IN     1
#define READ_COLOR  2
#define READ_HEIGHT 3
#define MOVE_OUT    4

//Pin definitions
#define INFRA_1 A1
#define INFRA_2 A2
#define INFRA_3 A3
#define BUZZER  5
#define POT     A0
#define MOTOR_A 10
#define MOTOR_B 11
#define pino_trigger 7 //sensor ultrassonico: (trigger no pino digital 7)
#define pino_echo 8    //sensor ultrassonico: (echo no pino digital 8)

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

//Global variables
//Servo myservo;  // Create servo object to control a servo
char state = 0; // To the state machine

/*---------------------------------------------------------------------
  FUNCTION MAIN
  ---------------------------------------------------------------------*/
int infra_1 = 0;
float cmMsec, inMsec;

void setup() {

  lcd.begin(16, 2);         //Define o número de colunas e linhas do LCD
  lcd.clear();              //Limpa a tela

  //myservo.attach(9);
  pinMode(INFRA_1, INPUT);
  pinMode(INFRA_2, INPUT);
  pinMode(INFRA_3, INPUT);
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(MOTOR_A, LOW);

  analogWrite(MOTOR_B, 150);

  Serial.begin(9600);
  Serial.println("Welcome to PI-2!!!");
  Serial.println("waiting...");
  delay(100);

    lcd.begin(16, 2);
  // clear old screen data
  lcd.clear();
  lcd.print ("PI-2 Elvis / Leo ");

}

void loop() {

  //Serial.println(INFRA_1);

  delay(20);

  switch (state) {
    /* State Wait: will do nothing until the infrared sensor 1 (positioned in the begin of the conveyor) detect the object*/
    case WAIT:
      //infra_1 = analogRead(A1);
      //Serial.println(infra_1);
      if (analogRead(INFRA_1) < 200) {
        Serial.println("Object detected");
        lcd.setCursor(0, 1);         // (column 0) of the second line (line 1):
        lcd.clear();
        lcd.print ("motor ligado");
        //Serial.println(analogRead(INFRA_1));
        sound_alert();
        //read_height();
        analogWrite(MOTOR_A, 150);
        state = MOVE_IN;
      }
      break;
    /* State Move In: just accionates the DC motor until the object reach the infrared sensor 2*/
    case MOVE_IN:
      if (analogRead(INFRA_2) <200) {
        analogWrite(MOTOR_A, 0);
        state = READ_COLOR;
      }
      break;
    /* State Read Color: just call the read_color() funcion*/
    case READ_COLOR:
      Serial.print("Color: ");
      Serial.println(read_color() == 1 ? "red" : "blue");
      state = READ_HEIGHT;
      break;
    /* State read height: just call the read_height() function. Does not calculates the volume, that is done in the server */
    case READ_HEIGHT:
      cmMsec = calculaAltura();
      lcd.setCursor(0, 1);                  // (column 0) of the second line (line 1):
      lcd.clear();
      lcd.print ("Dist: ");                 //print in LCD
      lcd.print (cmMsec);        
      Serial.print("Altura lida (em cm):"); //Print in serial
      Serial.println(cmMsec);
      delay(1000);
      state = MOVE_OUT;
      delay(2000); //just for debug...
      analogWrite(MOTOR_A, 150);
      break;
    /* State move out: will move the motor until the object reach infrared sensor 3*/
    case MOVE_OUT:
      if (analogRead(INFRA_3) < 200) {
        analogWrite(MOTOR_A, 0);
        Serial.println("Process finished\n");
        lcd.setCursor(0, 1);         // (column 0) of the second line (line 1):
        lcd.clear();
        lcd.print ("Process finished");
        sound_alert();
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

float calculaAltura()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  return (cmMsec);
}



