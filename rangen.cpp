#include "rangen.h"

ranGen::ranGen()
{
}

long ranGen::rand()
{
    return (mt()%6);
}

void ranGen::srand(int seed)
{
    mt.seed(seed);
}
