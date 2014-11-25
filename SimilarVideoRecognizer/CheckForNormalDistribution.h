#pragma once
#include "GroupOfHashFunction.h"
class CheckForNormalDistribution :
	public HashFunction
{
public:
	CheckForNormalDistribution();
	~CheckForNormalDistribution();
	static void CountForPoints();
};

