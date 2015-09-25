/*
 * MainAssembler.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: keshav
 */
#include<fstream>
#include<iostream>
#include<vector>
#include<regex>
#include<map>

#include<Assembler/Encoder.h>
#include<Assembler/Assembler.h>
#include<NP_Processor/NPPGlobals.h>

using namespace std;

vector<string> binInstructions;

Assembler::Assembler(string ifile,string dfile,string ofile){
	parseInput(ifile);
	parseDictionary(dfile);
	encode(ofile);
}

/**
 * CONDITIONS ASSUMED :
 *
 * If entire line is comment, line must start with #
 * (or) comment must be at the end of the line and must begin with #
 *
 * TODO : Unnecessary assumption - must remove
 * The instruction ends with a ';'
 *
 */
void Assembler::parseInput(string inputFile){
  ifstream input;
  input.open(inputFile,ios::in);
  string instruction;
  int comment=0,endinst=0,lineno=0;
  while(getline(input,instruction)){
	  if(instruction=="") continue;//May occur at the end
	  comment=instruction.find('#');
	  if(comment==0)
		  continue; //Ignore the comment lines
	  else
		  instruction = instruction.substr(0,comment);
	  endinst=instruction.find(';');
	  instruction=instruction.substr(0,endinst);
	  instruction=checkLabel(instruction,++lineno);
	  instructions.push_back(instruction);
  }
  input.close();
}

/**
 * The dicionary file contains set of lines
 * each line representing how to encode a particular instruction
 *
 * Format of the line :
 * regex;binaryencoding
 *
 * It must contain the regular expression that matches the instruction
 * required and 'binaryencoding' is a string determining how to encode
 * the instruction
 *
 * For format of 'binaryencoding' refer to 'Encoder.h' - 'binaryformat'
 */
void Assembler::parseDictionary(string dictionaryFile){
	ifstream dict;
	dict.open(dictionaryFile);
	string line;
	vector<string> spline;
	while(getline(dict,line)){
		if(line=="") continue;//May occur at the end
		spline = Assembler::split(line,";");
		if(spline.size()<2)
			throw invalid_argument("The dictionary file does not contain appropriate info");
		else{
			trim(spline[0]);
			trim(spline[1]);
			regex r(spline[0]);
			string binFormat = spline[1];
			Encoder e(r,binFormat);
			dictionary.push_back(e);
		}
	}
	dict.close();
}

/**
 * Checks if a label is present in the instruction,
 * if so adds it to the 'label' map, along with it's line
 * number in the program, the line number is after ignoring comment lines
 *
 * CONDITIONS ASSUMED :
 * The general form of a label is -
 * LabelName : instruction
 *
 * @return instruction
 */
string Assembler::checkLabel(string line,int line_no){
	regex labelReg("^([a-zA-Z0-9]*) : ");
	smatch getLabelName;
	string label;
	if(!regex_search(line,getLabelName,labelReg))
		return line;
	else{
		label=getLabelName[1];
		labels[label] = line_no;
		vector<string> seperateLabel = Assembler::split(line,":");
		Assembler::trim(seperateLabel[1]);
		return seperateLabel[1];
	}
}

vector<string> Assembler::split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL){
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }
    return arr;
}

void Assembler::trim(string& str){
  string::size_type pos = str.find_last_not_of(' ');
  if(pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}

/**
 * Does the real encoding of the instructions
 */
void Assembler::encode(string outputFile){
	ofstream output(outputFile);
	string binInst;
	for(size_t i=0;i<instructions.size();i++){
		string inst = instructions[i];
		for(size_t j=0;j<dictionary.size();j++){
			Encoder e = dictionary[j];
			if(e.match(inst)){
				binInst=e.encode(inst,i,labels);
				output<<binInst<<endl;
				binInstructions.push_back(binInst);
			}
		}
	}
	output.close();
//	cout<<"Output succesfully written to "<< endl << outputFile;
}

//int main(int argc,char *argv[]){
//	if(argc != 4)
//		cout<<"Expected usage : "<<"<input-file-name> <dictionary-file-name> <output-file-name>";
//	string ifile = argv[1];
//	string dfile = argv[2];
//	string ofile = argv[3];
//	Assembler a(ifile,dfile,ofile);
//	Assembler a("/home/keshav/Desktop/simMIPS/Factorial.asm","/home/keshav/Desktop/simMIPS/pseudoMIPS.dict"
//			,"/home/keshav/Desktop/simMIPS/Factorial.bin");
//}
