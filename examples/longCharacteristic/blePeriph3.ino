// Import libraries (BLEPeripheral depends on SPI)
#include <SPI.h>
#include <BLEPeripheral.h>

//////////////
// Hardware //
//////////////
#define BTN_PIN    6 // BTN pin on 6
#define BTN_ACTIVE LOW
#define LED_PIN    7 // LED on pin 7
#define LED_ACTIVE LOW // Pin 7 LED is active low

///////////////////////
// BLE Advertisments //
///////////////////////
const char * localName = "nRF52832 Button";
BLEPeripheral blePeriph;
BLEService bleServ("2805");
BLEService bleServ2("3900");
BLEBoolCharacteristic btnBool("1103", BLERead | BLENotify);
BLEIntCharacteristic intCharacteristic("1104",  BLERead | BLENotify |BLEWrite);
BLECharArrayCharacteristic charCharacteristic( "1234", BLERead | BLENotify, "hello\0" );
BLEDescriptor descriptor( "8901", "helloWorld");
char s[100];

void setup() 
{
  Serial.begin(115200); // Set up serial at 115200 baud
  

  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, !LED_ACTIVE);

  setupBLE();
}

void loop()
{
  blePeriph.poll();

  sprintf(s, "Connected? %d\n", blePeriph.connected());
  Serial.println(s);
  
  // read the current button pin state
  bool buttonValue = digitalRead(BTN_PIN);
  int intInput = intCharacteristic.value();

  // has the value changed since the last read
  bool buttonChanged = (btnBool.value() != buttonValue);

  if (buttonChanged) 
  {
    // button state changed, update characteristics
    btnBool.setValue(buttonValue);
    if (buttonValue)
      digitalWrite(LED_PIN, LED_ACTIVE);
    else
      digitalWrite(LED_PIN, !LED_ACTIVE);
  }
}

void setupBLE()
{
  // Advertise name and service:
  blePeriph.setDeviceName(localName);
  blePeriph.setLocalName(localName);
  blePeriph.setAdvertisedServiceUuid(bleServ.uuid());

  // Add service
  blePeriph.addAttribute(bleServ);
  
  // Add characteristic
  blePeriph.addAttribute(btnBool);
  blePeriph.addAttribute(descriptor);
  blePeriph.addAttribute(intCharacteristic);
  blePeriph.addAttribute(charCharacteristic);
  
  //configure characteristics
  intCharacteristic.setValue(0);
  btnBool.setValue(0);
  
  //unsigned char len = 4;
  //const unsigned char uCharVal[] = "1234";
  //charCharacteristic.setValue(&uCharVal[0],len);

  blePeriph.addAttribute(bleServ2);

  // Now that device, service, characteristic are set up,
  // initialize BLE:
  blePeriph.begin(); 
}
