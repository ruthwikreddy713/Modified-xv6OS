#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
int main(int argc, char *argv[])
{
	if(argc <2){
		printf(1,"Time <command> is the syntax\n");
		exit();
	}
	int newp;
	int a,b;
	newp=fork();
	if(newp==0){
		exec(argv[1],&argv[1]);
		printf(1,"exec %s failed\n",argv[1]);
		exit();
	}
	else {
		waitx(&a,&b);
		printf(1,"Wait time is %d\nRun Time is %d\n",a,b);
		exit();
	}
	exit();
}