from PIL import Image, ImageDraw
from math import *
image = Image.new("RGB", (1000, 1000),(255,255,255))
draw = ImageDraw.Draw(image)

def Bezier(coorArr, i, j, t):
    if j == 0:
        return coorArr[i]
    return Bezier(coorArr, i, j - 1, t) * (1 - t) + Bezier(coorArr, i + 1, j - 1, t) * t

coorArrX=[300,500,500,600]
coorArrY=[300,250,450,300]
def plot_curve(coorArrX,coorArrY):
# plot the curve
    n=len(coorArrX)
    numSteps = 10000
    for k in range(numSteps):
        t = float(k) / (numSteps - 1)
        x = int(Bezier(coorArrX, 0, n - 1, t))
        y = int(Bezier(coorArrY, 0, n - 1, t))
        try:
            image.putpixel((x, y), (0, 0, 0))
        except:
            pass
    cr = 2 # circle radius
    for k in range(n):
        x = coorArrX[k]
        y = coorArrY[k]
        try:
            draw.ellipse((x - cr, y - cr, x + cr, y + cr), (255, 0, 0))
        except:
            pass


            
def turn_curve(coorArrX,coorArrY, alpha):
    newcoorX=[]
    newcoorY=[]
    alpha=-alpha*pi/180
    for ix,iy in zip(coorArrX,coorArrY):
        newcoorX.append(int(ix*cos(alpha)-iy*sin(alpha)))
        newcoorY.append(int(ix*sin(alpha)+iy*cos(alpha)))
    plot_curve(newcoorX,newcoorY)      

def shift_curve(coorArrX,coorArrY, deltax,deltay):
    newcoorX=[]
    newcoorY=[]
    for ix,iy in zip(coorArrX,coorArrY):
        newcoorX.append(ix+deltax)
        newcoorY.append(iy+deltay) 
    plot_curve(newcoorX,newcoorY)

def scale_curve(coorArrX,coorArrY,Mx,My):
    newcoorX=[]
    newcoorY=[]
    for ix,iy in zip(coorArrX,coorArrY):
        newcoorX.append(int(ix*Mx))
        newcoorY.append(int(iy*My)) 
    plot_curve(newcoorX,newcoorY)
            
plot_curve(coorArrX,coorArrY)        
#turn_curve(coorArrX,coorArrY, -30)  
#shift_curve(coorArrX,coorArrY, 250,250)  
#scale_curve(coorArrX,coorArrY, 1.5,1)    
        
        
image.save("Curve.png")