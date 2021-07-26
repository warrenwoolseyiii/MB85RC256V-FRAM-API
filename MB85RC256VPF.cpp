#include "MB85RC256VPF.h"

#if defined( SAMD )
#include <I2C.h>
#include <Arduino.h>
#include <Debug.h>
#endif /* SAMD */

MB85RC256VPF::MB85RC256VPF( int a210Value )
{
    _i2cAddr = ( MB85RC256VPF_DEVICE_CODE << 3 ) | ( 0x07 & a210Value );
}

int MB85RC256VPF::GetID()
{
    int tmpAddr = MB85RC256VPF_RSV_SLAVE_ID_0;
    int tmpPayload = _i2cAddr << 1;
    if( !i2cStart( tmpAddr, true ) ) return 0;
    if( i2cWrite( (uint8_t *)&tmpPayload, 1, false ) != 1 ) return 0;
    if( !i2cStart( tmpAddr, false ) ) return 0;
    uint8_t b[3];
    if( i2cRead( b, 3, true ) != 3 ) return 0;
    return ( b[0] << 16 | b[1] << 8 | b[2] );
}

int MB85RC256VPF::WriteBytes( int addr, uint8_t *data, int len )
{
    // Check the address
    if( addr > MB85RC256VPF_MEMORY_SIZE ) return 0;

    // Start, send the address, and data
    if( !i2cStart( _i2cAddr, true ) ) return 0;
    uint8_t b[] = { addr >> 8, addr };
    if( i2cWrite( b, 2, false ) != 2 ) return 0;
    return i2cWrite( data, len, true );
}

int MB85RC256VPF::ReadBytes( int addr, uint8_t *data, int len )
{
    // Check the address
    if( addr > MB85RC256VPF_MEMORY_SIZE ) return 0;

    // Start, send the address, start, read the data
    if( !i2cStart( _i2cAddr, true ) ) return 0;
    uint8_t b[] = { addr >> 8, addr };
    if( i2cWrite( b, 2, false ) != 2 ) return 0;
    if( !i2cStart( _i2cAddr, false ) ) return 0;
    return i2cRead( data, len, true );
}

int MB85RC256VPF::ReadBytesFromLastAddr( uint8_t *data, int len )
{
    // Start, read
    if( !i2cStart( _i2cAddr, false ) ) return 0;
    return i2cRead( data, len, true );
}

// User populated
bool MB85RC256VPF::i2cStart( int i2cAddr, bool isWrite )
{
#if defined( SAMD )
    int err = TwoWire.MasterStartTransac( i2cAddr & 0xFF, isWrite );
    if( err != I2CM_ERR_NONE ) {
        SYS_ERR( "i2cStart failure, %d\n", err );
        TwoWire.ResolveError( err );
        return false;
    }
    return true;
#else
    // TODO: User implementation here
    return false;
#endif /* SAMD */
}

int MB85RC256VPF::i2cWrite( uint8_t *data, int len, bool stop )
{
#if defined( SAMD )
    int err = TwoWire.MasterSendBytes( data, len, stop );
    if( err != I2CM_ERR_NONE ) {
        SYS_ERR( "i2cWrite failure, %d\n", err );
        TwoWire.ResolveError( err );
        return 0;
    }
    return len;
#else
    // TODO: User implementation here
    return 0;
#endif /* SAMD */
}

int MB85RC256VPF::i2cRead( uint8_t *data, int len, bool stop, bool ack )
{
#if defined( SAMD )
    int err = TwoWire.MasterReceiveBytes( data, len, ack, stop );
    if( err != I2CM_ERR_NONE ) {
        SYS_ERR( "i2cWrite failure, %d\n", err );
        TwoWire.ResolveError( err );
        return 0;
    }
    return len;
#else
    // TODO: User implementation here
    return 0;
#endif /* SAMD */
}
