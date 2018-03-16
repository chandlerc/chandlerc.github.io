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

# Spectre
## Speculative Execution Covert Side-Channels
.footnote[Chandler Carruth, <chandlerc@gmail.com>, [@chandlerc1024](https://twitter.com/chandlerc1024)]

???
Intro:

---
name: understanding
template: title-layout

# Understanding Spectre variant #1

???

- First, let's walk through how Spectre v1 works.
- This is the most fundamental and important variant.
- Other variants typically involve some specific hardware flaw, makes them more
  viable to "just fix" in hardware long-term.
- v1 is very fundamental to how we scale up performance of superscalar
  processors with increasing memory latency relative to clock rate: speculative,
  out-of-order execution through accurate branch prediction.
- important to know the critical components: speculative execution, with
  prediction, and a covert side-channel
- There is always a side-channel though. Assume it. Focus on the speculation and
  prediction.

- For completeness, there is a v2 as well as Meltdown, but we won't be covering
  that in any detail.

---
name: v1-ex1.0
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

if (untrusted_offset < arr1->length) {
  unsigned char value = arr1->data[untrusted_offset];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- Basic example from the Google Project Zero blog post
- Let's step through it to see how spectre attacks this

---
name: v1-ex1.1
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

*if (untrusted_offset < arr1->length) {
  unsigned char value = arr1->data[untrusted_offset];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- first, we cause the length to be out of cache or otherwise make this
  comparison resolve VERY SLOWLY
- since it is slow, the branch predictor will be used to figure out where to go
- branch predictor has *no* access to the data in these registers or the
  comparison, just uses the address in the instruction pointer and some
  history-based prediction to figure out which edge to take
- Can train this to predict that the offset is in-bounds and then send
  a surprise out-of-bounds offset but still be predicted to be in-bounds

---
name: v1-ex1.2
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

if (untrusted_offset < arr1->length) {
* unsigned char value = arr1->data[untrusted_offset];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- So now we're speculating, entering the predicted destination. all of this will
  be thrown away, but not before we potentially leak some data
- Here we do a load from memory with this offset. the bounds check hasn't
  actually happened, so the offset could be *anything*. it could be attack
  controlled and thus arbitrarily move around the address space
- The load takes place (again, speculatively)

---
name: v1-ex1.3
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

if (untrusted_offset < arr1->length) {
  unsigned char value = arr1->data[untrusted_offset];
* unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- Now we extract a bit from the loaded valaue and use it to select two other
  offsets

---
name: v1-ex1.4
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

if (untrusted_offset < arr1->length) {
  unsigned char value = arr1->data[untrusted_offset];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
* unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- And finally, we access memory using this index.
- Index depends on a bit of the loaded value, and which index we load determines
  which cache line is populated
- Attacker can time these two cache lines later to recover a bit of the loaded
  value.

---
name: v1-ex2.0
template: basic-layout

```cpp
const char *string::get_pointer() const {
  if (is_long())
    return get_long_pointer();
  else
    return get_short_pointer();
}

const char &string::operator[](size_t i) const {
	const char *pointer = get_pointer();
  return pointetr[i];
}

const char *string::data() const {
	return get_pointer();
}
```

???
- This isn't just about bounds checks though, we can bypass arbitrary predicates

---
name: v1-ex2.1
template: basic-layout

```cpp
const char *string::get_pointer() const {
* if (is_long())
    return get_long_pointer();
  else
    return get_short_pointer();
}

const char &string::operator[](size_t i) const {
	const char *pointer = get_pointer();
  return pointetr[i];
}

const char *string::data() const {
	return get_pointer();
}
```

???
- ...like the check for the correct representation for a small string.
- can also operate interprocedurally, speculating both in and back out of
  functions

---
name: v1-ex3.0
template: basic-layout

```cpp
struct KeyBase {
  virtual sha256 secure_hash() = 0;
private:
  std::vector<std::byte> key_data;
};

struct PublicKey : KeyBase {
  sha256 secure_hash() override {
    return fast_non_constant_time_hash(key_data);
  }
};

struct PrivateKey : KeyBase {
  sha256 secure_hash() override {
    return slow_constant_time_hash(key_data);
  }
};

void do_crypto(KeyBase &key) const {
  auto h = key.secure_hash();
  // ...
}
```

???
- Can even have type confusion where we go to the wrong destination of an
  indirect call

---
name: v1-ex3.1
template: basic-layout

```cpp
struct KeyBase {
  virtual sha256 secure_hash() = 0;
private:
  std::vector<std::byte> key_data;
};

struct PublicKey : KeyBase {
  sha256 secure_hash() override {
    return fast_non_constant_time_hash(key_data);
  }
};

struct PrivateKey : KeyBase {
  sha256 secure_hash() override {
    return slow_constant_time_hash(key_data);
  }
};

void do_crypto(KeyBase &key) const {
* auto h = key.secure_hash();
  // ...
}
```

???
- These indirect calls are predicted just like conditional branches
- Can call w/ public keys over and over until it is trained in that direction
- Run it w/ a private key and get some of the information leaks in their crypto
  code

---
name: m1
template: basic-layout

```cpp
template <typename T>
T load_no_speculate(const volatile T *ptr, const volatile void *lower,
                    const volatile void *upper, T failval,
                    const volatile void *cmpptr) {
  T result;

  if (cmpptr >= lower && cmpptr < upper)
    result = *ptr;
  else
    result = failval;
  return result;
}
```

???
- Initial idea around mitigation APIs for this focused on the bounds check
  aspects.
- We developed several variations internally, but they all were variations on
  what ARM has published as part of their work.

---
name: v1-ex1-m1
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

if (untrusted_offset < arr1->length) {
* unsigned char value = load_no_speculate(arr1->data + untrusted_offset,
*                                         arr1->data, arr1->data + arr1->length,
*                                         0u, arr1->data + untrusted_offset);
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- We can add it to our first example like this. it's pretty verbose and heavy
  weight.
- Plus, in some cases it is quite expensive as we have to re-compute the
  predicate.
- Last but not least, doesn't work at all w/ the other examples

---
name: m2
template: basic-layout

```cpp
// Requires: All 'Ts' are integral or pointer types.
// Returns: 'predicate'.
// Remarks: If 'predicate' is false, then any speculative execution in
// which it is treated as true will also treat 'zero_args...' as zero.
template <typename ...Ts>
bool protect_from_speculation(bool predicate, Ts &...zero_args);
```

???
- So we suggested a more general API. This is what was in the initial revision
  of the paper.

---
name: v1-ex1-m2
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

*if (protect_from_speculation(untrusted_offset < arr1->length,
*                            untrusted_offset)) {
  unsigned char value = arr1->data[untrusted_offset];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- This works much more cleanly and orthogonally.
- Working on prototypes of this. good idea of how to codgen efficiently.
- Important to realize at this point that this routine is truly magical.
  - Doesn't actually obey as-if and constraints, etc.

---
name: v1-ex1-m2b
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset = ...;

if (untrusted_offset < 0)
  return;

// Loooooooots of code....

*if (protect_from_speculation(untrusted_offset < arr1->length,
*                            untrusted_offset)) {
  unsigned char value = arr1->data[untrusted_offset];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- For example, we may have missed marking intermediate predicates that could
  cause our predicates to get bypassed. Need to make this as-if the variables
  referenced in this predicate are potentially modified right before evaluating
  them.

---
name: v1-ex2-m2
template: basic-layout

```cpp
const char *string::get_pointer() const {
* if (protect_from_speculation(is_long(), this)
    return get_long_pointer();
  else
    return get_short_pointer();
}

const char &string::operator[](size_t i) const {
	const char *pointer = get_pointer();
  return pointetr[i];
}

const char *string::data() const {
	return get_pointer();
}
```

???
- But using this to mitigate the second example starts to get... awkward.
- We can't realistically mutate the `this` pointer here.

---
name: v1-ex2-m2b
template: basic-layout

```cpp
const char *string::get_pointer() const {
  bool is_short = !protect_from_speculation(is_long(), this);
  // ... lots of code ...
* if (is_short)
    return get_short_pointer();
  else
    return get_long_pointer();
}

const char &string::operator[](size_t i) const {
	const char *pointer = get_pointer();
  return pointetr[i];
}

const char *string::data() const {
	return get_pointer();
}
```

???
- What's worse, it's really easy to accidentally refactor the function call out
  of the condition.
- Implementing this effectively often relies on seeing the control flow
- And it is the control flow that gets mispredicted

---
name: v1-ex2-m3
template: basic-layout

```cpp
const char *string::get_pointer() const {
  bool is_short = !is_long();
  // ... lots of code ...
* if [[harden_misspeculation(this)]] (is_short)
    return get_short_pointer();
  else
    return get_long_pointer();
}

const char &string::operator[](size_t i) const {
	const char *pointer = get_pointer();
  return pointetr[i];
}

const char *string::data() const {
	return get_pointer();
}
```

???
- This made us start thinking of more language-level constructs. Here, an
  attribute, but not sure what the rgiht approach is.
- Can both change the semantics of the condition expression and the meaning.
- But this is a weird attribute that attaches load sof semantics here.

---
name: v1-ex3-m3
template: basic-layout

```cpp
struct KeyBase {
  virtual sha256 secure_hash() = 0;
private:
  std::vector<std::byte> key_data;
};

struct PublicKey : KeyBase {
  sha256 secure_hash() override {
    return fast_non_constant_time_hash(key_data);
  }
};

struct PrivateKey : KeyBase {
  sha256 secure_hash() override {
    return slow_constant_time_hash(key_data);
  }
};

void do_crypto(KeyBase &key) const {
* auto h = [[harden_misspeculation(key)]] key.secure_hash();
  // ...
}
```

???
- Also has a chance of helping w/ expressions that do an indirect call. Need it
  to be the expression though
-

---
name: questions
template: title-layout

# Questions?

???
-
-

---
name: polls
template: basic-layout

# Semantics / specification polls

- Mumble
- Mumble
- Mumble

---
name: polls2
template: basic-layout

# Syntax polls

- Use magic functions for this?
- Use magic attributes for this?
- Other (probably bad) options:
  - Magic operator, applies to either condition expression or indirect call.
  - Suggestions?

---
name:
template: basic-layout

```cpp

```

???
-
-

---
name:
template: basic-layout

.left-col[
```cpp

```
]
.right-col[
```cpp

```
]

???
-
-

