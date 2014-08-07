#ifndef CCGE_CONTROLLERS_TESTSQLITECONTROLLER_H_
#define CCGE_CONTROLLERS_TESTSQLITECONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include "CCGEMacros.h"
#include "BaseController.h"

NS_CC_GE_BEGIN

/**
 * 战斗直接使用直角坐标系
 * 显示可以使用斜视角
 */
class TestSqliteController:public BaseController
{
public:
	
    TestSqliteController(void);
    
	~TestSqliteController(void);

	void viewDidLoad();
    
    void onCreateTable(yhge::Event* event);
    
    void onInsertTable(yhge::Event* event);
    
    void onShowTable(yhge::Event* event);
    
    void update1(float delta);
    
    void update2(float delta);
    
    void update3(float delta);
    
    void update4(float delta);
    
private:
    
    void createTable();
    
    void insertData(std::string key,std::string value,int inte,float fl);
    
    void showTable();
   
private:
    
    yhge::sqlite::SqliteDriver* m_sqliteDriver;
    
    yhge::UpdateManager* m_um;
    
    int m_tt;
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_TESTSQLITECONTROLLER_H_
