.text

.global count_det
count_det:
    push {r4}
    ldr r1, [r0], #16
    ldr r2, [r0], #16
    ldr r3, [r0], #-4
    mul r2, r3, r2
    ldr r3, [r0], #-8
    ldr r4, [r0], #-16
    mul r3, r4, r3
    sub r2, r2, r3
    mul r1, r1, r2
    
    ldr r2, [r0], #16
    ldr r3, [r0], #4
    ldr r4, [r0], #8
    mul r3, r4, r3
    mul r3, r2, r3
    add r1, r3, r1
    ldr r4, [r0], #-20
    ldr r3, [r0], #-4
    mul r3, r4, r3
    mul r3, r2, r3
    sub r1, r1, r3
    
    ldr r2, [r0], #4
    ldr r3, [r0], #16
    ldr r4, [r0], #-4
    mul r3, r4, r3
    mul r3, r2, r3
    add r1, r3, r1    
    ldr r4, [r0], #-8
    ldr r3, [r0]
    mul r3, r4, r3
    mul r3, r2, r3
    sub r1, r1, r3
    mov r0, r1
    pop {r4}
    bx lr
