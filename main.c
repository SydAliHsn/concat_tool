#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHelp();
int concatenate(char *sourceFileName, char *destinationFileName);

int main(int argc, char *argv[])
{
    int i, res;
    char *destinationFileName = argv[argc - 1];

    // If using the help switch.
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--h") == 0)
    {
        printHelp();
        return 0;
    }

    for (i = 1; i <= argc - 2; i++)
    {
        res = concatenate(argv[i], destinationFileName);

        if (res != 0)
            return 1;
    }

    return 0;
}

int concatenate(char *sourceFileName, char *destinationFileName)
{

    FILE *sourceFile, *destinationFile;

    // Open the source file in binary mode
    sourceFile = fopen(sourceFileName, "rb");
    if (sourceFile == NULL)
    {
        perror("Error opening source file");
        printf("\"%s\"\n", sourceFileName);
        return 1;
    }

    // Open the destination file in binary mode for writing
    destinationFile = fopen(destinationFileName, "ab");
    if (destinationFile == NULL)
    {
        perror("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }

    // Seek to the end of the source file to determine its size
    fseek(sourceFile, 0, SEEK_END);
    long fileSize = ftell(sourceFile);
    rewind(sourceFile); // Reset the file position indicator to the beginning

    // Allocate memory to store the source file content
    char *buffer = (char *)malloc(fileSize);
    if (buffer == NULL)
    {
        perror("Error allocating memory");
        fclose(sourceFile);
        fclose(destinationFile);
        return 1;
    }

    // Read the entire source file into the buffer
    size_t bytesRead = fread(buffer, 1, fileSize, sourceFile);

    if (bytesRead != fileSize)
    {
        perror("Error reading source file");
        free(buffer);
        fclose(sourceFile);
        fclose(destinationFile);
        return 1;
    }

    // Write the content of the buffer to the destination file
    size_t bytesWritten = fwrite(buffer, 1, bytesRead, destinationFile);

    if (bytesWritten != bytesRead)
    {
        perror("Error writing to destination file");
        free(buffer);
        fclose(sourceFile);
        fclose(destinationFile);
        return 1;
    }

    // Clean up
    free(buffer);
    fclose(sourceFile);
    fclose(destinationFile);

    return 0;
}

void printHelp()
{
    printf("\nUsage: ./concat_tool INPUT_FILES... OUTPUT_FILE\n\nConcatenate multiple files into a single output file.\n\n");

    printf("Options:\n-h, --help\tShow this help message and exit.\n\n");

    printf("Arguments:\nINPUT_FILES\tList of input files to be concatenated in the specified order.\nOUTPUT_FILE\tPath to the output file where the concatenated content will be saved.\n\n");

    printf("Example:\n./concat_tool file1.mp4 file2.mp4 file3.mp4 output.mp4");
}