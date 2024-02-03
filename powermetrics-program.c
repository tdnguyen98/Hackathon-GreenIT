#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char path[1035];

    /* Open the command for reading. */
    fp = popen("/usr/bin/sudo /usr/bin/powermetrics --samplers cpu_power", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        if (strstr(path, "Combined Power") != NULL) {
            printf("%s", path);
        }
    }

    /* close */
    pclose(fp);

    return 0;
}