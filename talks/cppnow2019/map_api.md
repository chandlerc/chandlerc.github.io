name: title-layout
layout: true
class: left, middle, title

---
name: basic-layout
layout: true
class: left, top

---
name: img-layout
layout: true
class: center, middle, image

---
name: title
template: title-layout

# A clean and minimal map API

.footnote[Chandler Carruth, <chandlerc@gmail.com>, [@chandlerc1024](https://twitter.com/chandlerc1024)]

--
name: title
template: title-layout
count: false

???

---
name: wharrgarbl
template: img-layout

![This talk is going to be ... a lot of code](talk_speed.jpg)

???

---
name: core-api
template: title-layout

# Four fundamental APIs

???

...

---
name: core-api-code
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: lookup-api
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
* auto lookup(const KeyT &Key) const -> LookupKVResult;

  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: lookup-api-return
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> `LookupKVResult`;

  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: lookup-result
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class LookupKVResult {
  public:
    explicit operator bool() const { return Key != nullptr; }

    KeyT &getKey() const { return *Key; }
    ValueT &getValue() const { return *Value; }

  private:
    KeyT *Key = nullptr;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: lookup-result-bool
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class LookupKVResult {
  public:
*   explicit operator bool() const { return Key != nullptr; }

    KeyT &getKey() const { return *Key; }
    ValueT &getValue() const { return *Value; }

  private:
    KeyT *Key = nullptr;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: lookup-result-key
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class LookupKVResult {
  public:
    explicit operator bool() const { return Key != nullptr; }

*   KeyT &getKey() const { return *Key; }
    ValueT &getValue() const { return *Value; }

  private:
    KeyT *Key = nullptr;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: lookup-result-value
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class LookupKVResult {
  public:
    explicit operator bool() const { return Key != nullptr; }

    KeyT &getKey() const { return *Key; }
*   ValueT &getValue() const { return *Value; }

  private:
    KeyT *Key = nullptr;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: insert-api
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

* auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: insert-api-return
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  auto insert(const KeyT &Key, ValueT Value) -> `InsertKVResult`;

  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: insert-result
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class InsertKVResult {
  public:
    bool isInserted() const { return KeyAndInserted.getInt(); }

    KeyT &getKey() const { return *KeyAndInserted.getPointer(); }
    ValueT &getValue() const { return *Value; }

  private:
    PointerIntPair<KeyT *, 1, bool> KeyAndInserted;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: insert-result-isinserted
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class InsertKVResult {
  public:
*   bool isInserted() const { return KeyAndInserted.getInt(); }

    KeyT &getKey() const { return *KeyAndInserted.getPointer(); }
    ValueT &getValue() const { return *Value; }

  private:
    PointerIntPair<KeyT *, 1, bool> KeyAndInserted;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: insert-result-key
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class InsertKVResult {
  public:
    bool isInserted() const { return KeyAndInserted.getInt(); }

*   KeyT &getKey() const { return *KeyAndInserted.getPointer(); }
    ValueT &getValue() const { return *Value; }

  private:
    PointerIntPair<KeyT *, 1, bool> KeyAndInserted;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: insert-result-value
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class InsertKVResult {
  public:
    bool isInserted() const { return KeyAndInserted.getInt(); }

    KeyT &getKey() const { return *KeyAndInserted.getPointer(); }
*   ValueT &getValue() const { return *Value; }

  private:
    PointerIntPair<KeyT *, 1, bool> KeyAndInserted;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: insert-result-pointerintpair
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class InsertKVResult {
  public:
    bool isInserted() const { return KeyAndInserted.getInt(); }

    KeyT &getKey() const { return *KeyAndInserted.getPointer(); }
    ValueT &getValue() const { return *Value; }

  private:
*   PointerIntPair<KeyT *, 1, bool> KeyAndInserted;
    ValueT *Value;
  };

  // ...
};
```

???

---
name: update-api
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

* auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: update-api-return
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto update(const KeyT &Key, ValueT Value) -> `InsertKVResult`;

  auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: remove-api
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

* auto remove(const KeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: remove-api-return
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;

  auto remove(const KeyT &Key) -> `RemoveKVResult`;

  // ...
};
```

???

---
name: remove-result
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class RemoveKVResult {
  public:
    explicit operator bool() const { return RemovedKey; }

    KeyT &getKey() { return *RemovedKey; }
    ValueT &getValue() { return *RemovedValue; }

    KeyT takeKey() { return *std::move(RemovedKey); }
    ValueT takeValue() { return *std::move(RemovedValue); }

  private:
    std::optional<KeyT> RemovedKey;
    std::optional<ValueT> RemovedValue;
  };

  // ...
};
```

???

---
name: remove-result-bool
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class RemoveKVResult {
  public:
*   explicit operator bool() const { return RemovedKey; }

    KeyT &getKey() { return *RemovedKey; }
    ValueT &getValue() { return *RemovedValue; }

    KeyT takeKey() { return *std::move(RemovedKey); }
    ValueT takeValue() { return *std::move(RemovedValue); }

  private:
    std::optional<KeyT> RemovedKey;
    std::optional<ValueT> RemovedValue;
  };

  // ...
};
```

???

---
name: remove-result-key
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class RemoveKVResult {
  public:
    explicit operator bool() const { return RemovedKey; }

*   KeyT &getKey() { return *RemovedKey; }
    ValueT &getValue() { return *RemovedValue; }

    KeyT takeKey() { return *std::move(RemovedKey); }
    ValueT takeValue() { return *std::move(RemovedValue); }

  private:
    std::optional<KeyT> RemovedKey;
    std::optional<ValueT> RemovedValue;
  };

  // ...
};
```

???

---
name: remove-result-value
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class RemoveKVResult {
  public:
    explicit operator bool() const { return RemovedKey; }

    KeyT &getKey() { return *RemovedKey; }
*   ValueT &getValue() { return *RemovedValue; }

    KeyT takeKey() { return *std::move(RemovedKey); }
    ValueT takeValue() { return *std::move(RemovedValue); }

  private:
    std::optional<KeyT> RemovedKey;
    std::optional<ValueT> RemovedValue;
  };

  // ...
};
```

???

---
name: remove-result-take
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  class RemoveKVResult {
  public:
    explicit operator bool() const { return RemovedKey; }

    KeyT &getKey() { return *RemovedKey; }
    ValueT &getValue() { return *RemovedValue; }

*   KeyT takeKey() { return *std::move(RemovedKey); }
*   ValueT takeValue() { return *std::move(RemovedValue); }

  private:
    std::optional<KeyT> RemovedKey;
    std::optional<ValueT> RemovedValue;
  };

  // ...
};
```

???

---
name: deeper1
template: title-layout

# We've just scratched the surface...

???

---
name: deeper1-meme
template: img-layout

![Should we go deeper?](should_we_go_deeper.jpg)

???

---
name: secondary-api
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  auto operator[](const KeyT &Key) const -> Value *;

  auto contains(const KeyT &Key) const -> bool;

  auto begin() -> ...;
  auto end() -> ...;

  // ...
};
```

???

---
name: square-brackets
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

* auto operator[](const KeyT &Key) const -> Value *;

  auto contains(const KeyT &Key) const -> bool;

  auto begin() -> ...;
  auto end() -> ...;

  // ...
};
```

???

---
name: square-brackets-pointer
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  auto operator[](const KeyT &Key) const -> `Value *`;

  auto contains(const KeyT &Key) const -> bool;

  auto begin() -> ...;
  auto end() -> ...;

  // ...
};
```

???

---
name: contains
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  auto operator[](const KeyT &Key) const -> Value *;

* auto contains(const KeyT &Key) const -> bool;

  auto begin() -> ...;
  auto end() -> ...;

  // ...
};
```

???

---
name: range
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...

  auto operator[](const KeyT &Key) const -> Value *;

  auto contains(const KeyT &Key) const -> bool;

* auto begin() -> ...;
* auto end() -> ...;

  // ...
};
```

???

---
name: heterogenous-lookup
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
* template <typename OtherKeyT>
  auto lookup(const OtherKeyT &Key) -> LookupKVResult;

* template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key, ValueT Value) -> InsertKVResult;

* template <typename OtherKeyT>
  auto update(const OtherKeyT &Key, ValueT Value) -> InsertKVResult;

* template <typename OtherKeyT>
  auto remove(const OtherKeyT &Key) -> RemoveKVResult;

  // ...
};
```

???

---
name: lazy-value
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<ValueT()> LazyValue) -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<ValueT()> LazyValue) -> InsertKVResult;

  // ...
};
```

???

---
name: lazy-value-erased
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              `function_ref`<ValueT()> LazyValue) -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<ValueT()> LazyValue) -> InsertKVResult;

  // ...
};
```

???

---
name: lazy-value-closure
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<`ValueT()`> LazyValue) -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<ValueT()> LazyValue) -> InsertKVResult;

  // ...
};
```

???

---
name: inplace-value
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(ValueT *ValueStorage)> ValueCreator)
      -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<void(ValueT *ValueStorage)> ValueCreator)
      -> InsertKVResult;

  // ...
};
```

???

---
name: inplace-value-signature
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<`void(ValueT *ValueStorage)`> ValueCreator)
      -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<void(ValueT *ValueStorage)> ValueCreator)
      -> InsertKVResult;

  // ...
};
```

???

---
name: inplace-value-ex
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(ValueT *ValueStorage)> ValueCreator)
      -> InsertKVResult;

  // ...
};

void f(Map<std::string, BigComplexType> &big_map) {
  auto Result =
      big_map.insert("something-new",
                     [](BigComplexType *Storage) {
                       new (Storage) BigComplexType(...);
                     });
  // ...
```

???

---
name: inplace-value-ex-new
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(ValueT *ValueStorage)> ValueCreator)
      -> InsertKVResult;

  // ...
};

void f(Map<std::string, BigComplexType> &big_map) {
  auto Result =
      big_map.insert("something-new",
                     [](BigComplexType *Storage) {
*                      new (Storage) BigComplexType(...);
                     });
  // ...
```

???

---
name: inplace-both
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  // ...
};
```

???

---
name: inplace-both-key
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(`KeyT *KeyStorage`,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  // ...
};
```

???

---
name: inplace-both-value
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                `ValueT *ValueStorage`)> KVCreator)
      -> InsertKVResult;

  template <typename OtherKeyT>
  auto update(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  // ...
};
```

???

---
name: inplace-both-ex
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  // ...
};

void f(std::string_view Name, Map<std::string, BigComplexType> &big_map) {
  auto Result =
      big_map.insert(Name,
                     [Name](std::string *KeyStorage,
                            BigComplexType *ValueStorage) {
                       new (KeyStorage) std::string(Name);
                       new (ValueStorage) BigComplexType(...);
                     });
  // ...
```

???

---
name: inplace-both-ex-capture
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  // ...
};

void f(std::string_view Name, Map<std::string, BigComplexType> &big_map) {
  auto Result =
      big_map.insert(Name,
                     [`Name`](std::string *KeyStorage,
                            BigComplexType *ValueStorage) {
                       new (KeyStorage) std::string(Name);
                       new (ValueStorage) BigComplexType(...);
                     });
  // ...
```

???

---
name: inplace-both-ex-new
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, ...>
class Map {
public:
  // ...
  template <typename OtherKeyT>
  auto insert(const OtherKeyT &Key,
              function_ref<void(KeyT *KeyStorage,
                                ValueT *ValueStorage)> KVCreator)
      -> InsertKVResult;

  // ...
};

void f(std::string_view Name, Map<std::string, BigComplexType> &big_map) {
  auto Result =
      big_map.insert(Name,
                     [Name](std::string *KeyStorage,
                            BigComplexType *ValueStorage) {
*                      new (KeyStorage) std::string(Name);
*                      new (ValueStorage) BigComplexType(...);
                     });
  // ...
```

???

---
name: deeper2-meme
template: img-layout

![Should we go even deeper?](should_we_go_even_deeper.png)

???

---
name: small-size
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, int SmallSize>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;
  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto remove(const KeyT &Key) -> RemoveKVResult;

private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
};
```

???

---
name: small-size-hl
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, `int SmallSize`>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;
  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto remove(const KeyT &Key) -> RemoveKVResult;

private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
};
```

???

---
name: small-size-buffer-ptr
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, int SmallSize>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;
  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto remove(const KeyT &Key) -> RemoveKVResult;

private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
*   void *BufferPtr;
    ... SmallBuffer;
  };
};
```

???

---
name: small-size-small-buffer
template: basic-layout

```cpp
template <typename KeyT, typename ValueT, int SmallSize>
class Map {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;
  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto remove(const KeyT &Key) -> RemoveKVResult;

private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
*   ... SmallBuffer;
  };
};
```

???

---
name: map-ref
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapRef {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;
  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto remove(const KeyT &Key) -> RemoveKVResult;

private:
  Map::DataMembers *Data;
  int SmallSize;
  void **BufferPtrOrSmallBuffer;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
public:
  explicit operator MapRef<KeyT, ValueT>();

  // ...
```

???

---
name: map-ref-conv
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapRef {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;
  auto insert(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto update(const KeyT &Key, ValueT Value) -> InsertKVResult;
  auto remove(const KeyT &Key) -> RemoveKVResult;

private:
  Map::DataMembers *Data;
  int SmallSize;
  void **BufferPtrOrSmallBuffer;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
public:
* explicit operator MapRef<KeyT, ValueT>();

  // ...
```

???

---
name: map-ref-data
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapRef {
private:
  Map::DataMembers *Data;
  int SmallSize;
  void **BufferPtrOrSmallBuffer;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
};
```

???

---
name: map-ref-data-members
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapRef {
private:
* Map::DataMembers *Data;
  int SmallSize;
  void **BufferPtrOrSmallBuffer;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
* DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
};
```

???

---
name: map-ref-small-size
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapRef {
private:
  Map::DataMembers *Data;
* int SmallSize;
  void **BufferPtrOrSmallBuffer;
};

template <typename KeyT, typename ValueT, `int SmallSize`>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
};
```

???

---
name: map-ref-buffer-ptr
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapRef {
private:
  Map::DataMembers *Data;
  int SmallSize;
* void **BufferPtrOrSmallBuffer;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
*   void *BufferPtr;
*   ... SmallBuffer;
  };
};
```

???

---
name: map-view
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapView {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  // ...
};

template <typename KeyT, typename ValueT>
class MapRef {
public:
  explicit operator MapView<KeyT, ValueT>() const;

  // ... 
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
public:
  explicit operator MapView<KeyT, ValueT>() const;

  // ...
```

???

---
name: map-view-hl
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapView {
public:
  auto lookup(const KeyT &Key) const -> LookupKVResult;

  // ...
};

template <typename KeyT, typename ValueT>
class MapRef {
public:
* explicit operator MapView<KeyT, ValueT>() const;

  // ... 
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
public:
* explicit operator MapView<KeyT, ValueT>() const;

  // ...
```

???

---
name: map-view
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapView {
private:
  int Size;
  int SmallSize;
  int Entropy;
  void *Data;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
```

???

---
name: map-view-size
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapView {
private:
* int Size;
  int SmallSize;
  int Entropy;
  void *Data;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
private:
  struct DataMembers {
    int `Size`, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
```

???

---
name: map-view-small-size
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapView {
private:
  int Size;
* int SmallSize;
  int Entropy;
  void *Data;
};

template <typename KeyT, typename ValueT, `int SmallSize`>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
```

???

---
name: map-view-entropy
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapView {
private:
  int Size;
  int SmallSize;
* int Entropy;
  void *Data;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, `Entropy`;
  };
  DataMembers Data;
  union {
    void *BufferPtr;
    ... SmallBuffer;
  };
```

???

---
name: map-view-data
template: basic-layout

```cpp
template <typename KeyT, typename ValueT>
class MapView {
private:
  int Size;
  int SmallSize;
  int Entropy;
* void *Data;
};

template <typename KeyT, typename ValueT, int SmallSize>
class Map {
private:
  struct DataMembers {
    int Size, GrowthBudget, Entropy;
  };
  DataMembers Data;
  union {
*   void *BufferPtr;
*   ... SmallBuffer;
  };
```

???

---
name: fine-meme
template: img-layout

![And we have a clean and minimal map API!](api_minions.gif)

???

---
name: credits
template: basic-layout
class: bottom, right

Thanks to Hana and Jeff for their photoshop assistance.

Thanks to Hana, Jeff, and Michael for review and feedback.

???

---
count: false
