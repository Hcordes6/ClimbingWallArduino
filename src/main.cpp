#include <Arduino.h>

// put function declarations here:
const int dataPin = 2;   // SER
const int clockPin = 3;  // SRCLK
const int latchPin = 4;  // RCLK

const int numRows = 12;
const int numCols = 8;

// 2D array representing LED states (1 = ON, 0 = OFF)
byte ledState[12][8] = {
  {1,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,0},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,1,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,0}
};


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

  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  for (int row = 0; row < numRows; row++) {
    // Create byte arrays for shift registers
    byte rowData[2] = {0};   // For rows (only one bit HIGH at a time)
    byte colData[1] = {0};   // For columns (1 = OFF, 0 = ON for active LEDs)

    // Set the active row
    if (row < 6) {
      rowData[1] = (1 << row);
    } else {
      rowData[0] = (1 << (row - 6));
    }

    // Set columns based on ledState[row][col]
    for (int col = 0; col < numCols; col++) {
      if (ledState[row][col] == 1) {
        if (col < 8) {
          colData[0] &= ~(1 << col);  // LED ON = column LOW
        } 
      } else {
        if (col < 8) {
          colData[0] |= (1 << col);  // LED OFF = column HIGH
        } 
      }
    }

    // Shift out: first columns, then rows
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colData[0]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowData[0]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowData[1]);
    digitalWrite(latchPin, HIGH);

    delayMicroseconds(1000); // Small delay
  }
}

