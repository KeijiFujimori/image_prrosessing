#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
// ここで"using namespace std;"しない。変数betaが std::beta in c++17と衝突する。
using std::cin;
using std::cout;
using std::endl;
using namespace cv;
int main( int argc, char** argv )
{
    //入力画像パスのデフォルトは../data/lena.jpg
    CommandLineParser parser( argc, argv, "{@input | ../image.jpg | input image}" );
    Mat image = imread( parser.get<String>( "@input" ) );
    if( image.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }
    //元画像と同じサイズ・タイプで、値が0埋めされた出力画像を準備
    Mat new_image = Mat::zeros( image.size(), image.type() );
    //αとβはユーザ入力
    double alpha = 1.0; /*< Simple contrast control */
    int beta = 0;       /*< Simple brightness control */
    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";    cin >> beta;

    //行・列・カラーチャネルをforで回し、各ピクセルに上式の変換を適用する
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  //saturate_cast<uchar>は値が整数でない場合や範囲外の場合に有効な値に直す
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }
    //元画像と結果を表示
    imshow("Original Image", image);
    imshow("New Image", new_image);
    //キー入力待ち
    waitKey();
    return 0;
}
