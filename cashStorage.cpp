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

// TODO: Errors for statuses

// Text file object
std::fstream g_cashStorage;

int main()
{
    int menuSelection;           // What do you think
    int codeStatusCheck = 0;     // Input for codeStats
    int codeStatusEdit = 0;      // Input 1 for codeEdit
    string codeStatusEditChange; // Input 2 for codeEdit

    // Seed the randomness function
    srand(time(NULL));

    // Opening hello + menu
    cout << endl
         << "Welcome!" << endl
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
            cout << "New code generated!" << endl;
            break;

        // Create code case
        case 2:
            createCode();
            break;

        // Check status of code case
        case 3:
            // Asks for code
            cout << "Enter the code you want to check:" << endl;
            cin >> codeStatusCheck;

            // Prints status
            cout << endl
                 << checkStatus(codeStatusCheck) << endl
                 << endl;
            break;
        // Change status case
        case 4:
            // Inputs
            cout << "Enter the code you want to edit the status of:" << endl;
            cin >> codeStatusEdit;
            cout << endl
                 << "Enter what you want to change the status to (Unissued, Issued, Cashed, that exact spelling):" << endl;
            cin >> codeStatusEditChange;

            // Function complete, error or not
            cout << endl
                 << editStatus(codeStatusEdit, codeStatusEditChange) << endl
                 << endl;
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

    return 0;
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
    } while (intCheck != codeCheck && g_cashStorage.good());

    g_cashStorage.close();

    if (intCheck == codeCheck)
    {
        return "Status: " + status;
    }
    else
    {
        return "There was an error somewhere, try again!";
    }
}

string editStatus(int codeEdit, string codeEditStatus)
{
    string status; // String to determine the status of unissued, issued, or cashed
    int intCheck;  // Int where the text to check is input

    g_cashStorage.open("storage.txt", ios::in);

    do
    {
        g_cashStorage >> intCheck;
        g_cashStorage >> status;
    } while (intCheck != codeEdit && g_cashStorage.good());

    status.replace(status.find(status), status.length(), codeEditStatus);

    g_cashStorage.close();

    return "Test";
}