// Constants
const int NUM_MOVES = 1000;
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

// Variables
int xPos = 0;
int yPos = 0;


void setup() {

  Serial.begin(1000000);

//  for (int i = 0; i < NUM_POINTS; ++i) {
//    BM_COORDS[i][0] = map(BM_COORDS[i][0], -10, 10, 0, 1024);
//    BM_COORDS[i][1] = map(BM_COORDS[i][1], -10, 10, 0, 1024);
//  }

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
  for(int i = 0; i < 2; ++i) {
    gotoPos(X_POINTS[0], 0, DURATION);
//    gotoPos(X_POINTS[0], 0, DURATION);
    gotoPos(X_POINTS[1], 0, DURATION);
//    for (int j = 0; j < 100; ++j) {
//      rw_diode();
//      delayMicroseconds(1);
//    }
  }
//  for(int i = 0; i < NUM_POINTS; ++i) {
//    gotoPos(X_POINTS[i], 0, DURATION);
////    delayMicroseconds(1000);
//  }
//  for (int i = 0; i < NUM_MOVES + 1; ++i) {
//    Serial.write(code1[i]);
////    Serial.println(code1[i]);
//    
//  }
//  for (int i = 0; i < NUM_MOVES+1; ++i) {
//    Serial.write(code2[i]);
//  }

//  free(code1);
//  free(code2);

  
  
  write_flags(SCAN_END);
  Serial.flush();
//  delay(1000);
}

byte* gotoPos(int newX, int newY, double duration) {
  double xIncr = double(newX - xPos) / double(NUM_MOVES);
  double yIncr = double(newY - yPos) / double(NUM_MOVES);
  
//  double moveDelay = duration / double(NUM_MOVES);

  double xPosTmp = xPos;
  double yPosTmp = yPos;

//  byte* code = (byte*) malloc((NUM_MOVES+1) * sizeof(byte));
//  byte code[NUM_MOVES+1];
  

//  rw_diode();

  for(int i = 0; i < NUM_MOVES; ++i) {
    xPosTmp += xIncr;
    yPosTmp += yIncr;
    
//    code[i] = ((unsigned int)PINB & B10000000) >> 7;
    
 //digitalRead(readPin);
//    Serial.write((PINB & B10000000) >> 7)
//    rw_diode(0);

//    val = digitalRead(readPin);
//    const uint8_t buffer[] = {val, 0};
//    Serial.write(buffer, 2);
    
//    analogWrite(xPin, xPosTmp);
//    analogWrite(yPin, yPosTmp);
    OCR1A = xPosTmp;
    OCR1B = yPosTmp;
//    delayMicroseconds(moveDelay);
    rw_diode();
  }

//  code[NUM_MOVES] = digitalRead(readPin);
//  rw_diode(1);
//  val = digitalRead(readPin);
//  const uint8_t buffer[] = {val, 1};
//  Serial.write(buffer, 2);

//  analogWrite(xPin, newX);
//  analogWrite(yPin, newY);
  OCR1A = newX;
  OCR1B = newY;
//  rw_diode();
//  code[NUM_MOVES] = ((unsigned int)PINB & B10000000) >> 7;


//  for (int i = 0; i <= NUM_MOVES; ++i) {
//    Serial.write(code[i]);
//  }
  rw_diode();
//  write_flags(SCAN_END);
//  Serial.flush();

//  for (int i = 0; i < NUM_MOVES+1; ++i) {
//    Serial.write(code[i]);
//  }
//  Serial.write(2);
//  const uint8_t buf[] = code;
//  Serial.write(buf, NUM_MOVES+1);

  xPos = newX;
  yPos = newY;

//  return code;
}

size_t rw_diode() {
  return Serial.write(((unsigned int)PINB & B10000000) >> 7);
//  int val = digitalRead(readPin);
//  if (flag == 1) {
//    Serial.println(2)
//  } else {
//    Serial.println(val);
//  }
//  Serial.println(val);
//  const uint8_t buffer[] = {val, flag};
//  Serial.write(buffer, 2);
//  Serial.flush();
}

size_t write_flags(byte flags) {
  return Serial.write(flags);
}
