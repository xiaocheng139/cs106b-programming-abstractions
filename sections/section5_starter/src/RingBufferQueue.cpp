#include "RingBufferQueue.h"
#include "testing/SimpleTest.h"
# include "error.h"

using namespace std;

const int kDefaultCapacity = 5;

/**
 * Initialise the RBQueue
 */
RBQueue::RBQueue() {
    capacity = kDefaultCapacity;
    elements = new int[capacity];
    numItems = 0;
    headIdx = 0;
}

/**
 * Destructor
 */
RBQueue::~RBQueue() {
    delete[] elements;
}

//Enqueues elem if the queue has room; throws an error if queue is full
void RBQueue::enqueue(int elem) {
    if (isFull()) {
        resize();
    }
    int tailIdx = getTailIdx();
    tailIdx = (tailIdx + 1) % capacity;
    elements[tailIdx] = elem;
    numItems++;
}


//Returns and removes the element at the front of the queue; throws a string exception if queue is empty
int RBQueue::dequeue() {
    if (isEmpty()) {
        error("Queue is empty");
    }
    int eleOut = elements[headIdx];
    headIdx = (headIdx + 1) % capacity;
    numItems--;
    return eleOut;
}

//Returns element at the front of the queue; throws a string exception if queue is empty
int RBQueue::peek() const{
    if (isEmpty()) {
        error("Queue is empty");
    }
    return elements[headIdx];
}

//Returns true if queue is empty and false otherwise
bool RBQueue::isEmpty() const{
    return numItems == 0;
}

//Returns true if queue is full and false otherwise
bool RBQueue::isFull() const {
    return numItems == capacity;
}

//Returns number of elements in the queue.
int RBQueue::size() const{
    return numItems;
}

// Returns the index of the tail in the array
int RBQueue::getTailIdx() const {
    return (headIdx + numItems - 1) % capacity;
}

// Expand the capacity
void RBQueue::resize() {
    int* newElements = new int[2 * capacity];
    for (int i = 0; i < capacity; i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity *= 2;
    headIdx = 0;
}

// Opeator overloading - print elements in the queue
ostream& operator<<(ostream& out, const RBQueue& queue) {
    // The following lines are just here to
    // disable compiler warnings and errors.
    // Delete these lines, then implement
    // this method.
    (void) queue;
    return out;
}

/* Provided Tests Below This Line */

PROVIDED_TEST("Simple Example From Handout, No resizing"){
    RBQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQUAL(q.peek(), 1);
    q.enqueue(4);
    q.enqueue(5);
    EXPECT(q.isFull());
    EXPECT_EQUAL(q.dequeue(), 1);
    EXPECT_EQUAL(q.dequeue(), 2);
    EXPECT_EQUAL(q.peek(), 3);
    q.enqueue(6);
    EXPECT_EQUAL(q.dequeue(), 3);
    EXPECT_EQUAL(q.dequeue(), 4);
    EXPECT_EQUAL(q.dequeue(), 5);
    EXPECT_EQUAL(q.dequeue(), 6);
    EXPECT(q.isEmpty());
}

PROVIDED_TEST("Example from Handout, with Resizing"){
    RBQueue q;
    for (int i = 10; i <= 50; i+= 10){
        q.enqueue(i);
    }
    EXPECT(q.isFull());
    // Adding the 6th element should trigger a resizing
    q.enqueue(60);
    EXPECT(!q.isFull());
    for (int i = 10; i <= 60; i += 10){
        EXPECT_EQUAL(i, q.peek());
        EXPECT_EQUAL(i, q.dequeue());
    }
    EXPECT(q.isEmpty());
}
