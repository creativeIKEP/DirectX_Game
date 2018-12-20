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


	//DX���C�u�����̉�ʂ��E�B���h�E���[�h��
	ChangeWindowMode(TRUE);
	//�E�B���h�E�T�C�Y�̕ύX1200*800px, 32�r�b�g�J���[
	SetGraphMode(1200, 800, 32);
	//Dx���C�u�����̏������B-1�Ȃ牽�炩�̃G���[
	if (DxLib_Init() == -1) return -1;

	//model�ƃA�j���[�V�����̓ǂݍ���
	model1 = MV1LoadModel("Player\\PC.mv1");
	if (model1 == -1)return -1;
	anim_nutral = MV1LoadModel("Player\\Anim_Neutral.mv1");
	if (anim_nutral == -1)return -1;
	anim_run = MV1LoadModel("Player\\Anim_Run.mv1");
	if (anim_run == -1)return -1;

	stage = MV1LoadModel("map.mv1");
	if (stage == -1)return -1;

	//model��anim��ݒ�
	attachidx = MV1AttachAnim(model1, 0, anim_nutral);
	//id�����ɃA�j���[�V�����̑��Đ����Ԃ��擾
	anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);


	rootflm = MV1SearchFrame(model1, "root");
	MV1SetFrameUserLocalMatrix(model1, rootflm, MGetIdent());



	//�E����ʕ\���ɐݒ�B�`��Ώۂ��E����ʂɁBscreenFlip()�ŉ�ʂ�؂�ւ��Ȃ��ƕ\������Ȃ�
	SetDrawScreen(DX_SCREEN_BACK);

	//SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 0.0f, 1.0f));

	//CheckHitKey�ŉ�����Ă���L�[�̃`�F�b�N�Besc�����ꂽ�烋�[�v�I��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//�A�j���[�V�����̐i�s
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
				//�A�j���[�V�������͂���
				MV1DetachAnim(model1, attachidx);
				//�V�K�̃A�j���[�V������ݒ�
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
		

		//��ʏ���
		ClearDrawScreen();
		//���F���l�p�`�̕`��
		DrawBox(0, 0, 1200, 800, GetColor(255, 255, 255), TRUE);

		MV1SetRotationXYZ(model1, VGet(0.0f, 1.57f*direction, 0.0f));
		MV1SetPosition(model1, pos);
		MV1DrawModel(model1);

		MV1SetPosition(stage, pos);
		MV1DrawModel(stage);

		//�\��ʂƃE����ʂ̐؂�ւ�
		ScreenFlip();
	}
	//DX���C�u�����̃������J�����E�B���h�E����
	DxLib_End();
	return 0;
}