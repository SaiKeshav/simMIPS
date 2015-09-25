/*
 * NPPGlobals.h
 *
 *  Created on: 04-Sep-2015
 *      Author: keshav
 */

#include<vector>
#include<string>
#include<map>
#include<fstream>

using namespace std;

#ifndef NPPGLOBALS_H_
#define NPPGLOBALS_H_

extern vector<string> binInstructions;
extern string instruction;

extern bool load;

//ALU Inputs and Outputs
extern int input1;
extern int input2;
extern int output;

//ALU Controls
extern bool addALU;
extern bool mulALU;
extern bool andALU;
extern bool orALU;

//WriteBack Controls
extern bool MEMREG;//True - store in memory, False- store in register
extern int inputWB;
extern int addressWB;
extern bool BRANCH;//Nothing to write back in this case

//Register File
extern map<string,int> Registers;
//Memory
extern map<int,int> Memory;

#endif /* NPPGLOBALS_H_ */
