#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv; 
using namespace std;

int main(void) {


    Mat img = imread("/home/keiji/image_processing/0.jpg");

        cout<<
        "横幅=" << img.cols                                                               
        << "," <<
        "縦幅=" << img.rows
        << endl;

    imshow("View", img);

    waitKey();

    return 0;


}