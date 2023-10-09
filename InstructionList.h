#ifndef INSTRUCTIONLIST_H_INCLUDED
#define INSTRUCTIONLIST_H_INCLUDED

class InstructionList{
    private:
        // Instruction register array. Set max size in Structures.h
        InstructionRG InstRegister[MAX_INSTRUCTIONS];
        // Keep track of the instructions that were skipped when a jmp command is found
        InstructionRG InstSkipped[MAX_INSTRUCTIONS];
        int iTop; //Stores the last+1 instruction position
        int iTopSkipped; //Stores the last+1 instruction position of the skipped list
    public:
        InstructionList();
        ~InstructionList();
        void Insert(InstructionRG newRegister);
        void SetStatus(int iPosition);
        int GetStatus(int iPosition);
        int GetCount();
        bool LastInstructionCycleComplete();
        void PrintInstruction(int iPosition);
        void QuickPrint(int iPosition);
        void PurgeList();
        void PrintPurgedList();
        void DeleteRegister(int iPos);
        string StripFirstChar(string str);
        string GetOpCode(int iPos);
        string GetSource(int iPos);
        string GetDest(int iPos);
};

//Constructor
InstructionList::InstructionList(){
    iTop = 0;
    iTopSkipped = 0;
}

//Destructor
InstructionList::~InstructionList(){
}

//Inserts a new instruction in the array
void InstructionList::Insert(InstructionRG newRegister){
    if (iTop < MAX_INSTRUCTIONS){ //validate there's space for one more instruction
        InstRegister[iTop] = newRegister;
        iTop++;
    }
}

// Sets the next status, validates valid status
void InstructionList::SetStatus(int iPosition){
    if (iPosition < iTop){ //Validate position
        if (InstRegister[iPosition].iCurrentState != END){ //Validate is not the last status
            InstRegister[iPosition].iCurrentState++; //Move to the next state
        }
    }
}

// Gets the current status of the requested instruction
int InstructionList::GetStatus(int iPosition){
    return InstRegister[iPosition].iCurrentState;
}

// gets the instruction count
int InstructionList::GetCount(){
    return iTop;
}

// returns true if the last instruction is complete: Status=END
bool InstructionList::LastInstructionCycleComplete(){
    if (InstRegister[iTop-1].iCurrentState == END){
        return true;
    }
    else{
        return false;
    }
}

// Prints opcode, source and destination for each instruction
void InstructionList::PrintInstruction(int iPosition){
    cout << "Opcode = " << InstRegister[iPosition].sOpcode << " ";
    cout << "Source = " << InstRegister[iPosition].sSource << " ";
    cout << "Destination = " << InstRegister[iPosition].sDestination << endl;
}

// Prints a quick instruction format
void InstructionList::QuickPrint(int iPosition){
    cout << InstRegister[iPosition].sOpcode << " " << InstRegister[iPosition].sSource << " " << InstRegister[iPosition].sDestination << " = ";
}

// Strips first $ from source and destination
string InstructionList::StripFirstChar(string str){
    string sRes;
    if(str[0] == '$'){
        for(unsigned int i=1; i<str.length(); i++){
            sRes += str[i];
        }
    }
    else{
        sRes = "0"; //It didn't start with $, so ignore and return 0
    }
    return sRes;
}

// Deletes a register in main list. Moves all registers so we dont have empty spaces
void InstructionList::DeleteRegister(int iPos){
    int i = iPos;
    while(i < iTop){
        InstRegister[i] = InstRegister[i+1];
        i++;
    }
    iTop--;
}

// Purges the main list. Moves all skipped instructions to the purge list if a jmp command is found
void InstructionList::PurgeList(){
    int i = 0;
    string sLabel = "";
    bool bFoundJMP = false;
    while(i < iTop){
        if(InstRegister[i].sOpcode == "jmp"){ // found jmp command
            sLabel = InstRegister[i].sSource;
            bFoundJMP = true;
            i++;
        }
        else if(InstRegister[i].sOpcode == sLabel){ // Found the label we are looking for?
                bFoundJMP = false; // Set found to false, so skipping  is done
                i++;
        }
        else if(bFoundJMP){
            InstSkipped[iTopSkipped] = InstRegister[i]; // Move instruction to skipped
            DeleteRegister(i); // Delete register from main list
            iTopSkipped++; // Increase iTopSkipped
        }
        else{
            i++; // for all other cases
        }
    }
}

// Prints the purged list.
void InstructionList::PrintPurgedList(){
    int i = 0;
    while(i < iTopSkipped){
        cout << InstSkipped[i].sOpcode << " " << InstSkipped[i].sSource << " " << InstSkipped[i].sDestination << endl;
        i++;
    }
}

string InstructionList::GetOpCode(int iPos){
    return InstRegister[iPos].sOpcode;
}

string InstructionList::GetSource(int iPos){
    return StripFirstChar(InstRegister[iPos].sSource);
}

string InstructionList::GetDest(int iPos){
    return StripFirstChar(InstRegister[iPos].sDestination);
}

#endif // INSTRUCTIONLIST_H_INCLUDED
