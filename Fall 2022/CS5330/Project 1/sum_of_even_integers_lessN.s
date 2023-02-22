	.data
N:		.word		9
Result: 	.word 		0
#Result_String:	.asciiz		"Result: "   #### Used to test the stored value of Result

	.text
	.globl main

main:	
	la		$t0, N
	la		$t1, Result
	lw		$s0, 0($t0)
	li 		$t2, 2
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
	
fin:
##### Block used to test the value stored in Result
#	la		$t3, Result
#	lw		$t3, 0($t3)
	
#	li		$v0, 4
#	la		$a0, Result_String
#	syscall
	
#	li		$v0, 1
#	move		$a0, $t3
#	syscall
##### Block used to test the value stored in Result
	
	li		$v0, 10
	syscall	
