#include "TestSqliteController.h"
#include <yhge/yhge.h>
#include <yhgui/yhgui.h>

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGUI;
USING_NS_CC_YHGE_SQLITE;

NS_CC_GE_BEGIN

static const float kGameTileWidth=100;
static const float kGameTileHeight=90;

TestSqliteController::TestSqliteController(void)
:m_sqliteDriver(NULL)
{
    m_sName="TestSqliteController";
}

TestSqliteController::~TestSqliteController(void)
{
    CCLOG("TestSqliteController destroy");
    m_sqliteDriver->close();
    CC_SAFE_DELETE(m_sqliteDriver);
}

void TestSqliteController::viewDidLoad()
{
    //in test sqlite
    CCSize visibleSize=getPreferredContentSize();
    
    ccColor3B pressColor=ccc3(255, 0, 0);
    
    //纯文字按钮
    
    //create
    NormalButton* button=new NormalButton();
    button->init();
    
    button->setLabel(CCLabelTTF::create("create", "Arial", 34));
    
    
    button->setStateLabelColor(NormalButton::kPressed, pressColor);
    
    button->addEventListener(kEventTouchUpInside, this, YH_EVENT_SELECTOR(TestSqliteController::onCreateTable));
    
    button->setPosition(ccp(visibleSize.width/2,100));
    
    m_view->addChild(button);
    button->release();
    
    //insert
    NormalButton* insertBtn=NormalButton::create("insert", "Arial", 34);
    
    insertBtn->setStateLabelColor(NormalButton::kPressed, pressColor);
    
    insertBtn->addEventListener(kEventTouchUpInside, this, YH_EVENT_SELECTOR(TestSqliteController::onInsertTable));
    
    insertBtn->setPosition(ccp(visibleSize.width/2,160));
    
    m_view->addChild(insertBtn);

    //show
    NormalButton* showBtn=NormalButton::create("show", "Arial", 34);
    
    showBtn->setStateLabelColor(NormalButton::kPressed, pressColor);
    
    showBtn->addEventListener(kEventTouchUpInside, this, YH_EVENT_SELECTOR(TestSqliteController::onShowTable));
    
    showBtn->setPosition(ccp(visibleSize.width/2,220));
    
    m_view->addChild(showBtn);
    

    m_sqliteDriver=new SqliteDriver();
    std::string dbPath=CCFileUtils::sharedFileUtils()->getWritablePath()+"test.db";
    
    m_sqliteDriver->connect(dbPath,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

    m_tt=0;
    
    m_um=new UpdateManager();
    m_um->init();
    
    m_um->addUpdater(this, schedule_selector(TestSqliteController::update1), 1);
    m_um->addUpdater(this, schedule_selector(TestSqliteController::update2), 2);
    m_um->addUpdater(this, schedule_selector(TestSqliteController::update3), 3);
    m_um->addUpdater(this, schedule_selector(TestSqliteController::update4), 4);
    
    m_um->update(1.0f);
    
    m_um->update(1.0f);
}


void TestSqliteController::createTable()
{
    std::string createSql="CREATE TABLE IF NOT EXISTS data(key TEXT PRIMARY KEY,value TEXT,inte INTEGER,fl REAL);";
    m_sqliteDriver->execute(createSql);
}

void TestSqliteController::insertData(std::string key,std::string value,int inte,float fl)
{
//    const char *insertSql = "INSERT into data(key,value,inte,fl) VALUES(?,?,?,?)";
//    Statement stmt(*m_sqliteDriver, insertSql);
//    stmt.bind(1, key);
//    stmt.bind(2, value);
//    stmt.bind(3, inte);
//    stmt.bind(4, fl);
//    stmt.execute();
//    
//    stmt.reset();
//    stmt.bind(1, "aa");
//    stmt.bind(2, "bb");
//    stmt.bind(3, 1);
//    stmt.bind(4, 2.0f);
//    stmt.execute();
    
    const char *insertSql = "INSERT into data(key,value,inte,fl) VALUES(?,:a,?,:b)";
    Statement stmt(*m_sqliteDriver, insertSql);
    stmt.bind(1, key);
    stmt.bind(":a", value);
    stmt.bind(3, inte);
    stmt.bind(":b", fl);
    stmt.execute();
}

void TestSqliteController::showTable()
{
    const char *selectSQl = "SELECT * FROM data;";
    Statement stmt(*m_sqliteDriver, selectSQl);
    
    int colCount=stmt.getColumnCount();
    
    while (stmt.executeStep()) {
        std::string out="";
        for (int i=0; i<colCount; i++) {
            Column col=stmt.getColumn(i);
            out+=CCString::createWithFormat("%s[%d]=%s,",col.getName(),col.getType(),col.getText())->getCString();
        }
        CCLOG("%s",out.c_str());
    }
}

void TestSqliteController::onCreateTable(yhge::Event* event)
{
    CCLOG("####create table#####");
    
    createTable();
}

void TestSqliteController::onInsertTable(yhge::Event* event)
{
    CCLOG("####insert table#####");
    insertData("test1","testa",1,1.1);
//    insertData("test2","testb",2,2.2);
//    insertData("test3","testc",3,3.3);
}

void TestSqliteController::onShowTable(yhge::Event* event)
{
    CCLOG("####show table#####");
    showTable();
}

void TestSqliteController::update1(float delta)
{
    CCLOG("update1");

}

void TestSqliteController::update2(float delta)
{
    CCLOG("update2");
    if (m_tt==0) {
        m_um->removeUpdater(this,schedule_selector(TestSqliteController::update3));
    }
    ++m_tt;
}

void TestSqliteController::update3(float delta)
{
    CCLOG("update3");
}

void TestSqliteController::update4(float delta)
{
    CCLOG("update4");
}

NS_CC_GE_END