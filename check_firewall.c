#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *trimwhitespace(char *str)
{
  char *end;

  while(isspace((unsigned char)*str)) str++;

  if(*str == 0) 
    return str;

  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  *(end+1) = 0;

  return str;
}

int main( int argc, char *argv[] )
{

	FILE *fp;
	char path[4096];

	popen("sudo iptables-save > /firewall/iptables.txt", "r");
	
	fp = popen("sudo iptables-save", "r");

	if (fp == NULL) {
 		printf("Problem with run command iptables-save\n" );
    		exit(1);
 	}

	int numINPUT = 0;
	int numOUTPUT = 0;
	int numFORWARD = 0;

 	while (fgets(path, sizeof(path), fp) != NULL) {

		char *token, *str, *tofree;

		tofree = str = strdup(path);
	
		int nr = 0;
	
		while ((token = strsep(&str, " "))){

			token = trimwhitespace(token);

			if(nr == 1 && strcmp("INPUT", token) == 0){
				numINPUT++;
			}

			if(nr == 1 && strcmp("OUTPUT", token) == 0){
				numOUTPUT++;
			}

			if(nr == 1 && strcmp("FORWARD", token) == 0){
				numFORWARD++;
			}
			
			nr++;
		
		}

		free(tofree);

  	}

	pclose(fp);

	if(numINPUT > 0 || numOUTPUT > 0 || numFORWARD > 0){

		printf("FIREWALL iptables ON [");
		
		printf("INPUT: %d / ", numINPUT); 
		printf("OUTPUT: %d / ", numOUTPUT);
		printf("FORWARD: %d ]\n", numFORWARD);

	} else {
		
		printf("FIREWALL iptables OFF\n");

		exit(1);
	
	}

  	return 0;
}