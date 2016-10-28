#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<iostream>
#include <fstream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

double minVal; double maxVal;
Point val;
Point minLoc, maxLoc;

//transform the image point to World point
cv::Point2f transformPoint(cv::Point2f current, cv::Mat transformation)
{
	cv::Point2f transformedPoint;
	transformedPoint.x = current.x * transformation.at<double>(0,0) + current.y * transformation.at<double>(0,1) + transformation.at<double>(0,2);
	transformedPoint.y = current.x * transformation.at<double>(1,0) + current.y * transformation.at<double>(1,1) + transformation.at<double>(1,2);
	float z = current.x * transformation.at<double>(2,0) + current.y * transformation.at<double>(2,1) + transformation.at<double>(2,2);
	transformedPoint.x /= z;
	transformedPoint.y /= z;

	return transformedPoint;
}

int main()
{

	//read from test.yml
	FileStorage fs2("test.yml", FileStorage::READ);
	Mat image2World;
	fs2["mapping"] >> image2World;
	fs2.release();
//	int fps=30;
	cv::VideoCapture capture;
	capture.open("fun.mpeg");
	double fps = capture.get( CV_CAP_PROP_FPS );
	cv::Size size(1200,900);
	Mat tmp;
	//ofstream myfile;
 	//myfile.open ("transformedPoints.txt");
	cv::VideoWriter writer;
	writer.open( "bobo.mpeg", CV_FOURCC('M','P','E','G'), fps, size, false );	
	//VideoWriter::VideoWriter("fun.mpeg",CV_FOURCC('M','P','E','G'),30,size,true);
	
	while(1)
	{
		Mat frame;
		capture >> frame;
		
		if( frame.empty() ) break;
		Mat frame1= Mat::zeros(900,1200,CV_8UC1);
		cvtColor(frame, frame, CV_RGB2GRAY);
		//imshow("test2",frame);
		//waitKey(0);
		minMaxLoc( frame, &minVal, &maxVal, &minLoc, &maxLoc );
		//frame.setTo(cv::Scalar::all(0));
		cv::Point2f t = transformPoint(maxLoc, image2World);
		//cv::Point2f t1 = transformPoint(Point(320,290), image2World);
		//myfile<<t<<endl;
		//cout<<"hi"<<t1<<endl;
		cout<<t<<endl;
		//waitKey(0);
		//frame.set2D(t,cv::Scalar(255,255,255));
		//cout<<t.y<<" "<<t.x<<endl;
	        /*frame1.at<cv::Vec3b>(t.y,t.x)[0] = 255;
		frame1.at<cv::Vec3b>(t.y,t.x)[1] = 255;
		frame1.at<cv::Vec3b>(t.y,t.x)[2] = 255;
		*/
		rectangle(frame1, t, t, cv::Scalar(255, 255, 255), 1, 8, 0);
		//cout<<t<<endl;
		
		//imshow("test",frame1);
		writer << frame1;
		char c = cv::waitKey(33);
		if( c == 27 ) break;	
	}
	//myfile.close();
	capture.release();
	
}
