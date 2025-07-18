#pragma once
#include<Novice.h>
#include <memory>
#include "GameManager.h"
#include "ClearScene.h"
#include "StageScene.h"
#include "TitleScene.h"

class IScene;

class GameManager {

private:
	// シーン配列
	std::unique_ptr<IScene> sceneArr_[3];

	int currentSceneNo_;

	int prevSceneNo_;

public:
	GameManager();

	//~GameManager();

	int Run();
};