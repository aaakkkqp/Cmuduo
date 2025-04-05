#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

struct SmallNode{
    unsigned char * start;
    unsigned char * end;
    unsigned int cntQuote;
    unsigned int cntFail;
    struct SmallNode *next;
};

#endif