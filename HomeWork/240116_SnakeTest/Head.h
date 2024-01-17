#pragma once
#include <ConsoleEngine/ConsoleObject.h>
#include <vector>

class Head : public ConsoleObject
{
public:
	void Move();
	void BodyCollisionCheck();
	void WallCollisionCheck();

protected:

	void Update() override;
	int2 PrevDir = { 0, 0 };
	std::vector<class Body*> TailBody;
};

