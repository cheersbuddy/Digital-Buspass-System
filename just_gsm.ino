#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

void setup() {
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  Serial.println("Setup complete."); // Debug statement
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 's':
        Serial.println("Sending SMS..."); // Debug statement
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(1000);  // Delay of 1 second
        mySerial.println("AT+CMGS=\"+919688113385\""); // Replace x with mobile number
        delay(1000);
        mySerial.println("Technolab creation"); // The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
        delay(1000);
        break;

      case 'r':
        Serial.println("Receiving live SMS..."); // Debug statement
        mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
        delay(1000);
        break;
    }
  }

  if (mySerial.available() > 0) {
    Serial.write(mySerial.read());
  }
}
