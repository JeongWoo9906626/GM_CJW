#pragma once
#include "Part.h"
#include <vector>

class Head : public Part
{
public:
	void Move();

protected:
	void Update() override;
	int2 PrevDir = { 0, 0 };
	std::vector<class Body*> TailBody;
};

