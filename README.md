Challenge Summaries:-

Challenge 1- Grid Transformation:
Input Files Used
inputs/grid.txt
inputs/directions.txt

Approach
I read the grid into an array of strings.
I read the directions (R L R L R) and applied rotation row-wise:
R: rotate right → last character moves to front
L: rotate left → first character moves to end
After all rotations, I took the middle row (3rd row, index 2).
I computed the sum of ASCII values of all characters in that row.

Result
Clue 1 = 385


Challenge 2- Multi-Pass Strind Processing 
Input File Used
inputs/input2.txt

Operations (in strict order)
Reverse the string
Remove every 3rd character
Shift each character by +2 ASCII positions
Count vowel characters (a, e, i, o, u)

Approach
The input string was "soscchallenge".
I reversed it.
I iterated through the reversed string and skipped positions where (index+1) % 3==0.
I applied char + 2 to shift ASCII values.
Finally, I counted vowels in the new transformed string.

Result
Clue 2 = 4 (count of vowels)


Challenge 3- State Sequence Simulation. 
Input File
inputs/states.txt → 2 7 10 11 13 4 5

We simulate a 4-state system:
Even numbers → always advance to the next state
Prime numbers → jump directly to the final terminal state
Odd composite numbers → do NOT advance

Approach
I checked each number:
If prime → count as reaching terminal state
If even → simulate movement through states until DONE
If odd composite → stays in initial state
Finally counted how many reach the final state.

Result
Clue 3 = 7


Final Key
Given:
Clue 1 = 385
Clue 2 = 4
Clue 3 = 7

Steps:
Convert Clue 1 to hexadecimal
385 (decimal) → 0x181 → "181"
Repeat the string of Clue 2 exactly Clue 3 times
"4" repeated 7 times → "4444444"
Combine with a hyphen separator:
181-4444444
