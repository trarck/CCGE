#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "BaseScene.h"

NS_CC_GE_BEGIN

class MainScene : public BaseScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

    void loadContents();

	// implement the "static node()" method manually
    CREATE_FUNC(MainScene);
private:

};

NS_CC_GE_END

#endif // __MainScene_SCENE_H__
