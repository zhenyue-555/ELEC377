/*+
 * Module:  lab2.c
 *
 * Purpose: Skeleton solution to ELEC 377 Lab2.
 *
-*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#define	  K   (PAGE_SIZE>>10)	 
//ii
static struct task_struct * firstTask, *theTask;

int cnt;

int my_read_proc(char * page, char **start, off_t fpos, int blen, int * eof, void * data){

    int numChars;
    if (fpos == 0){
	//numChars = sprintf(page,"Hello");
	//numChars += sprintf(page + numChars, "World\n");
	numChars = sprintf(page, " PID    UID    VSZ    RSS\n");
	//numChars += sprintf(page + numChars, "%4d %4d",firstTask->pid, firstTask->uid);	
	theTask = &init_task;
	while(theTask->pid == 0){
		theTask = theTask->next_task;	
	}
	firstTask = theTask;
	numChars += sprintf(page + numChars, "%4d   %4d",theTask->pid, theTask->uid);
	
	if(theTask->mm == NULL){
		numChars += sprintf(page + numChars, "   0      0\n");
	}else{
		numChars += sprintf(page + numChars, "   %4d   %4d\n", (theTask->mm->total_vm)*K,(theTask->mm->rss)*K);
	}
	do{
		theTask = theTask->next_task;
	}while(theTask->pid == 0);
	// find first task
        // write first task
        // advance to next task
    } else {
	if (theTask==firstTask){
            *eof = 0;
            *start = page;
            return 0;
	    
	}
	numChars = sprintf(page,"%4d   ", theTask->pid);
	numChars += sprintf(page + numChars, "%4d   ", theTask->uid);
	if(theTask->mm == NULL){
		numChars +=sprintf(page + numChars, "   0      0\n");
	}else{
	int vm = (theTask->mm->total_vm)*K;
	int rss = (theTask->mm->rss)*K;
		numChars += sprintf(page + numChars, "%4d   ",    vm);
		numChars += sprintf(page + numChars, "%4d\n", rss);
	}
	do{
		theTask = theTask->next_task;
	}while(theTask->pid == 0);	


//	theTask = theTask->next_task;
	// write task info for one task
	}    // advance to next task
    *eof = 1;
    *start = page;
    return numChars;
}

int init_module(){
   struct proc_dir_entry * proc_entry;
   proc_entry = create_proc_entry("lab2",0444,NULL);
   if(proc_entry == NULL){
   	return -1;
	}
   	proc_entry->read_proc = my_read_proc;
	return 0;
   
}

void cleanup_module(){
	remove_proc_entry("lab2", NULL);

}
