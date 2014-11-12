#include "stdafx.h"
#include "OSIDGenerater.h"
#include <fstream>


OSIDGenerater::OSIDGenerater()
{
}


OSIDGenerater::~OSIDGenerater()
{
}

std::vector<std::vector <double>> OSIDGenerater::GetEigenvectorForEachSampleFrame(const std::string &filename)
{
	cv::VideoCapture video(filename);
	assert(video.isOpened());
	int counter = 0;

	std::vector<std::vector<double>> ret;
	cv::Mat image;
	int count = 0;

	while (video.read(image))
	{
		if (!count)
		{
//			imwrite("D:\\files\\output\\" + std::to_string(counter) + ".jpg", image);
			counter++;
			ret.push_back(EigenvectorExtracterForImage::GetEigenvector(image));
		}
		count = (count + 1) % GapOfGettingSample;
	}
	return std::move(ret);
}

std::vector<LayerOfEigenvector> OSIDGenerater::Do(const std::string &filename)
{
//	std::ofstream fff("D:\\output\\FrameFeature.txt");
	std::vector<std::vector<double>> VEigenvector = GetEigenvectorForEachSampleFrame(filename);
	std::vector <LayerOfEigenvector> ResVector;
	LayerOfEigenvector origin(VEigenvector);
	int count = 0;
	int combination = NumberOfSamplesIn1stLayerVEC;

	for (int i = 0; i < NumberOfLayer; ++i)
	{
		LayerOfEigenvector NewLayer = origin.GetLayer(combination);
		ResVector.push_back(NewLayer);
		combination *= MultipleOfAdjacentLayer;
	}
	return std::move(ResVector);
}