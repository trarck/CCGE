#include "DataFactory.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const char* kDataDir="datas/";
static const char* kGameDB="game.db";

static DataFactory* s_dataFactoryInstance=NULL;

DataFactory::DataFactory()
:m_driver(NULL)
,m_animationDAO(NULL)
,m_mapDAO(NULL)
,m_zoneDAO(NULL)
,m_unitDAO(NULL)
,m_monsterDAO(NULL)
,m_characterDAO(NULL)
,m_skillDAO(NULL)
,m_skillGroupDAO(NULL)
{

}

DataFactory::~DataFactory()
{
    CC_SAFE_RELEASE_NULL(m_driver);
    CC_SAFE_RELEASE_NULL(m_animationDAO);
    CC_SAFE_RELEASE_NULL(m_mapDAO);
    CC_SAFE_RELEASE_NULL(m_zoneDAO);
    CC_SAFE_RELEASE_NULL(m_unitDAO);
    CC_SAFE_RELEASE_NULL(m_monsterDAO);
    CC_SAFE_RELEASE_NULL(m_characterDAO);
    CC_SAFE_RELEASE_NULL(m_skillDAO);
    CC_SAFE_RELEASE_NULL(m_skillGroupDAO);
}

bool DataFactory::init()
{
    setup();
    return true;
}

DataFactory* DataFactory::getInstance()
{
    if (!s_dataFactoryInstance)
    {
        s_dataFactoryInstance=new DataFactory();
        s_dataFactoryInstance->init();
    }
    return s_dataFactoryInstance;
}

void DataFactory::setup()
{
    setupDriver();
    setupDAO();
}


void DataFactory::setupDriver()
{
    //game db里面的内容是不可写的。
    //game db会随着发布放在app里，而app里的内容是不可改变的。
    //就算放在Document或Cache目录下，也没有写的需要，通常是在开发的时候生成好的。
    //所以game db无法做增量更新，只能更新整个DB.当然放在可写目录可以考增量，但复杂度大大增加。
    //如果需要可写的DB，保存一些零时信息，可以考虑创建一个DB

    sqlite::SqliteDriver* sqliteDriver=new sqlite::SqliteDriver();
    
    m_driver=new yhge::data::CocosSqliteDriver(sqliteDriver);
    
    sqliteDriver->connect(getDataFilePath(kGameDB), SQLITE_OPEN_READONLY);

}

void DataFactory::setupDAO()
{
    m_animationDAO=new AnimationDAO();
    m_animationDAO->init();
    m_animationDAO->loadFromFile(getDataFilePath("animation.json"));
    
    m_mapDAO=new MapDAO();
    m_mapDAO->init();
    m_mapDAO->loadFromFile(getDataFilePath("map.json"));
    
    m_zoneDAO=new BaseDAO();
    m_zoneDAO->init();
    m_zoneDAO->loadFromFile(getDataFilePath("zone.json"));
    
    m_unitDAO=new UnitDAO();
    m_unitDAO->init(m_driver,"units");
    
    m_monsterDAO=new MonsterDAO();
    m_monsterDAO->init(m_driver,"monsters");
    
    m_characterDAO=new CharacterDAO();
    m_characterDAO->init(m_driver,"characters");
    
    m_skillDAO=new SkillDAO();
    m_skillDAO->init(m_driver,"skills");
    
    m_skillGroupDAO=new BaseSqlDAO();
    m_skillGroupDAO->init(m_driver,"skill_groups");
    
}

std::string DataFactory::getDataFilePath(const std::string& file)
{
    std::string filePath=file;

    //如果是绝对路径，则直接使用
    if (filePath[0]!='/')
    {
        //如果不是在data目录，则添加到data目录
        if (file.substr(0,strlen(kDataDir))!=kDataDir)
        {
            filePath=kDataDir+file;
        }

        //转到绝对目录
        filePath=CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath.c_str());
    }
    
    return filePath;
}

NS_CC_GE_END
