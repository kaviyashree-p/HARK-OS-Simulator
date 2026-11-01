#include <iostream>
#include <fstream>      // File handling: ifstream, ofstream, fstream
#include <iomanip>      // Formatted I/O: setw, setfill, left
#include <string>
#include <vector>       // STL: vector
#include <list>         // STL: list
#include <map>          // STL: map
#include <limits>
#include <exception>
#include <stdexcept>
#include <cctype>

using namespace std;

// ============================================================
//  Custom Exceptions
// ============================================================
class EmptyTitleException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Note title cannot be empty!";
    }
};

class InvalidNoteInputException : public exception
{
private:
    string message;

public:
    InvalidNoteInputException(const string &m = "Invalid input provided for note operation!")
        : message(m) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// ============================================================
//  Abstract Base Class (Runtime Polymorphism)
// ============================================================
class NoteOperation
{
public:
    virtual void display() = 0;
    virtual ~NoteOperation() {}
};

// ============================================================
//  Base Class (Inheritance)
// ============================================================
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

// ============================================================
//  Class Template
// ============================================================
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

// Forward declaration + STL container type used to store all notes
// (map: unique, sorted keys -> each note gets a unique ID)
class Notes;
typedef map<int, Notes> NoteMap;

// ============================================================
//  Friend Class (declared here, defined after Notes)
// ============================================================
class NoteManager
{
public:
    void showNoteCount(const NoteMap &notes) const;
    void displayTable(const NoteMap &notes) const;
    vector<int> searchNotes(const NoteMap &notes, const string &keyword) const;
    int saveToFile(const NoteMap &notes, const string &filename) const;
    int loadFromFile(NoteMap &notes, int &nextId, const string &filename) const;
};

// ============================================================
//  Notes: Multiple Inheritance
// ============================================================
class Notes : public BaseNote, public NoteOperation
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

    Notes(const string &t, const string &c)
    {
        title = t;
        content = c;
    }

    ~Notes() override {}

    // Runtime polymorphism implementation
    void display() override
    {
        viewNote();
    }

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

    // Friend declarations
    friend void displayNoteDetails(const Notes &n);
    friend class NoteManager;
};

// ============================================================
//  Friend Function
// ============================================================
void displayNoteDetails(const Notes &n)
{
    cout << "\n----- Selected Note Details -----\n";
    cout << "Title   : " << n.title << endl;
    cout << "Content : " << n.content << endl;
}

// ============================================================
//  Helper functions (string handling)
// ============================================================
string toLowerCase(string s)
{
    for (size_t i = 0; i < s.length(); i++)
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    return s;
}

// Shortens long text for table display using substr() and append()
string shorten(const string &s, size_t maxLen)
{
    if (s.length() <= maxLen)
        return s;

    string result = s.substr(0, maxLen - 3);
    result.append("...");
    return result;
}

// ============================================================
//  NoteManager (Friend Class) member functions
// ============================================================
void NoteManager::showNoteCount(const NoteMap &notes) const
{
    int count = 0;

    for (NoteMap::const_iterator it = notes.begin(); it != notes.end(); ++it)
        if (!it->second.isDeleted())
            count++;

    cout << "\nTotal number of files: " << count << endl;
}

// Formatted I/O: setw, setfill, left
void NoteManager::displayTable(const NoteMap &notes) const
{
    cout << "\n" << left
         << setw(6)  << "ID"
         << setw(24) << "Title"
         << setw(10) << "Length"
         << "Content Preview" << endl;

    cout << setfill('-') << setw(70) << "" << setfill(' ') << endl;

    for (const auto &entry : notes)
    {
        const Notes &n = entry.second;      // friend access to private members

        cout << left
             << setw(6)  << entry.first
             << setw(24) << shorten(n.title, 22)
             << setw(10) << n.content.length()
             << shorten(n.content, 30) << endl;
    }
}

// STL vector holds the IDs of all notes that match the keyword
vector<int> NoteManager::searchNotes(const NoteMap &notes, const string &keyword) const
{
    vector<int> matches;
    string key = toLowerCase(keyword);

    for (const auto &entry : notes)
    {
        const Notes &n = entry.second;

        if (toLowerCase(n.title).find(key) != string::npos ||
            toLowerCase(n.content).find(key) != string::npos)
        {
            matches.push_back(entry.first);
        }
    }

    return matches;
}

// File output using the constructor method: ofstream out("file")
int NoteManager::saveToFile(const NoteMap &notes, const string &filename) const
{
    ofstream out(filename.c_str());

    if (!out)
        throw runtime_error("Error opening file for writing!");

    int saved = 0;

    // File format: ID line, title line, content line (repeated)
    for (const auto &entry : notes)
    {
        out << entry.first << '\n'
            << entry.second.title << '\n'
            << entry.second.content << '\n';
        saved++;
    }

    out.close();
    return saved;
}

// File input using ifstream + getline(), with status checking
int NoteManager::loadFromFile(NoteMap &notes, int &nextId, const string &filename) const
{
    ifstream in(filename.c_str());

    if (!in)
        throw runtime_error("File not found! Save the notes first (option 13).");

    NoteMap loaded;
    int id = 0, maxId = 0;

    while (in >> id)
    {
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        string t, c;
        getline(in, t);
        getline(in, c);

        loaded[id] = Notes(t, c);

        if (id > maxId)
            maxId = id;
    }

    if (in.bad())
        throw runtime_error("A serious error occurred while reading the file!");

    in.close();

    notes = loaded;
    nextId = maxId + 1;

    return static_cast<int>(loaded.size());
}

// ============================================================
//  File-handling helper functions
// ============================================================

// Opening a file using open() with ios::app, also keeps the
// recent activity in an STL list (newest first, max 5 entries)
void logActivity(list<string> &recent, const string &message)
{
    recent.push_front(message);

    if (recent.size() > 5)
        recent.pop_back();

    fstream file;
    file.open("activity_log.txt", ios::out | ios::app);

    if (file)
        file << message << '\n';

    file.close();
}

// Unformatted I/O: get() and put() copy the file character by character
void backupFile(const string &source, const string &destination)
{
    ifstream fin(source.c_str(), ios::binary);

    if (!fin)
        throw runtime_error("Nothing to back up! Save the notes first (option 13).");

    ofstream fout(destination.c_str(), ios::binary);

    if (!fout)
        throw runtime_error("Could not create the backup file!");

    char ch;
    long bytes = 0;

    while (fin.get(ch))
    {
        fout.put(ch);
        bytes++;
    }

    fin.close();
    fout.close();

    cout << "\nBackup created: " << destination << " (" << bytes << " bytes)\n";
}

// Reading a text file back with getline()
void showLogFile()
{
    ifstream fin("activity_log.txt");

    if (!fin)
    {
        cout << "\nNo activity log found yet.\n";
        return;
    }

    cout << "\n------ Activity Log (activity_log.txt) ------\n";

    string line;
    int number = 1;

    while (getline(fin, line))
        cout << number++ << ". " << line << endl;

    fin.close();
}

// Checking file status: eof(), fail(), bad(), good()
void showFileStatus(const string &filename)
{
    ifstream fin(filename.c_str());

    if (!fin)
    {
        cout << "\nFile '" << filename << "' could not be opened.\n";
        return;
    }

    // seekg / tellg to find the file size
    fin.seekg(0, ios::end);
    streamoff size = fin.tellg();
    fin.seekg(0, ios::beg);

    string line;
    int lines = 0;

    while (getline(fin, line))
        lines++;

    cout << "\n------ File Status: " << filename << " ------\n";
    cout << "Size  : " << size << " bytes\n";
    cout << "Lines : " << lines << endl;
    cout << boolalpha;
    cout << "eof()  : " << fin.eof()  << "  (end of file reached)\n";
    cout << "fail() : " << fin.fail() << "  (last read had nothing left)\n";
    cout << "bad()  : " << fin.bad()  << "  (no serious error)\n";
    cout << "good() : " << fin.good() << "  (false after reading to the end)\n";
    cout << noboolalpha;

    fin.close();
}

// ============================================================
//  Function Template
// ============================================================
template <typename T>
T maximum(T a, T b)
{
    return (a > b) ? a : b;
}

// ============================================================
//  Select a note by ID from the map (uses find())
// ============================================================
NoteMap::iterator selectNote(NoteMap &notes)
{
    int id;

    cout << "Enter note ID: ";

    if (!(cin >> id))
        throw invalid_argument("Please enter a valid note ID.");

    NoteMap::iterator it = notes.find(id);

    if (it == notes.end())
        throw InvalidNoteInputException("No note found with that ID!");

    return it;
}

// ============================================================
//  main
// ============================================================
int main()
{
    const string NOTES_FILE  = "notes.txt";
    const string BACKUP_FILE = "notes_backup.txt";

    NoteMap notes;              // STL map   : ID -> Note
    list<string> recent;        // STL list  : recent activity
    NoteManager manager;
    int nextId = 1;
    int choice = 0;

    do
    {
        cout << "\n================================\n";
        cout << "         HARK OS - NOTES\n";
        cout << "================================\n";
        cout << " 1. Create Note\n";
        cout << " 2. Create Note with Initial Content\n";
        cout << " 3. Display All Notes\n";
        cout << " 4. Edit Note (Add/Delete Text)\n";
        cout << " 5. Append Content using + Operator\n";
        cout << " 6. Display Selected Note using Friend Function\n";
        cout << " 7. Show Total Number of Files using Friend Class\n";
        cout << " 8. Delete Note\n";
        cout << " 9. Class Template Demo\n";
        cout << "10. Function Template Demo\n";
        cout << "11. Runtime Polymorphism Demo\n";
        cout << "12. Search Notes\n";
        cout << "13. Save Notes to File\n";
        cout << "14. Load Notes from File\n";
        cout << "15. Backup Notes File\n";
        cout << "16. View Recent Activity\n";
        cout << "17. View Activity Log File\n";
        cout << "18. Check Notes File Status\n";
        cout << "19. Exit Notes\n";
        cout << "================================\n";
        cout << "Enter your choice: ";

        try
        {
            if (!(cin >> choice))
                throw invalid_argument("Invalid input! Please enter a valid number.");

            switch (choice)
            {
                case 1:
                {
                    Notes n;
                    n.createNote();
                    notes[nextId] = n;

                    cout << "\nNote created successfully! (ID: " << nextId << ")\n";
                    logActivity(recent, "Created note #" + to_string(nextId));
                    nextId++;
                    break;
                }

                case 2:
                {
                    string initialContent;
                    cout << "\nEnter initial content: ";
                    getline(cin >> ws, initialContent);

                    Notes n;
                    n.createNote(initialContent);
                    notes[nextId] = n;

                    cout << "\nNote created with initial content! (ID: " << nextId << ")\n";
                    logActivity(recent, "Created note #" + to_string(nextId) + " with initial content");
                    nextId++;
                    break;
                }

                case 3:
                    if (notes.empty())
                        cout << "\nNo notes available.\n";
                    else
                    {
                        cout << "\n========== ALL NOTES ==========";
                        manager.displayTable(notes);
                    }
                    break;

                case 4:
                    if (notes.empty())
                        cout << "\nNo note available!\n";
                    else
                    {
                        manager.displayTable(notes);
                        cout << endl;
                        NoteMap::iterator it = selectNote(notes);
                        it->second.editNote();
                        logActivity(recent, "Edited note #" + to_string(it->first));
                    }
                    break;

                case 5:
                    if (notes.empty())
                        cout << "\nNo note available!\n";
                    else
                    {
                        manager.displayTable(notes);
                        cout << endl;
                        NoteMap::iterator it = selectNote(notes);

                        string extraContent;
                        cout << "Enter content to append: ";
                        getline(cin >> ws, extraContent);

                        it->second = it->second + extraContent;   // operator+
                        cout << "\nContent appended successfully!\n";
                        logActivity(recent, "Appended content to note #" + to_string(it->first));
                    }
                    break;

                case 6:
                    if (notes.empty())
                        cout << "\nNo note available!\n";
                    else
                    {
                        manager.displayTable(notes);
                        cout << endl;
                        NoteMap::iterator it = selectNote(notes);
                        displayNoteDetails(it->second);           // friend function
                    }
                    break;

                case 7:
                    manager.showNoteCount(notes);                 // friend class
                    break;

                case 8:
                    if (notes.empty())
                        cout << "\nNo note available!\n";
                    else
                    {
                        manager.displayTable(notes);
                        cout << endl;
                        NoteMap::iterator it = selectNote(notes);
                        int deletedId = it->first;

                        it->second.deleteNote();
                        notes.erase(it);                          // map erase

                        cout << "\nNote deleted successfully!\n";
                        logActivity(recent, "Deleted note #" + to_string(deletedId));
                    }
                    break;

                case 9:
                {
                    NoteData<string> textData("HARK OS Notes");
                    textData.displayData();

                    NoteData<size_t> countData(notes.size());
                    countData.displayData();
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
                    if (notes.empty())
                        cout << "\nNo note available!\n";
                    else
                    {
                        manager.displayTable(notes);
                        cout << endl;
                        NoteMap::iterator it = selectNote(notes);

                        NoteOperation *operation = &it->second;   // base class pointer
                        cout << "\nRuntime Polymorphism Output:\n";
                        operation->display();                     // dynamic binding
                    }
                    break;

                case 12:
                {
                    string keyword;
                    cout << "\nEnter keyword to search: ";
                    getline(cin >> ws, keyword);

                    if (keyword.empty())
                        throw InvalidNoteInputException("Search keyword cannot be empty!");

                    vector<int> matches = manager.searchNotes(notes, keyword);

                    if (matches.empty())
                        cout << "\nNo notes matched \"" << keyword << "\".\n";
                    else
                    {
                        cout << "\n" << matches.size() << " note(s) found:\n";

                        for (size_t i = 0; i < matches.size(); i++)
                        {
                            displayNoteDetails(notes[matches[i]]);
                            cout << "ID      : " << matches[i] << endl;
                        }
                    }

                    logActivity(recent, "Searched for \"" + keyword + "\"");
                    break;
                }

                case 13:
                {
                    int saved = manager.saveToFile(notes, NOTES_FILE);
                    cout << "\n" << saved << " note(s) saved to " << NOTES_FILE << endl;
                    logActivity(recent, "Saved " + to_string(saved) + " note(s) to file");
                    break;
                }

                case 14:
                {
                    int loaded = manager.loadFromFile(notes, nextId, NOTES_FILE);
                    cout << "\n" << loaded << " note(s) loaded from " << NOTES_FILE << endl;
                    logActivity(recent, "Loaded " + to_string(loaded) + " note(s) from file");
                    break;
                }

                case 15:
                    backupFile(NOTES_FILE, BACKUP_FILE);
                    logActivity(recent, "Created backup of notes file");
                    break;

                case 16:
                    if (recent.empty())
                        cout << "\nNo recent activity.\n";
                    else
                    {
                        cout << "\n------ Recent Activity (newest first) ------\n";
                        int number = 1;
                        for (const string &entry : recent)
                            cout << number++ << ". " << entry << endl;
                    }
                    break;

                case 17:
                    showLogFile();
                    break;

                case 18:
                    showFileStatus(NOTES_FILE);
                    break;

                case 19:
                    cout << "\nExiting Notes...\n";
                    break;

                default:
                    cout << "\nInvalid choice! Please select an option from 1 to 19.\n";
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

    } while (choice != 19);

    return 0;
}
