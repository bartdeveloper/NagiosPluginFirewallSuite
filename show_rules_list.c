#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main()
{

	char *data = malloc(200);
	data = getenv("QUERY_STRING");

	printf("Content-type: text/html\n\n");
	printf("<html>\n");
	printf("<body>\n");
	printf("<h1>Rules list %s</h1>\n", data);

	DIR *dir;
	struct dirent *ent;
	
	if ((dir = opendir ("/usr/lib/nagios/plugins/firewall")) != NULL) {
  		
		while ((ent = readdir (dir)) != NULL) {
			
			const char *ext = strrchr(ent->d_name, '.');
			
			if(strstr(ent->d_name, data) != NULL && strcmp(ext, ".txt") == 0)
    			printf ("<li><a href='show.cgi?plik=%s'>%s</a></li><br>", ent->d_name, ent->d_name);
			
		}
	 
  	closedir (dir);
	
	} else {
		perror ("Problem with open file");
	}

  printf("</body>\n");
  printf("</html>\n");
 
  return 0;
}
