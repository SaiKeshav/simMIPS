/*
 * Assembler.h
 *
 *  Created on: 09-Aug-2015
 *      Author: keshav
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

using namespace std;

class Assembler{
public :
	/**
	 * @param
	 * ifile - contains path to input file - must end with .asm
	 * dfile - contains path to dictionary file - must end with .dict
	 * ofile - contains path to output file - must end with .bin
	 */
	Assembler(string ifile,string dfile,string ofile);
private :
	//The set of instructions(excluding comments and with labels removed)
	vector<string> instructions;
	//The set of encoder objects derived from dictionary file
	vector<Encoder> dictionary;
	//All the labels in the code along with their line numbers
	map<string,int> labels;
	//Fills 'instructions' from input file
	void parseInput(string ifile);
	//Fills 'dicionary' from dictionary file
	void parseDictionary(string dfile);
	//Trims the string to remove any leading or trailing whitespaces
	void trim(string& str);
	//split the string 's' based on string 'delimiter' and returns the vector of splitted strings
	vector<string> split(string s,string delimiter);
	//Perform all encoding and output it to 'ofile'
	void encode(string ofile);
	//check if 'line' has a label, if so add it to 'dictionary'
	//and return the label free instruction
	string checkLabel(string line,int line_no);
};


#endif /* ASSEMBLER_H_ */
