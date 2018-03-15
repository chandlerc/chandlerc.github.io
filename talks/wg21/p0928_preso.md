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
## Speculative Execution <br> Covert Side-Channel Exploits
.footnote[Chandler Carruth, <chandlerc@gmail.com>, [@chandlerc1024](https://twitter.com/chandlerc1024)]

???
Intro:

---
name: understanding
template: title-layout

# Understanding Spectre variant #1

???

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
- 
- 

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
- 
- 

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
- 
- 

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
- 
- 

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
- 
- 

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
- 
- 

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
- 
- 

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
- 
- 

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
- 
- 

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
- 
- 

---
name: m2 
template: basic-layout

```cpp
;
// Requires: All 'Ts' are integral or pointer types.
// Returns: 'predicate'.
// Remarks: If 'predicate' is false, then any speculative execution in
// which it is treated as true will also treat 'zero_args...' as zero.
template <typename ...Ts>
bool protect_from_speculation(bool predicate, Ts &...zero_args);
```

???
- 
- 

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

if (protect_from_speculation(untrusted_offset < arr1->length,
                             untrusted_offset)) {
  unsigned char value = arr1->data[untrusted_offset];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- 
- 

---
name: v1-ex2-m2
template: basic-layout

```cpp
const char *string::get_pointer() const {
  if (protect_from_speculation(is_long(), this)
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
- 
- 

---
name: v1-ex2-m2b
template: basic-layout

```cpp
const char *string::get_pointer() const {
  bool is_short = !protect_from_speculation(is_long(), this);
  // ... lots of code ...
  if (is_short)
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
- 
- 

---
name: v1-ex2-m3
template: basic-layout

```cpp
const char *string::get_pointer() const {
  bool is_short = !is_long();
  // ... lots of code ...
  if [[harden_misspeculation(this)]] (is_short)
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
- 
- 

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
  sha256 secure_hash() override { return slow_constant_time_hash(key_data); }
};

void do_crypto(KeyBase &key) const {
  auto h = [[harden_misspeculation(key)]] key.secure_hash();
  // ...
}
```

???
- 
- 

---
name: 
template: title-layout

# 

???
- 
- 

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

