/*
 * Arduino Hello World serial app. 
 */

// The setup function is required and runs a single time when the program starts
void setup() {
  Serial.begin(9600);
}

// The loop function loops infinitely after the setup function returns 
void loop() {
	Serial.println("Hello, world!"); 
	delay(1); // Delay one second 
}