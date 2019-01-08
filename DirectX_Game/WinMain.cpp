#include <DxLib.h>
#include "InputManager.h"
#include "FollowCamera.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"


int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	ChangeWindowMode(TRUE);
	SetGraphMode(1200, 800, 32);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//write custom initialize from here
	if (!StageInitialize()) {
		return -1;
	}
	PlayerInit();
	if (!EnemyInit())return -1;
	//end custom initialize
	

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		

		//write cutom update from here
		StageDraw();
		InputCheck();
		SetCamera();
		PlayerUpdate();
		EnemyUpdate();
		//end cutom update

	
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
