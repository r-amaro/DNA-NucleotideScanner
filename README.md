# DNA-NucleotideScanner
This C program scans through DNA nucleotides and stores, then prints the 'words' of size 10 along with their locations.

Steps to run the .txt file through the C program:
1. cc p1.c
2. ./a.out "file-name.txt"

*Don't type quotation marks for step 2*

Memory is allocated for 30 locations per each specific genetic code 'word'. 
^Future plans are to make the memory allocated dynamically increase. 

---------------------------------------------------------------------

Hashing was used as an index to store words in the final[] array.

AAAAAAAAAA = 0

TTTTTTTTTT = 1,048,575

---------------------------------------------------------------------

UnHash() translates the hashing value back to the options 0->3 = A->T
and results to the original 'word'.
