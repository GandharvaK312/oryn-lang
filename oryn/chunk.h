#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum{
    
    OP_RETURN,  //used on a function to return its value

} OpCode;

typedef struct{

    int count, capacity;
    
    // a dynamic array used since we dont know how big the array is going to be, difference from a normal array is that it has capacity(total declared) and count(how much is in use).
    // so basically whenever the count seems to exceed the capacity, the capacity is doubled and a new array with double the capacity is allocated with existing elements
    uint8_t* code;

} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);







#endif