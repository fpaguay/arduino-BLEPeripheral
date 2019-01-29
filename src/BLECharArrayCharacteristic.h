#ifndef _BLE_CHAR_ARRAY_CHARACTERISTIC_H_
#define _BLE_CHAR_ARRAY_CHARACTERISTIC_H_

#include "BLECharacteristic.h"

class BLECharArrayCharacteristic : public BLECharacteristic {
  public:
    BLECharArrayCharacteristic(const char* uuid, unsigned char properties, unsigned char valueSize);
    BLECharArrayCharacteristic(const char* uuid, unsigned char properties, const char* value);

    virtual bool fixedLength() const;
};

#endif
