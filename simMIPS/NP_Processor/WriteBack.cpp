/*
 * WriteBack.cpp
 *
 *  Created on: 10-Sep-2015
 *      Author: keshav
 */

#include<NP_Processor/NPPGlobals.h>
#include<NP_Processor/WriteBack.h>
#include<bitset>
#include<iostream>

bool MEMREG;//True - store in memory, False- store in register
int inputWB;
int addressWB;

void writeback(){
	string address=bitset<4>(addressWB).to_string();
	string input=bitset<4>(inputWB).to_string();
	if(MEMREG){
		if(load){
			Registers[address]=Memory[inputWB];
			cout<<"Writing back result into register from memory"<<endl;
		}else{
			Memory[inputWB]=Registers[address];
			cout<<"Writing back result into memory from register"<<endl;
		}
	}else if(!BRANCH){
		Registers[address]=inputWB;
		cout<<"Writing back result into register having address"<<address<<endl;
	}else{
		cout<<"Nothing to write back"<<endl;
	}
}


