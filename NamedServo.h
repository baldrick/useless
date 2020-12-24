#include <Arduino.h>
#include <Servo.h>
#include "Steps.h"

class NamedServo : public Servo {
  public:
    NamedServo(String name, unsigned int pin, int retracted, int extended, int homePercent);
    boolean isAtHome();
    void goHome();
    void moveToPercent(int percentOut, unsigned int msWaitBetweenMoves, StepSize stepSize);

  private:
    String name;
    int retracted;
    int extended;
    int homePercent;

    int percentPos(int percentOut);
    void move(int targetPosition);
    void move(int targetPosition, unsigned int msWaitBetweenMoves);
    void move(int targetPosition, unsigned int msWaitBetweenMoves, StepSize stepSize);
    void moveAndDelay(int pos, unsigned int msWaitBetweenMoves);
};
