#****************************************
# Matrix Manipulation
# Sudharsan Sundaravenkataraman
# The University of Texas at Dallas
# Homework #6
# December 9, 2022
# Macbook
# Study Group:
# Study Group Members:
#****************************************

class Matrix:
    def __init__(self, data = [[1,0,0], [0,1,0], [0, 0, 1]]): #Default value for any matrix is Identity Matrix.
        self.data = data

    def __add__(self, other):
        new_data = list() #create an empty list to store the lists containing each row
        for i in range(0, 3): # iterate through rows
            row = list() # create a separate list for each row
            for j in range(0, 3): # iterate through columns
                row.append(self.data[i][j] + other.data[i][j])  # add corresponding elements in both matrices
                                                                # and append to the row list
            new_data.append(row) # append the row into the matrix

        return Matrix(new_data) # return a new matrix with the sum of the two matrices

    def __mul__(self, other):
        new_data = list() #create an empty list to store the lists containing each row

        for i in range(0, 3): # iterate through rows
            row = list() # create a separate list for each row
            for j in range(0, 3): #iterate through columns
                sum = 0 #initialize the total sum of the matrix product for one element to zero.
                for x in range(0, 3): #iterate through each element in the first matrix's row
                                      # and each element in the second matrix's column. multiply
                                      # corresponding elements and then sum those products together to
                                      # form the element corresponding to the row number from the first
                                      # matrix and the column number of the second matrix

                    sum = sum + self.data[i][x] * other.data[x][j] #multiply element a_i_x * b_x_j
                row.append(sum)       # append the new element to the row list
            new_data.append(row) # when all the elements are determined add the row list to the matrix list.

        return Matrix(new_data) # return a new matrix with the product of the two matrices

    def __str__(self):
        result_str = str()

        for i in range(0, 3):
            result_str = result_str + "|" # add the left bracket to the row
            for j in range(0,3): #right align the digits, with a width of 5 filled with empty spaces.
                result_str = result_str +\
                "{0:{align}{width}{base}}".format(self.data[i][j], align='>', width=5, base='d')
            result_str = result_str + "|\n" # add the right bracket to the row

        return result_str

def createMatrices():
    data = list() # list of lists containing the data for the two matrices
    for x in range(0,2):
        print("\nYou will be prompted to enter in data for Matrix " + str((x+1)))
        print("corresponding to a row and column.\n")
        matrix_data = list() # matrix list for one of the two matrices
        for i in range(0, 3): # iterate through rows
            row = list() # create a separate list for each row
            for j in range(0, 3): # iterate through columns
                aij = input(
                        "Please enter a value for matrix entry (" +
                        str((i+1)) +
                        "," +
                        str((j+1)) +
                        "): "
                      ) # prompt the user for the value for matrix element ( row+1, column+1 )
                        # our loop starts with 0 but matrix elements start with 1
                row.append(aij) # append the user input for the current element into the row list.

            matrix_data.append(row) # when the row is complete append the row list to the full matrix list.

        data.append(matrix_data) # append the matrix_list to the data list that contains the data
                                 # for matrix 1 and matrix 2

    mat1 = Matrix(data[0])
    mat2 = Matrix(data[1])

    return mat1, mat2

def menu():
    print("Matrix Manipulation\n")
    print("Sudharsan Sundaravenkataraman\n");
    print("CS5303-001\n");
    print("December 9, 2022\n");
    print("--------------------------\n")

    done = False

    A = Matrix()
    B = Matrix()

    while (not done):

        print("1. Create Matrices\n")
        print("2. Multiply Matrices\n")
        print("3. Add Matrices\n")
        print("4. Quit\n")
        print("--------------------------\n\n")
        a = input("Please choose:")

        if (a == 1):
            A, B = createMatrices()

        elif (a == 2):
            print("\n")
            print(A)
            print(B)
            result = A * B
            print(result)

        elif (a == 3):
            print("\n")
            print(A)
            print(B)
            result = A + B
            print(result)

        elif (a == 4):
            done=True

        else:
            print("Silly human. That was not an option!")

        print("\n")

    return


#Main
def main():
    menu() #call the menu function from the main method.

main() #call the main method to run the program.
