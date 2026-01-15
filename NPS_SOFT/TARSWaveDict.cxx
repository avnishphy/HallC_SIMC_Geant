// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TARSWaveDict
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
#include "TARSWave.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TARSWave(void *p = nullptr);
   static void *newArray_TARSWave(Long_t size, void *p);
   static void delete_TARSWave(void *p);
   static void deleteArray_TARSWave(void *p);
   static void destruct_TARSWave(void *p);
   static void streamer_TARSWave(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TARSWave*)
   {
      ::TARSWave *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TARSWave >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TARSWave", ::TARSWave::Class_Version(), "TARSWave.h", 43,
                  typeid(::TARSWave), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TARSWave::Dictionary, isa_proxy, 16,
                  sizeof(::TARSWave) );
      instance.SetNew(&new_TARSWave);
      instance.SetNewArray(&newArray_TARSWave);
      instance.SetDelete(&delete_TARSWave);
      instance.SetDeleteArray(&deleteArray_TARSWave);
      instance.SetDestructor(&destruct_TARSWave);
      instance.SetStreamerFunc(&streamer_TARSWave);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TARSWave*)
   {
      return GenerateInitInstanceLocal(static_cast<::TARSWave*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TARSWave*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TARSWave::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TARSWave::Class_Name()
{
   return "TARSWave";
}

//______________________________________________________________________________
const char *TARSWave::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSWave*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TARSWave::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSWave*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TARSWave::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSWave*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TARSWave::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSWave*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TARSWave::Streamer(TBuffer &R__b)
{
   // Stream an object of class TARSWave.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TARSBase::Streamer(R__b);
      R__b >> fWave;
      R__b >> fNbChannel;
      R__b >> fSubstracted;
      R__b >> fAnalyzed;
      R__b >> fNPulse;
      delete [] fa;
      fa = new Double_t[fNPulse];
      R__b.ReadFastArray(fa,fNPulse);
      delete [] ft;
      ft = new Double_t[fNPulse];
      R__b.ReadFastArray(ft,fNPulse);
      R__b >> fb;
      R__b >> fchi2;
      R__b >> fDAC;
      R__b >> fVME;
      R__b >> fChan;
      R__b.CheckByteCount(R__s, R__c, TARSWave::IsA());
   } else {
      R__c = R__b.WriteVersion(TARSWave::IsA(), kTRUE);
      TARSBase::Streamer(R__b);
      R__b << fWave;
      R__b << fNbChannel;
      R__b << fSubstracted;
      R__b << fAnalyzed;
      R__b << fNPulse;
      R__b.WriteFastArray(fa,fNPulse);
      R__b.WriteFastArray(ft,fNPulse);
      R__b << fb;
      R__b << fchi2;
      R__b << fDAC;
      R__b << fVME;
      R__b << fChan;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TARSWave(void *p) {
      return  p ? new(p) ::TARSWave : new ::TARSWave;
   }
   static void *newArray_TARSWave(Long_t nElements, void *p) {
      return p ? new(p) ::TARSWave[nElements] : new ::TARSWave[nElements];
   }
   // Wrapper around operator delete
   static void delete_TARSWave(void *p) {
      delete (static_cast<::TARSWave*>(p));
   }
   static void deleteArray_TARSWave(void *p) {
      delete [] (static_cast<::TARSWave*>(p));
   }
   static void destruct_TARSWave(void *p) {
      typedef ::TARSWave current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TARSWave(TBuffer &buf, void *obj) {
      ((::TARSWave*)obj)->::TARSWave::Streamer(buf);
   }
} // end of namespace ROOT for class ::TARSWave

namespace {
  void TriggerDictionaryInitialization_TARSWaveDict_Impl() {
    static const char* headers[] = {
"TARSWave.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TARSWaveDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TARSWave.h")))  TARSWave;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TARSWaveDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TARSWave.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TARSWave", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TARSWaveDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TARSWaveDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TARSWaveDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TARSWaveDict() {
  TriggerDictionaryInitialization_TARSWaveDict_Impl();
}
