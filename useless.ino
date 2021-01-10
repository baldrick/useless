#include "Debug.h"
#include "NamedServo.h"
#include "Speed.h"
#include "Steps.h"

NamedServo *pArmServo;
NamedServo *pLidServo;
NamedServo *pHeadServo;

const int BUTTON_PIN = 2;

void setup()
{
  Serial.begin(9600);
  DEBUG("Setting up...");
  pinMode(BUTTON_PIN, INPUT);
  pHeadServo = new NamedServo("head", 9, 45, 135, 50);
  pArmServo = new NamedServo("arm", 8, 180, 0, 0);
  pLidServo = new NamedServo("lid", 10, 190, 90, 0);
  delay(100);
  goHome();
  randomSeed(analogRead(0));
  DEBUG("... setup complete");
}

void loop()
{
  if (switchedOn()) {
    switchOff();
  } else {
    goHome();
  }
}

bool switchedOn() {
  TRACE("Reading button state...");
  int buttonState = digitalRead(BUTTON_PIN);  // Read the button position
  String strButtonState = (buttonState == HIGH) ? " " : " not ";
  TRACE("... button is" + strButtonState + "pressed");
  return buttonState == HIGH;
}

void switchOff() {
  int algorithm = random(10);
  switch (algorithm) {
    case 0:
    case 1:
      amy();
      break;
    case 2:
    case 3:
      holly();
      break;
    case 4:
    case 5:
    case 6:
      simple();
      break;
    case 7:
    case 8:
    case 9:
      tentative();
      break;
    default:
      // shouldn't get here!
      DEBUG("WARNING: out of band algorithm chosen: " + String(algorithm) + " but only 0..1 available");
      simple();
      break;
  }
  delay(500);
  goHome();
}

void goHome() {
  pArmServo->goHome();
  pHeadServo->goHome();
  pLidServo->goHome();
  delay(500);
}

void simple() {
  DEBUG("Simple");
  pLidServo->moveToPercent(100, Speed::NORMAL, Steps::MEDIUM);
  pHeadServo->moveToPercent(0, Speed::NORMAL, Steps::MEDIUM);
  pHeadServo->moveToPercent(100, Speed::NORMAL, Steps::MEDIUM);
  pHeadServo->moveToPercent(50, Speed::NORMAL, Steps::MEDIUM);
  pArmServo->moveToPercent(100, Speed::NORMAL, Steps::MEDIUM);
  pArmServo->moveToPercent(0, Speed::NORMAL, Steps::MEDIUM);
  pLidServo->moveToPercent(0, Speed::NORMAL, Steps::MEDIUM);
}

void tentative() {
  DEBUG("Tentative");
  DEBUG("Opening lid slowly");
  pLidServo->moveToPercent(30, Speed::FAST, Steps::SMALL);
  pLidServo->moveToPercent(0, Speed::FAST, Steps::SMALL);
  pLidServo->moveToPercent(100, Speed::FAST, Steps::SMALL);
  pArmServo->moveToPercent(30, Speed::SLOW, Steps::SMALL);
  pArmServo->moveToPercent(0, Speed::FAST, Steps::SMALL);
  pArmServo->moveToPercent(100, Speed::FAST, Steps::MEDIUM);
  delay(500);
  pArmServo->moveToPercent(0, Speed::FAST, Steps::LARGE);
  pLidServo->moveToPercent(0, Speed::FAST, Steps::MEDIUM);
}

void amy() {
  pLidServo->moveToPercent(100, Speed::NORMAL, Steps::MEDIUM);
  pArmServo->moveToPercent(30, Speed::NORMAL, Steps::MEDIUM);
  pHeadServo->moveToPercent(0, Speed::FAST, Steps::SMALL);
  pHeadServo->moveToPercent(100, Speed::FAST, Steps::SMALL);
  pHeadServo->moveToPercent(50, Speed::FAST, Steps::SMALL);
  pArmServo->moveToPercent(100, Speed::FAST, Steps::SMALL);
  pArmServo->moveToPercent(0, Speed::FAST, Steps::SMALL);
  pLidServo->moveToPercent(0, Speed::FAST, Steps::SMALL);
}

void holly() {
  pLidServo->moveToPercent(100, Speed::SLOW, Steps::SMALL);
  pArmServo->moveToPercent(50, Speed::NORMAL, Steps::LARGE);
  pHeadServo->moveToPercent(20, Speed::FAST, Steps::MEDIUM);
  pHeadServo->moveToPercent(85, Speed::FASTEST, Steps::SMALL);
  pArmServo->moveToPercent(100, Speed::FAST, Steps::SMALL);
  pArmServo->moveToPercent(0, Speed::NORMAL, Steps::SMALL);
  pLidServo->moveToPercent(0, Speed::FAST, Steps::SMALL);
}
