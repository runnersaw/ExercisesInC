## Chapter 1


### Compilation

1) Give an example of a feature common in interpreted languages that is rare in compiled languages.

Interpreted languages can have dynamic types, so you can change the type of variables at runtime.

2) Name two advantages of static typing over dynamic typing.

1. Error checking at compile time. For example, changing the type of a variable in Python could break your program at runtime, but in C an int will always be able to be added to another int.
2. Memory saving. For example, all variable names are stored when running a program in Python.

3) Give an example of a static semantic error.

`int x = "hi";`

4) What are two reasons you might want to turn off code optimization?

1. Improves ease of debugging.
2. Lower compile time.

5) When you run `gcc` with `-S`, why might the results look different on different computers?

Computers might run different architectures, which have different versions of assembly language.

6) If you spell a variable name wrong, or if you spell a function name wrong,
the error messages you get might look very different.  Why?

Those steps are handled by different steps. Functions are linked by a linker, and variables are a different step of the process.

7) What is a segmentation fault?

Reading or writing to an incorrect location in memory.


## Chapter 2


### Processes

1) Give a real-world example of virtualization (ideally not one of the ones in the book).

Video game emulation is an example of virtualization. For example, I have an emulator for an old Playstation on my system that uses virtualization.

2) What is the difference between a program and a process?

A process is an object that represents a running program. It contains information about what to run and the current state of the program. Multiple processes can be used to run one program, in which case they share program text, but each have independent states. It is also possible for one program to run multiple processes.

3) What is the primary purpose of the process abstraction?  What illusion does the process abstraction create?

The process abstraction creates the illusion that the process is running in its own space and doesn't have to worry about interfering with or getting interfered with by any other process. 

4) What is the kernel?

The kernel is the part of the operating system that handles core capabilities and maintains the abstractions for the rest of the software.

5) What is a daemon?

A daemon is a process that runs in the background.


## Chapter 3


### Virtual memory

1) The Georgian alphabet has 33 letters.  How many bit are needed to specify a letter?

6 bits.

2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.
Ignoring the details of the encoding scheme, how many different characters can be represented?

4 GiB

3) What is the difference between "memory" and "storage" as defined in Think OS?

Memory is volatile, which means that it goes away when the computer is shut off. Storage persists even between machine restarts.

4) What is the difference between a GiB and a GB?  What is the percentage difference in their sizes?

A GiB is 2^30, and a GB is 1,000,000,000. These are different by 7.4%.

5) How does the virtual memory system help isolate processes from each other?

The operating system maps virtual memory on a per-process basis, so even if two processes tried to access the same virtual address, they would each get their own physical address.

6) Why do you think the stack and the heap are usually located at opposite ends of the address space?

This is probably to make it easier for the operating system to keep track of them and keep them separate so that they don't override or overlap with each other.

7) What Python data structure would you use to represent a sparse array?

A dictionary.

8) What is a context switch?

When the operating system pauses a process, and begins to run another process.

In this directory, you should find a subdirectory named `aspace` that contains `aspace.c`.  Run it on your computer and compare your results to mine.

```
Address of main is 0x40057d
Address of global is 0x60104c
Address of local is 0x7ffc2a19b884
Address of p is 0x1ad1010
```

1) Add a second call to `malloc` and check whether the heap on your system grows up (toward larger addresses).

2) Add a function that prints the address of a local variable, and check whether the stack grows down.

q is a new pointer to memory that is allocated with `malloc` after p. l is a new local that is allocated after local. You can see that q has a higher memory address that p, which means that the heap grows up. l has a higher address than local, which seems weird to me. I though that the stack grows down, so I would expect l to have a lower address than local

```
Address of main is 0x40057d
Address of global is 0x60104c
Address of local is 0x7fff78a9bb88
Address of l is 0x7fff78a9bb8c
Address of p is 0x1a5a010
Address of q is 0x1a5a0a0
```

3) Choose a random number between 1 and 32, and allocate two chunks with that size.
How much space is there between them?  Hint: Google knows how to subtract hexadecimal numbers.

I picked 24 and got:

```
Address of p is 0x79b010
Address of q is 0x79b030
```

Their difference is 0x20, which is actually 32. There is more space between them than 24.

## Chapter 4


### Files and file systems

1) What abstractions do file systems provide?  Give an example of something that is logically true about files systems but not true of their implementations.

They provide the abstraction that file systems are actually a dictionary from strings to bytes. The actual implementations obviously need to do work to translate the string into the memory address, and they have to do work to read or write from blocks in such a way that it abstracts away the blocks and pretends that everything is bytes.

2) What information do you imagine is stored in an `OpenFileTableEntry`?

- Current memory address
- File name
- Read/write mode

3) What are some of the ways operating systems deal with the relatively slow performance of persistent storage?

Operating systems can switch to other processes while it is waiting for an I/O operation to finish. It can also pre-load blocks for you based on heuristics (such as loading the next block after the one you're currently looking at). It only performs writes when the file is closed or the processor has idle time to write it.

4) Suppose your program writes a file and prints a message indicating that it is done writing.Then a power cut crashes your computer.  After you restore power and reboot the computer, you find that the file you wrote is not there.  What happened?

It is possible that the write only wrote to a buffer, and the operating system had not yet completed the work of writing that buffer to the disk.

5) Can you think of one advantage of a File Allocation Table over a UNIX inode?  Or an advantage of a inode over a FAT?

The FAT implementation seems like a linked list, so it is probably generally easy to insert or delete or move pieces of memory, but that means that reading farther into the file might take longer, since you have to traverse a linked list. 

6) What is overhead?  What is fragmentation?

Overhead is the amount of space used to keep track of current allocations. Fragmentation is when some blocks are left unused or are only partially used.

7) Why is the "everything is a file" principle a good idea?  Why might it be a bad idea?

It makes it easy for processes to interface with each other, as it is defined that they will both take and output a stream of bytes. This could be a bad idea maybe if the abstraction means that the operating system has to do more work to provide that abstraction.

If you would like to learn more about file systems, a good next step is to learn about journaling file systems.
Start with [this Wikipedia article](https://en.wikipedia.org/wiki/Journaling_file_system), then
[Anatomy of Linux Journaling File Systems](http://www.ibm.com/developerworks/library/l-journaling-filesystems/index.html).
Also consider reading [this USENIX paper](https://www.usenix.org/legacy/event/usenix05/tech/general/full_papers/prabhakaran/prabhakaran.pdf).


## Chapter 5


### Bits and bytes

1) Suppose you have the value 128 stored as an unsigned 8-bit number.  What happens if you convert
it to a 16-bit number and accidentally apply sign extension?

128 = 10000000
128 -> 16-bit w/ sign extension = 11111111 10000000
Interpreted as unsigned integer: 65408

2) Write a C expression that computes the two's complement of 12 using the XOR bitwise operator.
Try it out and confirm that the result is interpreted as -12.

```
#include <stdio.h>

int two_complement(int x) {
  int complement = x ^ 0xffffffff;
  return complement + 1;
}

int main() {
  printf("%d\n", two_complement(12));
  return 0;
}
```

3) Can you guess why IEEE floating-point uses biased integers to represent the exponent rather than a
sign bit or two's complement?

To shift the center of the represented numbers in order to have greater accuracy for larger orders of magnitude than very small decimals. For example, with a bias of 127, maybe you can have the same precision for 255 as you can have for the ones digit.

4) Following the example in Section 5.4, write the 32-bit binary representation of -13 in single precision
IEEE floating-point.  What would you get if you accidentally interpreted this value as an integer?

You would get some nonsense number that would probably be very large because there is likely bits in the top 9 bits (due to either sign or exponent).

5) Write a function that takes a string and converts from lower-case to upper-case by flipping the sixth bit.
As a challenge, you can make a faster version by reading the string 32 or 64 bits at a time, rather than one
character at a time.  This optimization is made easier if the length of the string is a multiple of 4 or 8 bytes.

```
def upper(char *str) {
  char *c = str;
  while (*c != '\0') {
    *c = *c ^ 0x20;
  }
}
```

## Chapter 6


### Memory management

1) Which memory management functions would you expect to take constant time?  Which ones take time proportional to the size of the allocated chunk?

2) For each of the following memory errors, give an example of something that might go wrong:

a) Reading from unallocated memory.

Getting a garbage value that doesn't make sense.

b) Writing to unallocated memory.

Segfault

c) Reading from a freed chunk.

Getting a garbage value or segfault.

d) Writing to a freed chunk.

Segfault/override other data

e) Failing to free a chunk that is no longer needed.

Running out of memory

3) Run

    ps aux --sort rss

to see a list of processes sorted by RSS, which is "resident set size", the amount of physical
memory a process has.  Which processes are using the most memory?

```
python3
mongod
compix
Xorg
evolution-calendar-factory
```

4) What's wrong with allocating a large number of small chunks?  What can you do to mitigate the problem?

There is a minimum chunk size, so you may be using a lot of physical space that you don't need to.

If you want to know more about how malloc works, read
[Doug Lea's paper about dlmalloc](http://gee.cs.oswego.edu/dl/html/malloc.html)



## Chapter 7


### Caching

1) What happens if a program writes a new value into the program counter?

2) What is the fundamental problem caches are meant to solve?

3) If cache access time is 1 ns and memory access time is 10 ns, what is the average
access time of a program with hit rate 50%?  How about 90%?

4) The book gives several examples of programming language features, like loops, that tend
to improve locality in the access pattern of instructions and/or data.  Can you think of other examples?
Or counter-examples that might decrease locality?

5)  If you refactor a program to improve locality, would you say the program is "cache aware"?  Why not?

6) See if you can estimate the cost of a memory cache by comparing the prices of two similar CPUs with
different cache sizes.

7) Why are cache policies generally more complex at the bottom of the memory hierarchy?

8) Can you think of a strategy operating systems could use to avoid thrashing or recover when it occurs?

Run the cache code on your laptop or another computer and see if you can infer the cache size and block size.
If you can find the technical specifications for your computer, see if your inferences are right.

1) In this directory you should find a subdirectory named `cache` that contains `cache.c` and supporting files.  Read `cache.c`, then run `make` and `./cache`.

2) Run `python graph_data.py` to see the results.  What can you infer about the cache structure on your computer?


## Chapter 8


### Multitasking

1) What is the kernel's most basic task?

2) When an interrupt occurs, what part of the hardware state is saved by hardware?

3) What is the difference between an interrupt and a context switch?

4) Give an example of an event that might cause a process to move from the blocked to the ready state.

5) Why might a scheduler want to give higher priority to an I/O bound process?

When I make French toast, I usually make a batch of 12 slices.  But my griddle only has room for 8 slices.  Each piece of toast has to cook for 5 minutes on each side.  How can I schedule 12 slices onto 8 "cores" to minimize the elapsed time to cook all 12 slices?  (Note: this question is not hypothetical; this is really how I make French toast.)



## Chapter 9


### POSIX threads and mutexes

As you read Chapter 9, you should compile and run the example code.  By the nature of multi-threaded programs, you results will probably be different from mine, possibly in interesting ways.

1) Why does each thread have its own stack?

2) What does the `gcc flag -lpthread` do?

3) What does the argument of `pthread_exit` do?

4) Normally the same thread that created a thread also waits to join it.  What happens if another thread tries to join a thread it did not create?

5) What goes wrong if several threads try to increment a shared integer at the same time?

6) What does it mean to "lock a mutex"?



## Chapter 10


### Condition variables

1) What does it mean to say that a data structure is thread safe?

2) In the circular buffer implementation of a queue, why is the maximum number of elements in the queue `n-1`,
if `n` is the size of the array?

3) If there is no mutex to protect the queue, give an example of a sequence of steps that could leave
the queue in an inconsistent state.

4) When a thread calls cond_wait, why does it have to unlock the mutex before blocking?

5) When a thread returns from cond_wait, what do we know is definitely true?  What do we think is probably true?

6) What happens if you signal a condition variable when there are no waiting threads?

7) Do you have to lock the mutex to signal a condition variable?

8) Does the condition have to be true when you signal a condition variable?



## Chapter 11


### Semaphores in C
