// Constants
const int DELAY_20HZ = 500; // microseconds
const int DELAY_1HZ = 10; // milliseconds
const int DELAY_RATIO = (DELAY_1HZ*1000) / DELAY_20HZ;
const int NUM_SAMPLES = 100; // samples

// Variable
int sineTable[NUM_SAMPLES];
int fastCount = 0;

void setup() {
  // Set PORTB and PORTL pins to output (1)
  DDRB = 0xFF;
  DDRL = 0xFF;

  // Sine pattern
  for(int i=0;i<NUM_SAMPLES;i++) {
    sineTable[i]= 128+127*sin(2*PI*i/NUM_SAMPLES);
  }
}

void loop() {
  for (int i = 0; i < NUM_SAMPLES; ++i) {
    // Iterate over values for slow sine
    
    for (int j = 0; j < DELAY_RATIO; ++j) {
      // Iterate over values for fast sine
      
      PORTB = sineTable[fastCount++];
      fastCount %= NUM_SAMPLES;
      delayMicroseconds(DELAY_20HZ);
    }
    PORTL = sineTable[i];
  }
}
