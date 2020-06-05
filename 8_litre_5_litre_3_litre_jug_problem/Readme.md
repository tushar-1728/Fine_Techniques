## Implementation
- Back-trackng and state-space search approach for solving a special case of 8 litre 5 litre 3 litre jug problem.
- User is asked to enter the initial and final state and the output is redirected to op.txt file.
## Input format:
1. In first line user is supposed to enter initial contents of 8, 5 and 3 litre jug.
2. In second line user is supposed to enter final contents of 8, 5 and 3 litre jug.
### Sample input:
> Enter the initial contents of 8L 5L 3L jug: 8 0 0  
> Enter the final contents of 8L 5L 3L jug: 4 4 0

## Format of output file:
1. First all the transitions which lead to solution are listed, contents of each jug separated by space, each transition separated by newline and each set of transitions separated by 2 newlines.
2. The last line gives the total number of solutons.
### Sample output:
> 8 0 0  
> 3 5 0  
> 3 2 3  
> 6 2 0  
> 6 0 2  
> 1 5 2  
> 1 4 3  
> 4 4 0  
>
> 8 0 0  
> 5 0 3  
> ...  
> ...  
> 4 4 0  
>
> ...  
> ...  
> ...  
>
> 16

## Code for executing the C program:
```bash
gcc client.c impl.c
```
