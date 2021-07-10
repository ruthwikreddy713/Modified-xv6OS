Running the file
make clean;
make qemu-nox  (this means default scheduler ROUND ROBIN HERE)
make qemu-nox SCHEDULER=<FCFS,PBS,MLFQ,DEFAULT>  (choose one and write without <>)
Here Default is Round Robin
PART 1:
1)Implementing waitx syscall and time user program
Defined syscall as we have to do in files like user.h usys.S and others 
Then implemented waitx syscall as given the return value should be similar to wait command so copied wait command and made changes added rtime,etime,ctime and iotime to the  proc struct as we need this for waitx.
ctime is creation time , etime is end time rtime is runtime iotime is time taken for io sleep 
rtime is p->rtime
wtime is p->etime - p->etime - p->rtime -  p->iotime 
etime is recorded at exit rtime iotime in trap.c ctime is ticks at allocation so allocproc function
implemented time.c which is used as time (command) which calls waitx and we get run time and wait time for the command
2)Imolementing ps userprogram
basically adding wtime to proc structure and looping through processblock and printing so cps is the systemcall  which does that ps userprogram (ps.c) calls cps and which prints
PART 2:
1) Implementing FCFS system call
in proc.c scheduler function we add #ifdef FCFS to see what was used in make qemu (flag)
    struct proc * firstp=0;
    for(p=ptable.proc;p<&ptable.proc[NPROC];p++){
      if(p->state!=RUNNABLE)
        continue;
      if(firstp==0){
        firstp=p;
      }
      else if (firstp->ctime > p->ctime){
        firstp=p;
      }
    }
    goto foundnowrun;
Here we  find the first one and run it
2) Priority based Scheduling 
added priority to the process  struct gave 60 as initial priority except for first 2 process which is 1,2
    struct proc *highpriorproc=0;
    for(p=ptable.proc;p<&ptable.proc[NPROC];p++){
      if(p->state!=RUNNABLE)
        continue;
      if (highpriorproc==0)
        highpriorproc=p;
      else if (highpriorproc->priority > p->priority){
        //comparing based on priority
        highpriorproc=p;
      }
      flag=1;
    }
    goto foundnowrun;
Changing when we get better process with lower priority

implementing set_priority system call changing it by looking for pid that's it
3) MLFQ
Added queue number number of ticks at each level and others to the proc struct
implemented aging as if a process waited for a long time then promoted to top queues or reducing the queue number 
Comparing all 4 algos for scheduling
Round Robin Default: 
$ time benchmark
Wait time is 2001
Run Time is 3
FCFS :
$ time benchmark
Wait time is 2217
Run Time is 3
PBS:
$ time benchmark
Wait time is 2000
Run Time is 3
MLFQ:
$ time benchmark
Wait time is 1998
Run Time is 5
We can see almost all are near 2.0s to 2.2s so almost all are similar PBS and RR are almost same.
MLFQ is better among all FCFS is comparitively not good here.