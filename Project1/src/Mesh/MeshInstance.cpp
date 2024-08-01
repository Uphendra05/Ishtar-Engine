#include "MeshInstance.h"

void MeshInstance::Draw(Shader* shader)
{
    if (!isVisible)
    {
        return;
    }

    shader->Bind();
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        shader->Bind();
        meshes[i]->meshMaterial->UpdateMaterial(shader);
       
        meshes[i]->VAO->Bind();
        meshes[i]->IBO->Bind();
        if (isWireFrame)
        {
            GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
        }
        else
        {
            GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
        }

        const unsigned int numberCount = listOfMatices.size();

        if (numberCount == 0) return;


        shader->setMat4("instanceModel", numberCount, GL_FALSE, glm::value_ptr(listOfMatices[0]));

        GLCALL(glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(meshes[i]->indices.size()), GL_UNSIGNED_INT,nullptr, numberCount));

        meshes[i]->VAO->Unbind();
    }
}

void MeshInstance::AddTransformData(const TransformData& transformData)
{

	glm::vec3 position = transformData.position;
	glm::quat quatRotation = glm::quat(glm::radians(transformData.rotation));
	glm::vec3 scale = transformData.scale;
	glm::mat4 rotation = glm::mat4_cast(quatRotation);

	glm::mat4 transformedMatrix =   glm::translate(glm::mat4(1.0f), position) * rotation *
		glm::scale(glm::mat4(1.0f), scale);


	listOfMatices.push_back(transformedMatrix);
	meshTransformDataList.push_back(transformData);
}

void MeshInstance::AddTransformData(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3 scale)
{
    glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(rotation)));

    glm::mat4 transformedMatrix = glm::translate(glm::mat4(1.0f), position) * rotationMatrix *
        glm::scale(glm::mat4(1.0f), scale);

    listOfMatices.push_back(transformedMatrix);
    meshTransformDataList.push_back(TransformData(position, rotation,scale));
}

void MeshInstance::DrawProperties()
{
    Model::DrawProperties();
}

void MeshInstance::SceneDraw()
{
    Model::SceneDraw();
}
