/*
On the STM32, some magic is worked internally so that each bit in a pre-defined memory range can be addressed as another location in a kind of virtual address space somewhere else. So, for example, the 32 bit value stored at address 0x20000000 also appears as 32 sequential memory locations starting at 0x22000000. There are two regions of memory that have bit-band alias regions. First there is a 1Mbyte SRAM region from 0x20000000 – 0x20100000 where each bit is aliases by a byte address in the range 0x22000000 – 0x23FFFFFF. Then there is the peripheral space from 0x40000000 – 0x40100000 which is aliased in the same way to the range 0x42000000 – 0x43FFFFFF.

Using this scheme, a read or write to memory location 0x22000000 is the same as a read or write to the least significant bit of SRAM location 0x20000000. I have no intention of going through the whole thing.

If you want to find out more about this and many other dark STM32 secrets, read the excellent book by Joseph Yiu – The Definitive Guide to the Arm Cortex – M3

The Peripheral Library, among other sources, provides us C programmers with macros to do the address translation. They look like this for the SRAM memory space:
*/

#define RAM_BASE 0x20000000
#define RAM_BB_BASE 0x22000000

#define Var_ResetBit_BB(VarAddr, BitNumber)
(*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)

#define Var_SetBit_BB(VarAddr, BitNumber)
(*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Var_GetBit_BB(VarAddr, BitNumber)
(*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))

/*
These are all well and good but not too intuitive to use. Even if you understand what they do. Rather than mess with these, I define a couple of additional versions that look like this:
*/

#define varSetBit(var,bit) (Var_SetBit_BB((u32)&var,bit))
#define varGetBit(var,bit) (Var_GetBit_BB((u32)&var,bit))
#define varGetBit(var,bit) (Var_GetBit_BB((u32)&var,bit))

// Using these macros is quite simple. The following are all legitimate ways to use them:


uint32_t flags;
uint32_t status;
varSetBit(flags,1);
varSetBit(flags,READY_BIT);
varClrBit(flags,3);
ready = varGetBit(flags,READY_BIT);

// It is interesting to note that the varGetBit macro is an LValue so that it can be used in an assignment like this:


varGetBit(flags,4) = y;
varGetBit(flags,ARRIVED) = varGetBit(status,READY);
  /*
  These methods are not primarily about speed but convenience. 
  The compiler cannot know where the variables will be stored when the code 
  is generated so you will see some of the calculations done at run time by your program. 
  However, if you use the pointer method in the code fragment above, the calculation of 
  the alias address is done only once and you will be able to get to the bit variables 
  quite efficiently after that. To access bits in the peripheral registers, you use the 
  exact same technique but with different base registers. There is, of course, no reason 
  why you could not define a macro that refers to a specific bit in a peripheral register 
  at a known address. Then you get the addresses completely pre-calculated by the compiler 
  and the most efficient code since the peripheral register addresses are known at compile time.
  */
