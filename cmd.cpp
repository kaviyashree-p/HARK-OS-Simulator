#include <iostream>
#include <string>
using namespace std;


// ======================================================
// FORWARD DECLARATION
// ======================================================

class CommandPrompt;
class CommandManager;


// ======================================================
// FRIEND FUNCTION DECLARATION
// ======================================================

void showStatus(CommandPrompt &obj);


// ======================================================
// BASE CLASS
// INHERITANCE
// ======================================================

class OSComponent
{
protected:

    string componentName;

public:

    // Parameterized Constructor
    OSComponent(string name)
    {
        componentName = name;
    }


    // INLINE FUNCTION
    inline void displayComponent()
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
    // DISPLAY CONTENT
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
// CLASS TEMPLATE
// GENERIC STORAGE
// ======================================================

template <class T>
class Storage
{
private:

    T data[20];

    int count;


public:

    // ==================================================
    // CONSTRUCTOR
    // ==================================================

    Storage()
    {
        count = 0;
    }


    // ==================================================
    // ADD ITEM
    // ==================================================

    void add(T item)
    {
        if(count < 20)
        {
            data[count] = item;

            count++;
        }
    }


    // ==================================================
    // GET ITEM
    // ==================================================

    T& get(int index)
    {
        return data[index];
    }


    // ==================================================
    // GET SIZE
    // ==================================================

    int size()
    {
        return count;
    }


    // ==================================================
    // REMOVE ITEM
    // ==================================================

    void remove(int index)
    {
        if(index >= 0 && index < count)
        {
            for(int i = index;
                i < count - 1;
                i++)
            {
                data[i] = data[i + 1];
            }

            count--;
        }
    }
};


// ======================================================
// FUNCTION TEMPLATE
// ======================================================

template <class T>
void addItem(Storage<T>& storage, T item)
{
    storage.add(item);
}


// ======================================================
// COMMAND PROMPT CLASS
// INHERITANCE
// ======================================================

class CommandPrompt : public OSComponent
{
private:

    string currentPath;

    string lastCommand;

    int commandCount;

    // CLASS TEMPLATE
    Storage<File> files;

    // CLASS TEMPLATE
    Storage<string> commandHistory;

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

        cout << "HISTORY   - Show command history" << endl;

        cout << "STATUS    - Show system status" << endl;

        cout << "COMPONENT - Show OS component" << endl;

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

        cout << endl;

        cout << "Directory of "
             << currentPath
             << endl;

        cout << "-----------------------------------"
             << endl;


        if(files.size() == 0)
        {
            cout << "No files found."
                 << endl;
        }
        else
        {
            for(int i = 0;
                i < files.size();
                i++)
            {
                cout << files.get(i).getFileName()
                     << endl;
            }
        }


        cout << "-----------------------------------"
             << endl;
    }


    // ==================================================
    // CREATE FILE
    // FUNCTION OVERLOADING - VERSION 1
    // ==================================================

    void createFile(string name)
    {
        lastCommand = "CREATE";


        if(files.size() >= 20)
        {
            cout << "File storage is full!"
                 << endl;

            return;
        }


        // Check whether file already exists

        for(int i = 0;
            i < files.size();
            i++)
        {
            if(files.get(i) == name)
            {
                cout << "File already exists!"
                     << endl;

                return;
            }
        }


        File newFile(name);

        // FUNCTION TEMPLATE
        addItem(files, newFile);


        cout << "File created successfully!"
             << endl;

        cout << "File Name: "
             << name
             << endl;
    }


    // ==================================================
    // FUNCTION OVERLOADING
    // VERSION 2
    // ==================================================

    void createFile()
    {
        string name;

        cout << "Enter file name: ";

        cin >> name;

        createFile(name);
    }


    // ==================================================
    // FUNCTION OVERLOADING
    // VERSION 3
    // ==================================================

    void createFile(string name, string data)
    {
        createFile(name);

        if(files.size() > 0)
        {
            files.get(files.size() - 1)
                 .writeContent(data);
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


        for(int i = 0;
            i < files.size();
            i++)
        {
            if(files.get(i) == name)
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


        files.get(position)
             .writeContent(data);


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


        for(int i = 0;
            i < files.size();
            i++)
        {
            if(files.get(i) == name)
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


        files.get(position)
             .displayContent();
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


        for(int i = 0;
            i < files.size();
            i++)
        {
            if(files.get(i) == name)
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


        // CLASS TEMPLATE REMOVE FUNCTION

        files.remove(position);


        cout << "File deleted successfully!"
             << endl;
    }


    // ==================================================
    // PWD
    // ==================================================

    void pwd()
    {
        lastCommand = "PWD";

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

        cout << "========== COMMAND HISTORY =========="
             << endl;


        if(commandHistory.size() == 0)
        {
            cout << "No commands executed."
                 << endl;
        }
        else
        {
            for(int i = 0;
                i < commandHistory.size();
                i++)
            {
                cout << i + 1
                     << ". "
                     << commandHistory.get(i)
                     << endl;
            }
        }


        cout << "====================================="
             << endl;
    }


    // ==================================================
    // CLEAR SCREEN
    // ==================================================

    void clearScreen()
    {
        lastCommand = "CLS";


        for(int i = 0;
            i < 30;
            i++)
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


        // ==================================================
        // FUNCTION TEMPLATE
        // Add command into generic storage
        // ==================================================

        addItem(commandHistory, command);


        // ==================================================
        // COMMAND CHECKING
        // ==================================================

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


        else if(command == "COMPONENT" ||
                command == "component")
        {
            displayComponent();
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

    cout << "OS Component : "
         << obj.componentName
         << endl;

    cout << "Current Path : "
         << obj.currentPath
         << endl;

    cout << "Last Command : "
         << obj.lastCommand
         << endl;

    cout << "File Count   : "
         << obj.files.size()
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
             << obj.files.size()
             << endl;

        cout << "Commands: "
             << obj.commandCount
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