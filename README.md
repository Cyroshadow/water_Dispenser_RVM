This code was written by Rajah Yuuan C. Nubla, a student of the Naga City Science Highschool in Philippines.
The basic run down of this machine is that it starts with a red led on indicating that it is not ready to dispense to detect if an object is inserted, with the ready to dispense state set to false
then it will run a motor that allows the object to fall into a container. Once the object has fallen out of the container, it then runs the
motor in a reversed direction to close the opening. After all this, a green led lights up indicating that the button can be pressed and sets the
ready to dispense state to true. Pressing the button whilst it is not in the ready to dispense state simply does nothing. This works by cutting the power supply to the
button and instead of the button allowing power to pass through to the machine, it instead sends a "high" signal to one of the digital pins that
the arduino receives, when the arduino receives this signal it powers a relay that runs a water pump. It keeps this relay powered for a set amt of time
and once the time runs out it stops dispensing water and sets the ready to dispense state to false.
