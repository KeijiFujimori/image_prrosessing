// 画像サイズを変更
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, const char* argv[])
{
  // 入力画像
  cv::Mat src = cv::imread("../../001.jpg", 1);
  if(src.empty()) std::cout << "not found" << std::endl;
  
  // 出力画像
  cv::Mat dst;

  // 画像リサイズ
  cv::resize(src, dst, cv::Size(), 0.09, 0.114);
  
  cv::namedWindow("RESIZE", cv::WINDOW_AUTOSIZE);
  cv::imshow("RESIZE", dst);
    
  cv::waitKey(0);
}