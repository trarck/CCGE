#include "TestSqliteController.h"
#include <yhge/yhge.h>

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGE_SQLITE;

NS_CC_GE_BEGIN

static const float kGameTileWidth=100;
static const float kGameTileHeight=90;

TestSqliteController::TestSqliteController(void)
:m_sqliteDB(NULL)
{
    m_sName="TestSqliteController";
}

TestSqliteController::~TestSqliteController(void)
{
    CCLOG("TestSqliteController destroy");
    CC_SAFE_RELEASE_NULL(m_sqliteDB);
}

void TestSqliteController::layerDidLoad()
{
    //in test sqlite
    
    std::string dbPath=CCFileUtils::sharedFileUtils()->getWritablePath()+"test.db";
    
    m_sqliteDB=new SqliteDB();

    m_sqliteDB->connect(dbPath,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
    
    createTable();
    
    insertData("test1","testa",1,1.1);
    insertData("test2","testb",2,2.2);
    insertData("test3","testc",3,3.3);
    
    showTable();
    
    m_sqliteDB->close();
}


void TestSqliteController::createTable()
{
    std::string createSql="CREATE TABLE IF NOT EXISTS data(key TEXT PRIMARY KEY,value TEXT,inte integer,fl real);";
//    m_sqliteDB->execute(createSql);
}

void TestSqliteController::insertData(std::string key,std::string value,int inte,float fl)
{
    const char *insertSql = "INSERT into data(key,value) VALUES(?,?,?,?)";
    Statement stmt(*m_sqliteDB, insertSql);
    stmt.bind(1, key);
    stmt.bind(2, value);
    stmt.bind(3, inte);
    stmt.bind(4, fl);
    stmt.execute();
}

void TestSqliteController::showTable()
{
    const char *selectSQl = "SELECT * FROM data;";
    Statement stmt(*m_sqliteDB, selectSQl);
    
    int colCount=stmt.getColumnCount();
    
    while (stmt.executeStep()) {
        for (int i=0; i<colCount; i++) {
            Column col=stmt.getColumn(i);
            printf("%s[%d]=%s,",col.getName(),col.getType(),col.getText());
        }
        printf("\n");
    }
}

NS_CC_GE_END