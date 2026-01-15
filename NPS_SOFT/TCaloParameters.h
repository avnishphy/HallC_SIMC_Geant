//
// TCaloParameters.h, v1.0, Thu Sep 12 11:13:57
// Author: F. Sabatie
//

#ifndef __TCaloParameters__
#define __TCaloParameters__

#include "TObject.h"
#include "TString.h"

////////////////////////////////////////////////////////////////////////////////
//
// TParameters
//
// DVCS calorimeter parameter class
//
// Contains information on parameters for the clustering algorithm.
// 
////////////////////////////////////////////////////////////////////////////////

class TCaloParameters : public TObject
{
  private:

  static Bool_t fgIsInit;                  // Are the parameters initialized?

  protected:

  static Float_t  fClustWo;           // Clustering Parameter Wo
  static Float_t  fClustEth;          // Clustering Parameter Eth

  static TString fConfig;             // Config file

  private:

  void Reset(void);

  public:

  TCaloParameters();
  TCaloParameters(const char*);
  virtual ~TCaloParameters();

  void Init(const char*);                   // Read parameters from files
  void InitDB(Int_t run);
  virtual void Print(const char*);

  Float_t GetClusWo(void) {return fClustWo ; }
  Float_t GetClusEth(void) {return fClustEth ; }

  ClassDef(TCaloParameters,1)         // DVCS Calorimeter Parameter Class

}; // End of TCaloParameters class definition

#endif









