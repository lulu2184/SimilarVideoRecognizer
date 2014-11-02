// SimilarVideoRecognizer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SampleExtracter.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SampleExtracter sample("D:\\files\\1.ts", 25);
	sample.SaveSampleImageAsFile("D:\\files\\output", FirstElement);

	return 0;
}

