In the optimized version of problem1.c, the largest performance improvement comes from a key observation:
We only need the final CENTRAL row.
So we do NOT need to rotate every row.

Original approach
Read all rows
Rotate every row based on directions
Pick central row → sum ASCII values
This costs O(n·m) time (n = rows, m = columns).


Optimized approach
We reduce the work dramatically:
Read direction list once
So we know which direction applies to the central row only.
Scan the grid twice
First pass → count how many rows exist
Second pass → load only the central row
Rotate only the central row
No need to rotate any other row.
Sum ASCII values


Result
Complexity drops from O(n·m) → O(m).
Everything else (memory, logic, output) stays exactly the same.