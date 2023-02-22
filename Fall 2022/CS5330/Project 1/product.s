	.data	
arg:	.word	2
arg2:	.word	5

	.text
	.globl main
main:
	la 	$t0, arg
	la	$t1, arg2
	lw	$s1, 0($t0) 
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
