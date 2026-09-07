#include <iostream>
#include <string>
using namespace std;

class Notes;

// Friend Class
class NoteManager
{
public:
    void showNoteCount(Notes &n);
};

class Notes
{
private:
    string title;
    string content;

public:
    Notes()
    {
        title = "Untitled";
        content = "";
    }

    // Parameterized Constructor
    Notes(string t, string c)
    {
        title = t;
        content = c;
    }

    ~Notes()
    {
    }

    // Function Overloading
    void createNote()
    {
        cout << "\nEnter note title: ";
        getline(cin >> ws, title);
        cout << "Enter note content: ";
        getline(cin, content);
    }

    void createNote(string initialContent)
    {
        cout << "\nEnter note title: ";
        getline(cin >> ws, title);
        content = initialContent;
    }

    void viewNote()
    {
        cout << "\nTitle   : " << title << endl;
        cout << "Content : " << content << endl;
    }

    void editNote()
    {
        cout << "\nCurrent title: " << title << endl;
        cout << "Enter new title (press - to keep current): ";
        string newTitle;
        getline(cin >> ws, newTitle);

        if (newTitle != "-")
            title = newTitle;

        cout << "Current content: " << content << endl;
        cout << "Enter word/text to delete (press - to skip): ";
        string textToDelete;
        getline(cin, textToDelete);

        if (textToDelete != "-")
        {
            size_t position = content.find(textToDelete);

            if (position != string::npos)
            {
                content.erase(position, textToDelete.length());
                cout << "\nSelected text deleted successfully!\n";
            }
            else
            {
                cout << "\nText not found in the note.\n";
            }
        }

        cout << "Enter text to add (press - to skip): ";
        string textToAdd;
        getline(cin, textToAdd);

        if (textToAdd != "-")
        {
            content += " " + textToAdd;
            cout << "Text added successfully!\n";
        }

        cout << "\nNote edited successfully!\n";
    }

    void addContent()
    {
        string extraContent;
        cout << "\nEnter content to add: ";
        getline(cin >> ws, extraContent);
        content += " " + extraContent;
        cout << "\nContent added successfully!\n";
    }

    void deleteNote()
    {
        title = "";
        content = "";
    }

    bool isDeleted()
    {
        return title == "";
    }

    // Operator Overloading
    Notes operator+(string extraContent)
    {
        Notes temp(title, content + " " + extraContent);
        return temp;
    }

    friend void displayNoteDetails(Notes &n);
    friend class NoteManager;
};

// Friend Function - displays private data of one selected note
void displayNoteDetails(Notes &n)
{
    cout << "\n----- Selected Note Details -----\n";
    cout << "Title   : " << n.title << endl;
    cout << "Content : " << n.content << endl;
}

    // Friend Class - displays the number of files
void NoteManager::showNoteCount(Notes &n)
{
    if (!n.isDeleted())
        cout << "\nTotal number of files: 1" << endl;
    else
        cout << "\nTotal number of files: 0" << endl;
}

int main()
{
    Notes note;
    NoteManager manager;
    int choice;

    do
    {
        cout << "\n\n================================\n";
        cout << "          HARK OS - NOTES\n";
        cout << "================================\n";
        cout << "1. Create Note\n";
        cout << "2. Create Note with Initial Content\n";
        cout << "3. Display All Notes\n";
        cout << "4. Edit Note (Add/Delete Text)\n";
        cout << "5. Append Content using + Operator\n";
        cout << "6. Display Selected Note using Friend Function\n";
        cout << "7. Show Total Number of Files using Friend Class\n";
        cout << "8. Delete Note\n";
        cout << "9. Exit Notes\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                note.createNote();
                cout << "\nNote created successfully!\n";
                break;

            case 2:
            {
                string initialContent;
                cout << "\nEnter initial content: ";
                getline(cin >> ws, initialContent);

                note.createNote(initialContent);
                cout << "\nNote created with initial content!\n";
                break;
            }

            case 3:
            {
                if (note.isDeleted())
                {
                    cout << "\nNo notes available.\n";
                    break;
                }

                cout << "\n========== NOTE ==========\n";
                note.viewNote();
                break;
            }

            case 4:
            {
                if (!note.isDeleted())
                    note.editNote();
                else
                    cout << "\nNo note available!\n";
                break;
            }

            case 5:
            {
                string extraContent;
                if (!note.isDeleted())
                {
                    cout << "Enter content to append: ";
                    getline(cin >> ws, extraContent);
                    note = note + extraContent;
                    cout << "\nContent appended successfully!\n";
                }
                else
                    cout << "\nNo note available!\n";
                break;
            }

            case 6:
            {
                if (!note.isDeleted())
                    displayNoteDetails(note);
                else
                    cout << "\nNo note available!\n";
                break;
            }

            case 7:
                manager.showNoteCount(note);
                break;

            case 8:
            {
                if (!note.isDeleted())
                {
                    note.deleteNote();
                    cout << "\nNote deleted successfully!\n";
                }
                else
                    cout << "\nNo note available!\n";
                break;
            }

            case 9:
                cout << "\nExiting Notes...\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while(choice != 9);

    return 0;
}

