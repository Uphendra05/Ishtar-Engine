#pragma once
#include <PxPhysicsAPI.h>
#include "../../model.h"
#include "../../CameraManager.h"

using namespace physx;


enum FrustumPlaneIndex
{
	FRUSTUM_PLANE_LEFT = 0,
	FRUSTUM_PLANE_RIGHT = 1,
	FRUSTUM_PLANE_TOP = 2,
	FRUSTUM_PLANE_BOTTOM = 3,
	FRUSTUM_PLANE_NEAR = 4,
	FRUSTUM_PLANE_FAR = 5,
};

struct OcculsionObject
{
	PxGeometryHolder	mGeom;
	PxTransform			mPose;

	PxBounds3           modelAABB;
	Model*              model = nullptr;
	PxU32 visibleIndex = -1;
};



struct LocalCB : PxBVH::OverlapCallback
{
	LocalCB()
	{
		mVisibles.reserve(10000);
	}

	virtual bool reportHit(PxU32 boundsIndex)
	{
		mVisibles.pushBack(boundsIndex);
		return true;
	}

	PxArray<PxU32>		mVisibles;
	LocalCB& operator=(const LocalCB&) { return *this; }
};

class OcculsionManager : public Entity
{
public:


	static OcculsionManager& GetInstance();
	OcculsionManager();
	~OcculsionManager();

	void InitializeOcculusion();
	void UpdateOcculsion();

private:

	void Start() override {};
	void Update(float deltaTime) override {};
	void OnDestroy() override {};
	void Render() override;

	void DrawProperties() override;
	void SceneDraw() override;

	void InitializeOcclusionModels();
	void CreateBVH();
	void UpdatePlanes();
	void UpdateDynamicsPosition();

	PxBounds3 GetModelAABB(Model* model);


	std::vector<OcculsionObject> listOfOcculsionObjects;
	std::vector<OcculsionObject> listOfDynamicOcculsionObjects;

	Camera* mainCamera = nullptr;
	PxBVH* mBVH = nullptr;
	PxPlane planes[6];

	bool isOcculsionIntialized = false;

};

