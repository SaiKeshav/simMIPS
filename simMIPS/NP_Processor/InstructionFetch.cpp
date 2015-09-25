/*
 * InstructionFetch.cpp
 *
 *  Created on: 04-Sep-2015
 *      Author: keshav
 */
#include<NP_Processor/NPPGlobals.h>
#include<iostream>

int ProgramCounter=0;

string instruction;

/**
 * Fetches the current instruction pointed by program counter
 * and increments the PC
 */
void fetchInstruction(){
	//Log
	cout<<"Fetching instruction..."<<endl;

	instruction=binInstructions[ProgramCounter];
	ProgramCounter++;
}

/**
 * The offset(OFS) directly got from the instruction
 * 1 must be subtracted from OFS
 * as PC has already been incremented
 */
void branchPC(int offset){
	ProgramCounter+=offset-1;
}

void jmpPC(int absLineNo){
	ProgramCounter=absLineNo-1;//to make it 0 indexed
}

/**
 * Indicates if the program reached its end of execution
 *
 * Since this is non-pipelined simulation, this is sufficient
 * to indicate that the program has finished, as ,if there
 * were any intermediate branch instructions, in the execution
 * phase the PC would be change to that address
 */
bool stopProgram(){
	return ProgramCounter==binInstructions.size();
}


