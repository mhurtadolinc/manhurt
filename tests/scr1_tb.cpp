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

#define ADDS      0
#define EN_W      1
#define EN_R      2
#define DATA      3
#define DATA_O    4
#define LT       5
#define LTU      6DS

#define DATA1       0x001
#define DATA2       0x002
#define DATA3       0X003
#define DATA4       0x004


#define MISA        0x301
#define MVENDORID   0xF11
#define MARCHID     0xF12
#define MIMPID      0xF13
#define ALU_OR    0b0110
#define ALU_XOR   0b0100
#define ALU_SRL   0b0101
#define ALU_SLL   0b0001
#define ALU_SRA   0b1101
#define ALU_SLT   0b0010
#define ALU_SLTU  0b0011


#define TOTAL_TESTS 4


using namespace std;

class SIMULATIONTB: public Testbench<Valu> {
  public:
    // -----------------------------------------------------------------------------
    // Testbench constructor
    SIMULATIONTB(double frequency=1e6, double timescale=1e-9): Testbench(frequency, timescale) {}

    int Simulate(unsigned long max_time=1000000){
      Reset();

      // Test data    [ADDS | EN_WRITE | ENREAD | DATA | DATA OUT]
      
      int data[TOTAL_TESTS][5] = {                               //             Operation          | Equal | Less than | Less than (unsigned)
//           [ADDRESS | EN_W | EN_R | DATA | DATA_O]
        {      MISA,        1,       0,     DATA1  , DATA1},    //                     |   0   |     1     |       1
        { MVENDORID,        1,       0,     DATA2  , DATA1},    // -20 + 5 = -15                  |   0   |     1     |       0
        {   MARCHID,        1,       0,     DATA3  , DATA1},    // -187 + 187 = 0                 |   0   |     1     |       0
        {    MIMPID,        1,       0,     DATA4  , DATA1},    // 4 - 3 = 1                      |   0   |     0     |       0
        {        -23,  -127,   ALU_SUB,        104, 0, 0, 0},    // -23 - (-127) = 104             |   0   |     0     |       0
        {         -1,     0,   ALU_SUB,         -1, 0, 1, 0},    // -1 - 0 = -1                    |   0   |     1     |       0
        {        120,   245,   ALU_AND,        112, 0, 1, 1},    // 245 & 120 = 112                |   0   |     1     |       1
        {        540,   540,   ALU_AND,        540, 1, 0, 0},    // 540 & 540 = 540                |   1   |     0     |       0
        {        100,    50,   ALU_OR,         118, 0, 0, 0},    // 100 | 50 = 118                 |   0   |     0     |       0
        {          0,     0,   ALU_OR,           0, 1, 0, 0},    // 0 | 0 = 0                      |   1   |     0     |       0
        {        573,   215,   ALU_XOR,        746, 0, 0, 0},    // 573 ^ 215 = 746                |   0   |     0     |       0
        {       4500,  4500,   ALU_XOR,          0, 1, 0, 0},    // 4500 ^ 4500 = 0                |   1   |     0     |       0
        {       1024,     3,   ALU_SRL,        128, 0, 0, 0},    // 1024 >> 4 = 128                |   0   |     0     |       0
        {-2147483648,     5,   ALU_SRL,   67108864, 0, 1, 0},    // -2147483648 >> 5 = 67108864    |   0   |     1     |       0
        {-2147483648,     5,   ALU_SRA,  -67108864, 0, 1, 0},    // -2147483648 >> 5 = -67108864   |   0   |     1     |       0
        {       2048,     1,   ALU_SRA,       1024, 0, 0, 0},    // 2048 >> 1 = 1024               |   0   |     1     |       0
        {         64,     5,   ALU_SLL,       2048, 0, 0, 0},    // 64 << 5 = 2048                 |   0   |     0     |       0
        {         -2,     1,   ALU_SLL,         -4, 0, 1, 0},    // -2 << 1 = -4                   |   0   |     1     |       0
        {          1,    10,   ALU_SLT,          1, 0, 1, 1},    // 1 < 10 = true                  |   0   |     1     |       1
        {         20,    10,   ALU_SLT,          0, 0, 0, 0},    // 20 < 10 = false                |   0   |     0     |       0
        {        -20,   -10,   ALU_SLT,          1, 0, 1, 1},    // -20 < -10 = true               |   0   |     1     |       1
        {         50,   800,   ALU_SLTU,         1, 0, 1, 1},    // 50 < 800 = true (Unsigned)     |   0   |     1     |       1
        {         30,    20,   ALU_SLTU,         0, 0, 0, 0},    // 30 < 20 = false (Unsigned)     |   0   |     0     |       0
        {        100,  -200,   ALU_SLTU,         1, 0, 0, 1}};   // 100 < -200 = true (Unsigned)   |   0   |     0     |       1


      for (int num_test = 0; num_test < TOTAL_TESTS; num_test++) {
        m_core->address_i = data[num_test][ADDS];
        m_core->en_read_i = data[num_test][EN_R];
        m_core->en_write_i = data[num_test][EN_W] ;
        m_core->data_i = data[num_test][DATA];
        
        Tick())
          

        if((m_core->data_out_o != data[num_test][DATA_O]))
          return num_test;
      }
    }
};


int main(int argc, char **argv, char **env) {
  std::unique_ptr<SIMULATIONTB> tb(new SIMULATIONTB());

  tb->OpenTrace("alu.vcd");

  int ret = tb->Simulate();

  printf("\nALU Testbench:\n");

  if(ret == TOTAL_TESTS)
    printf(OK_COLOR "[OK]" NO_COLOR " Test Passed! ");
  else
    printf(ERROR_COLOR "[FAILED]" NO_COLOR " Test Failed! ");

  printf("Complete: %d/%d\n", ret, TOTAL_TESTS);

  exit(0);
}
