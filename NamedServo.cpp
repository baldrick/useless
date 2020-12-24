#include <Servo.h>
#include "Debug.h"
#include "NamedServo.h"
#include "Speed.h"

NamedServo::NamedServo(String name, unsigned int pin, int retracted, int extended, int homePercent)
    : name(name)
    , retracted(retracted)
    , extended(extended)
    , homePercent(homePercent) {
    attach(pin);
}

boolean NamedServo::isAtHome() {
  int pos = read();
  int homePos = percentPos(homePercent);
  TRACE(name + " at position " + String(pos) + " (home is " + String(homePos) + ")");
  return pos == homePos;
}

void NamedServo::goHome() {
  if (!isAtHome()) {
    DEBUG(name + " going home ...");
    moveToPercent(homePercent, 0, Steps::LARGE);
    delay(500);
    DEBUG(name + " home safe at " + String(read()));
  }
}

int NamedServo::percentPos(int percentOut) {
  int diff = extended - retracted;
  int moveAmount = diff * percentOut / 100;
  return retracted + moveAmount;
}

void NamedServo::moveToPercent(int percentOut, unsigned int msWaitBetweenMoves, StepSize stepSize) {
  int targetPosition;
  if (percentOut <= 0) {
    targetPosition = retracted;
  } else if (percentOut >= 100) {
    targetPosition = extended;
  } else {
    targetPosition = percentPos(percentOut);
  }
  DEBUG("Moving " + name + " to " + String(percentOut) + "% (position " + String(targetPosition) + ") in " + stepSize.sizeName + " steps, waiting " + String(msWaitBetweenMoves) + "ms");
  move(targetPosition, msWaitBetweenMoves, stepSize);
  delay(500);
}

// Do not make targetPosition unsigned - messes up the check with pos
void NamedServo::move(int targetPosition) {
  move(targetPosition, Speed::NORMAL);
}

void NamedServo::move(int targetPosition, unsigned int msWaitBetweenMoves) {
  move(targetPosition, msWaitBetweenMoves, Steps::SMALL);
}

void NamedServo::move(int targetPosition, unsigned int msWaitBetweenMoves, StepSize stepSize) {
  int pos = read();
  int diff = pos - targetPosition;
  int absdiff = abs(diff);
  if (absdiff < 10) {
    // Already (roughly) where we need to be
    DEBUG("Not moving to " + String(targetPosition) + " as we're already close at " + String(pos));
  } else {
    int moveAmount = stepSize.moveAmount;
    if (targetPosition < pos) {
      moveAmount = -1 * moveAmount;
    }
    DEBUG("Moving " + name + " from " + String(pos) + " to " + String(targetPosition)
        + " in " + stepSize.sizeName + " steps waiting " + String(msWaitBetweenMoves) + "ms between moves...");
    if (moveAmount > 0) {
      for (pos = read();  pos <= targetPosition;  pos += moveAmount) {
        moveAndDelay(pos, msWaitBetweenMoves);
      }
    } else {
      for (pos = read();  pos >= targetPosition;  pos += moveAmount) {
        moveAndDelay(pos, msWaitBetweenMoves);
      }
    }
    // in case the step size meant the loops didn't actually move the servo all the way to the target
    moveAndDelay(targetPosition, 0);
    DEBUG("... move complete");
  }
}

void NamedServo::moveAndDelay(int pos, unsigned int msWaitBetweenMoves) {
  TRACE("Moving " + name + " to " + String(pos) + " then waiting " + String(msWaitBetweenMoves) + "ms");
  write(pos);
  delay(msWaitBetweenMoves);
}
