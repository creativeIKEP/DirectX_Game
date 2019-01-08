#include <DxLib.h>


int DroneInit();
void DroneDraw(int, VECTOR);


int DroneInit() {
	return MV1LoadModel("Enemy\\Drone\\drone.mv1");
}

void DroneDraw(int model, VECTOR pos) {
	MV1SetPosition(model, pos);
	MV1SetScale(model, VGet(5, 5, 5));
	MV1DrawModel(model);
}