#include <DxLib.h>
#include "FollowCamera.h"


void InputCheck();
void KeyInputCheck();

void InputCheck() {
	KeyInputCheck();
}


void KeyInputCheck() {
	if (CheckHitKey(KEY_INPUT_S)==1){
		MoveBack();
	}
	if (CheckHitKey(KEY_INPUT_W) == 1) {
		MoveForward();
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		MoveLeft();
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		MoveRight();
	}

	RotateCamera();
}