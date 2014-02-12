#ifndef CCGE_CONTROLLERS_TESTSQLITECONTROLLER_H_
#define CCGE_CONTROLLERS_TESTSQLITECONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 战斗直接使用直角坐标系
 * 显示可以使用斜视角
 */
class TestSqliteController:public yhmvc::LayerController
{
public:
	
    TestSqliteController(void);
    
	~TestSqliteController(void);

	void layerDidLoad();
    
private:
    
    void createTable();
    
    void insertData(std::string key,std::string value,int inte,float fl);
    
    void showTable();
   
private:
    
    yhge::sqlite::SqliteDB* m_sqliteDB;
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_TESTSQLITECONTROLLER_H_
