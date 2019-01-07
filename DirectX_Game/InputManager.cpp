#include <DxLib.h>
#include "FollowCamera.h"


void InputCheck() {
	
}


void CheckKeyInput() {
	int key;
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (key & PAD_INPUT_DOWN) {
		MoveBack();
	}
	if (key & PAD_INPUT_UP) {
		MoveForward();
	}
	if (key & PAD_INPUT_LEFT) {
		MoveLeft();
	}
	if (key & PAD_INPUT_RIGHT) {
		MoveRight();
	}

	RotateCamera();
}