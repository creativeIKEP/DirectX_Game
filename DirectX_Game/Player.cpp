#include <DxLib.h>
#include <math.h>
#include "Enemy.h"
#include "FollowCamera.h"


int life = 10;

void PlayerInit();
void PlayerUpdate();
void PlayerShoot();
void PlayerLIfeDown();

void PlayerInit() {
	
}

void PlayerUpdate() {
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);
	DrawString(windowWidth / 2, windowHeight / 2, "+", GetColor(0, 0, 0));
}

void PlayerShoot() {
	//hit check
	VECTOR cameraPos = GetCameraPos();
	VECTOR cameraDirection = GetCameraDirection();
	float enemyRadius = GetEnemyCollisionRadius();
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
	life--;
}