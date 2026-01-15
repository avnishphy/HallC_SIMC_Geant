#ifndef __TGCalo__
#define __TGCalo__

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TFile
#include "TFile.h"
#endif

#ifndef ROOT_TPaveText
#include "TPaveText.h"
#endif

#ifndef ROOT_TPad
#include "TPad.h"
#endif

#ifndef ROOT_TTree
#include "TTree.h"
#endif


#ifndef __TCaloTrigger__
#include "TCaloTrigger.h"
#endif

#ifndef __TCaloEvent__
#include "TCaloEvent.h"
#endif

#include <RQ_OBJECT.h>

class TGCalo 
{

RQ_OBJECT("TGCalo")   // for classes not derived from TQObject
                      // RQ_OBJECT macro should be used

  private:

 Int_t fNevent; //Event number 
 Bool_t fTest; 

 TFile *fFile; //File 
 TTree *fTree; //Tree
 TBranch *fBranchPA; //Branch PA
 TBranch *fBranchCalo; //Branch Calo

 TPad *fPAPad; //Proton Array Pad 
 TPad *fCaloPad; //Calorimeter Pad
 TPad *fPAPadInfo; //Proton Array Info Pad
 TPad *fCaloPadInfo; //Calorimeter Info Pad
 TPad *fPAARSPad; //Proton Array ARS Pad
 TPad *fCaloARSPad; //Calorimeter ARS Pad
 TPad *fControlPad; //ControlPad
 TPad *fCaloARSPadInfo;
 TPaveText *ftcalo;

 TCaloEvent *fCaloEvent;
 // TCaloTrigger *fTrigger;

 // THPA *fHPA; //Proton Array Histogram

 TH1F *fhCalo;
 TH1F *fhPA;
 
 public:

 TGCalo(TFile* file);
 ~TGCalo();
 
 void Init(TFile* file);
 void SetFile (TFile* file) { fFile=file ; }
 
 void SetPAPad (TPad* papad) { fPAPad=papad ; }
 void SetCaloPad (TPad* calopad) { fCaloPad=calopad ; }
 void SetPAPadInfo (TPad* papadinfo) { fPAPadInfo=papadinfo ; }
 void SetCaloPadInfo (TPad* calopadinfo) { fCaloPadInfo=calopadinfo ; }
 void SetPAARSPad (TPad* paparspad) { fPAARSPad=paparspad ; }
 void SetCaloARSPad (TPad* caloarspad) { fCaloARSPad=caloarspad ; }
 void SetControlPad (TPad* controlpad) { fControlPad=controlpad ; }
 void SetCaloARSPadInfo (TPad* pad) { fCaloARSPadInfo=pad ; }
 // void SetHPA (THPA* hpa) { fHPA=hpa ; }

 void SetCaloEvent (TCaloEvent* caloev) { fCaloEvent=caloev ; }

 void ExecuteEvent (Int_t event, Int_t px, Int_t py, TObject *sel);
 void ShowNext (void) ;
 void FillEvent (Int_t nevent) ;

 void HandlePA(TPad* pad, Int_t event, Int_t px, Int_t py, TObject* sel);
 void HandleCalo(TPad* pad, Int_t event, Int_t px, Int_t py, TObject* sel);

 TCaloEvent* GetCaloEvent(void) { return fCaloEvent ; }
 Int_t GetEventNumber(void) {return fNevent ; }

 ClassDef(TGCalo,1) //TGCalo Class
   
};
   
#endif
