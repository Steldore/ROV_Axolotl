//testtest

// SimpleRxAckPayload- the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8

//NTC_THERMISTOR
int ThermistorPin = A3;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//LDR_LIGHTMETER
const int ldrPin = A2;


const byte thisSlaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN);

char msg[10];
float sensdata[3]={};


//DATA TO RECEIVE
struct Directions{
int dir;
int knob;
int sink;
};

Directions directionpack;


void setup() {
//INITIALISING SENSOR DATA
for(int i=0;i<=3;i++){
  int sensval =analogRead(i);
  sensval=sensdata[i];
}


    Serial.begin(9600);

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);

    radio.enableAckPayload();



    radio.startListening();

pinMode(A3, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);


pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(A4, OUTPUT);
pinMode(A5, OUTPUT);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);

}
void loop() {


if (radio.available()){
  radio.read(&directionpack,sizeof(Directions));
  radio.writeAckPayload(1,&sensdata,sizeof(sensdata));
  navigate();
Serial.println(directionpack.dir);

}

//navigate();

//Serial.println(directionpack.dir);
//Serial.println(directionpack.knob);
//Serial.println(directionpack.sink);





collectSensordata();

//Serial.println( sensdata[0]);
//Serial.println( sensdata[1]);
//Serial.println( sensdata[2]);
//Serial.println( "    ");
//delay(3000);


}

void navigate (){

  //DOWN
  if (directionpack.dir<100 && directionpack.dir>0){
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);

    analogWrite(6,directionpack.knob);

    if(directionpack.sink>100 && directionpack.sink<400){
    digitalWrite(A4,LOW);
    digitalWrite(A5,HIGH);
    }

    else if(directionpack.sink<100){
    digitalWrite(A4,HIGH);
    digitalWrite(A5,LOW);

    }
    else{
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
    }

  }

  //UP
  else if (directionpack.dir>300 && directionpack.dir<400){
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);

    analogWrite(6,directionpack.knob);

    if(directionpack.sink>100 && directionpack.sink<400){
    digitalWrite(A4,LOW);
    digitalWrite(A5,HIGH);
    }
    else if(directionpack.sink<100){
    digitalWrite(A4,HIGH);
    digitalWrite(A5,LOW);

    }
    else{
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);

    }
  }

  //LEFT
  else if (directionpack.dir>200 && directionpack.dir<300){
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);

    analogWrite(6,directionpack.knob);

    if(directionpack.sink>100 && directionpack.sink<400){
    digitalWrite(A4,LOW);
    digitalWrite(A5,HIGH);
    }
    else if(directionpack.sink<100){
    digitalWrite(A4,HIGH);
    digitalWrite(A5,LOW);

    }
    else{
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);

    }
  }

  //RIGHT
  else if (directionpack.dir>400 && directionpack.dir<500){
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);

   analogWrite(6,directionpack.knob);
    if(directionpack.sink>100 && directionpack.sink<400){
    digitalWrite(A4,LOW);
    digitalWrite(A5,HIGH);
    }
    else if(directionpack.sink<100){
    digitalWrite(A4,HIGH);
    digitalWrite(A5,LOW);

    }
    else{
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);

    }
  }

  else{
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    analogWrite(6,directionpack.knob);

    if(directionpack.sink>100 && directionpack.sink<400){
    digitalWrite(A4,LOW);
    digitalWrite(A5,HIGH);
    }
    else if(directionpack.sink<100){
    digitalWrite(A4,HIGH);
    digitalWrite(A5,LOW);

    }
    else{
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);

    }
  }
}


void collectSensordata(){  //Function for Sensor Data

  // PRESURE_SENSOR
  // read the input on analog pin 1:
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  sensdata[0] = (voltage+0.475)/(0.045);


//  LDR_SENSOR
  sensdata[1] = analogRead(ldrPin);


//TEMP_SENSOR
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  sensdata[2] = T - 273.15;
}
