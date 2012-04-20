 int first = 0;

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
      if (first == 0){
        Serial.write(62);//opcode for Switches next
        Serial.write(~(65)); //byte 0
        Serial.write(~(66)); //byte 1
        Serial.write(~(67)); //byte 2
        Serial.write(~(68)); //byte 3
        Serial.write(~(69)); //byte 4
        Serial.write(~(70)); //byte 5
        Serial.write(~(71)); //byte 6
        Serial.write(~(72)); //byte 7
        Serial.write(255);  //end of line
        first = 0;
      };
     };
     
    if (incomingByte == 61){
      digitalWrite(13, HIGH);      
      Serial.write(61);  //Cabinet buttons to follow
      Serial.write(239);  //Cabinet Switch - Start Button
      Serial.write(155);  //who cares
      Serial.write(255);  //end of line
      
    };
  };
};

