// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDVCSEventMCDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "TDVCSEventMC.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TDVCSEventMC(void *p = nullptr);
   static void *newArray_TDVCSEventMC(Long_t size, void *p);
   static void delete_TDVCSEventMC(void *p);
   static void deleteArray_TDVCSEventMC(void *p);
   static void destruct_TDVCSEventMC(void *p);
   static void streamer_TDVCSEventMC(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDVCSEventMC*)
   {
      ::TDVCSEventMC *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDVCSEventMC >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDVCSEventMC", ::TDVCSEventMC::Class_Version(), "TDVCSEventMC.h", 34,
                  typeid(::TDVCSEventMC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDVCSEventMC::Dictionary, isa_proxy, 16,
                  sizeof(::TDVCSEventMC) );
      instance.SetNew(&new_TDVCSEventMC);
      instance.SetNewArray(&newArray_TDVCSEventMC);
      instance.SetDelete(&delete_TDVCSEventMC);
      instance.SetDeleteArray(&deleteArray_TDVCSEventMC);
      instance.SetDestructor(&destruct_TDVCSEventMC);
      instance.SetStreamerFunc(&streamer_TDVCSEventMC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDVCSEventMC*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDVCSEventMC*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDVCSEventMC*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDVCSEventMC::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDVCSEventMC::Class_Name()
{
   return "TDVCSEventMC";
}

//______________________________________________________________________________
const char *TDVCSEventMC::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEventMC*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDVCSEventMC::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEventMC*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDVCSEventMC::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEventMC*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDVCSEventMC::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEventMC*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDVCSEventMC::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDVCSEventMC.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      fElectron->Streamer(R__b);
      fPhoton->Streamer(R__b);
      fProton->Streamer(R__b);
      fVertex.Streamer(R__b);
      R__b >> fSigmaP;
      R__b >> fSigmaM;
      R__b >> fPSF;
      R__b >> fNelectrons;
      R__b >> fNphotons;
      R__b >> fNprotons;
      R__b.CheckByteCount(R__s, R__c, TDVCSEventMC::IsA());
   } else {
      R__c = R__b.WriteVersion(TDVCSEventMC::IsA(), kTRUE);
      TObject::Streamer(R__b);
      fElectron->Streamer(R__b);
      fPhoton->Streamer(R__b);
      fProton->Streamer(R__b);
      fVertex.Streamer(R__b);
      R__b << fSigmaP;
      R__b << fSigmaM;
      R__b << fPSF;
      R__b << fNelectrons;
      R__b << fNphotons;
      R__b << fNprotons;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TDVCSEventMC(void *p) {
      return  p ? new(p) ::TDVCSEventMC : new ::TDVCSEventMC;
   }
   static void *newArray_TDVCSEventMC(Long_t nElements, void *p) {
      return p ? new(p) ::TDVCSEventMC[nElements] : new ::TDVCSEventMC[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDVCSEventMC(void *p) {
      delete (static_cast<::TDVCSEventMC*>(p));
   }
   static void deleteArray_TDVCSEventMC(void *p) {
      delete [] (static_cast<::TDVCSEventMC*>(p));
   }
   static void destruct_TDVCSEventMC(void *p) {
      typedef ::TDVCSEventMC current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDVCSEventMC(TBuffer &buf, void *obj) {
      ((::TDVCSEventMC*)obj)->::TDVCSEventMC::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDVCSEventMC

namespace {
  void TriggerDictionaryInitialization_TDVCSEventMCDict_Impl() {
    static const char* headers[] = {
"TDVCSEventMC.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDVCSEventMCDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDVCSEventMC.h")))  TDVCSEventMC;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDVCSEventMCDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDVCSEventMC.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDVCSEventMC", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDVCSEventMCDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDVCSEventMCDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDVCSEventMCDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDVCSEventMCDict() {
  TriggerDictionaryInitialization_TDVCSEventMCDict_Impl();
}
