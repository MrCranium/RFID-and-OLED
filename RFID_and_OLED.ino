
#include "Wire.h"
#include "Adafruit_NFCShield_I2C.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


#define IRQ 2
#define RESET 8

int redLED = 11;
int greenLED = 12;

Adafruit_NFCShield_I2C nfc(IRQ, RESET);


//////////////////////////////////// SETUP

void setup() {
  // set up Serial library at 9600 bps
  Serial.begin(9600);
  
  Serial.print("RFID & OLED Reader");
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  display.clearDisplay();
  
  pinMode(OLED_RESET, OUTPUT);
  
  Serial.println();
  Serial.print("Screen Ready.");
  Serial.println();
  
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // find Adafruit RFID/NFC shield
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();

}

/////////////////////////////////// LOOP

unsigned digit = 0;

void loop() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; // Buffer to store the returned UID
  uint8_t uidLength; // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // wait for RFID card to show up!
  Serial.println("Waiting for an ISO14443A Card ...");
  
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(27, 20);
  display.print("Please");
  display.println();
  display.print(" Scan Card");
  
  display.display();
  display.clearDisplay();

    
  // Wait for an ISO14443A type cards (Mifare, etc.). When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  uint32_t cardidentifier = 0;
  
  if (success) {
    // Found a card!

    Serial.print("Card detected #");
    // turn the four byte UID of a mifare classic into a single variable #
    cardidentifier = uid[3];
    cardidentifier <<= 8; cardidentifier |= uid[2];
    cardidentifier <<= 8; cardidentifier |= uid[1];
    cardidentifier <<= 8; cardidentifier |= uid[0];
    Serial.println(cardidentifier);
    
  // repeat this for loop as many times as you have RFID cards
    if (cardidentifier == xxxxxxxxxx) { // this is the card's unique identifier
                                        //replace the x's with your card's ID
      
      digitalWrite(OLED_RESET, HIGH);
      
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
     
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(23,10);
      display.println("Welcome");
      display.setTextSize(3);
      display.setCursor(20, 30);
      display.print("Ethan");
  
      display.display();
      display.clearDisplay();
  
      delay(2000);
    }
    
    if (cardidentifier == xxxxxxxxxx) {
      
      digitalWrite(OLED_RESET, HIGH);
      
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
     
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(23,10);
      display.println("Welcome");
      display.setTextSize(3);
      display.setCursor(13, 30);
      display.print("Bonnie");
  
      display.display();
      display.clearDisplay();
  
      delay(2000);
    }
    
  }
}
