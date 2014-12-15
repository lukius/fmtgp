#ifndef __MISC__H
#define __MISC__H

#define Regular typename
#define Integer typename
#define SemigroupOperation typename
#define MonoidOperation typename


template<Integer N>
bool odd(N n)
{
    return n & 0x1;
} 

template<Integer N>
N half(N n)
{
    return n >> 1;
} 

#endif
