name: title-layout
layout: true
class: center, middle, title

---
name: basic-layout
layout: true
class: left, top

---
name: title
template: title-layout

# Going Nowhere Faster
.footnote[Chandler Carruth, <chandlerc@gmail.com>, [@chandlerc1024](https://twitter.com/chandlerc1024)]

???
Intro:
- I'm Chandler Carruth
- I'm the lead for Google's C++ PL platform
- Also one of the core developers on the LLVM open source compiler project
- Obsessed with performance and optimization.

This is the third talk I'm giving on performance here at CppCon, super excited
to be back.

---
name: reflect
template: title-layout

1. Use efficient algorithms, fast data structures & idioms
1. Benchmark the code that matters, understand why
1. Use hybrid data structures to optimize allocations & cache locality

???
T+2 minutes -- take it slow to let folks settle

---
name: benchmark
template: title-layout

# You only care about performance that you benchmark!

---
name: you-have-a-loop
template: title-layout

# So you have a loop in a benchmark...

???
T+3 minutes -- ok, wrap up the slow intro, let's get down to business

---
name: data-oriented
template: title-layout

# It's probably the data...
- Watch Mike Acton's talk; use data-oriented design
- See my talk about profiling, but use counters to track cache miss rates
- In the future, use tools like Efficiency Sanitizer to optimize data structures

???
30 seconds of talking here worthwhile. give some context for ESan.

TODO(chandlerc): build a benchmark that suffers from cache misses and use perf live to catch it.
This will take 1-2 minutes to walk through, 1-2 minutes to benchmark, use perf events, and explain how it catches this

---
name: small-loops
template: title-layout

# What about small, tight loops?

???
T+8 minutes here, pick it up if T+10

Look at a simple "clamp" loop microbenchmark

- Show the most basic clamp loop (30s)
- Draw analogy to zlib and other compression algos for why this matters, get it all building and running (1m)
- discuss "obvious" alternatives on x86: cmov vs. branch (30s)
- (hopefully) show cmov being sloooooooow. why? don't switch to perf counters or profile deeply yet (30s

---
name: ooo-start
template: title-layout

# Modern processors are highly speculative

???
T+10 minutes

TODO: insert OOO demo from Jakub's keynote here

---
name: ooo-dot-product
template: basic-layout

```
int dot(int a[], int b[], int n)
{
 int sum = 0;
 for (int i = 0; i < n; i++)
 sum += a[i] * b[i];
 return sum;
}
```

---
name: ooo-demo
template: title-layout

# What tools can we use to identify this?

???
T+15 minutes

Back to the clamp loop

- use perf counters to show IPC and lack of stalls w/ branch, but stalls w/ cmov.
T+18 minutes

- introduce IACA, show throughput analysis
T+23 minutes

---
name: conclusion
template: title-layout

## 2.5 small size optimized structures, pointers, and bit packing

---
name: questions
template: title-layout

# Questions?

---
name: image-dummy
template: basic-layout
background-image: url(DragonFull.png)

???

---
name: code-dummy
template: basic-layout

```
```

???

---
name: two-col-dummy
template: basic-layout

.left-col[
```
```
]
.right-col[
```
```
]

???

---
name: img-dummy
template: title-layout

![Give me a pointer!](http://imgs.xkcd.com/comics/pointers.png)
.footnote[<http://xkcd.com/138/>]

???

