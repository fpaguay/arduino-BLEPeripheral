#include "BLECharArrayCharacteristic.h"

BLECharArrayCharacteristic::BLECharArrayCharacteristic(const char* uuid, unsigned char properties, unsigned char valueSize) :
  BLECharacteristic(uuid, properties, valueSize)
{
  this->_valueLength = valueSize;
}

BLECharArrayCharacteristic::BLECharArrayCharacteristic(const char* uuid, unsigned char properties, const char* value) :
  BLECharacteristic(uuid, properties, value)
{
}

bool BLECharArrayCharacteristic::fixedLength() const {
  return false;
}
