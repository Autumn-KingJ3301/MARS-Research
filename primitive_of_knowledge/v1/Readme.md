# Primitive of Knowledge

This is a small C implementation of my current research on the **primitive of knowledge**.

> "Distinction could be the starting point of information."

Current chain:

```text
Observation -> Difference -> Distinction
```

## Observation

> "An observation is the captured value of reality at any given instance."

\[
s(t)=f(w(t))
\]

## Difference

> "Difference is the non-overlapping set of values found when two components are compared. It describes how one component is not same as the other."

\[
\Delta(x,y)=\{(i,x_i,y_i)\mid x_i
eq y_i\}
\]

Current C representation stores:

```text
(index, x_value, y_value)
```

Example:

\[
x=(4,8,2),\quad y=(4,5,2)
\]

\[
\Delta(x,y)=\{(2,8,5)\}
\]

## Distinction

> "A distinction is separation of one possible state from another between components; it is a threshold judgement."

\[
d(x,y)>arepsilon
\]

Where:

- \(d\) = magnitude of difference
- \(arepsilon\) = discrimination threshold

### Current distance calculation

For now, the code uses Euclidean distance:

\[
d(x,y)=\sqrt{\sum_i(x_i-y_i)^2}
\]

This is only the current implementation of \(d\), not a final claim that every distinction must use Euclidean distance.

## Current assumptions

- Observations are numerical vectors.
- Two observations have corresponding components.
- Difference is checked using \(x_i
eq y_i\).
- Distinction uses one threshold \(arepsilon\).
- Euclidean distance is currently used for \(d\).

## Research notes

> "A single distinction on its own doesn't explain how, by how much, in what way or whether it will recur."

> "Distinction can also be noise."

> "A distinction is atomic i.e. it is the smallest unit we can define with respect to information."

> "More complex knowledge requires distinctions to be related to other distinctions."

Current open question:

> **How are multiple distinctions organized into something more structured?**

## Structure

```text
include/
    observation.h
    difference.h
    distinction.h

src/
    difference.c
    distinction.c

examples/
    basic.c

tests/
build/
```
