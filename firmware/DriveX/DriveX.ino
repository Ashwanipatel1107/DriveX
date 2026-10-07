


#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(0, 1);  // RX, TX

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define EMl 6
#define MrL1 7
#define MrL2 8
#define MrR1 9
#define MrR2 10
#define EMr 11

#define TRIGGER_PIN  3  
#define ECHO_PIN     2  

#define Maxspeed 255
#define MAX_DISTANCE 200 
#define servoSpeed 10  // lower is faster

short mode = 0;

Servo myservo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {

 Serial.begin(9600);
 BT.begin(9600);

 pinMode(EMl, OUTPUT);
 pinMode(MrL1, OUTPUT);
 pinMode(MrL2, OUTPUT);
 pinMode(MrR1, OUTPUT);
 pinMode(MrR2, OUTPUT);
 pinMode(EMr, OUTPUT);

 myservo.attach(5);

  lcd.init();        // Initialize LCD
  lcd.backlight();   // Turn on backlight

  STOP();
  delay(2000);
  myservo.write(90);
  
}


 void FORWARD(){

    digitalWrite(MrL1, HIGH);
    digitalWrite(MrL2, LOW);
    digitalWrite(MrR1, HIGH);
    digitalWrite(MrR2, LOW);

    analogWrite(EMl, Maxspeed);
    analogWrite(EMr, Maxspeed);
    

  }

  void BACKWARD(){
    digitalWrite(MrL1, LOW);
    digitalWrite(MrL2, HIGH);
    digitalWrite(MrR1, LOW);
    digitalWrite(MrR2, HIGH);

    analogWrite(EMl, Maxspeed);
    analogWrite(EMr, Maxspeed);

  }

  void STOP(){
    digitalWrite(MrL1, LOW);
    digitalWrite(MrL2, LOW);
    digitalWrite(MrR1, LOW);
    digitalWrite(MrR2, LOW);

    analogWrite(EMl, 0);
    analogWrite(EMr, 0);

  }

  void LEFT(){
    digitalWrite(MrL1, HIGH);
    digitalWrite(MrL2, LOW);
    digitalWrite(MrR1, LOW);
    digitalWrite(MrR2, HIGH);

    analogWrite(EMl, Maxspeed);
    analogWrite(EMr, Maxspeed);

  }

  void RIGHT(){
    digitalWrite(MrL1, LOW);
    digitalWrite(MrL2, HIGH);
    digitalWrite(MrR1, HIGH);
    digitalWrite(MrR2, LOW);

    analogWrite(EMl, Maxspeed);
    analogWrite(EMr, Maxspeed);

  }

  void btLcd(){
    lcd.setCursor(0, 0);
    lcd.print("Bluethoot Mode  ");
    
  }

  void obLcd(){
  lcd.setCursor(0, 0);
  lcd.print("obMode |Dist:");
  lcd.setCursor(0, 1);
  lcd.print("Left");
  lcd.setCursor(6, 1);
  lcd.print(" |Right");
  }

void bluethootMode(){
  btLcd();
  if (BT.available()) {
  char Data = BT.read();
  Serial.println(Data);

  if (Data == 'F') { lcd.setCursor(0, 1); lcd.print("FORWARD        "); FORWARD(); }
  else if (Data == 'B') { lcd.setCursor(0, 1); lcd.print("BACKWARD        "); BACKWARD();}
  else if (Data == 'R') { lcd.setCursor(0, 1); lcd.print("RIGHT           "); RIGHT();}
  else if (Data == 'L') { lcd.setCursor(0, 1); lcd.print("LEFT            "); LEFT();}
  else if (Data == 'S') { lcd.setCursor(0, 1); lcd.print("STOP            "); STOP();}
  else if (Data == 'X') { mode = 1; return; }
  else { lcd.setCursor(0, 1); lcd.print("Invalid Input"); STOP(); }
  }

}

void obsticalMode() {
 obLcd();
 myservo.write(90);
 if (BT.available()) {
   char obData = BT.read();
   if(obData == 'x') { mode = 0; STOP(); return; }
 }else{
    int distance = sonar.ping_cm();
    int rightDistance = 0;
    int leftDistance = 0;

    Serial.print("distance: ");
    Serial.print(distance);
    Serial.print("cm \n");   

    lcd.setCursor(13, 0);
    lcd.print(distance); 

    if(distance > 10 || distance == 0){
      FORWARD();
    }else {
      STOP();
      delay(500);
      BACKWARD();
      delay(300);
      STOP();
      delay(500);


      for(int i=90; i>=0; i-=2){   
       myservo.write(i);
       delay(servoSpeed);
      }
      delay(500);
      rightDistance = sonar.ping_cm();
      lcd.setCursor(13, 1);
      lcd.print(rightDistance);

      for(int i=0; i<=180; i+=2){   
       myservo.write(i);
       delay(servoSpeed);
      }      
      delay(500);
      leftDistance = sonar.ping_cm();
      lcd.setCursor(4, 1);
      lcd.print(leftDistance);

      for(int i=180; i>=90; i-=2){   
       myservo.write(i);
       delay(servoSpeed);
      }
      delay(500);
             
      if(rightDistance > leftDistance || rightDistance ==0 ){
        RIGHT();
        delay(650);
        STOP();
        delay(800);
      }else {
        LEFT();
        delay(650);
        STOP();
        delay(800);
        }
    } 
  }  
}


void loop(){

  if(mode == 0){
    bluethootMode();
  }else {
    obsticalMode();
  }

}
