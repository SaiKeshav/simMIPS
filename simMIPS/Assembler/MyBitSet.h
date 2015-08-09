/*
 * MyBitSet.h
 *
 *  Created on: 08-Aug-2015
 *      Author: keshav
 */

#include<bitset>

using namespace std;

/**
 * Modified version of Bitset includes the additional feature
 * of storing the length of bitset
 * and displaying only those many digits when to_string is called
 *
 * NOTE : the maximum length is only 64.
 * Will be sufficient for majority cases
 */
class MyBitSet{
	//TODO : Instead of 64, make it the maxm length required by the user
	bitset<64> b;
	int size;
public :
	MyBitSet(int i,int length);
	/**
	 * string limited to 'length' bits
	 */
	string to_string();
};



