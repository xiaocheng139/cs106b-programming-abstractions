// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"
using namespace std;

class LinkedListPatientQueue : public PatientQueue {
public:
    LinkedListPatientQueue();
    ~LinkedListPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    PatientNode* root;
    int numPatients;

    void freeMemory();

};
