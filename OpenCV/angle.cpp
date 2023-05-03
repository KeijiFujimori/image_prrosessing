#include<iostream>
#include<cmath>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
   	// 画像を格納するオブジェクトを宣言して画像を読み込む
	//cv::Mat	image = cv::imread("../../../image.jpg");;
    cv::Mat	image = cv::imread("/home/keiji/image_processing/image.jpg");;
 	//エラー処理
	if (image.empty() == true) {
		// 画像の中身が空なら終了する
		return 0;
	}
    float width = image.cols;
    float height = image.rows;
    
    cv::Point2f center = cv::Point2f((width / 2),(height / 2));//図形の中心
    double degree = 45.0;  // 回転角度
    double scale = 1; //大きさの定義

    cv::Mat change = cv::getRotationMatrix2D(center, degree, scale); //回転&拡大縮小
    cv::warpAffine(image, image, change, image.size(), cv::INTER_CUBIC,cv::BORDER_CONSTANT,cv::Scalar(0, 0, 0)); //画像の変換(アフィン変換)

	// ウィンドウに画像を表示する
	cv::imshow("opencv_logo", image);
	// キーが押されるまで待つ
	cv::waitKey(0);
	//  画像を書き出し
	cv::imwrite("output.png", image);	
 
    return 0;
}