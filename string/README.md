***Custom MyString container built using concepts of STL strng***

---

**Invariants**

Capacity is always bigger than size of the underlying array.
Capacity must always consider size for null ('\0') terminator

Underlying m_data array is never a nullptr

Last item of the m_data is always null ('\0') terminator

---

**Capacity growth**

When size is about to exceed the capacity of the array capacity gets multiplied by two

**Time complexities**

push_back() - Amortized O(1). In some cases when array is full the container will double its size by allocating new
array. All other cases are O(1).

pop() - O(1)

All constructors are in O(n)

Operator += - O(n)

Operators ==, != - Best Case - O(1), Worst Case - O(n)

reverse() - Best Case - O(1), Worst Case - O(n)

resize() - Best Case - O(1), Worst Case - O(n)

shrink_to_fit() - Best Case - O(1), Worst Case - O(n)


