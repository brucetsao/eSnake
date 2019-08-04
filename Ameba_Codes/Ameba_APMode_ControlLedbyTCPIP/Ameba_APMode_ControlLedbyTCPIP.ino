#include <String.h>   // use String onject 

#include <WiFi.h>   // use wifi object 

char ssid[12] ="AMEBA"     ;  // your network SSID (name)
char pass[9] = "12345678";     // your network password
char channel[] = "1";
uint8_t MacData[6];     //get mac addrss
IPAddress  Meip ,Megateway ,Mesubnet ;    // get wifi parameter
String MacAddress ;     // get mac address by string
int status = WL_IDLE_STATUS;      // wifi status

String ReadStr = "" ;     // receive data use
int delayval = 500; // delay for half a second
WiFiServer server(80);      // declare web server  by port 80
    int count = 0 ;
  boolean readok = false ;
  unsigned long strtime ;

  //----------------
int ledPins[]={8,9,10,11} ;

unsigned char btchar ;

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
          
    //    Serial.print("client connected  in while");
   //       Serial.println(millis());
          if (client.available())
          {
            
            //  Serial.println("something readrable");
            btchar = client.read();
            Serial.print(btchar) ;
            // give the web browser time to receive the data
            if (btchar == '@')
            {
             if (client.available())
                   {
                        btchar = client.read();
                         Serial.print(btchar) ;
                  if (btchar == '+')
                      {
                          Serial.println("Open Led") ; 
                          btchar = client.read(); ;
                          TurnOnLed((int)(btchar-48)) ;
                          Serial.print("(") ;
                          Serial.print((int)(btchar-48)) ;
                          Serial.print(")\n") ;
                          client.print("OK") ;
                           // return ;
                      }   // end of  (btchar == '+')
                  if (btchar == '-')
                      {
                          Serial.println("Close Led") ; 
                          btchar = client.read(); ;
                          TurnOffLed((int)(btchar-48)) ;
                          Serial.print("(") ;
                          Serial.print((int)(btchar-48)) ;
                          Serial.print(")\n") ;
                          
                          client.print("OK") ;
                           // return ;
                      }   // end of (btchar == '-')
         
                   }    // end of client.available()
                  
               }  //  end of (btchar == '@')

            
            }   // end of if (client.available())
            

            
      }  //end  of while (client.connected())

 
    }   //end of   if (client)


   //    delay(800) ;
  //  free(client);
}


void initPins()
{
    for (int i=0 ; i <4; i++)
      {
          pinMode(ledPins[i], OUTPUT) ;
          digitalWrite(  ledPins[i], LOW) ;    
      }
    
}
void TurnOnLed(int ledno)
{
  if ((ledno <=4 ) && (ledno >=1 ) )
    {
        digitalWrite(  ledPins[ledno-1], HIGH) ; 
    }
    
}

void TurnOffLed(int ledno)
{
    if ((ledno <=4 ) && (ledno >=1 ) )
    {
        digitalWrite(  ledPins[ledno-1], LOW) ; 
    }
    
}
