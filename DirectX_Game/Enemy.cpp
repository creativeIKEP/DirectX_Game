#include <DxLib.h>
#include<random>
#include "EnemyDrone.h"
#include "EnemyRobot.h"
#include "FollowCamera.h"
#include "Stage.h"
#include "Player.h"
#include "ShootEffect.h"


#define ENEMY_COUNT 10

int enemyes[ENEMY_COUNT];
int enemyType[ENEMY_COUNT];
float enemyCollisionRadius = 80.0f;
bool isAlive[ENEMY_COUNT];
VECTOR enemyPos[ENEMY_COUNT] = 
{
	VGet(0.0f, 160.0f, 2381.3f),
	VGet(2734.0f, 160.0f, 2766.57f),
	VGet(1527.21f, 160.0f, 1575.2f),
	VGet(1890.52f, 160.0f, -1566.85f),
	VGet(4661.70f, 160.0f, -770.32f),
	VGet(5090.91f, 160.0f, 2768.0f),
	VGet(7487.0f, 160.0f, 36.39f),
	VGet(7453.25f, 160.0f, 704.62f),
	VGet(7495.0f, 160.0f, 2811.47f),
	VGet(7495.0f, 160.0f, 2811.47f),
};

int preAttackTime[ENEMY_COUNT];
MATRIX AttackDirectionMatrix[ENEMY_COUNT];
int explosinoEffect;
VECTOR explosionPos[ENEMY_COUNT];
int explosionTime[ENEMY_COUNT];
int clear;
int deadNum = 0;
int enemySootSound;
int enemyDeathSound;


bool EnemyInit();
void EnemyUpdate();
int EnemyCheckHitSphere(VECTOR, float);
VECTOR EnemyMostNearHitPos(VECTOR, float, int);
float GetEnemyCollisionRadius();
VECTOR GetEnemyesPos(int);
void SetDead(int);
void EnemyCheckCollision(int);
void HitCheck(VECTOR, VECTOR);


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
		preAttackTime[i] = 0;
	}

	explosinoEffect = LoadGraph("explosion.png");
	clear = LoadGraph("clear.png");
	enemySootSound = LoadSoundMem("Audio\\enemyShot.mp3");
	enemyDeathSound = LoadSoundMem("Audio\\explosion.mp3");
	ChangeVolumeSoundMem(255 * 200 / 100, enemyDeathSound);

	return true;
}

void EnemyUpdate() {
	VECTOR camePos = GetCameraPos();
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemyType[i] == 0 && isAlive[i]) {
			VECTOR sub = VSub(camePos, enemyPos[i]);
			if (VSize(sub) <= 1500 && VSize(sub)>1000) {
				VECTOR y0sub = sub;

				y0sub.y = 0;
				VECTOR y0subNorm = VNorm(y0sub);
				enemyPos[i] = VAdd(enemyPos[i], VScale(y0subNorm, 5.0f));

				VECTOR subnorm = VNorm(sub);
				MATRIX matrix = MGetRotVec2(VGet(0, 0, -1), VGet(subnorm.x, 0, subnorm.z));
				MV1SetRotationMatrix(enemyes[i], matrix);
			}
			if (VSize(sub) <= 1000) {
				VECTOR subnorm = VNorm(sub);
				MATRIX matrix = MGetRotVec2(VGet(0, 0, -1), VGet(subnorm.x, 0, subnorm.z));
				if ((GetNowCount() - preAttackTime[i]) > 1000 * 1) {
					if ((GetNowCount() - preAttackTime[i]) < 1000 * (3+1)) {
						MV1SetRotationMatrix(enemyes[i], matrix);
						AttackDirectionMatrix[i] = matrix;
						
					}
					else if((GetNowCount() - preAttackTime[i]) < 1000 * (3 + 3)){
						VECTOR direction = VTransform(VGet(0, -0.2f, -1), AttackDirectionMatrix[i]);
						ShootEffectSet(VAdd(enemyPos[i], VScale(direction, 200)));
						HitCheck(enemyPos[i], VNorm(direction));
						ShootEffect();
						if (CheckSoundMem(enemySootSound) == 0)PlaySoundMem(enemySootSound, DX_PLAYTYPE_BACK);
					}
					else if ((GetNowCount() - preAttackTime[i]) >= 1000 * (3 + 3)) {
						MV1SetRotationMatrix(enemyes[i], matrix);
						preAttackTime[i] = GetNowCount();
					}
				}
				else {
					MV1SetRotationMatrix(enemyes[i], matrix);
				}
			}

			EnemyCheckCollision(i);

			DroneDraw((enemyes[i]), enemyPos[i]);
		}
		else if (enemyType[i] == 1 && isAlive[i]) {
			VECTOR sub = VSub(camePos, enemyPos[i]);
			if (VSize(sub) <= 1500 && VSize(sub)>1000) {
				VECTOR subnorm = VNorm(sub);

				VECTOR y0sub = sub;
				y0sub.y = 0;
				VECTOR y0subNorm = VNorm(y0sub);
				enemyPos[i] = VAdd(enemyPos[i], VScale(y0subNorm, 5.0f));

				MATRIX matrix = MGetRotVec2(VGet(-1, 0, 0), VGet(subnorm.x, 0, subnorm.z));
				MV1SetRotationMatrix(enemyes[i], matrix);
			}
			if (VSize(sub) <= 1000) {
				VECTOR subnorm = VNorm(sub);
				MATRIX matrix = MGetRotVec2(VGet(-1, 0, 0), VGet(subnorm.x, 0, subnorm.z));
				if ((GetNowCount() - preAttackTime[i]) > 1000 * 1) {
					if ((GetNowCount() - preAttackTime[i]) < 1000 * (3 + 1)) {
						MV1SetRotationMatrix(enemyes[i], matrix);
						AttackDirectionMatrix[i] = matrix;

					}
					else if ((GetNowCount() - preAttackTime[i]) < 1000 * (3 + 3)) {
						VECTOR direction = VTransform(VGet(-1, 1, -1), AttackDirectionMatrix[i]);
						ShootEffectSet(VAdd(enemyPos[i], VScale(direction, 80)));
						HitCheck(enemyPos[i], VNorm(direction));
						ShootEffect();
						if (CheckSoundMem(enemySootSound) == 0)PlaySoundMem(enemySootSound, DX_PLAYTYPE_BACK);
					}
					else if ((GetNowCount() - preAttackTime[i]) >= 1000 * (3 + 3)) {
						MV1SetRotationMatrix(enemyes[i], matrix);
						preAttackTime[i] = GetNowCount();
					}
				}
				else {
					MV1SetRotationMatrix(enemyes[i], matrix);
				}
			}

			EnemyCheckCollision(i);
			RobotDraw((enemyes[i]), enemyPos[i]);
		}
		ShootEffect();

		int explosionDeltaTime = GetNowCount() - explosionTime[i];
		if (explosionTime[i] != 0 && explosionDeltaTime<=0.25f*1000) {
			double rate = explosionDeltaTime / (0.25f * 1000);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)255*rate);
			DrawExtendGraph3D(explosionPos[i].x, explosionPos[i].y, explosionPos[i].z, rate, rate, explosinoEffect, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);
	DrawFormatString(windowWidth - 300, 50, GetColor(0, 0, 0), "“|‚µ‚½”:%d/%d", deadNum, ENEMY_COUNT);

	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (isAlive[i]) {
			return;
		}
	}
	DrawExtendGraph(0, 0, windowWidth, windowHeight, clear, TRUE);
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
	explosionPos[index] = enemyPos[index];
	if(isAlive[index])explosionTime[index] = GetNowCount();
	if(isAlive[index])deadNum++;
	if (deadNum > ENEMY_COUNT)deadNum = ENEMY_COUNT;
	isAlive[index] = false;
	if (CheckSoundMem(enemyDeathSound) == 0)PlaySoundMem(enemyDeathSound, DX_PLAYTYPE_BACK);
}

void EnemyCheckCollision(int index) {
	if (CheckHitSphere(enemyPos[index], enemyCollisionRadius)) {
		VECTOR nearPos = MostNearHitPos(enemyPos[index], enemyCollisionRadius);
		VECTOR sub = VSub(enemyPos[index], nearPos);
		float dis = VSize(sub);
		VECTOR subNorm = VNorm(sub);
		subNorm.y = 0;
		VECTOR moveVec = VScale(subNorm, abs((long)((enemyCollisionRadius - dis)*0.2f)));
		enemyPos[index] = VAdd(enemyPos[index], moveVec);
	}
}

void HitCheck(VECTOR enemypos, VECTOR enemyDirection) {
	VECTOR cameraPos = GetCameraPos();
	float playerRadius = GetCameraCollisionRadius();

	float distance = VSize(VSub(enemypos, cameraPos));
	float maxAngle_rad = asinf(playerRadius / distance);

	float dot = VDot(enemyDirection, VSub(cameraPos, enemypos));
	float cosValue = dot / (distance*VSize(enemyDirection));
	float angle_rad = acosf(cosValue);

	if (angle_rad <= maxAngle_rad) {
		//player hit!
		PlayerLIfeDown();

		return;
	}
}