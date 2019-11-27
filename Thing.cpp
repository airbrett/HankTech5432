#include "Thing.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Thing::Thing() :
	mRot()
{
	Draw = true;
	MatStale = true;
}

const glm::vec3& Thing::GetPos()
{
	return Pos;
}

void Thing::SetPos(const float x, const float y, const float z)
{
	Pos.x = x;
	Pos.y = y;
	Pos.z = z;

	MatStale = true;
}

void Thing::Turn(const glm::vec3& Rot)
{
	const glm::vec3 RotRad(glm::radians(Rot.x), glm::radians(Rot.y), glm::radians(Rot.z));

	mRot *= glm::quat(RotRad);

	MatStale = true;
}

void Thing::Move(const glm::vec3& Vec)
{
	Pos = Transform(Vec);
	MatStale = true;
}

const glm::mat4& Thing::GetMatrix()
{
	if (MatStale)
	{
		MatStale = false;

		mMat = glm::translate(glm::mat4(1.0f), Pos) * glm::mat4_cast(mRot);
	}

	return mMat;
}

bool Thing::DoDraw()
{
	return Draw;
}

glm::vec3 Thing::Transform(const glm::vec3& Pt)
{
	return GetMatrix() * glm::vec4(Pt, 1.0f);
}

glm::vec3 Thing::InverseTransform(const glm::vec3& Pt)
{
	return glm::inverse(GetMatrix()) * glm::vec4(Pt, 1.0f);
}
