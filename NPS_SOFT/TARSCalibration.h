///////////////////////////////////////////////////////////////////////////////
//
//
//             class TARSCalibration
//            Calibration class contains offset and calibration constants
//              to return an energy and time
//
///////////////////////////////////////////////////////////////////////////////


#include <TObject.h>
#include <Rtypes.h>
#include <iostream> 

class TARSCalibration : public TObject

{
 public:
  TARSCalibration();
  ~TARSCalibration();
 protected:
  Int_t fTimeOffset;
  Double_t fEConst;
  ClassDef(TARSCalibration,1)
};



