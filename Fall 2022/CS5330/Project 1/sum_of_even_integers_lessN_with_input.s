	.data
N:		.word		0
Result: 	.word 		0
Result_String:	.asciiz		"Result: " 
error:		.asciiz		"N < 0, invalid for this program!\n"
input: 		.asciiz		"Enter a positive integer for input, N, to find sum of all even numbers less than N: "

	.text
	.globl main

main:
	li		$v0, 4
	la		$a0, input
	syscall
	
	la		$t0, N
	li		$v0, 5
	syscall
	sw		$v0, 0($t0)

	la		$t1, Result
	lw		$s0, 0($t0)
	li 		$t2, 2
	slt 		$t3, $s0, $zero
	bne 		$t3, $zero, store_negative_one
	slt 		$t3, $s0, $t2
	bne 		$t3, $zero, store_zero
			
summation:
	add 		$s1, $s1, $t2
	addi  		$t2, $t2, 2
	slt 		$t3, $t2, $s0
	bne 		$t3, $zero, summation
	sw 		$s1, 0($t1)
	j		fin

store_zero:
	sw 		$zero, 0($t1)
	j 		fin

store_negative_one:
	li		$v0, 4
	la		$a0, error
	syscall
	
	li 		$t4, -1
	sw 		$t4, 0($t1)
	j 		fin
	
fin:
	la		$t4, Result
	lw		$t4, 0($t4)
	
	li		$v0, 4
	la		$a0, Result_String
	syscall
	
	li		$v0, 1
	move		$a0, $t4
	syscall
	
	li		$v0, 10
	syscall	