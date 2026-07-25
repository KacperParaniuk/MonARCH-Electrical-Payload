

uint8_t LED_PIN = 17;


void setup() {

// Set Pins. 
  pinMode(LED_PIN, OUTPUT);
  delay(1000);

}

void loop() {

// Set Blinking Code 
  digitalWrite(LED_PIN, true);
  delay(1000);
  digitalWrite(LED_PIN, false); 
  delay(1000);

}
