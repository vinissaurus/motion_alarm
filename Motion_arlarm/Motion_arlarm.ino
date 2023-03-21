#define VOLT_READ         A7          // VOLTAGE DROP READING PIN
#define S_PIN             2           // MOTION SENSOR PIN
#define T_PIN             8           // TONE PIN
#define T_PITCH           1980        // TONE PITCH
#define T_LONG_TIME       300         // LONG TONE DURATION IN MS
#define T_SHORT_TIME      100         // SHORT TONE DURATION IN MS
#define WORKING_RATE      10          // UPDATING RATE
#define ONE               1           // REFERENCE ON MY FORMER BOSS, A.K.A "sMARTEST GUY IN THE wORLD"
#define MIN_BEEP          5           // MINIMUM OF BEEPS TO MAKE SOME NOISE

uint8_t S_STATE = 0;                  // FOR READING THE STATE OF THE SENSOR
uint8_t S_STATE_LAST = 0;             // PREVIOUS STATE OF THE SENSOR
uint8_t beep_counter = 0;             // BEEPS TO BE SOUNDED
uint16_t step_counter = 0;            // STEPS TO COUNT, MAYBE USELESS, WE'LL SEE
uint16_t T_TIME = T_LONG_TIME;        // BEEP TIME DURATION
unsigned long time_counter = 0;       // TIME COUNTER TO KEEP TRACK OF BEEPS
unsigned long current_time = 0;       // TIME COUNTER FOR SOMETHING
uint16_t VOLT_MAX = 0;                // MAX REGISTERED VOLTAGE 
uint16_t VOLT_CURRENT = 0;            // CURRENT VOLTAGE

void setup()
{
  Serial.begin(9600);
  Serial.println("Init!");
  pinMode(T_PIN, OUTPUT);
  pinMode(S_PIN, INPUT);
  pinMode(VOLT_READ, INPUT);

  // BARELY TYPICAL ALARM ARMING SOUND
  tone(T_PIN, T_PITCH, T_SHORT_TIME);
  delay(T_SHORT_TIME);
  noTone(T_PIN);
  delay(50);
  tone(T_PIN, T_PITCH, T_SHORT_TIME);
  delay(T_SHORT_TIME);
  noTone(T_PIN);

  S_STATE = digitalRead(S_PIN);
  S_STATE_LAST = S_STATE;
}

void loop()
{
  // READING
  S_STATE = digitalRead(S_PIN);
  VOLT_CURRENT = analogRead(VOLT_READ);

  // ACTIONS
  if(VOLT_CURRENT>VOLT_MAX){
    VOLT_MAX = VOLT_CURRENT;
  }
  if(VOLT_CURRENT < VOLT_MAX - 50){
    // ACTIONS FOR DISARMING OR JUST BEEP
    // TEST WITH BUZZER AND CAP
  }

  if (S_STATE_LAST != S_STATE)
  {
    if (beep_counter == 0)
    {
      beep_counter+=MIN_BEEP;
    }
    else
    {
      beep_counter += beep_counter;
    }

    if(beep_counter>MIN_BEEP)
    {
      T_TIME = T_LONG_TIME/2;
    }
    else
    {
      T_TIME = T_LONG_TIME;
    }
   
  }

  if (beep_counter > 0)
  {
    current_time = millis();
    // FIRST THE BEEP
    if (time_counter == 0)
    {
      tone(T_PIN, T_PITCH, T_LONG_TIME);
      time_counter = current_time;
    }
    // THEN THE BEEP PAUSE
    else if (current_time >= time_counter + T_TIME && current_time < time_counter + T_TIME + T_SHORT_TIME)
    {
      noTone(T_PIN);
    }
    else if (current_time >= time_counter + T_TIME + T_SHORT_TIME)
    {
      beep_counter--;
      time_counter = 0;
    }
  }

  S_STATE_LAST = digitalRead(S_PIN);

  step_counter++;
  if (step_counter >= WORKING_RATE + T_SHORT_TIME)
  {
    step_counter = 0;
  }
  // delay(ONE);
}
