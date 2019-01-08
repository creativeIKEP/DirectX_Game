#include "EnemyDrone.h"
#include <DxLib.h>
#include<random>

#define ENEMY_COUNT 10

int enemyes[ENEMY_COUNT];
int enemyType[ENEMY_COUNT];
VECTOR enemyPos[ENEMY_COUNT];


bool EnemyInit();
void EnemyUpdate();


bool EnemyInit() {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		enemyes[i] = DroneInit();
		enemyType[i] = 0;
		enemyPos[i] = VGet(rand() % 100, rand() % 100, rand() % 100);
		if (enemyes[i] == -1)return false;
	}

	return true;
}

void EnemyUpdate() {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemyType[i] == 0) {
			DroneDraw((enemyes[i]), enemyPos[i]);
		}
	}
}