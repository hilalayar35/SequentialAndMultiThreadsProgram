# SequentialAndMultiThreadsProgram


The subject of this project is to calculate the standard deviation of the numbers in one file with sequential and multi-threads program and compare the runtimes of sequential and multi-threads program and see the effect of using multi-threads program on the program’s runtime.
 
Runtime of the multi-threads program is the same or more than the runtime of sequential program. In general, the calculation time increases as the number of threads produced increases. The multi-threads program is more efficient than a sequential program because it divides the calculation into multiple parts. Also, threads use less memory because they share the global datas of the programs. And it is more economical to context-switch between threads than context-switching between processes.

Operating Systems: Ubuntu Linux

Programming Languages: C
