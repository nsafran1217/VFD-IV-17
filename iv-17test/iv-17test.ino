

int LATCHPIN = 9;

int CLOCKPIN = 10;

int DATAPIN = 8;
int blank = 11;
int num;
unsigned long timeStart = millis();
unsigned long lastTime = 0;
unsigned long j = 0;

unsigned long asciiLookupIV17[128] = {

0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

0b00100000000000001100,  //!
0b00000000001000000100,  //"
0b00001000101000111100,  //#
0b00001010101010111011,  //$
0b00001110111010011001,  //%
0b00001001001101110001,  //&
0b00000000001000000000,  //'
0b00000001010000000000,  //(
0b00000100000100000000,  //)
0b00001111111100000000,  //*
0b00001010101000000000,  //+
0b00000100000000000000,  //,
0b00001000100000000000,  //-
0b00100000000000000000,  //.
0b00000100010000000000,  ///

0b00000100010011111111,  //0
0b00000000010000001100,  //1
0b00001000100001110111,  //2
0b00000000100000111111,  //3
0b00001000100010001100,  //4
0b00001001000010110011,  //5
0b00001000100011111011,  //6
0b00000000000000001111,  //7
0b00001000100011111111,  //8
0b00001000100010111111,  //9
0b00000010001000000000,  //:
0b00000100001000000000,  //;
0b00000001010000000000,  //<
0b00001000100000110000,  //=
0b00000100000100000000,  //>
0b00100010100000000111,  //?
0b00000000101011110111,  //@
0b00001000100011001111,  //A
0b00000010101000111111,  //B
0b00000000000011110011,  //C
0b00000010001000111111,  //D
0b00001000000011110011,  //E
0b00001000000011000011,  //F
0b00000000100011111011,  //G
0b00001000100011001100,  //H
0b00000010001000110011,  //I
0b00000000000001111100,  //J
0b00001001010011000000,  //K
0b00000000000011110000,  //L
0b00000000010111001100,  //M
0b00000001000111001100,  //N
0b00000000000011111111,  //O
0b00001000100011000111,  //P
0b00000001000011111111,  //Q
0b00001001100011000111,  //R
0b00001000100010111011,  //S
0b00000010001000000011,  //T
0b00000000000011111100,  //U
0b00000100010011000000,  //V
0b00000101000011001100,  //W
0b00000101010100000000,  //X
0b00001000100010111100,  //Y
0b00000100010000110011,  //Z
0b00000010001000010010,  //[
0b00000001000100000000,  //\
0b00000010001000100001,  //]
0b00000101000000000000,  //^
0b00000000000000110000,  //_
0b00000000000100000000,  //`
0b00001010000001110000,  //a
0b00001010000011100000,  //b
0b00001000000001100000,  //c
0b00000010100000011100,  //d
0b00001100000001100000,  //e
0b00001010101000000010,  //f
0b00001010001010100001,  //g
0b00001010000011000000,  //h
0b00000010000000000000,  //i
0b00000010001001100000,  //j
0b00000011011000000000,  //k
0b00000000000011000000,  //l
0b00001010100001001000,  //m
0b00001010000001000000,  //n
0b00001010000001100000,  //o
0b00001000001011000001,  //p
0b00001010001010000001,  //q
0b00001000000001000000,  //r
0b00001010000010100001,  //s
0b00001000000011100000,  //t
0b00000010000001100000,  //u
0b00000100000001000000,  //v
0b00000101000001001000,  //w
0b00000101010100000000,  //x
0b00000000101000011100,  //y
0b00001100000000100000,  //z
0b00001010001000010010,  //{
0b00000010001000000000,  //|
0b00000010101000100001,  //}
0b00001100110000000000,  //~
0b00000000000000000000,  //
0

  
  };





void setup()
{
    //Start Serial for debuging purposes
    Serial.begin(9600);
    //set pins to output because they are addressed in the main loop
    pinMode(LATCHPIN, OUTPUT);

  pinMode(CLOCKPIN, OUTPUT);
  pinMode(DATAPIN, OUTPUT);
    pinMode(blank, OUTPUT);
    digitalWrite(blank, LOW);

  pinMode(blank, OUTPUT);
//analogWrite(blank, 100);
  for (int i=0;i<82;i++){
  digitalWrite(LATCHPIN, LOW);
      digitalWrite(DATAPIN, LOW);
          digitalWrite(CLOCKPIN, HIGH);
        digitalWrite(CLOCKPIN, LOW); 
        delay(5);
        digitalWrite(LATCHPIN, HIGH);
        Serial.println(i);
}
}
void loop()
{
  uint32_t grid = 0b01000000000000000000;
 


 for (uint16_t i=32 ; i < 127 ; i++){
     
     //shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, startvar); 
  
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, asciiLookupIV17[i] | grid); //262144
    digitalWrite(LATCHPIN, HIGH);
    //Serial.println(startvar);

    delay(500);
}


}
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint32_t val)
{
    uint8_t i;

    for (i = 0; i < 20; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1ul << i)));   //1ul tells it to use an unisgned long. If we use just 1, its only 16 bits
        else    
            digitalWrite(dataPin, !!(val & (1ul << (19 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);        
    }
}
