#ifndef _CPUTIME_H

#define _CPUTIME_H

/* This should be max clock frequency, not the actual one -- so, the
   information in /proc/cpuinfo may not be acurate. Also, note that
   /proc/cpuinfo should contain constant_tsc, for the timing to be
   accurate. */

static const double iCPS = 1.0/1861913000.0; /* (t2-t1)*iCPS = time taken in seconds */
/*static const double iCPS = 1.0/2327500000.0;*/

static __inline__ unsigned long long int cputime(void)
  {
    unsigned long long int lo,hi;

    /* Note: to avoid out-of-order execution, cpuid can be used. But it reduces the resolution of the timer */
    /* unsigned long long int eax, ebx, ecx, edx;
    const unsigned long long in=0;

     __asm__ __volatile__ ("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(in)); */

    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));

    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
  }


#endif
