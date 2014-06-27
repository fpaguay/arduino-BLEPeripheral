#ifndef _BLE_PERIPHERAL_H_
#define _BLE_PERIPHERAL_H_

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "BLEAttribute.h"
#include "BLEService.h"
#include "BLECharacteristic.h"
#include "BLEDescriptor.h"

class BLEPeripheral
{
  public:
    BLEPeripheral(int8_t req, int8_t rdy, int8_t rst);
  
    bool begin();
    void poll(void);

    void setAdvertisedServiceUuid(const char* advertisedServiceUuid);
    void setManufacturerData(const char* manufacturerData, int manufacturerDataLength);
    void setLocalName(const char *localName);

    void setDeviceName(const char* deviceName);
    void setAppearance(unsigned short appearance);

    void addAttribute(BLEAttribute& attribute);

  private:
    const char*    _localName;
    const char*    _advertisedServiceUuid;
    const char*    _manufacturerData;
    int            _manufacturerDataLength;

    const char*    _deviceName;
    unsigned short _appearance;

    int            _numCustomSetupMessages;
    unsigned short _nextHandle;
    int            _numAttributes;
    BLEAttribute*  _attributes[15];
};

#endif