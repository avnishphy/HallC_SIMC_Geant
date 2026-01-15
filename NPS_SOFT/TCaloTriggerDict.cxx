// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloTriggerDict
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
#include "TCaloTrigger.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloTrigger(void *p = nullptr);
   static void *newArray_TCaloTrigger(Long_t size, void *p);
   static void delete_TCaloTrigger(void *p);
   static void deleteArray_TCaloTrigger(void *p);
   static void destruct_TCaloTrigger(void *p);
   static void streamer_TCaloTrigger(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloTrigger*)
   {
      ::TCaloTrigger *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloTrigger >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloTrigger", ::TCaloTrigger::Class_Version(), "TCaloTrigger.h", 46,
                  typeid(::TCaloTrigger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloTrigger::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloTrigger) );
      instance.SetNew(&new_TCaloTrigger);
      instance.SetNewArray(&newArray_TCaloTrigger);
      instance.SetDelete(&delete_TCaloTrigger);
      instance.SetDeleteArray(&deleteArray_TCaloTrigger);
      instance.SetDestructor(&destruct_TCaloTrigger);
      instance.SetStreamerFunc(&streamer_TCaloTrigger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloTrigger*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloTrigger*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloTrigger*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloTrigger::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloTrigger::Class_Name()
{
   return "TCaloTrigger";
}

//______________________________________________________________________________
const char *TCaloTrigger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloTrigger*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloTrigger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloTrigger*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloTrigger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloTrigger*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloTrigger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloTrigger*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloTrigger::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloTrigger.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TCaloBase::Streamer(R__b);
      fADCValue->Streamer(R__b);
      fTowerBit->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TCaloTrigger::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloTrigger::IsA(), kTRUE);
      TCaloBase::Streamer(R__b);
      fADCValue->Streamer(R__b);
      fTowerBit->Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloTrigger(void *p) {
      return  p ? new(p) ::TCaloTrigger : new ::TCaloTrigger;
   }
   static void *newArray_TCaloTrigger(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloTrigger[nElements] : new ::TCaloTrigger[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloTrigger(void *p) {
      delete (static_cast<::TCaloTrigger*>(p));
   }
   static void deleteArray_TCaloTrigger(void *p) {
      delete [] (static_cast<::TCaloTrigger*>(p));
   }
   static void destruct_TCaloTrigger(void *p) {
      typedef ::TCaloTrigger current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloTrigger(TBuffer &buf, void *obj) {
      ((::TCaloTrigger*)obj)->::TCaloTrigger::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloTrigger

namespace {
  void TriggerDictionaryInitialization_TCaloTriggerDict_Impl() {
    static const char* headers[] = {
"TCaloTrigger.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloTriggerDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloTrigger.h")))  TCaloTrigger;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloTriggerDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloTrigger.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloTrigger", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloTriggerDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloTriggerDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloTriggerDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloTriggerDict() {
  TriggerDictionaryInitialization_TCaloTriggerDict_Impl();
}
