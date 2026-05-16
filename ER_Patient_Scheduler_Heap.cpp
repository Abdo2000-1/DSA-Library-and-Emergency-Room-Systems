#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Patient {
    int id;
    string name;
    int severity;
    int arrivalTime;
};

bool hasPriority(Patient p1, Patient p2) {
    if (p1.severity == p2.severity)
        return p1.arrivalTime < p2.arrivalTime;
    return p1.severity > p2.severity;
}

class ERHeap {
private:
    vector<Patient> heap;

    void up(int i) {
        int parent = (i - 1) / 2;
        while (i > 0 && hasPriority(heap[i], heap[parent])) {
            swap(heap[i], heap[parent]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int maxIdx = i;

        if (left < heap.size() && hasPriority(heap[left], heap[maxIdx]))
            maxIdx = left;

        if (right < heap.size() && hasPriority(heap[right], heap[maxIdx]))
            maxIdx = right;

        if (maxIdx != i) {
            swap(heap[i], heap[maxIdx]);
            down(maxIdx);
        }
    }

public:
    void insert(Patient p) {
        heap.push_back(p);
        up(heap.size() - 1);
    }

    void treatNextPatient() {
        if (heap.empty()) return;

        cout << "Treating Patient: " << heap[0].name << " (Severity: " << heap[0].severity << ")\n";

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) down(0);
    }

    void viewNextPatient() {
        if (heap.empty()) return;
        cout << "Next Patient: " << heap[0].name << " (Severity: " << heap[0].severity << ")\n";
    }

    void updateSeverity(int id, int newSeverity) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].id == id) {
                int oldSeverity = heap[i].severity;
                heap[i].severity = newSeverity;

                if (newSeverity > oldSeverity) up(i);
                else down(i);

                return;
            }
        }
    }

    void displayAll() {
        for (const auto& p : heap) {
            cout << "ID: " << p.id << " | Name: " << p.name
                << " | Severity: " << p.severity << " | Arrival: " << p.arrivalTime << "\n";
        }
    }
};

int main() {
    ERHeap er;

    er.insert({ 1, "Ahmed", 8, 100 });
    er.insert({ 2, "Mona", 5, 105 });
    er.insert({ 3, "Sayed", 10, 110 });
    er.insert({ 4, "Nour", 8, 95 });

    cout << "--- Current ER Queue ---\n";
    er.displayAll();
    cout << "\n";

    er.viewNextPatient();
    er.treatNextPatient();

    cout << "\nAfter treating the highest priority:\n";
    er.displayAll();

    cout << "\nUpdating Mona's severity to 9...\n";
    er.updateSeverity(2, 9);
    er.viewNextPatient();

    return 0;
}