/*

FLEX SENSOR

  Use the "flex sensor" to change the position of a servo

  In the previous sketch, we learned how to command a servo to
  mode to different positions. In this sketch, we'll introduce
  a new sensor, and use it to control the servo.

  A flex sensor is a plastic strip with a conductive coating.
  When the strip is straight, the coating will be a certain
  resistance. When the strip is bent, the particles in the coating
  get further apart, increasing the resistance. You can use this
  sensor to sense finger movement in gloves, door hinges, stuffed
  animals, etc. See http://www.sparkfun.com/tutorials/270 for
  more information.

Hardware connections:

  Flex sensor:

    The flex sensor is the plastic strip with black stripes.
    It senses bending away from the striped side.

    The flex sensor has two pins, and since it's a resistor,
    the pins are interchangable.

    Connect one of the pins to ANALOG IN pin 0 on the Arduino.
    Connect the same pin, through a 10K Ohm resistor (brown
    black orange) to GND.
    Connect the other pin to 5V.
*/
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int count = 0;
bool isFlex;

// Define the analog input pin to measure flex sensor position: 
const int FLEX_PIN1 = A0;
const int FLEX_PIN2 = A1;
const int FLEX_PIN3 = A2;
const int FLEX_PIN4 = A3;
const int FLEX_PIN5 = A4;
void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);
  pinMode(FLEX_PIN5, INPUT);
////////////////////////////////////
mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  //myDFPlayer.play(1);
}
///////////////////////////////////////////////

 
  int finger1; 
  int finger3;
  int finger4;
  int finger2;
  int finger5;
  int position1;  
  int position2; 
  int position3;
  int position4;
  int position5;
void loop() 
{ 
  // Read the position of the flex sensor (0 to 1023):
  finger1 = analogRead(FLEX_PIN1);
  finger2 = analogRead(FLEX_PIN2);
  finger3 = analogRead(FLEX_PIN3);
  finger4 = analogRead(FLEX_PIN4);
  finger5 = analogRead(FLEX_PIN5);
  // Because the voltage divider circuit only returns a portion
  // of the 0-1023 range of analogRead(), we'll map() that range
  // to the servo's range of 0 to 180 degrees. The flex sensors
  // we use are usually in the 600-900 range:

  position1 = constrain(map(finger1, 600, 900, 0, 180), 0, 180);
  position2 = constrain(map(finger2, 600, 900, 0, 180), 0, 180);
  position3 = constrain(map(finger3, 600, 900, 0, 180), 0, 180);
  position4 = constrain(map(finger4, 600, 900, 0, 180), 0, 180);
  position5 = constrain(map(finger5, 600, 900, 0, 180), 0, 180);
  //Serial.println(position5);
  comeHere(position1, position2, position3, position4);
  isFlexed(position1, position2, position3, position4);
  
  fuckOff(position1, position2, position3, position4);
  isFlexed(position1, position2, position3, position4);

  goPack(position1, position2, position3, position4);
  isFlexed(position1, position2, position3, position4);

  yes(position1, position2, position3, position4, position5);
  isFlexed(position1, position2, position3, position4);

  no(position1, position2, position3, position4, position5);
  isFlexed(position1, position2, position3, position4);

  help(position1, position2, position3, position4, position5);
  isFlexed(position1, position2, position3, position4);
  Serial.println(position4);

  // After you upload the sketch, turn on the serial monitor
  // (the magnifying-glass icon to the right of the icon bar).
  // You'll be able to see the sensor values. Bend the flex sensor
  // and note its minimum and maximum values. If you replace the
  // 600 and 900 in the map() function above, you'll exactly match
  // the flex sensor's range with the servo's range.

  delay(200);  // wait 500 ms between servo updates
} 
void isFlexed(int p1, int p2, int p3, int p4){
    if((p1 < 40 && p2 < 40 && p3 < 40 && p4 < 40)){
    isFlex = false;
  }
}

//all fingers down
void yes(int p1, int p2, int p3, int p4, int p5){
  if((p1 > 76 && p2 > 76 && p3 > 76 && p4 > 76 && p5 > 76) && (isFlex == false)){
    Serial.println("YES");
    myDFPlayer.play(1); //yes
    isFlex = true;
  }
}
//first two fingers up and rest down
void no(int p1, int p2, int p3, int p4, int p5){
  if((p1 < 30 && p2 < 30 && p3 > 76 && p4 > 76 && p5 < 30) && (isFlex == false)){
    Serial.println("NO");
    myDFPlayer.play(0); //no
    isFlex = true;
  }
}

//all fingers up and thumb down
void help(int p1, int p2, int p3, int p4, int p5){
  if((p1 > 76 && p2 > 76 && p3 > 76 && p4 > 76 && p5 < 30)&& (isFlex == false)){
    Serial.println("HELP");
    myDFPlayer.play(2);
    isFlex = true;
  }
}
void comeHere(int p1, int p2, int p3, int p4){
  if((p1 > 66 && p2 > 66 && p3 > 66 && p4 > 66) && (isFlex == false)){
    Serial.println("COME HERE");
    myDFPlayer.play(3);
    isFlex = true;
  }
}

void goPack(int p1, int p2, int p3, int p4){
  if((p1 < 30 && p2 > 66 && p3 > 66 && p4 < 30)){
    Serial.println("GO PACK!");
    myDFPlayer.play(4);
    delay(500);
    isFlex = true;
  }
}
void fuckOff(int p1, int p2, int p3, int p4){
  if((p1 > 60 && p3 > 60 && p4 > 60 && p2 < 20) && (isFlex == false)){
    Serial.println("********   *   *");
    Serial.println("*          *   *");
    Serial.println("****       *   *");
    Serial.println("*          *   *");
    Serial.println("*           ***");
    Serial.println();
    Serial.println();
    myDFPlayer.play(5);
    isFlex = true;
  }
}




//////////////////////////////////////////////////////////////////////
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
