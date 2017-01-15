// LDD Setup
#include <Stepper.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <dht.h>
#define dataPin 4 // Defines pin number to which the sensor is connected
dht DHT; // Creats a DHT object

#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);

int n = 1;
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
DallasTemperature sensors(&oneWire);

int stepsPerRevolution = 0; 
int xPin = A1;
int yPin = A2;;
int xPosition = 0;
int yPosition = 0;
 
Stepper myStepper(10, 8, 9, 10, 11);

void setup() 
{
// start serial port
  Serial.begin(9600);
  // lcd.print("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();

pinMode(xPin, INPUT);
pinMode(yPin, INPUT); 
lcd.begin (16,2); //  <<----- My LCD was 16x2

 
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home
}

// SERVO CONTROL
void loop() 
{
  // Centre value for D/A when joystick is centralised is about 530. Choose +and- sitching points for X and Y to suite required sensativity for joystick
    // FORWARD (Fine)
    xPosition = analogRead(xPin);
    while(xPosition < 400){
    myStepper.setSpeed(700);
    stepsPerRevolution = (20);
    myStepper.step(2);
    xPosition = analogRead(xPin);
    lcd.setCursor (0,0);
    lcd.print("FORWARD Fine  ");

    }
    // REVERSE (Fine)
    xPosition = analogRead(xPin);
    while(xPosition > 700){
    myStepper.setSpeed(700);
    stepsPerRevolution = (20);
    myStepper.step(-2);
    xPosition = analogRead(xPin);
    lcd.setCursor (0,0);
    lcd.print("REVERSE Fine  ");
    }
    
    // FORWARDS (Coarse)
    yPosition = analogRead(yPin);
    while(yPosition < 400){
    myStepper.setSpeed(3000);
    stepsPerRevolution = (1);
    myStepper.step(-100);
    yPosition = analogRead(yPin);
    lcd.setCursor (0,0);
    lcd.print("FORWARD Coarse");    
    }
    
    // REVERSE (Coarse)
    yPosition = analogRead(yPin);
    while(yPosition > 700){ 
    myStepper.setSpeed(3000);
    stepsPerRevolution = (1);
    myStepper.step(100);
    yPosition = analogRead(yPin);
    lcd.setCursor (0,0);
    lcd.print("REVERSE Coarse");
    }  
  
  // DIGITAL TEMPERATURE SENSOR (If Required.) 
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  //sensors.requestTemperatures(); // Send the command to get temperatures
  //lcd.setCursor (0,1);
  //lcd.print("T ");
  //lcd.setCursor (2,1);
  //lcd.print(sensors.getTempCByIndex(0));
  //lcd.setCursor(7,1);
  //lcd.print("C"); 

  //HUMIDITY DHT-11
  int readData = DHT.read22(dataPin); // Reads the data from the sensor
  float t = DHT.temperature; // Gets the values of the temperature
  float h = DHT.humidity; // Gets the values of the humidity
  
  // Printing the results on the serial monitor
  sensors.requestTemperatures(); // Send the command to get temperatures 
  
  // Print "TXX.XXc and HXX.XX%" on line 2 of LCD
  lcd.setCursor (0,1);
  lcd.print("T");
  lcd.setCursor (1,1);
  lcd.print(t/30);
  lcd.setCursor(6,1);
  lcd.print("c"); 
  lcd.setCursor (9,1);
  lcd.print("H ");
  lcd.setCursor (10,1);
  lcd.print(h/30);
  lcd.setCursor(15,1);
  lcd.print("%");   
  //delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz

}

