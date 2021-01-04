
// Fil
//:	shell.c
//
// Purpose:	This program implements a simple shell program. It does not start
//		processes at this point in time. However, it will change directory
//		and list the contents of the current directory.
//
//		The commands are:
//		   cd name -> change to directory name, print an error if the directory doesn't exist.
//		              If there is no parameter, then change to the home directory.
//		   ls -> list the entries in the current directory.
//			      If no arguments, then ignores entries starting with .
//			      If -a then all entries
//		   pwd -> print the current directory.
//		   exit -> exit the shell (default exit value 0)
//
//		if the command is not recognized an error is printed.
//-

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <ctype.h>

#define CMD_BUFFSIZE 1024
#define MAXARGS 10

int splitCommandLine(char * commandBuffer, char* args[], int maxargs);
void doCommand(char * args[], int nargs);

int main() {

    char commandBuffer[CMD_BUFFSIZE];
    char *args[MAXARGS];

    // print prompt.. fflush is needed because
    // stdout is line buffered, and won't
    // write to terminal until newline
    printf("%%> ");
    fflush(stdout);

    while(fgets(commandBuffer,CMD_BUFFSIZE,stdin) != NULL){

		//Remove newline at end of buffer
       		int j= 0;
		while(commandBuffer[j] !='\n'){
		j++;
	}
		commandBuffer[j] = '\0';
	int nargs = splitCommandLine(commandBuffer,args,MAXARGS);
//	Debugging for step 2
//		printf("%d\n",nargs);
//	int  i;
//	for(i=0;i<nargs;i++){
//	printf("%d: %s\n",i,args[i]);
//	}
	  
	// Execute the command
	if (nargs != 0){       //ensure that input is  not null
	doCommand(args,nargs);}  //get the command as input and match the specific function
	      printf("%%> ");
	fflush(stdout);  //
}
 }
////////////////////////////// String Handling ///////////////////////////////////

//+
// Function:	skipChar
//
// Purpose:	This function skips over a given char in a string
//		For security, the function will not skip null chars.
//
// Parameters:
//    charPtr	Pointer to string
//    skip	character to skip
//
// Returns:	Pointer to first character after skipped chars.
//		Identity function if the string doesn't start with skip,
//		or skip is the null character
//-

char * skipChar(char * charPtr, char skip){

	while(*charPtr != '\0'){  //enter into function if ccommandbuffer is not null
		if(*charPtr == skip) //if it has space
		charPtr ++;  	     //pointer increment
		else

		break;
		
		}
		return  charPtr; //return the pointer which points to the first address of the character
}

//+
// Function:	splitCommandLine
//
// Purpose:	This splits a string into an array of strings.
//		The array is passed as an argument. The string
//		is modified by replacing some of the space characters
//		with null characters to terminate each of the strings.
//
// Parameters:
//	commandBuffer	The string to split
//	args		An array of char pointers
//	maxargs		Size of array args (max number of arguments)
//
// Returns:	Number of arguments (< maxargs).
//
//-

int splitCommandLine(char * commandBuffer, char* args[], int maxargs){
   
   int count = 0;  //count the number of pointer stored in the array
   char * next = commandBuffer;//"next"pointer points to the  first  character
   while(1){
   
  	 next = skipChar(next, ' ');//"next" pointer points to the first word in the array

	if(*next == '\0'){//reaches the end of array
	count--;
	break;
	}
	
	args[count++] = next;//store pointer into array, array size increases
	
	 if(strchr(next, ' ')=='\0')//check if next word exists in the array
	 {
	 break;
	 }
  	 
  	 

   next = strchr(next,' ');
   *next = '\0';
   next++;
   }
   
   if(count>maxargs){
   	fprintf(stderr, "the amount of elements in the array is greater than the size of the array");
	return -1;  //retturn size of args[]
   
   
} 
return count; 

}   // errors that are encountered to stderr.


////////////////////////////// Command Handling ///////////////////////////////////

//typedef for pointer to command handling functions
typedef void (*functionPointer)(char*args [], int nargs);

struct commandStruct {

	char* commandName;
	functionPointer commandHandler;
};
	// protoypes for command handling functions
	void exitFunc(char* args[], int nargs);
        void pwdFunc(char* args[], int nargs);
	void lsFunc(char* args[], int nargs);
	void cdFunc(char* args[], int nargs);
	int funcFilter(const struct dirent *d);

	struct commandStruct  commanarray[]={
	{"pwd", pwdFunc},
	{"ls", lsFunc},
	{"cd", cdFunc},
	{"exit",exitFunc},
	{NULL, NULL}
};
//+
// Function:	doCommand
//
// Purpose:	This command calls a command handling funciton from
//		the commands array based on the first argument passed
//		in the args array.
//
// Parameters:
//	args	command and parameters, an array of pointers to strings
//	nargs	number of entries in the args array
//
// Returns	nothing (void)
//-

void doCommand(char * args[], int nargs){
  int i = 0;
  while(commanarray[i].commandName!= NULL ){
	if(strcmp(commanarray[i].commandName,args[0])==0){
	commanarray[i].commandHandler(args,nargs);
		return;
		}
		i++;
	}
	fprintf(stderr,"Command not recognized");
}
//////////////////////////////////////////////////
//            command Handling Functions        //
//////////////////////////////////////////////////
// all command handling functions have the same
// parameter types and return values.
//////////////////////////////////////////////////

//+
// Function:	all handling functions
//
// Purpose:	this command performs the funcdtion
//		associated with the commands.
//		The name of the comomand is in first argument.
//	 	Since it is called by doCommand, it is known
//		that arg is at least one element long
//
// Parameters:
//	args	command and parameters, an array of pointers to strings
//	nargs	number of entries in the args array
//
// Returns	nothing (void)
//-
// exit function will exit the program
void exitFunc(char*args[], int nargs){
	e/xit(0);
}
// pwd function will print the current working directory
void pwdFunc(char* args[], int nargs){
	char*cwd = getcwd(NULL,0);
	printf("%s\n",cwd);
	free(cwd);
}
// cd function will change the directory
void cdFunc(char*args[], int nargs){
	if(nargs == 1){
	struct passwd *pw = getpwuid(getuid());
		if(pw == NULL){
			fprintf(stderr, "Could not find the name of the homw directory");
		//	return;
		}
		if(chdir(pw->pw_dir)!= 0){
			fprintf(stderr, "Could not change to the directory %s successfully", pw->pw_dir);
		}
	}else if(nargs >=2){
		if(chdir(args[1])!=0){
			fprintf(stderr, " Could not change the directory to %s ",args[1] );
	
		}
	}
}

// check the names that start with dot
int funcFilter(const struct dirent *d){
	char *start = (*d).d_name;
	if(*start =='.' ){ 
		return 0;
	}
	return 1;
}

// ls function will list the files in the directory
void lsFunc(char*args[],int nargs){

int i;
if(nargs== 1){
	struct dirent **namelist;
	int numEnts = scandir(".", &namelist,funcFilter, NULL);
		for(i=0; i<numEnts; i++){
			printf("%s\n",namelist[i]->d_name);
		}
	}else if(nargs>=2){
		if(strcmp(args[1],"-a")!=0){
		printf("Could not find the command\n");
		}else{
		
		struct dirent **namelist;
		int numEnts = scandir(".", &namelist,NULL ,NULL );
		for(i= 0; i<numEnts; i++){
			printf("%s\n", namelist[i]->d_name);
		}
		}
	
	
	}
	
}









