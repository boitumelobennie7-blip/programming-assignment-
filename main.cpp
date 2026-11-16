#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int USER_COUNT = 3;

// Function declarations
int findAccount(string accountNumbers[], string wantedAccount, int size);
int signIn(string accountNumbers[], string pins[], int size);
int displayMenu();
double getAmount();
bool depositMoney(double balances[], int userIndex);
bool withdrawMoney(double balances[], int userIndex);
bool transferMoney(string names[], string accountNumbers[], double balances[], int userIndex, int size);
void showBalance(string names[], string accountNumbers[], double balances[], int userIndex);

int main()
{
    // Sample accounts for demonstration. Change these details before submission if required.
    string names[USER_COUNT] = {"Lerato Mokoena", "Daniel Nkosi", "Amina Dlamini"};
    string accountNumbers[USER_COUNT] = {"NB1001", "NB1002", "NB1003"};
    string pins[USER_COUNT] = {"2468", "1357", "8642"};
    double balances[USER_COUNT] = {2500.00, 1800.00, 3200.00};

    cout << "=====================================\n";
    cout << "             GCC BANK               \n";
    cout << "       Your money, your control      \n";
    cout << "=====================================\n\n";

    int activeUser = signIn(accountNumbers, pins, USER_COUNT);

    if (activeUser == -1)
    {
        cout << "Access denied. Please contact the bank administrator.\n";
        return 0;
    }

    cout << "\nWelcome, " << names[activeUser] << "!\n";

    int choice;
    do
    {
        choice = displayMenu();

        switch (choice)
        {
            case 1:
                depositMoney(balances, activeUser);
                break;

            case 2:
                withdrawMoney(balances, activeUser);
                break;

            case 3:
                transferMoney(names, accountNumbers, balances, activeUser, USER_COUNT);
                break;

            case 4:
                showBalance(names, accountNumbers, balances, activeUser);
                break;

            case 5:
                cout << "\nThank you for using Nova Bank. Goodbye!\n";
                break;

            default:
                cout << "Invalid menu option. Choose a number from 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}

// Searches the account array and returns the matching position, or -1 if absent.
int findAccount(string accountNumbers[], string wantedAccount, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (accountNumbers[i] == wantedAccount)
        {
            return i;
        }
    }
    return -1;
}

// Checks the account number and PIN. Three unsuccessful attempts are allowed.
int signIn(string accountNumbers[], string pins[], int size)
{
    string enteredAccount;
    string enteredPin;

    for (int attempt = 1; attempt <= 3; attempt++)
    {
        cout << "Account number: ";
        cin >> enteredAccount;
        cout << "PIN: ";
        cin >> enteredPin;

        int position = findAccount(accountNumbers, enteredAccount, size);

        if (position != -1 && pins[position] == enteredPin)
        {
            return position;
        }

        cout << "Incorrect account number or PIN. Attempts remaining: "
             << 3 - attempt << "\n\n";
    }

    return -1;
}

// Displays the options and returns the number entered by the user.
int displayMenu()
{
    int option;

    cout << "\n-------------- NOVA BANK --------------\n";
    cout << "1. Add funds\n";
    cout << "2. Withdraw funds\n";
    cout << "3. Transfer money\n";
    cout << "4. View account balance\n";
    cout << "5. Exit\n";
    cout << "----------------------------------------\n";
    cout << "Enter your selection: ";

    if (!(cin >> option))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return 0;
    }

    return option;
}

// Reads a numeric amount and rejects text, zero and negative values.
double getAmount()
{
    double amount;

    while (true)
    {
        cout << "Enter amount (R): ";

        if (cin >> amount)
        {
            if (amount > 0)
            {
                return amount;
            }
            cout << "The amount must be greater than zero.\n";
        }
        else
        {
            cout << "Please enter a valid number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

// Adds money to the selected user's balance and returns success status.
bool depositMoney(double balances[], int userIndex)
{
    double amount = getAmount();
    balances[userIndex] = balances[userIndex] + amount;

    cout << fixed << setprecision(2);
    cout << "Deposit successful. New balance: R" << balances[userIndex] << "\n";
    return true;
}

// Withdraws money only when the amount is positive and affordable.
bool withdrawMoney(double balances[], int userIndex)
{
    double amount = getAmount();

    if (amount > balances[userIndex])
    {
        cout << "Transaction declined. Your balance is not sufficient.\n";
        return false;
    }

    balances[userIndex] = balances[userIndex] - amount;

    cout << fixed << setprecision(2);
    cout << "Withdrawal successful. New balance: R" << balances[userIndex] << "\n";
    return true;
}

// Finds the recipient and updates both accounts after checking the conditions.
bool transferMoney(string names[], string accountNumbers[], double balances[], int userIndex, int size)
{
    string recipientAccount;
    cout << "Enter recipient account number: ";
    cin >> recipientAccount;

    int recipientIndex = findAccount(accountNumbers, recipientAccount, size);

    if (recipientIndex == -1)
    {
        cout << "That account number does not exist. Transfer cancelled.\n";
        return false;
    }

    if (recipientIndex == userIndex)
    {
        cout << "You cannot transfer money to your own account.\n";
        return false;
    }

    cout << "Recipient: " << names[recipientIndex] << "\n";
    double amount = getAmount();

    if (amount > balances[userIndex])
    {
        cout << "Transfer declined. Your balance is not sufficient.\n";
        return false;
    }

    balances[userIndex] = balances[userIndex] - amount;
    balances[recipientIndex] = balances[recipientIndex] + amount;

    cout << fixed << setprecision(2);
    cout << "Transfer completed successfully.\n";
    cout << "Your new balance: R" << balances[userIndex] << "\n";
    return true;
}

// Displays the signed-in user's account information and current balance.
void showBalance(string names[], string accountNumbers[], double balances[], int userIndex)
{
    cout << fixed << setprecision(2);
    cout << "\n----------- ACCOUNT SUMMARY -----------\n";
    cout << "Account holder: " << names[userIndex] << "\n";
    cout << "Account number: " << accountNumbers[userIndex] << "\n";
    cout << "Available balance: R" << balances[userIndex] << "\n";
    cout << "---------------------------------------\n";
}
