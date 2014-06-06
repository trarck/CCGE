#ifndef CCGE_ANIMATIONS_FCAINFO_H_
#define CCGE_ANIMATIONS_FCAINFO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

struct FcaElement
{
    std::string name;
    std::string textureKey;
    int index;
    CCSize size;
    
};

struct FcaFrameEvent
{
    int type;
    std::string arg;
    CCPoint anchor;
    CCAffineTransform matrix;
    int index;
};

struct FcaFrameElement
{
    short int index;
    unsigned char alpha;
    CCAffineTransform matrix;
};

struct FcaFrame
{
    std::vector<FcaFrameEvent> events;
    std::vector<FcaFrameElement> elements;
};

struct FcaAction
{
    std::string name;
    float fps;
    std::vector<FcaFrame> frames;
};


class MySpriteFrameCache:public CCSpriteFrameCache
{
public:
    
    MySpriteFrameCache();
    
    ~MySpriteFrameCache();
    
};


class FcaInfo:public CCObject
{
public:
	
    FcaInfo(void);
    
	~FcaInfo(void);
    
    bool init();
    
    CCSpriteFrame* getSpriteFrame(const std::string& spriteName);
    
    static FcaInfo* create(const std::string& fcaFile);
    
public:
    
    
    inline void setName(const std::string& name)
    {
        m_name = name;
    }
    
    inline const std::string& getName()
    {
        return m_name;
    }
    
    inline void setElements(const std::vector<FcaElement>& elements)
    {
        m_elements = elements;
    }
    
    inline std::vector<FcaElement>& getElements()
    {
        return m_elements;
    }
    
    inline void setActions(const std::vector<FcaAction>& actions)
    {
        m_actions = actions;
    }
    
    inline std::vector<FcaAction>& getActions()
    {
        return m_actions;
    }
    
    inline void setSpriteFrameCache(MySpriteFrameCache* spriteFrameCache)
    {
        CC_SAFE_RETAIN(spriteFrameCache);
        CC_SAFE_RELEASE(m_spriteFrameCache);
        m_spriteFrameCache = spriteFrameCache;
    }
    
    inline CCSpriteFrameCache* getSpriteFrameCache()
    {
        return m_spriteFrameCache;
    }
    
protected:
    
    std::string m_name;
    std::vector<FcaElement> m_elements;
    std::vector<FcaAction> m_actions;
    MySpriteFrameCache* m_spriteFrameCache;
};

NS_CC_GE_END

#endif //CCGE_ANIMATIONS_FCAINFO_H_
