//MOTOR
//#include <analogWrite.h>
/* Different servos require different pulse widths to vary servo angle, but the range is 
 * an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
 * sweep 180 degrees, so the lowest number in the published range for a particular servo
 * represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
 * of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
 * 1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 1800
 * degrees.
 * 
 * Circuit: (using an ESP32 Thing from Sparkfun)
 * Servo motors have three wires: power, ground, and signal. The power wire is typically red,
 * the ground wire is typically black or brown, and the signal wire is typically yellow,
 * orange or white. Since the ESP32 can supply limited current at only 3.3V, and servos draw
 * considerable power, we will connect servo power to the VBat pin of the ESP32 (located
 * near the USB connector). THIS IS ONLY APPROPRIATE FOR SMALL SERVOS. 
 * 
 * We could also connect servo power to a separate external
 * power source (as long as we connect all of the grounds (ESP32, servo, and external power).
 * In this example, we just connect ESP32 ground to servo ground. The servo signal pins
 * connect to any available GPIO pins on the ESP32 (in this example, we use pin 18.
 * 
 * In this example, we assume a Tower Pro SG90 small servo connected to VBat.
 * The published min and max for this servo are 500 and 2400, respectively.
 * These values actually drive the servos a little past 0 and 180, so
 * if you are particular, adjust the min and max values to match your needs.
 */
 
#include <ESP32Servo.h>  // Include the ESP32 Arduino Servo Library instead of the original Arduino Servo Library
Servo myservo;  // create servo object to control a servo
// Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33 
int servoPin = 18;  // attaches the servo on pin 18 to the servo object
int deflection_angle = 90;    

#define MOTOR_SPEED_MIN -500 // Minimum reading from motor
#define MOTOR_SPEED_MAX 500 // Maximum reading from motor

void motor_setup(){

// Allow allocation of all timers
  ESP32PWM::allocateTimer(0);  // using SG90 servo min/max of 500us and 2400us
  ESP32PWM::allocateTimer(1);  // for MG995 large servo, use 1000us and 2000us,
  ESP32PWM::allocateTimer(2);  // which are the defaults, so this line could be
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 600, 2300);
}

void motor_set(int motor_speed){

//deflection_angle = map(constrain(motor_speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX),0, 180);
motor_speed = constrain(motor_speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX);
//Serial.print("Inside motor_set loop - motor speed");
//Serial.println(motor_speed);
deflection_angle = map(motor_speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(deflection_angle);                            // set the servo position according to the scaled value
  delay(20);                                             // wait for the servo to get there
  Serial.print("Rudder angle ");
  Serial.println(deflection_angle);
}

 