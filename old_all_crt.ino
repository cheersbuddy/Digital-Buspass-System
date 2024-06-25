#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte accessUID[4] = {0x13, 0x4C, 0x10, 0xF5};
int GreenPin = 2;
int RedPin = 3;
int buzzerPin = 4;
int accessLimit = 2;  // Number of accesses allowed per day

SoftwareSerial mySerial(9, 10);  // RX, TX for GSM module

unsigned long lastAccessMillis = 0;
const long dayInterval = 86400000;  // One day in milliseconds

void setup() {
  pinMode(GreenPin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(RedPin, LOW);
  digitalWrite(GreenPin, LOW);
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  mySerial.begin(9600);
  delay(100);

  // Initialize EEPROM
  if (EEPROM.read(0) == 255) {
    EEPROM.write(0, 0);  // Initialize access count to 0
  }

  // Ensure LEDs are initially off
  digitalWrite(GreenPin, LOW);
  digitalWrite(RedPin, LOW);
}

void sendSMS(String message) {
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+919688113385\"\r");
  delay(1000);
  mySerial.println(message);
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}

void updateAccessCount() {
  int accessCount = EEPROM.read(0);  // Read access count from EEPROM

  // Check if a new day has started
  if (millis() - lastAccessMillis >= dayInterval) {
    accessCount = 0;  // Reset the access count for the new day
    lastAccessMillis = millis();  // Update lastAccessMillis
  }

  accessCount++;  // Increment the access count

  EEPROM.write(0, accessCount);  // Write the updated access count to EEPROM
}

bool isCardValid() {
  int accessCount = EEPROM.read(0);  // Read access count from EEPROM
  return accessCount < accessLimit;
}

void accessGrantedAction() {
  Serial.println("Access Granted");

  if (isCardValid()) {
    updateAccessCount();  // Update the access count in EEPROM
    digitalWrite(GreenPin, HIGH);
    tone(buzzerPin, 1000, 200);
    delay(1500);
    digitalWrite(GreenPin, LOW);
    noTone(buzzerPin);

   // Serial.println("Sending SMS - Access Granted");

    // Send SMS for Access Granted
    sendSMS("Name:Sowmiya \n Access:Granted \n ");
  } else {
    Serial.println("Card limit exceeded - Access Denied");
    accessDeniedAction();  // Implement access denied action
  }

  // Ensure LEDs are turned off after actions are completed
  digitalWrite(GreenPin, LOW);
  digitalWrite(RedPin, LOW);
}

void accessDeniedAction() {
  Serial.println("Access Denied");
  digitalWrite(RedPin, HIGH);
  digitalWrite(buzzerPin, HIGH);
  tone(buzzerPin, 800, 1000);
  delay(1000);
  digitalWrite(RedPin, LOW);
  noTone(buzzerPin);

  //Serial.println("Sending SMS - Access Denied");
  // Send SMS for Access Denied
  sendSMS("Access Denied");

  // Ensure LEDs are turned off after actions are completed
  digitalWrite(GreenPin, LOW);
  digitalWrite(RedPin, LOW);
}

void loop() {
  delay(500);
  digitalWrite(GreenPin, LOW);
  digitalWrite(RedPin, LOW);
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  if (mfrc522.uid.uidByte[0] == accessUID[0] && mfrc522.uid.uidByte[1] == accessUID[1] && mfrc522.uid.uidByte[2] == accessUID[2] && mfrc522.uid.uidByte[3] == accessUID[3]) {
    accessGrantedAction();
  } else {
    accessDeniedAction();
  }

  mfrc522.PICC_HaltA();
}