#include <String.h>

char ssid[12] ="AMEBA"   ;  // your network SSID (name)
char pass[9] = "12345678";     // your network password
char channel[] = "1";
uint8_t MacData[6];           // get mac address
String MacAddress ;
int status = WL_IDLE_STATUS;   // wifi status

String ReadStr = "" ;// recive data
int delayval = 500; // delay for half a second
int count = 0 ;
  boolean readok = false ;
  unsigned long strtime ;

  //------------
int ledPins[]={8,9,10,11} ;

unsigned char btchar ;
String btstring;

struct Pos {
  int x;
  int y;
  boolean isUpdated;
} ;

Pos newPosition = { 10 , 10 , false };
Pos nowPosition = { 10 , 10 , false };
Pos tempPosition = { 0 , 0 , false };

int bound_x1 = 5;
int bound_y1 = 5;
int bound_x2 = 30;
int bound_y2 = 30;
int HHeight = 25;
int WWidth = 25;


//-----------------

#include <SoftwareSerial.h>
const byte rxPin = 0;
const byte txPin = 1;

SoftwareSerial mySerial (rxPin, txPin);
