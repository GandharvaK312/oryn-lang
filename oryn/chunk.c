#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk){
    chunk->count = 0;
    chunk->capacity = 0; // empty array
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk){
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line){
    if(chunk->capacity < chunk->count + 1){  
        // arrays are zero indexed, capacity is being checked with count + 1. This is because we are currently in index count, capacity should be minimum count + 1.
        // so the accepted size is capacity >= count + 1. so if capcity < count + 1, then error. you cannot write in index 4 with total size 4. so if(4 < 4 + 1) trigger
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value){  //does not "add", it only inserts the element into the chunk
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}