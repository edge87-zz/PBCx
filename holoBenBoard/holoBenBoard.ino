byte one = B10101000;
byte two = B10101000;
byte three = B10101000;
byte four = B10101000;
byte five = B10101000;
byte six = B10101000;
byte seven = B10101000;
byte eight = B10101000;

byte cab0 = B11101111;
byte cab1 = B11111111;

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
      digitalWrite(13, HIGH);
      Serial.write(62);
      Serial.write(one);
      Serial.write(two);
      Serial.write(three);
      Serial.write(four);
      Serial.write(five);
      Serial.write(six);
      Serial.write(seven);
      Serial.write(eight);
      Serial.write(255);
     };
     
    if (incomingByte == 61){    
      Serial.write(61);
      Serial.write(cab0);
      Serial.write(cab1);
      Serial.write(255);  
    };
  };
};

