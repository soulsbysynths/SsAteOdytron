/* 
* AtePatch.h
*
* Created: 27/09/2016 16:21:12
* Author: paulsoulsby
*/


#ifndef __ATEPATCH_H__
#define __ATEPATCH_H__
#include <math.h>
#include <stdlib.h>
#include "AtePatchBase.h"
#include "SsHelpers.h"

#ifndef bitRead
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#endif
#ifndef bitSet
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#endif
#ifndef bitClear
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#endif
#ifndef bitWrite
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#endif

class AtePatch
{
//variables
public:
	static const unsigned char PATCH_SIZE = 60;
protected:
private:
	unsigned char funcCs_ = 4;
	unsigned char funcs_ = 8;
	unsigned char optCs_ = 1;
	unsigned char opts_ = 7;
	unsigned char ctrls_ = 5;
	unsigned char* funcValueC_;
	unsigned char* optValueC_;
	unsigned char* ctrlValue_;
	AtePatchBase* base_ = NULL;
//functions
public:
	AtePatch(AtePatchBase* base, unsigned char* initFuncC, unsigned char initFuncs, unsigned char* initOptC, unsigned char initOpts, unsigned char* initCtrl, unsigned char initCtrls);
	AtePatch() {}
	~AtePatch();
	void setFunctionValue(unsigned char func, unsigned char newValue);
	unsigned char getFunctionValue(unsigned char func);
	void setOptionValue(unsigned char func, bool newValue);
	bool getOptionValue(unsigned char func);
	void setCtrlValue(unsigned char ctrl, unsigned char newValue);
	unsigned char getCtrlValue(unsigned char ctrl);
	void readPatch(unsigned char patchNum);
	void writePatch(unsigned char patchNum);
	void easterEgg(unsigned int seed);
protected:
private:
	AtePatch( const AtePatch &c );
	AtePatch& operator=( const AtePatch &c );

}; //AtePatch

#endif //__ATEPATCH_H__
