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

    io.outputstring("Enter number of names: ");
    numberOfNames = io.inputint();

    if (numberOfNames <= 0 || numberOfNames > MAX_NAMES)
    {
        io.errorstring("Invalid number of names.\n");
        return 1;
    }

    long totalSize = (long)numberOfNames * MAX_NAME_LENGTH;

    // Allocate memory for all names
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

    // Read each name
    for (int i = 0; i < numberOfNames; ++i)
    {
        io.outputstring("Enter name ");
        io.outputint(i + 1);
        io.outputstring(": ");

        char* currentName = names + (i * MAX_NAME_LENGTH);

        io.inputstring(currentName, MAX_NAME_LENGTH);

        io.outputstring("Name stored successfully.\n");
    }

    // Display all names
    io.outputstring("\nNames entered:\n");

    for (int i = 0; i < numberOfNames; ++i)
    {
        io.outputint(i + 1);
        io.outputstring(": ");
        io.outputstring(names + (i * MAX_NAME_LENGTH));
        io.terminate();
    }

    // Release the allocated memory
    syscall3(
        SYS_MUNMAP,
        (long)names,
        totalSize,
        0
    );

    return 0;
}
