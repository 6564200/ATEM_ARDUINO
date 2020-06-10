
#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>

byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x00, 0xE8, 0xE9 };		// <= SETUP
IPAddress ip(192, 168, 0, 20);				// <= SETUP

#include <ATEM.h>

ATEM AtemSwitcher(IPAddress(192, 168, 0, 150), 56417);  // <= SETUP (the IP address of the ATEM switcher)

void setup() { 

    // Set up pins for 
  pinMode(7, INPUT);  // Cut
  pinMode(2, INPUT);  // Select 1 for Preview
  pinMode(3, INPUT);  // Select 2 for Preview
  pinMode(4, OUTPUT);  // LED: 1 is on Program (Tally)
  pinMode(5, OUTPUT);  // LED: 2 is on Program (Tally)
    
  Ethernet.begin(mac,ip);
  Serial.begin(9600);  

  // Initialize a connection to the switcher:
  AtemSwitcher.serialOutput(true);
  AtemSwitcher.connect();
}

int pushButton = 0;

void loop() {
  
    // Check for packets, respond to them etc. Keeping the connection alive!
  AtemSwitcher.runLoop();


    // Write the Tally LEDS:
  digitalWrite(4, !AtemSwitcher.getProgramTally(1));
  digitalWrite(5, !AtemSwitcher.getProgramTally(2));


  if (digitalRead(2))  {
    if (pushButton !=2)  {
      pushButton=2;
      Serial.println("Select 1");
      AtemSwitcher.changePreviewInput(1);
    }
  } else if (pushButton==2) {
    pushButton = 0; 
  }
  if (digitalRead(3))  {
    if (pushButton !=3)  {
      pushButton=3;
      Serial.println("Select 2");
      AtemSwitcher.changePreviewInput(2);
    }
  } else if (pushButton==3) {
    pushButton = 0; 
  }
  if (digitalRead(7))  {
    if (pushButton !=7)  {
      pushButton=7;
      Serial.println("Cut");
      AtemSwitcher.doCut();
    }
  } else if (pushButton==7) {
    pushButton = 0; 
  }
}
