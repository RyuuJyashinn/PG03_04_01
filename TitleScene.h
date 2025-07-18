#pragma once

#include "IScene.h"

class TitleScene : public IScene {

public:
	void Initialize() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

	private:
	int titlegraph;
};
