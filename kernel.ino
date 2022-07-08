// This is a list storing the names of the menu items
String menuItems[] = {"System Info", "Graphics Test", "RedLED", "BlueLED", "GreenLED", "RGB-Nano"};
int readKey;
int savedDistance = 0;
int menuPage = 0;
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int cursorPosition = 0;
// These byte arrays contain the graphics for the up and down arrow, along with the menu cursor
byte downArrow[8] = {0b00100,0b00100,0b00100,0b00100,0b00100,0b10101,0b01110,0b00100};
byte upArrow[8] = {0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b00100,0b00100};
byte menuCursor[8] = {B01000,B00100,B00010,B00001,B00010,B00100,B01000,B00000};
// Here we are importing the modules for displaying text on the LCD Screen
#include <Wire.h>
#include <LiquidCrystal.h>
// This is initializing the pins that the LCD Display is connected to on the Arduino
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// This is the setup loop in whihc we initialize several items 
void setup() {
  // Here we are seting up these digital pins as output pins that provide HIGH or LOW Signals
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  // We are declaring that pin 14 will output a HIGH Signal
  digitalWrite(14, HIGH); 
  // Now we are just turing on the serial monitor at 9600 Baud
  Serial.begin(9600);
  // This is initializing the dimensions of the LCD Display at 16x2
  lcd.begin(16, 2);
  lcd.clear();
  // Here we are creating new characters using the byte arrays 
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);}
void loop() {
  mainMenuDraw();
  drawCursor();
  operateMainMenu();}
void mainMenuDraw() {
  Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));}}
void drawCursor() {
  for (int x = 0; x < 2; x++) {    
    lcd.setCursor(0, x);
    lcd.print(" ");}
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) { 
      lcd.setCursor(0, 0);
      lcd.write(byte(0));}
    if (cursorPosition % 2 != 0) {  
      lcd.setCursor(0, 1);
      lcd.write(byte(0));}}
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  
      lcd.setCursor(0, 1);
      lcd.write(byte(0));}
    if (cursorPosition % 2 != 0) {  
      lcd.setCursor(0, 0);
      lcd.write(byte(0));}}}
void operateMainMenu() {
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 0:
        break;
      case 1: 
        button = 0;
        switch (cursorPosition) { 
          case 0:
            menuItem1();
            break;
          case 1:
            menuItem2();
            break;
          case 2:
            menuItem3();
            break;
          case 3:
            menuItem4();
            break;
          case 4:
            menuItem5();
            break;
          case 5:
            menuItem6();
            break;
          case 6:
            menuItem7();
            break;
          case 7:
            menuItem8();
            break;
          case 8:
            menuItem9();
            break;
          case 9:
            menuItem10();
            break;}
        activeButton = 1;
        mainMenuDraw();
        drawCursor();
        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));}
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);}
        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);}
        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);}
        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);}
        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;}}}
// This is to detect when a button is pressed.
// Since all the buttons are connected to A0...
// The buttons detect spikes and drops in voltage levels to figure out which buttons are being pressed.
int evaluateButton(int x) {
  int result = 0;
  if (x < 50) {
    result = 1; // right
  } else if (x < 195) {
    result = 2; // up
  } else if (x < 380) {
    result = 3; // down
  } else if (x < 790) {
    result = 4; // left}
  return result;}
void drawInstructions() {
  lcd.setCursor(0, 1); // Setting the cursor to the second line of the display
  lcd.print("Use ");
  lcd.write(byte(1)); // Displaying the up arrow character
  lcd.print("/");
  lcd.write(byte(2)); // Displaying the down arrow character
  lcd.print(" buttons");}
void menuItem1() {
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pamos-Beta v.2.1");
  lcd.setCursor(0,1);
  lcd.print("VID:2341PID:0042");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem2() { 
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1000000000000000");
  delay(200);
  lcd.clear();
  lcd.print("0100000000000000");
  delay(200);
  lcd.clear();
  lcd.print("0010000000000000");
  delay(200);
  lcd.clear();
  lcd.print("0001000000000000");
  delay(200);
  lcd.clear();
  lcd.print("00001000000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000100000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000010000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000001000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000100000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000010000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000001000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000100000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000010000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000001000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000100");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000010");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("1000000000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("0100000000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("0010000000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("0001000000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00001000000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000100000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000010000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000001000000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000100000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000010000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000001000000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000000100000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000000010000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000000001000");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000000000100");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.setCursor(0, 1);
  lcd.print("00000000000000010");
  delay(200);
  lcd.clear();
  lcd.print("00000000000000000");
  lcd.clear();
  lcd.setCursor(0, 1);
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem3() { 
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  digitalWrite(27, HIGH); 
  lcd.print("RedLED ON");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem4() { 
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  digitalWrite(23, HIGH);
  lcd.print("BlueLED ON");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem5() { 
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  digitalWrite(25, HIGH); 
  lcd.print("GreenLED ON");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem6() {
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RGB-Nano Booted");
  digitalWrite(14, LOW); 
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem7() { 
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 7");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem8() {
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 8");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem9() { 
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 9");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;}}}
void menuItem10() { 
  int activeButton = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Arduino Mega 2560");
  lcd.print("VID: 2341 PID: 0042");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);}
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;}}}
