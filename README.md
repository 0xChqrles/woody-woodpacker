# woody-woodpacker

The goal of this program is to encrypt a program give as parameter. Only 64 bits ELF files will be managed here. A new program called “woody” will be generated from this execution. When this new program (woody) will be executed, it will be decrypted and run. Its execution is at any point identical to the program given as parameter in the last step, except that the new program will print `....WOODY....\n` on stdout.

```
$ ./sample
Hello World!
```
```
$ ./woody
....WOODY....
Hello World!
```
