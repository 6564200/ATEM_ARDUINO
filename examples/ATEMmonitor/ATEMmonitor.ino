#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>


// MAC address and IP address for this *particular* Ethernet Shield!
// MAC address is printed on the shield
// IP address is an available address you choose on your subnet where the switcher is also present:
byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x00, 0xE8, 0xE9 };		// <= SETUP
IPAddress ip(192, 168, 0, 20);				// <= SETUP


// Include ATEM library and make an instance:
#include <ATEM.h>

// Connect to an ATEM switcher on this address and using this local port:
// The port number is chosen randomly among high numbers.
ATEM AtemSwitcher(IPAddress(192, 168, 0, 150), 56417);  // <= SETUP (the IP address of the ATEM switcher)



void setup() { 

  // Start the Ethernet, Serial (debugging) and UDP:
  Ethernet.begin(mac,ip);
  Serial.begin(9600);  
  Serial.println("Serial started.");

  // Initialize a connection to the switcher:
  AtemSwitcher.serialOutput(true);
  AtemSwitcher.connect();
}

void loop() {
      // Check for packets, respond to them etc. Keeping the connection alive!
  AtemSwitcher.runLoop();
}
