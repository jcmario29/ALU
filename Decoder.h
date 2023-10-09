#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED



class Decoder{
    private:
        string sFileName;
    public:
        Decoder();
        ~Decoder();
        void StartDecoder(string sFileName, InstructionList &List);
};

/*
    Constructor
*/
Decoder::Decoder(){

}

/*
    Destructor
*/
Decoder::~Decoder(){
    // Nothing to do here
}

/*
    Opens the file and reads line by line. They will be stored in the Instruction List object
*/
void Decoder::StartDecoder(string sFileName, InstructionList &List){
    this->sFileName = sFileName; //Stores the file name
    ifstream fInstructionsFile; //File variable for reading
    fInstructionsFile.open(sFileName.c_str(), ifstream::in); // Open file
    string sInstruction; // String variable to read each line
    string sDelimiter; //Stores data read from file
    InstructionRG newRegister;

    while (getline (fInstructionsFile, sInstruction)) { // Reads line by line
        istringstream ss(sInstruction);
        getline(ss, sDelimiter, ' ');
        newRegister.sOpcode = sDelimiter;
        getline(ss, sDelimiter, ' ');
        if( newRegister.sOpcode == sDelimiter){ // If a label is encountered, set source and destination to ""
            newRegister.sSource = "";
            newRegister.sDestination = "";
        }
        else{ // All other cases, store the source and destination fields
            newRegister.sSource = sDelimiter;
            if (newRegister.sOpcode == "jmp"){ // Validate jmp command to skip destination field
                newRegister.sDestination = "";
            }
            else{
                getline(ss, sDelimiter, ' ');
                newRegister.sDestination = sDelimiter;
            }
        }
        newRegister.iCurrentState = INIT;
        List.Insert(newRegister); //Insert new register into list
    }

    fInstructionsFile.close(); // Close the file
    List.PurgeList(); // Purges the main list, skipping the instructions between the jmp command and the label
}



#endif // DECODER_H_INCLUDED
