// YOOOO WINNERS
#include <arduino.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"

// OLED display library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define OLED_SDA 21
#define OLED_SCL 22

// Create an instance of the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Button and Buzzer pins
#define BUTTON_PIN 3
#define BUZZER_PIN 1

// TCS color sensor instance
TaskHandle_t Task1;
float red, green, blue;

#define commonAnode true
byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// IR sensor pins
#define ir1 34
#define ir2 35
#define ir3 32
#define ir4 33
#define ir5 25
#define ir6 26
#define ir7 27
#define ir8 14
#define irN1 12
#define irN2 2
#define irN3 0

// IR sensor threshold values
#define thr1 3728
#define thr2 3684
#define thr3 3700
#define thr4 3655
#define thr5 3702
#define thr6 3821
#define thr7 3781
#define thr8 3954
#define thrN1 2480
#define thrN2 1762
#define thrN3 3557

// Maximum size for the data array
#define MAX_SIZE 30

// RGB LED pin assignments
#define PIN_RED 15
#define PIN_GREEN 23
#define PIN_BLUE 13

// Variables for storing IR sensor readings
int st1, st2, st3, st4, st5, st6, st7, st8, stN1, stN2, stN3;  // from left to right

// Data array for storing decisions
char data[MAX_SIZE];
int size = 0;

// Variables for PID control
int desired = 0;
int I = 0;
int prev_error = 0;
int actual, error, D, P;
float kp = 2.6;
int kd = 0;
float ki = 0.06;

// Motor control pins
int enR = 4, inRa = 16, inRb = 17;
int enL = 5, inLa = 19, inLb = 18;

int speedR, speedL, speed;
bool solve = 0;
bool stope = 0;

unsigned long previousMillis = 0;   // Stores the previous time
const unsigned long interval = 100;  // 100ms delay

// Function declarations
void forward();
void makeD();
void left();
void right();
void back();
bool isINTER();
void stopp();
void readIR();
void addElement(char element);
void removeElement(int index);
void optimizeArray();
int searchElement();
void printArray();
bool isENTER();

void setup() {
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2.5);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WALL-EYE");
  display.display();

  // Set pin modes for motor control
  pinMode(enR, OUTPUT);
  pinMode(enL, OUTPUT);
  pinMode(inRa, OUTPUT);
  pinMode(inRb, OUTPUT);
  pinMode(inLa, OUTPUT);
  pinMode(inLb, OUTPUT);

  // Set pin modes for IR sensors
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(ir6, INPUT);
  pinMode(ir7, INPUT);
  pinMode(ir8, INPUT);
  pinMode(irN1, INPUT);
  pinMode(irN2, INPUT);
  pinMode(irN3, INPUT);

  // Set pin modes for RGB LED
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  // Initialize gamma table for OLED display
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    //Serial.println(gammatable[i]);
  }

  // Create a new task for reading IR sensors
  xTaskCreatePinnedToCore(Task1code, "Task1", 6000, NULL, 1, &Task1, 0);


  speed = 100;
  speedR = speed;
  speedL = speed + 10;
}

void loop() {
  readIR();
  makeD();
}



void readIR() {
  st1 = analogRead(ir1);
  st2 = analogRead(ir2);
  st3 = analogRead(ir3);
  st4 = analogRead(ir4);
  st5 = analogRead(ir5);
  st6 = analogRead(ir6);
  st7 = analogRead(ir7);
  st8 = analogRead(ir8);
  stN1 = analogRead(irN1);
  stN2 = analogRead(irN2);
  stN3 = analogRead(irN3);

  // Thresholding
  st1 = (st1 > thr1) ? 1 : 0;
  st2 = (st2 > thr2) ? 1 : 0;
  st3 = (st3 > thr3) ? 1 : 0;
  st4 = (st4 > thr4) ? 1 : 0;
  st5 = (st5 > thr5) ? 1 : 0;
  st6 = (st6 > thr6) ? 1 : 0;
  st7 = (st7 > thr7) ? 1 : 0;
  st8 = (st8 > thr8) ? 1 : 0;
  stN1 = (stN1 > thrN1) ? 1 : 0;
  stN2 = (stN2 > thrN2) ? 1 : 0;
  stN3 = (stN3 > thrN3) ? 1 : 0;
}
void makeD() {  //check decision then turn (LFRB)

  if (st1 == 1 && st2 == 1 && st3 == 1 && st4 == 1 && st5 == 1 && st6 == 1 && st7 == 1 && st8 == 1 && stN1 == 1 && stN2 == 1 && stN3 == 1) {
    delay(80);//Checking twice
    if (st1 == 1 && st2 == 1 && st3 == 1 && st4 == 1 && st5 == 1 && st6 == 1 && st7 == 1 && st8 == 1 && stN1 == 1 && stN2 == 1 && stN3 == 1) {
      Serial.println("stop");
      stopp();
    }
  } else if (st1 == 0 && st2 == 0 && st3 == 0 && st4 == 0 && st5 == 0 && st6 == 0 && st7 == 0 && st8 == 0 && stN1 == 0 && stN2 == 0 && stN3 == 0) {
    delay(10);//checking twice
    if (st1 == 0 && st2 == 0 && st3 == 0 && st4 == 0 && st5 == 0 && st6 == 0 && st7 == 0 && st8 == 0 && stN1 == 0 && stN2 == 0 && stN3 == 0) {
      //back
      Serial.println("back");
      analogWrite(enR, 0);
      analogWrite(enL, 0);
      delay(50);
      back();
    }
  } else if ((st1 == 1 && st2 == 1 && st3 == 1)) {
    //left
    Serial.println("left");
    left();
  } else if (stN1 == 0 && stN2 == 0 && stN3 == 0 && st1 == 0 && st2 == 0 && st3 == 0 && st6 == 1 && st7 == 1 && st8 == 1) {
    //right
    Serial.println("right");
    right();
  } else {
    //forward
    forward();
  }
}

void forward() {  // go forward
  oled("F");
  Serial.println("forward");
  if (isENTER()) {//WALL-EYE is at an intersection and decides to proceed forward.
    oled("FF");
    addElement('F');//We store the decision.
  }
  //PID in order to run in center of the line
  actual = -(20 * st1) - (14 * st2) - (9 * st3) - (5 * st4) + (5 * st5) + (9 * st6) + (14 * st7) + (20 * st8);
  error = desired - actual;
  P = error * kp;
  I += ki * error;

  //I chose to use only a PI controller because I didn't observe any noticeable impact of the derivative component on WALL-EYE's performance.
  float output = P + I;
  if (st6 == 1 && st7 == 1 && st8 == 1) output = 0;
  if (st1 == 1 && st2 == 1 && st3 == 1) output = 0;

  int mR = constrain(speed + output, 0, 255);
  int mL = constrain(speed - output, 0, 255);

  analogWrite(enR, mR);
  analogWrite(enL, mL);
  digitalWrite(inLa, LOW);
  digitalWrite(inLb, HIGH);
  digitalWrite(inRa, LOW);
  digitalWrite(inRb, HIGH);
}

void left() {
  oled("L");  // Display "L" on the OLED screen
  addElement('L');  // Add 'L' to the data array
  // Set motor control pins to make a left turn
  digitalWrite(inLa, HIGH);
  digitalWrite(inLb, LOW);
  digitalWrite(inRa, LOW);
  digitalWrite(inRb, HIGH);
  analogWrite(enR, speedR * 1.4);
  analogWrite(enL, speedL * 1.4);

  // Wait until the north IR sensors detect white surface
  while ((stN1 || stN2 || stN3)) {
    stN1 = analogRead(irN1);
    stN2 = analogRead(irN2);
    stN3 = analogRead(irN3);
    stN1 = (stN1 > thrN1) ? 1 : 0;
    stN2 = (stN2 > thrN2) ? 1 : 0;
    stN3 = (stN3 > thrN3) ? 1 : 0;
    Serial.println("left to white");
  }

  // Wait until the north IR sensors detect the line
  while (!(stN1 || stN2 || stN3)) {
    stN1 = analogRead(irN1);
    stN2 = analogRead(irN2);
    stN3 = analogRead(irN3);
    stN1 = (stN1 > thrN1) ? 1 : 0;
    stN2 = (stN2 > thrN2) ? 1 : 0;
    stN3 = (stN3 > thrN3) ? 1 : 0;
    Serial.println("left to black");
  }

  // move forward for a specific duration
  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= interval) {
    currentMillis = millis();
    forward();
    readIR();
    Serial.println("centring() after left");
  }
}

void right() {
  oled("R");
  addElement('R');
  digitalWrite(inLa, LOW);
  digitalWrite(inLb, HIGH);
  digitalWrite(inRa, HIGH);
  digitalWrite(inRb, LOW);
  analogWrite(enR, speedR * 1.4);
  analogWrite(enL, speedL * 1.4);

  // Wait until the north IR sensors detect the line
  while (!(stN1 || stN2 || stN3 )) {
    stN1 = analogRead(irN1);
    stN2 = analogRead(irN2);
    stN3 = analogRead(irN3);
    stN1 = (stN1 > thrN1) ? 1 : 0;
    stN2 = (stN2 > thrN2) ? 1 : 0;
    stN3 = (stN3 > thrN3) ? 1 : 0;
    Serial.println("right to black");
  }
  // move forward for a specific duration
  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= interval) {
    currentMillis = millis();
    forward();
    readIR();
  }
}

void back() {
  oled("B");
  addElement('B');

  digitalWrite(inLa, HIGH);
  digitalWrite(inLb, LOW);
  digitalWrite(inRa, HIGH);
  digitalWrite(inRb, LOW);
  analogWrite(enR, speedR * 1.8);
  analogWrite(enL, speedL * 1.4);
    // run backward until any of the middle IR sensors detect black surface
  do {
    readIR();
    Serial.println("back to arr");
  } while (!(st3 || st4 || st5 || st6));
  
  analogWrite(enR, speedR * 1.4);
  analogWrite(enL, speedL * 1.4);
  digitalWrite(inLa, LOW);
  digitalWrite(inLb, HIGH);
  digitalWrite(inRa, HIGH);
  digitalWrite(inRb, LOW);
  do {
    stN1 = analogRead(irN1);
    stN2 = analogRead(irN2);
    stN3 = analogRead(irN3);
    stN1 = (stN1 > thrN1) ? 1 : 0;
    stN2 = (stN2 > thrN2) ? 1 : 0;
    stN3 = (stN3 > thrN3) ? 1 : 0;
    Serial.println("rotate right to black");
  } while (!(stN1 || stN2 || stN3));
  // this two function in order to make WALL-EYE run forward for small period in order to return to center of the line
  //1
  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  while (currentMillis - previousMillis <= interval) {
    currentMillis = millis();
    forward();
    readIR();
  }
  //2
  /* while (!((stN1 || stN2 || stN3) && (st4 || st5 || st6 || st5)) ) {
     forward();
     readIR();
    }*/
}

void stopp() {
  oled("S");
  analogWrite(enR, 0);
  analogWrite(enL, 0);
  optimizeArray();
  delay(10000);//Delay for 10 seconds (You can replace this with a push-button to start traversing the maze with the shortest path)
}

// This function returns 1 if WALL-EYE is at an intersection
bool isENTER() {
  // Check if the left sensors (st1, st2, and st3) or the right sensors (st8, st7, and st6) detect a line
  return ((st1 && st2 && st3) || (st8 && st7 && st6));
}

void oled(const String& decision) {
  // Clear the OLED display
  display.clearDisplay();
  // Set the text size and color
  display.setTextSize(6);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  // Print the decision on the OLED display
  display.println(decision);
  // Update the OLED display
  display.display();
}


void addElement(char element) {
  if (size < MAX_SIZE) {
    data[size] = element;
    size++;
    Serial.println("Element added successfully.");
  } else {
    Serial.println("Array is full. Cannot add more elements.");
  }
}

void removeElement(int index) {
  if (index >= 0 && index < size) {
    for (int i = index; i < size - 1; i++) {
      data[i] = data[i + 1];
    }
    size--;
    Serial.println("Element removed successfully.");
  } else {
    Serial.println("Invalid index. Cannot remove element.");
  }
}
int searchElement(char element) {
  for (int i = 0; i < size; i++) {
    if (data[i] == element) {
      Serial.print("Element found at index: ");
      Serial.println(i);
      return i;
    }
  }
  Serial.println("Element not found.");
  return -1;
}
void optimizeArray() {
  int indexB = searchElement('B');
  while (indexB != -1) {
    if (indexB > 0 && indexB < size - 1) {
      char prev = data[indexB - 1];
      char current = data[indexB];
      char next = data[indexB + 1];

      if (prev == 'L' && current == 'B' && next == 'R') {
        removeElement(indexB + 1);
        removeElement(indexB);
        data[indexB - 1] = 'B';
      } else if (prev == 'L' && current == 'B' && next == 'F') {
        removeElement(indexB + 1);
        removeElement(indexB);
        data[indexB - 1] = 'R';
      } else if (prev == 'R' && current == 'B' && next == 'L') {
        removeElement(indexB + 1);
        removeElement(indexB);
        data[indexB - 1] = 'B';
      } else if (prev == 'F' && current == 'B' && next == 'L') {
        removeElement(indexB + 1);
        removeElement(indexB);
        data[indexB - 1] = 'R';
      } else if (prev == 'F' && current == 'B' && next == 'F') {
        removeElement(indexB + 1);
        removeElement(indexB);
        data[indexB - 1] = 'B';
      } else if (prev == 'L' && current == 'B' && next == 'L') {
        removeElement(indexB + 1);
        removeElement(indexB);
        data[indexB - 1] = 'F';
      }
    }
    indexB = searchElement('B');
  }
}
void Task1code(void* parameter) {

  for (;;) {
    float red, green, blue;

    tcs.setInterrupt(false);  // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRGB(&red, &green, &blue);

    tcs.setInterrupt(true);  // turn off LED

    if (red > 100 && green < 70 && blue < 50) {

      analogWrite(PIN_RED, 255);
      analogWrite(PIN_GREEN, 0);
      analogWrite(PIN_BLUE, 0);
      //red ;
    }

    else if (red > 130 && green > 70 && blue < 73) {
      analogWrite(PIN_RED, 255);
      analogWrite(PIN_GREEN, 0);
      analogWrite(PIN_BLUE, 255);
      Serial.print("magenta");
    } else if (red < 100 && green > 100 && blue < 100) {
      analogWrite(PIN_RED, 0);
      analogWrite(PIN_GREEN, 255);
      analogWrite(PIN_BLUE, 0);
      //blue

    }

    else if ((92 > red) && (green < 100) && (73 > blue)) {
      analogWrite(PIN_RED, 0);
      analogWrite(PIN_GREEN, 100);
      analogWrite(PIN_BLUE, 100);
      //cyan
    }


    else if ((130 < red) && (green < 100) && (50 > blue)) {
      analogWrite(PIN_RED, 255);
      analogWrite(PIN_GREEN, 191);
      analogWrite(PIN_BLUE, 0);
      //yellow
    }

    else if (red < 100 && blue > green) {
      analogWrite(PIN_RED, 0);
      analogWrite(PIN_GREEN, 0);
      analogWrite(PIN_BLUE, 255);
      //green
    }

    else if (red > 100 && green > 70 && blue > 40) {
      analogWrite(PIN_RED, 255);
      analogWrite(PIN_GREEN, 255);
      analogWrite(PIN_BLUE, 255);
      //white
    }
  }
}
