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
name: v1-ex1 
template: basic-layout

```cpp
struct array {
  unsigned long length;
  unsigned char data[];
};
array &arr1 = ...; /* small array */
array &arr2 = ...; /* array of size 0x400 */

unsigned long untrusted_offset_from_caller = ...;

if (untrusted_offset_from_caller < arr1->length) {
  unsigned char value = arr1->data[untrusted_offset_from_caller];
  unsigned long index2 = ((value & 1) * 0x100) + 0x200;
  unsigned char value2 = arr2->data[index2];
  // ... doesn't matter what else
}
```

???
- 
- 

---
name: v1-ex2 
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

