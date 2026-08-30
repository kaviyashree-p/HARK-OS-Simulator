#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// ============================================================
// FILE CLASS
// ============================================================

class File
{
private:
    string fileName;
    string content;

public:

    File(string name)
    {
        fileName = name;
        content = "";
    }

    string getName()
    {
        return fileName;
    }

    void writeContent(string data)
    {
        content = data;
    }

    void appendContent(string data)
    {
        content += data;
    }

    void displayContent()
    {
        if (content.empty())
        {
            cout << "[File is empty]" << endl;
        }
        else
        {
            cout << content << endl;
        }
    }
};


// ============================================================
// DIRECTORY CLASS
// ============================================================

class Directory
{
private:
    string directoryName;

    vector<Directory*> subDirectories;
    vector<File*> files;

public:

    Directory(string name)
    {
        directoryName = name;
    }

    ~Directory()
    {
        for (auto dir : subDirectories)
            delete dir;

        for (auto file : files)
            delete file;
    }

    string getName()
    {
        return directoryName;
    }

    // --------------------------------------------------------
    // FIND DIRECTORY
    // --------------------------------------------------------

    Directory* findDirectory(string name)
    {
        for (auto dir : subDirectories)
        {
            if (dir->getName() == name)
                return dir;
        }

        return nullptr;
    }

    // --------------------------------------------------------
    // FIND FILE
    // --------------------------------------------------------

    File* findFile(string name)
    {
        for (auto file : files)
        {
            if (file->getName() == name)
                return file;
        }

        return nullptr;
    }

    // --------------------------------------------------------
    // CREATE DIRECTORY
    // --------------------------------------------------------

    bool createDirectory(string name)
    {
        if (findDirectory(name) != nullptr)
        {
            return false;
        }

        if (findFile(name) != nullptr)
        {
            return false;
        }

        Directory* newDir = new Directory(name);

        subDirectories.push_back(newDir);

        return true;
    }

    // --------------------------------------------------------
    // CREATE FILE
    // --------------------------------------------------------

    bool createFile(string name)
    {
        if (findFile(name) != nullptr)
        {
            return false;
        }

        if (findDirectory(name) != nullptr)
        {
            return false;
        }

        File* newFile = new File(name);

        files.push_back(newFile);

        return true;
    }

    // --------------------------------------------------------
    // DELETE FILE
    // --------------------------------------------------------

    bool deleteFile(string name)
    {
        for (int i = 0; i < files.size(); i++)
        {
            if (files[i]->getName() == name)
            {
                delete files[i];

                files.erase(files.begin() + i);

                return true;
            }
        }

        return false;
    }

    // --------------------------------------------------------
    // DISPLAY DIRECTORY CONTENT
    // --------------------------------------------------------

    void displayContents()
    {
        cout << endl;

        cout << "Directory: " << directoryName << endl;

        cout << "----------------------------------------" << endl;

        if (subDirectories.empty() && files.empty())
        {
            cout << "[Directory is empty]" << endl;
        }

        // Display folders

        for (auto dir : subDirectories)
        {
            cout << "<DIR>   " << dir->getName() << endl;
        }

        // Display files

        for (auto file : files)
        {
            cout << "        " << file->getName() << endl;
        }

        cout << "----------------------------------------" << endl;
    }

    vector<Directory*>& getDirectories()
    {
        return subDirectories;
    }

    vector<File*>& getFiles()
    {
        return files;
    }
};


// ============================================================
// COMMAND PROMPT CLASS
// ============================================================

class CommandPrompt
{
private:

    Directory* root;

    Directory* currentDirectory;

    string currentPath;

    vector<string> history;

    bool running;

public:

    // ========================================================
    // CONSTRUCTOR
    // ========================================================

    CommandPrompt()
    {
        root = new Directory("HARK");

        currentDirectory = root;

        currentPath = "C:\\";

        running = true;

        cout << "HARK Command Prompt initialized." << endl;
    }


    // ========================================================
    // DESTRUCTOR
    // ========================================================

    ~CommandPrompt()
    {
        delete root;

        cout << "\nCommand Prompt closed." << endl;
    }


    // ========================================================
    // SHOW PROMPT
    // ========================================================

    void showPrompt()
    {
        cout << "\nHARK " << currentPath << "> ";
    }


    // ========================================================
    // SHOW HELP
    // ========================================================

    void showHelp()
    {
        cout << endl;

        cout << "==================================================" << endl;
        cout << "             HARK OS COMMAND HELP" << endl;
        cout << "==================================================" << endl;

        cout << "DIR                    - Display files and folders" << endl;
        cout << "MKDIR <name>           - Create a directory" << endl;
        cout << "CREATE <name>          - Create a file" << endl;
        cout << "WRITE <file>           - Write content to file" << endl;
        cout << "OPEN <file>            - Open and display a file" << endl;
        cout << "DELETE <file>          - Delete a file" << endl;
        cout << "CD <folder>            - Enter a directory" << endl;
        cout << "CD ..                  - Go to parent directory" << endl;
        cout << "PWD                    - Show current directory" << endl;
        cout << "CLS                    - Clear screen" << endl;
        cout << "HISTORY                - Show command history" << endl;
        cout << "HELP                   - Show available commands" << endl;
        cout << "EXIT                   - Exit command prompt" << endl;

        cout << "==================================================" << endl;
    }


    // ========================================================
    // CLEAR SCREEN
    // ========================================================

    void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }


    // ========================================================
    // SHOW HISTORY
    // ========================================================

    void showHistory()
    {
        cout << endl;

        cout << "---------- COMMAND HISTORY ----------" << endl;

        if (history.empty())
        {
            cout << "No commands executed." << endl;
            return;
        }

        for (int i = 0; i < history.size(); i++)
        {
            cout << i + 1 << ". " << history[i] << endl;
        }

        cout << "-------------------------------------" << endl;
    }


    // ========================================================
    // DIR COMMAND
    // ========================================================

    void dirCommand()
    {
        currentDirectory->displayContents();
    }


    // ========================================================
    // MKDIR COMMAND
    // ========================================================

    void mkdirCommand(string name)
    {
        if (name.empty())
        {
            cout << "Error: Directory name required." << endl;
            return;
        }

        if (currentDirectory->createDirectory(name))
        {
            cout << "Directory created successfully: "
                 << name << endl;
        }
        else
        {
            cout << "Error: Directory or file already exists." << endl;
        }
    }


    // ========================================================
    // CREATE COMMAND
    // ========================================================

    void createCommand(string name)
    {
        if (name.empty())
        {
            cout << "Error: File name required." << endl;
            return;
        }

        if (currentDirectory->createFile(name))
        {
            cout << "File created successfully: "
                 << name << endl;
        }
        else
        {
            cout << "Error: File or directory already exists." << endl;
        }
    }


    // ========================================================
    // WRITE COMMAND
    // ========================================================

    void writeCommand(string fileName)
    {
        if (fileName.empty())
        {
            cout << "Error: File name required." << endl;
            return;
        }

        File* file = currentDirectory->findFile(fileName);

        if (file == nullptr)
        {
            cout << "Error: File not found." << endl;
            return;
        }

        cout << "Enter content for " << fileName << endl;
        cout << "(Type END on a new line to finish)" << endl;

        string line;
        string content = "";

        while (true)
        {
            getline(cin, line);

            if (line == "END")
                break;

            content += line;
            content += "\n";
        }

        file->writeContent(content);

        cout << "File saved successfully." << endl;
    }


    // ========================================================
    // OPEN COMMAND
    // ========================================================

    void openCommand(string fileName)
    {
        if (fileName.empty())
        {
            cout << "Error: File name required." << endl;
            return;
        }

        File* file = currentDirectory->findFile(fileName);

        if (file == nullptr)
        {
            cout << "Error: File not found." << endl;
            return;
        }

        cout << endl;

        cout << "========== " << fileName << " ==========" << endl;

        file->displayContent();

        cout << "=================================" << endl;
    }


    // ========================================================
    // DELETE COMMAND
    // ========================================================

    void deleteCommand(string fileName)
    {
        if (fileName.empty())
        {
            cout << "Error: File name required." << endl;
            return;
        }

        if (currentDirectory->deleteFile(fileName))
        {
            cout << "File deleted successfully: "
                 << fileName << endl;
        }
        else
        {
            cout << "Error: File not found." << endl;
        }
    }


    // ========================================================
    // CD COMMAND
    // ========================================================

    void cdCommand(string folderName)
    {
        if (folderName.empty())
        {
            cout << "Error: Folder name required." << endl;
            return;
        }


        // -----------------------------------------------
        // GO TO PARENT DIRECTORY
        // -----------------------------------------------

        if (folderName == "..")
        {
            if (currentDirectory == root)
            {
                cout << "Already at root directory." << endl;
                return;
            }

            /*
               Find parent directory starting from root.
            */

            Directory* parent = findParent(root, currentDirectory);

            if (parent != nullptr)
            {
                currentDirectory = parent;

                removeLastPath();

                cout << "Moved to: " << currentPath << endl;
            }

            return;
        }


        // -----------------------------------------------
        // GO INTO SUBDIRECTORY
        // -----------------------------------------------

        Directory* target =
            currentDirectory->findDirectory(folderName);

        if (target == nullptr)
        {
            cout << "Error: Directory not found." << endl;
            return;
        }

        currentDirectory = target;

        if (currentPath != "C:\\")
            currentPath += "\\";

        currentPath += folderName;

        cout << "Changed directory to: "
             << currentPath << endl;
    }


    // ========================================================
    // FIND PARENT DIRECTORY
    // ========================================================

    Directory* findParent(Directory* parent,
                          Directory* child)
    {
        vector<Directory*>& dirs =
            parent->getDirectories();

        for (auto dir : dirs)
        {
            if (dir == child)
            {
                return parent;
            }

            Directory* result =
                findParent(dir, child);

            if (result != nullptr)
            {
                return result;
            }
        }

        return nullptr;
    }


    // ========================================================
    // REMOVE LAST PATH
    // ========================================================

    void removeLastPath()
    {
        if (currentPath == "C:\\")
            return;

        size_t position =
            currentPath.find_last_of("\\");

        if (position == 2)
        {
            currentPath = "C:\\";
        }
        else
        {
            currentPath =
                currentPath.substr(0, position);
        }
    }


    // ========================================================
    // PWD COMMAND
    // ========================================================

    void pwdCommand()
    {
        cout << "Current directory: "
             << currentPath << endl;
    }


    // ========================================================
    // EXECUTE COMMAND
    // ========================================================

    void executeCommand(string command)
    {
        if (command.empty())
            return;


        // Store command in history

        history.push_back(command);


        // Convert command to uppercase for comparison

        string originalCommand = command;

        stringstream ss(command);

        string operation;

        ss >> operation;


        // Convert operation to uppercase

        transform(operation.begin(),
                  operation.end(),
                  operation.begin(),
                  ::toupper);


        // ====================================================
        // HELP
        // ====================================================

        if (operation == "HELP")
        {
            showHelp();
        }


        // ====================================================
        // DIR
        // ====================================================

        else if (operation == "DIR")
        {
            dirCommand();
        }


        // ====================================================
        // MKDIR
        // ====================================================

        else if (operation == "MKDIR")
        {
            string name;

            ss >> name;

            mkdirCommand(name);
        }


        // ====================================================
        // CREATE
        // ====================================================

        else if (operation == "CREATE")
        {
            string name;

            ss >> name;

            createCommand(name);
        }


        // ====================================================
        // WRITE
        // ====================================================

        else if (operation == "WRITE")
        {
            string name;

            ss >> name;

            writeCommand(name);
        }


        // ====================================================
        // OPEN
        // ====================================================

        else if (operation == "OPEN")
        {
            string name;

            ss >> name;

            openCommand(name);
        }


        // ====================================================
        // DELETE
        // ====================================================

        else if (operation == "DELETE")
        {
            string name;

            ss >> name;

            deleteCommand(name);
        }


        // ====================================================
        // CD
        // ====================================================

        else if (operation == "CD")
        {
            string folder;

            ss >> folder;

            cdCommand(folder);
        }


        // ====================================================
        // PWD
        // ====================================================

        else if (operation == "PWD")
        {
            pwdCommand();
        }


        // ====================================================
        // CLS
        // ====================================================

        else if (operation == "CLS")
        {
            clearScreen();
        }


        // ====================================================
        // HISTORY
        // ====================================================

        else if (operation == "HISTORY")
        {
            showHistory();
        }


        // ====================================================
        // EXIT
        // ====================================================

        else if (operation == "EXIT")
        {
            running = false;

            cout << "Exiting HARK Command Prompt..." << endl;
        }


        // ====================================================
        // UNKNOWN COMMAND
        // ====================================================

        else
        {
            cout << "'" << originalCommand
                 << "' is not recognized as a HARK command."
                 << endl;

            cout << "Type HELP to see available commands."
                 << endl;
        }
    }


    // ========================================================
    // START COMMAND PROMPT
    // ========================================================

    void start()
    {
        string command;

        cout << endl;

        cout << "==================================================" << endl;
        cout << "             HARK OS COMMAND PROMPT" << endl;
        cout << "==================================================" << endl;

        cout << "Type HELP to see available commands." << endl;


        while (running)
        {
            showPrompt();

            getline(cin, command);

            executeCommand(command);
        }
    }
};


// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    CommandPrompt cmd;

    cmd.start();

    return 0;
}