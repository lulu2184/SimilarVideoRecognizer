// SimilarVideoRecognizer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SampleExtracter.h"
#include "OSIDGenerater.h"
#include "LayerOfEigenvector.h"
#include "GroupOfHashValueVector.h"
#include "GroupOfHashFunction.h"
#include "TrieTree.h"
#include "CheckForNormalDistribution.h"
#include <fstream>

void ResetHashFunctionFromFile(const std::string &filename)
{
	std::ifstream ifs("D:\\programming\\TEST\\HashFunctions.txt");
	for (int i = 0; i < GroupOfHashFunction::NumberOfFunctionGroups; ++i)
	{
		std::vector<std::vector<double>> a;
		std::vector<double> b;
		double x;
		a.resize(GroupOfHashFunction::FunctionsPerGroup);
		auto iter = a.begin();
		for (int j = 0; j < GroupOfHashFunction::FunctionsPerGroup; ++j)
		{
			for (int k = 0; k < LayerOfEigenvector::SizeOfEigenvector; ++k)
			{
				ifs >> x;
				iter->push_back(x);
			}
			ifs >> x;
			b.push_back(x);
			ifs >> x;
			++iter;
		}
		HashValueGenerator::GetInstance()->SetHashFunctionTable(i, a, b);
	}
	ifs.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string file = "D:\\files\\1.ts";
	std::vector<LayerOfEigenvector> result = OSIDGenerater::Do(file);
	std::ofstream ofs("D:\\output\\hash2.txt");

	//ResetHashFunctionFromFile("D:\\programming\\TEST\\HashFunctions.txt");
	std::array <TrieTree, GroupOfHashFunction::NumberOfFunctionGroups> Tree;
	for (auto iterOfLayer = result.begin(); iterOfLayer != result.end(); ++iterOfLayer)
	{
		LayerOfHashValue tmp;
		tmp.GenerateHashValue(*iterOfLayer);
		for (int i = 0; i < GroupOfHashFunction::NumberOfFunctionGroups; ++i)
		{
			std::vector <std::vector<int>> hashvec = tmp.GetVector(i);
			for (auto iter = hashvec.cbegin(); iter != hashvec.cend(); ++iter)
			{
				Tree[i].Insert(*iter, 1);
			}
		}
		tmp.print(ofs);
	}
	ofs.close();

	ofs.open("D:\\output\\HashFunction.txt");
	HashValueGenerator::GetInstance()->PrintHashFunctionTable(ofs);
	ofs.close();
//	CheckForNormalDistribution::CountForPoints();

//	std::ofstream ofs("D:\\output\\1.txt");
//	ofs.close();
	
//	for (auto iter = result.cbegin(); iter != result.cend(); ++iter)
//	{
//		iter->print();
//	}
//	SampleExtracter sample("D:\\files\\1.ts", 25);
//	sample.GetSampleImageVector(FirstElement);

	return 0;
}
