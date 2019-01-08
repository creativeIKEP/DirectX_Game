#include <DxLib.h>
#include<random>
#include "EnemyDrone.h"
#include "EnemyRobot.h"
#include "FollowCamera.h"

#define ENEMY_COUNT 10

int enemyes[ENEMY_COUNT];
int enemyType[ENEMY_COUNT];
float enemyCollisionRadius = 120.0f;
bool isAlive[ENEMY_COUNT];
VECTOR enemyPos[ENEMY_COUNT] = 
{
	VGet(0.0f, 160.0f, 2381.3f),
	VGet(2734.0f, 160.0f, 2766.57f),
	VGet(1527.21f, 160.0f, 1575.2f),
	VGet(1972.52f, 160.0f, -1594.85f),
	VGet(4661.70f, 160.0f, -770.32f),
	VGet(5090.91f, 160.0f, 2768.0f),
	VGet(7487.0f, 160.0f, 36.39f),
	VGet(7453.25f, 160.0f, 704.62f),
	VGet(7495.0f, 160.0f, 2811.47f),
	VGet(7495.0f, 160.0f, 2811.47f),
};


bool EnemyInit();
void EnemyUpdate();
int EnemyCheckHitSphere(VECTOR, float);
VECTOR EnemyMostNearHitPos(VECTOR, float, int);
float GetEnemyCollisionRadius();
VECTOR GetEnemyesPos(int);
void SetDead(int);


bool EnemyInit() {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (i % 2 == 0)
		{
			enemyes[i] = DroneInit();
			enemyType[i] = 0;
			enemyPos[i].y = 200;
			//enemyPos[i] = VGet(rand() % 100, rand() % 100, rand() % 100);
			if (enemyes[i] == -1)return false;
			isAlive[i] = true;
		}
		else {
			enemyes[i] = RobotInit();
			enemyType[i] = 1;
			enemyPos[i].y = 50;
			//enemyPos[i] = VGet(rand() % 100, rand() % 100, rand() % 100);
			if (enemyes[i] == -1)return false;
			isAlive[i] = true;
		}
	}

	return true;
}

void EnemyUpdate() {
	VECTOR camePos = GetCameraPos();
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemyType[i] == 0 && isAlive[i]) {
			VECTOR sub = VSub(camePos, enemyPos[i]);
			if (VSize(sub) <= 500) {
				MATRIX rotationMatrix = MGetRotVec2(VGet(0, 0, -1), VNorm(sub));
				VECTOR rot = VTransform(VGet(0, 0, -1), rotationMatrix);
				rot.y = -rot.x*1.5f;
				rot.x = 0;
				rot.z = 0;
				MV1SetRotationXYZ(enemyes[i],rot);
			}

			DroneDraw((enemyes[i]), enemyPos[i]);
		}
		else if (enemyType[i] == 1 && isAlive[i]) {
			RobotDraw((enemyes[i]), enemyPos[i]);
		}
	}
}


int EnemyCheckHitSphere(VECTOR centerPos, float radius) {
	for (int i=0; i < ENEMY_COUNT; i++) {
		VECTOR sub = VSub(centerPos, enemyPos[i]);
		float subDistance = VSize(sub);
		if (subDistance <= (radius + enemyCollisionRadius)) {
			return i;
		}
	}
	return -1;
}

VECTOR EnemyMostNearHitPos(VECTOR centerPos, float radius, int enemyIndex) {
	VECTOR sub = VSub(centerPos, enemyPos[enemyIndex]);
	VECTOR subNorm = VNorm(sub);
	return VAdd(enemyPos[enemyIndex], VScale(subNorm, enemyCollisionRadius));
}

float GetEnemyCollisionRadius() {
	return enemyCollisionRadius;
}

VECTOR GetEnemyesPos(int index) {
	return enemyPos[index];
}

void SetDead(int index) {
	isAlive[index] = false;
}