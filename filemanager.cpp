#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>   // needed for system()
using namespace std;

//====================================================
// FileInfo Class
// Stores information about a file
//====================================================
class FileInfo
{
private:
    string fileName;

public:
    // Constructors
    FileInfo()
    {
        fileName = "";
    }

    FileInfo(string name)
    {
        fileName = name;
    }

    // Functions
    void setFileName(string name)
    {
        fileName = name;
    }

    string getFileName()
    {
        return fileName;
    }

    // Operator Overloading
    // Compares two FileInfo objects (by const reference to avoid a copy)
    bool operator==(const FileInfo &f)
    {
        return fileName == f.fileName;
    }

    // Friend function
    friend void showFileInfo(FileInfo f);

    // Friend class
    friend class FileManager;
};


//====================================================
// Friend Function
//====================================================
void showFileInfo(FileInfo f)
{
    cout << "File Name : " << f.fileName << endl;
}


//====================================================
// FileManager Class
//====================================================
class FileManager
{
private:
    FileInfo fileList[50];
    int fileCount;

    string folderList[20];
    int folderCount;

    FileInfo recycleBin[10];
    int recycleCount;

public:

    // Constructor
    FileManager()
    {
        fileCount = 0;
        folderCount = 0;
        recycleCount = 0;
        cout << "File Manager Initialized." << endl;
    }

    // Destructor
    ~FileManager()
    {
        cout << "File Manager Closed." << endl;
    }


    //================================================
    // FUNCTION OVERLOADING
    //================================================

    // Create empty file
    void createFile(string name)
    {
        ofstream file(name);

        if (file)
        {
            file.close();

            if (fileCount < 50)
            {
                fileList[fileCount] = FileInfo(name);
                fileCount++;
            }

            cout << "File created successfully." << endl;
        }
        else
        {
            cout << "Unable to create file." << endl;
        }
    }

    // Create file with content
    void createFile(string name, string content)
    {
        ofstream file(name);

        if (file)
        {
            file << content;
            file.close();

            if (fileCount < 50)
            {
                fileList[fileCount] = FileInfo(name);
                fileCount++;
            }

            cout << "File created with content successfully." << endl;
        }
        else
        {
            cout << "Unable to create file." << endl;
        }
    }


    //================================================
    // OPEN FILE
    //================================================
    void openFile()
    {
        string name;
        string line;

        cout << "Enter file name: ";
        getline(cin, name);

        ifstream file(name);

        if (!file)
        {
            cout << "File not found." << endl;
            return;
        }

        cout << "\n----- File Content -----\n";

        while (getline(file, line))
        {
            cout << line << endl;
        }

        cout << "------------------------\n";

        file.close();
    }


    //================================================
    // EDIT FILE
    //================================================
    void editFile()
    {
        string name;
        string content;

        cout << "Enter file name: ";
        getline(cin, name);

        ifstream check(name);

        if (!check)
        {
            cout << "File not found." << endl;
            return;
        }

        check.close();

        ofstream file(name, ios::app);

        cout << "Enter content to add: ";
        getline(cin, content);

        file << "\n" << content;

        file.close();

        cout << "File edited successfully." << endl;
    }


    //================================================
    // DELETE FILE
    //================================================
    void deleteFile()
    {
        string name;

        cout << "Enter file name to delete: ";
        getline(cin, name);

        ifstream check(name);

        if (!check)
        {
            cout << "File not found." << endl;
            return;
        }

        check.close();

        if (recycleCount < 10)
        {
            recycleBin[recycleCount] = FileInfo(name);
            recycleCount++;

            remove(name.c_str());

            for (int i = 0; i < fileCount; i++)
            {
                if (fileList[i] == FileInfo(name))
                {
                    for (int j = i; j < fileCount - 1; j++)
                    {
                        fileList[j] = fileList[j + 1];
                    }
                    fileCount--;
                    break;
                }
            }

            cout << "File moved to Recycle Bin." << endl;
        }
        else
        {
            cout << "Recycle Bin is full." << endl;
        }
    }


    //================================================
    // SHOW FILES
    //================================================
    void showFiles()
    {
        if (fileCount == 0)
        {
            cout << "\nNo files created yet." << endl;
            return;
        }

        cout << "\n----- Files -----\n";

        for (int i = 0; i < fileCount; i++)
        {
            showFileInfo(fileList[i]);
        }

        cout << "------------------\n";
    }


    //================================================
    // CREATE FOLDER
    //================================================
    void createFolder()
    {
        string folderName;

        cout << "Enter folder name: ";
        getline(cin, folderName);

        // Quote the name so mkdir treats spaces as part of one name
        // instead of splitting into multiple arguments
        string command = "mkdir \"" + folderName + "\"";
        system(command.c_str());

        if (folderCount < 20)
        {
            folderList[folderCount] = folderName;
            folderCount++;
        }

        cout << "Folder created successfully." << endl;
    }


    //================================================
    // OPEN FOLDER
    //================================================
    void openFolder()
    {
        string folderName;

        cout << "Enter folder name to open: ";
        getline(cin, folderName);

#ifdef _WIN32
        string command = "explorer \"" + folderName + "\"";
#else
        string command = "ls \"" + folderName + "\"";
#endif

        int result = system(command.c_str());

        if (result != 0)
        {
            cout << "Folder not found or unable to open." << endl;
        }
    }


    //================================================
    // DELETE FOLDER
    //================================================
    void deleteFolder()
    {
        string folderName;

        cout << "Enter folder name to delete: ";
        getline(cin, folderName);

#ifdef _WIN32
        string command = "rmdir /s /q \"" + folderName + "\"";
#else
        string command = "rm -r \"" + folderName + "\"";
#endif

        system(command.c_str());

        for (int i = 0; i < folderCount; i++)
        {
            if (folderList[i] == folderName)
            {
                for (int j = i; j < folderCount - 1; j++)
                {
                    folderList[j] = folderList[j + 1];
                }
                folderCount--;
                break;
            }
        }

        cout << "Folder deleted successfully." << endl;
    }


    //================================================
    // SHOW FOLDERS
    //================================================
    void showFolders()
    {
        if (folderCount == 0)
        {
            cout << "\nNo folders created yet." << endl;
            return;
        }

        cout << "\n----- Folders -----\n";

        for (int i = 0; i < folderCount; i++)
        {
            cout << i + 1 << ". " << folderList[i] << endl;
        }

        cout << "--------------------\n";
    }


    //================================================
    // SHOW RECYCLE BIN
    //================================================
    void showRecycleBin()
    {
        if (recycleCount == 0)
        {
            cout << "\nRecycle Bin is empty." << endl;
            return;
        }

        cout << "\n----- Recycle Bin -----\n";

        for (int i = 0; i < recycleCount; i++)
        {
            cout << i + 1 << ". ";
            showFileInfo(recycleBin[i]);
        }

        cout << "-----------------------\n";
    }


    //================================================
    // RESTORE FILE
    //================================================
    void restoreFile()
    {
        if (recycleCount == 0)
        {
            cout << "Recycle Bin is empty." << endl;
            return;
        }

        int choice;

        showRecycleBin();

        cout << "Enter file number to restore: ";
        cin >> choice;
        cin.ignore();   // clear the newline left behind by cin >> choice

        if (choice < 1 || choice > recycleCount)
        {
            cout << "Invalid choice." << endl;
            return;
        }

        FileInfo restored = recycleBin[choice - 1];

        ofstream file(restored.getFileName());
        file.close();

        if (fileCount < 50)
        {
            fileList[fileCount] = restored;
            fileCount++;
        }

        cout << "File restored: ";
        showFileInfo(restored);

        for (int i = choice - 1; i < recycleCount - 1; i++)
        {
            recycleBin[i] = recycleBin[i + 1];
        }

        recycleCount--;
    }


    //================================================
    // EMPTY RECYCLE BIN
    //================================================
    void emptyRecycleBin()
    {
        if (recycleCount == 0)
        {
            cout << "Recycle Bin is already empty." << endl;
            return;
        }

        recycleCount = 0;

        cout << "Recycle Bin emptied successfully." << endl;
    }


    //================================================
    // FRIEND CLASS EXAMPLE
    //================================================
    friend class FileInfo;
};


//====================================================
// MAIN FUNCTION
//====================================================
int main()
{
    FileManager fm;

    int choice;

    do
    {
        cout << "\n";
        cout << "====================================\n";
        cout << "        HARK OS - FILE MANAGER\n";
        cout << "====================================\n";

        cout << "1. Create File\n";
        cout << "2. Create File with Content\n";
        cout << "3. Open File\n";
        cout << "4. Edit File\n";
        cout << "5. Delete File\n";
        cout << "6. Show Files\n";
        cout << "7. Create Folder\n";
        cout << "8. Open Folder\n";
        cout << "9. Delete Folder\n";
        cout << "10. Show Folders\n";
        cout << "11. Show Recycle Bin\n";
        cout << "12. Restore File\n";
        cout << "13. Empty Recycle Bin\n";
        cout << "14. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();   // discard the newline left after reading the menu number,
                         // so the getline() calls below read the actual name typed next

        switch (choice)
        {
            case 1:
            {
                string name;
                cout << "Enter file name: ";
                getline(cin, name);
                fm.createFile(name);
                break;
            }

            case 2:
            {
                string name;
                string content;

                cout << "Enter file name: ";
                getline(cin, name);

                cout << "Enter content: ";
                getline(cin, content);

                fm.createFile(name, content);
                break;
            }

            case 3:
                fm.openFile();
                break;

            case 4:
                fm.editFile();
                break;

            case 5:
                fm.deleteFile();
                break;

            case 6:
                fm.showFiles();
                break;

            case 7:
                fm.createFolder();
                break;

            case 8:
                fm.openFolder();
                break;

            case 9:
                fm.deleteFolder();
                break;

            case 10:
                fm.showFolders();
                break;

            case 11:
                fm.showRecycleBin();
                break;

            case 12:
                fm.restoreFile();
                break;

            case 13:
                fm.emptyRecycleBin();
                break;

            case 14:
                cout << "\nExiting File Manager...\n";
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 14);

    return 0;
}