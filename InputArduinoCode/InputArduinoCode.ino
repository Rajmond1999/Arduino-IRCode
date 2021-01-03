#include <IRremote.h>
int RECV_PIN = 11;


IRrecv irrecv(RECV_PIN);
decode_results results;

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
