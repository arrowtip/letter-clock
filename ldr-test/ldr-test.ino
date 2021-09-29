void setup() {
  pinMode(13, OUTPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  digitalWrite(13, HIGH);
}

void loop() {
  Serial.println(analogRead(A1));
  delay(10);

}
