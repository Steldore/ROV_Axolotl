

// SimpleTxAckPayload - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


#include <SD.h>
File myFile;


#define CE_PIN   7
#define CSN_PIN 8

const byte slaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio


float sensdata[3]={};


//DATA TO SEND
struct Dirdata{
int dir;
int knob;
int sink;
};

Dirdata dirpack;

long previousMillis = 0; 
//===============

void setup() {
  
    Serial.begin(9600);
    
    lcd.begin(20,4);
    lcd.setCursor(4,0);
  lcd.print("WAITING...");

   pinMode(A1, INPUT_PULLUP);
   pinMode(A0, INPUT_PULLUP);




    radio.begin();
    radio.setDataRate( RF24_250KBPS );

    radio.enableAckPayload();

    radio.setRetries(15,15); // delay, count
    radio.openWritingPipe(slaveAddress);
    radio.stopListening();
}



void loop() {

navigationInputs();

radio.write(&dirpack,sizeof(Dirdata));

getTelemetry();
Serial.println(dirpack.dir);

  //if(radio.write(&dirpack,sizeof(Dirdata))){

  //}



}

void sdLog(){
  String dataString = "";
  SD.begin();
  myFile = SD.open("ROVLOG.txt", FILE_WRITE);
  
if(myFile){
  dataString = " Pressure ";
  dataString +=String(sensdata[0]);
  dataString += " Temperature ";
  dataString +=String(sensdata[1]);
  dataString += " Light ";
  dataString +=String(sensdata[2]);

  myFile.println(dataString);
  myFile.close();
}

//else{
//  Serial.println("Failed opening file");
//}
SD.end();

}

void printScreen(){    //Function for Printing Sensor Data to LCD
  lcd.setCursor(4,0);
  lcd.print("ROV SENSORS");

     
  lcd.setCursor(0,1);
  lcd.print("Temperature ");
  lcd.setCursor(13,1);
  lcd.print(sensdata[2]);
  
  lcd.setCursor(0,2);
  lcd.print("Light ");
  lcd.setCursor(13,2);
  lcd.print(sensdata[1]);

  lcd.setCursor(0,3);
  lcd.print("Pressure ");
  lcd.setCursor(13,3);
  lcd.print(sensdata[0]);
  
}


void navigationInputs(){                       //Function for Navigation data
dirpack.dir=analogRead(A1);
dirpack.knob=analogRead(A7);
dirpack.knob = map(dirpack.knob, 0, 1023, 155, 255);
dirpack.sink=analogRead(A0);
}


void getTelemetry(){
  
      unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > 10000) {
      previousMillis = currentMillis;
    
    if(radio.isAckPayloadAvailable()){
      radio.read(&sensdata,sizeof(sensdata));
//      Serial.print("received an Ack: ");
//      Serial.println(String(" Pressure ")+sensdata[0]+String(" LUX ")+sensdata[1]+String(" Temperature ")+sensdata[2]);
  printScreen();
  sdLog();

     } 
    }
}

