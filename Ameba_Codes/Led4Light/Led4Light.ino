
int ledPins[]={8,9,10,11} ;

void setup() {
  // put your setup code here, to run once:
    initPins() ;
    Serial.begin(9600) ;
    Serial.println("Program Start") ;
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i=0 ; i <4; i++)
      {
          digitalWrite(  ledPins[i], LOW) ;    
          delay(1000) ;
      }
    
    for (int i=0 ; i <4; i++)
      {
          digitalWrite(  ledPins[i], HIGH);    
          delay(1000) ;
      }
    
    
    }


void initPins()
{
    for (int i=0 ; i <4; i++)
      {
          pinMode(ledPins[i], OUTPUT) ;
          digitalWrite(  ledPins[i], LOW) ;    
      }
    
}

