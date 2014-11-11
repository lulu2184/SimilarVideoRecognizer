// SimilarVideoRecognizer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SampleExtracter.h"
#include "OSIDGenerater.h"
#include "LayerOfEigenvector.h"
#include <fstream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::string file = "D:\\files\\1.ts";
	std::vector<LayerOfEigenvector> result = OSIDGenerater::Do(file);
	std::ofstream ofs("D:\\output\\1.txt");
	ofs.close();
	
	for (auto iter = result.cbegin(); iter != result.cend(); ++iter)
	{
		iter->print();
	}
//	SampleExtracter sample("D:\\files\\1.ts", 25);
//	sample.GetSampleImageVector(FirstElement);

	return 0;
}
