#include <iostream>
#include <string>
using namespace std;


// ======================================================
// FORWARD DECLARATION
// ======================================================

class CommandPrompt;
class CommandManager;


// ======================================================
// FRIEND FUNCTION
// ======================================================

void showStatus(CommandPrompt &obj);


// ======================================================
// FILE CLASS
// ======================================================

class File
{
private:

    string fileName;
    string content;

public:

    // Constructor
    File()
    {
        fileName = "";
        content = "";
    }


    // Parameterized Constructor
    File(string name)
    {
        fileName = name;
        content = "";
    }


    // Function to set file name
    void setFileName(string name)
    {
        fileName = name;
    }


    // Function to write content
    void writeContent(string data)
    {
        content = data;
    }


    // Display file content
    void displayContent()
    {
        cout << endl;
        cout << "File Name : " << fileName << endl;
        cout << "Content   : " << content << endl;
    }


    // Get file name
    string getFileName()
    {
        return fileName;
    }


    // Operator overloading
    bool operator==(string name)
    {
        return fileName == name;
    }


    // Friend class
    friend class CommandManager;
};


// ======================================================
// COMMAND PROMPT CLASS
// ======================================================

class CommandPrompt
{
private:

    string currentPath;

    string lastCommand;

    int commandCount;

    File files[20];

    int fileCount;

    bool running;


    // Friend function
    friend void showStatus(CommandPrompt &obj);


    // Friend class
    friend class CommandManager;


public:

    // ==================================================
    // CONSTRUCTOR
    // ==================================================

    CommandPrompt()
    {
        currentPath = "C:\\";

        lastCommand = "";

        commandCount = 0;

        fileCount = 0;

        running = true;

        cout << "HARK OS Command Prompt Started!"
             << endl;
    }


    // ==================================================
    // DESTRUCTOR
    // ==================================================

    ~CommandPrompt()
    {
        cout << endl;
        cout << "HARK OS Command Prompt Closed!"
             << endl;
    }


    // ==================================================
    // HELP
    // ==================================================

    void help()
    {
        cout << endl;

        cout << "========== HARK COMMANDS =========="
             << endl;

        cout << "DIR       - Display files" << endl;

        cout << "CREATE    - Create a new file" << endl;

        cout << "OPEN      - Open a file" << endl;

        cout << "WRITE     - Write into a file" << endl;

        cout << "DELETE    - Delete a file" << endl;

        cout << "PWD       - Show current path" << endl;

        cout << "HISTORY   - Show command count" << endl;

        cout << "STATUS    - Show system status" << endl;

        cout << "CLS       - Clear screen" << endl;

        cout << "EXIT      - Exit HARK OS" << endl;

        cout << "==================================="
             << endl;
    }


    // ==================================================
    // DIR
    // ==================================================

    void dir()
    {
        lastCommand = "DIR";

        commandCount++;

        cout << endl;

        cout << "Directory of "
             << currentPath
             << endl;

        cout << "-----------------------------------"
             << endl;


        if(fileCount == 0)
        {
            cout << "No files found."
                 << endl;
        }
        else
        {
            for(int i = 0; i < fileCount; i++)
            {
                cout << files[i].getFileName()
                     << endl;
            }
        }


        cout << "-----------------------------------"
             << endl;
    }


    // ==================================================
    // CREATE FILE
    // ==================================================

    void createFile(string name)
    {
        lastCommand = "CREATE";

        commandCount++;


        if(fileCount >= 20)
        {
            cout << "File storage is full!"
                 << endl;

            return;
        }


        // Check whether file already exists

        for(int i = 0; i < fileCount; i++)
        {
            if(files[i] == name)
            {
                cout << "File already exists!"
                     << endl;

                return;
            }
        }


        files[fileCount].setFileName(name);

        fileCount++;


        cout << "File created successfully!"
             << endl;

        cout << "File Name: "
             << name
             << endl;
    }


    // ==================================================
    // FUNCTION OVERLOADING
    // ==================================================

    // Version 1
    void createFile()
    {
        string name;

        cout << "Enter file name: ";

        cin >> name;

        createFile(name);
    }


    // Version 2
    void createFile(string name, string data)
    {
        createFile(name);

        if(fileCount > 0)
        {
            files[fileCount - 1].writeContent(data);
        }
    }


    // ==================================================
    // WRITE FILE
    // ==================================================

    void writeFile()
    {
        string name;

        cout << "Enter file name: ";

        cin >> name;


        int position = -1;


        for(int i = 0; i < fileCount; i++)
        {
            if(files[i] == name)
            {
                position = i;
                break;
            }
        }


        if(position == -1)
        {
            cout << "File not found!"
                 << endl;

            return;
        }


        string data;

        cout << "Enter content: ";

        cin.ignore();

        getline(cin, data);


        files[position].writeContent(data);


        cout << "Content saved successfully!"
             << endl;
    }


    // ==================================================
    // OPEN FILE
    // ==================================================

    void openFile()
    {
        string name;

        cout << "Enter file name: ";

        cin >> name;


        int position = -1;


        for(int i = 0; i < fileCount; i++)
        {
            if(files[i] == name)
            {
                position = i;
                break;
            }
        }


        if(position == -1)
        {
            cout << "File not found!"
                 << endl;

            return;
        }


        files[position].displayContent();
    }


    // ==================================================
    // DELETE FILE
    // ==================================================

    void deleteFile()
    {
        string name;

        cout << "Enter file name: ";

        cin >> name;


        int position = -1;


        for(int i = 0; i < fileCount; i++)
        {
            if(files[i] == name)
            {
                position = i;
                break;
            }
        }


        if(position == -1)
        {
            cout << "File not found!"
                 << endl;

            return;
        }


        // Shift files to left

        for(int i = position;
            i < fileCount - 1;
            i++)
        {
            files[i] = files[i + 1];
        }


        fileCount--;


        cout << "File deleted successfully!"
             << endl;
    }


    // ==================================================
    // PWD
    // ==================================================

    void pwd()
    {
        lastCommand = "PWD";

        commandCount++;

        cout << "Current Path: "
             << currentPath
             << endl;
    }


    // ==================================================
    // HISTORY
    // ==================================================

    void history()
    {
        cout << endl;

        cout << "Commands executed: "
             << commandCount
             << endl;
    }


    // ==================================================
    // CLEAR SCREEN
    // ==================================================

    void clearScreen()
    {
        lastCommand = "CLS";

        commandCount++;


        for(int i = 0; i < 30; i++)
        {
            cout << endl;
        }
    }


    // ==================================================
    // EXECUTE COMMAND
    // ==================================================

    void executeCommand(string command)
    {
        lastCommand = command;

        commandCount++;


        // Convert command to uppercase manually

        if(command == "HELP" ||
           command == "help")
        {
            help();
        }


        else if(command == "DIR" ||
                command == "dir")
        {
            dir();
        }


        else if(command == "CREATE" ||
                command == "create")
        {
            createFile();
        }


        else if(command == "OPEN" ||
                command == "open")
        {
            openFile();
        }


        else if(command == "WRITE" ||
                command == "write")
        {
            writeFile();
        }


        else if(command == "DELETE" ||
                command == "delete")
        {
            deleteFile();
        }


        else if(command == "PWD" ||
                command == "pwd")
        {
            pwd();
        }


        else if(command == "HISTORY" ||
                command == "history")
        {
            history();
        }


        else if(command == "STATUS" ||
                command == "status")
        {
            showStatus(*this);
        }


        else if(command == "CLS" ||
                command == "cls")
        {
            clearScreen();
        }


        else if(command == "EXIT" ||
                command == "exit")
        {
            running = false;

            cout << "Exiting HARK OS..."
                 << endl;
        }


        else
        {
            cout << "Unknown command!"
                 << endl;

            cout << "Type HELP to see available commands."
                 << endl;
        }
    }


    // ==================================================
    // START COMMAND PROMPT
    // ==================================================

    void start()
    {
        string command;


        while(running)
        {
            cout << endl;

            cout << "HARK "
                 << currentPath
                 << "> ";


            // Get command from USER

            cin >> command;


            // Execute command

            executeCommand(command);
        }
    }
};


// ======================================================
// FRIEND FUNCTION
// ======================================================

void showStatus(CommandPrompt &obj)
{
    cout << endl;

    cout << "========== HARK STATUS =========="
         << endl;

    cout << "Current Path : "
         << obj.currentPath
         << endl;

    cout << "Last Command : "
         << obj.lastCommand
         << endl;

    cout << "File Count   : "
         << obj.fileCount
         << endl;

    cout << "Commands     : "
         << obj.commandCount
         << endl;

    cout << "================================="
         << endl;
}


// ======================================================
// FRIEND CLASS
// ======================================================

class CommandManager
{
public:

    void display(CommandPrompt &obj)
    {
        cout << endl;

        cout << "====== COMMAND MANAGER ======"
             << endl;

        cout << "Path : "
             << obj.currentPath
             << endl;

        cout << "Files: "
             << obj.fileCount
             << endl;

        cout << "============================="
             << endl;
    }
};


// ======================================================
// MAIN
// ======================================================

int main()
{
    // Object creation

    CommandPrompt cmd;


    // Start dynamic command prompt

    cmd.start();


    return 0;
}