#ifndef SERVOPAIR_H
#define SERVOPAIR_H

#include <wiringPi.h> //rasperryPi kirjasto sudo apt-get update ja sudo apt-get install wiringpi
#include <iostream>

class ServoPair {
public:
    // Constructor to initialize the servo motors with pin numbers
    ServoPair(int servoPin1, int servoPin2);

    // Method to set the servo positions
    void setServoPositions(int position1, int position2);

    // Method to move servo motors to the given angles
    void moveToPosition(int angle1, int angle2);

private:
    int pin1;   // Pin for servo motor 1
    int pin2;   // Pin for servo motor 2
    int pwmRange; // PWM range for the servo motors (for mapping angles to pulse widths)

    // Method to initialize the servos
    void initializeServos();

    // Helper method to map the servo angle to PWM pulse width (in ms)
    int angleToPulseWidth(int angle);
};

#endif // SERVOPAIR_H
