#include <DxLib.h>
#include "InputManager.h"
#include "FollowCamera.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ShootEffect.h"
#include <string>
#include <stdio.h>


int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	int title;
	int isStart = 0;
	int time;
	std::string message = "今からそう遠くない未来2XXX年…\n\nこの世界は、AIによって支配された暗黒時代…\n\nAIは人間を危険な存在と判断し、捕獲・処刑していた…\n\n私はかろうじて逃げてきたが、すべてのAIロボットを倒さないとこの世界は平和にならない…\n\n銃を使ってすべてのAIロボットを倒し、この世界を変えなければならない…\n\n\n\nEnter Start";
	int messageCount = 0;
	int bgm;

	SetMainWindowText("DX GUN GALE");
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

	bgm = LoadSoundMem("Audio\\bgm.mp3");
	//end custom initialize
	

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();

		//write cutom update from here
		if (isStart == 2) {
			if(CheckSoundMem(bgm) == 0)PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
			StageDraw();
			InputCheck();
			SetCamera();
			EnemyUpdate();
			PlayerUpdate();
		}

		else if (isStart == 1) {
			if ((GetNowCount() - time) >= 0.05f * 1000) {
				time = GetNowCount();
				messageCount++;
			}
			std::string sub = message.substr(0, messageCount);
			int windowWidth, windowHeight;
			GetWindowSize(&windowWidth, &windowHeight);
			DrawString(windowWidth / 2 - 400, windowHeight/2-150, sub.c_str(), GetColor(255, 255, 255));

			if (CheckHitKey(KEY_INPUT_RETURN) == 1 && sub == message) {
				isStart = 2;
			}
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
					isStart = 1;
					time = GetNowCount();
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
