
# Round 2 — Coding Puzzle Challenge (2nd Years)

This challenge contains three independent problems. 
Each generates a numerical or symbolic clue. 
Your final answer is a composed key generated from all clues 
(precise combination rule included at the end).

No examples are provided intentionally.

---

## Problem 1 — Grid Transform
Using `inputs/grid.txt` and `inputs/directions.txt`, 
perform the prescribed transformations row-wise. 
Interpret rotation instructions strictly. 
After all operations, isolate the central row 
(central meaning index floor(n/2)). 
Compute a cumulative metric defined as the sum of integer representations 
of all characters in that row. 
This value becomes **Clue 1**.

---

## Problem 2 — Multi-Pass String Process
Given `inputs/input2.txt`, follow these operations IN ORDER:
1. Reverse.
2. Remove every k-th position where k = 3.
3. Apply a positive displacement of +2 over the underlying ordinal encoding 
   of each symbol.
4. Determine the count of vowel-class characters in the resulting sequence.

This count becomes **Clue 2**.

(*Interpret vowel-class using standard English vowel set.*)

---

## Problem 3 — State Sequence Simulation
Using `inputs/states.txt`, simulate movement through a 4‑state 
transition system with the following rules:

- Even-valued elements advance deterministically forward by one state per rule.
- Prime-valued elements do not follow the even rule; 
  instead they are subject to a distinct rule involving a direct transition.
- Odd composite elements follow a fallback rule and do not advance.

Count how many elements terminate in the final terminal state. 
This count becomes **Clue 3**.

---

## Final Key
The final key requires:
- Transforming Clue 1 into a non-decimal representation (base-16).
- Repeating the string representation of Clue 2 exactly Clue 3 times.
- Joining them with a symbolic separator.

---

**final_key should be:**

<hex of clue1>-<clue2 repeated clue3 times>

---

## File Naming Rules
Inside `solutions/`:
- Replace placeholder files with actual code files in your chosen language.
- Acceptable: problem1.py, problem1.cpp, problem1.java, problem1.js, etc.
- Do NOT leave files extensionless except final_key.txt.
- final_key.txt must contain ONLY the computed final key.

---

## Submission Requirements
Submit:
- All code files inside `solutions/`
- final_key.txt
- Your own README.md explaining your reasoning
- Do NOT include compiled binaries.

