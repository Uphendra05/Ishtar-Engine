#include "SoftBody.h"
#include "../../GraphicsRender.h"
#include "../PhysicsEngine.h"

SoftBodyObjs::SoftBodyObjs()
{
	

}

SoftBodyObjs::~SoftBodyObjs()
{
}

void SoftBodyObjs::InitializeSoftBody()
{

	PointAndConstraintsSetup();
	PhysicsEngine::GetInstance().AddSoftBody(this);
}

void SoftBodyObjs::SimulatePoints(float deltaTime)
{

	if (deltaTime > MAX_DELTATIME)
	{
		deltaTime = MAX_DELTATIME;
	}

	for (Point* point : m_ListOfPoints)
	{
		if (point->isLocked)
		{
			continue;
		}
		else
		{
			glm::vec3 currentPosition = point->curPosition;
			glm::vec3 prevPosition = point->oldPosition;

			point->curPosition += (currentPosition - prevPosition) + (this->acceleration * (float)(deltaTime * deltaTime));
			point->oldPosition = currentPosition;
		}

	}

}

void SoftBodyObjs::SimulateConstraints(float deltaTime)
{
	const unsigned int MAX_ITERATION = 3;

	for (size_t i = 0; i < MAX_ITERATION; i++)
	{
		for (Constraints* constraint : m_ListOfConstraints)
		{
			if (constraint->isActive)
			{

				Point* pointA = constraint->pointA;
				Point* pointB = constraint->pointB;

				glm::vec3 delta = pointB->curPosition - pointA->curPosition;

				float deltaLength = glm::length(delta);

				if (deltaLength != 0)
				{
					float diff = (deltaLength - constraint->length) / deltaLength;


					if (!pointA->isLocked)
					{
						pointA->curPosition += delta * 0.5f * diff * tightnessFactor;
					}


					if (!pointB->isLocked)
					{
						pointB->curPosition -= delta * 0.5f * diff * tightnessFactor;
					}


					CleanZeroes(pointA->curPosition);
					CleanZeroes(pointB->curPosition);
				}


				

			}

		}
	}


}

void SoftBodyObjs::StartSimultaion(float deltaTime)
{
	SimulatePoints(deltaTime);
	SimulateConstraints(deltaTime);
	//UpdateMeshVertices();
}

void SoftBodyObjs::PointAndConstraintsSetup()
{

	for (std::shared_ptr<Mesh> mesh : meshes)
	{
		CalculateMatrixForVertices(mesh);
		SetupPoints(mesh);
		SetupConstraints(mesh);

	}




}

void SoftBodyObjs::UpdateMeshVertices()
{
	for (Point* point : m_ListOfPoints)
	{
		glm::vec4 vertexMatrix = glm::vec4(point->curPosition, 1.0f);

		glm::mat4 modelInversematrix = transform.GetModelInverseMatrix();
		vertexMatrix = modelInversematrix * vertexMatrix;
		
		point->vertexData->Position = glm::vec3(vertexMatrix.x, vertexMatrix.y, vertexMatrix.z);

	}

	UpdateNormals();

	for (std::shared_ptr<Mesh> mesh : meshes)
	{
		mesh->UpdateVertices();
	}


}

void SoftBodyObjs::CalculateMatrixForVertices(std::shared_ptr<Mesh> vertSize) const
{

	for (size_t index = 0; index < vertSize->vertices.size(); index++)
	{
		glm::vec4 vertexMatrix = glm::vec4(vertSize->vertices[index].Position, 1.0f);

		vertexMatrix = transform.GetModelMatrix() * vertexMatrix;

		vertSize->vertices[index].Position = vertexMatrix;
		
	}


}

void SoftBodyObjs::SetupPoints(std::shared_ptr<Mesh> vertSize)
{
	m_ListOfPoints.reserve(vertSize->vertices.size());

	for (Vertex& pVert : vertSize->vertices)
	{

		Point* temp = new Point();

		temp->curPosition = pVert.Position;
		temp->oldPosition = temp->curPosition;
		temp->vertexData = &pVert;

		m_ListOfPoints.push_back(temp);

	}

}

void SoftBodyObjs::SetupConstraints(std::shared_ptr<Mesh> vertSize)
{

	for (size_t i = 0; i < vertSize->indices.size(); i += 3)
	{
		Triangle tempTri;

		tempTri.v1 = vertSize->vertices[vertSize->indices[i]].Position;
		tempTri.v2 = vertSize->vertices[vertSize->indices[i + 1]].Position;
		tempTri.v3 = vertSize->vertices[vertSize->indices[i + 2]].Position;

		tempTri.normal = (vertSize->vertices[vertSize->indices[i]].Normal +
			vertSize->vertices[vertSize->indices[i + 1]].Normal +
			vertSize->vertices[vertSize->indices[i + 2]].Normal) / 3.0f;

		tempTri.CalculateMidpoint();
		m_ListOfTriangles.push_back(tempTri);



		Point* point1 = m_ListOfPoints[vertSize->indices[i]];
		Point* point2 = m_ListOfPoints[vertSize->indices[i + 1]];
		Point* point3 = m_ListOfPoints[vertSize->indices[i + 2]];

		Constraints* edge1 = new Constraints(point1, point2);	
		Constraints* edge2 = new Constraints(point2, point3);	
		Constraints* edge3 = new Constraints(point3, point1);
		

		m_ListOfConstraints.push_back(edge1);
		m_ListOfConstraints.push_back(edge2);
		m_ListOfConstraints.push_back(edge3);

	}

}

void SoftBodyObjs::CalculateMatrixForMeshPoints(std::shared_ptr<Mesh> vertSize) const
{
}	

void SoftBodyObjs::DrawProperties()
{
	float width = 150;

	Model::DrawProperties();
	DrawTransformVector3ImGui("Acceleration", acceleration, 0, width);

	if (!ImGui::TreeNodeEx("Softbody properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGui::Text("Show Debug");
	ImGui::SameLine();
	ImGui::Checkbox("##ShowDebug", &showDebug);

	ImGui::Text("tightnessFactor");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(150);
	ImGui::InputFloat("##tightnessFactor", &tightnessFactor, 0, 0.1, "%.2f");

	ImGui::Text("LockRadius");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(150);
	ImGui::InputFloat("##lockRadius", &lockRadius, 0, 0.1, "%.2f");



	ImGui::SetNextItemWidth(80);
	ImGui::Text("LockCentre");
	ImGui::SameLine();
	ImGui::Text("X");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80);
	ImGui::DragFloat("##X", &lockSphereCenter.x);
	ImGui::SameLine();
	ImGui::Text("Y");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80);
	ImGui::DragFloat("###Y", &lockSphereCenter.y);
	ImGui::SameLine();
	ImGui::Text("Z");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80);
	ImGui::DragFloat("###Z", &lockSphereCenter.z);


	ImGui::NewLine();
	ImGui::TreePop();

	if (!ImGui::TreeNodeEx("List of points ", ImGuiTreeNodeFlags_OpenOnArrow))
	{
		return;
	}
	for (int i = 0; i < m_ListOfPoints.size(); ++i)
	{
		Point*& point = m_ListOfPoints[i];


		ImGui::Text("locked");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::Checkbox(("##locked" + std::to_string(i)).c_str(), &point->isLocked);




		ImGui::SetNextItemWidth(80);
		ImGui::Text("points");
		ImGui::SameLine();
		ImGui::Text("X");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::DragFloat(("##X" + std::to_string(i)).c_str(), &point->curPosition.x);
		ImGui::SameLine();
		ImGui::Text("Y");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::DragFloat(("###Y" + std::to_string(i)).c_str(), &point->curPosition.y);
		ImGui::SameLine();
		ImGui::Text("Z");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::DragFloat(("###Z" + std::to_string(i)).c_str(), &point->curPosition.z);

		ImGui::NewLine();
	}
	ImGui::TreePop();
}

void SoftBodyObjs::SceneDraw()
{
	Model::SceneDraw();
}

void SoftBodyObjs::AddLockSphere(unsigned int Index, float radius)
{
	lockSphereCenter = m_ListOfPoints[Index]->curPosition;
	lockRadius = radius;

	LockPoint(Index, radius);

}

void SoftBodyObjs::LockPoint(unsigned int Index, float radius)
{
	if (Index < 0 || Index >= m_ListOfPoints.size())
	{

		return;
	}

	for (size_t i = 0; i < m_ListOfPoints.size(); ++i) {
		// Calculate the squared distance between the points
		float squaredDistance = glm::distance2(
			glm::vec3(m_ListOfPoints[i]->curPosition.x, m_ListOfPoints[i]->curPosition.y, m_ListOfPoints[i]->curPosition.z),
			glm::vec3(m_ListOfPoints[Index]->curPosition.x, m_ListOfPoints[Index]->curPosition.y, m_ListOfPoints[Index]->curPosition.z)
		);


		if (squaredDistance <= radius * radius) {
			m_ListOfPoints[i]->isLocked = true;
		}
	}



	/*for (unsigned int index : listOfIndex)
	{
		if (index >= 0 && index < m_ListOfPoints.size())
		{
			m_ListOfPoints[index]->isLocked = true;
		}
	}*/



	/*for (size_t i = 0; i < m_ListOfPoints.size(); i++)
	{
		if (index >= 0 && index < m_ListOfPoints.size())
		{
			m_ListOfPoints[index]->isLocked = true;
			
		}

	}*/

}

void SoftBodyObjs::Start()
{

}

void SoftBodyObjs::Update(float deltaTime)
{
	
}

void SoftBodyObjs::Render()
{
	if (!showDebug) return;

	for (Point* point : m_ListOfPoints)
	{
		GraphicsRender::GetInstance().DrawSphere(point->curPosition, renderRadius, glm::vec4(0, 1, 1, 1), true);
	}

	for (Constraints* stick : m_ListOfConstraints)
	{
		GraphicsRender::GetInstance().DrawLine(stick->pointA->curPosition, stick->pointB->curPosition, glm::vec4(1, 1, 0, 1));
	}

	GraphicsRender::GetInstance().DrawSphere(lockSphereCenter, lockRadius, glm::vec4(1, 0, 0, 1), true);
}

void SoftBodyObjs::OnDestroy()
{
}

void SoftBodyObjs::CleanZeroes(glm::vec3& value)
{
	// 1.192092896e–07F 
	const float minFloat = 1.192092896e-07f;
	if ((value.x < minFloat) && (value.x > -minFloat))
	{
		value.x = 0.0f;
	}	
	if ((value.y < minFloat) && (value.y > -minFloat))
	{
		value.y = 0.0f;
	}
	if ((value.z < minFloat) && (value.z > -minFloat))
	{
		value.z = 0.0f;
	}

}

void SoftBodyObjs::UpdateNormals()
{

	for (std::shared_ptr<Mesh> mesh : meshes)
	{

		for (size_t i = 0; i < mesh->vertices.size(); i++)
		{
			mesh->vertices[i].Normal = glm::vec3(0);
		}
	}

	for (std::shared_ptr<Mesh> mesh : meshes)
	{
		for (size_t i = 0; i < mesh->indices.size(); i += 3)
		{
			unsigned int vertAIndex = mesh->indices[i + 0];
			unsigned int vertBIndex = mesh->indices[i + 1];
			unsigned int vertCIndex = mesh->indices[i + 2];


			Vertex& vertexA = mesh->vertices[vertAIndex];
			Vertex& vertexB = mesh->vertices[vertBIndex];
			Vertex& vertexC = mesh->vertices[vertCIndex];

			glm::vec3 vertA = vertexA.Position;
			glm::vec3 vertB = vertexB.Position;
			glm::vec3 vertC = vertexC.Position;

			glm::vec3 triangleEdgeAtoB = vertB - vertA;
			glm::vec3 triangleEdgeAtoC = vertC - vertA;


			glm::vec3 normal = glm::normalize(glm::cross(triangleEdgeAtoB, triangleEdgeAtoC));


			CleanZeroes(normal);

			{
				vertexA.Normal.x += normal.x;
				vertexA.Normal.y += normal.y;
				vertexA.Normal.z += normal.z;

				vertexB.Normal.x += normal.x;
				vertexB.Normal.y += normal.y;
				vertexB.Normal.z += normal.z;

				vertexC.Normal.x += normal.x;
				vertexC.Normal.y += normal.y;
				vertexC.Normal.z += normal.z;
			}



		}

	}
}
