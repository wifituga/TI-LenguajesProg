#include <iostream>
#include "fMatrices.h"
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

Mat grayScale(const Mat& image) {
    Mat grayImage(image.size(), CV_8UC1);
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            Vec3b pixel = image.at<Vec3b>(x, y);
            int grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;
            grayImage.at<uchar>(x, y) = grayValue;
        }
    }
    return grayImage;
}

Mat Sobel3x3FilterColor(const Mat& image) {

    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int sobelY[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    Mat gradX(image.size(), CV_16SC3);
    Mat gradY(image.size(), CV_16SC3);
    Mat gradient(image.size(), CV_64FC3);

    for (int x = 1; x < image.rows - 1; x++) {
        for (int y = 1; y < image.cols - 1; y++) {
            Vec3d pixelX(0.0, 0.0, 0.0);
            Vec3d pixelY(0.0, 0.0, 0.0);
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    Vec3b intensity = image.at<Vec3b>(x + i, y + j);
                    pixelX[0] += intensity[0] * sobelX[i + 1][j + 1];
                    pixelX[1] += intensity[1] * sobelX[i + 1][j + 1];
                    pixelX[2] += intensity[2] * sobelX[i + 1][j + 1];
                    pixelY[0] += intensity[0] * sobelY[i + 1][j + 1];
                    pixelY[1] += intensity[1] * sobelY[i + 1][j + 1];
                    pixelY[2] += intensity[2] * sobelY[i + 1][j + 1];
                }
            }
            gradX.at<Vec3s>(x, y) = pixelX;
            gradY.at<Vec3s>(x, y) = pixelY;

            Vec3d gradientValue;
            gradientValue[0] = sqrt(pixelX[0] * pixelX[0] + pixelY[0] * pixelY[0]);
            gradientValue[1] = sqrt(pixelX[1] * pixelX[1] + pixelY[1] * pixelY[1]);
            gradientValue[2] = sqrt(pixelX[2] * pixelX[2] + pixelY[2] * pixelY[2]);

            gradient.at<Vec3d>(x, y) = gradientValue;
        }
    }
    Mat output;
    gradient.convertTo(output, CV_8UC3);
    return output;
}
Mat Sobel3x3FilterGray(const Mat& image) {

    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int sobelY[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    Mat gImage = grayScale(image);
    Mat gradX(image.size(), CV_16S);
    Mat gradY(image.size(), CV_16S);
    Mat gradient(image.size(), CV_64F);

    for (int y = 1; y < gImage.rows - 1; y++) {
        for (int x = 1; x < gImage.cols - 1; x++) {
            int pixelX = 0;
            int pixelY = 0;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int index = (y + j) * gImage.cols + (x + i);
                    pixelX += gImage.at<uchar>(y + j, x + i) * sobelX[j + 1][i + 1];
                    pixelY += gImage.at<uchar>(y + j, x + i) * sobelY[j + 1][i + 1];
                }
            }
            gradX.at<short>(y, x) = pixelX;
            gradY.at<short>(y, x) = pixelY;
            gradient.at<double>(y, x) = abs(pixelX) + abs(pixelY);
        }
    }
    Mat output;
    gradient.convertTo(output, CV_8U);
    return output;
}

Mat Sobel5x5FilterColor(const Mat& image) {
    Mat gradX(image.size(), CV_32FC3);
    Mat gradY(image.size(), CV_32FC3);
    Mat gradient(image.size(), CV_8UC3);

    int sobelY[5][5] = {
            {2, 1, 0, -1, -2},
            {2, 1, 0, -1, -2},
            {4, 2, 0, -2, -4},
            {2, 1, 0, -1, -2},
            {2, 1, 0, -1, -2}
    };
    int sobelX[5][5] = {
        {2, 2, 4, 2, 2},
        {1, 1, 2, 1, 1},
        {0, 0, 0, 0, 0},
        {-1, -1, -2, -1, -1},
        {-2, -2, -4, -2, -2}
    };

    for (int y = 2; y < image.rows - 2; y++) {
        for (int x = 2; x < image.cols - 2; x++) {
            Vec3f pixelX(0.0, 0.0, 0.0);
            Vec3f pixelY(0.0, 0.0, 0.0);
            for (int j = -2; j <= 2; j++) {
                for (int i = -2; i <= 2; i++) {
                    Vec3b intensity = image.at<Vec3b>(y + j, x + i);
                    pixelX[0] += intensity[0] * sobelX[j + 2][i + 2];
                    pixelX[1] += intensity[1] * sobelX[j + 2][i + 2];
                    pixelX[2] += intensity[2] * sobelX[j + 2][i + 2];
                    pixelY[0] += intensity[0] * sobelY[j + 2][i + 2];
                    pixelY[1] += intensity[1] * sobelY[j + 2][i + 2];
                    pixelY[2] += intensity[2] * sobelY[j + 2][i + 2];
                }
            }
            gradX.at<Vec3f>(y, x) = pixelX;
            gradY.at<Vec3f>(y, x) = pixelY;

            Vec3f gradientValue;
            gradientValue[0] = sqrt(pixelX[0] * pixelX[0] + pixelY[0] * pixelY[0]);
            gradientValue[1] = sqrt(pixelX[1] * pixelX[1] + pixelY[1] * pixelY[1]);
            gradientValue[2] = sqrt(pixelX[2] * pixelX[2] + pixelY[2] * pixelY[2]);

            gradient.at<Vec3b>(y, x) = gradientValue;
        }
    }

    return gradient;
}
Mat Sobel5x5FilterGray(const Mat& image) {
    Mat gImage = grayScale(image);
    Mat gradX(image.size(), CV_32F);
    Mat gradY(image.size(), CV_32F);
    Mat gradient(image.size(), CV_8U);

    int sobelX[5][5] = {
        {-1, -2, 0, 2, 1},
        {-4, -8, 0, 8, 4},
        {-6, -12, 0, 12, 6},
        {-4, -8, 0, 8, 4},
        {-1, -2, 0, 2, 1}
    };

    int sobelY[5][5] = {
        {-1, -4, -6, -4, -1},
        {-2, -8, -12, -8, -2},
        {0, 0, 0, 0, 0},
        {2, 8, 12, 8, 2},
        {1, 4, 6, 4, 1}
    };

    for (int y = 2; y < gImage.rows - 2; y++) {
        for (int x = 2; x < gImage.cols - 2; x++) {
            float pixelX = 0.0;
            float pixelY = 0.0;
            for (int j = -2; j <= 2; j++) {
                for (int i = -2; i <= 2; i++) {
                    int index = (y + j) * gImage.cols + (x + i);
                    pixelX += gImage.at<uchar>(y + j, x + i) * sobelX[j + 2][i + 2];
                    pixelY += gImage.at<uchar>(y + j, x + i) * sobelY[j + 2][i + 2];
                }
            }
            gradX.at<float>(y, x) = pixelX;
            gradY.at<float>(y, x) = pixelY;
            gradient.at<uchar>(y, x) = abs(pixelX) + abs(pixelY);
        }
    }

    return gradient;
}

Mat Gaussian3x3FilterColor(const Mat& image) {
    Mat blurredImage(image.size(), CV_8UC3);

    float kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    int kernelSum = 16; // Sum of all kernel elements for normalization

    for (int y = 1; y < image.rows - 1; y++) {
        for (int x = 1; x < image.cols - 1; x++) {
            Vec3f sum(0.0, 0.0, 0.0);
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    Vec3b intensity = image.at<Vec3b>(y + j, x + i);
                    sum[0] += intensity[0] * kernel[j + 1][i + 1];
                    sum[1] += intensity[1] * kernel[j + 1][i + 1];
                    sum[2] += intensity[2] * kernel[j + 1][i + 1];
                }
            }
            blurredImage.at<Vec3b>(y, x) = Vec3b(sum[0] / kernelSum, sum[1] / kernelSum, sum[2] / kernelSum);
        }
    }

    return blurredImage;
}
Mat Gaussian3x3FilterGray(const Mat& image) {
    Mat blurredImage(image.size(), CV_8UC1);

    float kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    int kernelSum = 16; // Sum of all kernel elements for normalization

    for (int y = 1; y < image.rows - 1; y++) {
        for (int x = 1; x < image.cols - 1; x++) {
            int sum = 0;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    sum += image.at<uchar>(y + j, x + i) * kernel[j + 1][i + 1];
                }
            }
            blurredImage.at<uchar>(y, x) = sum / kernelSum;
        }
    }

    return blurredImage;
}

Mat Gaussian5x5FilterColor(const Mat& image) {
    Mat blurredImage(image.size(), CV_8UC3);

    float kernel[5][5] = {
        {1, 4, 7, 4, 1},
        {4, 16, 26, 16, 4},
        {7, 26, 41, 26, 7},
        {4, 16, 26, 16, 4},
        {1, 4, 7, 4, 1}
    };

    int kernelSum = 273;

    for (int y = 2; y < image.rows - 2; y++) {
        for (int x = 2; x < image.cols - 2; x++) {
            Vec3f sum(0.0, 0.0, 0.0);
            for (int j = -2; j <= 2; j++) {
                for (int i = -2; i <= 2; i++) {
                    Vec3b intensity = image.at<Vec3b>(y + j, x + i);
                    sum[0] += intensity[0] * kernel[j + 2][i + 2];
                    sum[1] += intensity[1] * kernel[j + 2][i + 2];
                    sum[2] += intensity[2] * kernel[j + 2][i + 2];
                }
            }
            blurredImage.at<Vec3b>(y, x) = Vec3b(sum[0] / kernelSum, sum[1] / kernelSum, sum[2] / kernelSum);
        }
    }

    return blurredImage;
}
Mat Gaussian5x5FilterGray(const Mat& image) {
    Mat blurredImage(image.size(), CV_8UC1);

    float kernel[5][5] = {
        {1, 4, 7, 4, 1},
        {4, 16, 26, 16, 4},
        {7, 26, 41, 26, 7},
        {4, 16, 26, 16, 4},
        {1, 4, 7, 4, 1}
    };

    int kernelSum = 273;

    for (int y = 2; y < image.rows - 2; y++) {
        for (int x = 2; x < image.cols - 2; x++) {
            int sum = 0;
            for (int j = -2; j <= 2; j++) {
                for (int i = -2; i <= 2; i++) {
                    sum += image.at<uchar>(y + j, x + i) * kernel[j + 2][i + 2];
                }
            }
            blurredImage.at<uchar>(y, x) = sum / kernelSum;
        }
    }

    return blurredImage;
}

Mat BoxBlurFilter(const Mat& image) {
    int height = image.rows;
    int width = image.cols;

    Mat blurredImage(height - 2, width - 2, CV_8UC3);

    float kernel[3][3] = { {1.0f / 9, 1.0f / 9, 1.0f / 9},
                           {1.0f / 9, 1.0f / 9, 1.0f / 9},
                           {1.0f / 9, 1.0f / 9, 1.0f / 9} };

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            Vec3f sum(0.0f, 0.0f, 0.0f);

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    Vec3b pixel = image.at<Vec3b>(y + i, x + j);
                    float weight = kernel[i + 1][j + 1];
                    sum[0] += pixel[0] * weight;
                    sum[1] += pixel[1] * weight;
                    sum[2] += pixel[2] * weight;
                }
            }

            Vec3b blurredPixel(static_cast<uchar>(sum[0]), static_cast<uchar>(sum[1]), static_cast<uchar>(sum[2]));
            blurredImage.at<Vec3b>(y - 1, x - 1) = blurredPixel;
        }
    }

    return blurredImage;
}

void calcularHistogramaColor(const Mat& image, const string& filename) {
    int histSize = 256;
    Mat hist(3, histSize, CV_32SC1, Scalar(0));

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            Vec3b intensity = image.at<Vec3b>(y, x);
            hist.at<int>(0, intensity[0])++;
            hist.at<int>(1, intensity[1])++;
            hist.at<int>(2, intensity[2])++;
        }
    }

    ofstream outputFile(filename);

    for (int channel = 0; channel < hist.rows; channel++) {
        for (int i = 0; i < hist.cols; i++) {
            outputFile << hist.at<int>(channel, i) << ",";
        }
        outputFile << "\n";
    }

    outputFile.close();
}
void calcularHistogramaGray(const Mat& image, const string& filename) {
    int histSize = 256;
    Mat hist(1, histSize, CV_32SC1, Scalar(0));

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            int pixelValue = image.at<uchar>(y, x);
            hist.at<int>(pixelValue)++;
        }
    }

    ofstream outputFile(filename);

    for (int i = 0; i < hist.cols; i++) {
        outputFile << hist.at<int>(i) << "\n";
    }

    outputFile.close();
}

void printImage(Mat image, Mat mImage) {
    namedWindow("Original", WINDOW_NORMAL);
    imshow("Original", image);
    namedWindow("Filtrada", WINDOW_NORMAL);
    imshow("Filtrada", mImage);
    waitKey(0);
}