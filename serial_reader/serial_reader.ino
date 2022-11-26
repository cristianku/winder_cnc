
//the definiens of 8bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function

// #define YP 6  // must be an analog pin, use "An" notation!
// #define XM A2  // must be an analog pin, use "An" notation!
// #define YM 7   // can be a digital pin
// #define XP A1   // can be a digital pin


void setup() {
  Serial.begin(115200);

  // Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


}


void loop() {

  String grbl_out = Serial.readString();
  if (grbl_out > "") {
    Serial.println("GOT: " + grbl_out);
    grbl_out = "";
  }


}




