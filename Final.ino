#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define GSM_RX 2
#define GSM_TX 3
#define BUZZER_PIN 4
#define VIBRATION_PIN 5
#define EYE_BLINK_PIN A0
#define SWITCH_PIN 7

SoftwareSerial gsmSerial(GSM_RX, GSM_TX);

TinyGPSPlus gps;
bool isDriverAwake = true;
bool isSwitchOn = false;
unsigned long lastBlinkTime = 0;
unsigned long lastVibrateTime = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(EYE_BLINK_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  gsmSerial.begin(9600);
}

void loop() {
  checkEyeBlink();
  checkAccident();
  checkSwitch();
}

void checkEyeBlink() {
  if (digitalRead(EYE_BLINK_PIN) == LOW) {
    if (!isDriverAwake) {
      isDriverAwake = true;
      turnOffAlert();
    }
  } else {
    if (isDriverAwake) {
      isDriverAwake = false;
      sendAlert();
    }
  }
}

void checkAccident() {
  if (!isDriverAwake) {
    if (millis() - lastVibrateTime > 15000) {
      sendLocation();
    }
  }
}

void checkSwitch() {
  if (digitalRead(SWITCH_PIN) == LOW) {
    isSwitchOn = true;
    turnOffAlert();
  } else {
    isSwitchOn = false;
  }
}

void turnOffAlert() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(VIBRATION_PIN, LOW);
}

void sendAlert() {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(VIBRATION_PIN, HIGH);
  
  if (!isSwitchOn) {
    gsmSerial.println("AT+CMGF=1"); 
    delay(1000);
    gsmSerial.println("AT+CMGS=\"+919321092120\""); 
    gsmSerial.println("Alert: Driver is not responding!"); 
    delay(1000);
    gsmSerial.println((char)26); 
    delay(1000);
  }
}

void sendLocation() {
  if (gps.location.isValid()) {
    String latitude = String(gps.location.lat(), 6);
    String longitude = String(gps.location.lng(), 6);
    String googleMapsUrl = "https://www.google.com/maps?q=" + latitude + "," + longitude;
    
    if (!isSwitchOn) {
      gsmSerial.println("AT+CMGF=1"); 
      delay(1000);
      gsmSerial.println("AT+CMGS=\"+919321092120\""); 
      delay(1000);
      gsmSerial.println(googleMapsUrl); 
      delay(1000);
      gsmSerial.println((char)26); 
      delay(1000);
    }
  }
}

void serialEvent() {
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      sendLocation();
    }
  }
}


// #include <SoftwareSerial.h>
// #include <TinyGPS++.h>

// #define GSM_RX 2
// #define GSM_TX 3
// #define BUZZER_PIN 4
// #define VIBRATION_PIN 5
// #define EYE_BLINK_PIN 6
// #define SWITCH_PIN 7

// SoftwareSerial gsmSerial(GSM_RX, GSM_TX);

// TinyGPSPlus gps;
// bool isDriverAwake = true;
// bool isSendingAlert = true;

// void setup() {
//   pinMode(BUZZER_PIN, OUTPUT);
//   pinMode(VIBRATION_PIN, OUTPUT);
//   pinMode(EYE_BLINK_PIN, INPUT);
//   pinMode(SWITCH_PIN, INPUT);
  
//   Serial.begin(9600);
//   gsmSerial.begin(9600);
// }

// void loop() {
//   checkEyeBlink();
//   checkAccident();
// }

// void checkEyeBlink() {
//   if (digitalRead(EYE_BLINK_PIN) == LOW) {
//     if (!isDriverAwake) {
//       isDriverAwake = true;
//       turnOffAlert();
//     }
//   } else {
//     if (isDriverAwake) {
//       isDriverAwake = false;
//       sendAlert();
//     }
//   }
// }

// void checkAccident() {
//   if (!isDriverAwake && isSendingAlert) {
//     unsigned long bufferTime = 15000; // 15 seconds buffer time
    
//     digitalWrite(BUZZER_PIN, HIGH);
//     digitalWrite(VIBRATION_PIN, HIGH);
//     delay(bufferTime);
    
//     if (!digitalRead(SWITCH_PIN)) {
//       isSendingAlert = false;
//     } else {
//       sendLocation();
//     }
//   }
// }

// void turnOffAlert() {
//   digitalWrite(BUZZER_PIN, LOW);
//   digitalWrite(VIBRATION_PIN, LOW);
// }

// void sendAlert() {
//   digitalWrite(BUZZER_PIN, HIGH);
//   digitalWrite(VIBRATION_PIN, HIGH);
  
//   gsmSerial.println("AT+CMGF=1"); 
//   delay(1000);
//   gsmSerial.println("AT+CMGS=\"+1234567890\""); // Replace +1234567890 with your designated contact number
//   delay(1000);
//   gsmSerial.println("Alert: Driver is not responding!"); // Message content
//   delay(1000);
//   gsmSerial.println((char)26); // End AT command with a CTRL+Z
//   delay(1000);
// }

// void sendLocation() {
//   if (gps.location.isValid()) {
//     String latitude = String(gps.location.lat(), 6);
//     String longitude = String(gps.location.lng(), 6);
//     String googleMapsUrl = "https://www.google.com/maps?q=" + latitude + "," + longitude;
    
//     gsmSerial.println("AT+CMGF=1"); 
//     delay(1000);
//     gsmSerial.println("AT+CMGS=\"+1234567890\""); // Replace +1234567890 with your designated contact number
//     delay(1000);
//     gsmSerial.println(googleMapsUrl); // Message content
//     delay(1000);
//     gsmSerial.println((char)26); // End AT command with a CTRL+Z
//     delay(1000);
//   }
// }

// void serialEvent() {
//   while (Serial.available() > 0) {
//     if (gps.encode(Serial.read())) {
//       sendLocation();
//     }
//   }
// }



// #include <SoftwareSerial.h>
// #include <TinyGPS++.h>

// #define GSM_RX 2
// #define GSM_TX 3
// #define BUZZER_PIN 4
// #define VIBRATION_PIN 5
// #define EYE_BLINK_PIN 6
// #define SWITCH_BUTTON_PIN 7

// SoftwareSerial gsmSerial(GSM_RX, GSM_TX);

// TinyGPSPlus gps;
// bool isDriverAwake = true;
// bool sendAlertFlag = true;

// void setup() {
//   pinMode(BUZZER_PIN, OUTPUT);
//   pinMode(VIBRATION_PIN, OUTPUT);
//   pinMode(EYE_BLINK_PIN, INPUT);
//   pinMode(SWITCH_BUTTON_PIN, INPUT_PULLUP);
  
//   Serial.begin(9600);
//   gsmSerial.begin(9600);
// }

// void loop() {
//   checkEyeBlink();
//   checkAccident();
// }

// void checkEyeBlink() {
//   if (digitalRead(EYE_BLINK_PIN) == LOW) {
//     if (!isDriverAwake) {
//       isDriverAwake = true;
//       turnOffAlert();
//     }
//   } else {
//     if (isDriverAwake) {
//       isDriverAwake = false;
//       sendAlertFlag = true;
//       sendAlert();
//     }
//   }
// }

// void checkAccident() {
//   if (!isDriverAwake) {
//     sendLocation();
    
//     if (sendAlertFlag && digitalRead(SWITCH_BUTTON_PIN) == LOW) {
//       sendAlert();
//       sendAlertFlag = false;
//     }
//   }
// }

// void turnOffAlert() {
//   digitalWrite(BUZZER_PIN, LOW);
//   digitalWrite(VIBRATION_PIN, LOW);
// }

// void sendAlert() {
//   digitalWrite(BUZZER_PIN, HIGH);
//   digitalWrite(VIBRATION_PIN, HIGH);
  
//   gsmSerial.println("AT+CMGF=1"); 
//   delay(1000);
//   gsmSerial.println("AT+CMGS=\"+1234567890\""); // Replace +1234567890 with your designated contact number
//   delay(1000);
//   gsmSerial.println("Alert: Driver is not responding!"); // Message content
//   delay(1000);
//   gsmSerial.println((char)26); // End AT command with a CTRL+Z
//   delay(1000);
  
//   delay(15000);
  
//   if (!isDriverAwake && sendAlertFlag) {
//     sendCall();
//     sendLocation();
//   }
// }

// void sendCall() {
//   gsmSerial.println("ATD+1234567890;"); // Replace +1234567890 with your designated contact number
//   delay(1000);
//   gsmSerial.println((char)26); // End AT command with a CTRL+Z
//   delay(1000);
// }

// void sendLocation() {
//   if (gps.location.isValid()) {
//     String latitude = String(gps.location.lat(), 6);
//     String longitude = String(gps.location.lng(), 6);
//     String googleMapsUrl = "https://www.google.com/maps?q=" + latitude + "," + longitude;
    
//     gsmSerial.println("AT+CMGF=1"); 
//     delay(1000);
//     gsmSerial.println("AT+CMGS=\"+1234567890\""); // Replace +1234567890 with your designated contact number
//     delay(1000);
//     gsmSerial.println(googleMapsUrl); // Message content
//     delay(1000);
//     gsmSerial.println((char)26); // End AT command with a CTRL+Z
//     delay(1000);
//   }
// }

// void serialEvent() {
//   while (Serial.available() > 0) {
//     if (gps.encode(Serial.read())) {
//       sendLocation();
//     }
//   }
// }
