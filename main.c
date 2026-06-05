#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin = fopen("input.txt", "r");
    char buffer[1024] = {0};
    char seg_check[2] = {0};
    if (fin == NULL)
    {
        printf("Error: no input file\n");
        fin = fopen("input.txt", "w");
        fprintf(fin, "const char *vertexShaderSource =\n\n\n\n\nconst char *fragmentShaderSource =\n//");
        fclose(fin);
        return 1;
    }
    FILE *fout = fopen("output.txt", "w");
    while (1)
    {
        fgets(buffer, sizeof(buffer), fin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strncmp(buffer, "//", 2) == 0)
            break;
        if (strcmp(buffer, "const char *vertexShaderSource =") == 0 ||
            strcmp(buffer, "const char *fragmentShaderSource =") == 0)
        {
            fprintf(fout, "%s\n", buffer);
            continue;
        }
        fprintf(fout, "\"%s\\n\"\n", buffer);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}