/*

 * MainProcessor.cpp
 *
 *  Created on: 03-Sep-2015
 *      Author: keshav
 */

#include<Assembler/Assembler.h>
#include<NP_Processor/NPPGlobals.h>
#include<NP_Processor/InstructionFetch.h>
#include<NP_Processor/InstructionDecode.h>
#include<NP_Processor/Execute.h>
#include<NP_Processor/WriteBack.h>
#include<NP_Processor/MainProcessor.h>
#include<iostream>
#include<map>

using namespace std;

/**
 * NOTE : NP_Processor is a non-pipelined simulation of the MIPS Processor
 *
 * This is the main class
 */

/*
 * TODO :
 * 1.Write comments
 * 2.Display some log info..
 */

//Register name and value in the register
map<string,int> Registers;
//Memory line number(starts from 0) and value at that line
map<int,int> Memory;

int main(int argc,char *argv[]){
	if(argc != 5)
		cout<<"Expected usage : "<<"<input-file-name> <dictionary-file-name> <output-file-name> <memory-file-name>";
	string ifile = argv[1];
	string dfile = argv[2];
	string ofile = argv[3];
	string mfile = argv[4];

	Assembler a(ifile,dfile,ofile);
//	Assembler a("/home/keshav/Desktop/COA Lab/simMIPS/Factorial.asm","/home/keshav/Desktop/COA Lab/simMIPS/pseudoMIPS.dict"
//				,"/home/keshav/Desktop/COA Lab/simMIPS/Factorial.bin");

	//Log
	cout<<"Taking input assembly code from "+ifile<<endl;
	cout<<"Making binary according dictionary in "+dfile<<endl;
	cout<<"Taking memory from "+mfile<<endl;
	cout<<"Wrtiting the binary code to "+ofile<<endl;

	initializeRegisters();
	initializeMemory(mfile);

	int CLOCK=0;
	while(!stopProgram()){
		fetchInstruction();
		decode();
		execute();
		writeback();
		CLOCK+=4;
	}

	writeBackMemory(mfile);

	cout<<endl<<"Number of clock cycles taken = "<<CLOCK<<endl;

}

//Copy memory file to array
void initializeMemory(string memFileName){
	//Log
	cout<<"Setting up the memory..."<<endl<<endl;

	ifstream MemoryFile;
	string memline;
	MemoryFile.open(memFileName,ios::in);
	int i=0;
	while(getline(MemoryFile,memline)){
		Memory[i]=stoi(memline);
	}
	MemoryFile.close();
}

//Re-convert memory array back into file
void writeBackMemory(string memFileName){
	//Log
	cout<<endl<<"Writing back the memory...";

	ofstream MemoryFile;
	MemoryFile.open(memFileName,ios::out);
	int maxlineno=-1;
	for(auto const ent : Memory){
		if(maxlineno<ent.first)
			maxlineno=ent.first;
	}


	for(int i=0;i<=maxlineno;i++){
		for(auto const ent : Memory){
			if(ent.first!=i)
				continue;
			MemoryFile<<ent.second;
		}
	}
	MemoryFile.close();
}

void initializeRegisters(){
	//Log
	cout<<endl<<"Initializing the registers..."<<endl;

	Registers["0000"]=0;
	Registers["0001"]=0;
	Registers["0010"]=0;
	Registers["0011"]=0;
	Registers["0100"]=0;
	Registers["0101"]=0;
	Registers["0110"]=0;
	Registers["0111"]=0;
	Registers["1000"]=0;
	Registers["1001"]=0;
	Registers["1010"]=0;
	Registers["1011"]=0;
	Registers["1100"]=0;
	Registers["1101"]=0;
	Registers["1110"]=0;
	Registers["1111"]=0;
}


