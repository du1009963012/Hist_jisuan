#include <opencv2\opencv.hpp>
#include <iostream>
#include <fstream>
using namespace std;

using namespace cv;

int main() {
	VideoCapture cap;
	Mat src;
	cap.open("E:\\MyProject\\Reimu.mp4");
	ofstream out("1out.txt");
	
	cap >> src;
	if (!src.data) {
		return -1;
	}
	int sizeHist = 256;
	float rang[] = {0,256};
	const float *rangHist = { rang };
	namedWindow("input_img",WINDOW_AUTOSIZE);
	namedWindow("output_img",WINDOW_AUTOSIZE);
	bool f = true;
	Mat *Mat_arry=new Mat[3];
	//out.open("1.txt", 'w+');
	while (waitKey(30) != 27) {
		cap >> src;
		resize(src,src,src.size()/4);
		
		split(src, Mat_arry);
		Mat b_change, g_change, r_change;
		calcHist(&Mat_arry[0],1,0,Mat(),b_change,1,&sizeHist,&rangHist,true,false);
		calcHist(&Mat_arry[1], 1, 0, Mat(), g_change, 1, &sizeHist, &rangHist, true, false);
		calcHist(&Mat_arry[2], 1, 0, Mat(), r_change, 1, &sizeHist, &rangHist, true, false);
		int Hist_h = src.rows;
		int Hist_w = src.cols;
		int bin_w = Hist_w / sizeHist;
		Mat Hist_img(Hist_h,Hist_w,CV_8UC3,Scalar(0,0,0));
		normalize(b_change,b_change,0,Hist_h,NORM_MINMAX,-1,Mat());
		normalize(g_change, g_change, 0, Hist_h, NORM_MINMAX, -1, Mat());
		normalize(r_change, r_change, 0, Hist_h, NORM_MINMAX, -1, Mat());
		
			if (out.is_open())
			{
				out <<"b通道"<<b_change<<"\n";
				out << "g通道" << g_change << "\n";
				out << "r通道" << r_change;
				
				out.close();
				f = false;
			}
		
		
		
		for (int i = 1; i < sizeHist; i++) {
			line(Hist_img,Point((i-1)*bin_w,cvRound(b_change.at<float>(i-1))),Point(i*bin_w,b_change.at<float>(i)),Scalar(255,0,0),1,CV_AA);
			line(Hist_img, Point((i - 1)*bin_w, cvRound(g_change.at<float>(i - 1))), Point(i*bin_w, g_change.at<float>(i)), Scalar(0, 255, 0), 1, CV_AA);
			line(Hist_img, Point((i - 1)*bin_w, cvRound(r_change.at<float>(i - 1))), Point(i*bin_w, r_change.at<float>(i)), Scalar(0, 0, 255), 1, CV_AA);
		}
		imshow("input_img", src);
		//imshow("output_img",);
		imshow("Hist_img", Hist_img);
	}
	
	
	
	
	
}