from __future__ import division
import sys 
from PIL import Image
from time import *
 
exp=[]
 
def _fpart(x):
    return x - int(x)
 
def _rfpart(x):
    return 1 - _fpart(x)
 
def putpixel(img, xy, color, alpha=1):
    
    c = tuple(map(lambda bg, fg: int(round(alpha * fg + (1-alpha) * bg)),
                  img.getpixel(xy), color))
    img.putpixel(xy, c)
 
def wuline(x1,y1,x2,y2, color,image):
    starclock=clock()
    dx, dy = x2-x1, y2-y1
    steep = abs(dx) < abs(dy)
    p = lambda px, py: ((px,py), (py,px))[steep]
 
    if steep:
        x1, y1, x2, y2, dx, dy = y1, x1, y2, x2, dy, dx
    if x2 < x1:
        x1, x2, y1, y2 = x2, x1, y2, y1
 
    grad = dy/dx
    intery = y1 + _rfpart(x1) * grad
    def draw_endpoint(pt):
        x, y = pt
        xend = round(x)
        yend = y + grad * (xend - x)
        xgap = _rfpart(x + 0.5)
        px, py = int(xend), int(yend)
        putpixel(image, (px, py), color, _rfpart(yend) * xgap)
        putpixel(image, (px, py+1), color, _fpart(yend) * xgap)
        return px
 
    xstart = draw_endpoint(p(*(x1,y1))) + 1
    xend = draw_endpoint(p(*(x2,y2)))
 
    for x in range(xstart, xend):
        y = int(intery)
        putpixel(image, p(x, y), color, _rfpart(intery))
        putpixel(image, p(x, y+1), color, _fpart(intery))
        intery += grad
    exp.append({'name':"Wu",'clock':(clock()-starclock)})	
    #image.save("wuline.jpg")	
 
 
def bresenham_circle(x0, y0, radius, color, image):
    starclock=clock()
    f = 1 - radius
    ddf_x = 1
    ddf_y = -2 * radius
    x = 0
    y = radius
    image.putpixel((x0, y0 + radius), color)
    image.putpixel((x0, y0 - radius), color)
    image.putpixel((x0 + radius, y0), color)
    image.putpixel((x0 - radius, y0), color)
 
    while x < y:
        if f >= 0: 
            y -= 1
            ddf_y += 2
            f += ddf_y
        x += 1
        ddf_x += 2
        f += ddf_x    
        image.putpixel((x0 + x, y0 + y), color)
        image.putpixel((x0 - x, y0 + y), color)
        image.putpixel((x0 + x, y0 - y), color)
        image.putpixel((x0 - x, y0 - y), color)
        image.putpixel((x0 + y, y0 + x), color)
        image.putpixel((x0 - y, y0 + x), color)
        image.putpixel((x0 + y, y0 - x), color)
        image.putpixel((x0 - y, y0 - x), color)
    exp.append({'name':"Bresenham Circle",'clock':(clock()-starclock)})	
    #image.save("breswnham_circle.jpg")	
	
def test_time():
    ttest=[]
    img4 = Image.new("RGB", (500,500), white)
    c=4
    for i in range(1000):
        wuline(10, 10, 450, 150,black,img4)
        bresenham_line(10,10,450,150,black,img4)
        bresenham_circle(250,250,100,black,img4)
        bresenham_ellipse(250,250,200,50,black,img4)
        dda_line(10,10,450,150,black,img4)
    for elem in exp:
        if c>=0: 
            ttest.append(elem)
            c-=1
        else:
            for telem in ttest:
                if elem['name']==telem['name']:
                    telem['clock']+=elem['clock']
    return ttest    
        
        
        
    
def dda_line(x1, y1, x2, y2, color, image):
    starclock=clock()
    dy = y2 - y1
    dx = x2 - x1
    if abs(dx) > abs(dy):
        steps = dx
    else:
        steps = dy
    xIncrement = float(dx) / float(steps)
    yIncrement = float(dy) / float(steps)
    image.putpixel((x1, y1), color)
    for i in range(steps):
        x1 += xIncrement
        y1 += yIncrement
        image.putpixel((int(round(x1)), int(round(y1))), color)	
    exp.append({'name':"DDA Line",'clock':(clock()-starclock)})
    #image.save("dda_line.jpg")	
 
def bresenham_line(x1,y1,x2,y2,color,image):
    starclock=clock()
    dx=abs(x1-x2)
    dy=abs(y1-y2)
    sx=-1
    sy=-1
    if x2>x1:
        sx=1
    if y2>y1:
        sy=1
    error=dx-dy
    while x1!=x2 or y1!=y2:
        image.putpixel((x1,y1),color)
        error_=error
        if error_>-dy:
            error-=dy
            x1+=sx
        if error_<dx:
            error+=dx
            y1+=sy
    exp.append({'name':"Bresenham Line",'clock':(clock()-starclock)})
    #image.save("bresenham_line.jpg")
	
def bresenham_ellipse(x0,y0,width,height,color,image):
    #a2,b2,fa2,fb2,x,y,sigma
    starclock=clock()
    a2=width*width
    b2=height*height
    fa2=4*a2
    fb2=4*b2
	
    #first half
    x = 0
    y = height
    sigma = 2*b2+a2*(1-2*height)
    while b2*x <= a2*y:
        image.putpixel((x0 + x, y0 + y), color)
        image.putpixel((x0 - x, y0 + y), color)
        image.putpixel((x0 + x, y0 - y), color)
        image.putpixel((x0 - x, y0 - y), color)
        if sigma>=0:
            sigma+=fa2*(1-y)
            y-=1
        sigma+=b2*(4*x+6)
        x+=1
	#second half
    x = width
    y = 0
    sigma = 2*a2+b2*(1-2*width)
    while a2*y<=b2*x:
        image.putpixel((x0 + x, y0 + y), color)
        image.putpixel((x0 - x, y0 + y), color)
        image.putpixel((x0 + x, y0 - y), color)
        image.putpixel((x0 - x, y0 - y), color)
        if sigma>=0:
            sigma+=fb2*(1-x)
            x-=1
        sigma+=a2*(4*y+6)
        y+=1
    exp.append({'name':"Bresenham Ellipse",'clock':(clock()-starclock)})	
    #image.save("bresenham_ellipse.jpg")
	
	
def print_time(expr):
    print "Time to draw 1000 lines(in seconds)"
    for alg in expr:
        print alg['name'],
        print alg['clock']	
	
def draw_lastname(color,image):
    bresenham_line(10,160,60,60,color,image)
    bresenham_line(60,10,60,160,color,image)
    bresenham_line(60,10,20,10,color,image)
    bresenham_line(20,10,10,15,color,image)
    bresenham_line(10,15,10,50,color,image)
    bresenham_line(10,50,20,60,color,image)
    bresenham_line(20,60,60,60,color,image)
    
    bresenham_line(70,10,70,160,color,image)
    bresenham_line(120,10,70,75,color,image)
    bresenham_line(70,75,120,160,color,image)
    
    bresenham_ellipse(150,85,30,75,color,image)
    
    bresenham_line(190,10,190,160,color,image)
    bresenham_line(190,10,230,10,color,image)
    bresenham_line(190,160,230,160,color,image)
    bresenham_line(190,60,230,60,color,image)
    bresenham_line(230,10,240,20,color,image)
    bresenham_line(230,160,240,150,color,image)
    bresenham_line(230,60,240,50,color,image)
    bresenham_line(190,60,240,80,color,image)
    bresenham_line(240,80,240,150,color,image)
    bresenham_line(240,50,240,20,color,image)
    
    bresenham_line(250,10,250,160,color,image)
    bresenham_line(250,85,300,85,color,image)
    bresenham_line(250,10,300,10,color,image)
    bresenham_line(250,160,300,160,color,image)
    
    bresenham_line(310,10,310,160,color,image)
    bresenham_line(360,10,360,160,color,image)
    bresenham_line(310,85,360,85,color,image)
    
    bresenham_line(370,10,370,160,color,image)
    bresenham_line(420,10,370,75,color,image)
    bresenham_line(370,75,420,160,color,image)
    
    bresenham_ellipse(450,85,30,75,color,image)  
    image.save("lastname.png")
    
def draw_lines(color,image):
    dda_line(10,10,450,150,color,image)
    bresenham_line(10,100,450,250,color,image)
    wuline(10, 200, 450, 350,color,image)
    image.save("Lines.png")

def draw_circles(color,image):
    bresenham_circle(150,250,75,color,image)
    bresenham_ellipse(350,100,100,50,color,image)  
    bresenham_ellipse(350,350,50,100,color,image)
    image.save("Circles.png")

white=(255,255,255)
black = (0, 0, 0)
img1 = Image.new("RGB", (500,400), white)
img2 = Image.new("RGB", (500,500), white)
img3 = Image.new("RGB", (500,170), white)
#wuline(10, 10, 450, 150,black,img1)
#bresenham_line(10,10,450,150,black,img2)
#bresenham_circle(250,250,100,black,img3)
#bresenham_ellipse(250,250,200,50,black,img4)
#dda_line(10,10,450,150,black,img5)
tttime=test_time()
print_time(tttime)
draw_lines(black,img1)
draw_circles(black,img2)
#draw_lastname(black,img3)
#print_time(exp)
    