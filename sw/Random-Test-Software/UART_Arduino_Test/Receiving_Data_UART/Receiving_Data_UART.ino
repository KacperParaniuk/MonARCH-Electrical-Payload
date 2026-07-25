int incomingByte = 0; // for incoming serial data


#include <SoftwareSerial.h>


SoftwareSerial mySerial(2, 3);



#define LED_1 8
#define LED_2 9


void setup() {
  Serial.begin(115200);      // For Serial Monitor
  mySerial.begin(115200);    // For STM32 (use lower baud like 9600 if issues)


  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

}

void loop() {
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.println(c);  // Echo to Serial Monitor for debugging
    digitalWrite(LED_1, 1);


    if(c==1){
// led ON 
      digitalWrite(LED_2, 1);

    }
    else if(c==0){
// LED OFF
      digitalWrite(LED_2, 0);


    }
    else{

      digitalWrite(LED_1, 1);
      delay(100);
      digitalWrite(LED_1, 0);
      delay(100);
      digitalWrite(LED_1, 1);
      delay(100);
      digitalWrite(LED_1, 0);
      delay(100);

    }

    delay(500);




  }
  else{
    delay(500);
    Serial.println("Nothing");
    digitalWrite(LED_1, 0);

  }

  
}



