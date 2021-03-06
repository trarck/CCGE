#ifndef CCGE_SCENES_INITIALIZESCENE_H_
#define CCGE_SCENES_INITIALIZESCENE_H_

#include "BaseScene.h"

NS_CC_GE_BEGIN

class InitializeScene : public BaseScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

    void loadContents();

	// implement the "static node()" method manually
    CREATE_FUNC(InitializeScene);
private:

};

NS_CC_GE_END

#endif // CCGE_SCENES_INITIALIZESCENE_H_
