#include <iostream>
#include <string>
#include <limits>
#include <exception>

using namespace std;

// ============================================================================
// 1. CUSTOM EXCEPTION CLASSES (Inheriting from std::exception)
// ============================================================================

class BatteryOverchargeException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Cannot charge further! Battery is already at 100%.";
    }
};

class InvalidBatteryValueException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Invalid input! Charge value must be a positive integer.";
    }
};

class InvalidMenuException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Invalid choice entered! Please select a valid number.";
    }
};

// ============================================================================
// 2. ABSTRACT BASE CLASS (FOR RUNTIME POLYMORPHISM)
// ============================================================================

class BatteryOperation
{
public:
    virtual void display() = 0;              // Pure virtual function
    virtual ~BatteryOperation() {}           // Virtual destructor
};

// ============================================================================
// 3. BASE CLASS (INHERITANCE)
// ============================================================================

class BaseComponent
{
protected:
    string deviceType;

public:
    BaseComponent()
    {
        deviceType = "HARK OS System Hardware";
    }

    void showComponentType() const
    {
        cout << "Hardware Type : " << deviceType << endl;
    }
};

// ============================================================================
// 4. CLASS TEMPLATE
// ============================================================================

template <class T>
class BatteryData
{
private:
    T data;

public:
    BatteryData(T d) : data(d) {}

    void displayData() const
    {
        cout << "Template Data : " << data << endl;
    }
};

// Forward Declaration
class Battery;

// ============================================================================
// 5. FRIEND CLASS
// ============================================================================

class BatteryManager
{
public:
    void showHealthReport(const Battery &b);
};

// ============================================================================
// 6. MAIN BATTERY CLASS (MULTIPLE INHERITANCE)
// ============================================================================

class Battery : public BaseComponent, public BatteryOperation
{
private:
    int batteryLevel;      // Percentage: 0 to 100
    bool isCharging;       // Charging status
    string healthStatus;

public:
    // Default Constructor
    Battery()
    {
        batteryLevel = 50;
        isCharging = false;
        healthStatus = "Good";
    }

    // Parameterized Constructor
    Battery(int level, bool charging)
    {
        if (level < 0 || level > 100)
            throw InvalidBatteryValueException();

        batteryLevel = level;
        isCharging = charging;
        healthStatus = "Good";
    }

    // Virtual Destructor
    ~Battery() override {}

    // Runtime Polymorphism Implementation
    void display() override
    {
        showBatteryStatus();
    }

    // Inline Function
    inline bool isCritical() const
    {
        return batteryLevel <= 15;
    }

    // Displays current battery percentage and charging status
    void showBatteryStatus() const
    {
        cout << "\nBattery Level   : " << batteryLevel << "%" << endl;
        cout << "Charging Status : " << (isCharging ? "Charging..." : "Discharging / Not Charging") << endl;
        cout << "Health Status   : " << healthStatus << endl;
        showComponentType();
    }

    // Simulates charging the battery to increase its charge level
    void chargeBattery()
    {
        if (batteryLevel >= 100)
            throw BatteryOverchargeException();

        int amount;
        cout << "\nCurrent Battery Level: " << batteryLevel << "%";
        cout << "\nEnter percentage to charge: ";

        if (!(cin >> amount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidBatteryValueException();
        }

        if (amount <= 0)
            throw InvalidBatteryValueException();

        if (batteryLevel + amount > 100)
        {
            batteryLevel = 100;
            isCharging = false;
            cout << "\nBattery charged to full (100%)!\n";
        }
        else
        {
            batteryLevel += amount;
            isCharging = true;
            cout << "\nBattery charged successfully to " << batteryLevel << "%!\n";
        }
    }

    // Operator Overloading (+) to boost battery level
    Battery operator+(int boost) const
    {
        int newLevel = batteryLevel + boost;
        if (newLevel > 100)
            newLevel = 100;

        Battery temp(newLevel, true);
        return temp;
    }

    // Friend Declarations
    friend void displayBatteryDetails(const Battery &b);
    friend class BatteryManager;
};

// ============================================================================
// 7. FRIEND FUNCTION & FRIEND CLASS METHOD DEFINITIONS
// ============================================================================

// Friend Function
void displayBatteryDetails(const Battery &b)
{
    cout << "\n----- Selected Battery Diagnostic -----\n";
    cout << "Current Level   : " << b.batteryLevel << "%\n";
    cout << "Power State     : " << (b.isCharging ? "Connected to AC Adapter" : "On Battery Power") << "\n";
    cout << "Low Power Alert : " << (b.isCritical() ? "CRITICAL (Please plug in charger)" : "Normal") << "\n";
}

// Friend Class Member Function
void BatteryManager::showHealthReport(const Battery &b)
{
    cout << "\n[BatteryManager Report]\n";
    cout << "Raw Level Value  : " << b.batteryLevel << "/100\n";
    cout << "Power Connection : " << (b.isCharging ? "Active" : "Idle") << "\n";
}

// ============================================================================
// 8. FUNCTION TEMPLATE
// ============================================================================

template <typename T>
T maximum(T a, T b)
{
    return (a > b) ? a : b;
}

// ============================================================================
// 9. MAIN INTERACTIVE DRIVER
// ============================================================================

int main()
{
    Battery battery;
    BatteryManager manager;
    BatteryOperation *operation = &battery; // Dynamic binding base pointer

    int choice = 0;

    do
    {
        cout << "\n================================\n";
        cout << "        HARK OS - BATTERY\n";
        cout << "================================\n";
        cout << "1. Show Battery Status\n";
        cout << "2. Charge Battery\n";
        cout << "3. Boost Charge (+ Operator Demo)\n";
        cout << "4. Display Diagnostic (Friend Function)\n";
        cout << "5. Show Manager Report (Friend Class)\n";
        cout << "6. Class Template Demo\n";
        cout << "7. Function Template Demo\n";
        cout << "8. Runtime Polymorphism Demo\n";
        cout << "9. Exit Battery Settings\n";
        cout << "================================\n";
        cout << "Enter your choice: ";

        try
        {
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw InvalidMenuException();
            }

            switch (choice)
            {
                case 1:
                    battery.showBatteryStatus();
                    break;

                case 2:
                    battery.chargeBattery();
                    break;

                case 3:
                {
                    int boost;
                    cout << "Enter boost charge percentage: ";
                    if (!(cin >> boost))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw InvalidBatteryValueException();
                    }

                    battery = battery + boost;
                    cout << "\nBoost applied! New battery status:\n";
                    battery.showBatteryStatus();
                    break;
                }

                case 4:
                    displayBatteryDetails(battery);
                    break;

                case 5:
                    manager.showHealthReport(battery);
                    break;

                case 6:
                {
                    BatteryData<string> batteryInfo("Lithium-Ion 4500mAh");
                    batteryInfo.displayData();
                    break;
                }

                case 7:
                {
                    int val1, val2;
                    cout << "\nEnter two battery threshold values: ";
                    if (!(cin >> val1 >> val2))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw InvalidBatteryValueException();
                    }

                    cout << "Higher Threshold = " << maximum(val1, val2) << "%" << endl;
                    break;
                }

                case 8:
                    cout << "\nRuntime Polymorphism Output (via BatteryOperation*):\n";
                    operation->display();
                    break;

                case 9:
                    cout << "\nExiting Battery Settings...\n";
                    break;

                default:
                    cout << "\nInvalid choice! Please select an option between 1 and 9.\n";
            }
        }
        catch (const BatteryOverchargeException &e)
        {
            cout << "\nBattery Warning: " << e.what() << endl;
        }
        catch (const InvalidBatteryValueException &e)
        {
            cout << "\nInput Error: " << e.what() << endl;
        }
        catch (const InvalidMenuException &e)
        {
            cout << "\nInput Error: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "\nGeneral Exception: " << e.what() << endl;
        }

    } while (choice != 9);

    return 0;
}
