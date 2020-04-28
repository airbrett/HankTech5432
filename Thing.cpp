#include "Thing.h"

#include "Physics.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Thing::Thing() :
	mRot(),
	mDeRez(false)
{
	PhysicalHandle = INVALID_HANDLE;
	Gfx.mVtx = INVALID_HANDLE;

	Draw = true;
	MatStale = true;
}

const glm::vec3& Thing::GetPos()
{
	return mPos;
}

void Thing::SetPos(const glm::vec3& Pos)
{
	mPos = Pos;

	MatStale = true;
}

const glm::vec3 Thing::GetRot()
{
	return glm::eulerAngles(mRot);
}

void Thing::Turn(const glm::vec3& Rot)
{
	const glm::vec3 RotRad(glm::radians(Rot.x), glm::radians(Rot.y), glm::radians(Rot.z));

	mRot *= glm::quat(RotRad);

	MatStale = true;
}

void Thing::Move(const glm::vec3& Vec)
{
	mPos = TransformPoint(Vec);
	MatStale = true;
}

const glm::mat4& Thing::GetMatrix()
{
	if (MatStale)
	{
		MatStale = false;

		mMat = glm::translate(glm::mat4(1.0f), mPos) * glm::mat4_cast(mRot);
	}

	return mMat;
}

bool Thing::DoDraw()
{
	return Draw;
}

glm::vec3 Thing::TransformRotation(const glm::vec3& Rot)
{
	return mRot * Rot;
}

glm::vec3 Thing::InverseTransformRotation(const glm::vec3& Rot)
{
	return Rot * mRot;
}

glm::vec3 Thing::TransformPoint(const glm::vec3& Pt)
{
	return GetMatrix() * glm::vec4(Pt, 1.0f);
}

glm::vec3 Thing::InverseTransformPoint(const glm::vec3& Pt)
{
	return glm::inverse(GetMatrix()) * glm::vec4(Pt, 1.0f);
}

glm::vec3 Thing::TransformVector(const glm::vec3& Vec)
{
	return mRot * Vec;
}

glm::vec3 Thing::InverseTransformVector(const glm::vec3& Vec)
{
	return Vec * mRot;
}

void Thing::DeRez()
{
	mDeRez = true;
}

bool Thing::PendingDeRez()
{
	return mDeRez;
}

void Thing::SetID(const std::size_t ID)
{
	mID = ID;
}

std::size_t Thing::GetID()
{
	return mID;
}
