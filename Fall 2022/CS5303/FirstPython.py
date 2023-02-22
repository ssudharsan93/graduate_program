
def menu():
    done=False
    while (not done):
        print("1. Red")
        print("2. Blue")
        print("q. Quit")
        print("-"*16)
        a=input("Please choose:")
        print(a)
        #No switch statement in python!
        if (a=='1'):
            print ("Roses are red")
            print ("And pink. And White")
            print ("Check out Tyler Texas!")
        elif (a=='2'):
            print ("Violets are Blue")
            print("No! Violets are Purple!")
            print("Wild violets are blue!")
        elif (a=='q'):
            done=True
        else:
            print("Silly human. That was not an option!")


    return

def linear(m,x,b):
    y=m*x+b
    return y


#Main
print("Program Begins")
print("*"*40)
print ("Good morning, Class. Is everyone sitting comfortably?")
print("*"*40)
y=linear(2,2,-2)
print (y)
print("*"*40)
for x in range(-10,11):
    y=linear(2,x,-2)
    print ("(",end="")
    print (x,end=",")
    print (y,end=")")
    print()
print("*"*40)
menu()







print ("Program Ends")
