//this code to allow random positions of the target(moving target) <2D>
#include<cv.h>
#include<highgui.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
int main(int argc, char** argv) {
	IplImage* background=cvLoadImage("Shoote.png", CV_LOAD_IMAGE_COLOR);
	IplImage* target= cvLoadImage("3.PNG", CV_LOAD_IMAGE_COLOR);
	IplImage* shadow= cvLoadImage("NEED_ME5.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage* dest=cvClone(background);
	//cvZero(dest);
	IplImage* img=cvCreateImage(cvGetSize(background), 8, 3);
	cvZero(img);
	int width= 122;
	int height= 266;
	int upper_limit_y=303;
	int lower_limit_y=569;
	CvPoint2D32f srcT[4], desT[4];
	CvMat* warp_mat;
	warp_mat=cvCreateMat(3, 3, CV_32FC1);
	//srand(time(NULL));
	//int yelo=rand%img->width;
	cvNamedWindow("IMAGE", CV_WINDOW_NORMAL);
	int yelo=0;
	int flag=1;
	CvVideoWriter* mov=   cvCreateVideoWriter("neo.mpeg", CV_FOURCC('M','P','E','G'), 33, cvSize(1200, 900), 1);  
	CvVideoWriter* mov_cv=cvCreateVideoWriter("shadow.mpeg", CV_FOURCC('M','P','E','G'), 33, cvGetSize(background), 1);  
	while(yelo<background->width) {
		dest=cvClone(background);
		cvRectangle(dest, cvPoint(yelo, 303), cvPoint(yelo+width , 569), cvScalarAll(0), -1, 8, 0);
		srcT[0].x=0;
		srcT[0].y=0;
		srcT[1].y=0;
		srcT[1].x=target->width;
		srcT[2].y=target->height;
		srcT[2].x=0;
		srcT[3].x=target->width;
		srcT[3].y=target->height;
		
		desT[0].x=yelo;//(1)
		desT[0].y=303;
		desT[1].x=yelo+width;//(1)
		desT[1].y=303;
		desT[2].x=yelo;//(1)
		desT[2].y=569;	
		desT[3].x=yelo+width;//(1)
		desT[3].y=569;
		cvZero(img);
		cvGetPerspectiveTransform(srcT, desT, warp_mat);
		cvWarpPerspective(target, dest, warp_mat, CV_INTER_NN, cvScalarAll(0));
		cvWarpPerspective(shadow, img, warp_mat, CV_INTER_NN, cvScalarAll(0));
		IplImage* qwe=cvCreateImage(cvSize(dest->width +20, dest->height +20), 8, 3);
		IplImage* res=cvCreateImage(cvSize( 1200, 900), 8, 3); // Resolution of projector size
		cvCopyMakeBorder(dest, qwe, cvPoint(10, 10), IPL_BORDER_CONSTANT, cvScalarAll(150));
		cvResize(qwe, res, CV_INTER_NN);
		cvSetWindowProperty("IMAGE", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
		cvShowImage("IMAGE", res);
		if(cvWaitKey(33)==27) break;
		cvWriteFrame(mov, res);
		cvWriteFrame(mov_cv, img);
		yelo+=20;
		cvReleaseImage(&res);
		cvReleaseImage(&qwe);
		if(yelo==background->width) {
			if(flag==1) {
				flag=0;
				cvReleaseVideoWriter(&mov_cv);
				cvReleaseVideoWriter(&mov);
			}
			yelo=0;
		}
	}
	
}
