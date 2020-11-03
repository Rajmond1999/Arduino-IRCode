const int ledPin = 13; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}




void loop() {
  char code=0;
  int state1=0;
  //  reading code
  if (Serial.available() > 0) {
    code = Serial.read();
    Serial.println("Olvasva");
    }
  switch(code){
  case '1': Serial.print("1\n");
            digitalWrite(ledPin, !digitalRead(ledPin));
            break;

  case '2': Serial.print("2\n"); break;

  case '3': Serial.print("3\n"); break;

  case '4': Serial.print("4\n"); break;
  
  case '5': Serial.print("5\n"); break;
  
  case '6': Serial.print("6\n"); break;
  delay(1000);
  default:  break;
  }
  delay(1000);
}
