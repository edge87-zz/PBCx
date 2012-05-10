//This whole thing hopefully waits 5ms sends 12 bytes, and repeats endless giving me an effective total of about 200 - 250 times per second. or fire..
//You might be asking yourself, why didn't i build an interrupt. That is too damn complex. 

#define MICROSECOND_DELAY 5000 // don't ask. 

unsigned char opcode = (char)62;
unsigned char eol = (char)255;

byte one   = B10101000;
byte two   = B10101000;
byte three = B10101000;
byte four  = B10101000;
byte five  = B10101000;
byte six   = B10101000;
byte seven = B10101000;
byte eight = B10101000;
byte nine  = B10101010;
byte ten   = B10101010;

void setup() {
  pinMode(13, OUTPUT);      
  Serial.begin(115200); 
  digitalWrite(13, HIGH); //I'm alive! 
};

void loop() {
  delayMicroseconds(MICROSECOND_DELAY);
  
  Serial.write(opcode);
  Serial.write(one);
  Serial.write(two);
  Serial.write(three);
  Serial.write(four);
  Serial.write(five);
  Serial.write(six);
  Serial.write(seven);
  Serial.write(eight);
  Serial.write(nine);
  Serial.write(ten);
  Serial.write(eol);

};

