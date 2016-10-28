#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


vector<vector<Point2f> > pointbuf;
bool found=0;

int main()
{


	Mat gry;
	cv::VideoCapture cap;
	cap.open(1);
	cv::Mat frame,tgry,dest;
	vector<Point2f> pointbuf;
	while( 1 )
	{
		cap >> frame;
		if( !frame.data ) break; // Ran out of film
		cv::namedWindow("Example3",CV_WINDOW_AUTOSIZE);
		cv::imshow( "Example3", frame );
		cvtColor(frame, tgry, CV_BGR2GRAY);
		cv::adaptiveThreshold(tgry,dest,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,71, 5);
		imshow( "Example4", dest );
		//imshow( "Example5", tgry );
		found = findChessboardCorners( dest, Size(14,13), pointbuf,CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
		if(found)break;
		cout<<found;
		if( cv::waitKey(33) >= 0 ) break;
	}

	//chessboard detection
	cv::namedWindow("Example4",CV_WINDOW_AUTOSIZE);
    	cv::imshow( "Example4", dest );
	cvtColor(frame, gry, CV_BGR2GRAY);
	cornerSubPix( gry, pointbuf, Size(11,11),Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
        drawChessboardCorners(frame, Size(14,13), pointbuf, found);
	imshow("RGB",frame);
	
	//mapping from image to world coordinates
	std::vector<cv::Point2f> imageLocs;
	
	imageLocs.push_back(pointbuf[0]);
	imageLocs.push_back(pointbuf[13]);
    	imageLocs.push_back(pointbuf[168]);
    	imageLocs.push_back(pointbuf[181]);
    	/* 1000x
	/*points
	(29,22)
	(969,22)
	(28,704)
	(969,704)
	*/
	
	std::vector<cv::Point2f> worldLocs;
 		
	worldLocs.push_back(cv::Point2f(62,53));
    	worldLocs.push_back(cv::Point2f(1151,53));
   	worldLocs.push_back(cv::Point2f(62,845));
    	worldLocs.push_back(cv::Point2f(1151,845));
	
	//perspective transformation
	cv::Mat image2World = cv::getPerspectiveTransform(imageLocs, worldLocs);
	
	
	FileStorage fs("test.yml", FileStorage::WRITE);
	fs << "mapping"<<image2World;
	fs.release();





	
    	waitKey(0);
}


