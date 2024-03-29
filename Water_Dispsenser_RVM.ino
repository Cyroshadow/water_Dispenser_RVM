#include <Servo.h>


//Variables used to declare pinOuts and pinIns; IMportant for code adaptability and stops me from going mad
const byte led_Red = 13; //I wonder what this could possibly be for
const byte led_Green= 12; //I wonder what this could possibly be for
const byte capacitive_Sensor = A0; //Take input from capacitive sensor; Detects if object is there or not
const byte servo_Pin = 11; //Motor for gate when object is inserted
const byte dispense_Button_Output = 10; //Activates button that will turn on the pump when pressed
const byte pump_Pin = 9; //Pump
const byte reverse_Motor_Direction = 8; //The pin of the relay that is powered when you want to reverse the direction of the motor
const byte dispense_Button_Input = 7; //Checks if button is pressed

const int dispense_Amt = 5000; //Change this to however much you want it to wait before it stops dispensing water
const int close_Angle = 0; //Change this to change how much the servo motor closes
const int open_Angle = 125; //Change this to change how much the servo motor opens 
//Variables used for logic and automation
bool object_Inserted = false; //Is an object inserted?
bool ready_Dispense = false; //Is it ready to dispense?
bool dispense_Query = false; //Should it be dispensing now?

Servo servo; //DO NOT DELETE THIS LINE OF CODE EVERYTHING BREAKS WITHOUT IT FSR

void setup() {

  pinMode(led_Red, OUTPUT);
  pinMode(led_Green, OUTPUT);  
  pinMode(reverse_Motor_Direction, OUTPUT); 
  pinMode(pump_Pin, OUTPUT);
  pinMode(dispense_Button_Output, OUTPUT);
  pinMode(dispense_Button_Input, OUTPUT);
  pinMode(capacitive_Sensor, INPUT);
  servo.attach(servo_Pin);
  servo.write(close_Angle);
}

void loop() {
  
  object_Inserted = digitalRead(capacitive_Sensor); //Checks if object is inserted

  if (object_Inserted) {
    servo.write(open_Angle); //Open hatch
    digitalWrite(led_Red, LOW); //I wonder what this could possibly be for
    //Uncomment the line of code below if you want it to be a set delay and remove the while loop
    //delay(10000);
    while (object_Inserted) {
      delay(100); //Repeatedly delay until object is no longer detected
    }
    ready_Dispense = true; //Indicate that it has accepted a viable plastic bottle
  } else {
    servo.write(close_Angle); //Close hatch
    digitalWrite(led_Green, LOW); //I wonder what this could possibly be for
    digitalWrite(led_Red, HIGH); //I wonder what this could possibly be for
  }

  if (ready_Dispense) {
    digitalWrite(led_Green, HIGH); //I wonder what this could possibly be for
    digitalWrite(dispense_Button_Output, HIGH); //Activate button that will power pump when pressed
    dispense_Query = digitalRead(dispense_Button_Input); //Check if button is pressed
    if (dispense_Query) { 
      digitalWrite(pump_Pin, HIGH); //Turn on pump
      delay(dispense_Amt); ///Wait until x amt of time has passed
      digitalWrite(pump_Pin, LOW); //Turn off pump
      ready_Dispense = false; //Tell machine that it has used up it's one time dispense ticket
    }
  }

}
