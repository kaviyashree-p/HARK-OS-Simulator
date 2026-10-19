#include <iostream>
#include <string>
#include <limits>
#include <exception>

using namespace std;

// Custom Exception for Empty Title
class EmptyTitleException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Note title cannot be empty!";
    }
};

// Custom Exception for Empty Content / Text Operations
class InvalidNoteInputException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Invalid input provided for note operation!";
    }
};

// Abstract Base Class for Runtime Polymorphism
class NoteOperation
{
public:
    virtual void display() = 0;              // Pure virtual function
    virtual ~NoteOperation() {}              // Virtual destructor
};

// Base Class demonstrating Inheritance
class BaseNote
{
protected:
    string category;

public:
    BaseNote()
    {
        category = "General";
    }

    void showCategory() const
    {
        cout << "Category : " << category << endl;
    }
};

// Class Template Demonstration
template <class T>
class NoteData
{
private:
    T data;

public:
    NoteData(T d) : data(d) {}

    void displayData() const
    {
        cout << "Template Data : " << data << endl;
    }
};

// Forward Declaration
class Notes;

// Friend Class
class NoteManager
{
public:
    void showNoteCount(const Notes &n);
};

// Derived Class: Implements Multiple Inheritance
class Notes : public BaseNote, public NoteOperation
{
private:
    string title;
    string content;

public:
    // Default Constructor
    Notes()
    {
        title = "Untitled";
        content = "";
    }

    // Parameterized Constructor
    Notes(const string &t, const string &c)
    {
        title = t;
        content = c;
    }

    // Virtual Destructor Override
    ~Notes() override {}

    // Runtime Polymorphism Implementation
    void display() override
    {
        viewNote();
    }

    // Inline Function
    inline bool isDeleted() const
    {
        return title.empty();
    }

    // Function Overloading - Variant 1
    void createNote()
    {
        cout << "\nEnter note title: ";
        getline(cin >> ws, title);

        if (title.empty())
            throw EmptyTitleException();

        cout << "Enter note content: ";
        getline(cin, content);
    }

    // Function Overloading - Variant 2
    void createNote(const string &initialContent)
    {
        cout << "\nEnter note title: ";
        getline(cin >> ws, title);

        if (title.empty())
            throw EmptyTitleException();

        content = initialContent;
    }

    void viewNote() const
    {
        cout << "\nTitle   : " << title << endl;
        cout << "Content : " << content << endl;
        showCategory();
    }

    void editNote()
    {
        cout << "\nCurrent title: " << title << endl;
        cout << "Enter new title (press - to keep current): ";

        string newTitle;
        getline(cin >> ws, newTitle);

        if (newTitle != "-")
        {
            if (newTitle.empty())
                throw EmptyTitleException();

            title = newTitle;
        }

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

    // Operator Overloading
    Notes operator+(const string &extraContent) const
    {
        Notes temp(title, content + " " + extraContent);
        return temp;
    }

    // Friend Declarations
    friend void displayNoteDetails(const Notes &n);
    friend class NoteManager;
};

// Friend Function Definition
void displayNoteDetails(const Notes &n)
{
    cout << "\n----- Selected Note Details -----\n";
    cout << "Title   : " << n.title << endl;
    cout << "Content : " << n.content << endl;
}

// Friend Class Member Function Definition
void NoteManager::showNoteCount(const Notes &n)
{
    if (!n.isDeleted())
        cout << "\nTotal number of files: 1" << endl;
    else
        cout << "\nTotal number of files: 0" << endl;
}

// Function Template
template <typename T>
T maximum(T a, T b)
{
    return (a > b) ? a : b;
}

int main()
{
    Notes note;
    NoteManager manager;
    NoteOperation *operation = &note; // Base class pointer for runtime polymorphism

    int choice = 0;

    do
    {
        cout << "\n================================\n";
        cout << "         HARK OS - NOTES\n";
        cout << "================================\n";
        cout << "1. Create Note\n";
        cout << "2. Create Note with Initial Content\n";
        cout << "3. Display All Notes\n";
        cout << "4. Edit Note (Add/Delete Text)\n";
        cout << "5. Append Content using + Operator\n";
        cout << "6. Display Selected Note using Friend Function\n";
        cout << "7. Show Total Number of Files using Friend Class\n";
        cout << "8. Delete Note\n";
        cout << "9. Class Template Demo\n";
        cout << "10. Function Template Demo\n";
        cout << "11. Runtime Polymorphism Demo\n";
        cout << "12. Exit Notes\n";
        cout << "================================\n";
        cout << "Enter your choice: ";

        try
        {
            if (!(cin >> choice))
                throw invalid_argument("Invalid input! Please enter a valid number.");

            switch (choice)
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
                    if (note.isDeleted())
                        cout << "\nNo notes available.\n";
                    else
                    {
                        cout << "\n========== NOTE ==========\n";
                        note.viewNote();
                    }
                    break;

                case 4:
                    if (!note.isDeleted())
                        note.editNote();
                    else
                        cout << "\nNo note available!\n";
                    break;

                case 5:
                {
                    if (!note.isDeleted())
                    {
                        string extraContent;
                        cout << "Enter content to append: ";
                        getline(cin >> ws, extraContent);

                        note = note + extraContent;
                        cout << "\nContent appended successfully!\n";
                    }
                    else
                    {
                        cout << "\nNo note available!\n";
                    }
                    break;
                }

                case 6:
                    if (!note.isDeleted())
                        displayNoteDetails(note);
                    else
                        cout << "\nNo note available!\n";
                    break;

                case 7:
                    manager.showNoteCount(note);
                    break;

                case 8:
                    if (!note.isDeleted())
                    {
                        note.deleteNote();
                        cout << "\nNote deleted successfully!\n";
                    }
                    else
                    {
                        cout << "\nNo note available!\n";
                    }
                    break;

                case 9:
                {
                    NoteData<string> textData("HARK OS Notes");
                    textData.displayData();
                    break;
                }

                case 10:
                {
                    int a, b;
                    cout << "\nEnter two numbers: ";
                    if (!(cin >> a >> b))
                        throw invalid_argument("Please enter valid integers.");

                    cout << "Maximum = " << maximum(a, b) << endl;
                    break;
                }

                case 11:
                    if (!note.isDeleted())
                    {
                        cout << "\nRuntime Polymorphism Output:\n";
                        operation->display(); // Dynamic binding resolution
                    }
                    else
                    {
                        cout << "\nNo note available!\n";
                    }
                    break;

                case 12:
                    cout << "\nExiting Notes...\n";
                    break;

                default:
                    cout << "\nInvalid choice! Please select an option from 1 to 12.\n";
            }
        }
        catch (const EmptyTitleException &e)
        {
            cout << "\nTitle Error: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "\nException: " << e.what() << endl;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

    } while (choice != 12);

    return 0;
}
