#include<sys/syscall.h>
#include<sys/defs.h>
#include<sys/virtualMemory.h>
#include<sys/kprintf.h>

#define MSR_EFER 0xC0000080
#define MSR_STAR 0xC0000081
#define MSR_LSTAR 0xC0000082
#define MSR_SFMASK  0xC0000084

uint64_t* userRSP = 0;
uint64_t* kernelRSP = 0;

uint64_t readMSR(uint32_t msrAddr)
{
    uint32_t msrLow, msrHigh;
    __asm__ __volatile__ ( "rdmsr" : "=a" (msrLow), "=d" (msrHigh) : "c" (msrAddr));
    return (uint64_t)msrHigh<<32|(uint64_t)msrLow;
}

uint64_t syscallHandler(uint64_t paramA,uint64_t paramB,uint64_t paramC,uint64_t paramD,uint64_t paramE,uint64_t paramF,uint64_t syscallNum) {
    kprintf("%d %d %d %d %d %d %d",syscallNum,paramA,paramB,paramC,paramD,paramE,paramF);
    return 100;
}

uint64_t syscall(uint64_t syscallNum,uint64_t param1,uint64_t param2,uint64_t param3,uint64_t param4,uint64_t param5,uint64_t param6) {
    uint64_t returnValue;
    __asm__ volatile ("movq %1, %%rax; movq %2, %%rdi; movq %3, %%rsi; movq %4, %%rdx; movq %5, %%r10; movq %6, %%r8;movq %7, %%r9;syscall;movq %%rax, %0;":"=g"(returnValue):"g"(syscallNum),"g"(param1),"g"(param2),"g"(param3),"g"(param4),"g"(param5),"g"(param6):"%rax","%rdi","%rsi","%rdx","%r10","%r8","%r9","memory");//clobber list
    return returnValue;
}

void writeMSR(uint64_t value,uint32_t msrAddr)
{
    uint32_t msrLow;
    uint32_t msrHigh;
    msrLow=(uint32_t)value;
    msrHigh=(uint32_t)(value>>32);
     __asm__ __volatile__ ("wrmsr"::"a"(msrLow),"d"(msrHigh),"c"(msrAddr));
}

void _syscallEntry();

void initSyscalls()
{
    kernelRSP = (uint64_t*)kmalloc();
    //STEP1: set the system call extension bit (SCE bit) to 1;
    uint64_t sce = readMSR(MSR_EFER);
    sce |= (0x1); //enable syscalls
    writeMSR(sce,MSR_EFER);
    
    writeMSR(1<<9,MSR_SFMASK);
    
    writeMSR((uint64_t)0x8<<32|(uint64_t)0x1B<<48,MSR_STAR);
    
    writeMSR((uint64_t)_syscallEntry,MSR_LSTAR);
    
    
    
}