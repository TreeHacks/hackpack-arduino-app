
int analogPin = A0;  

int val = 0; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin);
  Serial.println(val);
}
