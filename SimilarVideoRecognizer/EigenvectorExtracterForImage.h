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

const int NumberOfBins = 3;
const int NumberOfRowDivision = 3;
const int NumberOfColDivision = 3;

const CvSize SizeOfNormalizedImage = { 198, 198 };

class EigenvectorExtracterForImage
{
private:
	static int SizeOfBlock;
	static int ElementINABin;
	static int HeightOfBlock;
	static int WidthOfBlock;
	static void RemoveBlackBorder(cv::Mat &image);
	static void Prepare(cv::Mat &image);
	static int GetSpaceNumber(int PosNumber);
	static int GetHistogramNumber(int posnumber, int ordinalnumber);
	static int GetBinNumber(int ordinalnumber);
	static void Normalize(std::vector<double> &Vec);
	static std::vector<int> GetVectorFromMat(const cv::Mat &mat);
	static std::vector <double> GetHistogram(const std::vector <int> &ordinalvec);

public:
	EigenvectorExtracterForImage();
	~EigenvectorExtracterForImage();
	static void TransIntoOrdinal(std::vector <int> &ordinalvec);
	static std::vector <double> GetEigenvector(const cv::Mat &image);
};