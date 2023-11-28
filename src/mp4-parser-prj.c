#include "mp4-parser-prj.h"

// Define and populate types
char *types[8] = {"moof", "mfhd", "traf", "tfhd", "trun", "uuid", "uuid", "mdat"};

// Struct to hold relevant data
struct BoxInfo 
{
    int start;
    int end;
    char type[5];
    int size;
    int boxIndex;
};

// Function to process and print the box information
void ft_processBox(char *file, struct BoxInfo *box) 
{
    if (box->boxIndex == 7) 
    {
        // Calculate the size of the mdat box
        box->size = box->end - (box->start - 8);
        printf("Found box of type %s and size %d \nContent of mdat box is: ", box->type, box->size);

        // Save the content of mdat to a file
        FILE *mdatFile = fopen("mdat_content.dat", "wb");

        if (mdatFile != NULL) 
        {
            for (int i = box->start; i < box->end; i++) 
            {
                // Print the content and write to the file
                printf("%c", file[i]);
                fputc(file[i], mdatFile);
            }
            fclose(mdatFile);
            printf("\nContent of mdat box saved to 'mdat_content.dat'\n");
        } 
        else 
            printf("Failed to open file for saving mdat content.\n");
    }
    else 
        printf("Found box of type %s and size %d \n", box->type, box->size);
}

// Function to extract box information from the file
void ft_extractBox(char *file, int *i, int size, int boxc) 
{
    struct BoxInfo box;
    unsigned char stsize[4];
    int count = 0;

    // Initialize box parameters
    box.end = size;
    box.start = *i - 4;

    // Extract box size from the file
    while (box.start <= *i && count < 4) 
    {
        stsize[count] = file[box.start++];
        box.size = stsize[count++];
    }
    count = 0;

    // Extract box type from the file
    while (file[box.start] == types[boxc][count] && count < 4)
        box.type[count++] = file[box.start++];

    // Set box index and process the box
    box.boxIndex = boxc;
    ft_processBox(file, &box);
}

// Function to parse the file
int ft_parseFile(char *file, int size) 
{
    int i = 0;
    int boxc = 0;

    // Iterate string
    while (i < size) 
    {
        // Check if the current substring matches a known box type
        if (boxc < 8 && strncmp(&file[i], types[boxc], 4) == 0) 
        {
            // Extract and process the box information
            ft_extractBox(file, &i, size, boxc);
            boxc++;

            // Added a check for the end of the file
            if (i >= size)
                break;
        }
        i++;
    }
    return 0;
}

// Function to read the file and call ft_parseFile
int ft_readFile(FILE *file, char *n_file) 
{
    // Define struct stat
    struct stat v;
    // Define string to read file
    char *alfile;
    // Use stat to have size file and save in struct v
    stat(n_file, &v);

    // Allocate memory to store file content
    alfile = malloc(v.st_size * sizeof(char));

    if (alfile == NULL) 
    {
        perror("Memory allocation failed");
        return 1; // Return an error code
    }

    // Read the file content into alfile
    fread(alfile, 1, v.st_size, file);

    // Parse the file content
    ft_parseFile(alfile, v.st_size);

    // Free allocated memory
    free(alfile);

    return 0;
}