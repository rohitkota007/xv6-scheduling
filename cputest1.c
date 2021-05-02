#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "rand.h"

int getrandom(int tickets) {
  if(tickets <= 0) {
    return 1;
  }

  static int z1 = 12345; // 12345 for rest of zx
  static int z2 = 12345; // 12345 for rest of zx
  static int z3 = 12345; // 12345 for rest of zx
  static int z4 = 12345; // 12345 for rest of zx

  int b;
  b = (((z1 << 6) ^ z1) >> 13);
  z1 = (((z1 & 4294967294) << 18) ^ b);
  b = (((z2 << 2) ^ z2) >> 27);
  z2 = (((z2 & 4294967288) << 2) ^ b);
  b = (((z3 << 13) ^ z3) >> 21);
  z3 = (((z3 & 4294967280) << 7) ^ b);
  b = (((z4 << 3) ^ z4) >> 12);
  z4 = (((z4 & 4294967168) << 13) ^ b);

  // if we have an argument, then we can use it
  int rand = ((z1 ^ z2 ^ z3 ^ z4)) % tickets;

  if(rand < 0) {
    rand = rand * -1;
  }

  return rand;
}


int main(int argc, char *argv[]){
	int i, id, j, n, z;
	int wtime, rtime;
        int pid;
	int x = 0;
	if(argc < 2)
		n = 1;
	else if(argc == 2)
		n = atoi(argv[1]);
	else{
		printf(1, "Usage: prog  noofproc\n");
		exit();
	}
	set_tickets(10);
	printf(1, "no is %d\n", n);
	for(i = 0; i < n; i++){
		id = fork();
		if(id == 0){
			  int t = getrandom(i);
			  set_tickets(t);
			  printf(1, "pid %d tickets %d\n", getpid(), t);			
			  for(j = 0; j < 10000; j++){
				for (z = 0; z < 100000; z++){
					x =  x + 100 * 100;  
				}
			  }
			break;
		}
	}
	for(i = 0; i < n; i++){
		pid = wait2(&wtime, &rtime);
		if(pid != -1)
			printf(1, "pid %d, waiting time %d, running time %d\n", pid, wtime, rtime);
	}
	exit();
}
