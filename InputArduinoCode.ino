#include <IRremote.h>
const int ledPin = 13;
int RECV_PIN = 11;

int flag=0;

IRrecv irrecv(RECV_PIN);
decode_results results;
int result1,result2,result3;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
    {
 
      if(results.value==573503)
        {
          Serial.print("1"); 
        }
      if(results.value==532703)
        {
          Serial.print("2"); 
        }
      if(results.value==565343)
        {
          Serial.print("3"); 
        }
      
     irrecv.resume(); // Receive the next value
    }
}
