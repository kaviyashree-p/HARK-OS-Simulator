#include <iostream>
#include <string>
using namespace std;

class SettingsManager;   // Forward declaration


// ================= SETTINGS CLASS =================

class Settings
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

    // Default Constructor
    Settings()
    {
        settingId = 0;
        username = "";
        theme = "Light";
        language = "English";
        notification = true;
        powerSaver = false;
        volume = 50;
    }

    // Parameterized Constructor
    Settings(int id, string user, string t)
    {
        settingId = id;
        username = user;
        theme = t;
        language = "English";
        notification = true;
        powerSaver = false;
        volume = 50;
    }


    // ================= FUNCTION OVERLOADING =================

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
        volume = v;
    }


    // ================= INPUT SETTINGS =================

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

        int choice;

        cout << "Enable Notifications? (1-Yes / 0-No): ";
        cin >> choice;

        notification = choice;

        cout << "Enable Power Saver? (1-Yes / 0-No): ";
        cin >> choice;

        powerSaver = choice;
    }


    // ================= DISPLAY =================

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


    // ================= CHANGE SETTINGS =================

    void changeTheme()
    {
        cout << "\nEnter new theme: ";
        cin >> theme;

        cout << "Theme changed successfully!\n";
    }


    void changeLanguage()
    {
        cout << "\nEnter new language: ";
        cin >> language;

        cout << "Language changed successfully!\n";
    }


    void changeVolume()
    {
        cout << "\nEnter new volume: ";
        cin >> volume;

        if(volume < 0 || volume > 100)
        {
            cout << "Invalid volume!\n";
        }
        else
        {
            cout << "Volume changed successfully!\n";
        }
    }


    void toggleNotification()
    {
        notification = !notification;

        if(notification)
            cout << "Notifications enabled.\n";
        else
            cout << "Notifications disabled.\n";
    }


    void togglePowerSaver()
    {
        powerSaver = !powerSaver;

        if(powerSaver)
            cout << "Power Saver enabled.\n";
        else
            cout << "Power Saver disabled.\n";
    }


    // ================= OPERATOR OVERLOADING =================

    bool operator>(Settings s)
    {
        return volume > s.volume;
    }


    // ================= FRIEND FUNCTION =================

    friend void showSettingsDetails(Settings s);


    // ================= FRIEND CLASS =================

    friend class SettingsManager;


    // ================= DESTRUCTOR =================

    ~Settings()
    {
        cout << "\nSettings " << settingId << " destroyed.";
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
        cout << "\nTotal Settings: " << count << endl;
    }


    // Friend class accessing private members
    void changeUsername(Settings &s)
    {
        cin.ignore();

        cout << "Enter new username: ";
        getline(cin, s.username);

        cout << "Username changed successfully!\n";
    }


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


    // ================= DYNAMIC ALLOCATION =================

    Settings *settings = new Settings[n];

    SettingsManager manager;


    // ================= RUNTIME INPUT =================

    for(int i = 0; i < n; i++)
    {
        cout << "\n===== Setting " << i + 1 << " =====";

        settings[i].inputSettings();

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
        cout << "\n12. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;


        switch(choice)
        {
            case 1:
            {
                for(int i = 0; i < n; i++)
                {
                    settings[i].display();
                }

                break;
            }


            case 2:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    settings[pos - 1].changeTheme();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 3:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    settings[pos - 1].changeLanguage();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 4:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    settings[pos - 1].changeVolume();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 5:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    settings[pos - 1].toggleNotification();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 6:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    settings[pos - 1].togglePowerSaver();
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 7:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    manager.changeUsername(settings[pos - 1]);
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 8:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    showSettingsDetails(settings[pos - 1]);
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 9:
            {
                int pos;

                cout << "Enter setting number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    manager.resetSettings(settings[pos - 1]);
                }
                else
                {
                    cout << "Invalid setting number.\n";
                }

                break;
            }


            case 10:
            {
                int first, second;

                cout << "Enter first setting number: ";
                cin >> first;

                cout << "Enter second setting number: ";
                cin >> second;

                if(first >= 1 && first <= n &&
                   second >= 1 && second <= n)
                {
                    if(settings[first - 1] > settings[second - 1])
                    {
                        cout << "First setting has higher volume.\n";
                    }
                    else if(settings[second - 1] > settings[first - 1])
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


            case 11:
            {
                manager.showCount();
                break;
            }


            case 12:
            {
                cout << "\nExiting Settings...\n";
                break;
            }


            default:
            {
                cout << "Invalid choice.\n";
            }
        }

    } while(choice != 12);


    // ================= FREE MEMORY =================

    delete[] settings;

    return 0;
}