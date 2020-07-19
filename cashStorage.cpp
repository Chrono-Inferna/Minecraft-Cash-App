#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "cashStorage.hpp"

// Basically rand() but a larger scope RAND_MAX
#define rand32() (((unsigned long)rand()) << 16 | rand())

using std::cin;
using std::cout;
using std::endl;
using std::ios;

// TODO: 4 statuses, input code and see what status is
// TODO: Type in a code, say if you wanna change
// TODO: Statuses: Cahsed, issued, unissued

// Text file object
std::fstream g_cashStorage;

int main()
{
    // Input variables
    int menuSelection;
    int codeStatusCheck = 0;

    // Seed the randomness function
    srand(time(NULL));

    // Opening hello + menu
    cout << endl
         << "Welcome to the encryptor!" << endl
         << "What would you like to do?" << endl
         << endl;

    // Loop to do multiple actions
    do
    {
        // Displays menu
        options();

        // Input selection
        cin >> menuSelection;
        cout << endl;

        // Switch statement to do this or that based off of menuSelection
        switch (menuSelection)
        {
        // Read text file case
        case 1:
            cout << endl;
            break;

        // Create code case
        case 2:
            createCode();
            break;

        // Check status of code case
        case 3:
            // Asks for code
            cout << "Enter the code you want to check" << endl;
            cin >> codeStatusCheck;

            // Prints status
            cout << endl
                 << "Status: " << checkStatus(codeStatusCheck) << endl
                 << endl;
            break;
        // Change status case
        case 4:
        cout;

            break;

        // Exit program case
        case 9:
            cout << "Bye!" << endl;
            break;

        // Error case
        default:
            cout << "That didn't work, try again." << endl
                 << endl;
            break;
        }
    } while (menuSelection != 9);
}

void options()
{
    cout << "1) Show code storage text file" << endl
         << "2) Create new code" << endl
         << "3) Check status" << endl
         << "4) Edit status" << endl
         << "9) Exit program" << endl
         << endl;
}

void createCode()
{
    // New code to be input to the text file
    unsigned int newCode = rand32() % 9999999 + 1000000;

    // TODO: Check for repeats, if so, randomize again

    // Inputs new code
    g_cashStorage.open("storage.txt", ios::out | ios::app);
    g_cashStorage << newCode << " Unissued" << endl;
    g_cashStorage.close();
}

string checkStatus(int codeCheck)
{
    string status; // String to return the status of unissued, issued, or cashed
    int intCheck;  // Int where the text to check is input

    g_cashStorage.open("storage.txt", ios::in);

    // Keeps looping to find the code until it finds the right one
    do
    {
        g_cashStorage >> intCheck;
        g_cashStorage >> status;
    } while (intCheck != codeCheck);

    g_cashStorage.close();

    return status;
}

void editStats(int codeEdit, string codeEditStats)
{
    string status; // String to determine the status of unissued, issued, or cashed
    int intCheck;  // Int where the text to check is input

    g_cashStorage.open("storage.txt", ios::in);

    do
    {
        g_cashStorage >> intCheck;
        g_cashStorage >> status;
    } while (intCheck != codeEdit);

    // g_cashStorage.seekg(status.length(), ios::cur);

    status.replace(status.find(status), status.length(), codeEditStats);

    g_cashStorage.close();
}