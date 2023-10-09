CPU Simulator

CPU class:
Added the main registers in CPURegister struct. Only definition for now.
Added Instruction decoder object
Added Instruction list object
Simulates the clock cycle performing pipeline for every instruction.
pipeline status changes in every cycle. For now, it just displays a message
of the current status for each instruction.

Decoder:
Reads an assembly file and stores each instruction in the instruction list.

InstructionList:
New class added to handle the instructions to be executed.
Instructions read by the decoder are inserted in the list.
Changes the status pipeline for the given instruction.

Structures:
New header containing the structs that the program will use:
CPU Register and Instruction Register.
Also defines the enumeration STATUS and the maximum number of instructions.

***** Update ************************************************

New class ALU which will handle arithmetic and logic operations.

Changes in code:
- Struct CPURG now has one unsigned int ALU.
- Added get functions to InstructionList Class
- Added ALU object to CPU class
- Added ALU Class which executes the command read
- These operations are implemented:
	add, substract, multiply, xor, and, or
- It doesn't check if source or destination is IR. It only
	deals with constants e.g. $1, $0, etc

***** Update ************************************************

Add jmp command functionality to the program.
jmp is an unconditional jump to a certain label.
All instructions between jmp command and label will be skipped

Changes in code:
- Added validations to store properly the jmp command and a label command
	in function Decoder::StartDecoder
- Added a skipped instructions list in InstructionList Class to keep track
	of the skipped instructions when a jmp command is found
- Added an int to save the last position on the skipped array list
- Added PurgeList method to InstructionList Class. This method will move
	the skipped instructions to a separate list.
- Added PrintPurgedList method to InstructionList Class to print all
	instructions that were skippend when a jmp command was found
- Call the purgeList method in Decoder::StartDecoder
- Print the purgelist when cycle ends. Added call to CPU::Run method
