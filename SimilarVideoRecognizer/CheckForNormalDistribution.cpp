#include "stdafx.h"
#include "CheckForNormalDistribution.h"
#include <vector>
#include <iostream>


CheckForNormalDistribution::CheckForNormalDistribution()
{
}


CheckForNormalDistribution::~CheckForNormalDistribution()
{
}

void CheckForNormalDistribution::CountForPoints()
{
	std::vector <double> vec;
	vec.resize(10000);
	HashFunction::diceGaussForVector(vec);
	int count1 = 0, count2 = 0, count3 = 0;
	for (auto iter = vec.begin(); iter != vec.end(); ++iter)
	{
		if (fabs(*iter) < 2.58) count1++;
		if (fabs(*iter) < 1.96) count2++;
		if (fabs(*iter) < 1) count3++;
	}
	std::cout << count1 << " " << count2 << " " << count3 <<  std::endl;
}