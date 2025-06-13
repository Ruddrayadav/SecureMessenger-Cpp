#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> // For Sleep and system("cls")
using namespace std;

// Color definitions (ANSI escape codes) - Optional on Windows
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

string currentUser = "";

void pause(int seconds)
{
    Sleep(seconds * 1000); // Sleep takes milliseconds
}

void clearScreen()
{
    system("cls");
}

bool userExists(const string &username)
{
    ifstream file("users.txt");
    string user, pass;
    while (file >> user >> pass)
    {
        if (user == username)
            return true;
    }
    return false;
}

void registerUser()
{
    string username, password;
    cout << CYAN << "\n[ Registration ]\n"
         << RESET;
    cout << "Enter new username: ";
    cin >> username;

    if (userExists(username))
    {
        cout << RED << "Username already exists. Try another.\n"
             << RESET;
        pause(2);
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    cout << GREEN << "Registration successful!\n"
         << RESET;
    pause(2);
}

bool loginUser()
{
    string username, password;
    cout << CYAN << "\n[ Login ]\n"
         << RESET;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string user, pass;
    while (file >> user >> pass)
    {
        if (user == username && pass == password)
        {
            cout << GREEN << "Login successful!\n"
                 << RESET;
            currentUser = username;
            pause(2);
            return true;
        }
    }

    cout << RED << "Login failed. Please try again.\n"
         << RESET;
    pause(2);
    return false;
}

string encryptMessage(const string &message)
{
    string encrypted = message;
    for (char &ch : encrypted)
    {
        ch += 3;
    }
    return encrypted;
}

string decryptMessage(const string &encrypted)
{
    string decrypted = encrypted;
    for (char &ch : decrypted)
    {
        ch -= 3;
    }
    return decrypted;
}

void sendMessage()
{
    string recipient;
    cout << CYAN << "\n[ Send Message ]\n"
         << RESET;
    cout << "Enter recipient username: ";
    cin >> recipient;

    if (!userExists(recipient))
    {
        cout << RED << "No user found with that username. Message not sent.\n"
             << RESET;
        pause(2);
        return;
    }

    cin.ignore();
    string message;
    cout << "Enter your message: ";
    getline(cin, message);

    string fullMessage = "From " + currentUser + ": " + message;
    string encrypted = encryptMessage(fullMessage);

    ofstream file(recipient + "_messages.txt", ios::app);
    if (file.is_open())
    {
        file << encrypted << endl;
        file.close();
        cout << GREEN << "Message sent to " << recipient << " successfully.\n"
             << RESET;
    }
    else
    {
        cout << RED << "Error sending message.\n"
             << RESET;
    }

    pause(2);
}

void readMessage()
{
    ifstream file(currentUser + "_messages.txt");
    string encrypted;

    cout << CYAN << "\n[ Inbox ]\n"
         << RESET;
    if (file.is_open())
    {
        bool found = false;
        while (getline(file, encrypted))
        {
            string decrypted = decryptMessage(encrypted);
            cout << YELLOW << decrypted << RESET << endl;
            found = true;
        }
        file.close();
        if (!found)
        {
            cout << RED << "No new messages.\n"
                 << RESET;
        }
    }
    else
    {
        cout << RED << "No messages found!\n"
             << RESET;
    }

    pause(7);
}

void showMenu()
{
    cout << CYAN << "\n[ Secure Messaging Menu ]\n"
         << RESET;
    cout << MAGENTA << "Logged in as: " << currentUser << RESET << "\n\n";
    cout << "1. Send Message\n";
    cout << "2. Read Messages\n";
    cout << "3. Exit\n";
    cout << "4. Logout\n\n";
    cout << "Enter your choice: ";
}

void printBanner()
{
    cout << GREEN;
    cout << "========================================\n";
    cout << "         Secure Messaging App\n";
    cout << "========================================\n";
    cout << RESET;
}

int main()
{
    while (true)
    {
        currentUser = "";
        int option;
        clearScreen();
        printBanner();

        cout << "\n1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 2)
        {
            registerUser();
            continue;
        }
        else if (option == 3)
        {
            cout << GREEN << "Exiting... Goodbye!\n"
                 << RESET;
            pause(2);
            break;
        }
        else if (option == 1)
        {
            if (!loginUser())
            {
                cout << RED << "Login failed. Returning to main menu.\n"
                     << RESET;
                pause(2);
                continue;
            }
        }
        else
        {
            cout << RED << "Invalid choice. Try again.\n"
                 << RESET;
            pause(2);
            continue;
        }

        int choice;
        while (true)
        {
            clearScreen();
            showMenu();
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                sendMessage();
                break;
            case 2:
                readMessage();
                break;
            case 3:
                cout << GREEN << "Exiting... Goodbye!\n"
                     << RESET;
                pause(2);
                return 0;
            case 4:
                cout << YELLOW << "Logging out...\n"
                     << RESET;
                pause(2);
                break;
            default:
                cout << RED << "Invalid choice. Please try again.\n"
                     << RESET;
                pause(2);
            }

            if (choice == 4)
                break;
        }
    }

    return 0;
}
