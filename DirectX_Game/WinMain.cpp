#include <DxLib.h>
#include "InputManager.h"
#include "FollowCamera.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	int stage;

	ChangeWindowMode(TRUE);
	SetGraphMode(1200, 800, 32);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	stage = MV1LoadModel("Stage\\stagemap.mv1");
	if (stage == -1)return -1;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		

		//write cutom update from here
		MV1DrawModel(stage);
		CheckKeyInput();
		SetCamera();
		//end cutom update

	
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
