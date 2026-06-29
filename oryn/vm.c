#include <stdio.h>
#include "common.h"
#include "vm.h"
#include "debug.h"

VM vm;

void initVM(){

}

void freeVM(){

}

static InterpretResult run(){
    #define READ_BYTE() (*vm.ip ++) // it has read and increased ip already
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()]) // so here ip will point to the next ele
    // readbyte currently has values of where the ip is pointing to currently and then increments it to the next
    // and this run() runs continuously in loops until it checks through all the bytecode. so every instruction
    // is read by the read_byte

    for(;;){
        #ifdef DEBUG_TRACE_EXECUTION
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk -> code));
        #endif

        uint8_t instruction;
        switch(instruction = READ_BYTE()){  // decodes the instruction in the line and from the opcode, get the info
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            
            case OP_RETURN: { // every single opcode instrution has to be implemented
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk;
    vm.ip = chunk->code; //ip = instruction pointer or PC = program counter 
    return run();
}