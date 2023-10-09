#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

const int MAX_INSTRUCTIONS = 100;

//Enumeration status for instructions
enum STATUS{INIT = 0, IF, ID, EX, WB, C, END};

// CPU structure to hold registers
struct CPURG{
    unsigned int IR; //Register file
    unsigned int PC; //Program counter
    //These can be defined as two separate values or one: ALU
    unsigned int ALU; // ALU Arithmetic-logic unit
};

// Instruction register
struct InstructionRG{
    string sOpcode;
    string sSource;
    string sDestination;
    int iCurrentState;
};
#endif // STRUCTURES_H_INCLUDED
