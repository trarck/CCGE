#include "BaseSqlDAO.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

BaseSqlDAO::BaseSqlDAO()
:m_table("")
,m_key("id")
{

}

BaseSqlDAO::~BaseSqlDAO()
{

}

bool BaseSqlDAO::init(yhge::data::CocosSqliteDriver* driver,const std::string& table)
{
    if (yhge::data::JSONSqliteDAO::init(driver)) {
        setTable(table);
        return true;
    }
    
    return false;
}

Json::Value BaseSqlDAO::loadData(int key)
{
    std::string loadSql="SELECT * FROM "+m_table+" WHERE "+m_key+" = ?";
    return load(loadSql,key);
}

yhge::Json::Value BaseSqlDAO::findAll(const std::string& column,int value)
{
    Json::Value param;
    param.append(value);
    
    std::string sql="SELECT * FROM "+m_table+" WHERE "+column+" = ?";
    return fetchAll(sql,param);
}

yhge::Json::Value BaseSqlDAO::findAll(const std::string& column,float value)
{
    Json::Value param;
    param.append(value);
    
    std::string sql="SELECT * FROM "+m_table+" WHERE "+column+" = ?";
    return fetchAll(sql,param);
}

yhge::Json::Value BaseSqlDAO::findAll(const std::string& column,const std::string& value)
{
    Json::Value param;
    param.append(value);
    
    std::string sql="SELECT * FROM "+m_table+" WHERE "+column+" = ?";
    return fetchAll(sql,param);
}

NS_CC_GE_END
