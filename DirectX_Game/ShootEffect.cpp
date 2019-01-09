#include <DxLib.h>
#include <queue>

int shootEffect;
int shootStartTime = -1;
bool isShootEffectPlaying = false;
VECTOR ShootEffectPos;

void ShootEffectInit();
void ShootEffect();
void ShootEffectSet(VECTOR);


void ShootEffectInit() {
	shootEffect = LoadGraph("Effect\\eff_ring3.png");
}

void ShootEffect() {
	if (isShootEffectPlaying && shootStartTime<0) {
		shootStartTime = GetNowCount();
		SetDrawBright(255, 173, 144);
		DrawExtendGraph3D(ShootEffectPos.x, ShootEffectPos.y, ShootEffectPos.z, 0.1, 0.1, shootEffect, TRUE);
	}
	else if (isShootEffectPlaying && (GetNowCount()-shootStartTime)<0.05f*1000) {
		int shootDeltaTime = GetNowCount() - shootStartTime;
		double rate = 1 * shootDeltaTime / (0.05f * 1000);
		SetDrawBright(255, 173, 144);
		DrawExtendGraph3D(ShootEffectPos.x, ShootEffectPos.y, ShootEffectPos.z, rate, rate, shootEffect, TRUE);
	}
	else if (isShootEffectPlaying && (GetNowCount() - shootStartTime) >= 0.05f * 1000) {
		shootStartTime = -1;
		isShootEffectPlaying = false;
	}
}

void ShootEffectSet(VECTOR pos) {
	isShootEffectPlaying = true;
	ShootEffectPos = pos;
}