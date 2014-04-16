#ifndef CCGE_DATAS_MODELFACTORY_H_
#define CCGE_DATAS_MODELFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * @brief 模型工场
 */
class ModelFactory:public CCObject
{
public:
    
	ModelFactory();
    
	~ModelFactory();

    bool init();

    static ModelFactory* getInstance();
    
    void setup();

protected:

protected:

};

NS_CC_GE_END
#endif //CCGE_DATAS_MODELFACTORY_H_
