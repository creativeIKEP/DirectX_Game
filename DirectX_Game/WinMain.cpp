#include <DxLib.h>

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
	int model1, anim_nutral, anim_run, attachidx, rootflm;
	bool running = FALSE;
	float anim_totaltime, playtime = 0.0f;
	VECTOR pos = VGet(600.0f, 300.0f, -400.0f);
	VECTOR cpos = VGet(600.0f, 600.0f, -400.0f), ctgt = VGet(600.0f, 300.0f, -400.0f);
	int key;
	enum Direction { DOWN, LEFT, UP, RIGHT }direction = DOWN;

	int stage;


	//DXライブラリの画面をウィンドウモードに
	ChangeWindowMode(TRUE);
	//ウィンドウサイズの変更1200*800px, 32ビットカラー
	SetGraphMode(1200, 800, 32);
	//Dxライブラリの初期化。-1なら何らかのエラー
	if (DxLib_Init() == -1) return -1;

	//modelとアニメーションの読み込み
	model1 = MV1LoadModel("Player\\PC.mv1");
	if (model1 == -1)return -1;
	anim_nutral = MV1LoadModel("Player\\Anim_Neutral.mv1");
	if (anim_nutral == -1)return -1;
	anim_run = MV1LoadModel("Player\\Anim_Run.mv1");
	if (anim_run == -1)return -1;

	stage = MV1LoadModel("map.mv1");
	if (stage == -1)return -1;

	//modelにanimを設定
	attachidx = MV1AttachAnim(model1, 0, anim_nutral);
	//idを元にアニメーションの総再生時間を取得
	anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);


	rootflm = MV1SearchFrame(model1, "root");
	MV1SetFrameUserLocalMatrix(model1, rootflm, MGetIdent());



	//ウラ画面表示に設定。描画対象をウラ画面に。screenFlip()で画面を切り替えないと表示されない
	SetDrawScreen(DX_SCREEN_BACK);

	//SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 0.0f, 1.0f));

	//CheckHitKeyで押されているキーのチェック。esc押されたらループ終了
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//アニメーションの進行
		playtime += 0.5f;
		if (playtime > anim_totaltime) { playtime = 0.0f;}
		MV1SetAttachAnimTime(model1, attachidx, playtime);



		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (key & PAD_INPUT_DOWN) {
			pos.z -= 4.0f; 
			direction = DOWN;
		}
		if (key & PAD_INPUT_UP) {
			pos.z += 4.0f;
			direction = UP;
		}
		if (key & PAD_INPUT_LEFT) {
			pos.x -= 4.0f;
			direction = LEFT;
		}
		if (key & PAD_INPUT_RIGHT) {
			pos.x += 4.0f;
			direction = RIGHT;
		}

		if (key == 0) {
			if (running) {
				running = false;
				//アニメーションをはがす
				MV1DetachAnim(model1, attachidx);
				//新規のアニメーションを設定
				attachidx = MV1AttachAnim(model1, 0, anim_nutral);
				anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);
			}
		}
		else {
			if (!running) {
				running = true;
				MV1DetachAnim(model1, attachidx);
				attachidx = MV1AttachAnim(model1, 0, anim_run);
				anim_totaltime = MV1GetAnimTotalTime(model1, attachidx);
			}
		}
		

		//画面消去
		ClearDrawScreen();
		//黄色い四角形の描画
		DrawBox(0, 0, 1200, 800, GetColor(255, 255, 255), TRUE);

		MV1SetRotationXYZ(model1, VGet(0.0f, 1.57f*direction, 0.0f));
		MV1SetPosition(model1, pos);
		MV1DrawModel(model1);

		MV1SetPosition(stage, pos);
		MV1DrawModel(stage);

		//表画面とウラ画面の切り替え
		ScreenFlip();
	}
	//DXライブラリのメモリ開放＆ウィンドウ閉じる
	DxLib_End();
	return 0;
}