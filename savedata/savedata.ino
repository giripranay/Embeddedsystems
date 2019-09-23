void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:

}
int x=0;
void loop() {

while(x<21)
{
  x=x+1;
  // put your main code here, to run repeatedly:
Serial.println(x);
delay(1000);
}

}
