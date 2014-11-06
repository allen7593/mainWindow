#ifndef RANGEN_H
#define RANGEN_H

#define RAND_MAX1 100

class ranGen
{
public:
    ranGen();

    long rand(void);
    void srand(int);
    int rrand(int);
private:
#if __SIZEOF_POINTER__ == 4
    long
#endif
    long next;

};

#endif // RANGEN_H
