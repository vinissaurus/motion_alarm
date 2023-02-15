
#define S_PIN 2          // MOTION SENSOR PIN
#define T_PIN 8          // TONE PIN
#define T_PITCH 440      // TONE PITCH
#define T_LONG_TIME 2000 // LONG TONE DURATION IN MS
#define T_SHORT_TIME 500 // SHORT TONE DURATION IN MS
#define WORKING_RATE 10 // UPDATING RATE

uint8_t S_STATE = 0;
uint8_t S_STATE_LAST = 0;


void setup() {
  Serial.begin(9600);
  pinMode(T_PIN,OUTPUT);
  pinMode(S_PIN,INPUT);

  // TYPICAL ALARM ARMING SOUND
  tone(T_PIN,T_PITCH,T_SHORT_TIME);
  delay(T_SHORT_TIME);
  noTone(T_PIN);
  tone(T_PIN,T_PITCH,T_SHORT_TIME);
  delay(T_SHORT_TIME);
  noTone(T_PIN);

  S_STATE = digitalRead(S_PIN);
  S_STATE_LAST = S_STATE;
}

uint8_t beep_counter = 0;
void loop() {

  S_STATE = digitalRead(S_PIN);

  if(S_STATE_LAST !=S_STATE)
  {
    Serial.print("BEEP - ");
    Serial.print(beep_counter);
    Serial.println();
    beep_counter++;
  }

  S_STATE_LAST = digitalRead(S_PIN);
  // delay(WORKING_RATE);
}
