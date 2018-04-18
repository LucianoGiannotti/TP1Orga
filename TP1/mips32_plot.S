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
          sw a0, 80($fp)                                # Fin de creacion de SF
          lw t0, 44(a0)                                 # Obtengo dir de fp en t0
          addiu t0, t0, 14                              # Obtengo dir de fd en t0
          lh t0, 0(t0)                                  # Obtengo fd
          sw t0, 16($fp)                                # Salvo fd
          la a0, head_pgm
          jal my_strlen
          move a2, v0                                   # Cargo len(head_pgm)
          lw a0, 16($fp)                                # Cargo fd
          la a1, head_pgm                               # Cargo head_pgm
          jal my_fprintf                                # Escribo "P2"

return:
          lw ra, 72(sp)
          lw $fp, 68(sp)
          lw gp, 64(sp)
          addu sp, sp, 80
          jr ra
          .end mips32_plot
          .size mips32_plot, .-mips32_plot

          .ent my_strlen
my_strlen:
          .frame $fp, 16, ra
          .set noreorder
          .cpload t9
          .set reorder
          subu sp, sp, 16
          .cprestore 0
          sw $fp, 4(sp)
          move $fp, sp
          sw a0, 16($fp)                                # Fin de creacion de SF
          move t0, zero                                 # i = 0
          b test_end
increment:
          addiu t0, t0, 1                               # i++
test_end:
          addu t1, t0, a0
          lb t1, 0(t1)
          bnez t1, increment                            # if(s[i] != 0) -> increment
          move v0, t0
          lw $fp, 4(sp)
          lw gp, 0(sp)
          addu sp, sp, 16
          jr ra
          .end my_strlen
          .size my_strlen, .-my_strlen

          .ent my_fprintf
my_fprintf:
          .frame $fp, 40, ra
          .set noreorder
          .cpload t9
          .set reorder
          subu sp, sp, 40
          .cprestore 24
          sw $fp, 28(sp)
          sw ra, 32(sp)
          move $fp, sp
          sw a0, 40($fp)
          sw a1, 44($fp)
          sw a2, 48($fp)                                # Fin de creacion de SF
          move t0, zero                                 # n = 0
          move t1, zero                                 # total = 0
          sw t0, 16($fp)                                # n -> SF
          sw t1, 20($fp)                                # total -> SF
          b test_write
add_total:
          lw t1, 20($fp)
          lw t0, 16($fp)
          addu t1, t1, t0
          sw t0, 16($fp)
          sw t1, 20($fp)
test_write:
          lw a0, 40($fp)                                # Cargo fd
          lw t3, 44($fp)
          lw t2, 48($fp)
          lw t1, 20($fp)
          lw t0, 16($fp)
          addu a1, t3, t1                               # Cargo dir + total
          subu a2, t2, t1                               # Cargo len - total
          li v0, SYS_write
          syscall
          move t0, v0
          sw t0, 16($fp)
          bgtz t0, add_total
          lw ra, 32(sp)
          lw $fp, 28(sp)
          lw gp, 24(sp)
          addu sp, sp, 40
          jr ra
          .end my_fprintf
          .size my_fprintf, .-my_fprintf

          .rdata
          .align 2
msgs:     .word head_pgm, msg_1, msg_2
          .align 0
head_pgm: .asciiz "P2\n"
msg_1:    .asciiz "i/o error.\n"
msg_2:    .asciiz "cannot flush output file.\n"
