#include <DxLib.h>

bool EnemyInit();
void EnemyUpdate();
int EnemyCheckHitSphere(VECTOR, float);
VECTOR EnemyMostNearHitPos(VECTOR, float, int);
float GetEnemyCollisionRadius();
VECTOR GetEnemyesPos(int);
void SetDead(int);
void EnemyCheckCollision(int);