// 画像サイズを変更
// 3 枚の画像を読み取れる
// 角度を30度傾く
// 水平反転を加えた
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

//*****************************************************************//
//                  ファイルパスがなかったときの処理               //
//*****************************************************************//
void err_file(void) {
  cout << "not found" << endl;
}

//******************************************************************//
//                  ソースとなる画像のpath                          //
//******************************************************************//
string read_path(int x) {
    // int を string 型にキャスト
    string i_num = to_string(x);
    // ソース写真の絶対パス
    std::string path = "/home/keiji/image_processing/" + i_num + ".jpg";
    return path;
}

//******************************************************************//
//                  保存と処理をするpath                            //
//******************************************************************//
string save_path(int y) {
  // int を string 型にキャスト
  string out_num = to_string(y);
  // ソース写真の絶対パス
  string path = "/home/keiji/image_processing/cherry_test/dataset/" + out_num + ".jpg";
  return path;
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
  for(int i = 0; i < 3; ++i){

    // ソース画像を読み込みつつ定義
    cv::Mat src = cv::imread(read_path(i), 1);
    
    // なかったときの処理
    if(src.empty()) {
      err_file();
    }

    // 出力画像を定義
    cv::Mat dst;

    // 画像リサイズ
    // width * hight = 360 * 340 になるようにする 
    cv::resize(src, dst, cv::Size(), 0.09, 0.1134);
    // 出力のパスとなる数字、int を string 型にキャスト


    // 画像を格納するオブジェクトを宣言して画像を読み込む
    for(int k = 0; k < 8; ++k){
      // 画像を保存
      cv::imwrite(save_path(j), dst);

      // ファイルから画像を読み込む
      dst = cv::imread(save_path(j));

	  // なかったときの処理
      if(dst.empty()) {
        err_file();
      }

      float width = dst.cols;  // 列
      float height = dst.rows; // 行
    
      cv::Point2f center = cv::Point2f((width / 2),(height / 2));//図形の中心
      double degree = 45;  // 回転角度
      double scale = 1.0; //大きさの定義

      cv::Mat change = cv::getRotationMatrix2D(center, degree, scale); //回転&拡大縮小
      cv::warpAffine(dst, dst, change, dst.size(), cv::INTER_CUBIC,cv::BORDER_CONSTANT,cv::Scalar(0, 0, 0)); //画像の変換(アフィン変換)
      // ここでの画像の保存は上でやってくれる
      j++;

      // ファイルから画像を読み込む
      cv::Mat processing = cv::imread(save_path(j));
      cv::flip(dst, processing, 1);  // 水平反転
      cv::imwrite(save_path(j), processing); // 画像を保存

      j++;
    }
  }

  cout << "The work is complete." << endl;
  // キーボードが押されるまで待つ
  cv::waitKey(0);
}