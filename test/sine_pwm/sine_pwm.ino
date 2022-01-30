// Constants
const int DELAY_20HZ = 500; // microseconds
const int DELAY_1HZ = 10; // milliseconds
const int DELAY_RATIO = (DELAY_1HZ*1000) / DELAY_20HZ;
const int NUM_SAMPLES = 100; // samples

// Pin constants
const int fastSinePin = 11;
const int slowSinePin = 12;

// Variable
int sineTable[NUM_SAMPLES];
int fastCount = 0;

void setup() {
  // Set output pins
  pinMode(fastSinePin, OUTPUT);
  pinMode(slowSinePin, OUTPUT);

  // Generate 10-bit sine wave pattern
  for(int i=0;i<NUM_SAMPLES;i++) {
    sineTable[i]= 512+511*sin(2*PI*i/NUM_SAMPLES);
  }
  
  // Set PWM settings (Phase correct 10-bit with N=1 on output A and B)
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11) | (1<<WGM10);
  TCCR1B = (1<<CS10);
}

void loop() {
  for (int i = 0; i < NUM_SAMPLES; ++i) {
    // Iterate over values for slow sine
    
    for (int j = 0; j < DELAY_RATIO; ++j) {
      // Iterate over values for fast sine
      
      OCR1A = sineTable[fastCount++];
      fastCount %= NUM_SAMPLES;
      delayMicroseconds(DELAY_20HZ);
    }
    OCR1B = sineTable[i];
  }
}
