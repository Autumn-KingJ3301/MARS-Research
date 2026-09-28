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

## Invariance and continuity — working operational definitions

These additions are tools for examining proposed definitions, not claims that
knowledge or identity has been discovered. They retain numerical observations;
no ring, event encoding, modality, or learned transformation is assumed.

For a caller-supplied finite collection of transformations A:

    residual(x, y; A) = min over T in A of distance(T(x), y)
    match(x, y; A, epsilon) iff residual <= epsilon

`invariance()` tests this transformation-relative match. Strictly, this is a
comparison up to an allowed transformation; it does not itself construct an
invariant representation phi satisfying phi(T(x)) = phi(x).
The caller supplies callbacks and their parameters, including the identity
transformation if desired. The current metric is Euclidean distance, inherited
from the existing vector model. Epsilon is inclusive, complementing `> epsilon`
in distinction. Feature units and scaling therefore matter.

The result reports validity, minimum residual, the best candidate's index, and
how many candidates meet the threshold. Several matching candidates indicate
ambiguity; the first minimum is reported without claiming it is uniquely right.
An empty candidate list, invalid observation, invalid tolerance, or failed
callback returns `valid = 0`. A valid comparison with zero matches is a mismatch.
Callbacks must initialize a valid output, respect its fixed capacity, and avoid
mutating the input or context. Context lifetimes remain the caller's responsibility.

`continuity()` tests a pair of samples:

    0 < t2 - t1 <= max_gap AND match(s1, s2; A, epsilon)

This is a working definition of sampled temporal compatibility, not mathematical
continuity. Supply transformations admissible for that particular interval;
movement, speed, deformation, or other domain constraints are caller decisions.
Invalid or unordered times return `valid = 0`. An excessive gap is a valid
comparison with `continuous = 0`; its spatial/feature match remains available.

A sequence has an unbroken chain under this definition only if every adjacent
link passes. Pairwise matching can drift from the initial observation, and does
not prove global invariance or persistent object identity. Tolerance-based
matching need not be transitive; an arbitrary transformation collection need
not make matching symmetric. Occlusion and multiple-object tracking are not
implemented. Transformations are supplied, not discovered.

### Run

From this directory:

```sh
make demo
make test
```

`examples/continuity.c` supplies an additive-offset transformation as a small
example: `[1,3,5]` and `[2,4,6]` differ directly but match under an offset of 1.
The same match fails temporal continuity when its sampling gap is too large.
The offset rule belongs only to the example, not the primitive.

Tests cover transformation-relative matching, tolerance boundaries, ambiguous
matches, invalid inputs, time ordering, time gaps, and timeline capacity.
The existing `change()` loop now compares only actual adjacent pairs, avoiding
its previous read past the final point. Its existing aligned-vector assumptions
otherwise remain unchanged.
