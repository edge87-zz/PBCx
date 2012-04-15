void setup() {
  pinMode(13, OUTPUT);      
  Serial.begin(115200); 
};

void loop() {
  int opcode, incomingByte = 0;

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    //Check if it is our request switches
    if (incomingByte == 62){
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      
      Serial.write("ABCD");
    };
  };
};

