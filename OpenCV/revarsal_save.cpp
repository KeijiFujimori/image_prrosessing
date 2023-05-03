#include <opencv2/opencv.hpp>
// 画像を反転させて保存するプログラム
 
int main(void)
{
	// 画像を格納するオブジェクトを宣言する
	cv::Mat	srcImage, dstImage;
 
	// 画像ファイルから画像データを読み込む
	srcImage = cv::imread("../../image.jpg");
 
	if (srcImage.empty() == true) {
		// 画像データが読み込めなかったときは終了する
		return 0;
	}
 
	// 画像変換（画像の上下反転）
	// # srcImage を画像変換した結果を dstImage に入れる
	cv::flip(srcImage, dstImage, 0);
 
	// ウィンドウに画像を表示する
	cv::imshow("原画像", srcImage);
	cv::imshow("変換後画像", dstImage);
 
	// 画像を保存する
	// # ファイルフォーマットはファイル名の拡張子で自動判別される
	// # 保存先をフルパスで指定していないときは、ソースプログラムと同じフォルダに保存される
	cv::imwrite("../../変換後画像.jpg", dstImage);	// JPEGフォーマットで保存
	// cv::imwrite("変換後画像.png", dstImage);	//  PNGフォーマットで保存
 
	// 何かキーが押されるまで待つ
	cv::waitKey();
 
	return 0;
}