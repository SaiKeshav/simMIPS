/*
 * InstructionFetch.h
 *
 *  Created on: 04-Sep-2015
 *      Author: keshav
 */

#ifndef INSTRUCTIONFETCH_H_
#define INSTRUCTIONFETCH_H_

void fetchInstruction();
void branchPC(int offset);
bool stopProgram();
void jmpPC(int absLineNo);

#endif /* INSTRUCTIONFETCH_H_ */
