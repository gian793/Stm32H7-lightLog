/**
 * \file            ringBuffer.cpp
 * \brief           Ring buffer.
 * \author          g.marcolin
 */

/*---------------------------------------------------------------------------*/

#include <mutex>
#include <memory>
#include "stm32_lock.h"
#include "ringBuffer.h"

/*---------------------------------------------------------------------------*/

/**
  * @brief  Reset the buffer to zero.
  * @param  None
  * @retval None
  */

template <class T>
void ringBuffer<T>::reset( void )
{
    stm32_lock_acquire( &lock );

    head = tail;

    isBufFull = false;

    for( uint32_t i = 0; i < maxSize; ++i )
    {
        buf[ i ] = 0;
    }

    stm32_lock_release( &lock );
}

/**
  * @brief  Empty buffer check.
  * @param  None
  * @retval True if empty.
  */

template <class T>
bool ringBuffer<T>::isEmpty( void ) const
{
    // If head and tail are equal, it is empty
    return ( !isBufFull && ( head == tail ) );
}

/**
  * @brief  Full buffer check.
  * @param  None
  * @retval True if full.
  */

template <class T>
bool ringBuffer<T>::isFull( void ) const
{
    return isBufFull;
}

/**
  * @brief  Return buffer capacity.
  * @param  None
  * @retval Size of the buffer.
  */

template <class T>
size_t ringBuffer<T>::capacity( void ) const
{
    return maxSize;
}

/**
  * @brief  Return the number of items stored in the buffer.
  * @param  None
  * @retval Number of items stored.
  */

template <class T>
size_t ringBuffer<T>::size( void ) const
{
    size_t size = maxSize;

    if( !isBufFull )
    {
        if( head >= tail )
        {
            size = head - tail;
        }
        else
        {
            size = maxSize + head - tail;
        }
    }

    return size;
}

/**
  * @brief  Put a new item in the buffer.
  *         If the buffer is full the oldest one is overwritten.
  * @param  New item to store.
  * @retval None.
  */

template <class T>
void ringBuffer<T>::put( const T item )
{
    stm32_lock_acquire( &lock );

    buf[ head ] = item;

    if( isBufFull )
    {
        tail = ( tail + 1 ) % maxSize;
    }

    head = (head + 1) % maxSize;

    isBufFull = ( head == tail );

    stm32_lock_release( &lock );
}

/**
  * @brief  Put an array of new items in the buffer.
  *         If the buffer is full the oldest ones are overwritten.
  * @param  Array of new items to store.
  *         Number of item to store.
  * @retval None.
  */

template <class T>
void ringBuffer<T>::put( const T* itemBuf, const size_t itemCnt )
{
    stm32_lock_acquire( &lock );

    for( uint32_t i = 0; i < itemCnt; ++i )
    {
        buf[ head ] = itemBuf[i];

        if( isBufFull )
        {
            tail = ( tail + 1 ) % maxSize;
        }

        head = (head + 1) % maxSize;

        isBufFull = ( head == tail );
    }

    stm32_lock_release( &lock );
}

/**
  * @brief  Get the oldest item stored in the buffer.
  *         The item is removed.
  *         The size of the buffer is therefore decreased by 1.
  * @param  None.
  * @retval Oldest item in the buffer.
  */

template <class T>
const T ringBuffer<T>::get( void )
{
    stm32_lock_acquire( &lock );

    //Read data and advance the tail (we now have a free space)
    auto val = buf[ tail ];

    isBufFull = false;

    tail = ( tail + 1 ) % maxSize;

    stm32_lock_release( &lock );

    return val;
}

/*---------------------------------------------------------------------------*/

template class ringBuffer<char>;
template class ringBuffer<uint32_t>;

/*---------------------------------------------------------------------------*/
