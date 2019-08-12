/* 
 * ionZAPPER 2019-08
 * See: biotronics.eu
 * 
 * uC: ATTINY85 8MHz 3.3V
 * See how to install:  http://digistump.com/wiki/digispark/tutorials/connecting
 * 
    1. Arduino: File - Preferences -> Additional Board Manager URLs: http://digistump.com/package_digistump_index.json
    2. Install Digistump AVR Boards by Digistump: Tools -> Board -> Boards Manager...
    3. Install driver (DPInst64): https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip
    4. Tools -> Board -> Digispark(Default - 16.5mhz)
 */

#define PWM_PIN 1 
#define BUZZER_PIN 2
#define BTN_PIN 0

#define maxModes 3

//                     DC   90%  50%
int modes[maxModes] = {255, 230, 128};
int mode = 0;

void beep (int time, int repeat = 0 );


void setup() {
  TCCR0B = TCCR0B & 0b11111000 | 0b001;
  pinMode(PWM_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  analogWrite(PWM_PIN, modes[0]);
  beep(300);
}


void loop() {

  if (digitalRead(BTN_PIN)==LOW){
    delay(100);
    if (digitalRead(BTN_PIN)==LOW) {
      mode+=1;
      if (mode>=maxModes) mode = 0;
      analogWrite(PWM_PIN, modes[mode]);
      beep(200, mode);
    }
  }
}


void beep (int time, int repeat) {

  for (int i=0; i<=repeat;  i++){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(time);
    digitalWrite(BUZZER_PIN, LOW);
    delay(time);
  }
}
