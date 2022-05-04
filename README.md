<p align="center">
<img src="./gnl-logo.png" />
</p>
<h1 align="center">Get Next Line [GNL] </h1>
<p align="center">Function that returns a line read from a file descriptor: we should be
able to call getNextLine(int fd) multiple times and returns one line at a time. If some error occur or EOF is reached, return NULL.</p>

_

- SUMMARY |
The aim of this project is to code a function that returns a line, read from a file descriptor.

- NAME |
get_next_line - get line from a file descriptor

- SYNOPSIS |
#include "get_next_line.h"
char	*get_next_line(int fd);

- DESCRIPTION |
get_next_line() read a file descriptor and search for a '\n'(a line). If fd is -1, get_next_line() may detect the error.

- RETURN VALUE |
On success, the line read. If no '\n' is found and it reaches end of file, return what was read. If there is nothing to read, return NULL.

_

<h2>Useful Links</h2>
<ul>
<li><a href="https://github.com/fegastal/42SP_get_next_line/blob/main/my-notes-about-the-project.pdf.pdf">Static Variables</a></li>
<li><a href="https://github.com/fegastal/42SP_get_next_line/blob/main/memory_CS50x_harvard.pdf">Pointers</a></li>
<li><a href="https://github.com/fegastal/42SP_get_next_line/blob/main/dynamic_allocation_sizeof.pdf">Memory allocation</a></li>
<li><a href="">Analyse and Avoid Memory Leaks</a></li>
<li><a href="">Linked Lists (used in bonus part)</a></li>
</ul>

<h2>Use cases to consider</h2>
<ul>
<li>BUFFER_SIZE=1</li>
<li>BUFFER_SIZE=42</li>
<li>BUFFER_SIZE=1000000</li>
<li>BUFFER_SIZE=-32</li>
<li>FD VALID</li>
<li>FD Invalid</li>
<li>FD Empty</li>
<li>FD Multiple lines</li>
<li>FD Single line</li>
<li>FD with only multiples '\n'</li>
<li>After reach EOF, verify if has something in accumulator</li>
</ul>
