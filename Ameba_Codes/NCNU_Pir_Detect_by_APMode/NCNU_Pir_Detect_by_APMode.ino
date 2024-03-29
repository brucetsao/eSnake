// this program is copied from NCNU_ADV_APMODEControlLed
#include <WiFi.h>
#include <String.h>

#define LedPin 13
#define PowerLedPin 12
#define PirPin 8
#define Turnon HIGH
#define Turnoff LOW
uint8_t MacData[6];
char ssid[10] ;  //Set the AP's SSID
char pass[] = "12345678";     //Set the AP's password
char channel[] = "1";         //Set the AP's channel
int status = WL_IDLE_STATUS;     // the Wifi radio's status
String MacAddress ;
IPAddress  Meip ,Megateway ,Mesubnet ;

int keyIndex = 0;                 // your network key Index number (needed only for WEP)

WiFiServer server(80);



void printWifiData() {
  /*
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your subnet mask:
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
  Serial.println();
  */
}

void printCurrentNet() {
  // print the SSID of the AP:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of AP:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[0], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.println(bssid[5], HEX);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
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
Serial.print(tt);
Serial.print("\n");
  
  return tt ;
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


//----------------
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);      // set the LED pin mode
  pinMode(PowerLedPin,OUTPUT);      // set the LED pin mode
  pinMode(PirPin,INPUT);      // set the LED pin mode
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }
    MacAddress = GetWifiMac(); // get MacAddress
    ShowMac() ;       //Show Mac Address
  String a1 = print2HEX((int)MacData[4]);
  String a2 = print2HEX((int)MacData[5]);
  
  // attempt to start AP:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to start AP with SSID: ");
       String("NCNU_"+a1+a2).toCharArray(&ssid[0],9) ;

    Serial.println(ssid);
    status = WiFi.apbegin(ssid, pass, channel);
    digitalWrite(PowerLedPin,Turnon) ;
    delay(10000);
  }

  //AP MODE already started:
  Serial.println("AP mode already started");
  Serial.println();
    server.begin();    
  printWifiData();
  printCurrentNet();
}
void loop() {
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");

            client.println("Content-type:text/html");
            client.println();

            client.print("<title>Ameba AP Mode Control Relay</title>");
            client.println();
            client.print("<html>");
            client.println();
            // the content of the HTTP response follows the header:
            if (digitalRead(PirPin))
              {
                 client.print("Some one Coming <br>");
                 digitalWrite(LedPin,Turnon) ;
              } 
              else
              {
                 client.print("No Body <br>");
                 digitalWrite(LedPin,Turnon) ;
              }
              client.println();
            client.print("</html>");
            client.println();

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
 
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}




