// Roll No: MT26210
// Name: Harsh Dubey
#include "basicIO.h"

#define MAX_NAME_LENGTH 100
#define MAX_NAMES 100

#define SYS_MMAP 9
#define SYS_MUNMAP 11

extern "C" long syscall3(long number, long arg1, long arg2, long arg3);

extern "C" long syscall6(long number, long arg1, long arg2,
                         long arg3, long arg4, long arg5, long arg6);


int main()
{
    int numberOfNames;

    io.activateInput();

    // Get the initial number of names
    io.outputstring("Enter number of names: ");
    numberOfNames = io.inputint();

    if (numberOfNames <= 0 || numberOfNames > MAX_NAMES)
    {
        io.errorstring("Invalid number of names.\n");
        return 1;
    }

    long totalSize = (long)numberOfNames * MAX_NAME_LENGTH;

    // Allocate memory for the names
    char* names = (char*)syscall6(
        SYS_MMAP,
        0,
        totalSize,
        3,
        34,
        -1,
        0
    );

    if ((long)names < 0)
    {
        io.errorstring("Memory allocation failed.\n");
        return 1;
    }

    // Enter the names
    for (int i = 0; i < numberOfNames; ++i)
    {
        io.outputstring("Enter name ");
        io.outputint(i + 1);
        io.outputstring(": ");

        char* currentName = names + (i * MAX_NAME_LENGTH);

        io.inputstring(currentName, MAX_NAME_LENGTH);
    }

    // Display the names
    io.outputstring("\nNames entered:\n");

    for (int i = 0; i < numberOfNames; ++i)
    {
        io.outputint(i + 1);
        io.outputstring(": ");
        io.outputstring(names + (i * MAX_NAME_LENGTH));
        io.terminate();
    }


    // Ask whether the number of names should change
    char answer[10];

    io.outputstring("\nDo you want to change the number of names? (y/n): ");
    io.inputstring(answer, 10);

    if (answer[0] == 'y' || answer[0] == 'Y')
    {
        int newNumberOfNames;

        io.outputstring("Enter new number of names: ");
        newNumberOfNames = io.inputint();

        if (newNumberOfNames <= 0 || newNumberOfNames > MAX_NAMES)
        {
            io.errorstring("Invalid number of names.\n");

            syscall3(
                SYS_MUNMAP,
                (long)names,
                totalSize,
                0
            );

            return 1;
        }

        // Release the old memory
        syscall3(
            SYS_MUNMAP,
            (long)names,
            totalSize,
            0
        );

        // Calculate memory needed for the new number of names
        totalSize = (long)newNumberOfNames * MAX_NAME_LENGTH;

        // Allocate new memory
        names = (char*)syscall6(
            SYS_MMAP,
            0,
            totalSize,
            3,
            34,
            -1,
            0
        );

        if ((long)names < 0)
        {
            io.errorstring("Memory allocation failed.\n");
            return 1;
        }

        numberOfNames = newNumberOfNames;

        // Enter the new names
        for (int i = 0; i < numberOfNames; ++i)
        {
            io.outputstring("Enter name ");
            io.outputint(i + 1);
            io.outputstring(": ");

            char* currentName = names + (i * MAX_NAME_LENGTH);

            io.inputstring(currentName, MAX_NAME_LENGTH);
        }

        // Display the new names
        io.outputstring("\nNew names entered:\n");

        for (int i = 0; i < numberOfNames; ++i)
        {
            io.outputint(i + 1);
            io.outputstring(": ");
            io.outputstring(names + (i * MAX_NAME_LENGTH));
            io.terminate();
        }
    }
    else if (answer[0] != 'n' && answer[0] != 'N')
    {
        io.errorstring("Invalid choice. Please enter y or n.\n");

        syscall3(
            SYS_MUNMAP,
            (long)names,
            totalSize,
            0
        );

        return 1;
    }

    // Release the final memory allocation
    syscall3(
        SYS_MUNMAP,
        (long)names,
        totalSize,
        0
    );

    return 0;
}
