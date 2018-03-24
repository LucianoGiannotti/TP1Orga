	.file	1 "main.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,32,$ra		# vars= 16, regs= 2/0, args= 0, extra= 8
	.mask	0x50000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,32
	.cprestore 0
	sw	$fp,28($sp)
	sw	$gp,24($sp)
	move	$fp,$sp
	li	$v0,1	## a = 1		# 0x1
	sw	$v0,8($fp)
	li	$v0,2	##b == 2		# 0x2
	sw	$v0,12($fp)
	lw	$v1,8($fp)
	lw	$v0,12($fp)
	addu	$v0,$v1,$v0
	sw	$v0,16($fp) ##c
	lw	$v0,16($fp)
	move	$sp,$fp ## sp <- fp
	lw	$fp,28($sp)
	addu	$sp,$sp,32
	j	$ra
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"

int main(){
    int a = 1, b = 2;
    int c = a + b;
    return c;
}

