	.file	1 "main.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"Hola\000"
	.align	2
$LC1:
	.ascii	"Chau\000"
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,72,$ra		# vars= 32, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,72
	.cprestore 16
	sw	$ra,64($sp)
	sw	$fp,60($sp)
	sw	$gp,56($sp)
	move	$fp,$sp
	lw	$v0,$LC0
	sw	$v0,24($fp)
	lbu	$v0,$LC0+4
	sb	$v0,28($fp)
	lw	$v0,$LC1
	sw	$v0,32($fp)
	lbu	$v0,$LC1+4
	sb	$v0,36($fp)
	lw	$v0,$LC0
	sw	$v0,40($fp)
	lbu	$v0,$LC0+4
	sb	$v0,44($fp)
	addu	$v0,$fp,32
	addu	$a0,$fp,24
	move	$a1,$v0
	la	$t9,strcmp
	jal	$ra,$t9
	bne	$v0,$zero,$L18
	li	$v0,1			# 0x1
	sw	$v0,48($fp)
	b	$L17
$L18:
	addu	$v0,$fp,40
	addu	$a0,$fp,24
	move	$a1,$v0
	la	$t9,strcmp
	jal	$ra,$t9
	sw	$v0,48($fp)
$L17:
	lw	$v0,48($fp)
	move	$sp,$fp
	lw	$ra,64($sp)
	lw	$fp,60($sp)
	addu	$sp,$sp,72
	j	$ra
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
