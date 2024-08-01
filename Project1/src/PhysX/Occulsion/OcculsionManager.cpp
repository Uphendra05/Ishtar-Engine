#include "OcculsionManager.h"
#include "../../GraphicsRender.h"
#include "../PhysXUtils.h"

OcculsionManager& OcculsionManager::GetInstance()
{
	static OcculsionManager instance;
	return instance;
}

OcculsionManager::OcculsionManager()
{
	name = "Occulsion Manager";

	InitializeEntity(this);
}

OcculsionManager::~OcculsionManager()
{
	/*if (mBVH)
	{
		mBVH->release();
	}*/
}


void OcculsionManager::InitializeOcculusion()
{
	isOcculsionIntialized = true;

	mainCamera = CameraManager::GetInstance().GetMainCamera();

	InitializeOcclusionModels();

	CreateBVH();
}

void OcculsionManager::InitializeOcclusionModels()
{

	const std::vector<Model*> listOfModels = GraphicsRender::GetInstance().GetModelList();

	int i = 0;
	for (Model* model : listOfModels)
	{
		if (model->occulsionState == eOcculsionState::NO_OCCULSION)
		{
			continue;
		}

		OcculsionObject localObject;

		Transform* modelTransform = &model->transform;

		PxBounds3 aabb = GetModelAABB(model);

		aabb.minimum.x *= modelTransform->scale.x;
		aabb.minimum.y *= modelTransform->scale.y;
		aabb.minimum.z *= modelTransform->scale.z;

		aabb.maximum.x *= modelTransform->scale.x;
		aabb.maximum.y *= modelTransform->scale.y;
		aabb.maximum.z *= modelTransform->scale.z;



		PxBoxGeometry boxGeomentry(aabb.getDimensions() * 0.5f);

		PxTransform  transformPose = PxTransform(GLMToPxVec3(model->transform.position), GLMToPxQuat(model->transform.quaternionRotation));


		localObject.mGeom.storeAny(boxGeomentry);
		localObject.model = model;
		localObject.mPose = transformPose;
		localObject.visibleIndex = i;

		if (model->occulsionState == eOcculsionState::DYNAMIC)
		{
			listOfDynamicOcculsionObjects.push_back(localObject);
		}

		listOfOcculsionObjects.push_back(localObject);

		i++;
	}
}

void OcculsionManager::CreateBVH()
{

	const PxU32 nbObjects = listOfOcculsionObjects.size();

	PxBounds3* bounds = new PxBounds3[nbObjects];

	for (PxU32 i = 0; i < nbObjects; i++)
	{
		OcculsionObject& obj = listOfOcculsionObjects[i];

		PxGeometryQuery::computeGeomBounds(bounds[i], obj.mGeom.any(), obj.mPose);
	}


	PxBVHDesc bvhDesc;
	bvhDesc.bounds.count = nbObjects;
	bvhDesc.bounds.data = bounds;
	bvhDesc.bounds.stride = sizeof(PxBounds3);
	bvhDesc.enlargement = 0.0f;
	mBVH = PxCreateBVH(bvhDesc);
	delete[] bounds;
}

void OcculsionManager::UpdatePlanes()
{
	glm::mat4 view = mainCamera->GetViewMatrix();

	glm::mat4 projection = mainCamera->GetProjectionMatrix();

	glm::mat4 combined = projection * view;

	const PxMat44 combo = GLMToPxMat4(combined);

	planes[FRUSTUM_PLANE_LEFT].n.x = -(combo.column0[3] + combo.column0[0]);
	planes[FRUSTUM_PLANE_LEFT].n.y = -(combo.column1[3] + combo.column1[0]);
	planes[FRUSTUM_PLANE_LEFT].n.z = -(combo.column2[3] + combo.column2[0]);
	planes[FRUSTUM_PLANE_LEFT].d = -(combo.column3[3] + combo.column3[0]);

	planes[FRUSTUM_PLANE_RIGHT].n.x = -(combo.column0[3] - combo.column0[0]);
	planes[FRUSTUM_PLANE_RIGHT].n.y = -(combo.column1[3] - combo.column1[0]);
	planes[FRUSTUM_PLANE_RIGHT].n.z = -(combo.column2[3] - combo.column2[0]);
	planes[FRUSTUM_PLANE_RIGHT].d = -(combo.column3[3] - combo.column3[0]);

	planes[FRUSTUM_PLANE_TOP].n.x = -(combo.column0[3] - combo.column0[1]);
	planes[FRUSTUM_PLANE_TOP].n.y = -(combo.column1[3] - combo.column1[1]);
	planes[FRUSTUM_PLANE_TOP].n.z = -(combo.column2[3] - combo.column2[1]);
	planes[FRUSTUM_PLANE_TOP].d = -(combo.column3[3] - combo.column3[1]);

	planes[FRUSTUM_PLANE_BOTTOM].n.x = -(combo.column0[3] + combo.column0[1]);
	planes[FRUSTUM_PLANE_BOTTOM].n.y = -(combo.column1[3] + combo.column1[1]);
	planes[FRUSTUM_PLANE_BOTTOM].n.z = -(combo.column2[3] + combo.column2[1]);
	planes[FRUSTUM_PLANE_BOTTOM].d = -(combo.column3[3] + combo.column3[1]);

	planes[FRUSTUM_PLANE_NEAR].n.x = -(combo.column0[3] + combo.column0[2]);
	planes[FRUSTUM_PLANE_NEAR].n.y = -(combo.column1[3] + combo.column1[2]);
	planes[FRUSTUM_PLANE_NEAR].n.z = -(combo.column2[3] + combo.column2[2]);
	planes[FRUSTUM_PLANE_NEAR].d = -(combo.column3[3] + combo.column3[2]);

	planes[FRUSTUM_PLANE_FAR].n.x = -(combo.column0[3] - combo.column0[2]);
	planes[FRUSTUM_PLANE_FAR].n.y = -(combo.column1[3] - combo.column1[2]);
	planes[FRUSTUM_PLANE_FAR].n.z = -(combo.column2[3] - combo.column2[2]);
	planes[FRUSTUM_PLANE_FAR].d = -(combo.column3[3] - combo.column3[2]);


	for (PxU32 i = 0; i < 6; i++)
		planes[i].normalize();
}

void OcculsionManager::UpdateDynamicsPosition()
{
	if (listOfDynamicOcculsionObjects.size() == 0) return;

	PxBounds3* bounds = mBVH->getBoundsForModification();

	for (OcculsionObject& obj :  listOfDynamicOcculsionObjects)
	{

		Transform* modelTransform = &obj.model->transform;

		PxTransform modifiedPose = PxTransform(GLMToPxVec3(modelTransform->position), GLMToPxQuat(modelTransform->quaternionRotation));

		obj.mPose = modifiedPose;

		PxGeometryQuery::computeGeomBounds(bounds[obj.visibleIndex], obj.mGeom.any(), obj.mPose);
	}

	mBVH->refit();
	
}

void OcculsionManager::UpdateOcculsion()
{
	if (!isOcculsionIntialized) return;

	UpdateDynamicsPosition();

	UpdatePlanes();


	for (OcculsionObject& object :  listOfOcculsionObjects)
	{
		object.model->isOccluded = true;
	}

	if (mBVH)
	{
		
		LocalCB cb;

		mBVH->cull(6, planes, cb);

		for (size_t i = 0; i < cb.mVisibles.size() ; i++)
		{

			OcculsionObject& obj = listOfOcculsionObjects[cb.mVisibles[i]];

			if (obj.visibleIndex == cb.mVisibles[i])
			{
				obj.model->isOccluded = false;
			}
		}


	}
}


PxBounds3 OcculsionManager::GetModelAABB(Model* model)

{
	if (model->meshes.empty())
	{
		return PxBounds3{ PxVec3(0.0f), PxVec3(0.0f) };
	}

	PxBounds3 minMax;

	minMax.minimum = GLMToPxVec3(model->meshes[0]->vertices[0].Position);
	minMax.maximum = GLMToPxVec3(model->meshes[0]->vertices[0].Position);

	for (std::shared_ptr<Mesh> mesh : model->meshes)
	{
		PxBounds3 temp = CalculateAABB(mesh->vertices);

		minMax.minimum.x = PxMin(temp.minimum.x, minMax.minimum.x);
		minMax.minimum.y = PxMin(temp.minimum.y, minMax.minimum.y);
		minMax.minimum.z = PxMin(temp.minimum.z, minMax.minimum.z);

		minMax.maximum.x = PxMax(temp.maximum.x, minMax.maximum.x);
		minMax.maximum.y = PxMax(temp.maximum.y, minMax.maximum.y);
		minMax.maximum.z = PxMax(temp.maximum.z, minMax.maximum.z);
	}

	return PxBounds3(minMax.minimum, minMax.maximum);
}

void OcculsionManager::Render()
{
}

void OcculsionManager::DrawProperties()
{
	Entity::DrawProperties();
}

void OcculsionManager::SceneDraw()
{
	Entity::SceneDraw();

}