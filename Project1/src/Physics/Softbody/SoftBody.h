#pragma once
#ifndef SOFTBODY_H
#define SOFTBODY_H


#include "../../src/model.h"
#include <vector>

enum class SoftbodyTypes
{
	VERTEX = 0,
	MESH = 1
};

struct Point
{
	Point() = default;

	glm::vec3 curPosition = glm::vec3(0.0f);
	glm::vec3 oldPosition = glm::vec3(0.0f);

	Vertex* vertexData = nullptr;
	bool isLocked = false;
};


struct Constraints
{
	Constraints() = default;
	Constraints(Point* pA, Point* pB) : pointA(pA), pointB(pB) 
	{
		length = glm::distance(pointA->curPosition, pointB->curPosition);
	
	};

	Point* pointA;
	Point* pointB;

	float length = 0;
	bool isActive = true;
};





class SoftBodyObjs : public Model
{

public:

	SoftBodyObjs() ;
	~SoftBodyObjs();

	bool isSoftBodyActive = true;

	void InitializeSoftBody();

	void SimulatePoints(float deltaTime);
	void SimulateConstraints(float deltaTime);
	void StartSimultaion(float deltaTime);

	void AddLockSphere(unsigned int Index, float radius);
	void LockPoint(unsigned int Index, float radius);

	void PointAndConstraintsSetup();

	void UpdateMeshVertices();


	void CalculateMatrixForVertices(std::shared_ptr<Mesh> vertSize) const;
	void SetupPoints(std::shared_ptr<Mesh> vertSize);
	void SetupConstraints(std::shared_ptr<Mesh> vertSize);

	// Softbody for mesh

	// void Setup mesh of points and constraints
	// CalculateMatrixForVertices
	// update mesh

	void CalculateMatrixForMeshPoints(std::shared_ptr<Mesh> vertSize) const;

	void DrawProperties()override;
	void SceneDraw()override;

	 void Start() override;
	 void Update(float deltaTime) override;
	 void Render()override;
	 void OnDestroy()override;

	 struct Triangle
	 {
		 Triangle() {}
		 Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 normal)
		 {
			 this->v1 = v1;
			 this->v2 = v2;
			 this->v3 = v3;
			 this->normal = normal;
			 CalculateMidpoint();
		 }

		 glm::vec3 v1;
		 glm::vec3 v2;
		 glm::vec3 v3;
		 glm::vec3 normal;
		 glm::vec3 center;

		 glm::vec3 CalculateMidpoint()
		 {
			 center = (v1 + v2 + v3) / 3.0f;
			 return center;
		 }

		 Triangle& operator=(const Triangle& other)
		 {
			 if (this != &other)
			 {
				 v1 = other.v1;
				 v2 = other.v2;
				 v3 = other.v3;
				 normal = other.normal;
				 center = other.center;
			 }
			 return *this;
		 }

	 };
	 glm::vec3 acceleration = glm::vec3(0.0f, -1.0f, 0.0f);

private:

	bool showDebug = false;
	float tightnessFactor = 1;


	void CleanZeroes(glm::vec3& value);
	void UpdateNormals();

	const double MAX_DELTATIME = 1.0 / 60.0;

	float renderRadius = 0.025f;
	float lockRadius;
	glm::vec3 lockSphereCenter;


	std::vector<Triangle> m_ListOfTriangles;
	std::vector<Point*> m_ListOfPoints;
	std::vector<Constraints*> m_ListOfConstraints;

	// Beads Simulation

	


};

#endif // SOFTBODY_H