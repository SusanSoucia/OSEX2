#include <syscall.h>
int pid, cid;
int full;
int empty;

#define NZERO 20
#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4d00
#define RIGHT 0x4b00

extern void drawBar(int barSize, int length, int lEdge, int upHead, COLORREF r);

void control(int pid,int cid){
	int p1 = 20, p2 = 20;
	
	setpriority(task_getid(), 0);
	setpriority(pid, p1);
	setpriority(cid, p2);
	int key;
	while(1){

		int temp1 = 0;int temp2 = 0;
		int rightPrio = getpriority(2);
		if(temp1 != rightPrio)
			drawBar(15, rightPrio*20, 410, 580, RGB(0,0,255));
		temp1 = rightPrio;
	
		
		int leftPrio = getpriority(3);
		if (temp2 != leftPrio)
			drawBar(15, leftPrio*20, 0, 580, RGB(0,0,255));
		temp2 = leftPrio;
			
		key = getchar();
		
		if(UP == key){
			if(p1 < (2 * NZERO - 1)){
				p1++;
				setpriority(pid, p1);
			}
		}
		else if(DOWN == key){
			if(p1 > 0){
				p1--;
				setpriority(pid, p1);
			}
		}
		else if(LEFT == key){
			if(p2 < (2 * NZERO - 1)){
				p2++;
				setpriority(cid, p2);
			}
		}
		else if(RIGHT == key){
			if(p2 > 0){
				p2--;
				setpriority(cid, p2);
			}
		}


	}
}
