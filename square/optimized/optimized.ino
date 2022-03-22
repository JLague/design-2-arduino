// Constants
const int NUM_MOVES = 2000;
const int NUM_POINTS = 2;
const int DURATION = 1; // us
const int X_POINTS[NUM_POINTS] = {0, 255};
const int Y_POINTS[NUM_POINTS] = {0, 0};

const byte SCAN_END = B10;
const byte PATTERN_END = B11;

// Pin constants
const int xPin = 11;
const int yPin = 12;
const int laserPin = 7;
const int diodePin = 13;

// Variables
int xPos = 0;
int yPos = 0;


void setup() {

  Serial.begin(1000000);

  // Set output pins
  pinMode(xPin, OUTPUT);
  pinMode(yPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(diodePin, INPUT);

  digitalWrite(laserPin, HIGH);

  // Set PWM settings (Phase correct 10-bit with N=1 on output A and B)
//  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM12) | (1<<WGM11) | (1<<WGM10);
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (0<<WGM13) | (1<<WGM12) | (0<<WGM11) | (1<<WGM10);
  TCCR1B = (1<<CS10);
}

void loop() {
  for (int i = 0; i < 2048; ++i) {
    Serial.write(((unsigned int)PINB & B10000000) >> 7);
    OCR1A = i/8;
  }
  for (int i = 2047; i >= 0; --i) {
    Serial.write(((unsigned int)PINB & B10000000) >> 7);
    OCR1A = i/8;
  }
  Serial.write(2);
}
