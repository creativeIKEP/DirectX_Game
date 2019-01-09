#include <DxLib.h>
#include <math.h>
#include <float.h>


int stage, collision;


bool StageInitialize();
int StageLoad();
void StageDraw();
bool CheckHitSphere(VECTOR, float);
VECTOR MostNearHitPos(VECTOR centerPos, float radius);


bool StageInitialize() {
	if (StageLoad() == -1) {
		return false;
	}
	return true;
}

int StageLoad() {
	stage = MV1LoadModel("Stage\\stagemap.mv1");
	if (stage == -1)return -1;
	collision = MV1LoadModel("Stage\\stagemap.mv1");
	if (collision == -1)return -1;

	if (MV1SetupCollInfo(collision, -1, 8, 8, 8) == -1)return -1;

	return 0;
}

void StageDraw() {
	MV1DrawModel(stage);
}

bool CheckHitSphere(VECTOR centerPos, float radius) {
	MV1_COLL_RESULT_POLY_DIM  HitPolyDim = MV1CollCheck_Sphere(collision, -1, centerPos, radius);
	if (HitPolyDim.HitNum >= 1) {
		MV1CollResultPolyDimTerminate(HitPolyDim);
		return true;
	}
	else { return false; }

}

VECTOR MostNearHitPos(VECTOR centerPos, float radius) {
	MV1_COLL_RESULT_POLY_DIM  HitPolyDim = MV1CollCheck_Sphere(collision, -1, centerPos, radius);
	VECTOR mostNearPos;
	if (HitPolyDim.HitNum >= 1)
	{
		float minDistance = FLT_MAX;
		// “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚Ì”‚¾‚¯ŒJ‚è•Ô‚µ
		for (int i = 0; i < HitPolyDim.HitNum; i++)
		{
			VECTOR sumVec = VAdd(VAdd(HitPolyDim.Dim[i].Position[0], HitPolyDim.Dim[i].Position[1]), HitPolyDim.Dim[i].Position[2]);
			VECTOR centerVec = VGet(sumVec.x / 3, sumVec.y / 3, sumVec.z / 3);
			if (i == 0)mostNearPos = centerVec;
			else {
				float distance = sqrtf((centerVec.x - centerPos.x)*(centerVec.x - centerPos.x) + (centerVec.y - centerPos.y)*(centerVec.y - centerPos.y) + (centerVec.z - centerPos.z)*(centerVec.z - centerPos.z));
				if (distance < minDistance) {
					minDistance = distance;
					mostNearPos = centerVec;
				}
			}
		}
	}
	MV1CollResultPolyDimTerminate(HitPolyDim);

	return mostNearPos;
}