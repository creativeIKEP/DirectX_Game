#include <DxLib.h>


int RobotInit();
void RobotDraw(int, VECTOR);


int RobotInit() {
	return MV1LoadModel("Enemy\\Robot\\robots.mv1");
}

void RobotDraw(int model, VECTOR pos) {
	MV1SetPosition(model, pos);
	MV1SetScale(model, VGet(20, 20, 20));
	MV1DrawModel(model);
}