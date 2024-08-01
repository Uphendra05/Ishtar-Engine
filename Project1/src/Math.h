#pragma once
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
namespace MathUtils 
{
	class Math
	{
	public:
		static bool DecomposeTransform(const glm::mat4& transform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
		static int GetRandomIntNumber(int min, int max);
		static float GetRandomFloatNumber(float min, float max);
		static glm::vec2 randomInsideUnitCircle(float radius);
		static glm::vec2 randomInsideUnitCircle();
		static glm::vec3 randomInsideUnitSphereVec3();
		static float squareMagnitude(glm::vec2 value);
		static float squareMagnitudeVec3(glm::vec3 value);
		static glm::vec4 LerpVec4(const glm::vec4& start, const glm::vec4& end, float t);
		static glm::vec3 LerpVec3(const glm::vec3& start, const glm::vec3& end, float t);
		static glm::vec2 LerpVec2(const glm::vec2& start, const glm::vec2& end, float t);
		static float Lerp(float start,float end, float t);

		static float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
		static glm::vec2 SmoothDampVec2(glm::vec2 current, glm::vec2 target, glm::vec2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
		static glm::vec3 SmoothDampVec3(glm::vec3 current, glm::vec3 target, glm::vec3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
		static glm::vec4 SmoothDampVec4(glm::vec4 current, glm::vec4 target, glm::vec4& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
		static float DeltaAngle(float current, float target);
		static float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
		static float Remap(float value, float inputMin, float inputMax, float outputMin, float outputMax);

	};

}