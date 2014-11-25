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

class EigenvectorExtracterForImage
{
public:
	EigenvectorExtracterForImage();
	~EigenvectorExtracterForImage();
	static std::vector<int> TransIntoOrdinal(const cv::Mat &mat);
	static std::vector <double> GetEigenvector(const cv::Mat &image);

public:
	static int NumberOfBins;
	static int NumberOfRowDivision;
	static int NumberOfColDivision;
	static CvSize SizeOfNormalizedImage;

private:
	static void RemoveBlackBorder(cv::Mat &image);
	static void Prepare(cv::Mat &image);
	static int GetSpaceNumber(int PosNumber);
	static int GetHistogramNumber(int posnumber, int ordinalnumber);
	static int GetBinNumber(int ordinalnumber);
	static void Normalize(std::vector<double> &Vec);
	static std::vector <double> GetHistogram(const std::vector <int> &ordinalvec);

private:
	static int SizeOfBlock;
	static int ElementINABin;
	static int HeightOfBlock;
	static int WidthOfBlock;
	static int OutputFrameCounter;
};