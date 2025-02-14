#include "MotorServopair.h"

ServoPair::ServoPair(int servoPin1, int servoPin2) {
    pin1 = servoPin1;
    pin2 = servoPin2;

    // Initialize wiringPi library
    if (wiringPiSetup() == -1) {
        std::cerr << "WiringPi setup failed!" << std::endl;
        exit(1);
    }

    // Initialize the servos with the given pin numbers
    initializeServos();
}

void ServoPair::initializeServos() {
    pinMode(pin1, PWM_OUTPUT);
    pinMode(pin2, PWM_OUTPUT);
}

int ServoPair::angleToPulseWidth(int angle) {
    // Map the angle (from -90 to 90) to pulse width in milliseconds (1ms to 2ms)
    if (angle < -90) angle = -90;
    if (angle > 90) angle = 90;

    // Convert angle to the pulse width in milliseconds
    float pulseWidth = 1.5 + (angle * 0.005); // Map -90 to 90 degrees to 1ms to 2ms

    return static_cast<int>(pulseWidth * 1000); // Convert ms to microseconds (wiringPi uses microseconds)
}

void ServoPair::moveToPosition(int angle1, int angle2) {
    int pulseWidth1 = angleToPulseWidth(angle1);
    int pulseWidth2 = angleToPulseWidth(angle2);

    pwmWrite(pin1, pulseWidth1);  // Move the first servo to angle1
    pwmWrite(pin2, pulseWidth2);  // Move the second servo to angle2
}

void ServoPair::setServoPositions(int position1, int position2)  {
    // Set the servo motors to specific positions (angles)
    moveToPosition(position1, position2);
}
