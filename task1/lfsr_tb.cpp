#include "Vlfsr.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    Vlfsr* top = new Vlfsr;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sinegen.vcd");

    if (vbdOpen()!=1)  return(-1);
    
    vbdHeader("Lab 3");
    
    top->clk = 1;
    top->rst = 1;
    top->en = 1;
    // top->incr = 1;
    
    for (i=0; i<9999999; i++){

        for (clk=0; clk<2; clk++){
            tfp->dump (2*i + clk);
            top->clk = !top->clk;
            top->eval();
        }   
        
        

            // either simulaqtion finished, or 'q' is pressed
        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
            exit(0);                // ... exit if finish OR 'q' pressed
        
        vbdHex(1, top->data_out & 0xF);
        // vbdBar(top->data_out & 0xFF);
    
        

        vbdCycle(i+1);

        
        top->rst = vbdFlag();

        if (Verilated::gotFinish()) exit(0);

    }
    vbdClose();
    tfp->close();
    exit(0);
}