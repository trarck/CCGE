#ifndef CCGE_DATAS_SKILLDAO_H_
#define CCGE_DATAS_SKILLDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include "BaseSqlDAO.h"

NS_CC_GE_BEGIN

/**
 * 单位数据
 */
class SkillDAO:public BaseSqlDAO
{
public:
    
	SkillDAO();
    
	~SkillDAO();
    
    yhge::Json::Value getDataById(int aId);
    
    yhge::Json::Value getSkillActions(int skillId);
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_SKILLDAO_H_
