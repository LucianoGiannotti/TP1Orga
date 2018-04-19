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
          lh t0, 14(t0)                                 # Obtengo fd
          sw t0, 16($fp)                                # Salvo fd
          la a0, head_pgm
          jal my_strlen
          move a2, v0                                   # Cargo len(head_pgm)
          lw a0, 16($fp)                                # Cargo fd
          la a1, head_pgm                               # Cargo head_pgm
          jal my_fprintf                                # Imprimo "P2"
          lw t0, 80($fp)
          lw a0, 32(t0)                                 # Cargo x_res
          jal int_to_str                                # x_res -> str
          la a0, number
          jal my_strlen
          move a2, v0                                   # Cargo len(number)
          lw a0, 16($fp)                                # Cargo fd
          la a1, number                                 # Cargo number
          jal my_fprintf                                # Imprimo "x_res"
          lw a0, 16($fp)                                # Cargo fd
          la a1, new_line                               # Cargo "\n"
          li a2, 1                                      # Cargo len("\n")
          jal my_fprintf                                # Imprimo "\n"
          lw t0, 80($fp)
          lw a0, 36(t0)                                 # Cargo y_res
          jal int_to_str                                # y_res -> str
          la a0, number
          jal my_strlen
          move a2, v0                                   # Cargo len(number)
          lw a0, 16($fp)                                # Cargo fd
          la a1, number                                 # Cargo number
          jal my_fprintf                                # Imprimo "y_res"
          lw a0, 16($fp)                                # Cargo fd
          la a1, new_line                               # Cargo "\n"
          li a2, 1                                      # Cargo len("\n")
          jal my_fprintf                                # Imprimo "\n"
          lw t0, 80($fp)
          lw a0, 40(t0)                                 # Cargo shades
          subu a0, a0, 1                                # shades-1
          jal int_to_str                                # shades-1 -> str
          la a0, number
          jal my_strlen
          move a2, v0                                   # Cargo len(shades-1)
          lw a0, 16($fp)                                # Cargo fd
          la a1, number                                 # Cargo number
          jal my_fprintf                                # Imprimo "shades-1"
          lw a0, 16($fp)                                # Cargo fd
          la a1, new_line                               # Cargo "\n"
          li a2, 1                                      # Cargo len("\n")
          jal my_fprintf                                # Imprimo "\n"

return:
          lw ra, 72(sp)
          lw $fp, 68(sp)
          lw gp, 64(sp)
          addu sp, sp, 80
          jr ra
          .end mips32_plot
          .size mips32_plot, .-mips32_plot

          .ent int_to_str
int_to_str:
          .frame $fp, 40, ra
          .set noreorder
          .cpload t9
          .set reorder
          subu sp, sp, 40
          .cprestore 24
          sw $fp, 28(sp)
          sw ra, 32(sp)
          move $fp, sp
          sw a0, 40($fp)                                # Fin de creacion de SF
          la a1, number                                 # Cargo array
          la a2, index                                  # Cargo indice
          jal dig_to_char                               # Convierto digitos a char
          la a0, number                                 # Cargo array
          la a1, index                                  # Cargo indice
          jal put_end                                   # \0 al final
          lw ra, 32(sp)
          lw $fp, 28(sp)
          lw gp, 24(sp)
          addu sp, sp, 40
          jr ra
          .end int_to_str
          .size int_to_str, .-int_to_str

          .ent dig_to_char
dig_to_char:
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
          beqz a0, return_dig
          remu t0, a0, 10
          sw t0, 16($fp)
          divu a0, a0, 10
          jal dig_to_char
          lw t0, 16($fp)
          lb t1, 0(a2)
          addu t2, a1, t1
          addiu t0, t0, 48                              # ascii del numero
          sb t0, 0(t2)
          addiu t1, t1, 1
          sb t1, 0(a2)
return_dig:
          lw ra, 32(sp)
          lw $fp, 28(sp)
          lw gp, 24(sp)
          addu sp, sp, 40
          jr ra
          .end dig_to_char
          .size dig_to_char, .-dig_to_char

          .ent put_end
put_end:
          .frame $fp, 8, ra
          .set noreorder
          .cpload t9
          .set reorder
          subu sp, sp, 8
          .cprestore 0
          sw $fp, 4(sp)
          move $fp, sp
          sw a0, 8($fp)
          sw a1, 12($fp)                                 # Fin de creacion de SF
          lb t0, 0(a1)
          addu t0, a0, t0
          sb zero, 0(t0)
          sb zero, 0(a1)                                 # Reinicio indice
          lw $fp, 4(sp)
          lw gp, 0(sp)
          addu sp, sp, 8
          jr ra
          .end put_end
          .size put_end, .-put_end

          .ent my_strlen
my_strlen:
          .frame $fp, 8, ra
          .set noreorder
          .cpload t9
          .set reorder
          subu sp, sp, 8
          .cprestore 0
          sw $fp, 4(sp)
          move $fp, sp
          sw a0, 8($fp)                                 # Fin de creacion de SF
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
          addu sp, sp, 8
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
          lw v0, 20($fp)                                # Devuelvo el total
          lw ra, 32(sp)
          lw $fp, 28(sp)
          lw gp, 24(sp)
          addu sp, sp, 40
          jr ra
          .end my_fprintf
          .size my_fprintf, .-my_fprintf

          .rdata
          .align 2
msgs:     .word head_pgm, msg_1, msg_2, new_line
          .align 0
head_pgm: .asciiz "P2\n"
msg_1:    .asciiz "i/o error.\n"
msg_2:    .asciiz "cannot flush output file.\n"
new_line: .asciiz "\n"

          .data
number:   .space 11
index:    .byte 0
