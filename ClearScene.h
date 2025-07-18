#pragma once

#include "IScene.h"

// クリアシーン
class ClearScene : public IScene {

public:
	void Initialize() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	int gamecleargraph;
};

