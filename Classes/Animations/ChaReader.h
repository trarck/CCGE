#ifndef CCGE_ANIMATIONS_CHAREADER_H_
#define CCGE_ANIMATIONS_CHAREADER_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include "FcaInfo.h"

NS_CC_GE_BEGIN

extern void readCha(FcaInfo* fcaInfo,unsigned char* data,size_t size);

NS_CC_GE_END

#endif //CCGE_ANIMATIONS_FCAINFO_H_
