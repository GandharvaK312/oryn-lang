#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]){

    initVM();

    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);  //the opcode OP_CONSTANT takes an operand to access and load
    writeChunk(&chunk, constant, 123); //this is linked to the opcode and holds the index of the constant in the array.
        //writeChunk can write opcodes and operands.
    writeChunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}