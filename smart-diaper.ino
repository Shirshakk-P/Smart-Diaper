#include<SoftwareSerial.h>      //Arduino built-in library for wnabling serial communication on the digital pins of Arduino 
#include<RadioHead.h>          //Communication library for Bluetooth module
#include <RH_ASK.h>           //was intended to be used for data transfer via the RF module
#include <SPI.h>             //Communication library for Bluetooth module

int analogPin = A0;
int limit = 600;     //Critical Voltage Limit for the Soil Moisture Sensor
int moisture;
int percentage;
int flag = 0;

#define S0 2        //TCS-3200 Pin
#define S1 3        //TCS-3200 Pin
#define S2 4        //TCS-3200 Pin
#define S3 5        //TCS-3200 Pin
#define OUT 6       //TCS-3200 Pin

int RED_freq = 0;     //TCS 3200  Red_Frequency
int GREEN_freq = 0;   //TCS 3200  Green_Frequency
int BLUE_freq = 0;    //TCS 3200  Blue_Frequency

SoftwareSerial MyBlue(2, 3);  //Rx-Tx via Bluetooth Module

void setup() {
  //Soil Moisture Sensor
  Serial.begin(9600);  

  //TCS 3200
  pinMode(S0, OUTPUT);      //Built-in function for changing mode of Digital Pins
  pinMode(S1, OUTPUT);      //Built-in function for changing mode of Digital Pins
  pinMode(S2, OUTPUT);      //Built-in function for changing mode of Digital Pins
  pinMode(S3, OUTPUT);      //Built-in function for changing mode of Digital Pins
  pinMode(OUT, INPUT);      //Built-in function for changing mode of Digital Pins
  
  digitalWrite(S0,HIGH);    //Built-in function for setting up Digital Pins
  digitalWrite(S1,LOW);     //Built-in function for setting up Digital Pins
  

  //HC-05    
  Serial.println("Ready to Connect\n\n"); 
}


void loop() {
  //TCS 3200
  digitalWrite(S2,LOW);          //Built-in function for setting up Digital Pins
  digitalWrite(S3,LOW);          //Built-in function for setting up Digital Pins
  RED_freq = pulseIn(OUT, LOW);  //Built-in function for reading the value of Pulse input on pin

  digitalWrite(S2,HIGH);          //Built-in function for setting up Digital Pins
  digitalWrite(S3,HIGH);          //Built-in function for setting up Digital Pins
  GREEN_freq = pulseIn(OUT, LOW); //Built-in function for reading the value of Pulse input on pin
  delay(100);

  
  digitalWrite(S2,LOW);           //Built-in function for setting up Digital Pins
  digitalWrite(S3,HIGH);          //Built-in function for setting up Digital Pins
  BLUE_freq = pulseIn(OUT, LOW);  //Built-in function for reading the value of Pulse input on pin
  delay(100);
  
  //Soil Moisture Sensor
  moisture = analogRead(analogPin);
  Serial.println("Analog Value : ");
  Serial.println(moisture);


  if (MyBlue.available())       //Checking the connection status of the HC-05 module
  flag = MyBlue.read();
  if (moisture < limit) {       //Analog value of Voltage is less than the critical limit => Diaper is WET
  Serial.println("\n Condition: Moisture"); 
  Serial.println("\n Diaper Wet");}
  else if(RED_freq < GREEN_freq && GREEN_freq < BLUE_freq){
  Serial.println("\n YELLOW and Wet Condition");
  }
  
  else if(moisture > limit){      //Analog value of Voltage is more than the critical limit => Diaper is WET
  Serial.println("\n Condition: Dry");
  Serial.println("\n Diaper OK"); } 
  if(RED_freq > GREEN_freq && GREEN_freq > BLUE_freq){
  Serial.println("\n BLUE and Dry Condition");
  }
  delay(1000);                //Delay counter to space up successive readings
}
