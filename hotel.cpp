#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Room {
protected:
    int roomNumber;
    string guestName;

public:
    Room(int number) : roomNumber(number), guestName("Empty") {}

    virtual void displayStatus() const {
        cout << "Room " << roomNumber << " is " << guestName << "." << endl;
    }

    virtual void bookRoom(const string& guest) {
        guestName = guest;
        cout << "Room " << roomNumber << " is now booked by " << guestName << "." << endl;
    }

    virtual void checkOut() {
        if (guestName == "Empty") {
            cout << "Room " << roomNumber << " is already vacant." << endl;
        } else {
            guestName = "Empty";
            cout << "Guest has checked out of Room " << roomNumber << "." << endl;
        }
    }

    const string& getGuestName() const {
        return guestName;
    }

    bool isBooked() const {
        return guestName != "Empty";
    }
};

class StandardRoom : public Room {
public:
    StandardRoom(int number) : Room(number) {}

    void displayStatus() const override {
        cout << "Room " << roomNumber << " (Standard) is " << guestName << "." << endl;
    }
};

class DeluxeRoom : public Room {
public:
    DeluxeRoom(int number) : Room(number) {}

    void displayStatus() const override {
        cout << "Room " << roomNumber << " (Deluxe) is " << guestName << "." << endl;
    }
};

class Hotel {
private:
    vector<Room*> rooms;

public:
    Hotel() {
        for (int i = 1; i <= 10; ++i) {
            if (i <= 5) {
                rooms.push_back(new StandardRoom(i));
            } else {
                rooms.push_back(new DeluxeRoom(i));
            }
        }
    }

    ~Hotel() {
        for (Room* room : rooms) {
            delete room;
        }
    }

    void mainMenu() {
        int choice;
        cout << "\n\t\t\t**********";
        cout << "\n\t\t\t* HOTEL MANAGEMENT MENU *";
        cout << "\n\t\t\t**********";

        while (true) {
            cout << "\n1. Book a Standard Room";
            cout << "\n2. Book a Deluxe Room";
            cout << "\n3. Customer record";
            cout << "\n4. Rooms allotted";
            cout << "\n5. Edit record";
            cout << "\n6. Check Out";
            cout << "\n7. Exit menu";

            cout << "\n\nEnter your choice: ";
            cin >> choice;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    bookRoom("Standard");
                    break;
                case 2:
                    bookRoom("Deluxe");
                    break;
                case 3:
                    displayCustomerRecord();
                    break;
                case 4:
                    displayRoomsAllotted();
                    break;
                case 5:
                    editRecord();
                    break;
                case 6:
                    checkOut();
                    break;
                case 7:
                    return;
                default:
                    cout << "\nWrong choice! Please try again." << endl;
                    break;
            }
        }
    }

    void bookRoom(const string& type) {
        int roomNumber;
        cout << "Enter room number: ";
        cin >> roomNumber;

        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number. Please enter a valid room number." << endl;
            return;
        }

        Room* room = rooms[roomNumber - 1];

        if (room->isBooked()) {
            cout << "Room " << roomNumber << " (" << (room->getGuestName()) << ") is already booked." << endl;
            return;
        }

        string guestName;
        cout << "Enter guest name: ";
        cin >> guestName;

        if (roomTypeMatch(room, type)) {
            room->bookRoom(guestName);
        } else {
            cout << "Room " << roomNumber << " is of type " << type << " and does not match the requested type." << endl;
        }
    }

    bool roomTypeMatch(Room* room, const string& type) {
        return (room->getGuestName() == "Empty") || (room->getGuestName() == type);
    }

    void displayCustomerRecord() {
        int roomNumber;
        cout << "Enter room number: ";
        cin >> roomNumber;

        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number. Please enter a valid room number." << endl;
            return;
        }

        rooms[roomNumber - 1]->displayStatus();
    }

    void displayRoomsAllotted() {
        cout << "\nList of Rooms Allotted";
        cout << "\n----------------------";

        for (Room* room : rooms) {
            room->displayStatus();
        }

        cout << "\nPress any key to continue...";
        cin.get();
    }

    void editRecord() {
        int roomNumber;
        cout << "Enter room number: ";
        cin >> roomNumber;

        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number. Please enter a valid room number." << endl;
            return;
        }

        if (rooms[roomNumber - 1]->isBooked()) {
            string guestName;
            cout << "Enter new guest name: ";
            cin >> guestName;
            rooms[roomNumber - 1]->bookRoom(guestName);
        } else {
            cout << "Room " << roomNumber << " (" << (rooms[roomNumber - 1]->getGuestName()) << ") is empty and cannot be edited." << endl;
        }
    }

    void checkOut() {
        int roomNumber;
        cout << "Enter room number to check out: ";
        cin >> roomNumber;

        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number. Please enter a valid room number." << endl;
            return;
        }

        rooms[roomNumber - 1]->checkOut();
    }
};

int main() {
    Hotel hotel;
    hotel.mainMenu();
    return 0;
}