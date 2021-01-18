// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
using namespace std;

struct Patient {
    string patienName;
    int timeStamp;
    int priority;
};

class VectorPatientQueue : public PatientQueue {
public:
    VectorPatientQueue();
    ~VectorPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    Patient* patients;
    int capacity;
    int numPatients;
    int timeCount;

    void resize();
};
