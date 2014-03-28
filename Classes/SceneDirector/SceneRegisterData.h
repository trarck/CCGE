#ifndef CCGE_SCENES_SCENEREGISTERDATA_H_
#define CCGE_SCENES_SCENEREGISTERDATA_H_

#include <yhmvc/Core/SceneDirector.h>
#include "CCGEMacros.h"

typedef struct SceneRegisterItem
{
    std::string name;
    cocos2d::yhmvc::SceneCreate createFun;
} SceneRegisterItem;

//this file generate by tools.do not modify directorly

#include "Scenes/MainScene.h"
#include "Scenes/TestISOScene.h"
#include "Scenes/MissionScene.h"
#include "Scenes/BattleScene.h"
#include "Scenes/BattlePrepareScene.h"
#include "Scenes/TestSqliteScene.h"
#include "Scenes/SimpleScene.h"
#include "Scenes/InitializeScene.h"

NS_CC_GE_BEGIN

static SceneRegisterItem kSceneRegisterData[]=
{
	{kMainScene,SCENE_CREATE_SELECTOR(MainScene::create)},
	{kTestISOScene,SCENE_CREATE_SELECTOR(TestISOScene::create)},
	{kMissionScene,SCENE_CREATE_SELECTOR(MissionScene::create)},
	{kBattleScene,SCENE_CREATE_SELECTOR(BattleScene::create)},
	{kBattlePrepareScene,SCENE_CREATE_SELECTOR(BattlePrepareScene::create)},
	{kTestSqlite,SCENE_CREATE_SELECTOR(TestSqliteScene::create)},
    {kInitializeScene,SCENE_CREATE_SELECTOR(InitializeScene::create)},
};

NS_CC_GE_END

#endif //CCGE_SCENES_SCENEREGISTERDATA_H_
