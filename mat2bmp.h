#pragma once

//include
//#include <opencv2/opencv.hpp>

using namespace System;
using namespace System::Drawing;
//Add
using namespace System::Runtime::InteropServices;
using namespace cv;

public class mat2bmp
{

public:
	/*コンストラクタ*/
	mat2bmp(void)
	{
		/*何もしない*/
	}
	/*デストラクタ*/
	~mat2bmp(void)
	{
	}
	/*----- public function ------*/
	Bitmap^ mat2mbp(Mat img, Mat* OutImg) {
		const int alignedCols = static_cast<int>(alignSize(img.cols, 4));
		Mat alignedMat = Mat(img.rows, alignedCols, img.type());	/*Bitmapオブジェクトと変換するために
																	  行のバイト数が4Byteバウンダリ　*/
		*OutImg = Mat(alignedMat, Rect(0, 0, img.cols, img.rows));
		img.copyTo(*OutImg);	/*img -> mSrc*/

		Bitmap^ bmp = gcnew Bitmap(OutImg->cols, OutImg->rows,
			static_cast<int>(OutImg->step),
			System::Drawing::Imaging::PixelFormat::Format24bppRgb,
			IntPtr(OutImg->ptr()));

		return bmp;
	}

	Mat readFile(System::String^ fname) {
		/*System::Strine -> char* に変換*/
		/*マネージドコードSystem::Strine -> char* に変換*/
		char* pStr = (char*)Marshal::StringToHGlobalAnsi(fname).ToPointer();

		Mat mat = imread(pStr, IMREAD_UNCHANGED);

		/*メモリの解放*/
		Marshal::FreeHGlobal(IntPtr(pStr));

		return mat;
	}

	void writeFile(System::String^ fname, Mat* img) {
		/*System::Strine -> char* に変換*/
		/*マネージドコードSystem::Strine -> char* に変換*/
		char* pStr = (char*)Marshal::StringToHGlobalAnsi(fname).ToPointer();

		imwrite(pStr, *img);

		/*メモリの解放*/
		Marshal::FreeHGlobal(IntPtr(pStr));
	}
	/*----- private function ------*/
};