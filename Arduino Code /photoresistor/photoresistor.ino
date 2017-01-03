/* 
 *  Photoresistor sample code. Prints out value of photoresistor 
 *  reading on analog pin A5. 
 */

int pin = A5;  
int val = 0; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(pin);
  Serial.println(val);
}
