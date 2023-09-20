# Solutions Ficha 00 (HSO)

1. What directory are you in after executing each of the following commands? Check your
guesses by running the command pwd.
$ cd ~
$ cd
R: We are at the user folder 
====================================================================================

2. Use the mkdir command to create the following subtree in your current directory:
dir1
|-- dir2
| |-- dir4
| | |-- dir6
| |-- dir5
|-- dir3
R: It plots the dir structure (Mac alternative: find dir1 or brew install tree)
====================================================================================



3. Starting at the current directory, in what directory would you end up after running the
following commands?
$ tree dir1
dir1
|-- dir2
| |-- dir4
| | |-- dir6
| |-- dir5
|-- dir3
$ cd dir1/dir2/dir4/dir6/../..
R: We ended up in dir2
====================================================================================

4. Use the touch command to create empty files with the names as below within the
subtree you created.
dir1
|-- dir2
| |-- dir4
| | |-- g22.doc
| |-- f1.txt
| |-- h22.txt
|-- g368.pdf
|-- dir3
|-- f3a.txt
|-- g56.doc
|-- g3x.pdf
R: we see all the folder and file hierarchy
====================================================================================

5. What is printed by the last two commands in this sequence?
$ tree dir1
dir1
|-- dir2
| |-- dir4
| | |-- g22.doc
| |-- f1.txt
| |-- h22.txt
|-- g368.pdf
|-- dir3
|-- f3a.txt
|-- g56.doc
|-- g3x.pdf
$ find dir1/dir2 -name "[fg][35][4-7a-z].txt" -print (none found)
$ find dir1/dir3 -name "[fg][35][4-7a-z].txt" -print (print files name found)
R: It prints the files found under the regex expression, firt letter f or g, second 3 or 5, range 4-7, a-z

More details:
The command uses the find utility to search for files within a specified directory hierarchy based on certain criteria. Let's break down the command:

find: This is the command itself, used to search for files and directories.

dir1/dir3: This is the starting directory or path from which the search will begin. In this case, it starts in the "dir3" directory, which is a subdirectory of "dir1."

-name "[fg][35][4-7a-z].txt": This part of the command specifies the search criteria based on the file name. It's enclosed in double quotation marks to ensure that the shell does not interpret the special characters within it.

[fg]: This part of the pattern specifies that the first character of the file name should be either 'f' or 'g'.

[35]: The second character should be either '3' or '5'.

[4-7a-z]: The third character can be any digit between '4' and '7' or any lowercase letter between 'a' and 'z'.

.txt: Finally, the file extension should be '.txt'.

-print: This part of the command specifies that the matching file names should be printed to the standard output (usually the terminal).

In summary, this find command searches for files within the "dir1/dir3" directory and its subdirectories that meet the specified naming pattern. The pattern looks for files with names that start with either 'f' or 'g', followed by either '3' or '5', followed by any digit between '4' and '7' or any lowercase letter between 'a' and 'z', and ending with '.txt'. When it finds such files, it prints their paths to the terminal.
====================================================================================

6. What is the structure of the subtree with root at dir1 after running the last command
in this sequence?
$ tree dir1
dir1
|-- dir2
| |-- dir4
| | |-- g22.doc
| |-- f1.txt
| |-- h22.txt
|-- g368.pdf
|-- dir3
|-- f3a.txt
|-- g56.doc
|-- g3x.pdf
$ rm -rf dir1/dir2
R: Removed folder dir2 and all inside files (-f (force without confirmation) -r (attempt remove the dir hierarchy)  ) 
(base) HSO:ficha_00 hso$ find dir1
dir1
dir1/dir3
dir1/dir3/g56.txt
dir1/dir3/f3a.txt
dir1/dir3/g3x.txt
====================================================================================

7. Assume that at directory dir3 you have the following scenario. Write the permissions
of the 3 files in octal, indicate the owners of the files, their creation dates and size in bytes.
$ ls
f3a.txt g3x.pdf j52.docx
$ ls -l
total 28712
-rw-r--r-- 1 lblopes staff 1412 Dec 29 15:43 f3a.txt
-rw-r--r--@ 1 lblopes staff 13923695 Dec 29 15:44 g3x.pdf
-rw-r--r--@ 1 lblopes staff 13793 Dec 29 15:47 j52.docx
R: ls -n (show permission numerically, turns on -l auto)
(base) HSO:dir3 hso$ ls -n
total 0
-rw-r--r--  1 501  80  0 Sep 13 10:52 f3a.txt
-rw-r--r--  1 501  80  0 Sep 13 10:53 g3x.txt
-rw-r--r--  1 501  80  0 Sep 13 10:53 g56.txt
====================================================================================

8. What permissions have “user/owner”, “group” and “others” over the file doit after you execute
each of the following commands?
$ chmod 755 doit
$ chmod u-wx doit
$ chmod go-rx doit
$ chmod 644 doit
R: Check. https://linuxize.com/post/understanding-linux-file-permissions/
ll doit
-rw-r--r--  1 hso  admin  0 Sep 13 11:46 doit
chmod 755 doit (user: all, group:  execute, read, others: execute)
-rwxr-xr-x  1 hso  admin  0 Sep 13 11:46 doit
chmod u-wx doit (user: remove write and execute)
-r--r-xr-x  1 hso  admin  0 Sep 13 11:46 doit
chmod go-rx doit (group: remove read execute, and other also)
-r--------  1 hso  admin  0 Sep 13 11:46 doit
chmod 644 doit
-rw-r--r--  1 hso  admin  0 Sep 13 11:46 doit
====================================================================================

9. What is printed by the last two commands in this sequence?
$ cat > trees.txt
pine:253:221:1.2
oak:144:123:0.9
birch:92:83:1.6
yew:65:63:4.3
alder:12:5:9.6
^D
$ cat trees.txt | cut -d ’:’ -f 1,4
$ cat trees.txt | cut -d ’:’ -f 1,4 | sort
R: (cut -d (delimiter) :, -f (limit speficic fields 1, 4) ) 
(base) HSO:ficha_00 hso$ cat trees.txt | cut -d ':' -f 1,4 
pine:1.2
oak:0.9
birch:1.6
yew:4.3
alder:9.6

(base) HSO:ficha_00 hso$ cat trees.txt | cut -d ':' -f 1,4 | sort
alder:9.6
birch:1.6
oak:0.9
pine:1.2
yew:4.3
R: print file content, cut by delimiter : , select column 1 and 4, and sort

More details:
The command processes the contents of a file named "trees.txt." Let's break down the command step by step:

cat trees.txt: This part of the command uses the cat command to display the contents of the "trees.txt" file in the terminal. cat is used to concatenate and display file contents.

|: This vertical bar character (|) is a pipe operator. It is used to redirect the output of the cat command (i.e., the contents of "trees.txt") to the input of the next command in the pipeline.

cut -d ':' -f 1,4: This part of the command uses the cut command to extract specific fields from each line of the input. Here's what each part of this cut command does:

-d ':': This option specifies that the delimiter separating fields in each line is a colon (:). It tells cut to split each line into fields based on the colon character.
-f 1,4: This option specifies which fields to select and display. In this case, it selects the first field (field 1) and the fourth field (field 4) from each line.
sort: After the cut command extracts the specified fields, the resulting lines are passed to the sort command. The sort command is used to sort lines of text alphabetically by default. In this case, it sorts the lines based on the values in the selected fields from the previous step.

So, in summary, the command reads the contents of the "trees.txt" file, extracts the first and fourth fields from each line (assuming fields are separated by colons), and then sorts the lines based on the values in these fields. The final sorted output is displayed in the terminal.
====================================================================================


10. Consider the following file with a quote written in a single line (no newlines). What
is the output of the final three commands in this sequence? Explain why.
$ cat > q1.txt
Three Rings for the Elven-kings under the sky, -->
Seven for the dwarf-lords in their halls of stone, -->
Nine for Mortal Men doomed to die, -->
One for the Dark Lord on his dark throne, -->
In the Land of Mordor where the Shadows lie. -->
One Ring to rule them all, One Ring to find them, -->
One Ring to bring them all and in the darkness bind them -->
In the Land of Mordor where the Shadows lie.
^D
$ cat q1.txt | sed ’s/Ring/Sword/g’ > q2.txt
$ cat q2.txt | grep -v Mordor (select lines dont match Mordor. off course none, no new lines)
$ wc -l q2.txt          // count lines (word count (wc) - l (lines))
R:  Replaced Ring by Sword,

More details:
The command performs a text substitution operation using the sed (stream editor) utility and then redirects the modified text to a new file. Let's break down the command step by step:

cat q1.txt: This part of the command uses the cat command to display the contents of the "q1.txt" file in the terminal. The cat command is typically used to concatenate and display the contents of files.

|: This vertical bar character (|) is a pipe operator. It is used to redirect the output of the cat command (i.e., the contents of "q1.txt") to the input of the next command (sed) in the pipeline.

sed 's/Ring/Sword/g': This part of the command is a sed expression enclosed in single quotes. It specifies a text substitution operation to be applied to the input text:

s: This is a command within sed that stands for "substitute." It is used to perform text substitutions.
/: This character is used as a delimiter to separate the parts of the sed expression. In this case, it separates the pattern to be replaced ("Ring") and the replacement pattern ("Sword").
Ring: This is the pattern to be replaced in the text.
Sword: This is the replacement pattern.
/: Another delimiter to separate the replacement pattern and the following g character.
g: This stands for "global," and it's a flag that tells sed to perform the substitution globally throughout the text (i.e., on all occurrences of "Ring" in each line).
> q2.txt: The > symbol is used to indicate output redirection. It tells the shell to take the modified text resulting from the sed operation and save it to a new file named "q2.txt." If "q2.txt" does not exist, it will be created. If it already exists, its contents will be overwritten with the modified text.

In summary, this command reads the contents of the "q1.txt" file, performs a global text substitution, replacing all occurrences of "Ring" with "Sword," and then saves the modified text to a new file named "q2.txt." The original "q1.txt" remains unchanged, and "q2.txt" contains the modified text.
====================================================================================


11. What are the results of the diff commands in the sequence below?
$ cat > f1.txt
I don’t know half of you
half as well as I should like;
and I like less than half of you
half as well as you deserve
^D
$ sed ’s/half/two\ thirds/g’ < f1.txt > f2.txt (stream editor) (seach for half and replace  two thirds and dump to file f2)
$ diff f1.txt f2.txt (look for differences line by line) s - search  g- globally
$ sed ’s/like/do\ not\ like/g’ < f1.txt > f2.txt (look for like, replace do not like and dump to f2)
$ diff f1.txt f2.txt (look for differences line by line in file)
R: Replaces words found in file line by line and dump to new files,
diff seacrhc for diferences line by line in file

More details:
The command uses the sed (stream editor) utility to perform text substitution in a file named "f1.txt" and save the modified text in a new file named "f2.txt." Here's a breakdown of the command:

sed: This is the sed command, which is a powerful text stream editor in Unix/Linux. It allows you to perform various text transformations on an input stream (or file) and then redirect the modified text to an output stream (or file).

's/half/two\ thirds/g': This part of the command is a sed expression enclosed in single quotes. It specifies the text transformation to be applied to the input text:

s: This is a command within sed that stands for "substitute." It is used to perform text substitutions.
/: This character is used as a delimiter to separate the parts of the sed expression. In this case, it separates the pattern to be replaced ("half") and the replacement pattern ("two thirds").
half: This is the pattern to be replaced in the text.
two\ thirds: This is the replacement pattern. The backslash (\) is used to escape the space character to ensure that "two thirds" is treated as a single string.
/: Another delimiter to separate the replacement pattern and the following g character.
g: This stands for "global," and it's a flag that tells sed to perform the substitution globally throughout the text (i.e., on all occurrences of "half" in each line).
< f1.txt: The < symbol is used to indicate input redirection. It tells sed to take the input from the "f1.txt" file. In other words, "f1.txt" is the source file on which the sed command will operate.

> f2.txt: The > symbol is used to indicate output redirection. It tells sed to write the modified text to the "f2.txt" file. If "f2.txt" does not exist, it will be created. If it already exists, its contents will be overwritten with the modified text.

In summary, the sed command takes the contents of "f1.txt," performs a global text substitution, replacing all occurrences of "half" with "two thirds," and then saves the modified text to "f2.txt." The original "f1.txt" remains unchanged, and "f2.txt" contains the modified text.
====================================================================================


12. What is the output of the last two commands in this sequence? Explain why.
$ cat > numbers1.txt
66
43
77
22
91
^D
$ cat > words1.txt
Rivendell
Gondolin
Lothlorien
Angband
Gondor
Moria
Shire
$ sort -n < numbers1.txt > numbers2.txt (numeric sort)
$ sort -d < words.txt > words2.txt (dictionary sort)
R: Will order the numbers and sentences in increeasing order or dictionary order and redirect to new file
====================================================================================

13. The following command allows you to calculate, with a good approximation, something
about the processes currently being managed by the operating system. What?
$ ps -A | wc -l (Display info all user process | word count each file written on stdout) 
R: shows info user process, and count number of lines the output give (wc -l) on stdout
====================================================================================


14. What is the result of the last command in this sequence? Explain why.
$ emacs &
$ emacs &
$ emacs &
$ ps -A | grep emacs
3577 ttys001 0:00.02 /usr/local/bin/emacs
3578 ttys001 0:00.02 /usr/local/bin/emacs
3579 ttys001 0:00.02 /usr/local/bin/emacs
3583 ttys001 0:00.00 grep emacs
$ kill -9 3577 3578 3579
R: With & lauch process and frees shell command, ps -A | grep emacs lists all process info and filters by those  with name emacs (grep emacs)

Kill -9 sigkill the listed processes

10023 ttys002    0:00.10 emacs
10024 ttys002    0:00.01 emacs
10025 ttys002    0:00.01 emacs
10027 ttys002    0:00.00 grep emacs

[17]+  Stopped                 emacs
(base) HSO:ficha_00 hso$ kill -9 10023 10024 10025
[15]   Killed: 9               emacs
[16]-  Killed: 9               emacs
[17]+  Killed: 9               emacs
(base) HSO:ficha_00 hso$ 
====================================================================================