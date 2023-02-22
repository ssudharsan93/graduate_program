import turtle

def sierpinski(length, depth):

    #Draw a dot
    if depth > 1:
        turtle.dot()
        
    #If statement for recursion    
    if depth==0:
        turtle.stamp() #End Case
    else: #Recursion Case
        for i in range(0,3):
            turtle.forward(length)
            sierpinski(length/2,depth-1)
            turtle.backward(length)
            turtle.left(120)#120*3=360 degrees of the circle
            
#MAIN            
turtle.speed(0)
sierpinski(350,7)
turtle.exitonclick()