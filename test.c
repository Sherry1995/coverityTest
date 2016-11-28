/*PLOVER: CODE.EVAL*/

/*
Description: System() is called with user-provided data.
Keywords: Size0 Complex0 Taint Unsafe
InvalidArg: "';kill -TERM $PPID'"
*/

#include <stdio.h>
#include <stdlib.h>

#define	MAXSIZE		40

void test1(char *str)
{
	char buf[MAXSIZE];

	vsnprintf(buf, sizeof buf, "/bin/echo %s", str);
	system(buf);				/* BAD */
}


void test2(void)
{
	char buf[MAXSIZE];

	if(gets(buf))					/* BAD */
		printf("result: %s\n", buf);
}


void test3(void)
{
	FILE *stream;
	char tempstring[] = "String to be written";
	if( (stream = tmpfile()) == NULL ) {
		perror("Could not open new temporary file\n");
		return;
	}
	printf( "Temporary file %d was created\n"); 
	
	_rmtmp();
}


int
main(int argc, char **argv)
{
	char *userstr;

	if(argc > 1){
		userstr = argv[1];
		test1(userstr);
		test2();
		test3();
	}
	return 0;
}

