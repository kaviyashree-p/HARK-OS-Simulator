
#include <iostream>
#include <string>
using namespace std;


// =====================================================
// FORWARD DECLARATION
// =====================================================

class SettingsManager;


// =====================================================
// BASE CLASS
// INHERITANCE
// =====================================================

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


    // =================================================
    // INLINE FUNCTION
    // =================================================

    inline void displayComponent()
    {
        cout << "\nOS Component : "
             << componentName << endl;
    }


    // INLINE FUNCTION
    inline string getComponentName()
    {
        return componentName;
    }


    // Destructor
    ~OSComponent()
    {
    }
};


// =====================================================
// FUNCTION TEMPLATE
// GENERIC RANGE CHECK
// =====================================================

template <class T>
bool checkRange(T value, T minimum, T maximum)
{
    return value >= minimum && value <= maximum;
}


// =====================================================
// SETTINGS CLASS
// INHERITANCE
// =====================================================

class Settings : public OSComponent
{
private:

    int settingId;
    string username;
    string theme;
    string language;
    bool notification;
    bool powerSaver;
    int volume;


public:

    // =================================================
    // DEFAULT CONSTRUCTOR
    // =================================================

    Settings()
        : OSComponent("Settings")
    {
        settingId = 0;
        username = "";
        theme = "Light";
        language = "English";
        notification = true;
        powerSaver = false;
        volume = 50;
    }


    // =================================================
    // PARAMETERIZED CONSTRUCTOR
    // =================================================

    Settings(int id, string user, string t)
        : OSComponent("Settings")
    {
        settingId = id;
        username = user;
        theme = t;
        language = "English";
        notification = true;
        powerSaver = false;
        volume = 50;
    }


    // =================================================
    // INLINE FUNCTION
    // =================================================

    inline int getSettingId()
    {
        return settingId;
    }


    // =================================================
    // INLINE FUNCTION
    // =================================================

    inline int getVolume()
    {
        return volume;
    }


    // =================================================
    // FUNCTION OVERLOADING
    // =================================================

    void setSettings(string t)
    {
        theme = t;
    }


    void setSettings(string t, string l)
    {
        theme = t;
        language = l;
    }


    void setSettings(string t, string l, int v)
    {
        theme = t;
        language = l;

        if(checkRange(v, 0, 100))
        {
            volume = v;
        }
        else
        {
            cout << "Invalid volume!" << endl;
        }
    }


    // =================================================
    // INPUT SETTINGS
    // =================================================

    void inputSettings()
    {
        cout << "\nEnter Setting ID: ";
        cin >> settingId;

        cin.ignore();

        cout << "Enter Username: ";
        getline(cin, username);

        cout << "Enter Theme (Light/Dark): ";
        getline(cin, theme);

        cout << "Enter Language: ";
        getline(cin, language);

        cout << "Enter Volume (0-100): ";
        cin >> volume;


        // FUNCTION TEMPLATE
        if(!checkRange(volume, 0, 100))
        {
            cout << "Invalid volume! Setting volume to 50."
                 << endl;

            volume = 50;
        }


        int choice;

        cout << "Enable Notifications? (1-Yes / 0-No): ";
        cin >> choice;

        notification = choice;


        cout << "Enable Power Saver? (1-Yes / 0-No): ";
        cin >> choice;

        powerSaver = choice;
    }


    // =================================================
    // DISPLAY
    // =================================================

    void display()
    {
        cout << "\n================================";
        cout << "\n        HARK OS SETTINGS";
        cout << "\n================================";

        cout << "\nSetting ID       : " << settingId;
        cout << "\nUsername         : " << username;
        cout << "\nTheme            : " << theme;
        cout << "\nLanguage         : " << language;
        cout << "\nVolume           : " << volume;


        if(notification)
            cout << "\nNotifications    : ON";
        else
            cout << "\nNotifications    : OFF";


        if(powerSaver)
            cout << "\nPower Saver      : ON";
        else
            cout << "\nPower Saver      : OFF";


        cout << "\n================================\n";
    }


    // =================================================
    // CHANGE THEME
    // =================================================

    void changeTheme()
    {
        cout << "\nEnter new theme: ";
        cin >> theme;

        cout << "Theme changed successfully!\n";
    }


    // =================================================
    // CHANGE LANGUAGE
    // =================================================

    void changeLanguage()
    {
        cout << "\nEnter new language: ";
        cin >> language;

        cout << "Language changed successfully!\n";
    }


    // =================================================
    // CHANGE VOLUME
    // =================================================

    void changeVolume()
    {
        int newVolume;

        cout << "\nEnter new volume: ";
        cin >> newVolume;


        // FUNCTION TEMPLATE
        if(!checkRange(newVolume, 0, 100))
        {
            cout << "Invalid volume!\n";
        }
        else
        {
            volume = newVolume;

            cout << "Volume changed successfully!\n";
        }
    }


    // =================================================
    // TOGGLE NOTIFICATION
    // =================================================

    void toggleNotification()
    {
        notification = !notification;


        if(notification)
            cout << "Notifications enabled.\n";
        else
            cout << "Notifications disabled.\n";
    }


    // =================================================
    // TOGGLE POWER SAVER
    // =================================================

    void togglePowerSaver()
    {
        powerSaver = !powerSaver;


        if(powerSaver)
            cout << "Power Saver enabled.\n";
        else
            cout << "Power Saver disabled.\n";
    }


    // =================================================
    // OPERATOR OVERLOADING
    // =================================================

    bool operator>(Settings s)
    {
        return volume > s.volume;
    }


    // =================================================
    // FRIEND FUNCTION
    // =================================================

    friend void showSettingsDetails(Settings s);


    // =================================================
    // FRIEND CLASS
    // =================================================

    friend class SettingsManager;


    // =================================================
    // DESTRUCTOR
    // =================================================

    ~Settings()
    {
        cout << "\nSettings "
             << settingId
             << " destroyed.";
    }
};


// =====================================================
// CLASS TEMPLATE
// GENERIC STORAGE
// =====================================================

template <class T>
class Storage
{
private:

    T* data;
    int count;
    int capacity;


public:

    // =================================================
    // CONSTRUCTOR
    // =================================================

    Storage(int size)
    {
        capacity = size;
        count = 0;

        data = new T[capacity];
    }


    // =================================================
    // ADD ITEM
    // =================================================

    void add(T item)
    {
        if(count < capacity)
        {
            data[count] = item;
            count++;
        }
    }


    // =================================================
    // GET ITEM
    // =================================================

    T& get(int index)
    {
        return data[index];
    }


    // =================================================
    // GET COUNT
    // =================================================

    inline int size()
    {
        return count;
    }


    // =================================================
    // DESTRUCTOR
    // =================================================

    ~Storage()
    {
        delete[] data;
    }
};


// =====================================================
// FRIEND FUNCTION
// =====================================================

void showSettingsDetails(Settings s)
{
    cout << "\n===== FRIEND FUNCTION =====";

    cout << "\nSetting ID : " << s.settingId;
    cout << "\nUsername   : " << s.username;
    cout << "\nTheme      : " << s.theme;
    cout << "\nLanguage   : " << s.language;
    cout << "\nVolume     : " << s.volume << endl;
}


// =====================================================
// FRIEND CLASS
// =====================================================

class SettingsManager
{
private:

    int count;


public:

    SettingsManager()
    {
        count = 0;
    }


    void addCount()
    {
        count++;
    }


    void showCount()
    {
        cout << "\nTotal Settings: "
             << count
             << endl;
    }


    // =================================================
    // FRIEND CLASS ACCESSING PRIVATE MEMBERS
    // =================================================

    void changeUsername(Settings &s)
    {
        cin.ignore();

        cout << "Enter new username: ";

        getline(cin, s.username);

        cout << "Username changed successfully!\n";
    }


    // =================================================
    // RESET SETTINGS
    // =================================================

    void resetSettings(Settings &s)
    {
        s.theme = "Light";
        s.language = "English";
        s.notification = true;
        s.powerSaver = false;
        s.volume = 50;

        cout << "Settings reset successfully!\n";
    }
};


// =====================================================
// MAIN
// =====================================================

int main()
{
    int n;


    cout << "====================================\n";
    cout << "       HARK OS SETTINGS\n";
    cout << "====================================\n";


    cout << "\nEnter number of users/settings: ";
    cin >> n;


    // =================================================
    // CLASS TEMPLATE OBJECT
    // =================================================

    Storage<Settings> settings(n);


    SettingsManager manager;


    // =================================================
    // RUNTIME INPUT
    // =================================================

    for(int i = 0; i < n; i++)
    {
        cout << "\n===== Setting "
             << i + 1
             << " =====";

        Settings temp;

        temp.inputSettings();

        // CLASS TEMPLATE
        settings.add(temp);

        manager.addCount();
    }


    int choice;


    do
    {
        cout << "\n\n====================================";
        cout << "\n          SETTINGS MENU";
        cout << "\n====================================";

        cout << "\n1. Display All Settings";
        cout << "\n2. Change Theme";
        cout << "\n3. Change Language";
        cout << "\n4. Change Volume";
        cout << "\n5. Toggle Notifications";
        cout << "\n6. Toggle Power Saver";
        cout << "\n7. Change Username";
        cout << "\n8. Show Settings Details";
        cout << "\n9. Reset Settings";
        cout << "\n10. Compare Two Settings";
        cout << "\n11. Show Settings Count";
        cout << "\n12. Show OS Component";
        cout << "\n13. Exit";


        cout << "\nEnter your choice: ";
        cin >> choice;


        switch(choice)
        {
            // =========================================
            // DISPLAY
            // =========================================

            case 1:
            {
                for(int i = 0;
                    i < settings.size();
                    i++)
                {
                    settings.get(i).display();
                }

                break;
            }


            // =========================================
            // CHANGE THEME
            // =========================================

            case 2:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    settings.get(pos - 1).changeTheme();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // CHANGE LANGUAGE
            // =========================================

            case 3:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    settings.get(pos - 1).changeLanguage();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // CHANGE VOLUME
            // =========================================

            case 4:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    settings.get(pos - 1).changeVolume();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // TOGGLE NOTIFICATIONS
            // =========================================

            case 5:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    settings.get(pos - 1).toggleNotification();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // TOGGLE POWER SAVER
            // =========================================

            case 6:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    settings.get(pos - 1).togglePowerSaver();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // CHANGE USERNAME
            // FRIEND CLASS
            // =========================================

            case 7:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    manager.changeUsername(
                        settings.get(pos - 1)
                    );
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // FRIEND FUNCTION
            // =========================================

            case 8:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    showSettingsDetails(
                        settings.get(pos - 1)
                    );
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // RESET
            // FRIEND CLASS
            // =========================================

            case 9:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;


                if(pos >= 1 && pos <= settings.size())
                {
                    manager.resetSettings(
                        settings.get(pos - 1)
                    );
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // OPERATOR OVERLOADING
            // =========================================

            case 10:
            {
                int first, second;


                cout << "Enter first setting number: ";
                cin >> first;


                cout << "Enter second setting number: ";
                cin >> second;


                if(first >= 1 &&
                   first <= settings.size() &&
                   second >= 1 &&
                   second <= settings.size())
                {
                    if(settings.get(first - 1) >
                       settings.get(second - 1))
                    {
                        cout << "First setting has higher volume.\n";
                    }

                    else if(settings.get(second - 1) >
                            settings.get(first - 1))
                    {
                        cout << "Second setting has higher volume.\n";
                    }

                    else
                    {
                        cout << "Both settings have same volume.\n";
                    }
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            // =========================================
            // COUNT
            // =========================================

            case 11:
            {
                manager.showCount();

                break;
            }


            // =========================================
            // INHERITANCE
            // =========================================

            case 12:
            {
                if(settings.size() > 0)
                {
                    settings.get(0).displayComponent();
                }

                break;
            }


            // =========================================
            // EXIT
            // =========================================

            case 13:
            {
                cout << "\nExiting Settings...\n";

                break;
            }


            default:
            {
                cout << "Invalid choice.\n";
            }
        }

    } while(choice != 13);


    return 0;
}
