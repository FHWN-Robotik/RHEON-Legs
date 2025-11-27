#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  120 // minimum pulse length count
#define SERVOMAX  590 // maximum pulse length count

int angle1, angle2;

void setup() {
    Serial.begin(9600);
    pwm.begin();
    pwm.setPWMFreq(60);
}

void loop() {
    if (Serial.available() >= 4) { // Wait until four bytes are available (2 bytes each for two angles)
        // Read the first two bytes and combine into angle1
        byte lowByte1 = Serial.read();
        byte highByte1 = Serial.read();
        angle1 = (highByte1 << 8) | lowByte1;

        // Read the next two bytes and combine into angle2
        byte lowByte2 = Serial.read();
        byte highByte2 = Serial.read();
        angle2 = (highByte2 << 8) | lowByte2;

        // Set PWM for Motor1 and Motor2
        pwm.setPWM(0, 0, angleToPulse(angle1));
        pwm.setPWM(1, 0, angleToPulse(angle2));
    }
}

int angleToPulse(int ang) {
    int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
    Serial.print("Angle: "); Serial.print(ang);
    Serial.print(" Pulse: "); Serial.println(pulse);
    return pulse;
}
