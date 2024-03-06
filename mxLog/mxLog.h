/**
 * \file            mxLog.h
 * \brief           Usart log class.
 * \author          g.marcolin
 */

#ifndef MX_LOG_H_
#define MX_LOG_H_

//#ifdef __cplusplus
//extern "C" {
//#endif

#ifdef __cplusplus

/*---------------------------------------------------------------------------*/

#include "stm32h7xx.h"
#include "stm32_lock.h"
#include "ringBuffer.h"

/*---------------------------------------------------------------------------*/

//enum class usart {
//    usart1,
//    usart2,
//    usart3,
//    uart4,
//    uart5,
//    usart6,
//    uart7,
//    uart8  };

/*---------------------------------------------------------------------------*/

/* Functions definition in header file to avoid inline. */
/*---------------------------------------------------------------------------*/

class mxLog : public ringBuffer<char> {

    public:

        explicit mxLog( char* pBuf, const size_t bufSize, UART_HandleTypeDef& usartHandle ) : ringBuffer{ pBuf, bufSize }, pUsart{ &usartHandle } {}

        // disable copy/move
        mxLog( const mxLog& ) = delete;
        mxLog( mxLog&& ) = delete;
        mxLog& operator=( const mxLog& ) = delete;
        mxLog& operator=( mxLog&& ) = delete;

		size_t Info( const fLog formatLog, ... );

        size_t storeMsg( const fData_t* pfData, va_list args );

//        size_t Debug  ( const char* format, ... );
//        size_t Warn ( const char* format, ... );
//        size_t Error( const char* format, ... );

        void taskManager( void );

    private:
        UART_HandleTypeDef* pUsart;

//        consteval parType_t getParameterType( const char* format );

        size_t putPar( const char format, const char* par );

        size_t getParSize( const char format, const char* par );

        bool getHeader( void );

        void printOut( void );
        void printStr( const char* pStr, const char endChar );
        void printPar( const char format );


//        static constexpr std::array<uint32_t, 8> usartBaseList = {
//                USART1_BASE,
//                USART2_BASE,
//                USART3_BASE,
//                UART4_BASE,
//                UART5_BASE,
//                USART6_BASE,
//                UART7_BASE,
//                UART8_BASE    } ;
};

#else

typedef struct mxLog mxLog;

size_t mxLogInfo( mxLog* pLog, const char* format, ... );

#endif

//#ifdef __cplusplus
//}
//#endif

/*---------------------------------------------------------------------------*/

#endif /* MX_LOG_H_ */
