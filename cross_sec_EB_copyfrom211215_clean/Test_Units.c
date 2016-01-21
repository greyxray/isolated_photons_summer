#include "Test_Units.h"
using namespace std;

  // Test_Units::Test_Units()
  // {
  //   cout<<"THIS IS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
  //   h = new TH1D("h1", "h1 title", 5, 0, 5);
  //   for(int i=1; i<=5; i++)
  //   {
  //       h->SetBinContent(i, i);
  //   }
  //   dout("done");
  // }

  void Test_Units::Test_GetSumError()
  {
      if (GetSumError(h) != 15)
          cout << "Test_GetSumError FATAL ERROR: function failed parameters test" << endl;
  }

  
  Test_Units::~Test_Units()
  {
    cout << "Test_end" << endl;
  }

  // Member functions definitions including constructor
// Test_Units::Test_Units(void)
// {
//     std::cout << "Object is being created" << std::ndl;
// }
 
void Test_Units::setLength( double len )
{
    length = len;
    cout<<"!!#"<<endl;
}
 
double Test_Units::getLength( void )
{
    return length;
}
