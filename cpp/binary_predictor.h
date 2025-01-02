#ifndef BINARY_PREDICTOR_H
#define BINARY_PREDICTOR_H
#include <iostream>
#include <vector>
#include <locale>
#include <codecvt>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
//#include <cuda_provider_factory.h>  ///如果使用cuda加速，需要取消注释
#include <onnxruntime_cxx_api.h>


class UnetCNN
{
public:
	UnetCNN(const std::string& model_path);
	cv::Mat predict(const cv::Mat& srcimg);   
private:
	void preprocess(const cv::Mat& img);
	std::vector<float> input_image;
    int pad_info[4];
    int input_h;
    int input_w;
    cv::Mat postprocess(cv::Mat& img);

	Ort::Env env = Ort::Env(ORT_LOGGING_LEVEL_ERROR, "BINARY PREDICTOR");
	Ort::SessionOptions sessionOptions = Ort::SessionOptions();

	Ort::Session *ort_session = nullptr;
	const std::vector<const char*> input_names = {"input"};
	const std::vector<const char*> output_names = {"output"};

	Ort::MemoryInfo memory_info_handler = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
	Ort::RunOptions runOptions;
};


#endif