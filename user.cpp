#include <iostream>
#include <string>
using namespace std;

class UserManager;   // Forward declaration


// ================= USER CLASS =================

class User
{
private:
    int userId;
    string username;
    string password;
    string role;
    string email;
    bool active;

public:

    // ================= DEFAULT CONSTRUCTOR =================

    User()
    {
        userId = 0;
        username = "";
        password = "";
        role = "User";
        email = "";
        active = true;
    }


    // ================= PARAMETERIZED CONSTRUCTOR =================

    User(int id, string name, string r)
    {
        userId = id;
        username = name;
        role = r;
        password = "";
        email = "";
        active = true;
    }


    // ================= FUNCTION OVERLOADING =================

    void setUser(string name)
    {
        username = name;
    }

    void setUser(string name, string mail)
    {
        username = name;
        email = mail;
    }

    void setUser(string name, string mail, string r)
    {
        username = name;
        email = mail;
        role = r;
    }


    // ================= INPUT USER DETAILS =================

    void inputUser()
    {
        cout << "\nEnter User ID: ";
        cin >> userId;

        cin.ignore();

        cout << "Enter Username: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "Enter Email: ";
        getline(cin, email);

        cout << "Enter Role (Admin/User): ";
        getline(cin, role);

        active = true;
    }


    // ================= DISPLAY USER =================

    void display()
    {
        cout << "\n================================";
        cout << "\n          USER DETAILS";
        cout << "\n================================";

        cout << "\nUser ID   : " << userId;
        cout << "\nUsername  : " << username;
        cout << "\nEmail     : " << email;
        cout << "\nRole      : " << role;

        if(active)
            cout << "\nStatus    : Active";
        else
            cout << "\nStatus    : Inactive";

        cout << "\n================================\n";
    }


    // ================= CHANGE USERNAME =================

    void changeUsername()
    {
        cin.ignore();

        cout << "Enter new username: ";
        getline(cin, username);

        cout << "Username changed successfully!\n";
    }


    // ================= CHANGE PASSWORD =================

    void changePassword()
    {
        cin.ignore();

        cout << "Enter new password: ";
        getline(cin, password);

        cout << "Password changed successfully!\n";
    }


    // ================= CHANGE EMAIL =================

    void changeEmail()
    {
        cin.ignore();

        cout << "Enter new email: ";
        getline(cin, email);

        cout << "Email changed successfully!\n";
    }


    // ================= ACTIVATE / DEACTIVATE =================

    void toggleStatus()
    {
        active = !active;

        if(active)
            cout << "User activated successfully!\n";
        else
            cout << "User deactivated successfully!\n";
    }


    // ================= OPERATOR OVERLOADING =================

    bool operator>(User u)
    {
        return userId > u.userId;
    }


    // ================= FRIEND FUNCTION =================

    friend void showUserDetails(User u);


    // ================= FRIEND CLASS =================

    friend class UserManager;


    // ================= DESTRUCTOR =================

    ~User()
    {
        cout << "\nUser " << userId << " destroyed.";
    }
};


// =====================================================
// FRIEND FUNCTION
// =====================================================

void showUserDetails(User u)
{
    cout << "\n===== FRIEND FUNCTION =====";

    cout << "\nUser ID  : " << u.userId;
    cout << "\nUsername : " << u.username;
    cout << "\nEmail    : " << u.email;
    cout << "\nRole     : " << u.role << endl;
}


// =====================================================
// FRIEND CLASS
// =====================================================

class UserManager
{
private:
    int count;

public:

    UserManager()
    {
        count = 0;
    }


    void addCount()
    {
        count++;
    }


    void showCount()
    {
        cout << "\nTotal Users: " << count << endl;
    }


    // Friend class can access private members
    void changeRole(User &u)
    {
        cin.ignore();

        cout << "Enter new role: ";
        getline(cin, u.role);

        cout << "Role changed successfully!\n";
    }


    // Reset user
    void resetUser(User &u)
    {
        u.username = "";
        u.password = "";
        u.email = "";
        u.role = "User";
        u.active = true;

        cout << "User details reset successfully!\n";
    }
};


// =====================================================
// MAIN
// =====================================================

int main()
{
    int n;

    cout << "====================================";
    cout << "\n        HARK OS USER SYSTEM";
    cout << "\n====================================";

    cout << "\n\nEnter number of users: ";
    cin >> n;


    // ================= DYNAMIC ALLOCATION =================

    User *users = new User[n];

    UserManager manager;


    // ================= RUNTIME INPUT =================

    for(int i = 0; i < n; i++)
    {
        cout << "\n===== User " << i + 1 << " =====";

        users[i].inputUser();

        manager.addCount();
    }


    int choice;

    do
    {
        cout << "\n\n====================================";
        cout << "\n            USER MENU";
        cout << "\n====================================";

        cout << "\n1. Display All Users";
        cout << "\n2. Change Username";
        cout << "\n3. Change Password";
        cout << "\n4. Change Email";
        cout << "\n5. Activate / Deactivate User";
        cout << "\n6. Change Role";
        cout << "\n7. Show User Details";
        cout << "\n8. Reset User";
        cout << "\n9. Compare Two Users";
        cout << "\n10. Show User Count";
        cout << "\n11. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;


        switch(choice)
        {

            // ================= DISPLAY =================

            case 1:
            {
                for(int i = 0; i < n; i++)
                {
                    users[i].display();
                }

                break;
            }


            // ================= CHANGE USERNAME =================

            case 2:
            {
                int pos;

                cout << "Enter user number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    users[pos - 1].changeUsername();
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= CHANGE PASSWORD =================

            case 3:
            {
                int pos;

                cout << "Enter user number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    users[pos - 1].changePassword();
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= CHANGE EMAIL =================

            case 4:
            {
                int pos;

                cout << "Enter user number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    users[pos - 1].changeEmail();
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= TOGGLE STATUS =================

            case 5:
            {
                int pos;

                cout << "Enter user number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    users[pos - 1].toggleStatus();
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= CHANGE ROLE =================

            case 6:
            {
                int pos;

                cout << "Enter user number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    manager.changeRole(users[pos - 1]);
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= FRIEND FUNCTION =================

            case 7:
            {
                int pos;

                cout << "Enter user number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    showUserDetails(users[pos - 1]);
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= RESET USER =================

            case 8:
            {
                int pos;

                cout << "Enter user number: ";
                cin >> pos;

                if(pos >= 1 && pos <= n)
                {
                    manager.resetUser(users[pos - 1]);
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= OPERATOR OVERLOADING =================

            case 9:
            {
                int first, second;

                cout << "Enter first user number: ";
                cin >> first;

                cout << "Enter second user number: ";
                cin >> second;

                if(first >= 1 && first <= n &&
                   second >= 1 && second <= n)
                {
                    if(users[first - 1] > users[second - 1])
                    {
                        cout << "First user has greater User ID.\n";
                    }
                    else if(users[second - 1] > users[first - 1])
                    {
                        cout << "Second user has greater User ID.\n";
                    }
                    else
                    {
                        cout << "Both users have same User ID.\n";
                    }
                }
                else
                {
                    cout << "Invalid user number.\n";
                }

                break;
            }


            // ================= COUNT =================

            case 10:
            {
                manager.showCount();
                break;
            }


            // ================= EXIT =================

            case 11:
            {
                cout << "\nExiting User System...\n";
                break;
            }


            default:
            {
                cout << "Invalid choice.\n";
            }
        }

    } while(choice != 11);


    // ================= FREE MEMORY =================

    delete[] users;

    return 0;
}