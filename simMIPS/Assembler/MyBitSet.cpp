/*
 * MyBitSet.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: keshav
 */

#include<bitset>
#include<Assembler/MyBitSet.h>

using namespace std;


MyBitSet::MyBitSet(int i,const int length){
	//TODO : Dont know how to use 'b' directly to do this
	bitset<64> c(i);
	b=c;
	size=length;
}

string MyBitSet::to_string(){
	string reqBin = b.to_string();
	reqBin = reqBin.substr(b.size()-size,b.size()+1);
	return reqBin;
}




