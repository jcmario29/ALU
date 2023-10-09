#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED



class CPU{
    private:
        CPURG CPURegister; //struct CPU Register
        Decoder InstructionDecoder; //Decoder object
        InstructionList List; //Instruction list object
        ALU aluObj; // ALU object
        int iClockCounter;
    public:
        CPU(string sFileName);
        ~CPU();
        void Run(); // Starting point for CPU simulation
        void ProcessStatus(); //Prints Instruction status
};

// Constructor
CPU::CPU(string sFileName){
    iClockCounter = 0; // keep track of cycles
    InstructionDecoder.StartDecoder(sFileName, List);
}

//Destructor
CPU::~CPU(){


}

// Run the CPU object
void CPU::Run(){
    //Simulate Clock, set max clock cycles in constructor
    int iCurrentInstruction = 0;

    cout << "Starting CPU Simulator... \n\n";
    while( ! List.LastInstructionCycleComplete()){ //Loop through the list until complete
        cout << "\nClock Counter: " << iClockCounter << endl;
        for(int i=0; i<=iCurrentInstruction; i++){
            List.SetStatus(i);
        }
        ProcessStatus();
        iClockCounter++;
        //Sleep(1500); //Sleep 1.5 second
        cin.ignore();
        iCurrentInstruction++;
    }
    cout << "\n\nInstruction cycle complete." << endl;
    cout << "\n\nThe following instructions were skipped when a jmp command was found:"<<endl;
    List.PrintPurgedList();
}

// Eventually this function will call the associated method to each status
void CPU::ProcessStatus(){
    double dResult;
    for(int i=0; i<List.GetCount(); i++){
        cout << "Instruction : " << i+1 << " Status: ";

        switch(List.GetStatus(i)){
            case IF: cout << "Instruction Fetch" << endl; break;
            case ID: cout << "Instruction Decode: " << endl;
                List.PrintInstruction(i); break;
            case EX: cout << "ALU Execute: ";
                List.QuickPrint(i);
                dResult = aluObj.Execute(List.GetOpCode(i), List.GetSource(i), List.GetDest(i));
                if(!aluObj.GetError()){ //Returns 0 if everything OK
                    cout << dResult << endl;
                }
                else{
                    cout << "ERROR." <<endl;
                }
                break;
            case WB: cout << "Write Back" << endl; break;
            case C: cout << "Commit" << endl; break;
            default: cout << "" << endl;
        }
    }
}


#endif // CPU_H_INCLUDED
