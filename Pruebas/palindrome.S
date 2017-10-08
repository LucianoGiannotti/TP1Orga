#include <sys/syscall.h>
#include <mips/regdef.h>
	.text
	.align	2
	.globl	palindrome
	.ent	palindrome

palindrome: #por ahora lee el archivo en un buffer y lo imprime en otro
	.frame	$fp,48, ra		
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	 t9
	.set	reorder
	subu	sp,sp,48
	.cprestore 16
	sw	 ra,40(sp)
	sw	 $fp,36(sp)
	sw	 gp,32(sp)
	move	 $fp,sp
	sw	 a0,48($fp)
	sw	 a1,52($fp)
	sw	 a2,56($fp)
	lw	 a0,56($fp)
	la	 t9,mymalloc
	jal	 ra, t9
	sw	 v0,24($fp)
	lw	 a0,48($fp)
	lw	 a1,24($fp)
	lw	 a2,56($fp)
	la	 v0,SYS_read
	syscall
	lw	 a0,52($fp)
	lw	 a1,24($fp)
	lw	 a2,56($fp)
	la	 v0,SYS_write
	syscall
	move	 sp, $fp
	lw	 ra,40(sp)
	lw	 $fp,36(sp)
	addu	 sp, sp,48
	j	 ra
	.end	palindrome
	.size	palindrome, .-palindrome
	.rdata
	.align	2
