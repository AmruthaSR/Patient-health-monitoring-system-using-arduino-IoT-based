#include <Wire.h>
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int PulseWire = 0;
const int LED13 = 13;
int Threshold = 550;
PulseSensorPlayground pulseSensor;
int myBPM;

void setup()
{
  Serial.begin(9600);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();
  Wire.begin(0x07);
  Wire.onRequest(requestEvent);
}

void loop()
{
  myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat())
  {
    Serial.print("BPM: ");
    Serial.println(myBPM);
  }
  delay(10);
}

void requestEvent()
{
  Wire.write(myBPM);
}
