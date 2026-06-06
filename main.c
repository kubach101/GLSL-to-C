#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin = fopen("input.glsl", "r");
    char buffer[1024] = {0};
    if (fin == NULL)
    {
        printf("\033[31mERROR:\033[0m No input file\ntemplate file generated-type your code there\n");
        fin = fopen("input.glsl", "w");
        fprintf(fin, "const char *vertexShaderSource =\n\n//Your vertex shader code\n\nconst char *fragmentShaderSource =\n\n//Your fragment shader code\n\n///");
        fclose(fin);
        return 1;
    }
    FILE *fout = fopen("output.c", "w");
    while (1)
    {
        fgets(buffer, sizeof(buffer), fin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strstr(buffer, "///"))
        {
            fprintf(fout, ";");
            break;
        }
        char *comment = strstr(buffer, "//");
        if (comment != NULL)
            *comment = '\0';
        if (strstr(buffer, "const char *vertexShaderSource ="))
        {
            fprintf(fout, "%s\n", buffer);
            continue;
        }
        if (strstr(buffer, "const char *fragmentShaderSource ="))
        {
            fprintf(fout, "; \n%s\n", buffer);
            continue;
        }
        fprintf(fout, "\"%s\\n\"\n", buffer);
    }
    fclose(fin);
    fclose(fout);
    printf("\033[32mFile written and saved sucesfully\033[0m");
    return 0;
}