#include <sys/syscall.h>
#include <mips/regdef.h>
	.text
	.align	2
	.globl	getch
	.ent	getch
getch:	#devuelve un byte(char)
	.frame	$fp,24,ra
	.mask	0x50000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	t9
	.set	reorder
	subu	sp,sp,24
	.cprestore 0
	sw	$fp,20(sp)
	sw	gp,16(sp)
	move	$fp,sp
	sw	a0,24($fp) #a0 es el puntero al buffer origen
	sw	a1,28($fp) #a1 es el indice del buffer origen
	lw	v1,24($fp)
	lw	v0,28($fp)
	addu	v0,v1,v0
	lbu	v0,0(v0)
	sb	v0,8($fp)
	lb	v0,8($fp)
	move	sp,$fp
	lw	$fp,20(sp)
	addu	sp,sp,24
	j	ra
	.end	getch
	.size	getch, .-getch
