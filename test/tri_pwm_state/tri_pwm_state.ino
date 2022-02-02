// Constants
const int DELAY_20HZ = 500; // microseconds
const int DELAY_1HZ = 10; // milliseconds
const int DELAY_RATIO = (DELAY_1HZ*1000) / DELAY_20HZ;
const int NUM_SAMPLES = 100; // samples
const int INCREMENT = 64;
const int DELAY = 500;

// Pin constants
const int xPin = 11;
const int yPin = 12;

enum sweepState {
  x,
  y
};

// Variables
//int upSweep[NUM_SAMPLES/2];
//int downSweep[NUM_SAMPLES/2];
int triTable[NUM_SAMPLES];
unsigned long prevMicros;
int count = 0;
//sweepState state = xUp;

void setup() {
  
  // Set output pins
  pinMode(xPin, OUTPUT);
//  pinMode(yPin, OUTPUT);

  // Generate triangle wave pattern on 10 bits
  for(int i = 0; i < NUM_SAMPLES/2; ++i) {
    triTable[i] = ((1023*i) / 50);
  }
  for(int i = NUM_SAMPLES/2; i < NUM_SAMPLES; ++i) {
    triTable[i] = 2046 - ((1023*i)/50);
  }

  Serial.begin(9600);

//  for(int i = 0; i < NUM_SAMPLES/2; ++i) {
//    upSweep[i] = (1023*i) / 50;
//    downSweep[i] = 1023 - (1023*i)/50;
//  }

  // Set PWM settings (Phase correct 10-bit with N=1 on output A and B)
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11) | (1<<WGM10);
  TCCR1B = (1<<CS10);

  analogWrite(xPin, 0);
//  analogWrite(yPin, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long curMicros = micros();

  if(curMicros - prevMicros > DELAY) {
    analogWrite(xPin, triTable[count++]);
    prevMicros = curMicros;
    Serial.print(triTable[count-1]);
    Serial.print("\n");
    if(count == NUM_SAMPLES) {
      count = 0;
    }
  }
  
}

sweepState toggleSweepState(sweepState state) {
  sweepState newState;
  switch (state) {
    case x:
      newState = y;
      break;
    case y:
      newState = x;
  }
  return newState;
}
