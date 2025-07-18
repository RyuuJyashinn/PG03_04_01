#include "TitleScene.h"
#include <Novice.h>

void TitleScene::Initialize() { 
	
	titlegraph = Novice::LoadTexture("./images/ui/title.png");

}

void TitleScene::Update(char* keys, char* preKeys) {

	if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		TransitionTo(STAGE);
	}
}

void TitleScene::Draw() {

	Novice::DrawSprite(0, 0, titlegraph, 1.0f, 1.0f, 0.0f, WHITE);

}