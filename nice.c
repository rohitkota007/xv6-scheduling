#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
	int priority, pid;
	if(argc < 3){
		printf(1, "Usage: nice pid priority\n");
		exit();
	}
	pid = atoi(argv[1]);
	priority = atoi(argv[2]);
	if(priority < 0 || priority > 50){
		printf(1,"Invalid priority");
		exit();
	}
	set_priority(priority, pid);
	exit();
}

