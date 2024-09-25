#!/usr/bin/gawk -f

function eventcmp ( E1, E2, e1, e2 )
{
   split(E1, e1, ":")
   split(E2, e2, ":")
   e1[3] = int(e1[3])
   e2[3] = int(e2[3])
   if ((e1[1] == e2[1]) && (e1[2] == e2[2]) && (e1[3] == e2[3])) return 0
   if (e1[3]<e2[3]) return -1
   if (e1[3]>e2[3]) return 1
   if (e1[2] != e2[2]) {
      if (e1[2] == "ARRIVAL") return -1;
      if (e2[2] == "ARRIVAL") return 1;
      if (e1[2] == "IODONE") return -1;
      if (e2[2] == "IODONE") return 1;
   }
   if (e1[1] < e2[1]) return -1;
   return 1;
}

function EQins ( x, i, j )
{
   i = 1
   while ( (i <= EQsize) && (eventcmp(x,EQ[i]) > 0) ) ++i
   ++EQsize
   for (j=EQsize; j>i; --j) EQ[j] = EQ[j-1]
   EQ[i] = x
}

function EQdel ( i, e )
{
   if (EQsize == 0) {
      print "*** Error: EQ is empty"
      return 0
   }
   e = EQ[1]
   for (i=1; i<EQsize; ++i) EQ[i] = EQ[i+1]
   --EQsize
   return e
}

function printqueues ( pr, i )
{
   printf("[At time %d]\n", currtime)
   for (pr=1; pr<=3; ++pr) {
      printf("   Q%d:", pr)
      for (i=F[pr]; i<=B[pr]; ++i) printf(" %s", Q[pr,i])
      printf("\n")
   }
}

BEGIN {
   FS = ","
   EQsize = 0
   F[1] = F[2] = F[3] = 1
   B[1] = B[2] = B[3] = 0
   N[1] = N[2] = N[3] = 0
   TWT[1] = TWT[2] = TWT[3] = 0
}

{
   priority[$1] = int($2)
   ++N[priority[$1]]
   NBR[$1] = NF - 3
   for (i=4; i<=NF; ++i) BT[$1,i-3] = $i
   CBR[$1] = 0
   evstr = sprintf("%s:ARRIVAL:%s", $1, $3)
   EQins(evstr)
}

END {
   currtime = 0
   cpuidle = 1
   split(EQ[1], ev, ":");
   ev[3] = int(ev[3])
   if (ev[3] > 0) {
      printf("[%d--%d] CPU idle\n", currtime, ev[3])
   } 
   while (EQsize > 0) {
      nextevent = EQdel()
      split(nextevent, ev, ":")
      currtime = int(ev[3])
      if ((ev[2] == "ARRIVAL") || (ev[2] == "IODONE")) {
         pr = priority[ev[1]]
         ++B[pr]
         Q[pr,B[pr]] = ev[1]
         ST[ev[1]] = currtime
         if (ev[2] == "ARRIVAL") print "\t\t\t\t\t\t[" currtime "] " ev[1] " arrives"
         else print "\t\t\t\t\t\t[" currtime "] " ev[1] " completes IO"
      } else {
         if (NBR[ev[1]] == CBR[ev[1]]) {
            print "\t\t\t\t\t\t[" currtime "] " ev[1] " terminates"
         } else {
            ++CBR[ev[1]]
            evstr = sprintf("%s:IODONE:%d", ev[1], currtime + BT[ev[1], CBR[ev[1]]])
            EQins(evstr)
            print "\t\t\t\t\t\t[" currtime "] " ev[1] " starts IO"
         }
         cpuidle = 1
      }
      if (cpuidle == 1) {
         printqueues()
         if (B[1] >= F[1]) pr = 1
         else if (B[2] >= F[2]) pr = 2
         else if (B[3] >= F[3]) pr = 3
         else pr = 0
         if (pr > 0) {
            proc = Q[pr,F[pr]]
            TWT[pr] += (currtime - ST[proc])
            ++F[pr]
            ++CBR[proc]
            printf("[%d--%d] CPU runs %s\n", currtime, currtime + BT[proc, CBR[proc]], proc)
            evstr = sprintf("%s:CPUDONE:%d", proc, currtime + BT[proc, CBR[proc]])
            EQins(evstr)
            cpuidle = 0
         } else {
            if (EQsize > 0) {
               split(EQ[1], ev, ":");
               printf("[%d--%d] CPU idle\n", currtime, ev[3])
            } else {
               printf("[%d] CPU done with all processes\n", currtime)
               printf("[%d] CPU done with all processes\n", currtime) > "/dev/stderr"
            }
         }
      }
   }
   for (pr=1; pr<=3; ++pr) 
   {
       avg_wait_time = TWT[pr] / N[pr]
       printf("+++ Average wait time for priority %d processes = %f\n", pr, avg_wait_time)
       printf("+++ Average wait time for priority %d processes = %f\n", pr, avg_wait_time) > "/dev/stderr"
   }
    printf("+++ Refer for details : CPUTime.txt \n") > "/dev/stderr"
}
