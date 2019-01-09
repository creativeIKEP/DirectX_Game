#include <DxLib.h>
#include <math.h>
#include "Stage.h"
#include "Enemy.h"

#define MPI  3.14159265358979323846



VECTOR cpos = VGet(-600.0f, 150.0f, 0.0f), ctgt = VGet(-500.0f, 150.0f, 0.0f);
float cameraCollisionRadius = 150.0f;

int preMouseX, preMouseY;
float rotateX_degree, rotateY_degree;


void SetCamera();
void MoveForward();
void MoveBack();
void MoveRight();
void MoveLeft();
void DashForward();
void DashBack();
void DashRight();
void DashLeft();
void RotateCamera();
void CheckCollision();
VECTOR GetCameraPos();
VECTOR GetCameraDirection();
float GetCameraCollisionRadius();


void SetCamera() {
	SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));
}


void MoveForward() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x -= cameraDirection.x*4.0f;
	cpos.x -= cameraDirection.x*4.0f;
	ctgt.y -= cameraDirection.y*4.0f;
	cpos.y -= cameraDirection.y*4.0f;
	ctgt.z -= cameraDirection.z*4.0f;
	cpos.z -= cameraDirection.z*4.0f;
	CheckCollision();
}


void MoveBack() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x += cameraDirection.x*4.0f;
	cpos.x += cameraDirection.x*4.0f;
	ctgt.y += cameraDirection.y*4.0f;
	cpos.y += cameraDirection.y*4.0f;
	ctgt.z += cameraDirection.z*4.0f;
	cpos.z += cameraDirection.z*4.0f;
	CheckCollision();
}


void MoveRight() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x -= cameraDirection.z*4.0f;
	cpos.x -= cameraDirection.z*4.0f;
	ctgt.y -= cameraDirection.y*4.0f;
	cpos.y -= cameraDirection.y*4.0f;
	ctgt.z -= -cameraDirection.x*4.0f;
	cpos.z -= -cameraDirection.x*4.0f;
	CheckCollision();
}


void MoveLeft() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x += cameraDirection.z*4.0f;
	cpos.x += cameraDirection.z*4.0f;
	ctgt.y += cameraDirection.y*4.0f;
	cpos.y += cameraDirection.y*4.0f;
	ctgt.z += -cameraDirection.x*4.0f;
	cpos.z += -cameraDirection.x*4.0f;
	CheckCollision();
}

void DashForward() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x -= cameraDirection.x*10.0f;
	cpos.x -= cameraDirection.x*10.0f;
	ctgt.y -= cameraDirection.y*10.0f;
	cpos.y -= cameraDirection.y*10.0f;
	ctgt.z -= cameraDirection.z*10.0f;
	cpos.z -= cameraDirection.z*10.0f;
	CheckCollision();
}


void DashBack() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x += cameraDirection.x*10.0f;
	cpos.x += cameraDirection.x*10.0f;
	ctgt.y += cameraDirection.y*10.0f;
	cpos.y += cameraDirection.y*10.0f;
	ctgt.z += cameraDirection.z*10.0f;
	cpos.z += cameraDirection.z*10.0f;
	CheckCollision();
}


void DashRight() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x -= cameraDirection.z*10.0f;
	cpos.x -= cameraDirection.z*10.0f;
	ctgt.y -= cameraDirection.y*10.0f;
	cpos.y -= cameraDirection.y*10.0f;
	ctgt.z -= -cameraDirection.x*10.0f;
	cpos.z -= -cameraDirection.x*10.0f;
	CheckCollision();
}


void DashLeft() {
	VECTOR sub = VSub(cpos, ctgt);
	sub.y = 0;
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x += cameraDirection.z*10.0f;
	cpos.x += cameraDirection.z*10.0f;
	ctgt.y += cameraDirection.y*10.0f;
	cpos.y += cameraDirection.y*10.0f;
	ctgt.z += -cameraDirection.x*10.0f;
	cpos.z += -cameraDirection.x*10.0f;
	CheckCollision();
}

void RotateCamera() {
	int mouseX, mouseY, windowWidth, windowHeight;
	GetMousePoint(&mouseX, &mouseY);
	GetWindowSize(&windowWidth, &windowHeight);
	float deltaRotateX_degree = (float)(mouseX - preMouseX) * 360 / windowWidth;
	float deltaRotateY_degree = (float)(mouseY - preMouseY) * 360 / windowHeight;
	rotateX_degree -= deltaRotateX_degree;
	rotateY_degree -= deltaRotateY_degree;
	if (rotateY_degree >= 60)rotateY_degree = 60;
	if (rotateY_degree < -30)rotateY_degree = -30;

	cpos.x = ctgt.x + 100 * cos(MPI*rotateX_degree / 180);
	cpos.z = ctgt.z + 100 * sin(MPI*rotateX_degree / 180);
	ctgt.y = 100 * tan(MPI*rotateY_degree / 180);
	
	preMouseX = mouseX;
	preMouseY = mouseY;
}

void CheckCollision() {
	if (CheckHitSphere(cpos, cameraCollisionRadius)) {
		VECTOR nearPos = MostNearHitPos(cpos, cameraCollisionRadius);
		VECTOR sub = VSub(cpos, nearPos);
		float dis = VSize(sub);
		VECTOR subNorm = VNorm(sub);
		subNorm.y = 0;
		VECTOR moveVec = VScale(subNorm, abs((long)((cameraCollisionRadius-dis)*0.2f)));
		cpos = VAdd(cpos, moveVec);
		ctgt = VAdd(ctgt, moveVec);
	}

	int enemyModel = EnemyCheckHitSphere(cpos, cameraCollisionRadius);
	if (enemyModel != -1) {
		VECTOR nearPos = EnemyMostNearHitPos(cpos, cameraCollisionRadius, enemyModel);
		VECTOR sub = VSub(cpos, nearPos);
		float dis = VSize(sub);
		VECTOR subNorm = VNorm(sub);
		subNorm.y = 0;
		VECTOR moveVec = VScale(subNorm, abs((long)((cameraCollisionRadius - dis)*0.2f)));
		cpos = VAdd(cpos, moveVec);
		ctgt = VAdd(ctgt, moveVec);
	}
}

VECTOR GetCameraPos() {
	return cpos;
}
VECTOR GetCameraDirection() {
	return VNorm(VSub(ctgt, cpos));
}

float GetCameraCollisionRadius() {
	return cameraCollisionRadius;
}