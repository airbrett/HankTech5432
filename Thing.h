#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Thing //To be rezzed by a user
{
protected:
	glm::vec3 mPos;
	glm::quat mRot;
	glm::mat4 mMat;
	bool Draw;
	bool MatStale;
	bool mDeRez;

public:
	static const std::size_t INVALID_HANDLE = std::numeric_limits<std::size_t>::max();

	Thing();

	std::size_t PhysicalHandle;
	struct
	{
		size_t mIdxCount;
		size_t mTex;
		size_t mVtx;
		size_t mIdx;
	} Gfx;

	const glm::vec3& GetPos();
	const glm::vec3 GetRot();
	void SetPos(const glm::vec3& Pos);
	void Turn(const glm::vec3& Rot);
	void Move(const glm::vec3& Vec);
	const glm::mat4& GetMatrix();
	virtual void Update(const double dt) {}
	bool DoDraw();
	void DeRez();
	bool PendingDeRez();

	glm::vec3 TransformRotation(const glm::vec3& Rot);
	glm::vec3 InverseTransformRotation(const glm::vec3& Rot);
	glm::vec3 TransformPoint(const glm::vec3& Pt);
	glm::vec3 InverseTransformPoint(const glm::vec3& Pt);
	glm::vec3 TransformVector(const glm::vec3& Vec);
	glm::vec3 InverseTransformVector(const glm::vec3& Vec);
};
