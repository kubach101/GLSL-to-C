#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <windows.h>

int main()
{
    char exePath[256];
    GetModuleFileName(NULL, exePath, sizeof(exePath));
    char *last = strrchr(exePath, '\\');
    if (last)
        *last = '\0';

    char inputPath[256];
    char outputPath[256];
    snprintf(inputPath, sizeof(inputPath), "%s/../io/input.glsl", exePath);
    snprintf(outputPath, sizeof(outputPath), "%s/../io/output.c", exePath);

    FILE *fin = fopen(inputPath, "r");
    char buffer[1024] = {0};
    if (fin == NULL)
    {
        printf("\033[31mERROR:\033[0m No input file\ninput file generated, type your code there\n");
        fin = fopen(inputPath, "w");
        fprintf(fin, "//Type your shader code here");
        fclose(fin);
        return 1;
    }
    FILE *fout = fopen(outputPath, "w");
    int count;
    while (1)
    {
        if (fgets(buffer, sizeof(buffer), fin) == NULL)
            break;
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == '\0')
            continue;
        char *comment = strstr(buffer, "//");
        if (comment != NULL)
            *comment = '\0';
        if (buffer[0] == '\0')
            continue;
        fprintf(fout, "\"%s\\n\"\n", buffer);
    }
    fclose(fin);
    fclose(fout);
    printf("\033[32mFile written and saved sucesfully\033[0m");
    return 0;
}