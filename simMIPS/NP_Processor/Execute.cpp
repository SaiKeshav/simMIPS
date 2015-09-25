/*
 * Execute.cpp
 *
 *  Created on: 10-Sep-2015
 *      Author: keshav
 */

#include<NP_Processor/NPPGlobals.h>
#include<NP_Processor/Execute.h>
#include<iostream>

int input1;
int input2;
int output;

bool addALU;
bool mulALU;
bool andALU;
bool orALU;


void execute(){
	//Log
	cout<<"Executing in ALU"<<endl;

	//In case of branch instructions no need for ALU
	if(input1==-999 && input2==-999)
		return;

	if(addALU){
		output=input1+input2;
	}else if(mulALU){
		output=input1*input2;
	}else if(andALU){
		output=input1&input2;
	}else if(orALU){
		output=input1|input2;
	}

	inputWB=output;
}


