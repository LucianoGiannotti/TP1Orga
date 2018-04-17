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

        
