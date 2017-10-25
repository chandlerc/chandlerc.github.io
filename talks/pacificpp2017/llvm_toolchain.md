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

# LLVM: A Modern, Open C++ Toolchain
.footnote[Chandler Carruth, <chandlerc@gmail.com>, [@chandlerc1024](https://twitter.com/chandlerc1024)]

???
Intro:
- I'm Chandler Carruth
- I'm the lead for Google's C++ PL platform
- Also one of the core developers on the LLVM open source compiler project

TODO: moar intro

---
name: cxx-up-and-to-the-right
template: title-layout

# C++ is taking off

???
- Regular release cadence
- Awesome new features
- Continues to be uniquely positioned for performance critical or resource
  constrained code

TODO: maybe show Herb's graphic about the process?

---
name: toolchains-are-lagging
template: title-layout

# C++ toolchains ... aren't

???
- Toolchains dragging compared to the language
- Poll audience what compiler they can rely on when writing 80% of their C++
  code

---
name: toolchains-are-lagging-debian
template: title-layout

## Debian: GCC 6, Clang 3.8

---
name: toolchains-are-lagging-xenial
template: title-layout

## Ubuntu LTS (Xenial): GCC 5, Clang 3.8

---
name: toolchains-are-lagging-trusty
template: title-layout

## Ubuntu LTS (Trusty): GCC 4.8, Clang 3.4

---
name: toolchains-are-lagging-rhel
template: title-layout

## RHEL: GCC 4.8, Clang: NOPE!

---
name: toolchains-are-lagging-sad
template: title-layout

# =[

---
name: toolchain-release-cylces
template: basic-layout

## Stacked release cycles add up quickly
1. 6-months to 1-year for toolchain release
2. 6-months to N-years for distro release
3. ??? for deployment of distro

---
name: toolchain-bug-cycle
template: title-layout

## What happens when you hit a bug?

---
name: toolchain-bug-cycle
template: basic-layout

## Bug fixes are a nightmare...
1. 1 to N years to get new toolchain
2. Days or months to find a bug and report it
3. Days or months for upstream to fix it
4. 1 to N years to get fixed toolchain???

---
name: toolchain-dev
template: title-layout

## Need to develop toolchain in-house?

(you know, like Google, Apple, and others?)

???
The only path forward seems to be to develop an in-house toolchain...
This is what Google, Apple, Sony, Intel, IBM, ARM, Microsoft, and more all do.
But this is nuts, owning and developing toolchains is crazy hard, right?

---
name: toolchain-mission-impossible
template: title-layout

# In-house toolchain seems crazy...

???
make goofy mission impossible references, wake people up

---
name: closed-source
template: title-layout

### First: many are closed source and proprietary

---
name: hacking-gcc
template: title-layout

### Second: GCC is open source, but hard to hack on

---
name: binutils-linkers-and-gdb-oh-my
template: title-layout

### Third: Need to build binutils, GDB, etc.

.footnote[There is a whole project around this: Crosstool-NG]

---
name: dont-forget-the-bugs
template: title-layout

### Fourth: Now you need to debug miscompiles!

---
name: companies-invest-lots-in-toolchains
template: title-layout

## Companies doing this today are *huge!*

---
name: toolchain-impossible-redux
template: title-layout

# Building your own toolchain?

---
name: toolchain-impossible-redux-big
template: title-layout

# *IMPOSSIBLE!*

---
name: toolchain-in-a-talk
template: title-layout

# So let's do it live, during the talk!

---
name: llvm-game-changer 
template: title-layout

# LLVM changes the game a bit. ;]

---
name: what-is-llvm
template: basic-layout

## What is LLVM?
- Open source project
- Moduler collection of compiler & toolchain infra
- Includes code generation, optimization, linking, and loading
- Written in C++, of course. ;]

.footnote[(The letters don't stand for anything, like XKCD.)]

---
name: what-can-llvm-do

## What can you do with LLVM?
- Code generation for DSLs (e.g. Halide or XLA)
- Traditional compilers for general purpose languages
- Developer / editor tools for static analysis, refactoring, etc.
- There are active frontends targeting LLVM for a huge number of languages,
  including, of course...

.footnote[(DSL: Domain Specific Language)]

---
name: clang-fe
template: title-layout

## Clang: the LLVM C++ frontend

---
name: backup-llvm-is-software
template: title-layout

# But LLVM is still just C++ software

---
name: llvm-has-bugs
template: title-layout

## LLVM has bugs!

### (just like other software)

---
name: you-can-hack-onllvm
template: title-layout

## You can hack on LLVM!

###(just like other software)

---
name: open-source-community
template: title-layout

## *Open source* software:<br/> it comes with a community

---
name: back-to-demo
template: title-layout

# OK, back to building LLVM...

---
name: wrapup-time 
template: title-layout

# Summary time!

---
name: cxx-moving-faster
template: title-layout

## C++ is moving faster<br/>Your toolchain needs to catch up

---
name: toolchains-just-software
template: title-layout

## C++ toolchains are C++ software

---
name: hack-on-toolchains
template: title-layout

## If you hack on C++ software,<br/>you can hack on your toolchain

---
name: get-llvm
template: title-layout

## Start using (and hacking) on LLVM<br/>Enjoy some amazing tools

---
name: questions
template: title-layout

# Questions?

???

