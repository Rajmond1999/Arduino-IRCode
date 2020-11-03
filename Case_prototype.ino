void setup() {
  Serial.begin(9600);
}

void loop() {
  int code=1;
  //  reading code
  if (Serial.available() > 0) {
    code = Serial.read();
    code-='0';
    }
   Serial.println(code);
  switch(code){
  case 1: Serial.print("1\n"); break;;

  case 2: Serial.print("2\n"); break;

  case 3: Serial.print("3\n"); break;

  case 4: Serial.print("4\n"); break;
  
  case 5: Serial.print("5\n"); break;
  delay(500);
  default:  break;
  }
  delay(500);
}
