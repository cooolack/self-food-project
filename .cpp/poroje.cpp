#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// --------- Structures (Our Character Templates) ---------
struct User {
    string username;  // Username (nickname)
    string password;  // Password (life secret)
    int role;         // 0 = Admin, 1 = Hungry Student
};

struct Meal {
    int id;           // Food ID (identification code)
    string name;      // Food name (the hero of our story)
    int price;        // Price (the cost you must pay)
};

struct Reservation {
    string username;  // Who reserved?
    int mealId;       // What did they reserve?
    bool canceled;    // Changed their mind or not?
};

// --------- Data (The Main Actors) ---------
User users[10];           // 10 users (you + your roommates)
Meal meals[10];           // 10 types of food (3 always available)
Reservation reservations[20]; // 20 reservations (never full)

int userCount = 0;        // How many users?
int mealCount = 0;        // How many meals?
int resCount = 0;         // How many reservations?

// --------- Helper Functions ---------
bool userExists(string username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            return true;
        }
    }
    return false;
}

bool mealExists(int mealId) {
    for (int i = 0; i < mealCount; i++) {
        if (meals[i].id == mealId) {
            return true;
        }
    }
    return false;
}

// --------- Admin Menu (Royal Administration) ---------
void adminMenu() {
    int choice;
    while (true) {
        cout << "\n" << string(40, '=') << "\n";
        cout << "        ADMIN THRONE ROOM\n";
        cout << string(40, '=') << "\n";
        cout << "1. Add New(Student)\n";
        cout << "2. Show Student\n";
        cout << "3. Add (Food)\n";
        cout << "4. Show food\n";
        cout << "5. Show Requests (Reservations)\n";
        cout << "6. Return to Main Realm\n";
        cout << string(40, '-') << "\n";
        cout << "Your Command: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: { // Add Student (Recruitment!)
                if (userCount >= 10) {
                    cout << "🚨 Realm is full! No more space!\n";
                    break;
                }
                
                string username;
                cout << "New Soldier's Nickname: ";
                cin >> username;
                
                if (userExists(username)) {
                    cout << "❌ This nickname is already taken!\n";
                    break;
                }
                
                cout << "Secret Password: ";
                string password;
                cin >> password;
                
                users[userCount].username = username;
                users[userCount].password = password;
                users[userCount].role = 1;
                userCount++;
                
                cout << "✅ Soldier " << username << " registered successfully!\n";
                break;
            }
            
            case 2: { // Show Students (Military Parade)
                if (userCount <= 1) {
                    cout << "🏰 Only you (Admin) in the realm!\n";
                } else {
                    cout << "\n📜 Soldier List:\n";
                    cout << string(30, '-') << "\n";
                    for (int i = 1; i < userCount; i++) {
                        cout << i << ". " << users[i].username 
                             << " (Hungry Soldier)\n";
                    }
                }
                break;
            }
            
            case 3: { // Add Food (War Supplies!)
                if (mealCount >= 10) {
                    cout << "🚫 Kitchen is full!\n";
                    break;
                }
                
                int id;
                cout << "Supply Code: ";
                cin >> id;
                
                // Check duplicate ID
                for (int i = 0; i < mealCount; i++) {
                    if (meals[i].id == id) {
                        cout << "❌ This ID already exists!\n";
                        return;
                    }
                }
                
                cin.ignore();
                cout << "Supply Name: ";
                string name;
                getline(cin, name);
                
                cout << "Supply Cost (Coins): ";
                int price;
                cin >> price;
                
                meals[mealCount].id = id;
                meals[mealCount].name = name;
                meals[mealCount].price = price;
                mealCount++;
                
                cout << "✅ Supply " << name << " added!\n";
                break;
            }
            
            case 4: { // Show Food (War Buffet)
                if (mealCount == 0) {
                    cout << "🍽️ Kitchen is empty!\n";
                } else {
                    cout << "\n🍖 Supply Menu:\n";
                    cout << string(40, '-') << "\n";
                    cout << setw(5) << "ID" << setw(20) << "Name" 
                         << setw(15) << "Price\n";
                    cout << string(40, '-') << "\n";
                    
                    for (int i = 0; i < mealCount; i++) {
                        cout << setw(5) << meals[i].id
                             << setw(20) << meals[i].name
                             << setw(13) << meals[i].price << " Coins\n";
                    }
                }
                break;
            }
            
            case 5: { // Show Reservations (War Requests)
                if (resCount == 0) {
                    cout << "📭 No requests registered!\n";
                } else {
                    cout << "\n📋 Request List:\n";
                    cout << string(50, '-') << "\n";
                    cout << setw(5) << "No." << setw(15) << "Student" 
                         << setw(10) << "Food ID" << setw(15) << "Status\n";
                    cout << string(50, '-') << "\n";
                    
                    int activeCount = 0;
                    for (int i = 0; i < resCount; i++) {
                        if (!reservations[i].canceled) {
                            cout << setw(5) << i + 1
                                 << setw(15) << reservations[i].username
                                 << setw(10) << reservations[i].mealId
                                 << setw(15) << "ACTIVE\n";
                            activeCount++;
                        }
                    }
                    
                    if (activeCount == 0) {
                        cout << "No active requests found!\n";
                    }
                }
                break;
            }
            
            case 6: // Return to Main
                cout << "👋 Returning to main realm...\n";
                return;
                
            default:
                cout << "❌ Invalid command!\n";
        }
    }
}

// --------- Student Menu (Hungry Soldier's Life) ---------
void studentMenu(string username) {
    int choice;
    while (true) {
        cout << "\n" << string(40, '=') << "\n";
        cout << "   HUNGRY STUDENT: " << username << "\n";
        cout << string(40, '=') << "\n";
        cout << "1. View Food Menu\n";
        cout << "2. Reserve Food\n";
        cout << "3. My Reservations\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Logout\n";
        cout << string(40, '-') << "\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: { // View Food
                if (mealCount == 0) {
                    cout << "🍽️ No food available!\n";
                } else {
                    cout << "\n📋 TODAY'S MENU:\n";
                    cout << string(40, '-') << "\n";
                    for (int i = 0; i < mealCount; i++) {
                        cout << "[" << meals[i].id << "] " 
                             << meals[i].name << " - "
                             << meals[i].price << " Coins\n";
                    }
                }
                break;
            }
            
            case 2: { // Reserve Food
                if (resCount >= 20) {
                    cout << "🚫 Maximum reservations reached!\n";
                    break;
                }
                
                if (mealCount == 0) {
                    cout << "🍽️ No food to reserve!\n";
                    break;
                }
                
                // Show menu first
                cout << "\nAvailable Food:\n";
                for (int i = 0; i < mealCount; i++) {
                    cout << meals[i].id << " - " << meals[i].name 
                         << " (" << meals[i].price << " Coins)\n";
                }
                
                int mealId;
                cout << "\nEnter Food ID to reserve: ";
                cin >> mealId;
                
                if (!mealExists(mealId)) {
                    cout << "❌ Invalid Food ID!\n";
                    break;
                }
                
                // Check if already reserved (active)
                for (int i = 0; i < resCount; i++) {
                    if (reservations[i].username == username && 
                        reservations[i].mealId == mealId && 
                        !reservations[i].canceled) {
                        cout << "⚠️ You already reserved this!\n";
                        return;
                    }
                }
                
                // Make reservation
                reservations[resCount].username = username;
                reservations[resCount].mealId = mealId;
                reservations[resCount].canceled = false;
                resCount++;
                
                // Find meal name
                string mealName;
                for (int i = 0; i < mealCount; i++) {
                    if (meals[i].id == mealId) {
                        mealName = meals[i].name;
                        break;
                    }
                }
                
                cout << "✅ Successfully reserved: " << mealName << "\n";
                break;
            }
            
            case 3: { // My Reservations
                bool hasReservations = false;
                
                cout << "\n📌 MY RESERVATIONS:\n";
                cout << string(40, '-') << "\n";
                
                for (int i = 0; i < resCount; i++) {
                    if (reservations[i].username == username && 
                        !reservations[i].canceled) {
                        hasReservations = true;
                        int mealId = reservations[i].mealId;
                        
                        // Find meal details
                        for (int j = 0; j < mealCount; j++) {
                            if (meals[j].id == mealId) {
                                cout << "• " << meals[j].name 
                                     << " (ID: " << mealId 
                                     << ", Price: " << meals[j].price << " Coins)\n";
                                break;
                            }
                        }
                    }
                }
                
                if (!hasReservations) {
                    cout << "📭 You have no active reservations!\n";
                }
                break;
            }
            
            case 4: { // Cancel Reservation
                // Collect active reservations
                int myReservations[20];
                int myResCount = 0;
                
                for (int i = 0; i < resCount; i++) {
                    if (reservations[i].username == username && 
                        !reservations[i].canceled) {
                        myReservations[myResCount] = i;
                        myResCount++;
                    }
                }
                
                if (myResCount == 0) {
                    cout << "📭 No reservations to cancel!\n";
                    break;
                }
                
                // Display reservations
                cout << "\nYour Active Reservations:\n";
                for (int i = 0; i < myResCount; i++) {
                    int idx = myReservations[i];
                    int mealId = reservations[idx].mealId;
                    
                    // Find meal name
                    for (int j = 0; j < mealCount; j++) {
                        if (meals[j].id == mealId) {
                            cout << i + 1 << ". " << meals[j].name 
                                 << " (ID: " << mealId << ")\n";
                            break;
                        }
                    }
                }
                
                int cancelChoice;
                cout << "\nSelect reservation to cancel (0 to exit): ";
                cin >> cancelChoice;
                
                if (cancelChoice == 0) break;
                
                if (cancelChoice < 1 || cancelChoice > myResCount) {
                    cout << "❌ Invalid selection!\n";
                    break;
                }
                
                // Cancel the reservation
                int resIndex = myReservations[cancelChoice - 1];
                reservations[resIndex].canceled = true;
                
                // Get meal name for confirmation
                string mealName;
                int mealId = reservations[resIndex].mealId;
                for (int i = 0; i < mealCount; i++) {
                    if (meals[i].id == mealId) {
                        mealName = meals[i].name;
                        break;
                    }
                }
                
                cout << "✅ Reservation for " << mealName << " cancelled!\n";
                break;
            }
            
            case 5: // Logout
                cout << "👋 Goodbye " << username << "!\n";
                return;
                
            default:
                cout << "❌ Invalid choice!\n";
        }
    }
}

// --------- Main Function (The Grand Entrance) ---------
int main() {
    // Default setup
    users[0].username = "admin";
    users[0].password = "1234";
    users[0].role = 0;
    userCount = 1;
    
    // Sample meals
    meals[0] = {1, "Pizza", 25000};
    meals[1] = {2, "Burger", 30000};
    meals[2] = {3, "Pasta", 20000};
    mealCount = 3;
    
    cout << string(50, '=') << "\n";
    cout << "    UNIVERSITY FOOD RESERVATION SYSTEM\n";
    cout << string(50, '=') << "\n\n";
    
    while (true) {
        string username, password;
        
        cout << "Username (or 'exit' to quit): ";
        cin >> username;
        
        if (username == "exit") {
            cout << "👋 Goodbye! See you next meal!\n";
            break;
        }
        
        cout << "Password: ";
        cin >> password;
        
        bool loginSuccess = false;
        int userIndex = -1;
        
        // Check credentials
        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && 
                users[i].password == password) {
                loginSuccess = true;
                userIndex = i;
                break;
            }
        }
        
        if (loginSuccess) {
            cout << "\n✅ Login successful! Welcome " << username << "!\n";
            
            if (users[userIndex].role == 0) {
                adminMenu();
            } else {
                studentMenu(username);
            }
            
            cout << "\n" << string(40, '=') << "\n";
            cout << "    Back to Login Screen\n";
            cout << string(40, '=') << "\n";
        } else {
            cout << "❌ Login failed! Wrong username or password.\n\n";
        }
    }
    
    return 0;
}