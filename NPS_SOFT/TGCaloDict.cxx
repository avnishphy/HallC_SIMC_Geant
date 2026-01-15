// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TGCaloDict
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
#include "TGCalo.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void delete_TGCalo(void *p);
   static void deleteArray_TGCalo(void *p);
   static void destruct_TGCalo(void *p);
   static void streamer_TGCalo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TGCalo*)
   {
      ::TGCalo *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TGCalo >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TGCalo", ::TGCalo::Class_Version(), "TGCalo.h", 35,
                  typeid(::TGCalo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TGCalo::Dictionary, isa_proxy, 16,
                  sizeof(::TGCalo) );
      instance.SetDelete(&delete_TGCalo);
      instance.SetDeleteArray(&deleteArray_TGCalo);
      instance.SetDestructor(&destruct_TGCalo);
      instance.SetStreamerFunc(&streamer_TGCalo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TGCalo*)
   {
      return GenerateInitInstanceLocal(static_cast<::TGCalo*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TGCalo*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TGCalo::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TGCalo::Class_Name()
{
   return "TGCalo";
}

//______________________________________________________________________________
const char *TGCalo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGCalo*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TGCalo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGCalo*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TGCalo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGCalo*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TGCalo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGCalo*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TGCalo::Streamer(TBuffer &R__b)
{
   // Stream an object of class TGCalo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      fQObject.Streamer(R__b);
      R__b >> fNevent;
      R__b >> fTest;
      R__b >> fFile;
      R__b >> fTree;
      R__b >> fBranchPA;
      R__b >> fBranchCalo;
      R__b >> fPAPad;
      R__b >> fCaloPad;
      R__b >> fPAPadInfo;
      R__b >> fCaloPadInfo;
      R__b >> fPAARSPad;
      R__b >> fCaloARSPad;
      R__b >> fControlPad;
      R__b >> fCaloARSPadInfo;
      R__b >> ftcalo;
      R__b >> fCaloEvent;
      R__b >> fhCalo;
      R__b >> fhPA;
      R__b.CheckByteCount(R__s, R__c, TGCalo::IsA());
   } else {
      R__c = R__b.WriteVersion(TGCalo::IsA(), kTRUE);
      fQObject.Streamer(R__b);
      R__b << fNevent;
      R__b << fTest;
      R__b << fFile;
      R__b << fTree;
      R__b << fBranchPA;
      R__b << fBranchCalo;
      R__b << fPAPad;
      R__b << fCaloPad;
      R__b << fPAPadInfo;
      R__b << fCaloPadInfo;
      R__b << fPAARSPad;
      R__b << fCaloARSPad;
      R__b << fControlPad;
      R__b << fCaloARSPadInfo;
      R__b << ftcalo;
      R__b << fCaloEvent;
      R__b << (TObject*)fhCalo;
      R__b << (TObject*)fhPA;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TGCalo(void *p) {
      delete (static_cast<::TGCalo*>(p));
   }
   static void deleteArray_TGCalo(void *p) {
      delete [] (static_cast<::TGCalo*>(p));
   }
   static void destruct_TGCalo(void *p) {
      typedef ::TGCalo current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TGCalo(TBuffer &buf, void *obj) {
      ((::TGCalo*)obj)->::TGCalo::Streamer(buf);
   }
} // end of namespace ROOT for class ::TGCalo

namespace {
  void TriggerDictionaryInitialization_TGCaloDict_Impl() {
    static const char* headers[] = {
"TGCalo.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TGCaloDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TGCalo.h")))  TGCalo;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TGCaloDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TGCalo.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TGCalo", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TGCaloDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TGCaloDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TGCaloDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TGCaloDict() {
  TriggerDictionaryInitialization_TGCaloDict_Impl();
}
