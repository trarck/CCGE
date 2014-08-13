#include "DataFactory.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const char* kDataDir="datas/";
static const char* kGameDB="game.db";

static DataFactory* s_dataFactoryInstance=NULL;

DataFactory::DataFactory()
:m_gameDao(NULL)
,m_animationData(NULL)
,m_mapData(NULL)
,m_zoneData(NULL)
,m_unitData(NULL)
,m_monsterData(NULL)
,m_characterData(NULL)
,m_skillData(NULL)
{

}

DataFactory::~DataFactory()
{
    CC_SAFE_RELEASE_NULL(m_gameDao);
    CC_SAFE_RELEASE_NULL(m_animationData);
    CC_SAFE_RELEASE_NULL(m_mapData);
    CC_SAFE_RELEASE_NULL(m_zoneData);
    CC_SAFE_RELEASE_NULL(m_unitData);
    CC_SAFE_RELEASE_NULL(m_monsterData);
    CC_SAFE_RELEASE_NULL(m_characterData);
    CC_SAFE_RELEASE_NULL(m_skillData);
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
    setupDao();
    setupData();
}


void DataFactory::setupDao()
{
    m_gameDao=new JSONDAO();
    //game db里面的内容是不可写的。
    //game db会随着发布放在app里，而app里的内容是不可改变的。
    //就算放在Document或Cache目录下，也没有写的需要，通常是在开发的时候生成好的。
    //所以game db无法做增量更新，只能更新整个DB.当然放在可写目录可以考增量，但复杂度大大增加。
    //如果需要可写的DB，保存一些零时信息，可以考虑创建一个DB
    m_gameDao->init(getDataFilePath(kGameDB), SQLITE_OPEN_READONLY);
}

void DataFactory::setupData()
{
    m_animationData=new AnimationData();
    m_animationData->init();
    m_animationData->loadFromFile(getDataFilePath("animation.json"));
    
    m_mapData=new MapData();
    m_mapData->init();
    m_mapData->loadFromFile(getDataFilePath("map.json"));
    
    m_zoneData=new BaseData();
    m_zoneData->init();
    m_zoneData->loadFromFile(getDataFilePath("zone.json"));
    
    m_unitData=new UnitData();
    m_unitData->init(m_gameDao,"units");
    
    m_monsterData=new MonsterData();
    m_monsterData->init(m_gameDao,"monsters");
    
    m_characterData=new CharacterData();
    m_characterData->init(m_gameDao,"characters");
    
    m_skillData=new SkillData();
    m_skillData->init(m_gameDao,"skills");
    
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
