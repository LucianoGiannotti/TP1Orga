#include <sys/syscall.h>
#include <mips/regdef.h>
	.text
	.align	2
	.globl	putch
	.ent	putch
putch:
	.frame	$fp,16,ra		# vars= 0, regs= 2/0, args= 0, extra= 8
	.mask	0x50000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	t9
	.set	reorder
	subu	sp,sp,16
	.cprestore 0
	sw	$fp,12(sp)
	sw	gp,8(sp)
	move	$fp,sp
	sw	a0,16($fp)
	sw	a1,20($fp)
	sw	a2,24($fp)
	lw	a0,20($fp)
	lw	v1,16($fp)
	lw	v0,24($fp)
	addu	v0,v1,v0
	sw	v0,0(a0)
	move	sp,$fp
	lw	$fp,12(sp)
	addu	sp,sp,16
	j	ra
	.end	putch
	.size	putch, .-putch
	.align	2
