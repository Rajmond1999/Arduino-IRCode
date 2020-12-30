const int ledPin = 13; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  char code=0;
  //  reading code
  if (Serial.available() > 0) {
    code = Serial.read();
    }
    if(code=='1')
    {
      digitalWrite(ledPin, !digitalRead(ledPin));
      }
}
