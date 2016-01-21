#ifndef TEST_h
#define TEST_h
#include <TH1D.h>
#include "../inc/constants.h"
#include <iostream>
 
using namespace std;

class Test_Units
{
 public:

  TH1D* h;

  Test_Units()  
  {
    cout<<"TEST is being created"
    h = new TH1D("h1", "h1 title", 5, 0, 5);
    for(int i=1; i<=5; i++)
    {
        h->SetBinContent(i, i);
    }
  };
  void Test_GetSumError()  
  {
      if (GetSumError(h) != 15)
          cout << "Test_GetSumError FATAL ERROR: function failed parameters test" << endl;
        else
          cout << "Test_GetSumError passed" << endl;
  };

  ~Test_Units()
  {dout("TEST end");};

  void Test_GetFitRange( TH1D* h, bool f=true)
  {
      Int_t leftRange = 0.05;
      if (GetFitRange(0.05, true) != 1 ) 
      {
          dout("Test_GetFitRange FATAL ERROR: function failed parameters test");
      } 
      else 
      {
          dout("Test_GetFitRange passed");
      }
  }

  
};

#endif
