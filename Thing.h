#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Thing //To be rezzed by a user
{
protected:
	glm::vec3 Pos;
	glm::quat mRot;
	glm::mat4 mMat;
	bool Draw;
	bool MatStale;

public:
	Thing();

	const glm::vec3& GetPos();
	void SetPos(const float x, const float y, const float z);
	void Turn(const glm::vec3& Rot);
	void Move(const glm::vec3& Vec);
	const glm::mat4& GetMatrix();
	virtual void Update(const float dt) {}
	bool DoDraw();

	glm::vec3 Transform(const glm::vec3& Pt);
	glm::vec3 InverseTransform(const glm::vec3& Pt);
};
