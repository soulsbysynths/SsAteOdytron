/*
* AtePatch.cpp
*
* Created: 27/09/2016 16:21:12
* Author: paulsoulsby
*/


#include "AtePatch.h"
extern void writeMemory(const void* data, void* startAddr, size_t size);
extern void readMemory(void* data, const void* startAddr, size_t size);
// default constructor
AtePatch::AtePatch(AtePatchBase* base, unsigned char* initFuncC, unsigned char initFuncs, unsigned char* initOptC, unsigned char initOpts, unsigned char* initCtrl, unsigned char initCtrls)
{
	if(base!=NULL)
	{
		base_ = base;
	}

	funcs_ = initFuncs;
	funcCs_ = (funcs_ + 1) / 2;
	unsigned char *funcValueC_ = new unsigned char [funcCs_];
	for(unsigned char i=0;i<funcCs_;++i)
	{
		funcValueC_[i] = initFuncC[i];
	}

	opts_ = initOpts;
	optCs_ = (opts_ + 7) / 8;
	unsigned char *optValueC_ = new unsigned char [optCs_];
	for(unsigned char i=0;i<optCs_;++i)
	{
		optValueC_[i] = initOptC[i];
	}

	ctrls_ = initCtrls;
	for(unsigned char i=0;i<ctrls_;++i)
	{
		ctrlValue_[i] = initCtrl[i];
	}

} //AtePatch

// default destructor
AtePatch::~AtePatch()
{
	if(base_!=NULL)
	{
		delete base_;
	}
	delete[] funcValueC_;
	delete[] optValueC_;
	delete[] ctrlValue_;
} //~AtePatch

void AtePatch::setFunctionValue(unsigned char func, unsigned char newValue)
{
	unsigned char i = func>>1;
	funcValueC_[i] = compressFourBit(funcValueC_[i],newValue,func%2);
	if(base_!=NULL)
	{
		base_->patchValueChanged(func,newValue);
	}
}

unsigned char AtePatch::getFunctionValue(unsigned char func)
{
	unsigned char i = func>>1;
	return uncompressFourBit(funcValueC_[i],func%2);
}
void AtePatch::setOptionValue(unsigned char func, bool newValue)
{
	bitWrite(optValueC_,func,newValue);
	if(base_!=NULL)
	{
		base_->patchOptionChanged(func,newValue);
	}
}
bool AtePatch::getOptionValue(unsigned char func)
{
	return (bool)bitRead(optValueC_,func);
}
void AtePatch::setCtrlValue(unsigned char ctrl, unsigned char newValue)
{
	ctrlValue_[ctrl] = newValue;
	if(base_!=NULL)
	{
		base_->patchCtrlChanged(ctrl,newValue);
	}
}
unsigned char AtePatch::getCtrlValue(unsigned char ctrl)
{
	return ctrlValue_[ctrl];
}
void AtePatch::writePatch(unsigned char patchNum)
{
	unsigned int startAddr = (unsigned int)PATCH_SIZE * patchNum;
	unsigned int addr = 0;
	unsigned char i;
	unsigned char data[PATCH_SIZE];
	for(i=0;i<funcCs_;++i)
	{
		data[addr] = funcValueC_[i];
		addr++;
	}
	for(i=0;i<ctrls_;++i)
	{
		data[addr] = ctrlValue_[i];
		addr++;
	}
	data[addr] = optValueC_;
	addr++;
	writeMemory((const void*)data, (void*)startAddr, sizeof(data));
}
void AtePatch::readPatch(unsigned char patchNum)
{
	unsigned int startAddr = (unsigned int)PATCH_SIZE * patchNum;
	unsigned int addr = 0;
	unsigned char i,j;
	unsigned char data[PATCH_SIZE];
	readMemory((void*)data,(const void*)startAddr, sizeof(data));
	for(i=0;i<funcCs_;++i)
	{
		setFunctionValue(i<<1,uncompressFourBit(data[addr],false));
		setFunctionValue((i<<1)+1,uncompressFourBit(data[addr],true));
		addr++;
	}
	for(i=0;i<ctrls_;++i)
	{
		setCtrlValue(i,data[addr]);
		addr++;
	}
	for(i=0;i<optCs_;++i)
	{	
		setOptionValue(i,(bool)bitRead(data[addr],i));
		addr++;
	}
	
}
void AtePatch::easterEgg(unsigned int seed)
{
	unsigned char i;
	srand(seed);
	for(i=0;i<(funcs_-1);++i)  //don't touch patch num
	{
		setFunctionValue(i,rand()>>11);
		setOptionValue(i,(bool)(rand()>>14));
	}
	for(i=0;i<ctrls_;++i)
	{
		setCtrlValue(i,rand()>>7);
	}
}