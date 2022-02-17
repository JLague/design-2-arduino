// Constants
const int POINT_DELAY = 100; // ms
const int NUM_POINTS = 4;
const int X_POINTS[NUM_POINTS] = {0, 1023, 1023, 0};
const int Y_POINTS[NUM_POINTS] = {0, 0, 1023, 1023};

// Pin constants
const int xPin = 11;
const int yPin = 12;


void setup() {
  // Set output pins
  pinMode(xPin, OUTPUT);
  pinMode(yPin, OUTPUT);

  // Set PWM settings (Phase correct 10-bit with N=1 on output A and B)
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11) | (1<<WGM10);
  TCCR1B = (1<<CS10);
}

void loop() {
  for(int i = 0; i < NUM_POINTS; ++i) {
    gotoPos(X_POINTS[i], Y_POINTS[i]);
  }
}

void gotoPos(int newX, int newY) {
  analogWrite(xPin, newX);
  analogWrite(yPin, newY);
  delayMicroseconds(POINT_DELAY);
}
