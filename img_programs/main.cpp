// 画像サイズを変更
// 3 枚の画像を読み取れる
// 角度を30度傾く
// 水平反転を加えた
// エッジ検出を加えた
// ガンマ補正を加えた
// アルファー補正とベータ補正を加えた
// グレースケールに変更を加えた
// サイズを取得し、自動で調整してくれる
#include <iostream>
#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
using std::cin;
using std::cout;
using std::endl;
using namespace cv;

//*****************************************************************//
//                  ファイルパスがなかったときの処理               //
//*****************************************************************//
void err_file(void) {
  cout << "not found" << endl;
}

//******************************************************************//
//                  ソースとなる画像のpath                          //
//******************************************************************//
std::string read_path(int x) {
    // int を string 型にキャスト
    std::string i_num = std::to_string(x);
    // ソース写真の絶対パス
    std::string path = "/home/keiji/image_pro/" + i_num + ".jpg";
    return path;
}

//******************************************************************//
//                  保存と処理をするpath                            //
//******************************************************************//
std::string save_path(int y) {
  // int を string 型にキャスト
  std::string out_num = std::to_string(y);
  // ソース写真の絶対パス
  std::string path = "/home/keiji/image_pro/cherry_test/dataset/cherry_val/" + out_num + ".jpg";
  return path;
}

//********************************************************************//
//                          リサイズする関数                          //
//********************************************************************//
int image_size(int i, cv::Mat& src, cv::Mat& dst) {
    // ファイルの読み込み
    src = cv::imread(read_path(i), 1);
    // なかったときの処理
    if(src.empty()) {
        err_file();
        return 1;
    }
    
    // 指定の大きさにする計算
    double clos_enla = 360 / (double)src.cols;
    double rows_enla = 340 / (double)src.rows;

    // 画像リサイズ
    // width * hight = 360 * 340 になるようにする 
    cv::resize(src, dst, cv::Size(), clos_enla, rows_enla);
    return 0;
}

//**********************************************************************//
//                     画像の保存と読み込み                             //
//**********************************************************************//
int save_and_read(int j, cv::Mat& dst) {
    // 画像を保存
    cv::imwrite(save_path(j), dst);

    // ファイルから画像を読み込む
    dst = cv::imread(save_path(j));

	// なかったときの処理
    if(dst.empty()) {
        err_file();
        return 1;
    }

    return 0;
}

//**********************************************************************//
//                 回転と縮小拡大                                       //
//**********************************************************************//
int rotate_size(cv::Mat& dst) {
    float width = dst.cols;  // 列
    float height = dst.rows; // 行
    
    cv::Point2f center = cv::Point2f((width / 2),(height / 2));//図形の中心
    double degree = 45;  // 回転角度
    double scale = 1.0; //大きさの定義

    cv::Mat change = cv::getRotationMatrix2D(center, degree, scale); //回転&拡大縮小
    cv::warpAffine(dst, dst, change, dst.size(), cv::INTER_CUBIC,cv::BORDER_CONSTANT,cv::Scalar(0, 0, 0)); //画像の変換(アフィン変換)
    // ここでの画像の保存はsave_and_readでやってくれる
    return 0;
}

//**********************************************************************//
//                     Canny 法によるエッジ強調                         //
//**********************************************************************//
int Canny_edge(int& j,cv::Mat& dst) {
      // エッジ強調 , 出力の変数
      cv::Mat edge;
      Canny(dst,edge,50,200);
      j++;
      cv::imwrite(save_path(j), edge); // 画像を保存
      return 0;
}

//*********************************************************************//
//                    ガンマ補正                                       //
//*********************************************************************//
int gamma(int& j, cv::Mat dst) {
    // 画像を格納するオブジェクトを宣言する
    cv::Mat	dst2;
	// ルックアップテーブルを用いたガンマ補正
    cv::cvtColor(dst, dst2, cv::COLOR_BGR2GRAY);
	double gamma = 1.5;									// ガンマ値
	uchar  lut[256];									// ルックアップテーブル用配列
	for (int i = 0; i < 256; i++) {
		lut[i] = pow(i / 255.0, 1 / gamma) * 255.0;		// ガンマ補正式
	}
	cv::LUT(dst2, cv::Mat(1, 256, CV_8UC1, lut), dst2);	// ルックアップテーブル変換
    j++;
    cv::imwrite(save_path(j), dst2); // 画像を保存
    return 0;
}

//*********************************************************************//
//                      コントラストと明度調整                         //
//*********************************************************************//
int cont_bri(int& j, cv::Mat dst) {
    //元画像と同じサイズ・タイプで、値が0埋めされた出力画像を準備
    Mat new_image = Mat::zeros( dst.size(), dst.type() );
    //αとβはユーザ入力
    double alpha = 2.0; /*< Simple contrast control */
    int beta = 50;       /*< Simple brightness control */

    //行・列・カラーチャネルをforで回し、各ピクセルに上式の変換を適用する
    for( int y = 0; y < dst.rows; y++ ) {
        for( int x = 0; x < dst.cols; x++ ) {
            for( int c = 0; c < dst.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  //saturate_cast<uchar>は値が整数でない場合や範囲外の場合に有効な値に直す
                  saturate_cast<uchar>( alpha*dst.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }
    j++;
    cv::imwrite(save_path(j), new_image); // 画像を保存
    return 0;
}

//******************************************************************//
//                      メイン関数                                  //
//******************************************************************//
int main(int argc, const char* argv[])
{
  // j の初期値
  // この値を出力ファイル名にする
  int j = 0;
  // for 文でソース画像を取得し、表示していく
  for(int i = 0; i < 1; ++i){
    // ソース画像,出力画像
    cv::Mat src, dst;
    // 所定の大きさにリサイズする関数
    image_size(i, src, dst);


    // 画像を格納するオブジェクトを宣言して画像を読み込む
    for(int k = 0; k < 8; ++k){

      // 回転とscaleの関数
      rotate_size(dst);
    
      // 画像を読み込んで保存する関数
      save_and_read(j, dst);
      
      // Canny法によるエッジ強調
      Canny_edge(j, dst);

      // ガンマ補正
      gamma(j, dst);

      // コントラストと明度調整
      cont_bri(j,dst);




      // *******************************反転 ***************************//
      cv::Mat revasal;
      cv::flip(dst, revasal, 1);  // 水平反転
      j++;
      cv::imwrite(save_path(j), revasal); // 画像を保存

      // エッジ強調
      Canny_edge(j, revasal);

      gamma(j, revasal);


      cont_bri(j, revasal);
      j++;
    }
  }

  cout << "The work is complete." << endl;
  // キーボードが押されるまで待つ
  cv::waitKey(0);
}