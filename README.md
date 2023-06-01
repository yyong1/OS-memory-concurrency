# OS-memory-concurrency

```OUTPUT
Pausing the program. Press enter to continue...

Memory Usage:
  PID    RSS      VSZ COMMAND
68759    928 407972448 ./pr

Memory Image:
  PID STAT      TIME  SL  RE PAGEIN      VSZ    RSS   LIM     TSIZ  %CPU %MEM COMMAND
65206 Ss     0:01.16   0   0      0 408432496   3600     -        0   0,0  0,0 /bin/zsh -il
68759 S+     0:00.01   0   0      0 407973472    960     -        0   0,0  0,0 ./pr
Pausing the program. Press enter to continue...

Memory Usage:
  PID    RSS      VSZ COMMAND
68759    960 407973488 ./pr

Memory Image:
  PID STAT      TIME  SL  RE PAGEIN      VSZ    RSS   LIM     TSIZ  %CPU %MEM COMMAND
65206 Ss     0:01.16   0   0      0 408432496   3600     -        0   0,0  0,0 /bin/zsh -il
68759 S+     0:00.01   0   0      0 407974512    992     -        0   0,0  0,0 ./pr
Pausing the program. Press enter to continue...

Memory Usage:
  PID    RSS      VSZ COMMAND
68759   1040 407975536 ./pr

Memory Image:
  PID STAT      TIME  SL  RE PAGEIN      VSZ    RSS   LIM     TSIZ  %CPU %MEM COMMAND
65206 Ss     0:01.16   0   0      0 408432496   3600     -        0   0,0  0,0 /bin/zsh -il
68759 S+     0:00.01   0   0      0 407976560   1072     -        0   0,0  0,0 ./pr
```
Task 2.1. Memory management tools
- Understand how the mmap and munmap system calls work. Explore how to use mmap to obtain
pages of memory from the OS, and allocate chunks from these pages dynamically when
requested. Familiarize yourself with the various arguments to the mmap system call.
- Write a simple C program that runs for a long duration, say, by pausing for user input or by
sleeping. While the process is active, use the ps or any other similar command with suitable
options, to measure the memory usage of the process. Specifically, measure the virtual memory
size (VSZ) of the process, and the resident set size (RSS) of the process (which includes only
the physical RAM pages allocated to the process). You should also be able to see the various
pieces of the memory image of the process in the Linux proc file system, by accessing a
suitable file in the proc filesystem.
- Now, add code to your simple program to memory map an empty page from the OS. For this
program, it makes sense to ask the OS for an anonymous page (since it is not backed by any
file on disk) and in private mode (since you are not sharing this page with other processes). Do
not do anything else with the memory mapped page. Now, pause your program again and
measure the virtual and physical memory consumed by your process. What has changed, and
how do you explain it?
- Finally, write some data into your memory mapped page and measure the virtual and physical
memory usage again. Explain what you find.

Answer: 
1.After memory mapping an empty page from the OS, both the virtual memory size (VSZ) and resident set size (RSS) of the process have increased. This is because the memory-mapped page is now allocated in the process's address space, resulting in an increase in the virtual memory usage. However, the physical memory usage (RSS) may not change significantly unless the page is accessed and populated with data.

2.When data is written into the memory-mapped page, the virtual memory size (VSZ) remains the same as before. However, the resident set size (RSS) increases, indicating that physical memory is now allocated for the page. This increase in RSS reflects the actual memory usage of the process due to the data written into the memory-mapped page.