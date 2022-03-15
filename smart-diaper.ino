#include<SoftwareSerial.h>
#include<RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h> 

int analogPin = A0;
int limit = 600;     //Critical Limit
int moisture;
int percentage;
int flag = 0;

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define OUT 6

int RED_freq = 0;
int GREEN_freq = 0;
int BLUE_freq = 0;

SoftwareSerial MyBlue(2, 3); // RX | TX

void setup() {
  //Soil Moisture Sensor
  Serial.begin(9600);  

  //TCS 3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  

  //HC-05    
  Serial.println("Ready to Connect\n\n"); 
}


void loop() {
  //TCS 3200
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  RED_freq = pulseIn(OUT, LOW);
  //Serial.print("R = ");
  //Serial.println(RED_freq);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  GREEN_freq = pulseIn(OUT, LOW);
  //Serial.print(" G = ");
  //Serial.println(GREEN_freq);
  delay(100);

  
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  BLUE_freq = pulseIn(OUT, LOW);
  //Serial.print(" B = ");
  //Serial.println(BLUE_freq);
  delay(100);
  
  //Soil Moisture Sensor
  moisture = analogRead(analogPin);
  Serial.println("Analog Value : ");
  Serial.println(moisture);



  if (MyBlue.available()) //HC-05 
  flag = MyBlue.read();
  if (moisture < limit) {
  Serial.println("\n Condition: Moisture"); 
  Serial.println("\n Diaper Wet");}
  else if(RED_freq < GREEN_freq && GREEN_freq < BLUE_freq){
  Serial.println("\n YELLOW and Wet Condition");
  }
  
  else if(moisture > limit){
  Serial.println("\n Condition: Dry");
  Serial.println("\n Diaper OK"); } 
  if(RED_freq > GREEN_freq && GREEN_freq > BLUE_freq){
  Serial.println("\n BLUE and Dry Condition");
  }
  delay(1000);
}
