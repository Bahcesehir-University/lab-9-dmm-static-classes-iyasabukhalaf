// ============================================================
// Lab: Dynamic Memory Management & Static Classes
// Course: Object-Oriented Programming for Engineers
// Level: 2nd Year Engineering
// Duration: 50 minutes
// ============================================================
// This file contains ALL code for this lab.
// Do NOT create any .h files. Everything stays here.
// ============================================================
 
#include <iostream>
#include <string>
#include <cstring>
 
using namespace std;
 
// ================================================================
// CLASS DEFINITIONS
// ================================================================
 
// -------------------------------------------------
// Class: IntArray
// Purpose: A dynamic integer array that manages
//          its own memory using new/delete.
// -------------------------------------------------
class IntArray {
private:
    int* data;       // pointer to dynamically allocated array
    int  capacity;   // maximum number of elements
    int  count;      // current number of elements
 
public:
    // Constructor: allocate array of given capacity
    IntArray(int cap);
 
    // Destructor: free dynamically allocated memory
    ~IntArray();
 
    // Copy Constructor: deep copy another IntArray
    IntArray(const IntArray& other);
 
    // Copy Assignment Operator: deep copy with self-assignment check
    IntArray& operator=(const IntArray& other);
 
    // Add an element to the end. Return true if successful, false if full.
    bool add(int value);
 
    // Get element at index. Return -1 if index is out of bounds.
    int get(int index) const;
 
    // Return current number of elements
    int size() const;
 
    // Return the capacity
    int getCapacity() const;
 
    // Check if the array is empty
    bool isEmpty() const;
 
    // Remove the last element. Return true if successful, false if empty.
    bool removeLast();
};
 
// -------------------------------------------------
// Class: Tracker
// Purpose: A static utility class that counts how
//          many IntArray objects currently exist.
//          Cannot be instantiated.
// -------------------------------------------------
class Tracker {
private:
    static int objectCount;
 
    // Private constructor prevents instantiation
    Tracker() = delete;
 
public:
    // Increment the counter (call from IntArray constructor)
    static void objectCreated();
 
    // Decrement the counter (call from IntArray destructor)
    static void objectDestroyed();
 
    // Return current count of live IntArray objects
    static int getActiveCount();
 
    // Reset counter to zero (for testing purposes)
    static void resetCount();
};
 
// ================================================================
// STATIC MEMBER INITIALIZATION
// ================================================================
 
// TODO 1: Initialize Tracker's static member variable
// Static members live outside any object — they must be defined
// exactly once at file scope, outside the class body.
int Tracker::objectCount = 0;
 
 
// ================================================================
// TRACKER FUNCTION IMPLEMENTATIONS
// ================================================================
 
void Tracker::objectCreated() {
    // TODO 2: Increment objectCount
    objectCount++;
}
 
void Tracker::objectDestroyed() {
    // TODO 3: Decrement objectCount
    objectCount--;
}
 
int Tracker::getActiveCount() {
    // TODO 4: Return objectCount
    return objectCount;
}
 
void Tracker::resetCount() {
    // TODO 5: Reset objectCount to 0
    objectCount = 0;
}
 
// ================================================================
// INTARRAY FUNCTION IMPLEMENTATIONS
// ================================================================
 
// Constructor
IntArray::IntArray(int cap) {
    // TODO 6: Allocate a dynamic array of size cap on the heap,
    //         set capacity and count, then register with Tracker.
    data     = new int[cap];  // heap-allocate the array
    capacity = cap;
    count    = 0;
    Tracker::objectCreated();  // notify the tracker
}
 
// Destructor
IntArray::~IntArray() {
    // TODO 7: Release the heap memory and notify the Tracker.
    // delete[] must match new[] — using plain delete here is UB.
    delete[] data;
    Tracker::objectDestroyed();
}
 
// Copy Constructor
IntArray::IntArray(const IntArray& other) {
    // TODO 8: Deep copy — allocate brand-new memory so the two
    //         objects own separate arrays (no aliasing).
    capacity = other.capacity;
    count    = other.count;
    data     = new int[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = other.data[i];
    }
    Tracker::objectCreated();  // a new object is being born
}
 
// Copy Assignment Operator
IntArray& IntArray::operator=(const IntArray& other) {
    // TODO 9: Copy-assign with self-assignment guard.
    //         Step 1: guard — assigning to yourself is a no-op.
    //         Step 2: free old memory before allocating new memory
    //                 (skipping this leaks the original array).
    //         Step 3: allocate fresh memory and deep-copy.
    //         Step 4: return *this so chains like a = b = c work.
    //         NOTE: no Tracker call — the object count doesn't change.
    if (this != &other) {           // self-assignment check
        delete[] data;              // free the OLD array
        capacity = other.capacity;
        count    = other.count;
        data     = new int[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}
 
// Add element
bool IntArray::add(int value) {
    // TODO 10: Append value if there is room; return false if full.
    if (count < capacity) {
        data[count] = value;
        count++;
        return true;
    }
    return false;
}
 
// Get element at index
int IntArray::get(int index) const {
    // TODO 11: Bounds-check before accessing data[].
    //         -1 is the sentinel for "invalid index".
    if (index >= 0 && index < count) {
        return data[index];
    }
    return -1;
}
 
// Size
int IntArray::size() const {
    // TODO 12: Return the number of elements currently stored.
    return count;
}
 
// Capacity
int IntArray::getCapacity() const {
    // TODO 13: Return the maximum number of elements we can hold.
    return capacity;
}
 
// isEmpty
bool IntArray::isEmpty() const {
    // TODO 14: An array with no elements is empty.
    return count == 0;
}
 
// Remove last element
bool IntArray::removeLast() {
    // TODO 15: Logically remove the last element by decrementing count.
    //         The data is still in memory but is now "out of bounds"
    //         and will be overwritten on the next add().
    if (!isEmpty()) {
        count--;
        return true;
    }
    return false;
}
 
// ================================================================
// MAIN FUNCTION
// ================================================================
 
int main() {
    cout << "=== Dynamic Memory & Static Classes Lab ===" << endl;
    cout << endl;
 
    // Test basic creation
    cout << "[1] Creating IntArray with capacity 5..." << endl;
    IntArray arr(5);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;
    // Expected: 1
 
    // Test adding elements
    cout << "[2] Adding elements: 10, 20, 30" << endl;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    cout << "    Size: " << arr.size() << ", Capacity: " << arr.getCapacity() << endl;
    // Expected: Size: 3, Capacity: 5
 
    // Test get
    cout << "[3] Elements: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr.get(i) << " ";
    }
    cout << endl;
    // Expected: 10 20 30
 
    // Test copy constructor
    cout << "[4] Copy constructing arr2 from arr..." << endl;
    IntArray arr2(arr);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;
    // Expected: 2
    cout << "    arr2 size: " << arr2.size() << endl;
    // Expected: 3
 
    // Test copy assignment
    cout << "[5] Creating arr3(2), then assigning arr to arr3..." << endl;
    IntArray arr3(2);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;
    // Expected: 3
    arr3 = arr;
    cout << "    arr3 size after assignment: " << arr3.size() << endl;
    // Expected: 3
 
    // Test removeLast
    cout << "[6] Removing last from arr..." << endl;
    arr.removeLast();
    cout << "    arr size after removeLast: " << arr.size() << endl;
    // Expected: 2
 
    // Test scope-based destruction
    cout << "[7] Testing scope-based destruction..." << endl;
    {
        IntArray temp(3);
        temp.add(99);
        cout << "    Inside scope - Active objects: " << Tracker::getActiveCount() << endl;
        // Expected: 4 (arr, arr2, arr3, temp)
    }
    // temp's destructor fires here, decrementing the count
    cout << "    After scope  - Active objects: " << Tracker::getActiveCount() << endl;
    // Expected: 3
 
    cout << endl;
    cout << "=== Lab Complete ===" << endl;
    return 0;
}