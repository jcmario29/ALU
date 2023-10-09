#ifndef ALU_H_INCLUDED
#define ALU_H_INCLUDED

//Define 6 different commands for ALU use
const string ALUCommands[] = {"add", "sub", "imul", "xor", "and", "or"};
const int MAXCMD = 6;

class ALU{
    private:
        double dResult; //Stores the result
        int iError; //In case we need to handle errors
        string sOpCode; //Store current command
        unsigned int uSource; //Store current source
        unsigned int uDest; //Store current destination

        void SetCMD(string sOPC, string sSource, string sDest);
        int setCommand();
        double Add();
        double Substract();
        double Multiply();
        double XOR();
        double AND();
        double OR();
    public:
        ALU();
        ~ALU();
        int GetError();
        double Execute(string sOPC, string sSource, string sDest);
};

//constructor
ALU::ALU(){
    dResult = 0.0;
    iError = 0;
}

//Destructor
ALU::~ALU(){
    //Nothing to do here...
}

// Sets Opcode, source and destination
void ALU::SetCMD(string sOPC, string sSource, string sDest){
    stringstream sConvert; // Used to convert string to int

    this->sOpCode = sOPC; //We expect opcode to be lower-case

    sConvert << sSource; //Store sSource in sConvert
    sConvert >> this->uSource; //Convert sSource to int
    sConvert.clear(); //clear stringstream so we can keep using it

    sConvert << sDest; //Store sDest in sConvert
    sConvert >> this->uDest; //Convert sDest to int
    sConvert.clear(); //clear stringstream so we can keep using it
}

// Returns the value of the Error. 0 everything is OK
int ALU::GetError(){
    return iError;
}

// Executes command: opcode source destination
double ALU::Execute(string sOPC, string sSource, string sDest){
    int iResponse;
    iError = 0; //Initialize in 0
    iResponse = setCommand(); //Checks if command is ALU available, -1 if command not found
    SetCMD(sOPC,sSource,sDest); //Set variables and convert them to integers

    switch(iResponse){
        case -1: iError = -1; dResult=0.0; break; //Check if setCommand sent error
        case 0: dResult = Add(); break;
        case 1: dResult = Substract();  break;
        case 2: dResult = Multiply();  break;
        case 3: dResult = XOR();  break;
        case 4: dResult = AND();  break;
        case 5: dResult = OR();  break;
        default: iError = -1; dResult = 0.0; break;
    }
    return dResult;
}

// Checks what command is used. -1 if error
int ALU::setCommand(){
    int i = 0;
    int iReturn = -1;
    //Loop through the command array until we find the command
    while(i<MAXCMD && iReturn == -1){
        if(this->sOpCode == ALUCommands[i]){
            iReturn = i;
        }
        else{
            i++;
        }
    }
    return iReturn;
}

double ALU::Add(){
    return uSource + uDest;
}
double ALU::Substract(){
    return uSource - uDest;
}
double ALU::Multiply(){
    return uSource * uDest;
}
double ALU::XOR(){
    return uSource ^ uDest;
}
double ALU::AND(){
    return uSource & uDest;
}
double ALU::OR(){
    return uSource | uDest;
}

#endif // ALU_H_INCLUDED
