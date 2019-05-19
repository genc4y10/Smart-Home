//#include <SoftwareSerial.h>
#include <Servo.h>
#include <DHT.h>
#define DHTPIN 5
#define DHTTYPE DHT11

DHT sensorverisi(DHTPIN,DHTTYPE);
Servo servo;
Servo servo2;
const int sensorMin = 0; // sensor maksimum
const int sensorMax = 1024; // sensor minimum
int sensor = A0; 
int reg=0;
int yagmur = 0;  
String hareketVarMi="Yok";
int motorpin = 9; 
int pos=0;
int pos2=0;
int motorpin2=10;
int aci;
int say=0;
int deger;
int sayac=2;
int sayac2=0;
byte trigger = 12; 
byte echo = 11; 
unsigned long sure;  
double toplamYol; 
int aradakiMesafe; 

void setup() {
Serial.begin(9600);
pinMode(sensor, INPUT); 
pinMode(7, OUTPUT); 
pinMode(motorpin , OUTPUT);
pinMode(motorpin2, OUTPUT);
pinMode(8, OUTPUT);
pinMode(3, OUTPUT);
pinMode(2, INPUT);

sensorverisi.begin();
servo.attach(6);
servo2.attach(4);
servo.write(90); 
//servo2.write(0); 
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT); 
delay(1000);
}

void loop() {
float nem=sensorverisi.readHumidity();
float sicaklik=sensorverisi.readTemperature();
float fahren=sensorverisi.readTemperature(true);

yagmur = analogRead(A0); 
int range = map(yagmur, sensorMin, sensorMax, 0, 3); //okunana değeri 0 ile 3 arasındaki değere oranlama

int data=Serial.read();




//mesafe sensörü
 digitalWrite(trigger, HIGH);
  delayMicroseconds(30);
  digitalWrite(trigger, LOW);
  sure = pulseIn(echo, HIGH);
  toplamYol = (double)sure*0.034;
  aradakiMesafe = toplamYol / 2;
if(aradakiMesafe < 5 ){
  tone(3, 1000, 3000);
  digitalWrite(8,HIGH);
  delay(50);
  digitalWrite(8,LOW);
  delay(50);
}

if(data=='3'){
  reg=3;
}if(data=='4'){
  reg=4;
}
  

//sıcaklıga göre motor dondur
if(sicaklik >= 25){
  if( reg == 3){
    digitalWrite(motorpin , HIGH);
    digitalWrite(motorpin2, LOW);
  }else if( reg == 4){
    digitalWrite(motorpin, LOW);
    digitalWrite(motorpin2 , LOW);
  }else{
    digitalWrite(motorpin , HIGH);
    digitalWrite(motorpin2, LOW);
  }
  
}else if (sicaklik < 25){
  if( reg == 3){
    digitalWrite(motorpin , HIGH);
    digitalWrite(motorpin2, LOW);
  }else if( reg == 4){
    digitalWrite(motorpin, LOW);
    digitalWrite(motorpin2 , LOW);
  }else{
    digitalWrite(motorpin , LOW);
    digitalWrite(motorpin2, LOW);
  }
}

//garak kapısı servo kontrol

if(data == '1'){
    servo.write(10);             
  }
 if(data=='2'){
    servo.write(90);
  }
    



////yagmur kontrol servo
//Serial.println(yagmur);
switch (range) {
case 0:
servo2.write(90);
break;
case 1:
servo2.write(90);
break;
case 2:
servo2.write(0);
break;
}
delay(10);





//odanın ısıkları 
if(data == '7'){
  digitalWrite(7,HIGH);
}

 else if(data == '8'){
  digitalWrite(7,LOW);
 }

 
//hareket sensörü
deger = digitalRead(2);
if (data == '5') {
  sayac=1;
}
if (data == '6') {
  sayac=2;
}
if (sayac == 1) {
  if(deger == HIGH){
    hareketVarMi="Var";
    tone(3, 1000, 3000);
    for(int y=0; y<3; y++){
     digitalWrite(8, HIGH);
     delay(50);
    digitalWrite(8, LOW);
    delay(50);
    }
}  if(deger == LOW){
      hareketVarMi="Yok";
}
}
else if(sayac == 2){
    if(deger == HIGH){
      hareketVarMi="Var";
      digitalWrite(8,LOW);
}
else {
  digitalWrite(8, LOW); 
   hareketVarMi="Yok";
}
}else {
  digitalWrite(8, LOW); 
   hareketVarMi="Yok";
}
      




Serial.println(sicaklik);
Serial.println(nem);
Serial.println(aradakiMesafe);
Serial.println(hareketVarMi);
//Serial.println(yagmur);



delay(2000);
}
