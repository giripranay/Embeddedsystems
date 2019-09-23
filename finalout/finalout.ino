 #include <SoftwareSerial.h>

SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
//----------------------------------------------
String apiKey = "R885UB7JUNCTVZEF";     // replace with your channel's thingspeak WRITE API key

String ssid="Aravind";    // Wifi network SSID
String password ="babu1967";  // Wifi network password

boolean DEBUG=true;
//--------------------------------------------


                             
int c1=0,c2=0,c3=0,c4=0,flag=1,count=0,flag2=0,flag3=0,Time=0,turn;
char led='R';
void setup()
{
  pinMode(8, OUTPUT);  
  pinMode(9, OUTPUT);  
  pinMode(10, OUTPUT);
  if(led=='R')
  {
    digitalWrite(8,HIGH);
    }

        
 
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  esp8266.println("AT+CWLAP");
 //------------------------------------------------------------------------
    DEBUG=true;
     //esp8266.println("AT+CWMODE=3");   // set esp8266 as client
  //showResponse(1000);

  //esp8266.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  // set your home router SSID and password
//showResponse(5000);

   if (DEBUG)  Serial.println("Setup completed");   

thingSpeakWrite(c1,c2,c3);
 
}
 /* if(led=='R')
  {
    digitalWrite(8,HIGH);
    }
    
   if(led=='G')
  {
    digitalWrite(9,HIGH);
    }     
   
  if(led=='B')
  {
    digitalWrite(10,HIGH);
    }
 
*/
  //delay(5000);
  //setup();
  


void set()
{
    esp8266.println("AT+CWLAP");
    //thingSpeakWrite(c1,c2,c3);
}
void loop()
{


  
  if(esp8266.available()) // check if the esp is sending a message 
  {
    while(esp8266.available())
    {
      //thingSpeakWrite(c1,c2,c3);
      //delay(3000);
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
     // Serial.write(c);
      if(c=='"')
      {
       count++;
      }
      else if(c=='O')
      {
        flag3=1;}
      if(flag3==1&&c=='K')
      {
        //esp8266.write("density");
        Serial.println(Time);
        //thingSpeakWrite(c1,c2,c3);
        //delay(3000);
        density();
         
        
        change();
        
       // Serial.print(led);
        //Serial.println(turn);  
       
       
      //  Serial.println(Time);
        if(Time==30)
        {
          light();
          }
        delay(3000); 
        Time=Time+3;
        set();
        flag3=0;
        }   
      int r=count%2;
      int q=count/2;
      if(r==1 && q%2==0)
      {
        flag=0;
        flag2++;
      }
      if(flag==0&&flag2==2)
      {
      //Serial.write(c);
      if(c=='R')
      {c1++;
        }
       else if(c=='G')
       {
        c2++;}
          else if(c=='B')
       {
        c3++;}
       
      flag=1;
      }
      if(r==0 && q%2==1)
      {
       flag2=0; }
  
      
  }


  
 //delay(10000);
  
  if(Serial.available())
  {
    // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    delay(1000); 
    
    String command="";
    
    while(Serial.available()) // read the command character by character
    {
       
        // read one character
      command+=(char)Serial.read();
      
   }    
      esp8266.println(command); // send the read character to the esp8266
  }    
  
       
}
   
}
void density()
    {
     if(led=='R')
     {
      turn=c1;
      }
      else if(led=='G')
      {
        turn=c2;
        }
       else if(led=='B')
       {
        turn=c3;
        } 
      
      Serial.print("\n");
Serial.print("Number of RED cars ");
      Serial.println(c1);
  
      c1=0;
Serial.print("Number of GREEN cars ");
      Serial.println(c2);
       
       c2=0;
      Serial.print("Number of BLUE cars ");
      Serial.println(c3);
       c3=0;

       
      }
void light()
{Time=0;
  if (led=='R')
  {
    digitalWrite(8,LOW);
    led='G';
    digitalWrite(9,HIGH);
    }
   else if(led=='G')
   {

    digitalWrite(9,LOW);
    led='B';
    digitalWrite(10,HIGH);
    }
    else if(led=='B')
    {
      digitalWrite(10,LOW);
      led='R';
      digitalWrite(8,HIGH);
      }
  
  
  
  }

void change()
{
 if(turn==0) 
  { Time=0;
    if(led=='R')
    {
    digitalWrite(8,LOW);
    led='G';
    
    digitalWrite(9,HIGH);
      }
    
     else if(led=='G')
   {

    digitalWrite(9,LOW);
    led='B';
    digitalWrite(10,HIGH);
    }
    else if(led=='B')
    {
      digitalWrite(10,LOW);
      led='R';
      digitalWrite(8,HIGH);
      }
  
  }}  




//======================================================================== showResponce
void showResponse(int waitTime){
    long t=millis();
    char c;
    while (t+waitTime>millis()){
      if (esp8266.available()){
        c=esp8266.read();
        if (DEBUG) Serial.print(c);
      }
    }
                   
}

//========================================================================
boolean thingSpeakWrite(int value1,int value2,int value3){
  String cmd = "AT+CIPSTART=\"TCP\",\"";                  // TCP connection
  cmd += "184.106.153.149";                               // api.thingspeak.com
  cmd += "\",80";
  esp8266.println(cmd);
  if (DEBUG) Serial.println(cmd);
  if(esp8266.find("Error")){
    if (DEBUG) Serial.println("AT+CIPSTART error");
    return false;
  }
  
  
  String getStr = "GET /update?api_key=";   // prepare GET string
  getStr += apiKey;
  
  getStr +="&field1=";
  getStr += String(value1);
  getStr +="&field2=";
  getStr += String(value2);
  getStr +="&field3=";
  getStr += String(value3);
  // ...
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  esp8266.println(cmd);
  if (DEBUG)  Serial.println(cmd);
  
  delay(100);
  if(esp8266.find(">")){
    esp8266.print(getStr);
    if (DEBUG)  Serial.print(getStr);
  }
  else{
    esp8266.println("AT+CIPCLOSE");
    // alert user
    if (DEBUG)   Serial.println("AT+CIPCLOSE");
    return false;
  }
  return true;
}

