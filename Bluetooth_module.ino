#include <Servo.h>

Servo Hservo,Rservo,Lservo;  // create servo object to control a servo

// defines pins numbers
const int trigPin = 6;
const int echoPin = 7;
int piezoPin = 11;
int led = 13;
const int temperaturePin = 0;

// defines variables
long duration;
int distance,val;

 
void setup() {

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(led, OUTPUT);

Serial.begin(9600); // Starts the serial communication

  Rservo.attach(8); // right arm servo
  Hservo.attach(9); // head servo
  Lservo.attach(10);  // left arm servo
}
void loop() {

   float voltage, degreesC;
   voltage = getVoltage(temperaturePin);
   degreesC = (voltage - 0.5) * 100.0;
  
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    // Sets the trigPin on HIGH state for 3 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(3);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    
    delay(3000);

    if (distance < 10) //
    {
      // Prints the distance on the Serial Monitor
      Serial.print("Distance: ");
      Serial.println(distance); // print the currnet distance on serial port
      tone(piezoPin, 1000, 500);  // this will alarm the sound every time distance 
      digitalWrite(led, HIGH); 
      delay(3000); // wait 3 1second   
    }
    else
    {
      noTone(piezoPin);
      digitalWrite(led, LOW);
      delay(50); 
    }


   if(Serial.available())
   {
     String value = Serial.readStringUntil('\n'); // read the string from serial window
     Serial.println(value);
     if(value == "left")
     {
        Hservo.write(80);   // moving the head little left                
        delay(15); 
        Lservo.write(60);   // left arm up               
        delay(15);
        Rservo.write(20);   // right arm down               
        delay(15);
     }
     else if(value == "right")
     {
        Hservo.write(40);   // moving the head little right                
        delay(15);
        Lservo.write(20);   // left arm down               
        delay(15);
        Rservo.write(60);  // right arm up                
        delay(15);
     }
     else if(value == "temp")
     {
       Serial.print("voltage: "); // print temperature
       Serial.print(voltage);
       Serial.print("  deg C: "); 
     }
   }
}

float getVoltage(int pin)
{
  // point value, which is the true voltage on that pin (0 to 5V).
  return (analogRead(pin) * 0.004882814);
}
