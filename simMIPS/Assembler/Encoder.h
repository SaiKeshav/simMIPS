/*
 * Encoder.h
 *
 *  Created on: 08-Aug-2015
 *      Author: keshav
 */

#include<regex>
#include<map>

using namespace std;

/**
 * This object is used to encode an assembly instruction
 * It requires two inputs :
 * 1.The regex of the instruction it matches
 * 2.A string which determines how the instruction is to be encoded 'binaryFormat'
 *
 * The 'binaryFormat' is expected to be in the form
 * xxxGi=N1Gj=N2xxx
 *
 * 'x' represents either 0 or 1
 *
 * Then the ith group of the regex replaces Gi=N1 where N1 is
 * the number of bits the ith group must be encoded in.
 * Expected : ith group is a number(eg register no) which is converted
 * to binary and made to fit N1 digits
 *
 * If different encoding of the ith group is desired(eg : jmp,beq,bgt,blt)
 * then use Gi=spk where 'k' is a number such that spk_Encode(parameters)
 * contains the desired encoding and the corresponding condition
 * is added to @see Encoder::encode
 */
class Encoder{
	string binaryFormat; //How the instruction is to be encoded
	regex regularExp; //The instruction this object matches to
	//Special Encoding Scheme 1 for bgt,blt,beq
	string sp1_Encode(int lineNo,map<string,int> labels,string label);
	//Special Encoding Scheme 2 for jump
	string sp2_Encode(map<string,int> labels,string label);
public :
	Encoder(regex r,string s);
	bool match(string instr);
	string encode(string instr,int lineNo,map<string,int> labels);
};



