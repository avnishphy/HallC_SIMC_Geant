#include <iostream>

using namespace std;
extern "C"
{
extern void hrse_acceptance_maps2__(float*,bool*);
}

bool hrse()
{
  float tab[5];
  tab[0]=0;
  tab[1]=0;
 tab[2]=0;
 tab[3]=0;
 tab[4]=0.1;
  bool v;
  hrse_acceptance_maps2__(tab,&v);
    cout<<v<<endl;

}
