
#include "ClearScene.h"
#include <Novice.h>

void ClearScene::Initialize() {
	gamecleargraph = Novice::LoadTexture("./images/ui/gameclear.png"); 

}


void ClearScene::Update(char* keys, char* preKeys) {
	if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
		TransitionTo(TITLE);
	}
}

void ClearScene::Draw() { 
	Novice::DrawSprite(0, 0, gamecleargraph, 1.0f, 1.0f, 0.0f, WHITE);
}