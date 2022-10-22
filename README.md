# Finding the determinant using parent and child processes
  Calculating the determinant of a 6x6 matrix using the child process and using wait() system call to halt the parent process and using Shared Memory to access variables shaired bt the parent and the children.

## Objecitive:
* Calculate 3 determinant values of 3 2x2 matrix by forking 3 children
* Put the determinant in a shaired memory to be accessable by the parent.
* halt the parent with wait() to make sure all the children finish executiong and calculating the determimant values
* After the children have finished their jobs access the 3 determinant values in the shaired memeory to calculate the final determinant of a 6x6 matrix

## Challenges facced during developement:
* The child proceses forked child processes of its own.
  * Solved this by using an if statement to make sure the parent can only call the fork() system call.
* The shared memory created by parent was only accessable by the parent.
  * Solved this by forking the children after the shared memory is created.

## How to run the code:
* Make sure the code in running on a system which has linux installed.
* The 6x6 matris is the M int array on the DET.c file
```C
int M[] = {20, 20, 50, 10, 6, 70, 40, 3, 2};
```
* On the terminal do :
```bash
gcc DET.c
./a.out
```
* Output: 
```bash
Memory attached at 3094000
Child Process 1: working with element of D-> 0  
Determinant 1 is -198 calculated by child 1 
Child Process 2: working with element of D-> 1  
Determinant 2 is -2780 calculated by child 2 
Parent entres wait: 582 
Child Process 3: working with element of D-> 2  
Determinant 3 is -210 calculated by child 3 
Parent exit wait: 582 
Determinant M calculated by Parent is: 41140 
Determinant M1 is: -198 
Determinant M2 is: -2780 
Determinant M3 is: -210 
Start Time: 1666469593.499075 sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))
End Time: 1666469593.501042 sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))

Elapsed Time: 1967 micro sec
```
## Things to Note:
* This exercise covers topics from the book: Beginning Linux® Programming 4th Edition Neil Matthew Richard Stones
