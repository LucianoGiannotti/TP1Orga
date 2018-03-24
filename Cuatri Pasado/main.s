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
	.frame	$fp,56,$ra		# vars= 16, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$t9
	.set	reorder
	subu	$sp,$sp,56
	.cprestore 16
	sw	$ra,48($sp)
	sw	$fp,44($sp)
	sw	$gp,40($sp)
	move	$fp,$sp
	sw	$zero,24($fp)
	la	$a0,$LC0
	la	$a1,$LC1
	la	$t9,fopen
	jal	$ra,$t9
	sw	$v0,28($fp)
$L18:
	addu	$v0,$fp,32
	move	$a0,$v0
	li	$a1,4			# 0x4
	lw	$a2,28($fp)
	la	$t9,fgets
	jal	$ra,$t9
	beq	$v0,$zero,$L20
	b	$L19
$L20:
	lw	$v0,24($fp)
	addu	$v0,$v0,1
	sw	$v0,24($fp)
	b	$L18
$L19:
	lw	$a0,28($fp)
	la	$t9,fclose
	jal	$ra,$t9
	move	$v0,$zero
	move	$sp,$fp
	lw	$ra,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$ra
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"


int a = 0;
  FILE* file;
  file = fopen("prueba.txt","r+");
  char buffer[BUFF_SIZE];
  while (!(fgets(buffer, 4,file))){
     a++;
  }
  fclose(file);
  return 0;
