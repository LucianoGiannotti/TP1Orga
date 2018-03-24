	.file	1 "main.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"prueba.txt\000"
	.align	2
$LC1:
	.ascii	"r+\000"
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,48,$ra		# vars= 8, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,48
	.cprestore 16
	sw	$ra,40($sp)
	sw	$fp,36($sp)
	sw	$gp,32($sp)
	move	$fp,$sp
	la	$a0,$LC0
	la	$a1,$LC1
	la	$t9,fopen
	jal	$ra,$t9
	sw	$v0,24($fp)		#v0 = puntero al file lo almaceno en 24($fp)

	li	$a0,8			# 0x8 8 bytes pal malloc
	la	$t9,mymalloc
	jal	$ra,$t9
	sw	$v0,28($fp)		#v0 = puntero al retorno de mymalloc lo almaceno en 28($fp)

	lw	$a0,28($fp)		#mymalloc (p char)
	li	$a1,4			# 0x4
	lw	$a2,24($fp)		# file
	la	$t9,fgets
	jal	$ra,$t9

	lw	$a0,24($fp)
	la	$t9,fclose
	jal	$ra,$t9

	lw	$a0,28($fp)
	la	$t9,myfree
	jal	$ra,$t9
	
	move	$v0,$zero
	move	$sp,$fp
	lw	$ra,40($sp)
	lw	$fp,36($sp)
	addu	$sp,$sp,48
	j	$ra
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"

