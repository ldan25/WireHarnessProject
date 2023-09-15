int clockPin = 2;

int latchPin = 3;

int dataPin = 4;

byte leds = 0;

void setup() {

pinMode(latchPin, OUTPUT);

pinMode(dataPin, OUTPUT);

pinMode(clockPin, OUTPUT);

}

void loop() {

leds = 0;

updateShiftRegisterR();

delay(100);

for (int i = 0; i < 8; i++){

bitSet(leds, i);

updateShiftRegisterR();

delay(100);

}

leds = 0;

updateShiftRegisterL();

delay(100);

for (int i = 0; i < 8; i++){

bitSet(leds, i);

updateShiftRegisterL();

delay(100);

}

}

void updateShiftRegisterL(){

digitalWrite(latchPin, LOW);

shiftOut(dataPin, clockPin, MSBFIRST, leds);

digitalWrite(latchPin, HIGH);

}

void updateShiftRegisterR(){

digitalWrite(latchPin, LOW);

shiftOut(dataPin, clockPin, LSBFIRST, leds);

digitalWrite(latchPin, HIGH);

}
