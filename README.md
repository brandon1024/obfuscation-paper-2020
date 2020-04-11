# Analysis and Application of Various Machine-Level Obfuscation Techniques
This repository contains the LaTex source and code examples for a research-style paper I co-authored for an undergrad software security project. In this paper, we dive into a few common ways to obfuscate an algorithm and present various examples to demonstrate these techniques.

This paper won't be published, but I encourage anyone to suggest edits or point out errors/omissions!

## Abstract
The concept of software obfuscation is important and widely used in the software industry. Developers and cyber criminals often employ obfuscation techniques to challenge attempts to reverse engineer software, but these techniques are also applied to protect intellectual property, to reduce network traffic congestion, or sometimes to maintain security through obscurity. This paper presents the three classifications of software obfuscation and explores various different techniques that are often used to conceal or obscure an algorithm. We analyse the benefits, limitations, and application of different obfuscation techniques.

## Compiling and Running Examples
### Constant Unfolding Example
```
$ gcc -o constant-unfolding constant-unfolding.c
$ ./constant-unfolding
232
```

### Data Encoding Schemes Example
```
$ gcc -o data-encoding data-encoding.c
$ ./data-encoding
some secret
```

### Arithmetic Substitution Examples
```
$ gcc -o arithmetic-substitution-fermat-1 arithmetic-substitution-fermat-1.c
$ ./arithmetic-substitution-fermat-1 a b c
1024
$ gcc -o arithmetic-substitution-fermat-2 -lgmp arithmetic-substitution-fermat-2.c
$ ./arithmetic-substitution-fermat-2
1024
```

### Virtual Machine Example
```
$ cd vm-implementation/
$ mkdir build && cd build
$ cmake ..
$ make all
$ echo test | ./B64-Encoder-VM-Obfuscated
dGVzdAo=
```
