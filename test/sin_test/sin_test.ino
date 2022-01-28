// Constants
const int DELAY_20HZ = 500; // microseconds
const int DELAY_1HZ = 10; // milliseconds
const int TIME_DIFF = DELAY_1HZ*1000/DELAY_20HZ;
const int NUM_SAMPLES = 100; // samples

// Variable
int sinTable[NUM_SAMPLES];
int fastCount = 0;

void setup() {
  // Set PORTB and PORTL pins to output (1)
  DDRB = 0xFF;
  DDRL = 0xFF;

  // Sin pattern
  for(int i=0;i<NUM_SAMPLES;i++) {
    sinTable[i]= 46+46*sin(2*PI*i/NUM_SAMPLES);
  }
}

void loop() {
  for (int value : sinTable) {
    for (int i = 0; i < TIME_DIFF; ++i) {
      PORTB = sinTable[fastCount++];
      fastCount %= NUM_SAMPLES;
      delayMicroseconds(DELAY_20HZ);
    }
    PORTL = value;
  }
}
