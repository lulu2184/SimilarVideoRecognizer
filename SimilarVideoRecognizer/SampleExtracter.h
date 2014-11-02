#pragma once
#include <opencv2\\highgui\\highgui.hpp>
#include <opencv2\\core\\core.hpp>
#include <opencv2\\imgproc\\imgproc.hpp>
#include <vector>
#include <string>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")

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
	TCHAR *str2pTCHAR(const std::string &str);
	std::string Num2Str(int number);
	std::vector <int> GetSampleFrameNumberVector(TypeOfGettingSample sampleType);

public:
	SampleExtracter(const std::string &filepath, int gaplength);
	~SampleExtracter();
	std::vector <cv::Mat> GetSampleImageVector(TypeOfGettingSample sampleType);
	void SaveSampleImageAsFile(const std::string &outputpath, TypeOfGettingSample sampleType);
	void SetLengthOfGap(int gaplength);
};