#include <DxLib.h>


int model;
VECTOR pos;


int DroneInit();
void DroneDraw(int, VECTOR);


int DroneInit() {
	int model = MV1LoadModel("Enemy\\Drone\\drone.mv1");
	return model;
}

void DroneDraw(int model, VECTOR pos) {
	MV1SetPosition(model, pos);
	MV1SetScale(model, VGet(5, 5, 5));
	MV1DrawModel(model);
}