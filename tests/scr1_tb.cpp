/*
* ALU Module - TestBench
* Anderson Contreras
* Adaptado a scr1 por MANUEL HURTADO
*/


#include <iostream>

#include "Vscr1.h"
#include "testbench.h"


#define OK_COLOR    "\033[0;32m"
#define ERROR_COLOR "\033[0;31m"
#define NO_COLOR    "\033[m"

#define DATA0       0x000
#define DATA1       0x001
#define DATA2       0x002
#define DATA3       0X003
#define DATA4       0x004
#define DATA5       0x005
#define DATA6       0x006
        32'B111100010100 : REGISTER[32'B00101][31:0] <= DATA_I; // 5 MHARTID			0XF14
        32'B001101000010 : REGISTER[32'B00110][31:0] <= DATA_I; // 6 MCAUSE				0X342
        32'B001100000000 : REGISTER[32'B00111][31:0] <= DATA_I; // 7 MTATUS				0X300
        32'B001100000101 : REGISTER[32'B01000][31:0] <= DATA_I; // 8 MTVEC				0X305
        32'B001101000001 : REGISTER[32'B01001][31:0] <= DATA_I; // 9 MEPC				0X341
        32'B001101000100 : REGISTER[32'B01010][31:0] <= DATA_I; // 10 MIP 				0X344
        32'B001100000100 : REGISTER[32'B01011][31:0] <= DATA_I; // 11 MIE 				0X304
        32'B101100000000 : REGISTER[32'B01100][31:0] <= DATA_I; // 12 MCYCLE 			0XB00
        32'B101110000000 : REGISTER[32'B01101][31:0] <= DATA_I; // 13 MYCLEH 			0XB80
        32'B101100000010 : REGISTER[32'B01110][31:0] <= DATA_I; // 14 MINSTRET 			0XB02
        32'B101110000010 : REGISTER[32'B01111][31:0] <= DATA_I; // 15 MINSTRETH 		0XB82
        32'B001100000110 : REGISTER[32'B10000][31:0] <= DATA_I; // 16 MCOUNTEREN  		0X306


#define MISA        0x301
#define MVENDORID   0x011
#define MARCHID     0x012
#define MIMPID      0x013
#define MHARTID     0x014  
#define MCAUSE      0x342
#define MSTATUS     0x300
#define MTVEC       0x305
#define MEPC        0x341
#define MIP         0x344
#define MCYCLE      0x304
#define MYCLEH      0xb00
#define MINSTRET    0xb80
#define MINSTRETH   0xb82
#define MCOUNTEREN  0x306


#define ADDS        0
#define EN_W        1
#define EN_R        2
#define DATA        3
#define DATA_O      4
//


#define TOTAL_TESTS 12


using namespace std;

class SIMULATIONTB: public Testbench<Vscr1> {
  public:
    // -----------------------------------------------------------------------------
    // Testbench constructor
    SIMULATIONTB(double frequency=1e6, double timescale=1e-9): Testbench(frequency, timescale) {}

    int Simulate(unsigned long max_time=1000000){
      Reset();

      // Test data    [ADDS | EN_WRITE | ENREAD | DATA | DATA OUT]
      
      int resultado=0;
      
      int data[TOTAL_TESTS][5] = {                               //             Operation          | Equal | Less than | Less than (unsigned)
//           [ADDRESS | EN_W | EN_R | DATA | DATA_O]
        {      MISA,        1,       0,     DATA1  , DATA0},    // guarda DATA1 en misa
        {      MISA,        0,       1,     DATA1  , DATA1},    // guarda DATA1 en misa
        {      MVENDORID,   1,       0,     DATA2  , DATA0},    // guarda DATA2 en misa
        {      MVENDORID,   0,       1,     DATA2  , DATA2},    // guarda DATA2 en misa
        {      MISA,        1,       0,     DATA3  , DATA0},    // guarda DATA3 en misa
        {      MISA,        0,       1,     DATA3  , DATA3},    // guarda DATA3 en misa
        {      MISA,        1,       0,     DATA4  , DATA0},    // guarda DATA4 en misa
        {      MISA,        0,       1,     DATA4  , DATA4},    // guarda DATA4 en misa
        {      MISA,        1,       0,     DATA5  , DATA0},    // guarda DATA5 en misa
        {      MISA,        0,       1,     DATA5  , DATA5},    // guarda DATA5 en misa
        {      MISA,        1,       0,     DATA6  , DATA0},    // guarda DATA6 en misa
        {      MISA,        0,       1,     DATA6  , DATA6},    // guarda DATA6 en misa
      };

      for (int num_test = 0; num_test < TOTAL_TESTS; num_test++) {


        m_core->address_i = data[num_test][ADDS];

        if(data[num_test][EN_R]==1)
        {
          printf(OK_COLOR "[OK]" NO_COLOR " %d ",m_core->data_out_o);
          
          if(data[num_test][DATA_O]==m_core->data_out_o)
            resultado++;

        };
        m_core->en_read_i = data[num_test][EN_R];
        m_core->en_write_i = data[num_test][EN_W] ;
        m_core->data_i = data[num_test][DATA];       
   
        Tick();
        
        if(num_test==TOTAL_TESTS)
          return num_test;
        
      }
    }
 };


int main(int argc, char **argv, char **env) {
  std::unique_ptr<SIMULATIONTB> tb(new SIMULATIONTB());

  tb->OpenTrace("alu.vcd");

  int ret = tb->Simulate();

  printf("\nALU Testbench:\n");

  if(ret == 6)
    printf(OK_COLOR "[OK]" NO_COLOR " Test Passed! ");
  else
    printf(ERROR_COLOR "[FAILED]" NO_COLOR " Test Failed! ");

  printf("Complete: %d/%d\n", ret, TOTAL_TESTS);

  exit(0);
}
 
