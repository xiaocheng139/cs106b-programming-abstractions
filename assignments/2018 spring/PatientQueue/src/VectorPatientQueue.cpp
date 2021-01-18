// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "VectorPatientQueue.h"
#include <string>
#include <sstream>
#include "error.h"

const int INIT_CAPACITY = 3;

// Initialize a new empty queue
VectorPatientQueue::VectorPatientQueue() {
    capacity = INIT_CAPACITY;
    patients = new Patient[capacity];
    numPatients = 0;
    timeCount = 0;
}

// Free up any memory
VectorPatientQueue::~VectorPatientQueue() {
    delete[] patients;
}

// Remove all elements from the patient queue, freeing memory for all nodes that are removed.
void VectorPatientQueue::clear() {
    delete[] patients;
    patients = nullptr;
    numPatients = 0;
}

// Return the name of the most urgent patient (the person in the front of your patient queue)
string VectorPatientQueue::frontName() {
    if (isEmpty()) {
        error("No patient in the queue");
    }

    Patient target = patients[0];

    for (int i = 1; i < numPatients; i++) {
        if (patients[i].priority < target.priority) {
            target = patients[i];
        } else if (patients[i].priority == target.priority && patients[i].timeStamp < target.timeStamp) {
            target = patients[i];
        }
    }

    return target.patienName;
}

// Return the name of the most urgent patient (the person in the front of your patient queue
int VectorPatientQueue::frontPriority() {
    if (isEmpty()) {
        error("No patient in the queue");
    }
    int mostUrgent = patients[0].priority;

    for (int i = 1; i < numPatients; i++) {
        if (patients[i].priority < mostUrgent) {
            mostUrgent = patients[i].priority;
        }
    }

    return mostUrgent;
}

// Return true if your patient queue does not contain any elements and false if it does contain at least one patient
bool VectorPatientQueue::isEmpty() {
    return numPatients == 0;
}

// Add/enqueue the given person into your patient queue with the given priority
void VectorPatientQueue::newPatient(string name, int priority) {
    if (numPatients == capacity) {
        resize();
    }
    Patient* newPatient = new Patient();
    newPatient->patienName = name;
    newPatient->priority = priority;
    newPatient->timeStamp = timeCount += 1;

    patients[numPatients] = *newPatient;
    numPatients++;
}
// Remove/dequeue the patient with the most urgent priority from your queue
string VectorPatientQueue::processPatient() {
    if (isEmpty()) {
        error("No patient in the queue");
    }
    int targetIdx = 0;

    for (int i = 1; i < numPatients; i++) {
        if (patients[i].priority < patients[targetIdx].priority) {
            targetIdx = i;
        } else if (patients[i].priority == patients[targetIdx].priority && patients[i].timeStamp < patients[targetIdx].timeStamp) {
            targetIdx = i;
        }
    }
    string patientName = patients[targetIdx].patienName;

    for (int j = targetIdx; j < numPatients - 1; j++) {
        patients[j] = patients[j + 1];
    }
    numPatients -= 1;
    return patientName;
}

// Modify the priority of a given existing patient in the queue.
void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    bool found = false;
    int mostUrgent;
    int targertIdx;

    for (int i = 0; i < numPatients; i++) {
        if (patients[i].patienName == name) {
            found = true;
            if (patients[i].priority <= mostUrgent) {
                mostUrgent = patients[i].priority;
                targertIdx = i;
            }
        }
    }
    if (found == false) {
        error("Patient not found");
    }
    patients[targertIdx].priority = newPriority;
    patients[targertIdx].timeStamp = timeCount += 1;
}

// Print patient queue to the console
string VectorPatientQueue::toString() {
    std::stringstream buffer;
    buffer << "{";
    for (int i = 0; i < numPatients; i++) {
        buffer << patients[i].priority << ":" << patients[i].patienName << "T: " << patients[i].timeStamp;
        if (i != numPatients - 1) {
            buffer << ", ";
        }
    }
    buffer << "}" <<endl;
    return buffer.str();
}

// Double the array size
void VectorPatientQueue::resize() {
    Patient* newPatients = new Patient[capacity * 2];
    for (int i = 0; i < numPatients; i++) {
        newPatients[i] = patients[i];
    }
    delete[] patients;
    patients = newPatients;
    capacity *= 2;
}
