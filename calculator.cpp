#include <iostream>
using namespace std;

class Calculator
{
private:
    double num1;
    double num2;
    double result;

public:

    // Constructor
    Calculator()
    {
        num1 = 0;
        num2 = 0;
        result = 0;
    }

    // Function to get input from user
    void getInput()
    {
        cout << "Enter first number: ";
        cin >> num1;

        cout << "Enter second number: ";
        cin >> num2;
    }

    // Addition
    void add()
    {
        result = num1 + num2;

        cout << "Result = " << result << endl;
    }

    // Subtraction
    void subtract()
    {
        result = num1 - num2;

        cout << "Result = " << result << endl;
    }

    // Multiplication
    void multiply()
    {
        result = num1 * num2;

        cout << "Result = " << result << endl;
    }

    // Division
    void divide()
    {
        if(num2 == 0)
        {
            cout << "Cannot divide by zero!" << endl;
        }
        else
        {
            result = num1 / num2;

            cout << "Result = " << result << endl;
        }
    }

    // Destructor
    ~Calculator()
    {
        cout << "Calculator closed." << endl;
    }
};


int main()
{
    Calculator calc;

    int choice;
    char again;


    do
    {
        cout << endl;
        cout << "================================" << endl;
        cout << "          CALCULATOR" << endl;
        cout << "================================" << endl;

        cout << "1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Division" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;


        if(choice >= 1 && choice <= 4)
        {
            // Get numbers from USER
            calc.getInput();


            switch(choice)
            {
                case 1:
                    calc.add();
                    break;

                case 2:
                    calc.subtract();
                    break;

                case 3:
                    calc.multiply();
                    break;

                case 4:
                    calc.divide();
                    break;
            }
        }

        else if(choice == 5)
        {
            cout << "Exiting calculator..." << endl;

            break;
        }

        else
        {
            cout << "Invalid choice!" << endl;
        }


        if(choice != 5)
        {
            cout << "\nDo you want to calculate again? (Y/N): ";
            cin >> again;
        }
        else
        {
            again = 'N';
        }

    } while(again == 'Y' || again == 'y');

    return 0;
}