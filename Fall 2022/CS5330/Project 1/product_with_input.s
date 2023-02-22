	.data	

input1: 	.asciiz 	"Please enter a positive integer for the first input:"
input2: 	.asciiz		"Please enter a positive Integer for the second input:"
result: 	.asciiz		"Result: "

	.text
	.globl main
	
input:
	li		$v0, 4
	la 		$a0, input1
	syscall
	
	li		$v0, 5
	syscall
	move		$t0, $v0
	
	li		$v0, 4
	la 		$a0, input2
	syscall	
	
	li		$v0, 5
	syscall
	move		$t1, $v0
	
	slt		$t2, $t0, $zero
	bne		$t2, $zero, outputzero
	slt		$t2, $t1, $zero
	bne		$t2, $zero, outputzero

main:
	add		$s1, $t0, $zero
	add		$t1, $t1, $zero

	addi		$s3, $zero, 0
	beqz		$t1, fin
	
fori:
	add		$s3, $s3, $s1
	addi		$t1, $t1, -1
	bnez		$t1, fori
	
	li 		$v0, 4
	la 		$a0, result
	syscall
	
	li 		$v0, 1
	move 		$a0, $s3
	syscall
	
	j	 	fin

outputzero:
	li 		$v0, 4
	la 		$a0, result
	syscall
	
	li 		$v0, 1
	move 		$a0, $zero
	syscall

fin:
	li		$v0, 10
	syscall
