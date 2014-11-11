#pragma once
#include <opencv2\\highgui\\highgui.hpp>
#include <opencv2\\core\\core.hpp>
#include <opencv2\\imgproc\\imgproc.hpp>
#include <vector>
#include <string>
#include <windows.h>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")

const int MAX_LENGTH_FOR_DIR = 100;

enum TypeOfGettingSample{
	FirstElement = 0,
	Randomly
};

class SampleExtracter
{
private:
	cv::VideoCapture m_VideoCapture;
	int m_LengthOfGap;

	bool IsValidOutputPath(const std::string &outputpath);
	std::vector <int> GetSampleFrameNumberVector(TypeOfGettingSample sampleType);
	LPCWSTR SampleExtracter::StringToLPCWSTR(const std::string &str);
	void ChangeBrightnessOfImage(cv::Mat &image, double rate);

public:
	SampleExtracter(const std::string &filepath, int gaplength);
	~SampleExtracter();
	std::vector <cv::Mat> GetSampleImageVector(TypeOfGettingSample sampleType);
	void SaveSampleImageAsFile(const std::string &outputpath, TypeOfGettingSample sampleType);
	void SetLengthOfGap(int gaplength);
	cv::Mat GetNextSample();
};