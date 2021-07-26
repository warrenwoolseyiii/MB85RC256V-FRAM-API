# MB85RC256V-FRAM-API
This project is a simple firmware API for utilizing the MB85RC256V FRAM chip. The implementation is provided as a C++ class with user defined stubs for the i2c communication interface. This is a full implementation for the base feature set from the chip's datasheet which can be found here: https://cdn-shop.adafruit.com/product-files/1895/MB85RC256V-DS501-00017-3v0-E.pdf

# How to use
Simply clone this repoistory into your project and implement a user stub for the three i2c functions at the bottom of the class implementation. User is repsonsible for implementing:
1. `bool MB85RC256VPF::i2cStart( int i2cAddr, bool isWrite )` - which initializes a write or read i2c transaction by sending a start condition with the slave address, returns true if the transaction was successfully started and false otherwise.
2. `int MB85RC256VPF::i2cWrite( uint8_t *data, int len, bool stop )` - which writes len amount of the payload data and issues a stop condition if the stop argument is set to true, returns the amount of bytes written.
3. `int MB85RC256VPF::i2cRead( uint8_t *data, int len, bool stop, bool ack )` - which reads len amount of the payload into data and issues a stop condition if the stop argument is set to true, returns the amount of bytes read.

# Examples
A sample implementation using my [SAMD20 Arduino SDK](https://github.com/warrenwoolseyiii/Arduino-SAMD20) is baked into the main class and can be used by defining `SAMD` at compile time. 
