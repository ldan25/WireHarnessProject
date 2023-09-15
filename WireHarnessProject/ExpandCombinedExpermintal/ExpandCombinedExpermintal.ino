int ioSelect = 2;     // SR Pin 15.
int clockPulse = 3;   //SR Pin 7. 
int dataOut = 4;      //SR Pin 13.
int clearPin = 5; //Arduino pin 5 connected to Pin 10, SRCLR(Clear/Reset) of 74HC595
int serialData = 6;  //Arduino pin 6 connected to Pin 14, SER(serial input) of 74HC595
int shiftClock = 7;  //Arduino pin 7 connected to Pin 11, SRCLK(shift clock) of 74HC595
int latchClock = 8;  //Arduino pin 8 connected to Pin 12, RCLK(storage/latch clock) of 74HC595 ]

byte leds = 0;

int j;               //used in a for loop to declare which bit is set to 1
int value;           //stores the digital read value of the data pin 
                     //(0 if no button is pressed, 1 if a button is pressed)

byte switchVar = 0;  //stores a byte array to show which button was pressed

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
  leds = 0;
  updateShiftRegister();
  delay(250);
  for (int i = 0; i < 96; i++)
  {
    bitSet(leds, i);
      if (i >= 1){
        int k = i - 1;
        bitClear (leds, k);
      }
    updateShiftRegister();
    delay(250);
  }

  uint32_t  dataIn = 0;       //Swap out byte for uint16_t or uint32_t
  digitalWrite(ioSelect, 0);    // enables parallel inputs
  digitalWrite(clockPulse, 0);  // start clock pin low
  digitalWrite(clockPulse, 1);  // set clock pin high, data loaded into SR
  digitalWrite(ioSelect, 1);    // disable parallel inputs and enable serial output 

    for(j = 0; j < 48; j++) {         //sets integer to values 0 through 7 for all 8 bits
      value = digitalRead(dataOut); //reads data from SR serial data out pin
      Serial.print("Button Position: "); // checks bit position 0-7
      Serial.println(j);
      Serial.print("Button Value: ");  //checks whether button was pressed (high vs low)
      Serial.println(value);
      if (value) {
        int a = (1 << j);       // shifts bit to its proper place in sequence. 
                              /*for more information see Arduino "BitShift" */
        dataIn = dataIn | a;    //combines data from shifted bits to form a single 8-bit number
                              /*for more information see Arduino "Bitwise operators" */
        }
        digitalWrite(clockPulse, LOW);  //after each bit is logged, 
        digitalWrite(clockPulse, HIGH); //pulses clock to get next bit
    }
    /*   if (switchVar != dataIn)
    {
      switchVar = dataIn;
      Serial.print("dataIn DEC: "); // Will show readout of data in decimal
      Serial.print(dataIn, DEC);
      Serial.println();
      Serial.print("dataIn BIN: "); //Will show readout of data in binary
      Serial.print(dataIn, BIN);
      Serial.println();
    } */
 delay(20000); //short delay added for debugging
  
}

void updateShiftRegister() {
   digitalWrite(latchClock, LOW);    
          // take the latchClock low so 
          // the LEDs don't change while you're sending in bits:


   shiftOut(serialData, shiftClock, MSBFIRST, leds);      // shift out the bits
   digitalWrite(latchClock, HIGH);     //take the latch pin high so the LEDs will light up
   delay(250);     // pause before next value
}
