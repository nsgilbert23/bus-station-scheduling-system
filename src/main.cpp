#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

class Bus {
public:
    int busID;
    string route;
    int departureTime;
    int priority;
    int capacity;
    bool cancelled;
    bool delayed;

    Bus(int id, string r, int d, int p, int c) {
        busID = id;
        route = r;
        departureTime = d;
        priority = p;
        capacity = c;
        cancelled = false;
        delayed = false;
    }
};

class CompareBus {
public:
    bool operator()(Bus a, Bus b) {
        return a.priority > b.priority;
    }
};

priority_queue<Bus, vector<Bus>, CompareBus> busQueue;
queue<string> passengerQueue;

void addBus() {
    int id, dep, pri, cap;
    string route;

    cout << "\nEnter Bus ID: ";
    cin >> id;

    cout << "Enter Route: ";
    cin >> route;

    cout << "Enter Departure Time: ";
    cin >> dep;

    cout << "Enter Priority (lower number = higher priority): ";
    cin >> pri;

    cout << "Enter Capacity: ";
    cin >> cap;

    busQueue.push(Bus(id, route, dep, pri, cap));

    cout << "Bus added successfully.\n";
}

void addPassenger() {
    string name;

    cout << "Enter Passenger Name: ";
    cin >> name;

    passengerQueue.push(name);

    cout << "Passenger added to waiting queue.\n";
}

void showPassengers() {

    if (passengerQueue.empty()) {
        cout << "No passengers waiting.\n";
        return;
    }

    queue<string> temp = passengerQueue;

    cout << "\nPassenger Queue:\n";

    while (!temp.empty()) {
        cout << temp.front() << endl;
        temp.pop();
    }
}

void showBusSchedule() {

    if (busQueue.empty()) {
        cout << "No buses scheduled.\n";
        return;
    }

    priority_queue<Bus, vector<Bus>, CompareBus> temp = busQueue;

    cout << "\nBus Schedule\n";

    while (!temp.empty()) {

        Bus b = temp.top();
        temp.pop();

        cout << "Bus ID: " << b.busID
             << " | Route: " << b.route
             << " | Departure: " << b.departureTime
             << " | Capacity: " << b.capacity;

        if (b.cancelled)
            cout << " | Cancelled";

        if (b.delayed)
            cout << " | Delayed";

        cout << endl;
    }
}

void cancelBus() {

    if (busQueue.empty()) {
        cout << "No buses available.\n";
        return;
    }

    int id;
    cout << "Enter Bus ID to cancel: ";
    cin >> id;

    priority_queue<Bus, vector<Bus>, CompareBus> temp;

    while (!busQueue.empty()) {

        Bus b = busQueue.top();
        busQueue.pop();

        if (b.busID == id) {
            b.cancelled = true;
            cout << "Bus " << id << " cancelled.\n";
        }

        temp.push(b);
    }

    busQueue = temp;
}

void delayBus() {

    if (busQueue.empty()) {
        cout << "No buses available.\n";
        return;
    }

    int id;
    cout << "Enter Bus ID to delay: ";
    cin >> id;

    priority_queue<Bus, vector<Bus>, CompareBus> temp;

    while (!busQueue.empty()) {

        Bus b = busQueue.top();
        busQueue.pop();

        if (b.busID == id) {
            b.delayed = true;
            b.priority += 2;
            cout << "Bus " << id << " delayed.\n";
        }

        temp.push(b);
    }

    busQueue = temp;
}

void startBoarding() {

    if (busQueue.empty()) {
        cout << "No buses available.\n";
        return;
    }

    Bus bus = busQueue.top();
    busQueue.pop();

    if (bus.cancelled) {
        cout << "Bus " << bus.busID << " is cancelled.\n";
        return;
    }

    cout << "\nBoarding Bus " << bus.busID << " (Route: " << bus.route << ")\n";

    int seats = bus.capacity;

    while (seats > 0 && !passengerQueue.empty()) {

        cout << passengerQueue.front() << " boarded.\n";
        passengerQueue.pop();
        seats--;
    }

    if (seats == 0)
        cout << "Bus is full.\n";

    if (passengerQueue.empty())
        cout << "No more passengers waiting.\n";

    cout << "Bus " << bus.busID << " departed.\n";
}

void showMenu() {

    cout << "\n========== CITY BUS TERMINAL SYSTEM ==========\n";
    cout << "1. Add Bus\n";
    cout << "2. Add Passenger\n";
    cout << "3. Show Bus Schedule\n";
    cout << "4. Show Passenger Queue\n";
    cout << "5. Start Boarding\n";
    cout << "6. Delay Bus\n";
    cout << "7. Cancel Bus\n";
    cout << "8. Exit\n";
}

int main() {

    int choice;

    while (true) {

        showMenu();

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addBus();
            break;

        case 2:
            addPassenger();
            break;

        case 3:
            showBusSchedule();
            break;

        case 4:
            showPassengers();
            break;

        case 5:
            startBoarding();
            break;

        case 6:
            delayBus();
            break;

        case 7:
            cancelBus();
            break;

        case 8:
            cout << "Exiting system...\n";
            return 0;

        default:
            cout << "Invalid option.\n";
        }
    }
}
