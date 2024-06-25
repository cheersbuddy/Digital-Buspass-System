#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);
//byte accessUID[4] = {0x13, 0x4C, 0x10, 0xF5};
byte accessUID[][4] = {
  {0x13, 0x4C, 0x10, 0xF5},  // Existing UID 0x13
  {0xF3, 0x5B, 0x31, 0xFC}   // New UID
};
int numOfUIDs = sizeof(accessUID) / sizeof(accessUID[0]);  // Number of UID values
int GreenPin = 2;
int RedPin = 3;
//int buzzerPin = 4;
int accessLimit = 100;  // Number of accesses allowed per day

SoftwareSerial mySerial(9, 10);  // RX, TX for GSM module

unsigned long lastAccessMillis = 0;
const long dayInterval = 86400000;  // One day in milliseconds

void setup() {
  pinMode(GreenPin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  //pinMode(buzzerPin, OUTPUT);
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
  delay(50);

  // Initialize EEPROM
  if (EEPROM.read(0) == 255) {
    EEPROM.write(0, 0);  // Initialize access count to 0
  }
}

void sendSMS(String message) {
  mySerial.println("AT+CMGF=1");
  delay(1000);

  mySerial.println("AT+CMGS=\"+919688113385\"\r");
  delay(1000);

  mySerial.print(message);
  delay(500);

  mySerial.write((char)26); // Ctrl+Z to send the message
  delay(1000);

  // Wait for response from GSM module
  unsigned long timeout = millis();
  while (!mySerial.available() && millis() - timeout < 5000) {
    // Wait for response or timeout after 5 seconds
  }

  // Read response from GSM module
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }

  delay(100); // Delay for stability
}

void updateAccessCount() {
  unsigned long currentMillis = millis();  // Get the current time

  // Check if a new day has started
  if (currentMillis - lastAccessMillis >= dayInterval) {
    EEPROM.write(0, 0);  // Reset the access count for the new day
    lastAccessMillis = currentMillis;  // Update lastAccessMillis
  }

  // Read the access count from EEPROM
  int accessCount = EEPROM.read(0);

  // Increment the access count
  accessCount++;

  // Write the updated access count to EEPROM
  EEPROM.write(0, accessCount);
}


bool isCardValid() {
  // Read access count from EEPROM
  int accessCount = EEPROM.read(0);

  // Check if access count is less than the access limit
  return accessCount < accessLimit;
}

  

void accessGrantedAction() {
  bool cardValid = isCardValid();  // Check if the card is valid
  
  if (cardValid) {
    //Serial.println("Access Granted");
    updateAccessCount();  // Update the access count in EEPROM
    

    digitalWrite(GreenPin, HIGH);
    //tone(buzzerPin, 1000, 200);
    delay(100);
    digitalWrite(GreenPin, LOW);
    //noTone(buzzerPin);
    sendSMS("Name:Sowmiya \n Access:Granted \n "); // Send SMS for Access Granted
    Serial.println("Sending SMS - Access Granted");
  } else {
    Serial.println("Card limit exceeded - Access Denied");
    accessDeniedAction();  // Implement access denied action
  }
}


void accessDeniedAction() {
  //Serial.println("Access Denied");
  
  // Send SMS for Access Denied

  digitalWrite(RedPin, HIGH);
  //digitalWrite(buzzerPin, HIGH);
  //tone(buzzerPin, 800, 1000);
  delay(100);
  digitalWrite(RedPin, LOW);
  //noTone(buzzerPin);
  sendSMS("Access Denied");
  Serial.println("Sending SMS - Access Denied");


 // digitalWrite(buzzerPin, LOW);
}

void loop() {
  delay(50);
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
    bool accessGranted = false;
  
  // Loop through all stored UID values
  for (int i = 0; i < numOfUIDs; i++) {
    if (memcmp(mfrc522.uid.uidByte, accessUID[i], 4) == 0) {
      accessGranted = true;
      break;  // Exit the loop if a matching UID is found
    }
  }

  if (accessGranted) {
    accessGrantedAction();
  } else {
    accessDeniedAction();
  }

 /* if (mfrc522.uid.uidByte[0] == accessUID[0] && mfrc522.uid.uidByte[1] == accessUID[1] && mfrc522.uid.uidByte[2] == accessUID[2] && mfrc522.uid.uidByte[3] == accessUID[3]) {
    accessGrantedAction();
  } else {
    accessDeniedAction();
  }*/

  mfrc522.PICC_HaltA();
}