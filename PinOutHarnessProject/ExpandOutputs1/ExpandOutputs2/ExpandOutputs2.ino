int clearPin = 5; //Arduino pin 5 connected to Pin 10, SRCLR(Clear/Reset) of 74HC595
int serialData = 6;  //Arduino pin 6 connected to Pin 14, SER(serial input) of 74HC595
int shiftClock = 7;  //Arduino pin 7 connected to Pin 11, SRCLK(shift clock) of 74HC595
int latchClock = 8;  //Arduino pin 8 connected to Pin 12, RCLK(storage/latch clock) of 74HC595 ]

int numOfRegisters = 2;
byte* registerState;

long effectId = 0;
long prevEffect = 0;
long effectRepeat = 0;
long effectSpeed = 30;

void setup() {   //runs once at startup
   //set pins to output so you can control the shift register
  pinMode(clearPin, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(serialData, OUTPUT);


  digitalWrite(clearPin, LOW); //Pin is active-low, this clears the shift register
  digitalWrite(clearPin, HIGH); //Clear pin is inactive

    //Initialize array
  registerState = new byte[numOfRegisters];
  for (size_t i = 0; i < numOfRegisters; i++) {
    registerState[i] = 0;
  }
}

void loop() {
  do{
    effectId = random(6);
  } while (effectId == prevEffect);
  prevEffect = effectId;

  switch (effectId)
  {
  case 0:
    effectRepeat = random(1, 2);
    break;
  case 1:
    effectRepeat = random(1, 2);
    break;
  case 3:
    effectRepeat = random(1, 5);
    break;
  case 4:
    effectRepeat = random(1, 2);
    break;
  case 5:
    effectRepeat = random(1, 2);
    break;
  }

  for (int i = 0; i < effectRepeat; i++) {
    effectSpeed = random(10, 90);

    switch (effectId)
    {
    case 0:
      effectA(effectSpeed);
      break;
    case 1:
      effectB(effectSpeed);
      break;
    case 3:
      effectC(effectSpeed);
      break;
    case 4:
      effectD(effectSpeed);
      break;
    case 6:
      effectE(effectSpeed);
      break;
    }
  }
}

void effectA(int speed){
  for (int i = 0; i < 16; i++){
    for (int k = i; k < 16; k++){
      regWrite(k, HIGH);
      delay(speed);
      regWrite(k, LOW);
    }

    regWrite(i, HIGH);
  }
}

void effectB(int speed){
  for (int i = 15; i >= 0; i--){
    for (int k = 0; k < i; k++){
      regWrite(k, HIGH);
      delay(speed);
      regWrite(k, LOW);
    }

    regWrite(i, HIGH);
  }
}

void effectC(int speed){
  int prevI = 0;
  for (int i = 0; i < 16; i++){
    regWrite(prevI, LOW);
    regWrite(i, HIGH);
    prevI = i;

    delay(speed);
  }

  for (int i = 15; i >= 0; i--){
    regWrite(prevI, LOW);
    regWrite(i, HIGH);
    prevI = i;

    delay(speed);
  }
}

void effectD(int speed){
  for (int i = 0; i < 8; i++){
    for (int k = i; k < 8; k++)
    {
      regWrite(k, HIGH);
      regWrite(15 - k, HIGH);
      delay(speed);
      regWrite(k, LOW);
      regWrite(15 - k, LOW);
    }

    regWrite(i, HIGH);
    regWrite(15 - i, HIGH);
  }
}

void effectE(int speed){
  for (int i = 7; i >= 0; i--){
    for (int k = 0; k <= i; k++)
    {
      regWrite(k, HIGH);
      regWrite(15 - k, HIGH);
      delay(speed);
      regWrite(k, LOW);
      regWrite(15 - k, LOW);
    }

    regWrite(i, HIGH);
    regWrite(15 - i, HIGH);
  }
}

void regWrite(int pin, bool state){
  //Determines register
  int reg = pin / 8;
  //Determines pin for actual register
  int actualPin = pin - (8 * reg);

  //Begin session
  digitalWrite(latchClock, LOW);

  for (int i = 0; i < numOfRegisters; i++){
    //Get actual states for register
    byte* states = &registerState[i];

    //Update state
    if (i == reg){
      bitWrite(*states, actualPin, state);
    }

    //Write
    shiftOut(serialData, shiftClock, MSBFIRST, *states);
  }

  //End session
  digitalWrite(latchClock, HIGH);
}
