#include <iostream>
#include <string>

using namespace std;

// 1. Data structure for a patient (Linked List Node)
struct Patient {
    int id;
    string name;
    string illness;
    string doctorName; // Added to track the treating physician
    int day, month, year;
    Patient* next; // Pointer to the next patient
};

class HospitalSystem {
private:
    Patient* head;

public:
    HospitalSystem() {
        head = NULL;
    }

    // 2. Register a patient at the end of the list
    void registerPatient(int id, string name, string illness, string doctor, int d, int m, int y) {
        Patient* newPatient = new Patient();
        newPatient->id = id;
        newPatient->name = name;
        newPatient->illness = illness;
        newPatient->doctorName = doctor;
        newPatient->day = d;
        newPatient->month = m;
        newPatient->year = y;
        newPatient->next = NULL;

        if (head == NULL) {
            head = newPatient;
        } else {
            Patient* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newPatient;
        }
        cout << "\n>> SUCCESS: Patient " << name << " registered under Dr. " << doctor << ".\n";
    }

    // 3. Emergency registration at the front of the list
    void emergencyEntry(int id, string name, string illness, string doctor, int d, int m, int y) {
        Patient* newPatient = new Patient();
        newPatient->id = id;
        newPatient->name = name;
        newPatient->illness = illness;
        newPatient->doctorName = doctor;
        newPatient->day = d;
        newPatient->month = m;
        newPatient->year = y;

        newPatient->next = head;
        head = newPatient;
        cout << "\n>> EMERGENCY: Patient " << name << " moved to the front for Dr. " << doctor << ".\n";
    }

    // 4. Search for a patient by ID
    void searchPatient(int id) {
        Patient* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "\n--- Patient Record Found ---";
                cout << "\nID: " << temp->id;
                cout << "\nName: " << temp->name;
                cout << "\nIllness: " << temp->illness;
                cout << "\nAssigned Doctor: Dr. " << temp->doctorName;
                cout << "\nRegistration Date: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\n>> ERROR: Patient with ID " << id << " not found.\n";
    }

    // 5. Discharge a patient (Delete from list)
    void dischargePatient(int id) {
        if (head == NULL) {
            cout << "\n>> ERROR: The list is empty.\n";
            return;
        }
        if (head->id == id) {
            Patient* temp = head;
            head = head->next;
            delete temp;
            cout << "\n>> SUCCESS: Patient with ID " << id << " has been discharged.\n";
            return;
        }
        Patient* current = head;
        Patient* previous = NULL;
        while (current != NULL && current->id != id) {
            previous = current;
            current = current->next;
        }
        if (current != NULL) {
            previous->next = current->next;
            delete current;
            cout << "\n>> SUCCESS: Patient with ID " << id << " has been discharged.\n";
        } else {
            cout << "\n>> ERROR: Patient ID not found.\n";
        }
    }

    // 6. Display all patients in the queue
    void showAllPatients() {
        if (head == NULL) {
            cout << "\n>> The queue is currently empty.\n";
            return;
        }
        Patient* temp = head;
        cout << "\n========== CURRENT PATIENT QUEUE ==========\n";
        while (temp != NULL) {
            cout << "[ID: " << temp->id << " | Patient: " << temp->name
                 << " | Doctor: Dr. " << temp->doctorName
                 << " | Date: " << temp->day << "/" << temp->month << "/" << temp->year << "]\n   |\n   v\n";
            temp = temp->next;
        }
        cout << " [END OF QUEUE]\n";
    }
};

int main() {
    HospitalSystem hospital;
    int choice, id, d, m, y;
    string name, illness, doctor;

    do {
        cout << "\n======================================";
        cout << "\n   HOSPITAL MANAGEMENT SYSTEM";
        cout << "\n======================================";
        cout << "\n1. Register Patient (Normal)";
        cout << "\n2. Emergency Entry (Priority)";
        cout << "\n3. Discharge Patient";
        cout << "\n4. Search Patient Record";
        cout << "\n5. Show All Patients";
        cout << "\n6. Exit System";
        cout << "\n--------------------------------------";
        cout << "\nEnter choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
            case 2:
                cout << "Enter Patient ID: "; cin >> id;
                cout << "Enter Patient Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Illness/Reason: "; getline(cin, illness);
                cout << "Enter Assigned Doctor Name: "; getline(cin, doctor);
                cout << "Enter Day (DD): "; cin >> d;
                cout << "Enter Month (MM): "; cin >> m;
                cout << "Enter Year (YYYY): "; cin >> y;

                if (choice == 1)
                    hospital.registerPatient(id, name, illness, doctor, d, m, y);
                else
                    hospital.emergencyEntry(id, name, illness, doctor, d, m, y);
                break;

            case 3:
                cout << "Enter Patient ID to discharge: "; cin >> id;
                hospital.dischargePatient(id);
                break;

            case 4:
                cout << "Enter Patient ID to search: "; cin >> id;
                hospital.searchPatient(id);
                break;

            case 5:
                hospital.showAllPatients();
                break;

            case 6:
                cout << "Shutting down system... Goodbye!\n";
                break;

            default:
                cout << "Invalid selection! Please choose 1-6.\n";
        }
    } while (choice != 6);

    return 0;
}
