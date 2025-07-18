#pragma once

// シーン名
enum SCENE { TITLE, STAGE, CLEAR };

// インターフェースクラス
class IScene {

protected:
	static int sceneNo;

public:
	virtual ~IScene();

	virtual void Initialize() = 0;

	virtual void Update(char* keys, char* preKeys) = 0;

	virtual void Draw() = 0;

	 virtual void TransitionTo(SCENE nextScene) { sceneNo = nextScene; }

	int GetSceneNo() { return sceneNo; }
};