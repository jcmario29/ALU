#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

/*
Get assembly file: gcc –O –S main.cpp
*/

#include "Structures.h"
#include "InstructionList.h"
#include "Decoder.h"
#include "ALU.h"
#include "CPU.h"

int main()
{
    CPU CPUObject("assembly.txt");
    CPUObject.Run();
    return 0;
}
