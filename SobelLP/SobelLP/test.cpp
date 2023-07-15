#include <iostream>
#include "fMatrices.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    int kernel;
    int tam;
    char pColor;
    int blur;
    int sobel;
    Mat fotito = imread("aa2.png");
    Mat mImage;
    Mat mImage2;
    cout << "Grupo 3 | Lenguajes de programacion" << endl
         << "1. Sobel" << endl 
         << "2. Gaussian Blur" << endl 
         << "3. Blox Blur" << endl 
         << "4. Blur y Sobel" << endl 
         << "Seleccione la matriz a aplicar: ";
    cin >> kernel;
    switch (kernel) {
    case 1:
        cout << "1. Sobel 3x3 " << endl
             << "2. Sobel 5x5" << endl;
        cout << "Indique la matriz: ";
        cin >> tam;
        cout << "Imagen a color o blanco y negro (C/B): ";
        cin >> pColor;
        switch (tam) {
        case 1:
            if (fotito.empty()) {
                cout << "No se pudo cargar la imagen." << endl;
                return -1;
            }
            switch (pColor){
            case 'C':
                mImage = Sobel3x3FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'c':
                mImage = Sobel3x3FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'B':
                mImage = Sobel3x3FilterGray(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            case 'b':
                mImage = Sobel3x3FilterGray(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            default:
                break;
            }
            printImage(fotito, mImage);
            break;
        case 2:
            if (fotito.empty()) {
                cout << "No se pudo cargar la imagen." << endl;
                return -1;
            }
            switch (pColor) {
            case 'C':
                mImage = Sobel5x5FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'c':
                mImage = Sobel5x5FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'B':
                mImage = Sobel5x5FilterGray(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            case 'b':
                mImage = Sobel5x5FilterGray(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            default:
                break;
            }
            printImage(fotito, mImage);
            break;
        default:
            cout << "input invalido";
            break;
        }
        break;
    case 2:
        cout << "1. Gaussian Blur 3x3 " << endl
             << "2. Gaussian Blur 5x5" << endl;
        cout << "Indique la matriz: ";
        cin >> tam;
        cout << "Imagen a color o blanco y negro (C/B): ";
        cin >> pColor;
        switch (tam) {
        case 1:
            if (fotito.empty()) {
                cout << "No se pudo cargar la imagen." << endl;
                return -1;
            }
            switch (pColor) {
            case 'C':
                mImage = Gaussian3x3FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'c':
                mImage = Gaussian3x3FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'B':
                mImage2 = grayScale(fotito);
                mImage = Gaussian3x3FilterGray(mImage2);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            case 'b':
                mImage2 = grayScale(fotito);
                mImage = Gaussian3x3FilterGray(mImage2);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            default:
                break;
            }
            printImage(fotito, mImage);
            break;
        case 2:
            if (fotito.empty()) {
                cout << "No se pudo cargar la imagen." << endl;
                return -1;
            }
            switch (pColor) {
            case 'C':
                mImage = Gaussian5x5FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'c':
                mImage = Gaussian5x5FilterColor(fotito);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaColor(mImage, "imgC.csv");
                break;
            case 'B':
                mImage2 = grayScale(fotito);
                mImage = Gaussian5x5FilterGray(mImage2);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            case 'b':
                mImage2 = grayScale(fotito);
                mImage = Gaussian5x5FilterGray(mImage2);
                calcularHistogramaColor(fotito, "imgO.csv");
                calcularHistogramaGray(mImage, "imgB.csv");
                break;
            default:
                break;
            }
            printImage(fotito, mImage);
            break;
        default:
            cout << "input invalido";
            break;
        }
        break;
    case 3:
        if (fotito.empty()) {
            cout << "No se pudo cargar la imagen." << endl;
            return -1;
        }
        mImage = BoxBlurFilter(fotito);
        calcularHistogramaColor(fotito, "imgO.csv");
        calcularHistogramaColor(mImage, "imgC.csv");
        printImage(fotito, mImage);
        break;
    case 4:
        cout << "1. Gaussian Blur 3x3 " << endl
             << "2. Gaussian Blur 5x5" << endl
             << "3. BoxBlur" << endl;
        cout << "Ingrese el blur que desea aplicar: ";
        cin >> blur;
        switch (blur){
        case 1:
            mImage = Gaussian3x3FilterColor(fotito);
            break;
        case 2:
            mImage = Gaussian5x5FilterColor(fotito);
            break;
        case 3:
            mImage = BoxBlurFilter(fotito);
            break;
        default:
            break;
        }
        cout << "1. Sobel 3x3 " << endl
             << "2. Sobel 5x5" << endl;
        cout << "Ingrese el sobel que desea aplicar: ";
        cin >> sobel;
        switch (sobel) {
        case 1:
            mImage2 = Sobel3x3FilterColor(mImage);
            calcularHistogramaColor(mImage, "imgO.csv");
            calcularHistogramaColor(mImage2, "imgC.csv");
            printImage(mImage, mImage2);
            break;
        case 2:
            mImage2 = Sobel5x5FilterColor(mImage);
            calcularHistogramaColor(mImage, "imgO.csv");
            calcularHistogramaColor(mImage2, "imgC.csv");
            printImage(mImage, mImage2);
            break;
        default:
            break;
        }
    default:
        cout << "input invalido";
        break;
    };
    return 0;
}