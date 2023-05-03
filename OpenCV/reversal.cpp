// 画像を反転
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[]) {
	cv::Mat src_img = cv::imread("../../001.jpg",1);
	if(!src_img.data) return -1;
	
	cv::Mat v_img, h_img, b_img;
	cv::flip(src_img, v_img, 0);  // 垂直反転
	cv::flip(src_img, h_img, 1);  // 水平反転
	cv::flip(src_img, b_img, -1); // 両方の軸で反転
	
	cv::namedWindow("vertical flip image", cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);
	cv::namedWindow("horizontal flip image", cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);
	cv::namedWindow("both flip image", cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);
	cv::imshow("vertical flip image", v_img);
	cv::imshow("horizontal flip image", h_img);
	cv::imshow("both flip image", b_img);
	cv::waitKey(0);
}
