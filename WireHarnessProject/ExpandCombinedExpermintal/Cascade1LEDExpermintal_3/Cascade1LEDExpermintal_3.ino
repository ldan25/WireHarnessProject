int clearPin = 5; //Arduino pin 5 connected to Pin 10, SRCLR(Clear/Reset) of 74HC595
int serialData = 6;  //Arduino pin 6 connected to Pin 14, SER(serial input) of 74HC595
int shiftClock = 7;  //Arduino pin 7 connected to Pin 11, SRCLK(shift clock) of 74HC595
int latchClock = 8;  //Arduino pin 8 connected to Pin 12, RCLK(storage/latch clock) of 74HC595 ]

byte leds0 = 1;
byte leds1 = 0;
byte leds2 = 0;
byte leds3 = 0;
byte leds4 = 0;
byte leds5 = 0;
byte leds6 = 0;
byte leds7 = 0;
byte leds8 = 0;
byte leds9 = 0;
byte leds10 = 0;
byte leds11 = 0;

void setup() {   //runs once at startup
   //set pins to output so you can control the shift register
  pinMode(clearPin, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(serialData, OUTPUT);


  digitalWrite(clearPin, LOW); //Pin is active-low, this clears the shift register
  digitalWrite(clearPin, HIGH); //Clear pin is inactive
}


void loop() {
  updateShiftRegister();
  delay(250);

  leds0 = leds0 << 1;
  
  if (leds0 == 128){
    leds1 = 1;
    leds1 = leds1 << 1;
  }
  if (leds1 == 128){
    leds2 = 1;
    leds2 = leds2 << 1;
  }
  if (leds2 == 128){
    leds3 = 1;
    leds3 = leds3 << 1;
  }
  if (leds3 == 128){
    leds4 = 1;
  leds4 = leds4 << 1;
  }
  if (leds4 == 128){
    leds5 = 1;
  leds5 = leds5 << 1;
  }
  if (leds5 == 128){
    leds6 = 1;
  leds6 = leds6 << 1;
  }
  if (leds6 == 128){
    leds7 = 1;
  leds7 = leds7 << 1;
  }
  if (leds7 == 128){
    leds8 = 1;
  leds8 = leds8 << 1;
  }
  if (leds8 == 128){
    leds9 = 1;
  leds9 = leds9 << 1;
  }
  if (leds9 == 128){
    leds10 = 1;
  leds10 = leds10 << 1;
  }
  if (leds10 == 128){
    leds11 = 1;
  leds11 = leds11 << 1;
  }
  if (leds11 == 128){
    leds0 = 1;
  leds0 = leds0 << 1;
  }
  
  updateShiftRegister();
  delay(250);
}




void updateShiftRegister() {
   digitalWrite(latchClock, LOW);    
          // take the latchClock low so 
          // the LEDs don't change while you're sending in bits:

   shiftOut(serialData, shiftClock, MSBFIRST, leds11);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds10);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds9);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds8);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds7);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds6);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds5);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds4);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds3);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds2);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds1);      // shift out the bits
   shiftOut(serialData, shiftClock, MSBFIRST, leds0);      // shift out the bits
   
   digitalWrite(latchClock, HIGH);     //take the latch pin high so the LEDs will light up
   delay(250);     // pause before next value
}
