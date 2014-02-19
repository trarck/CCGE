#ifndef CCGE_DATAS_DATAFACTORY_H_
#define CCGE_DATAS_DATAFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "AnimationData.h"

NS_CC_GE_BEGIN

/**
 * 数据工场
 */
class DataFactory:public CCObject
{
public:
    
	DataFactory();
    
	~DataFactory();

    bool init();

    static DataFactory* getInstance();
    
    void setup();

    AnimationData* getAnimationData()
    {
        return m_animationData;
    }
    
protected:

    /**
     *@brief 取得数据的路径 
     *@param file 文件名。
     *@return 返回完整的配置文件路径。将来支持多语言。
     */
    std::string getDataFilePath(const std::string& file);

protected:
    //动画数据
    AnimationData* m_animationData;
};

NS_CC_GE_END
#endif //CCGE_DATAS_DATAFACTORY_H_
