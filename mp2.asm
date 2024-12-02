section .text
bits 64
default rel
global daxpy

daxpy:
    ; Arguments:
    ; X - rcx, Y - rdx, Z - r8, n - r9, A - xmm0 (scalar double-precision)

    test rcx, rcx           
    jz done                 

    xor r10, r10                ; r8 will serve as the loop counter (i = 0)

loop:
    movsd xmm1, [rcx + r10*8]   ; xmm1 = X[i]
    mulsd xmm1, xmm0            ; xmm1 = A * X[i]

    movsd xmm2, [rdx + r10*8]   ; xmm2 = Y[i]  
    addsd xmm1, xmm2            ; xmm1 = A * X[i] + Y[i]

    movsd [r8 + r10*8], xmm1    ; Store result into Z[i]

    inc r10                  
    cmp r10, r9              
    jl loop                 

done:
    ret   
