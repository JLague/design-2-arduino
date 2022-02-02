// Constants
const int DELAY_20HZ = 470; // microseconds
const int DELAY_1HZ = 10; // milliseconds
const int DELAY_RATIO = (DELAY_1HZ*1000) / DELAY_20HZ;
const int NUM_SAMPLES = 100; // samples
const int INCREMENT = 64;
const int DELAY = 500;

// Pin constants
const int xPin = 11;
const int yPin = 12;

enum sweepState {
  sweep,
  incUp,
  incDown
};

// Variables
//int upSweep[NUM_SAMPLES/2];
//int downSweep[NUM_SAMPLES/2];
int triTable[NUM_SAMPLES];
unsigned long prevMicros;
int count = 0;
int yVal = 0;
//sweepState state = xUp;

void setup() {
  // Set output pins
  pinMode(xPin, OUTPUT);
  pinMode(yPin, OUTPUT);

  for(int i = 0; i < NUM_SAMPLES/2; ++i) {
    triTable[i] = int((1023.0*i) / 50);
  }
  for(int i = NUM_SAMPLES/2; i < NUM_SAMPLES; ++i) {
    triTable[i] = 2046 - int((1023.0*i) / 50);
  }

  // Set PWM settings (Phase correct 10-bit with N=1 on output A and B)
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11) | (1<<WGM10);
  TCCR1B = (1<<CS10);
}

void loop() {
  unsigned long curMicros = micros();

  if(curMicros - prevMicros > DELAY) {
    OCR1B = triTable[count++];
    prevMicros = curMicros;
    count %= NUM_SAMPLES;
    
//    if(count == NUM_SAMPLES) {
//      count = 0;
//      switch (yState) {
//        case incUp:
//          yVal += INCREMENT;
//          break;
//        case incDown:
//          yVal -= INCREMENT;
//          break;
//      }
//      if(yVal > 1023) {
//        yState
//      }
//      
//    }
  }
  
}
