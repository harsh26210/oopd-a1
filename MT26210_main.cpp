//Name:harsh dubey
// roll no:MT26210
#include "basicIO.h"

int main()
{
    char name[100];
    char confirmation[10];
    int age;

    io.activateInput();

    // Get the user's name
    io.outputstring("Enter your name: ");
    io.inputstring(name, 100);

    // Make sure the name is not empty
    if (name[0] == '\0')
    {
        io.errorstring("Invalid name.\n");
        return 1;
    }

    // Get the user's age
    io.outputstring("Enter your age: ");
    age = io.inputint();

    // Check that the age is reasonable
    if (age <= 0 || age > 150)
    {
        io.errorstring("Invalid age.\n");
        return 1;
    }

    // Ask for confirmation
    io.outputstring("Confirm your details? (y/n): ");
    io.inputstring(confirmation, 10);

    if (confirmation[0] == 'y' || confirmation[0] == 'Y')
    {
        io.outputstring("Details confirmed.");
    }
    else if (confirmation[0] == 'n' || confirmation[0] == 'N')
    {
        io.outputstring("Details not confirmed.");
    }
    else
    {
        io.errorstring("Invalid confirmation. Please enter y or n.\n");
        return 1;
    }

    io.terminate();

    return 0;
}
