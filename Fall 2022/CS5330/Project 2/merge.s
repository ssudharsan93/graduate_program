# Sudharsan Sundaravenkataraman
# NetID : sxs220093
# Comet ID: 2021668140
	.data

solution:      .word    0
arg:	       .word    1,4,6,9
size_arg:      .word    4
arg2:	       .word    0,2,3,7
size_arg2:     .word    4
#arg3:         .word    -3, 0, 6
#size_arg3     .word    3
#arg4:         .word    -2, 0, 4, 5, 9
#size_arg4     .word    5


	.text
	.globl main

load_data:

              la       $s0, arg                     # loads the address of arg into s0
              la       $s1, arg2                    # loads the address of arg2 into s1
              la       $s3, size_arg                # loads the address of the size of arg into s2
              la       $s4, size_arg2               # loads the address of the size of arg into s3
              la       $s5, solution                # loads the address of solution into s5
              
              lw       $t3, 0($s3)                  # loads the size of arg into t3
              lw       $t4, 0($s4)                  # loads the size of arg2 into t4

main:
              lw       $t0, 0($s0)
              lw       $t1, 0($s1)
              
              li       $v0, 1                       # print the element
              move     $a0, $t0
              syscall
              
              li       $v0, 11                       # print the element
              li       $a0, 44
              syscall
              
              li       $v0, 1                       # print the element
              move     $a0, $t1
              syscall
              
              beq      $t3, $zero, rest_of_arg2     # if there are no more elements in arg store the rest of arg2
              beq      $t4, $zero, rest_of_arg      # if there are no more elements in arg2 store the rest of arg
              
              slt      $t2, $t0, $t1                # if t0 < t1 t2 is 1
              beq      $t2, $zero, add_second       # Add second element if t0 > t1
              sw       $t0, 0($s5)                  # store the smaller value into solution array
              addi     $s0, $s0, 4                  # move pointer to array 'arg' up one position
              addi     $s5, $s5, 4                  # move pointer to array 'solution' up one position
              subi     $t3, $t3, 1                  # there is one less argument in arg
              j        main

add_second:
              sw       $t1, 0($s5)                  # store the smaller value into solution array
              addi     $s1, $s1, 4                  # move pointer to array 'arg2' up one position
              addi     $s5, $s5, 4                  # move pointer to array 'solution' up one position
              subi     $t4, $t4, 1                  # there is one less element in arg2
              j        main
              
rest_of_arg:                                        # store the rest of the elements in arg
              beq      $t3, $zero, exit
              sw       $t0, 0($s5)                  # store the smaller value into solution array
              addi     $s0, $s0, 4                  # move pointer to array 'arg' up one position
              addi     $s5, $s5, 4                  # move pointer to array 'solution' up one position
              subi     $t3, $t3, 1                  # there is one less argument in arg
              j        rest_of_arg

rest_of_arg2:                                       # store the rest of the elements in arg2
              beq      $t4, $zero, exit
              sw       $t1, 0($s5)                  # store the smaller value into solution array
              addi     $s1, $s1, 4                  # move pointer to array 'arg2' up one position
              addi     $s5, $s5, 4                  # move pointer to array 'solution' up one position
              subi     $t4, $t4, 1                  # there is one less element in arg2
              j        rest_of_arg2
              
exit:
              la       $s0, solution                # load the address of solution into s0
              lw       $t1, 0($s3)                  # get the total size of the remaining array
              lw       $t2, 0($s4)                  
              add      $t1, $t1, $t2
              
print_solution:
              lw       $t0, 0($s0)                  # load the element at the current index of solution into t0

              li       $v0, 1                       # print the element
              move     $a0, $t0
              syscall
              
              subi     $t1, $t1, 1                  # number of remaining elements decreases by 1
              
              beq      $t1, $zero, terminate        # jump to terminate if the number of remaining elements is zero
              li       $v0, 11                      # otherwise print a comma
              li       $a0, 44
              syscall
              
              addi     $s0, $s0, 4                  # change the index to correspond to the next element of solution
              j        print_solution
              
terminate:
              li       $v0, 10
              syscall
