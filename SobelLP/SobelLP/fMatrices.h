#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

Mat grayScale(const Mat& image);
Mat Sobel3x3FilterColor(const Mat& image);
Mat Sobel3x3FilterGray(const Mat& image);
Mat Sobel5x5FilterColor(const Mat& image);
Mat Sobel5x5FilterGray(const Mat& image);
Mat Gaussian3x3FilterColor(const Mat& image);
Mat Gaussian3x3FilterGray(const Mat& image);
Mat Gaussian5x5FilterColor(const Mat& image);
Mat Gaussian5x5FilterGray(const Mat& image);
Mat BoxBlurFilter(const Mat& image);
void calcularHistogramaColor(const Mat& image, const string& filename);
void calcularHistogramaGray(const Mat& image, const string& filename);
void printImage(Mat image, Mat mImage);