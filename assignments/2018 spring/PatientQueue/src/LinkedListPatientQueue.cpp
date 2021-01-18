// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"
#include "error.h"
#include <string>
#include <sstream>

LinkedListPatientQueue::LinkedListPatientQueue() {
    root = nullptr;
    numPatients = 0;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    freeMemory();
}

void LinkedListPatientQueue::clear() {
    freeMemory();
    numPatients = 0;
    root = nullptr;
}

void LinkedListPatientQueue::freeMemory() {
    while (root != nullptr) {
        PatientNode* temp = root->next;
        delete root;
        root = temp;
    }
}

string LinkedListPatientQueue::frontName() {
    if (root == nullptr) {
        error("Empty priority queue");
    }
    return root->name;
}

int LinkedListPatientQueue::frontPriority() {
    if (root == nullptr) {
        error("Empty priority queue");
    }
    return root->priority;
}

bool LinkedListPatientQueue::isEmpty() {
    return numPatients == 0;
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    PatientNode* prev = nullptr;
    PatientNode* cur = root;
    PatientNode* newPatient = new PatientNode(name, priority, nullptr);

    if (root == nullptr) {
        root = newPatient;
    } else {
        while (cur != nullptr) {
            if (prev == nullptr && cur->priority > priority) {
                newPatient->next = cur;
                root = newPatient;
                return;
            } else if (prev != nullptr && prev->priority <= priority && cur->priority > priority) {
                prev->next = newPatient;
                newPatient->next = cur;
                return;
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
    }
    numPatients++;
}

string LinkedListPatientQueue::processPatient() {
    if (root == nullptr) {
        error("Empty priority queue");
    }
    string patientName = root->name;
    PatientNode* next = root->next;
    delete root;
    root = next;
    numPatients--;
    return patientName;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    PatientNode* cur = root;
    while (cur != nullptr) {
        if (cur->name == name) {
            cur->priority = newPriority;
            return;
        }
        cur = cur->next;
    }
    error("This patient is found in the queue");
}

string LinkedListPatientQueue::toString() {
    std::stringstream buffer;
    buffer << "{";
    PatientNode* cur = root;
    while (cur != nullptr) {
        buffer << cur->priority << ":" << cur->name;
        cur = cur->next;
        if (cur != nullptr) {
            buffer << ", " ;
        }
    }
    buffer << "}" <<endl;
    return buffer.str();
}
