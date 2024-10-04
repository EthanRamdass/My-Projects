#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Structure to represent a transaction
struct Transaction {
    int id;
    string type; // "Income" or "Expense"
    string category;
    double amount;
    string date; // Format: YYYY-MM-DD
    string description;

    // Constructor
    Transaction(int _id, const string& _type, const string& _category, double _amount, const string& _date, const string& _description)
        : id(_id), type(_type), category(_category), amount(_amount), date(_date), description(_description) {}
};

// Class to manage the Expense Tracker
class ExpenseTracker {
private:
    vector<Transaction> transactions;
    int nextId;
    const string dataFile = "transactions.csv";

public:
    ExpenseTracker() : nextId(1) {
        loadData();
    }

    ~ExpenseTracker() {
        saveData();
    }

    // Function to add a transaction
    void addTransaction() {
        string type;
        cout << "Enter transaction type (Income/Expense): ";
        cin >> type;
        // Convert to lowercase for consistency
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type != "income" && type != "expense") {
            cout << "Invalid type. Transaction not added.\n";
            return;
        }
        // Capitalize first letter
        type[0] = toupper(type[0]);

        string category;
        cout << "Enter category: ";
        cin.ignore(); // Ignore leftover newline
        getline(cin, category);

        double amount;
        cout << "Enter amount: ";
        cin >> amount;
        if (amount <= 0) {
            cout << "Amount must be positive. Transaction not added.\n";
            return;
        }

        string date;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        // Simple date validation can be added here

        string description;
        cout << "Enter description: ";
        cin.ignore();
        getline(cin, description);

        Transaction newTrans(nextId++, type, category, amount, date, description);
        transactions.push_back(newTrans);
        cout << "Transaction added successfully with ID " << newTrans.id << ".\n";
    }

    // Function to view all transactions
    void viewTransactions() const {
        if (transactions.empty()) {
            cout << "No transactions to display.\n";
            return;
        }

        cout << left << setw(5) << "ID"
             << left << setw(10) << "Type"
             << left << setw(15) << "Category"
             << left << setw(10) << "Amount"
             << left << setw(12) << "Date"
             << left << setw(30) << "Description" << "\n";
        cout << "--------------------------------------------------------------------------------\n";

        for (const auto& trans : transactions) {
            cout << left << setw(5) << trans.id
                 << left << setw(10) << trans.type
                 << left << setw(15) << trans.category
                 << left << setw(10) << fixed << setprecision(2) << trans.amount
                 << left << setw(12) << trans.date
                 << left << setw(30) << trans.description << "\n";
        }
    }

    // Function to filter transactions by category
    void filterByCategory() const {
        if (transactions.empty()) {
            cout << "No transactions to filter.\n";
            return;
        }

        string category;
        cout << "Enter category to filter: ";
        cin.ignore();
        getline(cin, category);

        bool found = false;
        cout << left << setw(5) << "ID"
             << left << setw(10) << "Type"
             << left << setw(15) << "Category"
             << left << setw(10) << "Amount"
             << left << setw(12) << "Date"
             << left << setw(30) << "Description" << "\n";
        cout << "--------------------------------------------------------------------------------\n";

        for (const auto& trans : transactions) {
            if (trans.category == category) {
                cout << left << setw(5) << trans.id
                     << left << setw(10) << trans.type
                     << left << setw(15) << trans.category
                     << left << setw(10) << fixed << setprecision(2) << trans.amount
                     << left << setw(12) << trans.date
                     << left << setw(30) << trans.description << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No transactions found in the category \"" << category << "\".\n";
        }
    }

    // Function to filter transactions by date
    void filterByDate() const {
        if (transactions.empty()) {
            cout << "No transactions to filter.\n";
            return;
        }

        string date;
        cout << "Enter date to filter (YYYY-MM-DD): ";
        cin >> date;

        bool found = false;
        cout << left << setw(5) << "ID"
             << left << setw(10) << "Type"
             << left << setw(15) << "Category"
             << left << setw(10) << "Amount"
             << left << setw(12) << "Date"
             << left << setw(30) << "Description" << "\n";
        cout << "--------------------------------------------------------------------------------\n";

        for (const auto& trans : transactions) {
            if (trans.date == date) {
                cout << left << setw(5) << trans.id
                     << left << setw(10) << trans.type
                     << left << setw(15) << trans.category
                     << left << setw(10) << fixed << setprecision(2) << trans.amount
                     << left << setw(12) << trans.date
                     << left << setw(30) << trans.description << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No transactions found on the date \"" << date << "\".\n";
        }
    }

    // Function to edit a transaction
    void editTransaction() {
        if (transactions.empty()) {
            cout << "No transactions to edit.\n";
            return;
        }

        int id;
        cout << "Enter the ID of the transaction to edit: ";
        cin >> id;

        auto it = find_if(transactions.begin(), transactions.end(),
                          [id](const Transaction& t) { return t.id == id; });

        if (it != transactions.end()) {
            cout << "Editing Transaction ID " << id << ":\n";

            string type;
            cout << "Enter new transaction type (Income/Expense) or press Enter to keep [" << it->type << "]: ";
            cin.ignore();
            getline(cin, type);
            if (!type.empty()) {
                // Convert to lowercase for consistency
                transform(type.begin(), type.end(), type.begin(), ::tolower);
                if (type == "income" || type == "expense") {
                    // Capitalize first letter
                    type[0] = toupper(type[0]);
                    it->type = type;
                } else {
                    cout << "Invalid type. Keeping previous value.\n";
                }
            }

            string category;
            cout << "Enter new category or press Enter to keep [" << it->category << "]: ";
            getline(cin, category);
            if (!category.empty()) {
                it->category = category;
            }

            string amountStr;
            cout << "Enter new amount or press Enter to keep [" << it->amount << "]: ";
            getline(cin, amountStr);
            if (!amountStr.empty()) {
                double amount = stod(amountStr);
                if (amount > 0) {
                    it->amount = amount;
                } else {
                    cout << "Invalid amount. Keeping previous value.\n";
                }
            }

            string date;
            cout << "Enter new date (YYYY-MM-DD) or press Enter to keep [" << it->date << "]: ";
            getline(cin, date);
            if (!date.empty()) {
                it->date = date;
            }

            string description;
            cout << "Enter new description or press Enter to keep [" << it->description << "]: ";
            getline(cin, description);
            if (!description.empty()) {
                it->description = description;
            }

            cout << "Transaction updated successfully.\n";
        } else {
            cout << "Transaction with ID " << id << " not found.\n";
        }
    }

    // Function to delete a transaction
    void deleteTransaction() {
        if (transactions.empty()) {
            cout << "No transactions to delete.\n";
            return;
        }

        int id;
        cout << "Enter the ID of the transaction to delete: ";
        cin >> id;

        auto it = find_if(transactions.begin(), transactions.end(),
                          [id](const Transaction& t) { return t.id == id; });

        if (it != transactions.end()) {
            transactions.erase(it);
            cout << "Transaction deleted successfully.\n";
        } else {
            cout << "Transaction with ID " << id << " not found.\n";
        }
    }

    // Function to save transactions to a file
    void saveData() const {
        ofstream outFile(dataFile);
        if (!outFile) {
            cout << "Error opening file for saving.\n";
            return;
        }

        for (const auto& trans : transactions) {
            outFile << trans.id << ","
                    << trans.type << ","
                    << trans.category << ","
                    << trans.amount << ","
                    << trans.date << ","
                    << trans.description << "\n";
        }

        outFile.close();
    }

    // Function to load transactions from a file
    void loadData() {
        ifstream inFile(dataFile);
        if (!inFile) {
            // File doesn't exist, no data to load
            return;
        }

        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            // Split the line by comma
            vector<string> fields;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos) {
                fields.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            fields.push_back(line); // Last field

            if (fields.size() != 6) continue; // Invalid line

            int id = stoi(fields[0]);
            string type = fields[1];
            string category = fields[2];
            double amount = stod(fields[3]);
            string date = fields[4];
            string description = fields[5];

            transactions.emplace_back(id, type, category, amount, date, description);
            if (id >= nextId) {
                nextId = id + 1;
            }
        }

        inFile.close();
    }

    // Function to display the menu
    void displayMenu() const {
        cout << "\n=== Expense Tracker Menu ===\n";
        cout << "1. Add Transaction\n";
        cout << "2. View All Transactions\n";
        cout << "3. View Transactions by Category\n";
        cout << "4. View Transactions by Date\n";
        cout << "5. Edit Transaction\n";
        cout << "6. Delete Transaction\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
    }
};

// Function to display the main menu and handle user choices
void runExpenseTracker() {
    ExpenseTracker tracker;
    int choice;

    do {
        tracker.displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                tracker.addTransaction();
                break;
            case 2:
                tracker.viewTransactions();
                break;
            case 3:
                tracker.filterByCategory();
                break;
            case 4:
                tracker.filterByDate();
                break;
            case 5:
                tracker.editTransaction();
                break;
            case 6:
                tracker.deleteTransaction();
                break;
            case 7:
                cout << "Exiting Expense Tracker. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7);
}

int main() {
    cout << "Welcome to the Expense Tracker Application!\n";
    runExpenseTracker();
    return 0;
}
