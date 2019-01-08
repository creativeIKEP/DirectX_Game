#include <DxLib.h>
#include "FollowCamera.h"


void InputCheck();
void KeyInputCheck();

void InputCheck() {
	KeyInputCheck();
}


void KeyInputCheck() {
	if (CheckHitKey(KEY_INPUT_S)==1){
		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
			DashBack();
		}
		else {
			MoveBack();
		}
	}
	if (CheckHitKey(KEY_INPUT_W) == 1) {
		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
			DashForward();
		}
		else {
			MoveForward();
		}
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
			DashLeft();
		}
		else {
			MoveLeft();
		}
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
			DashRight();
		}
		else {
			MoveRight();
		}
	}

	RotateCamera();
}