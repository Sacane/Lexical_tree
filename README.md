# Lexical_tree

By Johan "Sacane" Ramaroson Rakotomihamina and Christine Li 

Langage : C

Lexical management using ternary tree's algorithm.
This program is able to store words from a file and manipulate them as the program permits it. 

## How to compilate

You can use the makefile folder to compile sources and generate the executable "Lexique" by the command : make 
and then execute the program : ./Lexique

From there the program bring you to the menu in the terminal, just follow the instructions and enjoyt it ! 

## Command line

You can also use the program with options : 

./Lexique -l <namefile> : Allow you to display the words of the given file according to the lexical order.


• ./Lexique -s nom_du_fichier : Allow to save in a new file, the words of the lexicon in the lexical order of the given file. The new file's name will be the same as the given followed by the suffix ".LEX".

• ./Lexique -r <word> <namefile> : Check if the given word is in the given file. 
• ./Lexique -S <fileName> : Permet de sauvegarder l’arbre dans un fichier dont le nom sera celui du fichier d’entrée suivi du suffixe (.DIC) 
  Allow to save the tree builded by the given file, its name will be the same as the given file followed by the suffix ".DIC"
• ./Lexique -d <nameFile> <file.dot> : Allow you to generate a file.pdf which represents the tree builded by the given file.
  BEWARE : For this option you have to specify an empty file with the suffix ".dot" to make it works (the program will generate it if the file doesn't exists yet).
