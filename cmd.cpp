#include <iostream>
#include <string>
using namespace std;


// ======================================================
// BASE CLASS - OS COMPONENT
// ======================================================

class OSComponent
{
protected:

    string componentName;

public:

    // Constructor
    OSComponent(string name)
    {
        componentName = name;
    }

    // Common function for OS components
    void displayComponent()
    {
        cout << "OS Component : "
             << componentName
             << endl;
    }

    // Destructor
    ~OSComponent()
    {
    }
};


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

    // ==================================================
    // DEFAULT CONSTRUCTOR
    // ==================================================

    File()
    {
        fileName = "";
        content = "";
    }


    // ==================================================
    // PARAMETERIZED CONSTRUCTOR
    // ==================================================

    File(string name)
    {
        fileName = name;
        content = "";
    }


    // ==================================================
    // SET FILE NAME
    // ==================================================

    void setFileName(string name)
    {
        fileName = name;
    }


    // ==================================================
    // WRITE CONTENT
    // ==================================================

    void writeContent(string data)
    {
        content = data;
    }


    // ==================================================
    // DISPLAY FILE CONTENT
    // ==================================================

    void displayContent()
    {
        cout << endl;

        cout << "File Name : "
             << fileName
             << endl;

        cout << "Content   : "
             << content
             << endl;
    }


    // ==================================================
    // GET FILE NAME
    // ==================================================

    string getFileName()
    {
        return fileName;
    }


    // ==================================================
    // OPERATOR OVERLOADING
    // ==================================================

    bool operator==(string name)
    {
        return fileName == name;
    }


    // ==================================================
    // FRIEND CLASS
    // ==================================================

    friend class CommandManager;
};


// ======================================================
// COMMAND PROMPT CLASS
// INHERITANCE
// CommandPrompt IS-A OSComponent
// ======================================================

class CommandPrompt : public OSComponent
{
private:

    string currentPath;

    string lastCommand;

    int commandCount;

    File files[20];

    int fileCount;

    bool running;


    // ==================================================
    // FRIEND FUNCTION
    // ==================================================

    friend void showStatus(CommandPrompt &obj);


    // ==================================================
    // FRIEND CLASS
    // ==================================================

    friend class CommandManager;


public:

    // ==================================================
    // CONSTRUCTOR
    // ==================================================

    CommandPrompt()
        : OSComponent("Command Prompt")
    {
        currentPath = "C:\\";

        lastCommand = "";

        commandCount = 0;

        fileCount = 0;

        running = true;

        cout << endl;

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

        cout << "DIR       - Display files"
             << endl;

        cout << "CREATE    - Create a new file"
             << endl;

        cout << "OPEN      - Open a file"
             << endl;

        cout << "WRITE     - Write into a file"
             << endl;

        cout << "DELETE    - Delete a file"
             << endl;

        cout << "PWD       - Show current path"
             << endl;

        cout << "HISTORY   - Show command count"
             << endl;

        cout << "STATUS    - Show system status"
             << endl;

        cout << "COMPONENT - Show OS component"
             << endl;

        cout << "CLS       - Clear screen"
             << endl;

        cout << "EXIT      - Exit HARK OS"
             << endl;

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


        // HELP

        if(command == "HELP" ||
           command == "help")
        {
            help();
        }


        // DIR

        else if(command == "DIR" ||
                command == "dir")
        {
            dir();
        }


        // CREATE

        else if(command == "CREATE" ||
                command == "create")
        {
            createFile();
        }


        // OPEN

        else if(command == "OPEN" ||
                command == "open")
        {
            openFile();
        }


        // WRITE

        else if(command == "WRITE" ||
                command == "write")
        {
            writeFile();
        }


        // DELETE

        else if(command == "DELETE" ||
                command == "delete")
        {
            deleteFile();
        }


        // PWD

        else if(command == "PWD" ||
                command == "pwd")
        {
            pwd();
        }


        // HISTORY

        else if(command == "HISTORY" ||
                command == "history")
        {
            history();
        }


        // STATUS

        else if(command == "STATUS" ||
                command == "status")
        {
            showStatus(*this);
        }


        // COMPONENT
        // INHERITED FUNCTION

        else if(command == "COMPONENT" ||
                command == "component")
        {
            displayComponent();
        }


        // CLEAR SCREEN

        else if(command == "CLS" ||
                command == "cls")
        {
            clearScreen();
        }


        // EXIT

        else if(command == "EXIT" ||
                command == "exit")
        {
            running = false;

            cout << "Exiting HARK OS..."
                 << endl;
        }


        // UNKNOWN COMMAND

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


        // Inherited function from OSComponent

        displayComponent();


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