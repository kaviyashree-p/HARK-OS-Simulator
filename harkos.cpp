#include<iostream>
#include<string>
using namespace std;
class Harkos
{
    private:
        string osname;
        string version;
        bool running;
    public:
        Harkos()
        {
            osname="HARK OS";
            version="5.0";
            running=false;
        }
        ~Harkos()
        {
            cout<<"hark os is closed"<<endl;
        }
        void boot()
        {
            if(running)
            {
                cout<<"hark os is already running"<<endl;
            }
            else
            {
                cout<<"\n------------------------\n";
                cout<<"    HARK OS BOOTING\n";
                cout<<"--------------------------\n";
                cout<<"Loading system files...."<<endl;
                cout<<"initializing system....."<<endl;
                cout<<"starting hark os....."<<endl;
                running=true;
                cout<<"\n hark os booted successfully"<<endl;
            }
        }
        void desktop()
        {
            if(!running)
            {
                cout<<"boot the os first"<<endl;
            }
            else
            {
                cout << "\n----------------------------------" << endl;
                cout << "            HARK OS DESKTOP" << endl;
                cout << "------------------------------------" << endl;
                cout << "\n1. File Manager" << endl;
                cout << "2. Calculator" << endl;
                cout << "3. Notes" << endl;
                cout << "4. Calendar" << endl;
                cout << "5. Clock" << endl;
                cout << "6. Command Prompt" << endl;
                cout << "7. Task Manager" << endl;
                cout << "8. Settings" << endl;
                cout << "\nDesktop loaded successfully!" << endl;
            }
        }
        void shutdown()
        {
            if(!running)
            {
                cout<<"Hark os is already shut down"<<endl;
            }
            else
            {
                cout<<"\n------------------------\n";
                cout<<"    Hark Os shutting down\n";
                cout<<"--------------------------\n";
                cout<<"closing information...."<<endl;
                cout<<"saving system information...."<<endl;
                cout<<"shuttong down the system..."<<endl;
                running=false;
                cout<<"\n Harkos shut down successfully"<<endl;
            }
        }
        bool isrunning()
        {
            return running;
        }
        friend void showosinfo(Harkos h);
};
void showosinfo(Harkos h)
{
    cout<<"OS name: "<<h.osname<<endl;
    cout<<"OS version: "<<h.version<<endl;
}
int main()
{
    Harkos os;
    int choice;
    do
    {
        cout<<"\n--------------------------------\n";
        cout<<"           HARK OS\n";
        cout<<"----------------------------------\n";
         cout << "1. Boot HARK OS" << endl;
        cout << "2. Show Desktop" << endl;
        cout << "3. Show OS Information" << endl;
        cout << "4. Shutdown" << endl;
        cout << "5. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
                os.boot();
                break;

            case 2:
                os.desktop();
                break;

            case 3:
                showosinfo(os);
                break;

            case 4:
                os.shutdown();
                break;

            case 5:
                cout << "\nExiting HARK OS..." << endl;

                if (os.isrunning())
                {
                    os.shutdown();
                }

                break;

            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    } while (choice != 5);
    return 0;
}