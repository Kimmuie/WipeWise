#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 10
#define RST_PIN 96
MFRC522 mfrc522(SS_PIN, RST_PIN);
// Setup variables:
int buzzPin = 3;
bool cardDetected = false;
int turn = 1;
Servo myservo;
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(buzzPin, OUTPUT);
  pinMode(8, OUTPUT);
  myservo.attach(9);
  myservo.write(0);
}
void loop()
{
  if (!mfrc522.PICC_IsNewCardPresent()) {
    if (cardDetected) {
      Serial.println("Card removed, ready for new card.");
      cardDetected = false;
    }
    return;
  }
  if (!cardDetected) {
    cardDetected = true;
    Serial.println("Card found!");
    Serial.println();
    // Buzzer
    analogWrite(buzzPin, 20);
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    analogWrite(buzzPin, 0);
    if (turn % 2 == 0){
    myservo.write(90);
    delay(1000);
    myservo.write(180);
    }else{
    myservo.write(90);
    delay(1000);
    myservo.write(0);
    }
    turn =  turn + 1;
  }
}