#ifndef CCGE_LAYERS_GAMEACTIVESORTLAYER_H_
#define CCGE_LAYERS_GAMEACTIVESORTLAYER_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityComponent/GameEntity.h"

NS_CC_GE_BEGIN

/**
 * 活动层。
 * 提供场景活动元素的层
 * 使用遮挡排序来管理，活动元素。经测试性能还可以。
 * 游戏中的活动物体是GameEntity
 */
class GameActiveSortLayer : public yhge::isometric::ISOActiveLayer {

public:
	
	GameActiveSortLayer();
    
	virtual ~GameActiveSortLayer(void);
	
    virtual bool init();
    
    static GameActiveSortLayer* create();

    /**
     * 设置层
     */
    virtual void setupLayer();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();
    
    /**
     * 初始化显示tiles
     */
    virtual void setupObjects();
    
    /**
     * 检查是否要更新遮挡关系
     */
    virtual void sortAllChildren();
    
    /**
     * 更新遮挡树
     */
    void update();
    
    /**
     * 添加一个动态元素
     */
    void addDynamicObject(GameEntity* obj);
    
    /**
     * 移除一个动态组件
     */
    void removeDynamicObject(GameEntity* obj);
    
    /**
     * 动态物体的位置改变
     */
    void onDynamicObjectPositionChange(yhge::Message* message);
    
public:
    
    inline void setOcclusion(yhge::isometric::SortZIndex* occlusion)
    {
        CC_SAFE_RETAIN(occlusion);
        CC_SAFE_RELEASE(m_occlusion);
        m_occlusion = occlusion;
    }
    
    inline yhge::isometric::SortZIndex* getOcclusion()
    {
        return m_occlusion;
    }
    
    inline void setStaticObjects(CCArray* staticObjects)
    {
        CC_SAFE_RETAIN(staticObjects);
        CC_SAFE_RELEASE(m_staticObjects);
        m_staticObjects = staticObjects;
    }
    
    inline CCArray* getStaticObjects()
    {
        return m_staticObjects;
    }
    
//    inline void setDynamicObjects(CCArray* dynamicObjects)
//    {
//        CC_SAFE_RETAIN(dynamicObjects);
//        CC_SAFE_RELEASE(m_dynamicObjects);
//        m_dynamicObjects = dynamicObjects;
//    }
//    
//    inline CCArray* getDynamicObjects()
//    {
//        return m_dynamicObjects;
//    }
    
    inline void setStaticRootNode(yhge::isometric::SortZIndexNode* staticRootNode)
    {
        CC_SAFE_RETAIN(staticRootNode);
        CC_SAFE_RELEASE(m_staticRootNode);
        m_staticRootNode = staticRootNode;
    }
    
    inline yhge::isometric::SortZIndexNode* getStaticRootNode()
    {
        return m_staticRootNode;
    }
    
    inline void setDynamicNodes(CCDictionary* dynamicNodes)
    {
        CC_SAFE_RETAIN(dynamicNodes);
        CC_SAFE_RELEASE(m_dynamicNodes);
        m_dynamicNodes = dynamicNodes;
    }
    
    inline CCDictionary* getDynamicNodes()
    {
        return m_dynamicNodes;
    }
    
    inline void setOcclusionDirty(bool occlusionDirty)
    {
        m_occlusionDirty = occlusionDirty;
    }
    
    inline bool isOcclusionDirty()
    {
        return m_occlusionDirty;
    }
    
protected:
        
    //创建排序结点
    virtual yhge::isometric::SortZIndexNode* createSortZIndexNode(CCNode* mapObject,yhge::isometric::ISOObjectInfo* mapObjectDef);
    
    yhge::isometric::SortZIndexNode* createSortZIndexNodeWithRect(CCNode* mapObject,const CCRect& rect);
    
    //更新动态物体的ZOrder。创建成功的第一次更新
    virtual void updateDynamicObjectsZOrderFirst();
    
    //更新动态物体的ZOrder
    virtual void updateDynamicObjectsZOrder();
    
    //取得对象的类型
    int getObjectType(yhge::isometric::ISOObjectInfo* mapObjectDef);
    
    //创建动态对象
    GameEntity* createDynamicObject(int gid,const CCPoint& coord);
    
    //更新对象的排序结点
    void updateDynamicObjectZIndexNode(GameEntity* obj);
    
protected:

    //遮挡处理
    yhge::isometric::SortZIndex* m_occlusion;
    
    //所有静态物体的遮挡关系树
    yhge::isometric::SortZIndexNode* m_staticRootNode;
    
    //静态物体
    CCArray* m_staticObjects;
    
    //动态物体
//    CCArray* m_dynamicObjects;
    
    //动态元素结点
    CCDictionary* m_dynamicNodes;
    
    bool m_occlusionDirty;
};


NS_CC_GE_END

#endif //CCGE_LAYERS_GAMEACTIVESORTLAYER_H_
