#include <sys/syscall.h>
#include <mips/regdef.h>

	
	.abicalls
	.text
	.align	2
	.extern mymalloc
	.extern myfree
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
	.globl	putch
	.ent	putch

putch:
	.frame	$fp,24,ra		# vars= 8, regs= 2/0, args= 0, extra= 8
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
	move	v0,a0
	sw	a1,28($fp)
	sw	a2,32($fp)
	sb	v0,8($fp)
	lw	v1,28($fp)
	lw	v0,32($fp)
	addu	v1,v1,v0
	lbu	v0,8($fp)
	sb	v0,0(v1)
	move	sp,$fp
	lw	$fp,20(sp)
	addu	sp,sp,24
	j	ra
	.end	putch
	.size	putch, .-putch
	.align	2
	.globl	invertir
	.ent	invertir
invertir:
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
	lw	v0,60($fp)
	addu	v0,v0,1
	move	a0,v0
	la	t9,mymalloc
	jal	ra,t9
	sw	v0,28($fp)
	lw	a0,28($fp)
	move	a1,zero
	li	a2,4			# 0x4
	la	t9,memset
	jal	ra,t9
	lw	v0,28($fp)
	bne	v0,zero,L19
	sw	zero,32($fp)
	b	L18
L19:
	li	v0,1			# 0x1
	sw	v0,24($fp)
L20:
	lw	v0,60($fp)
	addu	v1,v0,1
	lw	v0,24($fp)
	sltu	v0,v0,v1
	bne	v0,zero,L23
	b	L21
L23:
	lw	v1,60($fp)
	lw	v0,24($fp)
	subu	v1,v1,v0
	lw	v0,56($fp)
	addu	v0,v1,v0
	lw	a0,28($fp)
	move	a1,v0
	li	a2,1			# 0x1
	la	t9,strncat
	jal	ra,t9
	lw	v0,24($fp)
	addu	v0,v0,1
	sw	v0,24($fp)
	b	L20
L21:
	lw	v0,28($fp)
	sw	v0,32($fp)
L18:
	lw	v0,32($fp)
	move	sp,$fp
	lw	ra,48(sp)
	lw	$fp,44(sp)
	addu	sp,sp,56
	j	ra
	.end	invertir
	.size	invertir, .-invertir
	.align	2
	.globl	esCapicua
	.ent	esCapicua
esCapicua:
	.frame	$fp,64,ra		# vars= 24, regs= 4/0, args= 16, extra= 8
	.mask	0xd0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	t9
	.set	reorder
	subu	sp,sp,64
	.cprestore 16
	sw	ra,60(sp)
	sw	$fp,56(sp)
	sw	gp,52(sp)
	sw	s0,48(sp)
	move	$fp,sp
	sw	a0,64($fp)
	sw	sp,36($fp)
	lw	v0,64($fp)
	lb	v0,0(v0)
	bne	v0,zero,L25
	sw	zero,32($fp)
	b	L24
L25:
	lw	a0,64($fp)
	la	t9,strlen
	jal	ra,t9
	move	v1,v0
	addu	v0,v1,1
	addu	v0,v0,7
	srl	v0,v0,3
	sll	v0,v0,3
	subu	sp,sp,v0
	addu	v0,sp,16
	sw	v0,40($fp)
	addu	v0,v1,1
	lw	a0,40($fp)
	move	a1,zero
	move	a2,v0
	la	t9,memset
	jal	ra,t9
	sw	zero,24($fp)
L26:
	lw	a0,64($fp)
	la	t9,strlen
	jal	ra,t9
	lw	v1,24($fp)
	sltu	v0,v1,v0
	bne	v0,zero,L29
	b	L27
L29:
	lw	v0,24($fp)
	lw	v1,40($fp)
	addu	s0,v1,v0
	lw	v1,64($fp)
	lw	v0,24($fp)
	addu	v0,v1,v0
	lb	v0,0(v0)
	move	a0,v0
	la	t9,tolower
	jal	ra,t9
	sb	v0,0(s0)
	lw	v0,24($fp)
	addu	v0,v0,1
	sw	v0,24($fp)
	b	L26
L27:
	lw	a0,64($fp)
	la	t9,strlen
	jal	ra,t9
	lw	a0,40($fp)
	move	a1,v0
	la	t9,invertir
	jal	ra,t9
	sw	v0,28($fp)
	lw	v0,28($fp)
	bne	v0,zero,L30
	lw	a0,28($fp)
	la	t9,myfree
	jal	ra,t9
	lw	sp,36($fp)
	li	v0,-1			# 0xffffffffffffffff
	sw	v0,32($fp)
	b	L24
L30:
	lw	a0,40($fp)
	lw	a1,28($fp)
	la	t9,strcmp
	jal	ra,t9
	bne	v0,zero,L31
	lw	a0,28($fp)
	la	t9,myfree
	jal	ra,t9
	lw	sp,36($fp)
	li	v1,1			# 0x1
	sw	v1,32($fp)
	b	L24
L31:
	lw	a0,28($fp)
	la	t9,myfree
	jal	ra,t9
	lw	sp,36($fp)
	sw	zero,32($fp)
L24:
	lw	v0,32($fp)
	move	sp,$fp
	lw	ra,60(sp)
	lw	$fp,56(sp)
	lw	s0,48(sp)
	addu	sp,sp,64
	j	ra
	.end	esCapicua
	.size	esCapicua, .-esCapicua
	.align	2
	.globl	initBufferInterno
	.ent	initBufferInterno
initBufferInterno:
	.frame	$fp,48,ra		# vars= 8, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	t9
	.set	reorder
	subu	sp,sp,48
	.cprestore 16
	sw	ra,40(sp)
	sw	$fp,36(sp)
	sw	gp,32(sp)
	move	$fp,sp
	sw	a0,48($fp)
	lw	a0,48($fp)
	la	t9,mymalloc
	jal	ra,t9
	sw	v0,24($fp)
	lw	a0,24($fp)
	move	a1,zero
	lw	a2,48($fp)
	la	t9,memset
	jal	ra,t9
	lw	v0,24($fp)
	move	sp,$fp
	lw	ra,40(sp)
	lw	$fp,36(sp)
	addu	sp,sp,48
	j	ra
	.end	initBufferInterno
	.size	initBufferInterno, .-initBufferInterno
	.rdata
	.align	2
LC0:
	.ascii	"\n"
	.ascii	"buffer interno: \000"
	.align	2
LC1:
	.ascii	"\n\000"
	.text
	.align	2
	.globl	palindrome
	.ent	palindrome
palindrome:
	.frame	$fp,72,ra		# vars= 32, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	t9
	.set	reorder
	subu	sp,sp,72
	.cprestore 16
	sw	ra,64(sp)
	sw	$fp,60(sp)
	sw	gp,56(sp)
	move	$fp,sp
	sw	a0,72($fp)
	sw	a1,76($fp)
	sw	a2,80($fp)
	sw	a3,84($fp)
	sw	zero,24($fp)
	sw	zero,28($fp)
	lw	a0,76($fp)
	la	t9,mymalloc
	jal	ra,t9
	sw	v0,32($fp)
	lw	a0,84($fp)
	la	t9,mymalloc
	jal	ra,t9
	sw	v0,36($fp)
	li	v0,1			# 0x1
	sb	v0,40($fp)
	li	a0,45			# 0x2d
	la	t9,initBufferInterno
	jal	ra,t9
	sw	v0,44($fp)
L34:
	lw	a0,72($fp)
	lw	a1,32($fp)
	lw	a2,76($fp)
	#la	t9,read
	#jal	ra,t9
	lw v0,SYS_read
	syscall
	bgtz	v0,L37
	b	L35
L37:
	lw	v0,24($fp)
	lw	v1,76($fp)
	sltu	v0,v0,v1
	bne	v0,zero,L39
	b	L38
L39:
	lw	a0,32($fp)
	lw	a1,24($fp)
	la	t9,getch
	jal	ra,t9
	sb	v0,40($fp)
	lw	a0,44($fp)
	la	t9,strlen
	jal	ra,t9
	move	v1,v0
	li	v0,4			# 0x4
	bne	v1,v0,L40
	lw	a0,44($fp)
	la	t9,strlen
	jal	ra,t9
	sll	v0,v0,2
	sw	v0,52($fp)
	lw	a0,52($fp)
	la	t9,mymalloc
	jal	ra,t9
	sw	v0,48($fp)
	lw	a0,48($fp)
	move	a1,zero
	lw	a2,52($fp)
	la	t9,memset
	jal	ra,t9
	lw	a0,44($fp)
	la	t9,strlen
	jal	ra,t9
	lw	a0,48($fp)
	lw	a1,44($fp)
	move	a2,v0
	la	t9,strncpy
	jal	ra,t9
	lw	a0,44($fp)
	la	t9,myfree
	jal	ra,t9
	lw	v0,48($fp)
	sw	v0,44($fp)
L40:
	lb	v0,40($fp)
	slt	v0,v0,65
	bne	v0,zero,L42
	lb	v0,40($fp)
	slt	v0,v0,91
	beq	v0,zero,L42
	b	L41
L42:
	lb	v0,40($fp)
	slt	v0,v0,97
	bne	v0,zero,L43
	lb	v0,40($fp)
	slt	v0,v0,123
	beq	v0,zero,L43
	b	L41
L43:
	la	a0,LC0
	la	t9,printf
	jal	ra,t9
	lw	a0,44($fp)
	la	t9,printf
	jal	ra,t9
	lw	a0,44($fp)
	la	t9,esCapicua
	jal	ra,t9
	move	v1,v0
	li	v0,1			# 0x1
	bne	v1,v0,L50
	sw	zero,28($fp)
L45:
	lw	a0,36($fp)
	la	t9,strlen
	jal	ra,t9
	lw	v1,84($fp)
	sltu	v0,v0,v1
	beq	v0,zero,L46
	lw	a0,44($fp)
	la	t9,strlen
	jal	ra,t9
	lw	v1,28($fp)
	sltu	v0,v1,v0
	bne	v0,zero,L47
	b	L46
L47:
	lw	v1,28($fp)
	lw	v0,84($fp)
	bne	v1,v0,L49
	lw	a0,36($fp)
	la	t9,strlen
	jal	ra,t9
	lw	a0,80($fp)
	lw	a1,36($fp)
	move	a2,v0
	##la	t9,write
	##jal	ra,t9
	lw	v0,SYS_write
	syscall
	lw	a0,80($fp)
	la	a1,LC1
	li	a2,1			# 0x1
	#la	t9,write
	#jal	ra,t9
	lw	v0,SYS_write
	syscall
	lw	a0,36($fp)
	move	a1,zero
	lw	a2,84($fp)
	la	t9,memset
	jal	ra,t9
L49:
	lw	a0,44($fp)
	lw	a1,28($fp)
	la	t9,getch
	jal	ra,t9
	sb	v0,40($fp)
	lw	a0,36($fp)
	la	t9,strlen
	jal	ra,t9
	move	v1,v0
	lb	v0,40($fp)
	move	a0,v0
	lw	a1,36($fp)
	move	a2,v1
	la	t9,putch
	jal	ra,t9
	lw	v0,28($fp)
	addu	v0,v0,1
	sw	v0,28($fp)
	b	L45
L46:
	lw	a0,36($fp)
	la	t9,strlen
	jal	ra,t9
	lw	a0,80($fp)
	lw	a1,36($fp)
	move	a2,v0
	#la	t9,write
	#jal	ra,t9
	lw	v0,SYS_write
	syscall
	lw	a0,80($fp)
	la	a1,LC1
	li	a2,1			# 0x1
	#la	t9,write
	#jal	ra,t9
	lw	v0,SYS_write
	syscall
	lw	a0,36($fp)
	move	a1,zero
	lw	a2,84($fp)
	la	t9,memset
	jal	ra,t9
L50:
	lw	a0,44($fp)
	la	t9,myfree
	jal	ra,t9
	li	a0,45			# 0x2d
	la	t9,initBufferInterno
	jal	ra,t9
	sw	v0,44($fp)
	b	L51
L41:
	lw	a0,44($fp)
	la	t9,strlen
	jal	ra,t9
	move	v1,v0
	lb	v0,40($fp)
	move	a0,v0
	lw	a1,44($fp)
	move	a2,v1
	la	t9,putch
	jal	ra,t9
L51:
	lw	v0,24($fp)
	addu	v0,v0,1
	sw	v0,24($fp)
	b	L37
L38:
	sw	zero,24($fp)
	b	L34
L35:
	sw	zero,28($fp)
	lw	a0,32($fp)
	la	t9,myfree
	jal	ra,t9
	lw	a0,36($fp)
	la	t9,myfree
	jal	ra,t9
	move	sp,$fp
	lw	ra,64(sp)
	lw	$fp,60(sp)
	addu	sp,sp,72
	j	ra
	.end	palindrome
	.size	palindrome, .-palindrome
	.align	2
	.globl	llenarBufferExterno
	.ent	llenarBufferExterno
llenarBufferExterno:
	.frame	$fp,24,ra		# vars= 8, regs= 2/0, args= 0, extra= 8
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
	move	v0,a0
	sw	a1,28($fp)
	sb	v0,8($fp)
	move	sp,$fp
	lw	$fp,20(sp)
	addu	sp,sp,24
	j	ra
	.end	llenarBufferExterno
	.size	llenarBufferExterno, .-llenarBufferExterno
