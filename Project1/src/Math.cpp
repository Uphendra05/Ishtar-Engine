#include "Math.h"
#include <glm/gtx/matrix_decompose.hpp>

using namespace MathUtils;

bool Math::DecomposeTransform(const glm::mat4& transform, glm::vec3& position,  glm::vec3& rotation, glm::vec3& scale)
{
	// From glm::decompose in matrix_decompose.inl

	using namespace glm;
	using T = float;

	mat4 LocalMatrix(transform);

	// Normalize the matrix.
	if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
		return false;

	// First, isolate perspective.  This is the messiest.
	if (
		epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
		epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
		epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
	{
		// Clear the perspective partition
		LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
		LocalMatrix[3][3] = static_cast<T>(1);
	}

	// Next take care of translation (easy).
	position = vec3(LocalMatrix[3]);
	LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

	vec3 Row[3], Pdum3;

	// Now get scale and shear.
	for (length_t i = 0; i < 3; ++i)
		for (length_t j = 0; j < 3; ++j)
			Row[i][j] = LocalMatrix[i][j];

	// Compute X scale factor and normalize first row.
	scale.x = length(Row[0]);
	Row[0] = detail::scale(Row[0], static_cast<T>(1));
	scale.y = length(Row[1]);
	Row[1] = detail::scale(Row[1], static_cast<T>(1));
	scale.z = length(Row[2]);
	Row[2] = detail::scale(Row[2], static_cast<T>(1));

	// At this point, the matrix (in rows[]) is orthonormal.
	// Check for a coordinate system flip.  If the determinant
	// is -1, then negate the matrix and the scaling factors.
#if 0
	Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
	if (dot(Row[0], Pdum3) < 0)
	{
		for (length_t i = 0; i < 3; i++)
		{
			scale[i] *= static_cast<T>(-1);
			Row[i] *= static_cast<T>(-1);
		}
	}
#endif

	rotation.y = asin(-Row[0][2]);
	if (cos(rotation.y) != 0) {
		rotation.x = atan2(Row[1][2], Row[2][2]);
		rotation.z = atan2(Row[0][1], Row[0][0]);
	}
	else {
		rotation.x = atan2(-Row[2][0], Row[1][1]);
		rotation.z = 0;
	}


	return true;
}

int MathUtils::Math::GetRandomIntNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define the distribution for the specified range
	std::uniform_int_distribution<int> distribution(min, max);

	// Generate and return a random number
	return distribution(gen);
}


float MathUtils::Math::GetRandomFloatNumber(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());

	// Use std::uniform_real_distribution for floating-point numbers
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(gen);
}

glm::vec2 MathUtils::Math::randomInsideUnitCircle(float radius)
{
	glm::vec2 randomPoint = glm::diskRand(radius);

	return randomPoint;
}

glm::vec2 MathUtils::Math::randomInsideUnitCircle()
{
	glm::vec2 randomPoint = glm::diskRand(1.0f);
	return randomPoint;
}

glm::vec3 MathUtils::Math::randomInsideUnitSphereVec3()
{
	glm::vec3 randomPoint = glm::ballRand(1.0f);
	return randomPoint;
}

float MathUtils::Math::squareMagnitude(glm::vec2 value)
{
	return value.x * value.x + value.y * value.y;
}

float MathUtils::Math::squareMagnitudeVec3(glm::vec3 value)
{
	return value.x * value.x + value.y * value.y + value.z * value.z;

}

glm::vec4 MathUtils::Math::LerpVec4(const glm::vec4& start, const glm::vec4& end, float t)
{
	return start + t * (end - start);
}

glm::vec3 MathUtils::Math::LerpVec3(const glm::vec3& start, const glm::vec3& end, float t)
{
	return start + t * (end - start);
}

glm::vec2 MathUtils::Math::LerpVec2(const glm::vec2& start, const glm::vec2& end, float t)
{
	return start + t * (end - start);
}

float MathUtils::Math::Lerp(float start, float end, float t)
{
	return  start + t * (end - start);
}

float MathUtils::Math::SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	maxSpeed = std::abs(maxSpeed);
	smoothTime = std::max(0.0001f, smoothTime);

	float omega = 2.0f / smoothTime;

	float x = omega * deltaTime;
	float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);


	float change = current - target;
	float originalTo = target;

	float maxChange = maxSpeed * smoothTime;
	change = glm::clamp(change, -maxChange, maxChange);
	target = current - change;


	float temp = (currentVelocity + omega * change) * deltaTime;
	currentVelocity = (currentVelocity - omega * temp) * exp;

	float output = target + (change + temp) * exp;
	if (originalTo - current > 0.0f == output > originalTo) {
		currentVelocity = 0.0f;
		output = originalTo;
	}

	return output;
}

glm::vec2 MathUtils::Math::SmoothDampVec2(glm::vec2 current, glm::vec2 target, glm::vec2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	return glm::vec2(
		SmoothDamp(current.x, target.x, currentVelocity.x, smoothTime, maxSpeed, deltaTime),
		SmoothDamp(current.y, target.y, currentVelocity.y, smoothTime, maxSpeed, deltaTime)
	);
}

glm::vec3 MathUtils::Math::SmoothDampVec3(glm::vec3 current, glm::vec3 target, glm::vec3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	return glm::vec3(
		SmoothDamp(current.x, target.x, currentVelocity.x, smoothTime, maxSpeed, deltaTime),
		SmoothDamp(current.y, target.y, currentVelocity.y, smoothTime, maxSpeed, deltaTime),
		SmoothDamp(current.z, target.z, currentVelocity.z, smoothTime, maxSpeed, deltaTime)
	);
}

glm::vec4 MathUtils::Math::SmoothDampVec4(glm::vec4 current, glm::vec4 target, glm::vec4& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	return glm::vec4(
		SmoothDamp(current.x, target.x, currentVelocity.x, smoothTime, maxSpeed, deltaTime),
		SmoothDamp(current.y, target.y, currentVelocity.y, smoothTime, maxSpeed, deltaTime),
		SmoothDamp(current.z, target.z, currentVelocity.z, smoothTime, maxSpeed, deltaTime),
		SmoothDamp(current.w, target.w, currentVelocity.w, smoothTime, maxSpeed, deltaTime)
	);
}

float MathUtils::Math::DeltaAngle(float current, float target)
{
	float delta = target - current;
	if (delta > 180.0f)
	{
		delta -= 360.0f;
	}
	else if (delta< -180.0f)
	{
		delta += 360.0f;
	}
	return delta;
}

float MathUtils::Math::SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	float deltaAngle = DeltaAngle(current, target);

	// Clamp the delta angle to ensure smooth movement
	deltaAngle =glm::clamp(deltaAngle, -maxSpeed * deltaTime, maxSpeed * deltaTime);

	// Calculate the target angle based on the clamped delta angle
	target = current - deltaAngle;

	// Smoothly interpolate towards the target angle
	return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

float MathUtils::Math::Remap(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
	// Ensure that the value is within the input range
	value = glm::clamp(value, inputMin, inputMax);

	// Map the value from the input range to the output range
	float inputRange = inputMax - inputMin;
	float outputRange = outputMax - outputMin;
	return ((value - inputMin) / inputRange) * outputRange + outputMin;
}

