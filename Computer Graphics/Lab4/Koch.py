from turtle import *
from Tkinter import *
import canvasvg

def snowflake(lengthSide, levels):
    if levels == 0:
        forward(lengthSide)
        return
    lengthSide /= 3.0
    snowflake(lengthSide, levels-1)
    left(90)
    snowflake(lengthSide, levels-1)
    right(180)
    snowflake(lengthSide, levels-1)
    left(90)
    snowflake(lengthSide, levels-1)
if __name__ == "__main__":
    speed(0)
    ht()
    length = 700.0
    penup()
    backward(length/2.0)
    pendown()
    snowflake(length, 3)
    ts = getscreen().getcanvas()
    canvasvg.saveall("Kochlevel3.svg", ts)
    clear()
    penup()
    backward(length/2.0)
    pendown()
    snowflake(length, 4)
    ts = getscreen().getcanvas()
    canvasvg.saveall("Kochlevel4.svg", ts)
    clear()
    penup()
    backward(length/2.0)
    pendown()
    snowflake(length, 5)
    ts = getscreen().getcanvas()
    canvasvg.saveall("Kochlevel5.svg", ts)