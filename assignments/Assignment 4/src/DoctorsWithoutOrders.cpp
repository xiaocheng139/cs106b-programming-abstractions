#include "DoctorsWithoutOrders.h"
#include "Testing/DoctorsWithoutOrdersTests.h"
using namespace std;

bool canAllPatientsBeSeenHelper(HashMap<string, int>& doctors,HashMap<string, int>& patients, HashMap<string, HashSet<string>>& schedule);

// Check whether there is a solution that all patients can be treated
bool canAllPatientsBeSeen( const HashMap<string, int>& doctors,
                           const HashMap<string, int>& patients,
                          HashMap<string, HashSet<string>>& schedule) {
    HashMap<string, int> newDoctors = doctors;
    HashMap<string, int> newPatients = patients;

    return canAllPatientsBeSeenHelper(newDoctors, newPatients, schedule);
}

bool canAllPatientsBeSeenHelper(HashMap<string, int>& doctors,HashMap<string, int>& patients, HashMap<string, HashSet<string>>& schedule) {
    if (patients.isEmpty()) {
        return true;
    }
    string patient = patients.front();
    int patientTime = patients[patient];

    for (string doctor: doctors.keys()) {
        if (doctors[doctor] >= patients[patient]) {
            doctors[doctor] -= patientTime;
            patients.remove(patient);
            schedule[doctor].add(patient);

            if (canAllPatientsBeSeen(doctors, patients, schedule)) {
                return true;
            }

            doctors[doctor] += patientTime;
            patients.add(patient, patientTime);
            schedule[doctor].remove(patient);
        }
    }
    return false;
}



/* * * * * * Test Cases Below This Point * * * * * */

ADD_TEST("Custom Test: example test.") {
    HashMap<string, int> doctors;
    doctors["Thomas"] = 10;
    doctors["Taussig"] = 8;
    doctors["Sacks"] = 8;
    doctors["Ofri"] = 8;

    HashMap<string, int> patients;
    patients["Lacks"] = 2;
    patients["Gage"] = 3;
    patients["Molaison"] = 4;
    patients["Writebol"] = 3;
    patients["St. Martin"] = 1;
    patients["Washkansky"] = 6;
    patients["Sandoval"] = 8;
    patients["Giese"] = 6;

    HashMap<string, HashSet<string>> schedule;
    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));
}













/* * * * * Provided Tests Below This Point * * * * */

ADD_TEST("Provided Test: Can't schedule if a patient requires more hours than any doctor has.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Zhivago", 8 },
        { "Dr. Strange", 8 },
        { "Dr. Horrible", 8 },
    };
    HashMap<string, int> patients = {
        { "You Poor Soul", 9 },  // Needs more time than any one doctor can provide
    };

    EXPECT(!canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Can schedule if doctor has way more time than patient needs.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Wheelock", 12 },
    };
    HashMap<string, int> patients = {
        { "Lucky Patient", 8 },
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Can schedule if there's one doctor and one patient with the same hours.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Wheelock", 8 },
    };
    HashMap<string, int> patients = {
        { "Lucky Patient", 8 },
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Schedule for one doctor and one patient is correct.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Wheelock", 8 },
    };
    HashMap<string, int> patients = {
        { "Lucky Patient", 8 },
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));

    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Dr. Wheelock", { "Lucky Patient" } }
    };
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Single doctor can see many patients.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. House", 7 },
    };
    HashMap<string, int> patients = {
        { "Patient A", 4 },
        { "Patient B", 2 },
        { "Patient C", 1 }
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));

    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Dr. House", { "Patient A", "Patient B", "Patient C" } }
    };
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Multiple doctors can see multiple patients.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. House", 7  },
        { "AutoDoc",   70 }
    };
    HashMap<string, int> patients = {
        { "Patient A", 4  },
        { "Patient B", 2  },
        { "Patient C", 1  },
        { "Patient D", 40 },
        { "Patient E", 20 },
        { "Patient F", 10 }
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));

    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Dr. House", { "Patient A", "Patient B", "Patient C" } },
        { "AutoDoc",   { "Patient D", "Patient E", "Patient F" } },
    };
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Doesn't necessarily assign neediest patient to most available doctor.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Doctor Workaholic", 10 },
        { "Doctor Average",    8 },
        { "Doctor Lazy",       6 },
    };
    HashMap<string, int> patients = {
        { "Patient EightHour", 8 },
        { "Patient SixHour",   6 },
        { "Patient FiveHour1", 5 },
        { "Patient FiveHour2", 5 }
    };

    /* You can't make this work if you assign Patient EightHour to Doctor Workaholic.
     * The only way for this setup to work is if you give the two five-hour patients
     * to Doctor Workaholic.
     */
    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Doctor Workaholic", { "Patient FiveHour1", "Patient FiveHour2" } },
        { "Doctor Average",    { "Patient EightHour" } },
        { "Doctor Lazy",       { "Patient SixHour" } }
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Can't schedule patients if there are no doctors.") {
    HashMap<string, int> patients = {
        { "You Poor Soul", 8 },
    };
    HashMap<string, HashSet<string>> schedule;
    EXPECT(!canAllPatientsBeSeen({}, patients, schedule));
}

ADD_TEST("Provided Test: Agreement in total hours doesn't mean a schedule exists (1).") {
    HashMap<string, int> doctors = {
        { "Doctor A", 3 },
        { "Doctor B", 3 },
    };
    HashMap<string, int> patients = {
        { "Patient X", 2 },
        { "Patient Y", 2 },
        { "Patient Z", 2 },
    };

    /* Notice the the total hours free (6) matches the total hours needed (6), but it's set
     * up in a way where things don't align properly.
     */
    HashMap<string, HashSet<string>> schedule;
    EXPECT(!canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Agreement in total hours doesn't mean a schedule exists (2).") {
    HashMap<string, int> doctors = {
        { "Doctor A", 8 },
        { "Doctor B", 8 },
        { "Doctor C", 8 },
    };
    HashMap<string, int> patients = {
        { "Patient U", 5 },
        { "Patient V", 5 },
        { "Patient W", 5 },
        { "Patient X", 4 },
        { "Patient Y", 3 },
        { "Patient Z", 2 },
    };

    /* Notice the the total hours free (24) matches the total number of hours needed
     * (24), but the way those hours are divvied up makes things impossible. Specifically,
     * no doctor can see two of the patients who each need five hours, so they need to be
     * spread around the three doctors evenly, but then there isn't enough time for
     * anyone to see the patient who needs four hours.
     */
    HashMap<string, HashSet<string>> schedule;
    EXPECT(!canAllPatientsBeSeen(doctors, patients, schedule));
}
