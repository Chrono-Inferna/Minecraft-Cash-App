#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "cashStorage.hpp"

// Basically rand() but a larger scope RAND_MAX
#define rand32() (((unsigned long)rand()) << 16 | rand())

// Using's b/c I'm lazy get out if you don't like it
using std::cin;
using std::cout;
using std::endl;
using std::ios;

// TODO: Errors for statuses, error catching in general

// Text file object
std::fstream g_cashStorage;

int main()
{
    string menuSelection;        // What do you think
    string readLine;             // Line variable for displaying the text file
    string codeStatusCheck;      // Input for codeStats
    string codeStatusEdit;       // Input 1 for codeEdit
    string codeStatusEditChange; // Input 2 for codeEdit

    // Seed random function
    srand(time(NULL));

    // Opening hello + menu
    cout << endl
         << "Welcome!" << endl
         << "What would you like to do?" << endl
         << endl;

    // Loop to do multiple actions
    do
    {
        // Menu
        options();
        cin >> menuSelection;
        cout << endl;

        // Switch statement to do this or that based off of menuSelection
        switch (stoi(menuSelection))
        {
        // Read text file case
        case 1:
            g_cashStorage.open("storage.txt", ios::in);

            // Reads each line and displays
            while (getline(g_cashStorage, readLine))
            {
                cout << readLine << endl;
            }

            // Final endl for formatting reasons
            cout << endl;

            g_cashStorage.close();
            break;

        // Create code case
        case 2:
            createCode();
            cout << "New code generated!" << endl
                 << endl;
            break;

        // Check status of code case
        case 3:
            // Input
            cout << "Enter the code you want to check:" << endl;
            cin >> codeStatusCheck;

            // Function complete, error or not
            cout << endl
                 << checkStatus(stoi(codeStatusCheck)) << endl
                 << endl;
            break;

        // Change status case
        case 4:
            // Inputs
            cout << "Enter the code you want to edit the status of:" << endl;
            cin >> codeStatusEdit;
            cout << endl
                 << "Enter what you want to change the status to (Unissued, Issued, Cashed, those exact spellings):" << endl;
            cin >> codeStatusEditChange;

            // Function complete, error or not
            cout << endl
                 << editStatus(stoi(codeStatusEdit), codeStatusEditChange) << endl
                 << endl;
            break;

        // Exit program case
        case 9:
            cout << "Bye!" << endl
                 << endl;
            break;

        // Error case
        default:
            cout << "That didn't work, try again." << endl
                 << endl;
            break;
        }
    } while (stoi(menuSelection) != 9);

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
    int m_intCheck;           // Int where the text to check is input
    string m_status;          // String to take in status, for reasons of ease
    bool m_duplicate = false; // Bool for whether or not newCode is a duplicate

    // New code to be input to the text file
    unsigned int m_newCode = rand32() % 9999999 + 1000000;

    g_cashStorage.open("storage.txt", ios::in);

    // Probably pointless, but keeps randomizing until newCode isn't a duplicate
    do
    {
        // Keeps looping to find the code until it finds the right one
        do
        {
            g_cashStorage >> m_intCheck;
            g_cashStorage >> m_status;
        } while (m_intCheck != m_newCode && g_cashStorage.good());

        // If duplicate, try again, else continue
        if (m_intCheck == m_newCode)
        {
            m_newCode = rand32() % 9999999 + 1000000;
        }
        else
        {
            m_duplicate = false;
        }
    } while (m_duplicate == true);

    // If for whatever reason, all codes have been taken, that's a problem
    // that I ain't dealin with

    g_cashStorage.close();

    // Inputs new code
    g_cashStorage.open("storage.txt", ios::out | ios::app);
    g_cashStorage << m_newCode << " Unissued" << endl;
    g_cashStorage.close();
}

string checkStatus(int codeCheck)
{
    string m_status; // String to return the status of unissued, issued, or cashed
    int m_intCheck;  // Int where the text to check is input

    g_cashStorage.open("storage.txt", ios::in);

    // Keeps looping to find the code until it finds the right one
    do
    {
        g_cashStorage >> m_intCheck;
        g_cashStorage >> m_status;
    } while (m_intCheck != codeCheck && g_cashStorage.good());

    g_cashStorage.close();

    if (m_intCheck == codeCheck)
    {
        return "Status: " + m_status;
    }
    else
    {
        return "There was an error somewhere, try again!";
    }
}

string editStatus(int codeEdit, string codeEditStatus)
{
    string m_status; // String to determine the status of unissued, issued, or cashed
    int m_intCheck;  // Int where the text to check is input

    g_cashStorage.open("storage.txt", ios::in);

    // Keeps looping to find the code until it finds the right one
    do
    {
        g_cashStorage >> m_intCheck;
        g_cashStorage >> m_status;
    } while (m_intCheck != codeEdit && g_cashStorage.good());

    m_status.replace(m_status.find(m_status), m_status.length(), codeEditStatus);

    g_cashStorage.close();

    // TODO: If/else to return error or not

    return "Test";
}