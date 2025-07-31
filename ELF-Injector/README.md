# ELF-Injector

ELF-Injector est un projet scolaire en sécurité informatique visant à manipuler et infecter des binaires ELF sur des systèmes Linux. Ce programme modifie la structure interne d'un fichier ELF, notamment en transformant le segment `PT_NOTE` en `PT_LOAD` et en ajustant les permissions pour permettre l'exécution de code arbitraire. Une fois les modifications effectuées, un shellcode est injecté à la fin du fichier pour permettre l'exécution de commandes dans un shell `/bin/sh`.

## Installation

```bash
sudo apt-get install nasm ld
```
 


## Utilisation


1. Assembler le fichier 

```bash
nasm -f elf64 -o injector.o injector.asm
```

2. Lier le fichier objet

```bash
ld -o injector injector.o
```

3. Préparer le fichier à infecter

```bash
cp /usr/bin/ls ls
```

4. Exécuter le programme d'infection

```bash
./injector
```



## Outils tiers utilisé 

J'ai utilisé plusieurs outils de debuggage et d'analyse.


- GDB : 

```bash
sudo apt-get install gdb
```


- Readealf :

Analyseur de fichiers ELF. Installé nativement sur Ubuntu.


- Objdump : 

Outil qui fournit des informations sur les fichiers ELF.


- md5sum :

Affiche le hash du fichier. Permet de voir si notre infector à modifier l'ELF.
