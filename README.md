# HRML cpp executer

This is my answer to the Hacker Rank's test about parsing attributes.
Code built using Ubuntu 20 g++ compiler.

The execution has two parts.
The first one when the code reads the tags and storage them in the memory.
And the second one where the queries are executed, printing the result in the standard output, if no result is found "Not Found!" is printed.

One tag has its name and its attributes, each attribute needs to have a value with the equal sign before it, and spaces in both sides of the equals sign, for exemple: attribute = "value".
Every tag needs to be closed, so to complement the example: <tagName attribute = "value"></tag>
One tag can be inside of another, although there's the needing of closing them in the same order (like HTML).

The queries needs to be placed after the Tags and both of them in the "in.txt" file.
Before the tags there's need to be a line with two numbers, the first one telling the number of lines that has tags in it, and the second one with the number of queries.
