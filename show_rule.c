#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main (int argc, char *argv[]) {

  printf("Content-type: text/html\n\n");
  printf("<html>\n");
  printf("<body>\n");
  printf("<h1>Content of rule</h1>\n");

  char *data = malloc(200);
  data = getenv("QUERY_STRING");

  printf("%s<br><br>", data);

  const char delim[2] = "=";

  char* token = strtok(data, delim);
  token = strtok(NULL, delim);

  int c;
  FILE *file;
  char *kat = "/usr/lib/nagios/plugins/firewall/";

  char buf[256];
  snprintf(buf, sizeof buf, "%s%s", kat, token);

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(buf, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    printf("<pre>");

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s<br>", line);
    }

    printf("</pre>");

    fclose(fp);
    if (line)
        free(line);

  printf("</body>\n");
  printf("</html>\n");
 
  return 0;
}
