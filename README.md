# Merge_Sort
Program works as follow:
Each time the list is divided; two threads are created to do merge-sort on each half separately. This step is repeated recursively until each sub-list has only one element.

**example input:**

```
10
100 20 15 3 4 8 7 -1 0 33
```
**output:**
```
-1 0 3 7 8 15 20 33 100
```
