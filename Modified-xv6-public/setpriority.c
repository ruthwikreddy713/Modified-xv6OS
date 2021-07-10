#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
int main(int argc, char const *argv[])
{
	if(argc!=3){
		printf(1,"The usage is set_priority newpriority pid");
		exit();
	}	
	int oldpr= set_priority(atoi(argv[1]),atoi(argv[2]));
	if(oldpr==-1){
		printf(1,"Give valid priority or pid errpr\n");
		exit();
	}
	else {
		printf(1,"Changed the priority of the process %d\n",oldpr);
		exit();
	}
}