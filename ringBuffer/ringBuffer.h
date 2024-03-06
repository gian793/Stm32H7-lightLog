/**
 * \file            ringBuffer.h
 * \brief           Ring buffer.
 * \author          g.marcolin
 */


#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

/*---------------------------------------------------------------------------*/

//#ifdef __cplusplus
//extern "C" {
//#endif

/*---------------------------------------------------------------------------*/

template <class T>
class ringBuffer
{
    public:
        ringBuffer( T* pBuf, const size_t size ) : buf{ std::unique_ptr<T[]>( pBuf ) }, maxSize{ size }
        {
            stm32_lock_init( &lock );
        }

        void reset( void );
        void put( const T item );
        void put( const T* itemBuf, const size_t itemCnt );
        const T get( void );
        bool isEmpty( void ) const;
        bool isFull( void ) const;
        size_t capacity( void ) const;
        size_t size( void ) const;

    protected:
        LockingData_t lock;

    private:
//        std::mutex rbMutex;  // protects g_i

        std::unique_ptr<T[]> buf;
        const size_t maxSize;

        size_t head = 0;
        size_t tail = 0;

        bool isBufFull = false;
};

//#ifdef __cplusplus
//}
//#endif

/*---------------------------------------------------------------------------*/
#endif
