#include<cv.h>
#include<highgui.h>
	
int main(int argc, char** argv) {
	IplImage* background=cvLoadImage("Shoote.png", CV_LOAD_IMAGE_COLOR);
	IplImage* target= cvLoadImage("3.PNG", CV_LOAD_IMAGE_COLOR);
	//IplImage* shadow= cvLoadImage("NEED_ME5.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage* dest=cvClone(background);
	//IplImage* dum=cvClone(background);
	//IplImage* dest=cvCreateImage(cvSize(1200, 900), 8, 3);
	//cvResize(dum, dest, CV_INTER_NN); 
	//cvZero(dest);
	IplImage* img=cvCreateImage(cvSize(1200, 900), 8, 1);
	cvZero(img);
	CvCapture* cap=cvCreateCameraCapture(1);
	IplImage* frames;
	IplImage* framed[65];	
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
	cvMoveWindow("IMAGE", 1366, 0);
	int yelo=1;
	int flag=0;
//1100 176
	CvVideoWriter* mov=   cvCreateVideoWriter("neo1.mpeg", CV_FOURCC('M','P','E','G'), 33, cvSize(1200, 900), 1);  
	CvVideoWriter* mov_cv=cvCreateVideoWriter("shadow2.mpeg", CV_FOURCC('M','P','E','G'), 33, cvSize(1200, 900), 0);
	CvVideoWriter* alsi=  cvCreateVideoWriter("gusto.mpeg",  CV_FOURCC('M','P','E','G'), 33, cvSize(cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_WIDTH), cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT)), 1);
	int i=0;
	cvReleaseCapture(&cap);
	while(yelo<background->width) {
		dest=cvClone(background);
		//cvRectangle(dest, cvPoint(yelo, 303), cvPoint(yelo+width , 569), cvScalarAll(0), -1, 8, 0);
		/*srcT[0].x=0;
		srcT[0].y=0;
		srcT[1].y=0;
		srcT[1].x=target->width;
		srcT[2].y=target->height;
		srcT[2].x=0;
		srcT[3].x=target->width;
		srcT[3].y=target->height;
		
		desT[0].x=img->width-yelo;//(1)
		desT[0].y=100;
		desT[1].x=img->width-yelo+width;//(1)
		desT[1].y=100;
		desT[2].x=img->width-yelo;//(1)
		desT[2].y=100+height;	
		desT[3].x=img->width-yelo+width;//(1)
		desT[3].y=100+height;
		cvZero(img);
		cvGetPerspectiveTransform(srcT, desT, warp_mat);
		cvWarpPerspective(target, dest, warp_mat, CV_INTER_NN, cvScalarAll(0));
		cvWarpPerspective(shadow, img, warp_mat, CV_INTER_NN, cvScalarAll(0));
		*/
		cvZero(img);
		cvCircle(dest, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 40, cvScalar(0 , 99, 0,  0), -1, 8, 0);
		cvCircle(dest, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 30, cvScalar(99,  0, 0, 0), -1, 8, 0);
		cvCircle(dest, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 20, cvScalar(0 , 99, 0, 0), -1, 8, 0);
		cvCircle(dest, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 10, cvScalar(0,   0, 0, 0), -1, 8, 0);

		cvCircle(img, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 40, cvScalarAll(10), -1, 8, 0);
		cvCircle(img, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 30, cvScalarAll(20), -1, 8, 0);
		cvCircle(img, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 20, cvScalarAll(40), -1, 8, 0);
		cvCircle(img, cvPoint(yelo, pow(img->width/2-yelo, 2)/img->width/3 +40), 10, cvScalarAll(100), -1, 8, 0);

		

		IplImage* qwe=cvCreateImage(cvSize(dest->width +20, dest->height +20), 8, 3);
		IplImage* res=cvCreateImage(cvSize( 1200, 900), 8, 3); // Resolution of projector size
		cvCopyMakeBorder(dest, qwe, cvPoint(10, 10), IPL_BORDER_CONSTANT, cvScalarAll(150));
		cvResize(qwe, res, CV_INTER_NN);
		cvSetWindowProperty("IMAGE", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
		cvShowImage("IMAGE", res);
		if(cvWaitKey(33)==27) break;
		if(flag==1) {
			cap=cvCreateCameraCapture(1);
			frames=cvQueryFrame(cap);
			framed[i]=cvClone(frames);
			cvReleaseCapture(&cap);
			i++;
		}
		if(flag==0) {
			cvWriteFrame(mov, res);
			cvWriteFrame(mov_cv, img);
		}
		yelo+=20;
		cvReleaseImage(&res);
		cvReleaseImage(&qwe);
		if(yelo>=background->width) {
			flag++;
			if(flag==1) {
				cvReleaseVideoWriter(&mov_cv);
				cvReleaseVideoWriter(&mov);
			}
			if(flag==2) break;
			yelo=0;
		}
	}
	//printf("YO");
	for(i=0;i<65;i++) {
	//	printf("LOL");
		cvWriteFrame(alsi, framed[i]);
	}
	cvReleaseVideoWriter(&alsi);
	//printf("YO");
	//long t;
	//for(t=0;t<100000000;t++);
	//printf("%d", i);
	cvReleaseImage(&background);
	cvReleaseImage(&target);
	cvReleaseImage(&img);
	cvReleaseImage(&dest);
//	cvReleaseImage(&shadow);
//	cvReleaseImage(&dum);
	IplImage* frame, *f2;
	cvNamedWindow("KOK", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("KOK", 0, 0);
	//printf("yoyoyoyoyo");
	i=0;
	CvCapture* capt=cvCreateFileCapture("neo1.mpeg");
	CvCapture* capt1=cvCreateFileCapture("gusto.mpeg");
	while(1) {
		f2=cvQueryFrame(capt1);
		frame=cvQueryFrame(capt);
		if(frame==NULL) break;  
		cvShowImage("IMAGE", frame);
		if(f2!=NULL) {
			cvShowImage("KOK", f2);
		}
		cvWaitKey(0);
		i++;
//		printf("%d", i);
		//char c=cvWaitKey(33);
		//if(c==27) break;
		
	}
}
