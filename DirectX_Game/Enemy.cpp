#include <DxLib.h>
#include<random>
#include "EnemyDrone.h"
#include "EnemyRobot.h"

#define ENEMY_COUNT 10

int enemyes[ENEMY_COUNT];
int enemyType[ENEMY_COUNT];
VECTOR enemyPos[ENEMY_COUNT];
float enemyCollisionRadius = 150.0f;


bool EnemyInit();
void EnemyUpdate();
int EnemyCheckHitSphere(VECTOR, float);
VECTOR EnemyMostNearHitPos(VECTOR, float, int);


bool EnemyInit() {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (i % 2 == 0)
		{
			enemyes[i] = DroneInit();
			enemyType[i] = 0;
			enemyPos[i] = VGet(rand() % 100, rand() % 100, rand() % 100);
			if (enemyes[i] == -1)return false;
		}
		else {
			enemyes[i] = RobotInit();
			enemyType[i] = 1;
			enemyPos[i] = VGet(rand() % 100, rand() % 100, rand() % 100);
			if (enemyes[i] == -1)return false;
		}
	}

	return true;
}

void EnemyUpdate() {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemyType[i] == 0) {
			DroneDraw((enemyes[i]), enemyPos[i]);
		}
		else if (enemyType[i] == 1) {
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