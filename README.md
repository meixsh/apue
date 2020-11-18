my primer apue(advanced programming in unix environment) learning progress.  
include linux commands, gdb, makefile, file-io, process management and multi-thread programming.

- apue main parts start from file introduction. Because anything is file
under unix/linux system, learning file and its io knowledge is very important
for subsequent learning. After studying file and its common cntrolling, apue
starts introducing the conception of process. General speaking, unix/linux is 
famous of its multi-task management. Multi-task can sharing the rare cpu resources of 
a computer, and it can imporve task handling effiency under multi-core or smp.
Naturally, the process conception is built. Important part of process is its 
five status across its whole life, start, ready, running, suspend, dead. In general,
put the start status at right if drawing their status changing figure. 
fork and exec functions are used for creating and assigning new tasks under new 
processes. If one process is forked from another, call them blood related, including 
parent-child and sibling. When a process is dead, should recycle its pcb resources in kernel 
zone. In unix/linux, the recycling work is completed by one's parent process. wait and waitpid
help parent process recyle its child which is dead. 
