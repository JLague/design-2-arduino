/**
  Prototype - Équipe 12 - PIE Engineering
  Name: smooth
  Purpose: Smoothly move galvanometers and sample barcode with photodiode

  @author Justin Lagüe
  @version 0.1
*/

// Points
const int NUM_POINTS = 2;
const int X_POINTS[NUM_POINTS] = {0, 255};
const int Y_POINTS[NUM_POINTS] = {0, 0};

// Star pattern
//const unsigned NUM_POINTS = 51;
//const uint8_t X_POINTS[NUM_POINTS] = {254, 0, 253, 2, 250, 6, 245, 12, 238, 20, 230, 29, 220, 40, 208, 52, 195, 66, 181, 80, 166, 95, 151, 111, 135, 127, 119, 143, 103, 159, 88, 174, 73, 188, 59, 202, 46, 214, 34, 225, 24, 234, 16, 242, 9, 248, 4, 252, 1, 254, 0};
//const uint8_t Y_POINTS[NUM_POINTS] = {127, 135, 111, 151, 95, 166, 80, 181, 66, 195, 52, 208, 40, 220, 29, 230, 20, 238, 12, 245, 6, 250, 2, 253, 0, 254, 0, 253, 2, 250, 6, 245, 12, 238, 20, 230, 29, 220, 40, 208, 52, 195, 66, 181, 80, 166, 95, 151, 111, 135, 127};

// Flags
const uint8_t SCAN_END = B10;
const uint8_t PATTERN_END = B11;

// Pin constants
const uint8_t X_PIN = 11;
const uint8_t Y_PIN = 12;
const uint8_t LASER_PIN = 7;
const uint8_t DIODE_PIN = 13;

// General constants
const unsigned long BAUDRATE = 9600;
const unsigned int NUM_SAMPLES = 1000;
const unsigned int SAMPLE_TIME = 1000; // us
const uint8_t NUM_TESTS = 2;

// Variables
uint8_t pos_x = 0;
uint8_t pos_y = 0;

void goto_pos(const unsigned int &new_x, const unsigned int &new_y, const unsigned int &num_samples, const unsigned int &sample_time);
void set_pos(unsigned int &x, unsigned int &y);
void rw_diode();
void write_flags(uint8_t flags);

void setup() {
  // Set pin modes
  pinMode(X_PIN, OUTPUT);
  pinMode(Y_PIN, OUTPUT);
  pinMode(LASER_PIN, OUTPUT);
  pinMode(DIODE_PIN, INPUT);

  // Start laser
  digitalWrite(LASER_PIN, HIGH);

  // Set PWM settings (8-bit Fast PWM with N=1 on output A and B)
  // For PWM types, see https://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf#page=145
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (0<<WGM13) | (1<<WGM12) | (0<<WGM11) | (1<<WGM10);
  TCCR1B = (1<<CS10);

  Serial.begin(BAUDRATE);
}

void loop() {
  // Do n swipes (for tests)
  for(int i = 0; i < NUM_TESTS; ++i) {
    goto_pos(X_POINTS[0], 0, NUM_SAMPLES, SAMPLE_TIME);
    goto_pos(X_POINTS[1], 0, NUM_SAMPLES, SAMPLE_TIME);
  }

  /* Uncomment for 2D scan */
//  for(int i = 0; i < NUM_POINTS; ++i) {
//    goto_pos(X_POINTS[i], Y_POINTS[i], NUM_SAMPLES, SAMPLE_TIME);
//  }
  
  write_flags(SCAN_END);
  Serial.flush();
}

/**
  Move galvanometers to a new position while sampling photodiode.

  @param new_x New x position.
  @param new_y New y position.
  @param num_samples Number of samples/steps between old and new position.
  @param sample_time Time in ms between samples/steps.
 */
void goto_pos(const unsigned int &new_x, const unsigned int &new_y, const unsigned int &num_samples, const unsigned int &sample_time) {
  const float incr_x = ((float)new_x - pos_x) / num_samples;
  const float incr_y = ((float)new_y - pos_y) / num_samples;

  float tmp_x = pos_x;
  float tmp_y = pos_y;

  for(int i = 0; i < num_samples; ++i) {
    tmp_x += incr_x;
    tmp_y += incr_y;
   
    set_pos((unsigned int)tmp_x, (unsigned int)tmp_y);
    rw_diode();
    
    delayMicroseconds(sample_time);
  }

  set_pos(new_x, new_y);
  rw_diode();
  
  pos_x = new_x;
  pos_y = new_y;
}

/**
  Move galvanometers to the desired position.

  @param x The x coordinate
  @param y The y coordinate
*/
void set_pos(const unsigned int &x, const unsigned int &y) {
  OCR1A = x;
  OCR1B = y;
}

/**
  Read digital value from photodiode and write to serial connection.

  Read one (1) byte from PINB7 (pin 13 for the Arduino Mega 2560)
  and write it to the serial connection.
*/
void rw_diode() {
  uint8_t diode_val = (PINB & (1<<PINB7)) >> PINB7;
  Serial.write(diode_val);
}

/**
  Write flags to the serial connection.

  @param flags Flags to write.
*/
void write_flags(uint8_t flags) {
  Serial.write(flags);
}
