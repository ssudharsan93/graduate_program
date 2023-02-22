	.data	
arg:	.word	5


	.text
	.globl main
main:
	la	$t1, arg	
	lw	$s1, 0($t1) 
	lw	$t1, 0($t1)

	addi	$s3, $zero, 0
	beqz	$t1, fin		
fori:
	add	$s3, $s3, $s1	
	addi	$t1, $t1, -1
	bnez	$t1, fori		
fin:
	li	$v0, 10
	syscall		
