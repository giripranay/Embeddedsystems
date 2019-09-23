#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int fre=0;
void setup() {
 pinMode(S0,OUTPUT);
 pinMode(S1,OUTPUT);
 pinMode(S2,OUTPUT);
 pinMode(S3,OUTPUT);
 pinMode(sensorOut,INPUT);

digitalWrite(S0,HIGH);
digitalWrite(S1,LOW);
Serial.begin(9600);
}

void loop() {

digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
fre=pulseIn(sensorOut,LOW);
Serial.print("RED= ");
Serial.print(fre);
Serial.print("  ");
delay(100);

digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
fre=pulseIn(sensorOut,LOW);
Serial.print("GREEN= ");
Serial.print(fre);
Serial.print("  ");
delay(100);

digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
fre=pulseIn(sensorOut,LOW);
Serial.print("BLUE= ");
Serial.print(fre);
Serial.println("  ");
delay(100);
  
}
