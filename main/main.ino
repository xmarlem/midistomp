/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play the notes
  F#-0 (0x1E) to F#-5 (0x5A) in sequence.

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor
  - Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  created 13 Jun 2006
  modified 13 Aug 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Midi
*/

int pushButton = 9;
int oldValue = 0;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  // Set MIDI baud rate:
  Serial.begin(31250);

  pinMode(pushButton, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  int buttonState = digitalRead(pushButton);

  if ((millis() - lastDebounceTime) > debounceDelay){
    if (buttonState != oldValue){
      oldValue = buttonState;
  
  
      Serial.write(0xB0); // MIDI control change; channel 1
      Serial.write(102); //    CC#102 (unused)
      Serial.write(127); // MIDI controller value from potentiometer 1
      
      delay(300);

      lastDebounceTime = millis();
    }

  }
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}


//  change the voice
void midiCC(byte CC_data, byte c_num, byte c_val){
 Serial.write((byte)c_num);
 Serial.write((byte)CC_data);
 Serial.write((byte)c_val);
}
