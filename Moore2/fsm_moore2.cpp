#include "systemc.h"

SC_MODULE(moore2){
  sc_in<bool> clk, a, reset;
  sc_out<bool> output;

  enum stat_type {s0, s1, s2, s3};
  sc_signal<state_type> current_state, next_state;
 
  void moore_trans(){
  if(reset)
	current_state = s0;
  else
    switch(current_state){
	   case s0: current_state = a ? S0: s2; break;
	   case s1: current_state = a ? S0: s2; break;
	   case s2: current_state = a ? S2: s3; break;
	   case s3: current_state = a ? S1: s3; break;
	   }
	   }
  void moore_output(){
  switch(moore_state){
	   case s0
	   case s1: output = 1;
	   case s2: output = 0;
	   case s3: 
	   }
	   }

  SC_CTOR(moore_trans){
    SC_METHOD(moore);
    sensitive<< clk.pos();
    SC_METHOD(moore_output);
    sensitive<< current_state;
	}
};
