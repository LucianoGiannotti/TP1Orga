#include <sys/syscall.h>
#include <mips/regdef.h>

          .text
          .abicalls
          .align 2
          .globl mips32_plot
          .ent mips32_plot
mips32_plot:
          .frame $fp, 80, ra
          .set noreorder
          .cpload t9
          .set reorder
          subu sp, sp, 80
          .cprestore 64
          sw $fp, 68(sp)
          sw ra, 72(sp)
          move $fp, sp
          sw a0, 80($fp)

          # TODA LA FUNCION

return:
          lw ra, 72(sp)
          lw $fp, 68(sp)
          lw gp, 64(sp)
          addu sp, sp, 80
          jr ra
          .end mips32_plot
          .size mips32_plot, .-mips32_plot

          .rdata
          .align 2
msgs:     .word head_pgm, msg_1, msg_2
          .align 0
head_pgm: .asciiz "P2\n"
msg_1:    .asciiz "i/o error.\n"
msg_2:    .asciiz "cannot flush output file.\n"
