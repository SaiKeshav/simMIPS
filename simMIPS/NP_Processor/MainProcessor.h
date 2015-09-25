/*
 * MainProcessor.h
 *
 *  Created on: 03-Sep-2015
 *      Author: keshav
 */

#ifndef MAINPROCESSOR_H_
#define MAINPROCESSOR_H_

extern int CLOCK;
void initializeRegisters();
void initializeMemory(string Memory_File_Name);
void writeBackMemory(string memFileName);

#endif /* MAINPROCESSOR_H_ */
