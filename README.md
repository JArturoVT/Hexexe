Hexexe
------
Display contents of a file in hexadecimal format. It's very useful to work with binary files converting to text ones.

Compile with GCC
----------------
So simple, you don't need any extra library.

    gcc hexexe.c -o hexexe
    
Using Hexexe
------------
Hexexe is a pretty simple program. You only have to specify the input file and output file if you want to. You possess two options to modify the output. First one is shellcode format where the output is printed like "C Style" Ex: \0x4d\0xb1. The another one is print the output in uppercase (needless to say more). You can combine both options for custom output.
