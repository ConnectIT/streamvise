#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Build with 
gcc -D NOLIB cit-helper.c  -o testcit-helper && ./testcit-helper
to test things with main function, 

or with
gcc -c cit-helper.c && gcc -o libcit-helper.so cit-helper.o --share 
to use it as a library..
*/


/*** PART1 : Generic functions ***/


/**
 * This function prints 2*whatever is given to it. 
 *
 * @todo: Get rid of it
 * @param int var to be print
 */
int myprint(int toprint){
	printf("here: %i", toprint);
	return 2*toprint;
}


/**
 * This function runs a shell command 
 *
 * @todo: Stop using "system()". Use a more appropriate execv function, in a new process etc.
 * @param char* the command to be run
 */
int runsystem(char* cmd){
	printf("*****   Running system command: %s\n",cmd);
	system(cmd);
	return 0;
}


/**
 * This function reads a setting from a configuration file (*filename input). The setting
 * read is returned. The delimiter used for each configuration file can be different,
 * so *delimiter input is required.
 *
 * @todo: Make debugging (DBG) printfs run only if debugging mode is ON
 * @param char * the filename of the file to be read
 * @param char * the name of the setting to be read
 * @param char * delimiter used for the specific configuration file
 */
char *readsetting(char *filename, char *setting, char *delimiter){

	printf("Looking for string %s in file %s\n", setting, filename);
	FILE *file;
	FILE *filetmp;
  size_t len = 0;
	char *line = NULL; //Will hold one line of the conf file
	char *ret = "Setting not found";


  if (file = fopen(filename,"r") ) {  //Open the file
    while ((getline(&line, &len, file)) != -1) { //Cycle through the lines

		  char tmp[1]; // TODO: maybe tmp should be defined as char *tmp[1] ???
		  sprintf(tmp, "%.*s\n", 1, &line[0]); //Save the line to a temporary variable

		  //Now do 2 checks:
		  //1. First character of line is not "#", so this is not a comment line
		  //2. Try to find the string we're looking for. If not null, we found it successfully.
		  if (strstr(tmp, "#") == NULL && strstr(line, setting) != NULL){ //This is our line!
			  strtok(line, delimiter);
			  //TODO: the following line creates problems
			  ret = strdup(strtok(NULL , delimiter));
		  } //This is not the line we were looking for.	
    }
	  fclose(file);
	  return ret;
  }
	  else{
		  printf("Error opening file %s!\n", filename);
		  return "fail";
	  }
}


/**
 * This function writes a setting to a configuration file (*filename input). The setting to
 * be written is *towrite and the setting's name is *setting. The delimiter used
 * for each configuration file can be different, so *delimiter input is required.
 * Returns 1 for success, -1 for failure
 *
 * @todo: Make debugging (DBG) printfs run only if debugging mode is ON
 * @param char * the filename of the file to be edited
 * @param char * the name of the setting to be written/edited
 * @param char * the value to be written
 * @param char * delimiter used for the specific configuration file
 */
int writesetting(char *filename, char *setting, char *towrite, char *delimiter){

	printf("Will write string %s in file %s, as setting %s\n", towrite, filename, setting);
	FILE *file;
	FILE *filetmp;
  size_t len = 0;
	char *line = NULL; //Will hold one line of the conf file
  int foundflag = 0; //Flag: Did we find the setting we were looking for? NOT found by default


	if (filetmp = fopen("/tmp/filetmp","w")) {
	  if (file = fopen(filename,"r") ) { // Open the file	
      printf("DBG: scanning through the lines\n");
	    while ((getline(&line, &len, file)) != -1) { //Scan through the lines

			  char tmp[100];	//TODO: maybe tmp should be defined as char *tmp[1] ???			
			  sprintf(tmp, "%.*s\n", 1, &line[0]); //Save the line to a temporary variable
     
			  //Now do 2 checks:
			  //1. First character of line is not "#", so this is not a comment line
			  //2. Try to find the string we're looking for. If not null, we found it!
			  if (strstr(tmp, "#") == NULL && strstr(line, setting) != NULL){ 
  					foundflag = 2; //The setting has been found
  		      printf("DBG: Setting found. Changing it\n");
				  //Is this about a dns setting?

        /*	TODO: Uncomment the following, in order to enable smart searching and writing

            if (strstr(setting, "option  dns") != NULL) {
  				  printf("This is a dns request.");
					
  				  strtok(line, delimiter); //Skip the line's first word
  				  strtok(NULL, delimiter); //Skip the line's second word
				    //If the third word is the same as the one we would write...
  				  if (strstr(towrite, strdup(strtok(NULL , delimiter))) != NULL) {
  				    fprintf(filetmp, "%s", line); //Just rewrite the line
  				  }else{//Append the line to the file
  				    fprintf(filetmp, "%s", line); //First rewrite the line
				      //Then append the new line:
  				    fprintf(filetmp,"%s%s%s\n", setting, delimiter, towrite);
  				  }
  				}else{ //This is not a DNS setting, just write the new value
      */
					  fprintf(filetmp,"%s%s%s\n", setting, delimiter, towrite);
 	    //	}
			  }else{ //This is not the line we were looking for. Rewrite it just to move the fprintf pointer.
				  fprintf(filetmp, "%s", line);
          printf("DBG: Not the line we're looking for. Rewriting it\n");
			  }			
      }


      if (foundflag == 0) { //If setting has not been found in file, write it
  			fprintf(filetmp,"%s%s%s\n", setting, delimiter, towrite);
  			printf("DBG: Setting not found, writing it\n");
  			foundflag = 0;
  		}
  		printf("DBG: Closing files\n");
		  fclose(file);
		  fclose(filetmp);

		  move_file("/tmp/filetmp", filename); //Move the temporary file over the original settings file, overwriting it
		  return 1;
	  }else{
		  printf("Error opening file %s!\n", filename);
		  return -1;
	  } //End else
	} //End if
}


/**
 * This function moves a file (source), to the destination, overwriting if destination file exists
 *
 * @todo: Remove commented printfs
 * @param char * the filename of the file to be used as source
 * @param char * the filename of the file to be used as destination
 */
move_file(char *src, char *dst){ 
	FILE *f1,*f2;
	char ch;
	f1=fopen(src,"r");
	if(f1==NULL)
		printf("Can't open the file");
	else {
		f2=fopen(dst,"w");
		while((ch=getc(f1))!=EOF)
			putc(ch,f2);
			
		fclose(f2);
		remove(src);
	}
	fclose(f1);
	return 0;
}


/*** PART2 : File-specific wrapper functions ***/

// Funtions for reading and writing UDHCPD settings


/**
 * This function writes a setting to the uDHCPd configuration file. Returns whatever the 
 * appropriate function returns.
 *
 * @todo: 
 * @param char * the name of the setting to be written/edited
 * @param char * the value to be written
 */
int writeudhcpd(char *setting, char *towrite){
	char file[]="/tmp/udhcpd.conf"; //UDHCPD configuration file
	return writesetting(file, setting, towrite, "	"); //TODO: maybe this delim should be two whitespaces?
}

/**
 * This function reads a setting from the uDHCPd configuration file. Returns whatever the 
 * appropriate function returns.
 *
 * @todo: 
 * @param char * the name of the setting to be read
 */
char *readudhcpd(char *tofind){
	char file[]="/tmp/udhcpd.conf"; //UDHCPD configuration file
	return readsetting(file, tofind, "	");
}


/*** PART3 : Test functions ***/

#ifdef NOLIB // Main function will be compiled only if we're running in debug mode, using the NOLIB option

/**
 * Main function. Used only for debugging purposes. Uncomment lines to test functions
 * apropriate function returns.
 *
 */
int main(){ 
  printf("*** Cit-helper Test Function starts running ***\n");

  //Test write setting:
  printf("Writing to uDHCPd config file...\n");
	writeudhcpd("option  lease", "4230");
	writeudhcpd("option  subnet", "4.5.5.11");
	//Test read setting:
	printf("Reading from uDHCPd config file...\nResult: %s\n", readudhcpd("option  lease"));
  printf("Reading from uDHCPd config file...\nResult: %s\n", readudhcpd("option  subnet"));
  printf("*** Cit-helper Test Function ends here ***\n");
	return 0;
}
#endif
