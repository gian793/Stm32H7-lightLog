/**
 * \file            fLog.h
 * \brief           Formatted log data for logging.
 * \author          g.marcolin
 */

#ifndef F_LOG_H_
#define F_LOG_H_

/*---------------------------------------------------------------------------*/

/* Data required to log a formatted string. */
typedef struct fData
{
    const char* const pStr; /* Pointer to the log string.                                */
    const int32_t pos;      /* Position of the % format in the string.-1 is not present. */
    const char format;      /* Format specifier. '0' if not present.                     */
}
fData_t;

/*---------------------------------------------------------------------------*/

constexpr int32_t fPositionGet( const char* p )
{
    int32_t i = 0;

    while( p[ i ] != '%' && p[ i ] != '\0' )
    {
        /* Increment by 2 if this is an escape char i.e. '\'. */
        i = ( p[ i ] == '\\' ) ? ( i + 2 ) : ( i + 1 );
    }

    if( p[ i ] != '%' )
    {
        i = -1;
    }

    return i;
}

constexpr char fFormatGet( const char* p )
{
    char format = '0';

    const int32_t pos =  fPositionGet( p );

    if( pos != -1 )
    {
        format = p[ pos + 1 ];
    }

    return format;
}

/*---------------------------------------------------------------------------*/

class fLog {

    consteval int32_t getPos( const char* pStr )
    {
        return fPositionGet( pStr );
    }

    consteval char getFormat( const char* pStr )
    {
        return fFormatGet( pStr );
    }

public:
    fData_t fData{};

    consteval fLog(const char* str): fData{ .pStr{ str },
                                            .pos{ getPos(str) },
                                            .format{ getFormat(str) } } {}
};


/*---------------------------------------------------------------------------*/

#endif /* F_LOG_H_ */
