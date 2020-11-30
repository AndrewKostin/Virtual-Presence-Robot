import numpy as np
import cv2, os
from PIL import Image
from time import sleep

cap = cv2.VideoCapture(0)
global x_prev
global y_prev
global s_prev
x_prev, y_prev, s_prev = None, None, None

while (True):
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    #img = cv2.flip(img, -1)
    
    cascadePath = "haarcascade_frontalface_default.xml"
    faceCascade = cv2.CascadeClassifier(cascadePath)
    
    faces = faceCascade.detectMultiScale(
        gray,     
        scaleFactor=1.2,
        minNeighbors=5
    )

    
    
    
    for (x, y, w, h) in faces:
        
        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)
        
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w] 
        
        s = w * h
        x_n, y_n = x, y
        if x_prev is not None:
         
    
            """if (s > s_prev):
                if ((s/s_prev - 1) >0.0001):
                    print("b")
            elif (s < s_prev):
                if ((s_prev/s - 1) >0.0001):
                    print("f")
            """
            if (s>40000):
                print("b")
            elif (s<25600):
                print("f")
            
            elif (abs(x + w/2 - 320) > 15):
                if ((x + w/2 - 320) > 0):
                    print("r")
                else:
                    print("l")
            else:
                print("s")         
            
      
        x_prev, y_prev, s_prev = x, y, s

    print (faces)
    
    cv2.imshow('Video', img)
    
    k = cv2.waitKey(30)
    if k==27:
        break
    #sleep(0.01)
cap.release()
cv2.destroyAllWindows()
