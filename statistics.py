import cv
import cv2
import fileinput
import os
#font=cv.CV_FONT_HERSHEY_PLAIN
font1=cv.InitFont(cv.CV_FONT_HERSHEY_PLAIN,1.0,1.0,0,3,8)
font=cv.InitFont(cv.CV_FONT_HERSHEY_PLAIN,3.0,3.0,0,3,8)
#with open('transformedPoints.txt') as f:
 #   content = f.readlines()
mas=cv.LoadImage("NEED_ME3.jpg")
rora=cv.LoadImage("Q2.png")
q=0
points=[int]*11
capo=cv.CaptureFromFile("bobo.mpeg")
red=cv.CreateImage((1200,900),8,1)
jingo=0
x=0
y=0
R=[None]*11
G=[None]*11
B=[None]*11
alpha=[None]*11
sump=0
while(1):
	telly=cv.QueryFrame(capo)
	#bingo=cv.CloneImage(telly)
	#red=cv.CreateImage(cv.GetSize(bingo),8,1)
	#bingo=cv.CloneImage(telly)
	cv.Zero(red)
	if(q==9):
		break;
	cv.Split(telly,None,None,red,None)
	(_,_,_,jingo)=cv.MinMaxLoc(red,None)
	(x,y)=jingo
	points[q]=cv.Get2D(mas,y,x)
	(B[q],G[q],R[q],alpha[q])=points[q]
	print "Points scored in shot"
	print q+1
	print "is:"
	print R[q]
	print G[q]
	print B[q]
	print alpha[q]
	cv.Circle(rora,jingo,3,cv.Scalar(0,0,255),-1,8)
	cv.PutText(rora,"YOUR SCORE IN SHOT "+str(q)+" IS: "+str(int(G[q])),(25,600+(35*q)), font,cv.Scalar(0,0,255))
	points[q]
	sump=sump+G[q]
	q+=1
#font = cv2.FONT_HERSHEY_SIMPLEX
cv.PutText(rora,"SIMULATION COMPLETED",(200,100), font,cv.Scalar(0,0,255))
cv.PutText(rora,"YOUR FINAL SCORE IS:",(150,200), font,cv.Scalar(0,200,0))
cv.PutText(rora,str(int(sump)),(700,200), font,cv.Scalar(0,0,255))

cv.SaveImage("resulty.jpg",rora)


	
	
