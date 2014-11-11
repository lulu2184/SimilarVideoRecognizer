#pragma once
#include "EigenvectorExtracterForImage.h"
#include "SampleExtracter.h"

#include <string>
#include <vector>
#include <opencv2\\highgui\\highgui.hpp>
#include <opencv2\\core\\core.hpp>
#include <opencv2\\imgproc\\imgproc.hpp>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")

class Controller
{
public:
	Controller();
	~Controller();
	void Do(std::string &filename, int gaplength);
};

