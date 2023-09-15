int clearPin = 5; //Arduino pin 5 connected to Pin 10, SRCLR(Clear/Reset) of 74HC595
int serialData = 6;  //Arduino pin 6 connected to Pin 14, SER(serial input) of 74HC595
int shiftClock = 7;  //Arduino pin 7 connected to Pin 11, SRCLK(shift clock) of 74HC595
int latchClock = 8;  //Arduino pin 8 connected to Pin 12, RCLK(storage/latch clock) of 74HC595 ]

byte leds[] = {00000001,
00000000,
00000000,
00000000,
00000000,
00000000,
00000000,
00000000};

void setup() {   //runs once at startup
   //set pins to output so you can control the shift register
  pinMode(clearPin, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(serialData, OUTPUT);


  digitalWrite(clearPin, LOW); //Pin is active-low, this clears the shift register
  digitalWrite(clearPin, HIGH); //Clear pin is inactive
}

void loop() 
{

  updateShiftRegister();
  
}

void updateShiftRegister()
{
   digitalWrite(latchClock, LOW);
   for(int i = 0 ; i < 96; i++){
       shiftOut(serialData, shiftClock, MSBFIRST, leds[i]);
   }
   digitalWrite(latchClock, HIGH);
   delay(250);
}
