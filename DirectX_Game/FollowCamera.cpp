#include <DxLib.h>

VECTOR cpos = VGet(-600.0f, 100.0f, 0.0f), ctgt = VGet(-500.0f, 100.0f, 0.0f);


void SetCamera() {
	SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));
}


void MoveForward() {
	VECTOR sub = VSub(cpos, ctgt);
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x -= cameraDirection.x*4.0f;
	cpos.x -= cameraDirection.x*4.0f;
	ctgt.y -= cameraDirection.y*4.0f;
	cpos.y -= cameraDirection.y*4.0f;
	ctgt.z -= cameraDirection.z*4.0f;
	cpos.z -= cameraDirection.z*4.0f;
}


void MoveBack() {
	VECTOR sub = VSub(cpos, ctgt);
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x += cameraDirection.x*4.0f;
	cpos.x += cameraDirection.x*4.0f;
	ctgt.y += cameraDirection.y*4.0f;
	cpos.y += cameraDirection.y*4.0f;
	ctgt.z += cameraDirection.z*4.0f;
	cpos.z += cameraDirection.z*4.0f;
}


void MoveRight() {
	VECTOR sub = VSub(cpos, ctgt);
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x -= cameraDirection.z*4.0f;
	cpos.x -= cameraDirection.z*4.0f;
	ctgt.y -= cameraDirection.y*4.0f;
	cpos.y -= cameraDirection.y*4.0f;
	ctgt.z -= -cameraDirection.x*4.0f;
	cpos.z -= -cameraDirection.x*4.0f;
}


void MoveLeft() {
	VECTOR sub = VSub(cpos, ctgt);
	VECTOR cameraDirection = VNorm(sub);
	ctgt.x += cameraDirection.z*4.0f;
	cpos.x += cameraDirection.z*4.0f;
	ctgt.y += cameraDirection.y*4.0f;
	cpos.y += cameraDirection.y*4.0f;
	ctgt.z += -cameraDirection.x*4.0f;
	cpos.z += -cameraDirection.x*4.0f;
}