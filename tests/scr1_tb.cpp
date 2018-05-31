/*
* scr1 - TestBench
* By Adrián González
*/

#include <iostream>
#include <stdint.h>
#include "Vscr1.h"
#include "testbench.h"


#define OK_COLOR    "\033[0;32m"
#define ERROR_COLOR "\033[0;31m"
#define NO_COLOR    "\033[m"

#define ADDRESS         0
#define EN_WRITE        1
#define EN_READ         2
#define DATA            3
#define DATA_OUT        4

#define TOTAL_TESTS     4

using namespace std;

class SIMULATIONTB: public Testbench<Vscr1> {
  public:
    // -----------------------------------------------------------------------------
    // Testbench constructor
    SIMULATIONTB(double frequency, double timescale=1e-9): Testbench(frequency, timescale) {}

    int Simulate(unsigned long max_time=1000000){
      Reset();


      // Test data   //
      int data[TOTAL_TESTS][5] = {
        
        {0b001100000001, 1, 0,  6,  0}, // write 6 on misa
        {0b111100010001, 1, 0,  8,  0}, // write 8 on mvendorid
        {0b111100010010, 1, 0, 10,  0}, // write 10 on marchid
        {0b111100010011, 1, 0, 12,  0}, // write 12 on mimpid
        
        
      };
        



      for (int num_test = 1; num_test < TOTAL_TESTS; num_test++) {

        m_core->address   = data[num_test][ADDRESS];
        m_core->en_write  = 1;
        m_core->en_read   = 0;
        m_core->data      = data[num_test][DATA];
        
        Tick();
        
        m_core->en_write  = 0;
        m_core->en_read   = 1;
        
        if(m_core->data_out != data[num_test][DATA])
        {return num_test;};
      }
    }
};

int main(int argc, char **argv, char **env) {

  double frequency = 1e6;
  std::unique_ptr<SIMULATIONTB> tb(new SIMULATIONTB(frequency));

  tb->OpenTrace("scr1.vcd");

  int ret = tb->Simulate(100e3);

  printf("\nBranch Unit Testbench:\n");

  if(ret == TOTAL_TESTS)
    printf(OK_COLOR "[OK]" NO_COLOR " Test Passed! Complete: %d/%d", ret, TOTAL_TESTS);
  else
    printf(ERROR_COLOR "[FAILED]" NO_COLOR " Test Failed! Complete: %d/%d", ret, TOTAL_TESTS);

  printf("\n");

  exit(0);
};
