// 2, 4 ,7 Digital Output Pins
const int Out_1 = 2;
const int Out_2 = 4;
const int Out_3 = 7;
const int ledPin = 13;
int command;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  command = Serial.read();
  switch(command){
    case 1: digitalWrite(Out_1, !digitalRead(Out_1));
            break;
    case 2: digitalWrite(Out_2, !digitalRead(Out_2));
            break;
    case 3: digitalWrite(Out_3, !digitalRead(Out_3));
            break;
  }

}
