#include <math.h>
#include <Servo.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PI 3.141592654

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
const unsigned char TeamLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xff, 0x83, 0x00, 0xc0, 0x00, 0x1f, 0x80, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xff, 0x87, 0x01, 0x80, 0x00, 0x3f, 0xc0, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xff, 0x8f, 0x01, 0x80, 0x00, 0x7f, 0xe0, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0x00, 0x03, 0x03, 0x00, 0x00, 0xe0, 0x70, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 
  0x00, 0x07, 0x00, 0x03, 0x03, 0x00, 0x00, 0xe0, 0x73, 0xfd, 0xdf, 0xf0, 0xff, 0xc3, 0xfc, 0x00, 
  0x00, 0x07, 0x00, 0x03, 0x06, 0x00, 0x00, 0xe0, 0x73, 0xfd, 0xdf, 0xfc, 0xff, 0xe3, 0xfc, 0x00, 
  0x00, 0x07, 0x00, 0x03, 0x06, 0x00, 0x00, 0xff, 0xf7, 0x01, 0xdf, 0xfc, 0xff, 0xe7, 0x00, 0x00, 
  0x00, 0x07, 0x80, 0x03, 0x0c, 0x70, 0x00, 0xff, 0xf7, 0x01, 0xc0, 0x0e, 0xe0, 0x77, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0x0f, 0xcc, 0xf8, 0x00, 0xff, 0xf3, 0xe1, 0xcf, 0xfe, 0xe0, 0x73, 0xe0, 0x00, 
  0x00, 0x01, 0xff, 0x80, 0x19, 0xcc, 0x00, 0xe0, 0x73, 0xf9, 0xcf, 0xfe, 0xe0, 0x73, 0xf8, 0x00, 
  0x00, 0x00, 0xff, 0xc0, 0x19, 0x8c, 0x00, 0xe0, 0x71, 0xfd, 0xdf, 0xfe, 0xe0, 0x71, 0xfc, 0x00, 
  0x00, 0x06, 0x01, 0xc0, 0x30, 0x38, 0x00, 0xe0, 0x70, 0x1d, 0xdc, 0x0e, 0xe0, 0x70, 0x1c, 0x00, 
  0x00, 0x07, 0x01, 0xc0, 0x30, 0x70, 0x00, 0xe0, 0x70, 0x1d, 0xdc, 0x0e, 0xe0, 0x70, 0x1c, 0x00, 
  0x00, 0x07, 0xff, 0xc0, 0x60, 0xe0, 0x00, 0xe0, 0x77, 0xf9, 0xcf, 0xfe, 0xe0, 0x77, 0xf8, 0x00, 
  0x00, 0x03, 0xff, 0x80, 0x61, 0xcc, 0x00, 0xe0, 0x77, 0xf9, 0xcf, 0xfe, 0xe0, 0x77, 0xf8, 0x00, 
  0x00, 0x01, 0xff, 0x00, 0xc1, 0xfc, 0x00, 0xe0, 0x77, 0xe1, 0xc3, 0xfe, 0xe0, 0x77, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Joystick & Motor Variables
Servo ESCLeft;
Servo ESCRight;

int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

int motorTopSpeed = 500;
int leftMotorTopSpeed = motorTopSpeed;
int rightMotorTopSpeed = motorTopSpeed;

float leftMotor = 1000;
float rightMotor = 1000;
float lastMotorSpeedLeft = 1000;
float lastMotorSpeedRight = 1000;

float joystickAngle = 0;

// Potentiometer & Motor Variables
Servo ESCMiddle;
int potValue = 0;

// Buttons Left and Right
int lastButtonStateL;
int lastButtonStateR;

void setup() {
  // Display Setup
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();

  // Display bitmap Startup
  display.drawBitmap(0, 0, TeamLogo , 128, 64, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  
  // Potentiometer & Motor Setup
  ESCMiddle.attach(11,1000,2000);
  // Joystick & Motor Setup
  ESCLeft.attach(9,1000,2000);
  ESCRight.attach(10,1000,2000);
  Serial.begin(9600); 
  // Buttons Setup
  pinMode(6, INPUT_PULLUP);  // enable the internal pull-up resistor
  lastButtonStateL = digitalRead(6);

  pinMode(7, INPUT_PULLUP);  // enable the internal pull-up resistor
  lastButtonStateR = digitalRead(7);
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}

void loop() {
  // Clears OLED display
  display.clearDisplay();
  
  // Button Left
  int buttonStateL = digitalRead(6);

  if (lastButtonStateL != buttonStateL) { // state changed
    delay(5); // debounce time

    if (buttonStateL == LOW) {
      if (motorTopSpeed > 100) {
        motorTopSpeed = motorTopSpeed - 100;
        leftMotorTopSpeed = motorTopSpeed;
        rightMotorTopSpeed = motorTopSpeed;
      }
      Serial.println("Left button pressed event");
    }
    lastButtonStateL = buttonStateL;
  }

  // Button Right
  int buttonStateR = digitalRead(7);

  if (lastButtonStateR != buttonStateR) { // state changed
    delay(5); // debounce time

    if (buttonStateR == LOW) {
      if (motorTopSpeed < 1000) {
        motorTopSpeed = motorTopSpeed + 100;
        leftMotorTopSpeed = motorTopSpeed;
        rightMotorTopSpeed = motorTopSpeed;
      }
      Serial.println("Right button pressed event");
    }
    lastButtonStateR = buttonStateR;
  }

  // OLED Display
  // Display current max motor speed
  // 1 pixel right of mid and 2 pixels down
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(19,15);
  display.println("MAX");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(61,15);
  display.println(motorTopSpeed + 1000);
  
  // Potentiometer & Motor Control
  potValue = analogRead(A2);
  potValue = map(potValue, 1000, 0, 1000, 2000);
  if (potValue < 1000) {
    potValue = 1000;
  }
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(51,1);
  display.println("M");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(58,1);
  display.println(potValue);
  
  ESCMiddle.writeMicroseconds(potValue);

  // Joystick & Motor Control
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(yPosition, 0, 1023, leftMotorTopSpeed, -leftMotorTopSpeed);
  mapY = map(xPosition, 0, 1023, rightMotorTopSpeed, -rightMotorTopSpeed);
  
  if (SW_state == 0) {
    goto serialTests;
  }

  // Maps Joystick position to equivalent motor thrust values
  joystickAngle = atan(mapY / mapX);
  if (mapY > 0) {
    if (mapX > 0) {
      // ROV turns Right
      // Split right quadrant into two regions to apply scaling effect to mapY
      if (joystickAngle >= 0 && joystickAngle < PI / 4) {
        leftMotor += mapX;
        rightMotor += mapY * (mapY / sqrt(pow(mapX, 2) + pow(mapY, 2)));
      } else if (joystickAngle >= PI / 4 && joystickAngle <= PI / 2) {
        leftMotor += mapY;
        rightMotor += mapY * (mapY / sqrt(pow(mapX, 2) + pow(mapY, 2)));
      }
    } else if (mapX < 0) {
      // ROV turns Left
      // Split left quadrant into two regions to apply scaling effect
      if (-joystickAngle >= 0 && -joystickAngle < PI / 4) {
        leftMotor += mapY * (mapY / sqrt(pow(mapX, 2) + pow(mapY, 2)));
        rightMotor += -mapX;
      } else if (-joystickAngle >= PI / 4 && -joystickAngle <= PI / 2) {
        Serial.print("Left");
        leftMotor += mapY * (mapY / sqrt(pow(mapX, 2) + pow(mapY, 2)));
        rightMotor += mapY;
      }
    }
  }
  
  // leftMotor and rightMotor Speed correction
  if (leftMotor < 1000) {
    leftMotor = 1000;
  }
  if (rightMotor < 1000) {
    rightMotor = 1000;
  }
  
  leftMotor = leftMotor * (0.18) + lastMotorSpeedLeft * (0.82);
  rightMotor = rightMotor * (0.18) + lastMotorSpeedRight * (0.82);
  // Stores latest motor speed
  lastMotorSpeedLeft = leftMotor;
  lastMotorSpeedRight = rightMotor;
  
  ESCLeft.writeMicroseconds((int) leftMotor);
  ESCRight.writeMicroseconds((int) rightMotor);
  
  // OLED Motor Speed Display
  // Left Motor
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
  display.println("L");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(8,1);
  display.println((int) leftMotor);

  display.drawRect(1, 10, 6, 20, SSD1306_WHITE);
  display.fillRect(2, 11, 4, map(leftMotor - 1000, 0, motorTopSpeed, 0, 19), SSD1306_WHITE);

  // Right Motor
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(97,1);
  display.println("R");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(104,1);
  display.println((int) rightMotor);

  display.drawRect(120, 10, 6, 20, SSD1306_WHITE);
  display.fillRect(121, 11, 4, map(rightMotor - 1000, 0, motorTopSpeed, 0, 19), SSD1306_WHITE);
  
  serialTests:
  // Serial Tests
  Serial.print("LeftMotorMs: ");
  Serial.print((int) leftMotor);
  Serial.print(" | RightMotorMs: ");
  Serial.print((int) rightMotor);
  Serial.print(" | MiddleMotorMs : ");
  Serial.println(potValue);

  // Resets motor speed
  rightMotor = 1000;
  leftMotor = 1000;

  display.display();
  delay(5);
}
