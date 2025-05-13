#include <Arduino.h>

// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  int wallWidth = 8;
  int wallHeight = 12;
  int wallMatrix[wallWidth][wallHeight];

  for(int i = 0; i < wallWidth; i++) { // initialize all positions as 0 for NULL
    for(int j = 0; j < wallHeight; j++) {
      wallMatrix[i][j] = 0;
    }
  }

  for(int i = 0; i < wallWidth; i++) { // Print Wall Matrix
    Serial.print("[ ");
    for(int j = 0; j < wallHeight; j++) {
      Serial.print(wallMatrix[i][j]);
      Serial.print(" ");
    }
    Serial.println("]");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

