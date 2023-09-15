int clearPin = 5; //Arduino pin 5 connected to Pin 10, SRCLR(Clear/Reset) of 74HC595
int serialData = 6;  //Arduino pin 6 connected to Pin 14, SER(serial input) of 74HC595
int shiftClock = 7;  //Arduino pin 7 connected to Pin 11, SRCLK(shift clock) of 74HC595
int latchClock = 8;  //Arduino pin 8 connected to Pin 12, RCLK(storage/latch clock) of 74HC595 ]

int ioSelect = 2;     // SR Pin 15.
int clockPulse = 3;   //SR Pin 7. 
int dataOut = 4;      //SR Pin 13.

int j;
int value;

byte switchVar = 0;  //stores a byte array to show which button was pressed

byte leds = 0;
int k = 0;

void setup() {   //runs once at startup
   //set pins to output so you can control the shift register
  pinMode(clearPin, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(serialData, OUTPUT);

  pinMode(ioSelect, OUTPUT);
  pinMode(clockPulse, OUTPUT);
  pinMode(dataOut, INPUT);  

  

  digitalWrite(clearPin, LOW); //Pin is active-low, this clears the shift register
  digitalWrite(clearPin, HIGH); //Clear pin is inactive

  Serial.begin(9600);  //setting baud rate
}


void loop() {
  updateShiftRegister();
  delay(250);

  if(k >= 1){
    bitSet(leds, k);
  }

  else {
    bitSet(leds, 0);
  }
  
  for (int i = 0; i < 12; i++){
    updateShiftRegister();
    bitClear (leds, i);



    digitalWrite(ioSelect, 0);    // enables parallel inputs
    digitalWrite(clockPulse, 0);  // start clock pin low
    digitalWrite(clockPulse, 1);  // set clock pin high, data loaded into SR
    digitalWrite(ioSelect, 1);    // disable parallel inputs and enable serial output 

    for(j = 0; j < 48; j++) {         //sets integer to values 0 through 7 for all 8 bits

      if(value = 1){
      value = digitalRead(dataOut); //reads data from SR serial data out pin

      Serial.print("Button Position: "); // checks bit position 0-7
      Serial.println(j);
      Serial.print("Button Value: ");  //checks whether button was pressed (high vs low)
      Serial.println(value);

      digitalWrite(clockPulse, LOW);  //after each bit is logged, 
      digitalWrite(clockPulse, HIGH); //pulses clock to get next bit
    }
    }
//    delay(250);
  }
  k++;
}

void updateShiftRegister() {
   digitalWrite(latchClock, LOW);    
          // take the latchClock low so 
          // the LEDs don't change while you're sending in bits:


   shiftOut(serialData, shiftClock, MSBFIRST, leds);      // shift out the bits
   digitalWrite(latchClock, HIGH);     //take the latch pin high so the LEDs will light up
   delay(250);     // pause before next value
}
