# MOS 6502 Emulator

**Warning** : The project is still under development. 

Welcome to MOS 6502 Emulator Dev. My goal is to get a software implementation 6502 running smoothly, and then deploy a tiny Operating System on the emulator to manage programs. I will be maintaining a small [blog](https://atman-kar.github.io/soft6502/) where I write about some of the hurdles I face. The emulator will be completely implemented in C. 

## Files

Here are the list of files & directories in the project.

```
soft6501
│   README.md
│   Makefile    
│   NESDoc.pdf
|
└───src
│   │   cpu.c
│   │   cpu.h
│   │   main.c
│   │   opcodes.c
│   │   opcodes.h
│   │
│   └───test
│       │   unittest.c
│       │   unittest.h

```

[NESDoc.pdf](https://www.nesdev.com/NESDoc.pdf) is the source of inspiration for this project. 
