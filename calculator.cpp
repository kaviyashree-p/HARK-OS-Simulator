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

    // Parameterized Constructor
    Calculator(double a, double b)
    {
        num1 = a;
        num2 = b;
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

    // FUNCTION OVERLOADING
    // calculate() with 2 parameters
    double calculate(double a, double b)
    {
        return a + b;
    }

    // calculate() with 3 parameters
    double calculate(double a, double b, double c)
    {
        return a + b + c;
    }

    // OPERATOR OVERLOADING
    // Overloading + operator
    Calculator operator+(Calculator obj)
    {
        Calculator temp;

        temp.num1 = num1 + obj.num1;
        temp.num2 = num2 + obj.num2;

        return temp;
    }

    // Display values
    void display()
    {
        cout << "First number = " << num1 << endl;
        cout << "Second number = " << num2 << endl;
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
        cout << "5. Function Overloading" << endl;
        cout << "6. Operator Overloading" << endl;
        cout << "7. Exit" << endl;

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


        // FUNCTION OVERLOADING
        else if(choice == 5)
        {
            double a, b, c;

            cout << "\nEnter two numbers: ";
            cin >> a >> b;

            cout << "calculate(a,b) = "
                 << calc.calculate(a, b) << endl;

            cout << "\nEnter three numbers: ";
            cin >> a >> b >> c;

            cout << "calculate(a,b,c) = "
                 << calc.calculate(a, b, c) << endl;
        }


        // OPERATOR OVERLOADING
        else if(choice == 6)
        {
            double a, b, c, d;

            cout << "\nEnter first number pair: ";
            cin >> a >> b;

            cout << "Enter second number pair: ";
            cin >> c >> d;

            Calculator calc1(a, b);
            Calculator calc2(c, d);

            Calculator calc3 = calc1 + calc2;

            cout << "\nAfter Operator Overloading (+):" << endl;

            calc3.display();
        }


        else if(choice == 7)
        {
            cout << "Exiting calculator..." << endl;
            break;
        }


        else
        {
            cout << "Invalid choice!" << endl;
        }


        if(choice != 7)
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

