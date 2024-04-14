#include <Servo.h>

//Variables used to declare pinOuts and pinIns; Important for code adaptability and stops me from going mad
const byte led_Red = 13; //I wonder what this could possibly be for
const byte led_Green = 12; //I wonder what this could possibly be for
const byte capacitive_Sensor = A0; //Take input from capacitive sensor; Detects if object is there or not
const byte servo_Pin = 11; //Motor for gate when object is inserted
const byte dispense_Button_Output = 10; //Activates button that will turn on the pump when pressed
const byte pump_Pin = 9; //Pump
const byte IR_Sensor = 8; //Out pin of IR Sensor
const byte dispense_Button_Input = 7; //Checks if button is pressed

//Macros used in functions
const int prox_Threshold = 100; //Change this to calibrate how sensitive you need the sensor to be
const int dispense_Amt = 5000; //Change this to however much you want it to wait before it stops dispensing water
const int close_Angle = 0; //Change this to change how much the servo motor closes
const int open_Angle = 125; //Change this to change how much the servo motor opens 

//Variables used for logic and automation
int proximity = 0; //How close is the object and how much does it disrupt the electric field?
int IR_Sens = false; //Is the IR sensor detecting an object?
bool ready_Dispense = false; //Is it ready to dispense?
bool dispense_Query = false; //Should it be dispensing now?
bool object_Inserted = false; //Is there an object?

Servo servo; //DO NOT DELETE THIS LINE OF CODE EVERYTHING BREAKS WITHOUT IT FSR

void setup() {

  pinMode(led_Red, OUTPUT);
  pinMode(led_Green, OUTPUT);  
  pinMode(pump_Pin, OUTPUT);
  pinMode(dispense_Button_Output, OUTPUT);
  pinMode(dispense_Button_Input, INPUT);
  pinMode(capacitive_Sensor, INPUT);
  pinMode(IR_Sensor, INPUT);
  
  digitalWrite(led_Green, LOW);
  digitalWrite(led_Red, HIGH);
  digitalWrite(pump_Pin, LOW);

  servo.attach(servo_Pin);
  servo.write(close_Angle);

  Serial.begin(9600);
}

void loop() {
  
  proximity = analogRead(capacitive_Sensor); //Checks if object is inserted
  IR_Sens = (digitalRead(IR_Sensor) != 0); //Check if object is stopping the IR waves from returning to the sensor
  Serial.println(proximity);
  Serial.println(IR_Sens);
  if (proximity <= prox_Threshold && IR_Sens == false) //Replace && with || if its supposed to be the capacitive sensor OR ir detects an object, not AND
  {
    object_Inserted = true; //If object detected then tell arduino there is object
  } else {
    object_Inserted = false; //If object not detected then tell arduino there is no object
  }
  if (object_Inserted) { 
    servo.write(open_Angle); //Open hatch
    delay(3000); //Delay for object to fall in
    ready_Dispense = true; //Indicate that it has accepted a viable plastic bottle
    
  } else {
    servo.write(close_Angle); //Close hatch
  }
  
  if (ready_Dispense) {
    digitalWrite(led_Green, HIGH); //I wonder what this could possibly be for
    digitalWrite(led_Red, LOW); //I wonder what this could possibly be for
    digitalWrite(dispense_Button_Output, HIGH); //Activate button that will power pump when pressed
    dispense_Query = !digitalRead(dispense_Button_Input); //Check if button is pressed; Reverse because arduino reads button pressed as 0 instead of 1 for some reason
    if (dispense_Query) { 
      digitalWrite(pump_Pin, HIGH); //Turn on pump
      delay(dispense_Amt); ///Wait until x amt of time has passed
      digitalWrite(pump_Pin, LOW); //Turn off pump
      ready_Dispense = false; //Tell machine that it has used up it's one time dispense ticket
      digitalWrite(led_Green, LOW); //I wonder what this could possibly be for
      digitalWrite(led_Red, HIGH); //I wonder what this could possibly be for
    }
  }

}
