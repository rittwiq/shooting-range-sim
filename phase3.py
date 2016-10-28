import cv2
import cv
import sys
import os
import subprocess


frames=[None]*229
loadframes=[None]*229	
xjay=[None]*229
yjay=[None]*229
'''check=subprocess.Popen("./foo_1 runin.jpg", shell=True)
cv.NamedWindow("Shooting Simulator",1)
while(1):
	
	getready1=cv.WaitKey(33)
	if getready1==121:
		check.terminate()
		rew=subprocess.Popen("./foo_1 pop2.png", shell=True) #Run program in parallel
		print "Callibrating please wait....(Warning:Do not disturb the camera setup) "
		os.system("./calibration")
		rew.terminate()
		rew1=subprocess.Popen("./foo_1 Q2.png", shell=True)
		break
	if getready1==110:
		check.terminate()
		rew1=subprocess.Popen("./foo_2", shell=True)
		break
		
'''	
capo_init = cv.CaptureFromCAM(1)
cv.WaitKey(1000)
first=cv.QueryFrame(capo_init)
cv.WaitKey(3000)
use=cv.CloneImage(first)
red=cv.CreateImage(cv.GetSize(use),8,1)
del capo_init		
minVal=0
maxVal=0
maxloc=[None]*229
locofinal=[None]*229

capture = cv.CaptureFromCAM(1)	
cap = cv2.VideoCapture("./neo1.mpeg")
capc = cv2.VideoCapture("./gusto.mpeg")
x=1
cv.WaitKey(3000)
print "FIRE!!!!"
cv.NamedWindow("Video", cv2.WND_PROP_FULLSCREEN);
while 1:
		#frame =cv.QueryFrame(cap)
		ret,frame=cap.read()
		if ret==False: break
		src = cv.fromarray(frame)
		#cv.MoveWindow("Video",)
		
		cv.MoveWindow("Video", 1366, 0)
		cv.SetWindowProperty("Video", cv2.WND_PROP_FULLSCREEN, cv2.cv.CV_WINDOW_FULLSCREEN)
		cv.ShowImage("Video",src)
		#frameCam=cv.QueryFrame(capture)
		frameCam=cv.QueryFrame(capture)
		#framec=cv.QueryFrame(capc)
		ret,framec=capc.read()
		live=cv.CloneImage(frameCam)
		cv.Zero(use)
		framec = cv.fromarray(framec)
		cv.Sub(live,framec,use)
		cv.Split(use,None,None,red,None)
		(minVal,maxVal,_,maxloc[x-1])=cv.MinMaxLoc(red,None)
		(xjay[x-1],yjay[x-1])=maxloc[x-1]
		if maxVal<60 :
				xjay[x-1]=0
				yjay[x-1]=0
		frames[x-1]=live	
		x=x+1
		print maxVal
		cv.ShowImage("Hi",use)
		cv.WaitKey(33)
print "Simulation Complete"
i=0
video=cv.CreateVideoWriter("fun.mpeg",cv.CV_FOURCC('M','P','E','G'),30,cv.GetSize(frames[1]), is_color=True)
#video=cv.CreateVideoWriter("fun",0,30,cv.GetSize(frames[1]), is_color=True)
while 1 :
	
	if frames[i]==None : break
	cv.ShowImage("Shooting Simulator",frames[i])
	loadframes[i]=cv.CloneImage(frames[i])
	cv.Zero(loadframes[i])
	cv.Set2D(loadframes[i],yjay[i],xjay[i],cv.Scalar(230,230,230))
	cv.WriteFrame(video,loadframes[i])
	
	i=i+1
	cv.WaitKey(33)
print maxloc
#rew1.terminate()

	
		


	
    
