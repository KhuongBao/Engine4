// Declaring variables

// Sonar pins
int echoPin = 8; //Echo to pin 8
int trigPin = 7; //Trig to pin 7
// L298 pins
int in1 = 4; // IN1 to pin 4
int in2 = 5; // IN2 to pin 5
int in3 = 9; // IN3 to pin 9
int in4 = 10; // IN4 to pin 10


// Lights
int breaklight = 6; //LED breaklights to 6
int button_in = 2; // Button input to 2
int siren_L = 11; // Left siren lights to 11
int siren_R = 3; // Right siren lights to 3

// Other variables
long duration; // Blinking lights duration variable
int distance; // Distance variable for ultrasonic sensor 
int lightvolts = 168; // Voltage for lights ~3.3V

void setup() {

  // Sonar digital pins
  pinMode(trigPin, OUTPUT); // Set trig pin to output
  pinMode(echoPin, INPUT); // Set echo pin to input

  // L298 pins output
  pinMode(in1, OUTPUT); // Set IN1 pin to output
  pinMode(in2, OUTPUT);  // Set IN2 pin to output
  pinMode(in3, OUTPUT); // Set IN3 pin to output
  pinMode(in4, OUTPUT); // Set IN4 pin to output

  // Lights
  pinMode(breaklight, OUTPUT); // Set breaklight pin to output
  pinMode(siren_L, OUTPUT); // Set left siren pin to output
  pinMode(siren_R, OUTPUT); // Set right siren pin to output

  // Button
  pinMode(button_in, INPUT_PULLUP); // Set button input pin to INPUT with built-in resistor 

  // Starting light pins on low
  analogWrite(breaklight, LOW); // Start breaklight pin on LOW (off)
  analogWrite(siren_L, LOW); // Start left siren lights pin on LOW (off)
  analogWrite(siren_R, LOW); // Start right siren lights pin on LOW (off)
  
}

// Blinking siren lights function
void sirenlight() {
  int i=0; // Set interger iteration = 0
  while (i<=10){ // Loop the function for 10 iterations

      analogWrite(siren_L, LOW); // Turn left siren lights off
      analogWrite(siren_R, lightvolts); // Turn right siren lights on (~3.3V)
      delay(200); // Wait 0.2s
      analogWrite(siren_L, lightvolts); // Turn left siren lights on (~3.3V)
      analogWrite(siren_R, LOW); // Turn right siren lights off
      delay(200); // Wait 0.2s
      i++; // Increase interger iteration by 1
    }

    // After completing loop
    analogWrite(siren_L, LOW); // Turn left siren lights off
    analogWrite(siren_R, LOW); // Turn right siren lights off
}


void loop() {
  // Siren light function
  if (digitalRead(button_in) == LOW){ // If button is pressed
    sirenlight(); // Call the siren light blinking function
  }
  
  // Receiving information from ultrasonic sensors, calculating the distance 
  digitalWrite (trigPin, LOW);//starts trig pin low
  delayMicroseconds (2); // wait for response

  digitalWrite (trigPin, HIGH); //makes trig pin high
  delayMicroseconds (10) ; //continues high trig pin state for 10 microseconds
  digitalWrite (trigPin, LOW); //after 10 microseconds trig pin is brought low

  duration = pulseIn (echoPin, HIGH); //reads echo as it receives the pulse 
  distance = duration * 0.034 / 2; // Converts the time of flight to distance to object
  

// When distance is less than or equal to 15cm, move backwards
  if (distance <= 15) {
    analogWrite(breaklight, LOW); // Set break lights to LOW (off)
    digitalWrite(in1, LOW); // Turn left motor anticlock wise (Backwards)
    digitalWrite(in2, HIGH); // Turn left motor anticlock wise (Backwards)
    digitalWrite(in3, LOW); // Turn right motor anticlock wise (Backwards)
    digitalWrite(in4, HIGH); // Turn right motor anticlock wise (Backwards)

// When distance is less than or equal to 30cm, stop moving, turn on breaklights only and siren lights
  } else if (distance <= 30) {

    digitalWrite(in1, LOW); // Stop left motor
    digitalWrite(in2, LOW); // Stop left motor
    digitalWrite(in3, LOW); // Stop right motor
    digitalWrite(in4, LOW); // Stop right motor
    analogWrite(breaklight, lightvolts); // Turn break lights on (~3.3V)

// When distance is less than or equal to 45cm, move forwards
  } else if (distance <= 45) {
    analogWrite(breaklight, LOW); // Set break lights to LOW (off)
    digitalWrite(in1, HIGH); // Turn left motor clock wise (Forwards)
    digitalWrite(in2, LOW); // Turn left motor clock wise (Forwards)
    digitalWrite(in3, HIGH); // Turn right motor clock wise (Forwards)
    digitalWrite(in4, LOW); // Turn right motor clock wise (Forwards)


// When distance is larger than 45cm, stop moving (out of range), turn on breaklighs only
  } else {

    digitalWrite(in1, LOW); // Stop left motor
    digitalWrite(in2, LOW); // Stop left motor
    digitalWrite(in3, LOW); // Stop right motor
    digitalWrite(in4, LOW); // Stop right motor
    analogWrite(breaklight, lightvolts); // Turn break lights on (~3.3V)

  }
  delay(50); // Delay 0.05s
}
