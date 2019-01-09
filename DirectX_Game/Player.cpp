#include <DxLib.h>
#include <math.h>
#include "Enemy.h"
#include "FollowCamera.h"
#include "ShootEffect.h"


int life = 3;
int preHitTime = 0;
int heart;
int gameover;

void PlayerInit();
void PlayerUpdate();
void PlayerShoot();
void PlayerLIfeDown();

void PlayerInit() {
	heart = LoadGraph("heart.png");
	gameover = LoadGraph("gameover.png");
}

void PlayerUpdate() {
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);
	DrawString(windowWidth / 2, windowHeight / 2, "+", GetColor(0, 0, 0));

	ShootEffect();

	if (life <= 0) {
		DrawExtendGraph(0, windowHeight/2 - 55, windowWidth, windowHeight / 2 - 55 + 200, gameover, TRUE);
	}

	else {
		for (int i = 0; i < life; i++) {
			DrawExtendGraph(i * 60, 30, i * 60 + 50, 50, heart, TRUE);
		}
	}
}

void PlayerShoot() {
	//hit check
	VECTOR cameraPos = GetCameraPos();
	VECTOR cameraDirection = GetCameraDirection();
	float enemyRadius = GetEnemyCollisionRadius();

	ShootEffectSet(VAdd(cameraPos, VScale(GetCameraDirection(), 100)));

	for (int i = 0; i < 10; i++) {
		VECTOR enePos = GetEnemyesPos(i);
		float distance = VSize(VSub(enePos, cameraPos));
		float maxAngle_rad = asinf(enemyRadius / distance);

		float dot = VDot(cameraDirection, VSub(enePos, cameraPos));
		float cosValue = dot / (distance*VSize(cameraDirection));
		float angle_rad = acosf(cosValue);

		if (angle_rad <= maxAngle_rad) {
			//enemy hit!
			SetDead(i);

			return;
		}
	}


}

void PlayerLIfeDown() {
	if ((GetNowCount() - preHitTime) > 1000 * 3.0f) {
		preHitTime = GetNowCount();
		life--;
	}
}