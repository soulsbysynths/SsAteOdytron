/*
 * AtePatchBase.h
 *
 * Created: 27/09/2016 16:21:25
 *  Author: paulsoulsby
 */ 


#ifndef ATEPATCHBASE_H_
#define ATEPATCHBASE_H_

class AtePatchBase
{
	public:
	virtual void patchValueChanged(unsigned char func, unsigned char newValue) = 0;
	virtual void patchOptionChanged(unsigned char func, bool newOpt) = 0;
	virtual void patchCtrlChanged(unsigned char ctrl, unsigned char newValue) = 0;
};



#endif /* ATEPATCHBASE_H_ */