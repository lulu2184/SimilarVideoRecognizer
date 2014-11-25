#pragma once
#include "EigenvectorExtracterForImage.h"
#include "LayerOfEigenvector.h"

#include <string>
#include <vector>
#include <opencv2\\highgui\\highgui.hpp>
#include <opencv2\\core\\core.hpp>
#include <opencv2\\imgproc\\imgproc.hpp>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")

class OSIDGenerater
{
public:
	OSIDGenerater();
	~OSIDGenerater();
	static std::vector<LayerOfEigenvector> Do(const std::string &filename);

public:
	static int GapOfGettingSample;

private:
	static std::vector<std::vector <double>> GetEigenvectorForEachSampleFrame(const std::string &filename);
};

