#include <sys/syscall.h>
#include <mips/regdef.h>	
	.file	1 "archivos.c"
	.text
	.align	2
	.globl	palindrome
	.ent	palindrome
palindrome:
	.frame	$fp,56,ra		# vars= 16, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	t9
	.set	reorder
	subu	sp,sp,56
	.cprestore 16
	sw	ra,48(sp)
	sw	$fp,44(sp)
	sw	gp,40(sp)
	move	$fp,sp
	sw	a0,56($fp)
	sw	a1,60($fp)
	sw	a2,64($fp)
	sw	a3,68($fp)
	sw	zero,24($fp)
	lw	a0,60($fp)
	la	t9,mymalloc
	jal	ra,t9
	sw	v0,28($fp)
	lw	a0,68($fp)
	la	t9,mymalloc
	jal	ra,t9
	sw	v0,32($fp)
	li	v0,1			# 0x1
	sb	v0,36($fp)
L18:
	lw	a0,56($fp)
	lw	a1,28($fp)
	lw	a2,60($fp)
	li	v0,SYS_read
	syscall
	bgtz	v0,L21
	b	L19
L21:
	lw	v0,24($fp)
	lw	v1,60($fp)
	sltu	v0,v0,v1
	bne	v0,zero,L23
	b	L22
L23:
	lw	a0,28($fp)
	lw	a1,24($fp)
	la	t9,getch
	jal	ra,t9
	sb	v0,36($fp)
	addu	v0,$fp,36
	lw	a0,64($fp)
	move	a1,v0
	li	a2,1			# 0x1
	li	v0,SYS_write
	syscall
	lw	v0,24($fp)
	addu	v0,v0,1
	sw	v0,24($fp)
	b	L21

L22:
	sw	zero,24($fp)
	b	L18
L19:
	lw	a0,28($fp)
	la	t9,myfree
	jal	ra,t9
	lw	a0,32($fp)
	la	t9,myfree
	jal	ra,t9
	move	sp,$fp
	lw	ra,48(sp)
	lw	$fp,44(sp)
	addu	sp,sp,56
	j	ra
	.end	palindrome
	.size	palindrome, .-palindrome
	.rdata
	.align	2

