// Constants
const int NUM_MOVES = 1000;
const int NUM_POINTS = 4;
const int DURATION = 1000; // us
const int X_POINTS[NUM_POINTS] = {0, 1023, 1023, 0};
const int Y_POINTS[NUM_POINTS] = {0, 0, 1023, 1023};

int BM_COORDS[][2] = {
    {1,6},
    {2,8},
    {1,5},
    {2,4},
    {3,4},
    {4,5},
    {5,7},
    {4,9},
    {6,6},
    {7,4},
    {7,0},
    {6,-4},
    {4,-7},
    {5,-5},
    {4,-3},
    {3,-2},
    {2,-1},
    {1,-3},
    {0,-6},
    {-1,-3},
    {-2,-2},
    {-3,-1},
    {-4,-3},
    {-5,-4},
    {-4,-7},
    {-6,-4},
    {-7,0},
    {-7,4},
    {-6,6},
    {-4,9},
    {-5,7},
    {-4,5},
    {-3,4},
    {-2,4},
    {-1,5},
    {-2,8},
    {-1,6}
};

// Pin constants
const int xPin = 11;
const int yPin = 12;
const int laserPin = 7;

// Variables
int xPos = 0;
int yPos = 0;

void setup() {

  for (int i = 0; i < NUM_POINTS; ++i) {
    BM_COORDS[i][0] = map(BM_COORDS[i][0], -10, 10, 0, 1024);
    BM_COORDS[i][1] = map(BM_COORDS[i][1], -10, 10, 0, 1024);
  }

  // Set output pins
  pinMode(xPin, OUTPUT);
  pinMode(yPin, OUTPUT);
  pinMode(laserPin, OUTPUT);

  digitalWrite(laserPin, HIGH);

  // Set PWM settings (Phase correct 10-bit with N=1 on output A and B)
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11) | (1<<WGM10);
  TCCR1B = (1<<CS10);
}

void loop() {
  for(int i = 0; i < NUM_POINTS; ++i) {
    gotoPos(X_POINTS[i], Y_POINTS[i], DURATION);
    delay(1);
  }
}

void gotoPos(int newX, int newY, double duration) {
  double xIncr = double(newX - xPos) / double(NUM_MOVES);
  double yIncr = double(newY - yPos) / double(NUM_MOVES);
  
  double moveDelay = duration / double(NUM_MOVES);

  double xPosTmp = xPos;
  double yPosTmp = yPos;

  for(int i = 0; i < NUM_MOVES; ++i) {
    xPosTmp += xIncr;
    yPosTmp += yIncr;
    
    analogWrite(xPin, xPosTmp);
    analogWrite(yPin, yPosTmp);
    delayMicroseconds(moveDelay);
  }

  analogWrite(xPin, newX);
  analogWrite(yPin, newY);

  xPos = newX;
  yPos = newY;
}
