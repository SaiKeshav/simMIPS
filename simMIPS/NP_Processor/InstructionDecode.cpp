/*
 * InstructionDecode.cpp
 *
 *  Created on: 04-Sep-2015
 *      Author: keshav
 */
#include<string>
#include<NP_Processor/NPPGlobals.h>
#include<NP_Processor/InstructionDecode.h>
#include<NP_Processor/InstructionFetch.h>
#include<iostream>

using namespace std;

bool load;
bool BRANCH;

string opcode;
string source1;
string source2;
string dest;
string offset;
string imm;

void decode(){
	addALU=false;
	mulALU=false;
	andALU=false;
	orALU=false;
	load=false;
	BRANCH=false;
	MEMREG=false;
	input1=-999;
	input2=-999;
	opcode=instruction.substr(0,4);
	setValues();
}

void setValues(){
	if(opcode=="0000"){
		//Reserved
	}
	else if(opcode=="0001"){
//		add=true;
		source1=instruction.substr(4,4);
		source2=instruction.substr(8,4);
		dest=instruction.substr(12,4);

		input1=Registers[source1];
		input2=Registers[source2];
		addALU=true;

		MEMREG=false;
		addressWB=stoi(dest,nullptr,2);
	}
	else if(opcode=="0010"){
//		addi=true;
		source1=instruction.substr(4,4);
		imm=instruction.substr(8,4);
		dest=instruction.substr(12,4);

		input1=Registers[source1];
		input2=stoi(imm,nullptr,2);
		addALU=true;

		MEMREG=false;
		addressWB=stoi(dest,nullptr,2);
	}
	else if(opcode=="0011"){
//		mul=true;
		source1=instruction.substr(4,4);
		source2=instruction.substr(8,4);
		dest=instruction.substr(12,4);

		input1=Registers[source1];
		input2=Registers[source2];
		mulALU=true;

		MEMREG=false;
		addressWB=stoi(dest,nullptr,2);
	}
	else if(opcode=="0100"){
//		muli=true;
		source1=instruction.substr(4,4);
		imm=instruction.substr(8,4);
		dest=instruction.substr(12,4);

		input1=Registers[source1];
		input2=stoi(imm,nullptr,2);
		mulALU=true;

		MEMREG=false;
		addressWB=stoi(dest,nullptr,2);
	}
	else if(opcode=="0101"){
//		bgt=true;
		BRANCH=true;
		source1=instruction.substr(4,4);
		source2=instruction.substr(8,4);
		offset=instruction.substr(12,4);

		if(Registers[source1]>Registers[source2]){
			branchPC(stoi(offset,nullptr,2));
		}
	}
	else if(opcode=="0110"){
//		blt=true;
		BRANCH=true;
		source1=instruction.substr(4,4);
		source2=instruction.substr(8,4);
		offset=instruction.substr(12,4);

		if(Registers[source1]<Registers[source2]){
			branchPC(stoi(offset,nullptr,2));
		}

	}
	else if(opcode=="0111"){
//		beq=true;
		BRANCH=true;
		source1=instruction.substr(4,4);
		source2=instruction.substr(8,4);
		offset=instruction.substr(12,4);

		if(Registers[source1]==Registers[source2]){
					branchPC(stoi(offset,nullptr,2));
		}
	}
	else if(opcode=="1000"){
//		jump=true;
		BRANCH=true;
		offset=instruction.substr(4,12);

		jmpPC(stoi(offset,nullptr,2));
	}
	else if(opcode=="1001"){
		load=true;
		source1=instruction.substr(4,4);
		offset=instruction.substr(8,4);
		dest=instruction.substr(12,4);

		input1=Registers[source1];
		input2=stoi(offset,nullptr,2);
		addALU=true;

		MEMREG=true;
		addressWB=stoi(dest,nullptr,2);
	}
	else if(opcode=="1010"){
//		store=true;
		dest=instruction.substr(4,4);
		offset=instruction.substr(8,4);
		source1=instruction.substr(12,4);

		input1=Registers[dest];
		input2=stoi(offset,nullptr,2);
		addALU=true;

		MEMREG=true;
		addressWB=stoi(source1,nullptr,2);
	}
	else if(opcode=="1011"){
//		aand=true;
		source1=instruction.substr(4,4);
		source2=instruction.substr(8,4);
		dest=instruction.substr(12,4);

		input1=Registers[source1];
		input2=Registers[source2];
		andALU=true;

		MEMREG=false;
		addressWB=stoi(dest,nullptr,2);
	}
	else if(opcode=="1100"){
//		oor=true;
		source1=instruction.substr(4,4);
		source2=instruction.substr(8,4);
		dest=instruction.substr(12,4);

		input1=Registers[source1];
		input2=Registers[source2];
		orALU=true;

		MEMREG=false;
		addressWB=stoi(dest,nullptr,2);
	}
	else if(opcode=="1101"){
		//Reserved
	}
	else if(opcode=="1110"){
		//Reserved
	}
	else if(opcode=="0100"){
		//Reserved
	}
	else
		throw invalid_argument("The opcode "+opcode+" is invalid");

	//Log
	cout<<"Processing opcode : "<<opcode<<endl;
}


