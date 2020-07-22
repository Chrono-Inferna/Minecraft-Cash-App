#include <fstream>
#include <regex>
#include <cstdlib>
#include <ctime>
#include "cashApp.hpp"

// Basically rand() but a larger scope RAND_MAX
#define rand32() (((unsigned long)rand()) << 16 | rand())

// Using's b/c I'm lazy; get out if you don't like it
using std::cin;
using std::cout;
using std::endl;
using std::ios;

// Text file objects
std::ifstream g_cashStorageIn;
std::ofstream g_cashStorageOut;

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
         << "Input a number from the menu to continue." << endl
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
            g_cashStorageIn.open("storage.txt");

            // Reads each line and displays
            while (getline(g_cashStorageIn, readLine))
            {
                cout << readLine << endl;
            }

            // Final endl for formatting reasons
            cout << endl;

            g_cashStorageIn.close();
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
            cout << "Thank you for using the Minecraft Cash App! Have a good day!" << endl
                 << endl;
            return 0;
            break;

        // Error case
        default:
            cout << "There was an error somewhere, try again!" << endl
                 << endl;
            break;
        }
    } while (stoi(menuSelection) != 9);
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
    int m_code;               // Int where the text to check is input
    string m_status;          // String to take in status, for reasons of ease
    bool m_duplicate = false; // Bool for whether or not newCode is a duplicate

    // New code to be input to the text file
    unsigned int m_newCode = rand32() % 8999999 + 1000000;

    g_cashStorageIn.open("storage.txt");

    // Probably pointless, but keeps randomizing until newCode isn't a duplicate
    do
    {
        // Keeps looping to find the code until it finds a duplicate or it's the end of the file
        do
        {
            g_cashStorageIn >> m_code;
            g_cashStorageIn >> m_status;
        } while (m_code != m_newCode && g_cashStorageIn.good());

        // If duplicate, try again, else continue
        if (m_code == m_newCode)
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

    g_cashStorageIn.close();

    // Inputs new code
    g_cashStorageOut.open("storage.txt", ios::app);
    g_cashStorageOut << endl
                     << m_newCode << " Unissued";
    g_cashStorageOut.close();
}

string checkStatus(int codeCheck)
{
    string m_status; // String to return the status of unissued, issued, or cashed
    int m_code;      // Int where the text to check is input

    g_cashStorageIn.open("storage.txt");

    // Keeps looping to find the code until it finds the right one
    do
    {
        g_cashStorageIn >> m_code;
        g_cashStorageIn >> m_status;
    } while (m_code != codeCheck && g_cashStorageIn.good());

    g_cashStorageIn.close();

    if (m_code == codeCheck)
        return "Status: " + m_status;
    else
        return "There was an error somewhere, try again!";
}

string editStatus(int codeEdit, string codeEditStatus)
{
    string m_status = "";    // String to determine the status of unissued, issued, or cashed
    int m_code = 0;          // Int where the text to check is input
    string m_lineEmpty = ""; // String to determine whether or not a line is empty, used to prevent duplication at the end of the text file
    bool codeFound = false;  // Bool to determine if the code was found or not

    if (codeEditStatus != "Unissued" && codeEditStatus != "Issued" && codeEditStatus != "Cashed")
        return "Error: The status you entered does not match the format, please try again!";

    // Open both in and out files
    g_cashStorageIn.open("storage.txt");
    g_cashStorageOut.open("temp.txt");

    // Keeps looping to find the code until it finds the right one
    while (g_cashStorageIn.eof() != true)
    {
        // Inputs then outputs to the temporary file
        g_cashStorageIn >> m_code;
        g_cashStorageOut << endl
                         << m_code << " ";
        g_cashStorageIn >> m_status;

        // If the code is the one we want to edit, edit
        if (m_code == codeEdit)
        {
            g_cashStorageOut << codeEditStatus;
            codeFound = true;
        }
        else
            g_cashStorageOut << m_status;
    }

    // Close objects up, rename, housekeeping stuff
    g_cashStorageIn.close();
    g_cashStorageOut.close();
    remove("storage.txt");
    rename("temp.txt", "storage.txt");

    // Returns if edit was successful or not
    if (codeFound == true)
        return "Edit was successful!";
    else
        return "There was an error somewhere, try again!";
}