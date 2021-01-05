#include "RingBufferQueue.h"
#include "error.h"
#include "testing/SimpleTest.h"

using namespace std;
const int INITIAL_LENGTH = 5;

/**
 * Initialise the RBQueue
 */
RBQueue::RBQueue() {
    capacity = INITIAL_LENGTH;
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
        error("Queue is full!");
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
bool RBQueue::isFull() const{
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

// Opeator overloading - print elements in the queue
ostream& operator<<(ostream& out, const RBQueue& queue) {
    out << "{";
    if (!queue.isEmpty()) {
        queue.elements[queue.headIdx];
        for (int i = 1; i < queue.size(); i++) {
            int index = (i + queue.headIdx) / queue.capacity;
            out << queue.elements[index];
        }
    }
    out << "}";
    return out;
}

/* Provided Tests Below This Line */

PROVIDED_TEST("Simple Example From Handout"){
    RBQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQUAL(q.peek(), 1);
    q.enqueue(4);
    q.enqueue(5);
    EXPECT(q.isFull()); // The test provided is wrong. The queue should be full
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
