#include <DxLib.h>
#include "InputManager.h"
#include "FollowCamera.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ShootEffect.h"


int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	int title;
	bool isStart = false;

	ChangeWindowMode(TRUE);
	SetGraphMode(1200, 800, 32);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//write custom initialize from here
	title = LoadGraph("title.png");

	if (!StageInitialize()) {
		return -1;
	}
	PlayerInit();
	if (!EnemyInit())return -1;

	ShootEffectInit();
	//end custom initialize
	

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		

		//write cutom update from here
		if (isStart) {
			StageDraw();
			InputCheck();
			SetCamera();
			EnemyUpdate();
			PlayerUpdate();
		}

		else {
			int windowWidth, windowHeight;
			GetWindowSize(&windowWidth, &windowHeight);
			DrawExtendGraph(0, 0, windowWidth, windowHeight, title, FALSE);
			SetFontSize(50);

			int xpos, ypos;
			GetMousePoint(&xpos, &ypos);
			if (windowWidth / 2 - 30 <= xpos && xpos <= windowWidth / 2 - 30 + 140 && windowHeight - 80 <= ypos && ypos <= windowHeight - 80 + 50) {
				DrawString(windowWidth / 2 - 30, windowHeight - 80, "START", GetColor(255, 0, 0));
			}
			else{ DrawString(windowWidth / 2 - 30, windowHeight - 80, "START", GetColor(255, 255, 255)); }


			int mouseClick = GetMouseInput();
			if (mouseClick && MOUSE_INPUT_LEFT) {
				int xpos, ypos;
				GetMousePoint(&xpos, &ypos);
				if (windowWidth / 2 - 30 <= xpos && xpos <= windowWidth / 2 - 30 + 140 && windowHeight - 80 <= ypos && ypos <= windowHeight - 80 + 50) {
					isStart = true;
				}
			}
			SetFontSize(-1);
		}
		//end cutom update

	
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
