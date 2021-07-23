#include "MB85RC256VPF.h"

MB85RC256VPF::MB85RC256VPF( int a210Value )
{
    _i2cAddr =
        ( MB85RC256VPF_DEVICE_CODE << 4 ) | ( ( 0x07 & a210Value ) << 1 );
}

int MB85RC256VPF::GetID()
{
    int deviceID = 0;
    if( i2cWrite( MB85RC256VPF_RSV_SLAVE_ID_0, (uint8_t *)&_i2cAddr, 1, true,
                  false ) != 1 ) {
        return 0;
    }
    if( i2cRead( MB85RC256VPF_RSV_SLAVE_ID_1, (uint8_t *)&deviceID, 3, true,
                 true ) != 3 ) {
        return 0;
    }
    return deviceID;
}

int MB85RC256VPF::WriteBytes( int addr, uint8_t *data, int len )
{
    // Check the address
    if( addr > MB85RC256VPF_MEMORY_SIZE ) return 0;

    // Transmit a start condition and the address to write to
    if( i2cWrite( _i2cAddr, (uint8_t *)&addr, 2, true, false ) != 2 ) {
        return 0;
    }

    // Continue the write until the end and send a stop condition
    return i2cWrite( _i2cAddr, data, len, false, true );
}

int MB85RC256VPF::ReadBytes( int addr, uint8_t *data, int len )
{
    // Check the address
    if( addr > MB85RC256VPF_MEMORY_SIZE ) return 0;

    // Transmit a start condition and the address to read from
    if( i2cWrite( _i2cAddr, (uint8_t *)&addr, 2, true, false ) != 2 ) {
        return 0;
    }

    // Read until the end and send a stop condition
    return i2cRead( _i2cAddr, data, len, true, true );
}

int MB85RC256VPF::ReadBytesFromLastAddr( uint8_t *data, int len )
{
    // Read until the end and send a stop condition
    return i2cRead( _i2cAddr, data, len, true, true );
}

// User populated
int MB85RC256VPF::i2cWrite( int i2cAddr, uint8_t *data, int len, bool start,
                            bool stop )
{
    // Stub for user to populate with their implementation
}

int MB85RC256VPF::i2cRead( int i2cAddr, uint8_t *data, int len, bool start,
                           bool stop )
{
    // Stub for user to populate with their implementation
}