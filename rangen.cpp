#include "rangen.h"

ranGen::ranGen()
{
    next=1;
}

long ranGen::rand()
{
    next=next*1103515245+12345;
//    next=next*110351+12345;
    return (
            #if __SIZEOF_POINTER__ == 4
            long
            #endif
                long)(next/65535)%32768;
}

void ranGen::srand(int seed)
{
    next=seed;
}

int ranGen::rrand(int n)
{
    return 1+(int)(n*rand())/(RAND_MAX1+1);
}
