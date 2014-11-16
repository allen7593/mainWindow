#ifndef RANGEN_H
#define RANGEN_H

#define RAND_MAX1 100

#include <random>

class ranGen
{
public:
    ranGen();

    long rand(void);
    void srand(int);
private:
    std::mt19937 mt;
};

#endif // RANGEN_H
