#include "AppDelegate.h"
#include "Game.h"
#include "Consts/GameDefine.h"
#include "SceneDirector/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHMVC;
USING_NS_CC_GE;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //set search paths for content
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths;
    
	searchPaths.push_back(GAME_CONTENT_PATH);

	pFileUtils->setSearchPaths(searchPaths);

    // create a scene. it's an autorelease object
    Game::getInstance()->setup();
    
    GameSceneDirector::getInstance()->runWithScene(kInitializeScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
