
// Declaring variables

// Sonar pins
int echoPin = 8;
int trigPin = 7;
// L298 pins
int in1 = 4; 
int in2 = 5; 
int in3 = 9; 
int in4 = 10; 

long duration;
int distance;

// Lights
int headlight = 2;
int breaklight = 3;
int siren_blue = 11;
int siren_red = 12;
int night_light = 13;


void setup() {

  // Sonar digital pins
  pinMode(trigPin, OUTPUT) ;
  pinMode(echoPin, INPUT);

  // L298 pins output
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 

  Serial.begin (9600) ; 

  // Lights
  pinMode(headlight, OUTPUT);
  pinMode(breaklight, OUTPUT);
  pinMode(headlight, OUTPUT);
  pinMode(breaklight, OUTPUT);

  // Starting light pins on low
  digitalWrite(headlight, LOW);
  digitalWrite(breaklight, LOW);
  digitalWrite(siren_blue, LOW);
  digitalWrite(siren_red, LOW);
  
}

// Blinking siren lights
void sirenlight() {
  digitalWrite(siren_blue, HIGH);
  digitalWrite(siren_red, LOW);
  delayMicroseconds(100);
  digitalWrite(siren_blue, LOW);
  digitalWrite(siren_red, HIGH);
  delayMicroseconds(100);
}


void loop() {
  
  // Receiving information from ultrasonic sensors, calculating the distance 
  digitalWrite (trigPin, LOW);//starts trig pin low
  delayMicroseconds (2); // wait for response

  digitalWrite (trigPin, HIGH); //makes trig pin high
  delayMicroseconds (10) ; //continues high trig pin state for 10 microseconds
  digitalWrite (trigPin, LOW); //after 10 microseconds trig pin is brought low

  duration = pulseIn (echoPin, HIGH); //reads echo as it receives the pulse 
  distance = duration * 0.034 / 2; // Converts the time of flight to distance to object

  // Displays the distance on the serial Monitor
  Serial.print ("Distance: ");
  Serial.print (distance);
  Serial.println(" cm");
  

// When distance is less than or equal to 15cm, move backwards, turn on both lights and siren lights
  if (distance <= 15) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(headlight, HIGH);
    digitalWrite(breaklight, HIGH);
    sirenlight();

// When distance is less than or equal to 30cm, stop moving, turn on breaklights only and siren lights
  } else if (distance <= 30) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(headlight, LOW);
    digitalWrite(breaklight, HIGH);
    sirenlight();

// When distance is less than or equal to 45cm, move forwards, turn on headlights only and siren lights
  } else if (distance <= 45) {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(headlight, HIGH);
    digitalWrite(breaklight, LOW);
    sirenlight();


// When distance is larger than 45cm, stop moving (out of range), torn on breaklighs only
  } else {

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(headlight, LOW);
    digitalWrite(breaklight, HIGH);

  }
  delay(10);
}
