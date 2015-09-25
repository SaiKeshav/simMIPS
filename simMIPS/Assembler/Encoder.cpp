/*
 * CRegex.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: keshav
 */
#include<regex>
#include<stdexcept>
#include<iostream>
#include<string>

#include<Assembler/Encoder.h>
#include<Assembler/MyBitSet.h>

using namespace std;


Encoder::Encoder(regex r,string s){
	binaryFormat=s;
	regularExp=r;
}

/**
 * true iff 'instruction' matches the 'regularExp'
 */
bool Encoder::match(string instruction){
	return regex_match(instruction,regularExp);
}

/**
 * Valid only if the match function returns true
 */
string Encoder::encode(string instruction,int lineNo,map<string,int> labels){
	//smatch is required when regex_match takes a string variable to match with the regex
	//cmatch is required when regex_match takes a string literal to match with the regex
	smatch captureGroups;
	string encoded=binaryFormat;

	if(!regex_match(instruction,captureGroups,regularExp))
		throw invalid_argument("The instruction "+instruction+" does not match the associated regex ");
	else{
		//The 0th group is the entire string itself
		for(size_t i=1;i<captureGroups.size();i++){
			smatch bitSizeMatch;
			string rep; //string to replace the ith group

			//Find the length of this group
			//G1=4 means the max length of the groups is 4
			string r="G"+to_string(i)+"=([[:digit:]])";
			regex groupLength(r);

			//If the group does not match the above format, then it must be a special encoding
			if(!regex_search(encoded,bitSizeMatch,groupLength)){
				//Special encoding
				regex specialRegex("G"+to_string(i)+"=sp([[:digit:]])");
				smatch spNumber;

				//If the syntax is wrong
				if(!regex_search(encoded,spNumber,specialRegex))
					throw invalid_argument(instruction+" does not match with any predifined instruction");

				//Get the special number to which instruction belongs
				//and execute the respective function
				int spNo = stoi(spNumber[1]);
				if(spNo==1)
					rep = sp1_Encode(lineNo,labels,captureGroups[i]);
				else if(spNo==2)
					rep = sp2_Encode(labels,captureGroups[i]);
				//Any further special encoding schemes required must be added here

				encoded = regex_replace(encoded,specialRegex,rep);
			}else{
				//Default encoding
				int lengthG=stoi(bitSizeMatch[1]);
				MyBitSet b(stoi(captureGroups[i]),lengthG);
				rep = b.to_string();
				encoded = regex_replace(encoded,groupLength,rep);
			}
		}
	}
	return encoded;
}

/**
 * For beq,bgt,blt statements which are PC-Relative
 */
string Encoder::sp1_Encode(int lineNo,map<string,int> labels,string label){
	int labelNo=0;
	labelNo=labels[label];
	int relativeDistance=labelNo-(lineNo+1);//The lineNo is 0 indexed
	//if 'relativeDistance'<0, bitset uses 2's complement form, as required
	MyBitSet branch(relativeDistance,4);
	return branch.to_string();
}

/**
 * For jump instructions which are absolute addressed
 */
string Encoder::sp2_Encode(map<string,int> labels,string label){
	int labelNo=labels[label];
	MyBitSet jmp(labelNo,12);
	return jmp.to_string();
}


