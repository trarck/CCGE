#ifndef CCGE_DATAS_ANIMATIONDATA_H_
#define CCGE_DATAS_ANIMATIONDATA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/Jsoncpp/json.h>

NS_CC_GE_BEGIN

class AnimationData:public CCObject
{
public:
    
	AnimationData();
    
	~AnimationData();
    
    
    yhge::Json::Value getEntityAnimateData(int entityId);
    
protected:
    
    
    
private:
    
    

};

NS_CC_GE_END



#endif //CCGE_DATAS_ANIMATIONDATA_H_
