/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 */
 
int led_1 = 0;
int led_2 = 1;
int led_3 = 4;

void PWM4_init() {
// Set up PWM on Trinket GPIO #4 (PB4, pin 3) using Timer 1
TCCR1 = _BV (CS10); // no prescaler
GTCCR = _BV (COM1B1) | _BV (PWM1B); // clear OC1B on compare
OCR1B = 127; // duty cycle initialize to 50%
OCR1C = 255; // frequency
}

void analogWrite4(int led, int val) {
    if (led==4) { OCR1B = val; }
    else { analogWrite(led, val); }
}

void setup() {                
  // initialize the digital pins as an output.
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  PWM4_init();
}

// states for 3 led strands
// 0 = off
// 1 = turning on
// 2 = on
// 3 = turning off
uint8_t state_1 = 0;
uint8_t state_2 = 2;
uint8_t state_3 = 3;

int count_1 = 0;
int count_2 = 50;
int count_3 = 100;

void update(int led, uint8_t *state, int *count) {
  switch (*state) {
    case 0: // off and waiting
      *count += 1;
      if (*count >= 50) {
        *state = 1; *count = 0;
      }
      break;
    case 1: // coming on, slowly
      *count += 1;
      analogWrite4(led, *count);
      if (*count >= 128) {
        *state = 2; *count = 0;
      }
      break;
    case 2: // on and waiting
      *count += 1;
      if (*count >= 100) {
        *state = 3; *count = 0;
      }
      break;
    case 3: // going off, slowly
      *count += 1;
      analogWrite4(led, 128 - *count);
      if (*count >= 128) {
        *state = 0; *count = 0;
      }
      break;
  }
}

void loop() {
  update(led_1, &state_1, &count_1);
  update(led_2, &state_2, &count_2);
  update(led_3, &state_3, &count_3);
  delay(20);
}


