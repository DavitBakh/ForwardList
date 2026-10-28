# 🔗 ForwardList — Custom STL-Compatible Singly Linked List in C++

![C++20](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)
![Type](https://img.shields.io/badge/Type-Singly%20Linked%20List%20%7C%20STL--like-green.svg)
![Coursework](https://img.shields.io/badge/University-Data%20Structures%20Course-orange.svg)
![Tests](https://img.shields.io/badge/Tests-TDD%20(19%20Suites)-brightgreen.svg)

A university coursework project for the **Data Structures and Algorithms** course. This repository provides an object-oriented implementation of a singly linked list (`ForwardList<T>`), matching the design, interface, and performance characteristics of `std::forward_list` from the C++ Standard Template Library (STL).

---

## 📌 Architectural Highlights

### 1. Minimal Node Overhead
Each list node is encapsulated in a lightweight internal structure:
```cpp
struct Node {
    T _val;
    Node* _next;
    Node(const T& val, Node* next = nullptr);
};
```
The list tracks a single `_head` pointer, achieving minimal per-element storage overhead (only one `_next` pointer per node).

### 2. Pointer-to-Pointer Idiom (`Node**`)
List creation, deep copying, and assignment utilize the clean double-pointer pattern:
```cpp
Node** curNode = &_head;
while (sourceNode != nullptr) {
    *curNode = new Node(sourceNode->_val);
    curNode = &(*curNode)->_next;
    sourceNode = sourceNode->_next;
}
```
This idiom eliminates repetitive `if (_head == nullptr)` checks and provides unified pointer manipulation for both head insertion and regular iteration.

### 3. STL-Compliant Forward Iterators
The container features fully functional `iterator` and `const_iterator` inner classes:
- Category tag: `iterator_category = std::forward_iterator_tag`.
- Standard traits exported: `value_type`, `difference_type`, `pointer`, `reference`.
- Operators implemented: dereference `*it`, member selection `it->member`, pre/post increment `++it` / `it++`, equality comparisons `==` and `!=`.
- Seamless interoperability and conversion between `iterator` and `const_iterator`.
- Full compatibility with standard algorithms from `<algorithm>` (`std::find`, `std::count`, `std::distance`, etc.).

### 4. In-Place Emplacement (`emplace_front`)
- `emplace_front(Args&&... args)` uses perfect forwarding (`std::forward`) to construct objects directly at the front of the list.

---

## 📁 Repository Structure

```text
ForwardList/
├── ForwardList.sln                  # Visual Studio 2022 Solution
├── .gitignore                       # Git ignores for build artifacts
│
└── ForwardList/
    ├── ForwardList.h                # Singly linked list template declaration & implementation
    ├── main.cpp                     # Test execution entry point
    ├── ForwardList.vcxproj          # MSVC Project file
    │
    └── Tests/                       # 19 Modular TDD Test Suites
        ├── 1BasicConstructorsTest.h
        ├── 2PushFrontTest.h
        ├── 3PopFrontTest.h
        ├── 4DestructorCallTest.h
        ├── 5CopyConstructorTest.h
        ├── 6AssignmentOperatorTest.h
        ├── 7DestructorWithAssignmentTest.h
        ├── 8EmplaceFrontTest.h
        ├── 9FrontTest.h
        ├── 10ClearTest.h
        ├── 11BasicIteratorTest.h
        ├── 12ConstIteratorTest.h
        ├── 13MemberAccessIteratorTest.h
        ├── 14InitializerListConstructorTest.h
        ├── 15IteratorConstructibleTest.h
        ├── 16ClassWithNoDefaultConstructorTest.h
        ├── 17InsertTest.h
        ├── 18EraseTest.h
        ├── 19StlCompatibilityTest.h
        └── Fixtures/                # CustomAsserts test helpers
```

---

## 📋 Method Reference & Complexity

| Method | Signature | Time Complexity | Description |
| :--- | :--- | :--- | :--- |
| `push_front` | `void push_front(const T& val)` | `O(1)` | Prepends a new element to the head |
| `emplace_front` | `void emplace_front(Args&&... args)` | `O(1)` | Constructs element in place at the head |
| `pop_front` | `void pop_front() noexcept` | `O(1)` | Removes the head node and deallocates memory |
| `front` | `T& front()`, `const T& front() const` | `O(1)` | Direct reference to the first element |
| `empty` | `bool empty() const` | `O(1)` | Checks whether the list is empty (`_head == nullptr`) |
| `clear` | `void clear()` | `O(N)` | Destroys all nodes and deallocates memory |
| `begin` / `end` | `iterator begin()`, `iterator end()` | `O(1)` | Returns forward iterators to beginning and end |
| `operator=` | `ForwardList& operator=(const ForwardList&)` | `O(N)` | Deep copy assignment with prior cleanup |
| `operator==` | `bool operator==(const ForwardList&, ...)` | `O(N)` | Element-by-element equality comparison |

---

## 🧪 Unit Testing (TDD)

The implementation passes **19 test suites**:
1. Default, sized, and filled constructors.
2. `push_front` sequencing.
3. `pop_front` head removal and pointer updates.
4. **Destructor tracker**: guarantees zero memory leaks upon destruction.
5. Deep copy constructor verification.
6. Copy assignment operator.
7. Proper destruction during reassignment.
8. Variadic `emplace_front`.
9. `front()` member access in const and non-const contexts.
10. Complete deallocation via `clear()`.
11. Standard iterator operators (`*it`, `++it`, `it++`, `==`, `!=`).
12. `const_iterator` access control.
13. Member access via `it->field`.
14. Initializer list construction (`std::initializer_list<T>`).
15. Range-based iterator construction.
16. Handling types with no default constructor.
17. Element insertion.
18. Element erasure.
19. **Standard library algorithm compatibility** (`std::find`, `std::count`, `std::distance`).

---

## ⚙️ Build and Execution

1. Open `ForwardList.sln` in **Visual Studio 2022**.
2. Set configuration to **Debug / x64** or **Release / x64**.
3. Compile and execute tests (`Ctrl + F5`).
4. Output when all suites pass:
   ```text
   All tests passed!
   ```

---

## 👨‍💻 Author

- **Davit Bakhshyan ([DavitBakh](https://github.com/DavitBakh))**
