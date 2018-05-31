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


#define MISA        0x301
#define MVENDORID   0xF11
#define MARCHID     0xF12
#define MIMPID      0xF13

#define ADDS        0
#define EN_W        1
#define EN_R        2
#define DATA        3
#define DATA_O      4



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
          return resultado;

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
 
