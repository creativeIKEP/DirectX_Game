#include <DxLib.h>


void PlayerInit();
void PlayerUpdate();

void PlayerInit() {
	
}

void PlayerUpdate() {
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);
	DrawString(windowWidth / 2, windowHeight / 2, "+", GetColor(0, 0, 0));
}