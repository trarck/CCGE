#include "CommonTableDAO.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

CommonTableDAO::CommonTableDAO()
:m_key("id")
{
    
}

CommonTableDAO::~CommonTableDAO()
{

}

Json::Value CommonTableDAO::loadData(const std::string& table,int key)
{
    std::string loadSql="SELECT * FROM "+table+" WHERE "+m_key+" = ?";
    return load(loadSql,key);
}

NS_CC_GE_END
