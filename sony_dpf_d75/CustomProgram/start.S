
    .section .start, "ax"
    .globl _start
_start:
    lui  $t0, %hi(_sbss)
    ori  $t0, $t0, %lo(_sbss)

    lui  $t1, %hi(_ebss)
    ori  $t1, $t1, %lo(_ebss)
_loop:
    beq $t0, $t1, _m
    nop
    sw $zero, 0($t0)
    addiu $t0, $t0, 4
    b _loop
    nop
_m:
    j main
    nop

