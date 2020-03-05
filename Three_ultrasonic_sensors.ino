/***********************************************************************************************************************
   - Original Author           : BEE MB
 * *********************************************************************************************************************/

/***********************************************************************************************************************
   - Enhanced by        : folafunmi-db
 * *********************************************************************************************************************/

//Start :
//define the pins that we will use for the first ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin1 9                           //pin number 9 in arduino MEGA2560
#define echoPin1 8                           // we'll use this pin to read the signal from the first sensor
#define LED_first_ping 22                    // I/O digital or analogue ( we will use pin 22 to command an LED (on/off))
//----------------------------------------------------------------------------------------------------------------------

//define the pins that we will use for the second ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin2 10
#define echoPin2 11
#define LED_second_ping 24
//----------------------------------------------------------------------------------------------------------------------

//define the pins that we will use for the third ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin3 5
#define echoPin3 6
#define LED_third_ping 20
//----------------------------------------------------------------------------------------------------------------------

//used variables
//----------------------------------------------------------------------------------------------------------------------
long duration, distance, UltraSensor1, UltraSensor2, UltraSensor3; //we'll use these variable to store and generate data

char data;
String SerialData = "";
//----------------------------------------------------------------------------------------------------------------------

//Make the setup of your pins
//----------------------------------------------------------------------------------------------------------------------
void setup()
{ // START SETUP FUNCTION
  Serial.begin (9600);     // we will use the serial data transmission to display the distance value on the serial monitor

  // setup pins first sensor
  pinMode(trigPin1, OUTPUT);            // from where we will transmit the ultrasonic wave
  pinMode(echoPin1, INPUT);             //from where we will read the reflected wave
  pinMode(LED_first_ping, OUTPUT);      // from where we will control the LED

  //setup pins second sensor
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(LED_second_ping, OUTPUT);

  //setup pins third sensor
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(LED_third_ping, OUTPUT);

  //inisialize LED status
  digitalWrite(LED_first_ping, LOW);
  digitalWrite(LED_second_ping, LOW);
  digitalWrite(LED_third_ping, LOW);
}// END SETUP FUNCTION

//write the code in the loop function
void loop()
{
  // START THE LOOP FUNCTION
  SonarSensor(trigPin1, echoPin1);              // look bellow to find the difinition of the SonarSensor function
  UltraSensor1 = distance;                      // store the distance in the first variable
  SonarSensor(trigPin2, echoPin2);              // call the SonarSensor function again with the second sensor pins
  UltraSensor2 = distance;                      // store the new distance in the second variable
  SonarSensor(trigPin3, echoPin3);              // call the SonarSensor function again with the third sensor pins
  UltraSensor3 = distance;                      // store the new distance in the third variable

  while (Serial.available())
  {
    delay(10);
    data = Serial.read();
    SerialData += data;
  }

  if (SerialData == "display distance")
  {
    // display the distances on the serial monitor for the first sensor
    //----------------------------------------------------------------------------------------------------------------------
    Serial.print("distance measured by the first sensor: ");
    Serial.print(UltraSensor1);
    Serial.println(" cm");
    //----------------------------------------------------------------------------------------------------------------------

    //display the distance on the serial monitor for the second sensor
    //----------------------------------------------------------------------------------------------------------------------
    Serial.print("distance measured by the second sensor: ");
    Serial.print(UltraSensor2);
    Serial.println(" cm");
    Serial.println("---------------------------------------------------------------------------------------------------------");
    //----------------------------------------------------------------------------------------------------------------------

    //display the distance on the serial monitor for the third sensor
    //----------------------------------------------------------------------------------------------------------------------
    Serial.print("distance measured by the third sensor: ");
    Serial.print(UltraSensor3);
    Serial.println(" cm");
    Serial.println("---------------------------------------------------------------------------------------------------------");
    //----------------------------------------------------------------------------------------------------------------------
  }

  SerialData = "";
  // make condition to control the LEDs
  if (UltraSensor1 <= 10) // if distance is less than 10 Cm turn the LED ON
  {
    digitalWrite(LED_first_ping, HIGH);
  }
  else                // else turn the LED OFF
  {
    digitalWrite(LED_first_ping, LOW);
  }

  // do the same thing for second sensor
  if (UltraSensor2 <= 10)
  {
    digitalWrite(LED_second_ping, HIGH);
  }
  else
  {
    digitalWrite(LED_second_ping, LOW);
  }

  // do the same thing for third sensor
  if (UltraSensor3 <= 10)
  {
    digitalWrite(LED_third_ping, HIGH);
  }
  else
  {
    digitalWrite(LED_third_ping, LOW);
  }
}//END LOOP FUNTION

// SonarSensor function used to generate and read the ultrasonic wave
void SonarSensor(int trigPinSensor, int echoPinSensor) //it takes the trigPIN and the echoPIN
{
  //START SonarSensor FUNCTION
  //generate the ultrasonic wave
  //----------------------------------------------------------------------------------------------------------------------
  digitalWrite(trigPinSensor, LOW);// put trigpin LOW
  delayMicroseconds(2);// wait 2 microseconds
  digitalWrite(trigPinSensor, HIGH);// switch trigpin HIGH
  delayMicroseconds(10); // wait 10 microseconds
  digitalWrite(trigPinSensor, LOW);// turn it LOW again
  //----------------------------------------------------------------------------------------------------------------------

  //read the distance
  //----------------------------------------------------------------------------------------------------------------------
  duration = pulseIn(echoPinSensor, HIGH);
  //pulseIn funtion will return the time on how much the configured pin remain the 
  //level HIGH or LOW; in this case it will return how much time echoPinSensor stay HIGH
  
  distance = (duration / 2) / 29.1; // first we have to divide the duration by two
}// END SonarSensor FUNCTION

/****************************----------------------- END PROGRAM -----------------------*********************************/
