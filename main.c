#include "parser.h"

int ft_readFiles(FILE *file, char *n_file);

int main(int argc, char **argv)
{
    if (argc != 2) 
    {
        printf("Execute program with a file as an argument.\n");
        return 1; // Return an error code
    }

    // Check if filename is passed 
    if(argc != 1)
    {
        // Create a file pointer
        FILE *fptr;

        // Attempt to open file in read mode
        fptr = fopen(argv[1], "rb");

        // Check if file is open, proceed to read file in next function
        if (fptr != NULL)
            ft_readFiles(fptr, argv[1]);
        else
            printf("Not able to open the file.");

        // Close the file
        fclose(fptr);
    }
    return 0;
}
