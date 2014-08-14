#ifndef CCGE_DATAS_COMMONTABLEDAO_H_
#define CCGE_DATAS_COMMONTABLEDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 数据库数据
 */
class CommonTableDAO:public yhge::data::JSONSqliteDAO
{
public:
    
	CommonTableDAO();
    
	~CommonTableDAO();
    
    yhge::Json::Value loadData(const std::string& table,int aId);
    
    inline void setKey(const std::string& key)
    {
        m_key = key;
    }
    
    inline const std::string& getKey()
    {
        return m_key;
    }
    
protected:
    
    std::string m_key;
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_COMMONTABLEDAO_H_
