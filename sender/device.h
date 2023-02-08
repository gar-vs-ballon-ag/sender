#ifndef DEVICE_H
#define DEVICE_H

class Device {
  public:
    // jedes physikalische gerät hat einen (oder mehrere, hier ist der datenpin gemeint) Pins
    virtual void setup(int pin) = 0;
};

#endif
