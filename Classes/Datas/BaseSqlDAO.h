#ifndef CCGE_DATAS_BASESQLDAO_H_
#define CCGE_DATAS_BASESQLDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 数据库数据
 */
class BaseSqlDAO:public yhge::data::JSONSqliteDAO
{
public:
    
	BaseSqlDAO();
    
	~BaseSqlDAO();
    
    bool init(yhge::data::CocosSqliteDriver* driver,const std::string& table);
    
    yhge::Json::Value loadData(int aId);
    
    yhge::Json::Value findAll(const std::string& column,int value);
    yhge::Json::Value findAll(const std::string& column,float value);
    yhge::Json::Value findAll(const std::string& column,const std::string& value);
    
    inline yhge::Json::Value getDataById(int aId)
    {
        return loadData(aId);
    }
    
    inline void setTable(const std::string& table)
    {
        m_table = table;
    }
    
    inline const std::string& getTable()
    {
        return m_table;
    }
    
    inline void setKey(const std::string& key)
    {
        m_key = key;
    }
    
    inline const std::string& getKey()
    {
        return m_key;
    }
    
protected:
    
    std::string m_table;
    
    std::string m_key;
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_BASESQLDAO_H_
