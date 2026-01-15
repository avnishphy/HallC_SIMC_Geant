//
// TDVCSParameters.h, v1.0, Thu Jan 17 11:13:57
// Author: C. Munoz Camacho
//

#ifndef __TDVCSParameters__
#define __TDVCSParameters__

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TString
#include "TString.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// TDVCSParameters
//
// DVCS parameter class
// 
////////////////////////////////////////////////////////////////////////////////

class TDVCSParameters : public TObject
{
  private:

  static Bool_t fgIsInit;             // Are the parameters initialized?
  void Reset(void);

  protected:

  static Float_t  fClusA;            // Clustering Parameter A
  static Float_t  fClusB;            // Clustering Parameter B

  static TString fConfig;             // Config file

  public:

  TDVCSParameters();
  TDVCSParameters(char *);
  virtual ~TDVCSParameters();

  Float_t GetClusA(void) { return fClusA ; }
  Float_t GetClusB(void) { return fClusB ; }

  void Init(const char*);                   // Read parameters from files
  void InitDB(Int_t run);

  virtual void Print(const char*);

  ClassDef(TDVCSParameters,1)         // DVCS Parameter Class

}; // End of TDVCSParameters class definition

#endif









