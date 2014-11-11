#include "stdafx.h"
#include "Controller.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::Do(std::string &filename, int gaplength)
{
	SampleExtracter extracter(filename, gaplength);
	std::vector <cv::Mat> Vsample = extracter.GetSampleImageVector(FirstElement);
	
	for (auto iter = Vsample.cbegin(); iter != Vsample.cend(); ++iter)
	{

	}
}