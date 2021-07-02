#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial hc06(2, 3);

Servo barOne;
Servo barTwo;

const int barOnePin = 9;
const int barTwoPin = 10;

const int openBar = 120;
const int closeBar = 40;

const int train = 13;

const int ledAC = 4; //AC
const int ledBD = 5; //BD
const int ledCD = 6; //CD
const int ledCx = 7; //Cx
const int ledDx = 8; //Dx'
const int A = 11;
const int B = 12;

void setup() {
  Serial.begin(9600);
  pinMode(train, OUTPUT);

  pinMode(ledAC, OUTPUT);
  pinMode(ledBD, OUTPUT);
  pinMode(ledCD, OUTPUT);
  pinMode(ledCx, OUTPUT);
  pinMode(ledDx, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  barOne.attach(barOnePin);
  barTwo.attach(barTwoPin);

  hc06.begin(9600);

  closeAllLed();
  
  closeBarOne();
  closeBarTwo();
}

void loop() {
  stopTrain(); 
  
  if (hc06.available()) {
    closeAllLed();
    closeBarOne();
    closeBarTwo();

    String command = hc06.readStringUntil('2');

    Serial.println(command);

    if (command == "10") {
      openBarOne();
      openBarTwo();
      openSignal(A1);
      runTrain();
    } else if (command == "11") {
      openBarOne();
      openBarTwo();
      openSignal(A1);
      openSignal(A2);
      runTrain();
    } else if (command == "01") {
      openBarOne();
      closeBarTwo();
      openSignal(A2);
      runTrain();
    } else if (command == "00") {
      closeBarOne();
      closeBarTwo();
    } else {
      int str_len = command.length() + 1;
      char char_array[str_len];
      command.toCharArray(char_array, str_len);

      if (char_array[0] == '1') {
        openLight(A);
      }

      if (char_array[1] == '1') {
        openLight(B);
      }

      if (char_array[2] == '1') {
        openLed(ledAC);
      }

      if (char_array[3] == '1') {
        openLed(ledBD);
      }

      if (char_array[4] == '1') {
        openLed(ledCD);
      }

      if (char_array[5] == '1') {
        openLed(ledCx);
      }

      if (char_array[6] == '1') {
        openLed(ledDx);
      }
    }

    if (command = "101") {
      openBarOne();
      openSignal(A1);
    } else if (command = "011") {
      openBarTwo();
      openSignal(A2);
    }
  }
}

void openBarOne() {
  barOne.write(openBar);
}

void openBarTwo() {
  barTwo.write(openBar);
}

void closeBarOne() {
  barOne.write(closeBar);
}

void closeBarTwo() {
  barTwo.write(closeBar);
}

void runTrain() {
  digitalWrite(train, LOW);
  delay(8000);
  stopTrain();
  closeBarOne();
  closeBarTwo();
}

void stopTrain() {
  digitalWrite(train, HIGH);
}

void openLed(int ledNum) {
  digitalWrite(ledNum, LOW);
}

void openLight(int lightNum) {
  digitalWrite(lightNum, HIGH);
}

void openSignal(int signalNum) {
  analogWrite(signalNum, HIGH);
}

void closeAllLed() {
  digitalWrite(ledAC, HIGH);
  digitalWrite(ledBD, HIGH);
  digitalWrite(ledCD, HIGH);
  digitalWrite(ledCx, HIGH);
  digitalWrite(ledDx, HIGH);
  analogWrite(A1, LOW);
  analogWrite(A2, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
}
