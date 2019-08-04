#include <String.h>    // Use String object

#include <WiFi.h>      // Use wifi 
#include "control.h"

IPAddress  Meip ,Megateway ,Mesubnet ;  //get network parameter

WiFiServer server(80);

void ShowMac()
{
  
     Serial.print("MAC:");
     Serial.print(MacAddress);
     Serial.print("\n");

}




String GetWifiMac()
{
   String tt ;
    String t1,t2,t3,t4,t5,t6 ;
    WiFi.status();    //this method must be used for get MAC
  WiFi.macAddress(MacData);
  
  Serial.print("Mac:");
   Serial.print(MacData[0],HEX) ;
   Serial.print("/");
   Serial.print(MacData[1],HEX) ;
   Serial.print("/");
   Serial.print(MacData[2],HEX) ;
   Serial.print("/");
   Serial.print(MacData[3],HEX) ;
   Serial.print("/");
   Serial.print(MacData[4],HEX) ;
   Serial.print("/");
   Serial.print(MacData[5],HEX) ;
   Serial.print("~");
   
   t1 = print2HEX((int)MacData[0]);
   t2 = print2HEX((int)MacData[1]);
   t3 = print2HEX((int)MacData[2]);
   t4 = print2HEX((int)MacData[3]);
   t5 = print2HEX((int)MacData[4]);
   t6 = print2HEX((int)MacData[5]);
 tt = (t1+t2+t3+t4+t5+t6) ;
 tt.toUpperCase() ;
Serial.print(tt);
Serial.print("\n");
  
  return (tt) ;
}

String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number,HEX);
  }
  else
  {
      ttt = String(number,HEX);
  }
  return ttt ;
}





void printWifiData() 
{
  // print your WiFi shield's IP address:
  Meip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(Meip);
  Serial.print("\n");

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

  // print your subnet mask:
  Mesubnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(Mesubnet);

  // print your gateway address:
  Megateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(Megateway);
}

void ShowInternetStatus()
{
    
        if (WiFi.status())
          {
               Meip = WiFi.localIP();
               Serial.print("Get IP is:");
               Serial.print(Meip);
               Serial.print("\n");
              
          }
          else
          {
                       Serial.print("DisConnected:");
                       Serial.print("\n");
          }

}

void initializeWiFi() {
   String SSIDName = String("AMEBA")+MacAddress.substring(6,11) ;
 //  stringcpy(SSIDName.toUpperCase(),&ssid[0]) ;
  stringcpy(SSIDName,&ssid[0]) ;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
   status = WiFi.apbegin(ssid, pass, channel);
  //   status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("\n Success to connect AP:") ;
  Serial.print(ssid) ;
  Serial.print("\n") ;
  

}

void stringcpy(String srcchar, char *tarchar)
{
      for (int i = 0 ; i < srcchar.length(); i++)
          {
              *(tarchar+i) = srcchar.charAt(i);
              
          }

}



void strcpy(char *srcchar, char *tarchar, int len)
{
      for (int i = 0 ; i < len; i++)
          {
              *(tarchar+i) = *(srcchar+i);
              
          }

}


//-------------------------------
void StringWrite_AT_Command(String  string){
  mySerial.print(string);
  while (mySerial.read() != 'E') {}
  delay(2);
  
}

void initATMode(){
  mySerial.write(0xf6);
  mySerial.write(0x01);
  delay(200);
}
///////////////////////////////////


//------------main
void setup() {
  Serial.begin(9600) ;
  initPins();
  
     MacAddress = GetWifiMac() ; // get MacAddress
    ShowMac() ;       //Show Mac Address
    initializeWiFi();
      server.begin();
    printWifiData() ;
   
     delay(2000) ;   //wait 2 seconds

//--game
  Serial.println("START Snake Game");
  mySerial.begin(115200);
  initATMode();
  
  //randomSeed(analogRead(A0));
  //GenerujPotravu();

 
  
  StringWrite_AT_Command("ATd0=()"); // clear display
  //ScreenAnimate();
  //TestAni();
  //StringWrite_AT_Command("AT91=(44,12,53,21,1)"); //Draw a play zone (square)
     
}

void Up(Pos *nowp)
{
    //if (nowp->y < bound_y1){  
      nowp->y --;
      
      Serial.print("y:");
      Serial.println(nowp->y);
      nowp->isUpdated = true ;
      Serial.print("nowp.isUpdated:");
      Serial.println(nowp->isUpdated);
      delay(20);
      
    //}
}

void Down(Pos *nowp)
{
    //if (nowp->y < bound_y2){  
      nowp->y++;
       Serial.print("y:");
      Serial.println(nowp->y);
      nowp->isUpdated = true ;
      Serial.print("nowp.isUpdated:");
      Serial.println(nowp->isUpdated);
      delay(20);
    //}
}

void Left(Pos *nowp)
{
    //if (nowp->x > bound_x1){  
      nowp->x--;
      Serial.print("x:");
      Serial.println(nowp->x);
      nowp->isUpdated = true ;
      Serial.print("nowp.isUpdated:");
      Serial.println(nowp->isUpdated);
      delay(20);
    //}
}

void Right(Pos *nowp)
{
    //if (nowp->x < bound_x2){  
      nowp->x++;
      Serial.print("x:");
      Serial.println(nowp->x);
      nowp->isUpdated = true ;
      Serial.print("nowp.isUpdated:");
      Serial.println(nowp->isUpdated);
      delay(20);
    //}
}



void Draw(Pos nowp)
{
  
  StringWrite_AT_Command("AT9e=("+String(nowp.x)+","+String(nowp.y)+")");
  Serial.print("Draw:");
  Serial.println(String(nowp.x)+","+String(nowp.y));
  
}

void Erase(Pos nowp)
{
  StringWrite_AT_Command("AT9f=("+String(nowp.x)+","+String(nowp.y)+")");
  Serial.print("Erase:");
  Serial.println(String(nowp.x)+","+String(nowp.y));
}


void loop()
{
  WiFiClient client = server.available();
  readok = false ;
  
  if (client)
  {
  
    Serial.println("Now Someone Access WebServer");
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
      {
  //        
        //Serial.print("client connected  in while");
          //Serial.println(millis());
           //   Serial.print("in Connected:(") ;
          //    Serial.print(client);
           //   Serial.println(")");
            
             if (client.available()>0)
             {
                        btstring = client.readStringUntil(0x0a);
                        //btchar = client.read();
                        delay(50);
                        Serial.print("btstring:"); 
                        Serial.println(btstring) ;

                  tempPosition.x = nowPosition.x;
                  tempPosition.y = nowPosition.y;
                        
                  
                  if (btstring == "L")
                  {
                    Left(&nowPosition);
                  } 
                  else if (btstring == "R")
                  {
                    Right(&nowPosition);
                  }
                  else if (btstring == "U")
                  {
                    Up(&nowPosition);
                  }
                  else if (btstring == "D")
                  {
                    Down(&nowPosition);
                  }          
                         

                  if (nowPosition.isUpdated == true){

                    Draw(nowPosition);
                    Erase(tempPosition);
                    nowPosition.isUpdated = false;
                    
                  }
                  
                  Draw(nowPosition);

                  
         
            }    // end of client.available()
                  
               


            
      }  //end  of while (client.connected())

 
    }   //end of   if (client)


   //    delay(800) ;
  //  free(client);

//game
/*
  SnakeControl(); 
  if ((millis() - CasZmeny) > rychlost) {
  CasZmeny = millis();
  Serial.println("before VymazHada, krok-score= "+String(krok - skore));
  VymazHada(had);

  
  Skore();
  Pohyb(); //move had
  if (xHad == xPotrava && yHad == yPotrava) snezeno = true;
    if (had[xHad][yHad] != 0) GameOver();
    
  Serial.println("krok="+String(krok));
  krok++;   //clock tick
  Serial.println("ticked, krok="+String(krok));
  had[xHad][yHad] = krok;
  Serial.println("set had["+String(xHad)+"]["+String(yHad)+"]="+String(krok));
   
  }
  Display(had, xPotrava, yPotrava);  //set led
  */
  
}

void TurnOnLed(int ledno)
{
    if ((ledno <= 4) && (ledno >= 1))
    {
      digitalWrite(ledPins[ledno-1], HIGH);  //array start from 0
    }
      
}      

void TurnOffLed(int ledno)
{
      if ((ledno <= 4) && (ledno >= 1))
    {
      digitalWrite(ledPins[ledno-1], LOW);  //array start from 0
    }
}  


void initPins()
{
    for (int i = 0 ; i < 4; i++)
      {
          pinMode(ledPins[i], OUTPUT) ;
          digitalWrite(ledPins[i], LOW) ;    
      }
    
}


/////////////////////////////////




String incomingByte;   // for incoming serial data
 

 

///////////////////////////////////////////////////////////////////
//Proměnné
int had[8][8] = {0};
 
byte xHad = 4;
byte yHad = 5;
byte xPotrava = 0;
byte yPotrava = 0;

int snake_x = {0};
int snake_y = {0};
int snake_len = 1;

byte smer = 0;
int krok = 1;
long CasZmeny = 0;
int rychlost = 500;
byte skore = 0;
 
boolean snezeno = false;
boolean zvuk = true;
boolean probehlo = false;


///////////////////////////////////////////////////////////////////

 
//Deklarování čísel
int Cislo[11][7] = {
  {B00000000,B00000000,B00000000,B00000000,B00000001,B01111111,B00100001}, //1
  {B00000000,B00000000,B00110001,B01001001,B01000101,B00100011},//2
  {B00000000,B00000000,B01000110,B01101001,B01010001,B01000001,B01000010},//3
  {B00000000,B00001000,B11111111,B01001000,B00101000,B00011000,B00001000},//4
  {B00000000,B00000000,B00111110,B01000101,B01001001,B01010001,B00111110}, //5
  {B00000000,B00000000,B00000110,B01001001,B01001001,B00101001,B00011110}, //6
  {B00000000,B00000000,B01110000,B01001000,B01000111,B01000000,B01100000}, //7
  {B00000000,B00000000,B00110110,B01001001,B01001001,B01001001,B00110110}, //8
  {B00000000,B00000000,B00111100,B01001010,B01001001,B01001001,B00110000}, //9
  {B00000000,B00000000,B00111110,B01010001,B01001001,B01000101,B00111110}, //0
  {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}, //mezera
  };



 

 

///////////////////////////////////////////////////////////////////
// Funkce
void Skore() {
  if (snezeno == true) {
    snezeno = false;
    GenerujPotravu();
 
    skore++;
    snake_len++;
    rychlost -= 20;
    /*
    for (int i = 0; i <= snake_len; i++){
        snake_x[i] = 
    }
    */
    Serial.print ("len: ");
    Serial.println (snake_len);
    Serial.print ("Skore: ");
    Serial.println (skore);
    
  }
}
 
void Display(int matrix[8][8], byte x, byte y) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((matrix[i][j] >= 1) || ((i == x) && (j == y) )) {
        StringWrite_AT_Command("AT9e=("+String(i+45)+","+String(j+13)+")");
        Serial.println("(i,j,on)=("+String(i)+","+String(j)+")");
      }
      /*
      else {
        StringWrite_AT_Command("AT9f=("+String(i+45)+","+String(j+13)+")");
        //Serial.println("(i,j,off)=("+String(i)+","+String(j)+")");
      }
      */
    }
  }
}

 
void VymazHada(int matice[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (matice[i][j] == (krok - skore)) {
        matice[i][j] = 0;
        StringWrite_AT_Command("AT9f=("+String(i+45)+","+String(j+13)+")");
        Serial.println("do VymazHada , had["+String(i)+"]["+String(j)+"]=0");
        }
      }
    }
  }

 
void Pohyb() {
  switch (smer) {
    case 0:
      xHad--;
      break;
    case 1:
      xHad++;
      break;
    case 2:
      yHad++;
      break;
    case 3:
      yHad--;
      break;
  }
  if (xHad == 8) xHad = 0;
  if (yHad == 8) yHad = 0;
  if (xHad == 255) xHad = 7;
  if (yHad == 255) yHad = 7;
}
 
void GenerujPotravu() {
  //lc.setLed(0, xPotrava, yPotrava, false);
  StringWrite_AT_Command("AT9f=("+String(xPotrava+45)+","+String(yPotrava+13)+")");
  do {
    xPotrava = random(0, 8);
    yPotrava = random(0, 8);
  } while (had[xPotrava][yPotrava] != 0 );
}
 
void VykresCislo(byte cislo){
  if(cislo ==0) cislo = 10;
    for (int col=0; col<7; col++) {
      //lc.setRow(0, col, Cislo[cislo-1][col]);    //show Cislo
  }
}
 
void GameOver() {
  Serial.println ("Game over");
  
  //ScreenAnimate();

  do {
  VykresCislo((skore/10)%10);
  delay(200);
  VykresCislo(skore%10);
  delay(200);
  VykresCislo(11);
  delay(1000);
  } while (true);
}

void SnakeControl(){
  if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                if ((incomingByte == "L") && (smer != 0)) smer = 1;  //left
                if ((incomingByte == "R") && (smer != 1)) smer = 0; //right
                if ((incomingByte == "U") && (smer != 3)) smer = 2; //up
                if ((incomingByte == "D") && (smer != 2)) smer = 3; //down

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte);
                
        }
  }

 void ScreenAnimate(){
  
  for (int row = 0; row < 30; row=row+5) {
    for (int col = 0; col < 96; col=col+10) {
      StringWrite_AT_Command("AT92=("+String(col)+","+String(row)+","+String(col+5)+","+String(row+5)+",1)");  //print square
      delay(15);
    }
  }

  for (int row = 0; row < 30; row=row+5) {
    for (int col = 0; col < 96; col=col+10) {
      StringWrite_AT_Command("AT92=("+String(col)+","+String(row)+","+String(col+5)+","+String(row+5)+",0)");  //print square
      delay(15);
    }
  }
  
 }



