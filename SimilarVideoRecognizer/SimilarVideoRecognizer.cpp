// SimilarVideoRecognizer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "SampleExtracter.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SampleExtracter sample("D:\\files\\1.ts", 25);
	sample.SaveSampleImageAsFile("D:\\files\\output", FirstElement);

	return 0;
}

