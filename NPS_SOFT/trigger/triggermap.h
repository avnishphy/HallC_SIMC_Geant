#ifndef Trig_Head
#define Trig_Head

struct TrigCalo
{
  /*  register name               offset   description  (w-write, r-read, r/w-read/write)*/
  unsigned short Data;  //    00 r/w  Data register (r)
  unsigned short Off;// 02 r/w First threshold (offset an pied 2*8 bit )
  unsigned short Thres;//04 r/w High and Low threshold ( 2x8bit)
  unsigned short ActChan[11];//06 r/w active channel
  unsigned short Param;//1C r/w trigger parameter  3 bit : mode 3 bit: integration 2bit threshold type
  unsigned short Empty2;//1E
  unsigned short Reset;//20 r/w
};

struct PTrig
{
  unsigned short mode:3;
  unsigned short width:3;
  unsigned short thres:2;
};

struct LogicMod
{
  unsigned short empty;
  unsigned short Param;// param trigger
  unsigned short Freq;//
  unsigned short ClrIn;//
  unsigned short Valid;//
};

struct FanInOut
{
  unsigned short empty;
  unsigned short Freq;// 0x2 rw 8bit frequency from 0.53 Hz to 953
  unsigned short Delay;// 0x4 rw 4bit
  unsigned short Width;// 0x6  rw 4 bit
  unsigned short ClrIn;// 0x8 rw
  
};

struct test
{
 unsigned int Data;  //    00     Data register (r)
  unsigned int Thres:8;
  unsigned int Pied:8;//02 High Threshold
   unsigned int Thres2:8;
  unsigned int Pied2:8;//04 Low Threshold
   unsigned long ActChan[13];
};


struct TriggerEv
{
  unsigned long int THit1[7];
  unsigned long int THit2[7];
  unsigned char Somme [36*4];
  unsigned char PMT [42*4];
};
#endif
