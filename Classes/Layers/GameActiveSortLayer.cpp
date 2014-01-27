#include "GameActiveSortLayer.h"
#include "EntityComponent/EntityFactory.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

enum ObjectType
{
    //静态物体
    kObjectTypeStatic,
    
    //动态物体
    kObjectTypeDynamic
};



GameActiveSortLayer::GameActiveSortLayer()
:m_occlusion(NULL)
,m_staticRootNode(NULL)
//,m_dynamicObjects(NULL)
,m_staticObjects(NULL)
,m_dynamicNodes(NULL)
,m_occlusionDirty(false)
{
	
}

GameActiveSortLayer::~GameActiveSortLayer()
{
    CC_SAFE_RELEASE_NULL(m_occlusion);
    CC_SAFE_RELEASE_NULL(m_staticRootNode);
    CC_SAFE_RELEASE_NULL(m_staticObjects);
//    CC_SAFE_RELEASE_NULL(m_dynamicObjects);
    CC_SAFE_RELEASE_NULL(m_dynamicNodes);
}

bool GameActiveSortLayer::init()
{
    if (ISOActiveLayer::init()) {
        
        m_occlusion=new SortZIndex();
        m_occlusion->init();
        
//        m_dynamicObjects=new CCArray();
        
        m_staticObjects=new CCArray();
        
        m_dynamicNodes=new CCArray();
        
        return true;
    }
    
	return false;
}

GameActiveSortLayer* GameActiveSortLayer::create()
{
    GameActiveSortLayer* pRet=new GameActiveSortLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

/**
 * 设置层
 */
void GameActiveSortLayer::setupLayer()
{
    ISOActiveLayer::setupLayer();
//    //尽量在其它更新器完成后，还没有开始draw的时候更新
//    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 1, false);
}

void GameActiveSortLayer::releaseLayer()
{
    ISOActiveLayer::releaseLayer();
}

void GameActiveSortLayer::setupObjects()
{
    if (m_objects) {
        CCObject* pObj=NULL;
        ISOObjectInfo* objInfo=NULL;
        
        struct timeval now;
        gettimeofday(&now,NULL);
        
        CCARRAY_FOREACH(m_objects, pObj){
            objInfo=static_cast<ISOObjectInfo*>(pObj);
            if (objInfo->getGid()!=0 && objInfo->getVisible()) {
                
                //按对象类型处理元素
                switch (this->getObjectType(objInfo)) {
                    case kObjectTypeStatic:{
                        //创建静态对象
                        CCSprite* mapObj=createObject(objInfo->getGid(), objInfo->getPosition());
                        
                        //添加到静态组中
                        m_staticObjects->addObject(objInfo);
                        
                        //对元素进行排序
                        m_occlusion->insert(createSortZIndexNode(mapObj, objInfo));
                        break;
                    }
                    case kObjectTypeDynamic:{
                        //添加到动态数组中。这里可以不添加
//                        m_dynamicObjects->addObject(objInfo);
                        
                        //创建动态对象
                        GameEntity* mapObj=createDynamicObject(objInfo->getGid(), objInfo->getPosition());
                        
                        //创建动态对象对应的排序结点
                        RendererComponent* renderer=mapObj->getRendererComponent();
                        m_dynamicNodes->addObject(createSortZIndexNode(renderer->getRenderer(), objInfo));
                        
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        
        struct timeval end;
        gettimeofday(&end,NULL);
        
        CCLOG("build static tree use:%ld", (end.tv_sec-now.tv_sec)*1000000+end.tv_usec-now.tv_usec);
        
        //保存当前的静态物体的遮挡关系树
        setStaticRootNode(m_occlusion->getRootNode()->clone());
        
        //把动态元素也加入排序树中
        updateDynamicObjectsZOrderFirst();
    }
}

void GameActiveSortLayer::sortAllChildren()
{
    //在画之前检查遮挡关系
    if (m_occlusionDirty) {
        m_occlusionDirty=false;
        update();
    }
    
    ISOActiveLayer::sortAllChildren();
}

/**
 * 更新遮挡树
 */
void GameActiveSortLayer::update()
{
//    if (m_occlusionDirty) {
//        m_occlusionDirty=false;
    //使用静态的根，减少排序时间
    SortZIndexNode* rootNode=NULL;
    if (m_staticRootNode) {
        rootNode=m_staticRootNode->clone();
    }else{
        //没有静态根，创建一个新的根
        rootNode=SortZIndexNode::create();
    }
    
    m_occlusion->setRootNode(rootNode);
    this->updateDynamicObjectsZOrder();
//    }
}


/**
 * 添加一个动态元素
 */
void GameActiveSortLayer::addDynamicObject(GameEntity* obj)
{
    RendererComponent* renderer=obj->getRendererComponent();
    ISOPositionComponent* positionComponent=obj->getISOPositionComponent();
    
    CCRect rect=CCRectMake(positionComponent->getX(),positionComponent->getY(), 1, 1);
    
    m_dynamicNodes->addObject(createSortZIndexNodeWithRect(renderer->getRenderer(), rect));
    m_occlusionDirty=true;
}

/**
 * 移除一个动态组件
 */
void GameActiveSortLayer::removeDynamicObject(GameEntity* obj)
{
    int i=0;
    
    CCObject* pObj=NULL;
    SortZIndexNode* node=NULL;
    CCARRAY_FOREACH_REVERSE(m_dynamicNodes, pObj){
        node=static_cast<SortZIndexNode*>(pObj);
        if (node->getEntity()==obj) {
            
            m_dynamicNodes->removeObjectAtIndex(i);
            m_occlusionDirty=true;
            break;
        }
        
        ++i;
    }
}


//创建排序结点
SortZIndexNode* GameActiveSortLayer::createSortZIndexNode(CCNode* mapObject,ISOObjectInfo* mapObjectDef)
{
    CCRect rect=CCRectMake(mapObjectDef->getPosition().x,mapObjectDef->getPosition().y,
//                             mapObjectDef->getSize().width, mapObjectDef->getSize().height
                             1,1
                           );
    
    return createSortZIndexNodeWithRect(mapObject,rect);
}

SortZIndexNode* GameActiveSortLayer::createSortZIndexNodeWithRect(CCNode* mapObject,const CCRect& rect)
{
    SortZIndexNode* node=new SortZIndexNode();
    
    node->setEntity(mapObject);
    node->setRect(rect);
    
    node->autorelease();
    
    return node;
}

//更新动态物体的ZOrder。创建成功的第一次更新
void GameActiveSortLayer::updateDynamicObjectsZOrderFirst()
{
    CCObject* pObj=NULL;
    SortZIndexNode* node=NULL;
    GameEntity* mapObject=NULL;
    
    CCARRAY_FOREACH(m_dynamicNodes, pObj){
        node=static_cast<SortZIndexNode*>(pObj);
        
        mapObject=static_cast<GameEntity*>(node->getEntity());
        CCRect nodeRect=node->getRect();
        
        node->reset();
        node->setEntity(mapObject);
        
        //更新位置，直接把屏幕坐标转成地图坐标，根据不同的实现，这里可能不同
        ISOPositionComponent* positionComponent=mapObject->getISOPositionComponent();
        nodeRect.origin=ccp(positionComponent->getX(),positionComponent->getY());
        node->setRect(nodeRect);
        
        m_occlusion->insert(node);
    }
    
    //更新zOrder值.无论有没有动态元素都要更新，因为静态元素还没有更新zOrder值。
    m_occlusion->updateZOrder();

}

//更新动态物体的ZOrder
void GameActiveSortLayer::updateDynamicObjectsZOrder()
{
    CCObject* pObj=NULL;
    SortZIndexNode* node=NULL;
    GameEntity* mapObject=NULL;
    
    CCARRAY_FOREACH(m_dynamicNodes, pObj){
        node=static_cast<SortZIndexNode*>(pObj);

        mapObject=static_cast<GameEntity*>(node->getEntity());
        CCRect nodeRect=node->getRect();
        
        node->reset();
        node->setEntity(mapObject);
        
        //更新位置，直接把屏幕坐标转成地图坐标，根据不同的实现，这里可能不同
        ISOPositionComponent* positionComponent=mapObject->getISOPositionComponent();
        nodeRect.origin=ccp(positionComponent->getX(),positionComponent->getY());
        node->setRect(nodeRect);

        m_occlusion->insert(node);
    }
    
    //更新zOrder值
    if (m_dynamicNodes->count()) {
        m_occlusion->updateZOrder();
    }
}

//取得对象的类型
int GameActiveSortLayer::getObjectType(yhge::ISOObjectInfo* mapObjectDef)
{
    //把字符串转成数字
    std::string objectTypeStr=mapObjectDef->getType();
    int objectType=kObjectTypeStatic;//默认为静态对象
    
    if (objectTypeStr!="") {
        objectType=atoi(objectTypeStr.c_str());
    }
    
    return objectType;
}

//创建动态对象
GameEntity* GameActiveSortLayer::createDynamicObject(int gid,const CCPoint& coord)
{
    GameEntity* gameObj=EntityFactory::getInstance()->createEntityById(gid);
    
    return gameObj;
}

NS_CC_GE_END
