#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>
#include <iomanip>

using namespace std;

class User {
public:
    string name;
    string address;
    string phone;
    string date;
    int bookingID;
    float advancePayment;
};

class EventNode {
public:
    int eventID;
    int timeDuration;
    int guestCount;
    string venueName;
    bool isBooked; 
    
    User client;       
    EventNode* next;   

    EventNode() {
        next = nullptr;
        isBooked = false; 
    }
};

EventNode* head = nullptr;

void splitList(EventNode* source, EventNode** frontRef, EventNode** backRef) {
    EventNode* fast = source->next;
    EventNode* slow = source;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

EventNode* mergeSortedLists(EventNode* leftHalf, EventNode* rightHalf) {
    if (leftHalf == nullptr) return rightHalf;
    if (rightHalf == nullptr) return leftHalf;

    EventNode* result = nullptr;
    
    if (leftHalf->eventID <= rightHalf->eventID) {
        result = leftHalf;
        result->next = mergeSortedLists(leftHalf->next, rightHalf);
    } else {
        result = rightHalf;
        result->next = mergeSortedLists(leftHalf, rightHalf->next);
    }
    return result;
}

void mergeSort(EventNode** headRef) {
    EventNode* currentHead = *headRef;
    EventNode* leftHalf;
    EventNode* rightHalf;

    if ((currentHead == nullptr) || (currentHead->next == nullptr)) {
        return;
    }

    splitList(currentHead, &leftHalf, &rightHalf); 
    mergeSort(&leftHalf);                          
    mergeSort(&rightHalf);                         
    *headRef = mergeSortedLists(leftHalf, rightHalf); 
}

class EventManager {
public:
    void addEvent(int id);
    void displaySingleEvent(EventNode* event);
    void viewAvailableEvents();
    void bookEvent();
    void searchUserByName(string searchName);
    void generateBill(int id);
    void viewGuestSummary();
};

void EventManager::addEvent(int id) {
    EventNode* newEvent = new EventNode();
    newEvent->eventID = id;
    
    cout << "\n    Total Guest Capacity : ";
    cin >> newEvent->guestCount;
    cout << "\n    Time Limit (in minutes) : ";
    cin >> newEvent->timeDuration;
    cout << "\n    Venue Name (One word, e.g., GrandHall) : ";
    cin >> newEvent->venueName;
    
    newEvent->next = head;
    head = newEvent;
    
    mergeSort(&head);

    cout << "\n    Event Venue Added Successfully!";
    getch();
}

void EventManager::displaySingleEvent(EventNode* event) {
    cout << "\n   Event ID     : " << event->eventID;
    cout << "\n   Venue Name   : " << event->venueName;
    cout << "\n   Max Guests   : " << event->guestCount;
    cout << "\n   Time Limit   : " << event->timeDuration << " minutes\n";
}

void EventManager::viewAvailableEvents() {
    EventNode* temp = head;
    bool foundAny = false;
    
    cout << "\n\t\t\t\t--- Available Venues ---\n";
    while (temp != nullptr) {
        if (!temp->isBooked) { 
            displaySingleEvent(temp);
            cout << "   ----------------------------------";
            foundAny = true;
        }
        temp = temp->next;
    }
    
    if (!foundAny) {
        cout << "\n   Sorry, all venues are currently booked or none exist.";
    }
    cout << "\n\n   Press any key to return...";
    getch();
}

void EventManager::bookEvent() {
    int id;
    cout << "\n   Enter Event ID to book : ";
    cin >> id;
    
    EventNode* temp = head;
    while (temp != nullptr) {
        if (temp->eventID == id) {
            if (temp->isBooked) {
                cout << "\n   Sorry, this Event ID is already booked.";
                getch();
                return;
            }
            
            system("cls");
            cout << "\n\t\t\t\t--- Event Booking Form ---\n\n";
            cout << "   Enter Booking ID Number : "; cin >> temp->client.bookingID;
            cout << "   Enter Client First Name : "; cin >> temp->client.name;
            cout << "   Enter City             : "; cin >> temp->client.address;
            cout << "   Enter Phone Number      : "; cin >> temp->client.phone;
            cout << "   Enter Event Date        : "; cin >> temp->client.date;
            cout << "   Enter Advance Payment   : $"; cin >> temp->client.advancePayment;
            
            temp->isBooked = true; 
            cout << "\n\n   Venue Booked Successfully for " << temp->client.name << "!";
            getch();
            return;
        }
        temp = temp->next;
    }
    cout << "\n   Event ID not found.";
    getch();
}

void EventManager::searchUserByName(string searchName) {
    EventNode* temp = head;
    bool found = false;
    
    while (temp != nullptr) {
        if (temp->isBooked && temp->client.name == searchName) {
            system("cls");
            cout << "\n\t\t\t\t--- Client Booking Record ---\n";
            cout << "\n   Client Name  : " << temp->client.name;
            cout << "\n   Event ID     : " << temp->eventID;
            cout << "\n   Venue        : " << temp->venueName;
            cout << "\n   Date         : " << temp->client.date;
            cout << "\n\n   Press any key to continue...";
            found = true;
            getch();
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "\n   No active bookings found for client: " << searchName;
        getch();
    }
}

void EventManager::generateBill(int id) {
    EventNode* temp = head;
    
    while (temp != nullptr) {
        if (temp->isBooked && temp->eventID == id) {
            system("cls");
            int actualGuests, actualTime;
            
            cout << "\n\t\t\t\t--- Final Billing Checkout ---\n";
            cout << "\n   Enter Actual Number of Guests : "; cin >> actualGuests;
            cout << "\n   Enter Actual Time (Minutes)   : "; cin >> actualTime;
            
            double staffNeeded = ceil(actualGuests / 10.0); 
            double staffCostPerHour = 30.00;
            double staffCostPerMin = 0.50;
            double costPerMeal = 100.00;
            double fixedOverhead = 2500.00; 
            
            double totalStaffCost = ((actualTime / 60) * staffCostPerHour) + ((actualTime % 60) * staffCostPerMin);
            totalStaffCost *= staffNeeded;
            
            double totalFoodCost = actualGuests * costPerMeal;
            double totalBill = totalFoodCost + totalStaffCost + fixedOverhead;
            
            system("cls");
            cout << "\n\t\t\t\t--- Final Invoice ---\n";
            cout << "\n   Client Name      : " << temp->client.name;
            cout << "\n   Event ID         : " << temp->eventID;
            cout << "\n   -----------------------------------------";
            cout << fixed << setprecision(2); 
            cout << "\n   Food Cost        : $" << totalFoodCost;
            cout << "\n   Staff Cost       : $" << totalStaffCost << " (" << staffNeeded << " staff members)";
            cout << "\n   Fixed Overhead   : $" << fixedOverhead;
            cout << "\n   -----------------------------------------";
            cout << "\n   Grand Total      : $" << totalBill;
            cout << "\n   Advance Paid     : $" << temp->client.advancePayment;
            cout << "\n   Remaining Due    : $" << totalBill - temp->client.advancePayment;
            cout << "\n   -----------------------------------------\n";
            
            int accNum;
            cout << "\n   Enter Bank Account Number to pay remaining balance: ";
            cin >> accNum;
            cout << "   Processing Payment... Transaction Successful!";
            
            temp->isBooked = false; 
            cout << "\n\n   Event checked out. Venue is now available again.";
            getch();
            return;
        }
        temp = temp->next;
    }
    cout << "\n   Event ID not found or is not currently booked.";
    getch();
}

void EventManager::viewGuestSummary() {
    system("cls");
    cout << "\n\t\t\t\t--- All Active Bookings ---\n\n";
    
    if (head == nullptr) {
        cout << "   System is empty. No venues exist yet.";
    } else {
        EventNode* temp = head;
        bool foundAny = false;
        
        while (temp != nullptr) {
            if (temp->isBooked) {
                cout << "   Client: " << temp->client.name << " | Event ID: " << temp->eventID << " | Date: " << temp->client.date << "\n";
                foundAny = true;
            }
            temp = temp->next;
        }
        
        if (!foundAny) cout << "   No active bookings at the moment.";
    }
    cout << "\n\n   Press any key to return...";
    getch();
}

void manageEventsMenu(EventManager& manager) {
    int opt, id;
    do {
        system("cls");
        cout << "\n\t\t\t\t--- Admin: Manage Venues ---\n";
        cout << "\n   1. Add New Venue/Event slot";
        cout << "\n   2. Back to Main Menu";
        cout << "\n\n   Select Option: ";
        cin >> opt;
        
        if (opt == 1) {
            cout << "\n   Enter New Event ID (Number) : ";
            cin >> id;
            
            EventNode* temp = head;
            bool exists = false;
            while (temp != nullptr) {
                if (temp->eventID == id) exists = true;
                temp = temp->next;
            }
            
            if (exists) {
                cout << "\n   Error: Event ID already exists. Please use a unique ID.";
                getch();
            } else {
                manager.addEvent(id);
            }
        }
    } while (opt != 2);
}

int main() {
    EventManager manager;
    int choice;
    string searchName;
    int searchID;
    
    do {
        system("cls");
        cout << "\n\t\t\t===================================================";
        cout << "\n\t\t\t|            EVENT MANAGEMENT SYSTEM              |";
        cout << "\n\t\t\t===================================================\n";
        cout << "\n\t\t\t   1. Manage Event Venues (Add)";
        cout << "\n\t\t\t   2. View Available Venues";
        cout << "\n\t\t\t   3. Book an Event";
        cout << "\n\t\t\t   4. Search Client Booking";
        cout << "\n\t\t\t   5. Checkout & Generate Bill";
        cout << "\n\t\t\t   6. View Guest Summary";
        cout << "\n\t\t\t   7. Exit Program";
        cout << "\n\n\t\t\t   Enter your choice: ";
        cin >> choice;
        
        if (choice >= 2 && choice <= 6 && head == nullptr) {
            cout << "\n   The database is empty. Please Add an Event Venue first (Option 1).";
            getch();
            continue; 
        }
        
        switch (choice) {
            case 1: manageEventsMenu(manager); break;
            case 2: manager.viewAvailableEvents(); break;
            case 3: manager.bookEvent(); break;
            case 4: 
                cout << "\n   Enter Client's First Name to search: ";
                cin >> searchName;
                manager.searchUserByName(searchName); 
                break;
            case 5:
                cout << "\n   Enter Event ID for Checkout: ";
                cin >> searchID;
                manager.generateBill(searchID);
                break;
            case 6: manager.viewGuestSummary(); break;
            case 7: cout << "\n   Shutting down system. Thank you!\n"; break;
            default: cout << "\n   Invalid Input. Please try again."; getch(); break;
        }
    } while (choice != 7);
    
    return 0;
}