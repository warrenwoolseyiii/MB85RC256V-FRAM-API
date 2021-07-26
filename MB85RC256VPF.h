#ifndef MB85RC256VPF_H_
#define MB85RC256VPF_H_

#include <stdint.h>

#define MB85RC256VPF_DEVICE_CODE 0b1010
#define MB85RC256VPF_DEVICE_ID 0x00A510
#define MB85RC256VPF_MEMORY_SIZE 0x8000
#define MB85RC256VPF_RSV_SLAVE_ID_0 ( 0xF8 >> 1 )

class MB85RC256VPF
{
  public:
    MB85RC256VPF( int a210Value );
    int GetID();
    int WriteBytes( int addr, uint8_t *data, int len );
    int ReadBytes( int addr, uint8_t *data, int len );
    int ReadBytesFromLastAddr( uint8_t *data, int len );

  protected:
    int _i2cAddr;

    // User populated
    bool i2cStart( int i2cAddr, bool isWrite );
    int  i2cWrite( uint8_t *data, int len, bool stop );
    int  i2cRead( uint8_t *data, int len, bool stop, bool ack = true );
};

#endif /* MB85RC256VPF_H_ */
