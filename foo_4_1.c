#include<cv.h>
#include<highgui.h>
#include<stdio.h>
#include<math.h>
int shot=0, x, y;
IplImage* img;
CvPoint bullet;
void mouseCall(int evt, int mx, int my, int flag, void* param) {
	IplImage* tmp=(IplImage*) param;
	if(evt==CV_EVENT_LBUTTONDBLCLK) {
		if(mx>abs(sqrt( 40*40 - pow((y -my),2) ) ) ) {
			shot=1;
			bullet.x=mx;
			bullet.y=my;
		}
	}
} 



int main(int argc, char** argv) {
	IplImage* init=cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);	//CHOOSE FROM A VARIETY OF BACKGROUNDS
	IplImage* background=cvCreateImage(cvSize(1200, 900), 8, 3);	//RESIZING TO THE REQUIRED DIMENSIONS
	cvResize(init, background, CV_INTER_NN);
	img=cvClone(background);
	IplImage* tmp=cvClone(background);
	x=0; y=0;int flag=0;
	cvNamedWindow("IMAGE", CV_WINDOW_NORMAL);
	cvSetWindowProperty("IMAGE", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	cvSetMouseCallback("IMAGE", mouseCall, tmp);
	while(x<img->width) {
		if(shot==0) {
			y=pow(img->width/2-x, 2)/img->width/3 +40;
			cvCircle(img, cvPoint(x, y), 40, cvScalar(255, 0, 0, 0), -1, 8, 0);
			cvCircle(img, cvPoint(x, y), 30, cvScalar(0,   0, 0, 0), -1, 8, 0);
			cvCircle(img, cvPoint(x, y), 20, cvScalar(255, 0, 0, 0), -1, 8, 0);
			cvCircle(img, cvPoint(x, y), 10, cvScalar(0,   0, 0, 0), -1, 8, 0);
			cvCircle(img, cvPoint(x, y),  1, cvScalar(0,   0, 0, 0), -1, 8, 0); 
		}
		if(shot==1) {
			printf("YO");
			int i=0, j=0;
			while(1) {
				printf("%d %d \n", i, j);
				cvEllipse(img, cvPoint(x, y), cvSize(40-j, 40-i/2  ), 0, 0, 360, cvScalar(255, 0, 0, 0), -1, 8, 0);
				cvEllipse(img, cvPoint(x, y), cvSize(30-j, 30-i*3/8), 0, 0, 360, cvScalarAll(0), -1, 8, 0);
				cvEllipse(img, cvPoint(x, y), cvSize(20-j, 20-i*1/4), 0, 0, 360, cvScalar(255, 0, 0, 0), -1, 8, 0);
				cvEllipse(img, cvPoint(x, y), cvSize(10-j, 10-i*1/8), 0, 0, 360, cvScalarAll(0 ), -1, 8, 0);
				cvEllipse(img, cvPoint(x, y), cvSize(1   , 1-i*1/80), 0, 0, 360, cvScalarAll(255), -1, 8, 0);
				//cvEllipse(img, bullet,        cvSize(1,    1-i*1/40), 0, 0, 360, cvScalarAll(0), -1, 8, 0);
				y+=5;
				if(i<40) i+=5;
				else i-=5;
				if(j>20) j+=5;
				cvShowImage("IMAGE", img);
				char c=cvWaitKey(33);
				if(c==27) break;
				img=cvClone(background);
				if(y>370) {
					background=cvClone(img);
					flag=1;
					break;
				}
			}
		}
		cvShowImage("IMAGE", img);
		char c=	cvWaitKey(33);
		if(c==27) break;
		if(flag==1) break;
		img=cvClone(background);
		x+=10;
	}
}	
		
