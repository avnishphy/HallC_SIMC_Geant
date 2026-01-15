// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloEventDict
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
#include "TCaloEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloEvent(void *p = nullptr);
   static void *newArray_TCaloEvent(Long_t size, void *p);
   static void delete_TCaloEvent(void *p);
   static void deleteArray_TCaloEvent(void *p);
   static void destruct_TCaloEvent(void *p);
   static void streamer_TCaloEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloEvent*)
   {
      ::TCaloEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloEvent", ::TCaloEvent::Class_Version(), "TCaloEvent.h", 58,
                  typeid(::TCaloEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloEvent::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloEvent) );
      instance.SetNew(&new_TCaloEvent);
      instance.SetNewArray(&newArray_TCaloEvent);
      instance.SetDelete(&delete_TCaloEvent);
      instance.SetDeleteArray(&deleteArray_TCaloEvent);
      instance.SetDestructor(&destruct_TCaloEvent);
      instance.SetStreamerFunc(&streamer_TCaloEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloEvent::Class_Name()
{
   return "TCaloEvent";
}

//______________________________________________________________________________
const char *TCaloEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TCaloBase::Streamer(R__b);
      fCluster->Streamer(R__b);
      fCaloBlocks->Streamer(R__b);
      R__b >> fCaloTrigger;
      R__b >> fNbClusters;
      R__b >> fNbBlocks;
      R__b >> fNWave;
      R__b >> fLogicType;
      R__b.ReadStaticArray((double*)fDTScalers);
      fScalers->Streamer(R__b);
      fARSWaves->Streamer(R__b);
      fADC->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TCaloEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloEvent::IsA(), kTRUE);
      TCaloBase::Streamer(R__b);
      fCluster->Streamer(R__b);
      fCaloBlocks->Streamer(R__b);
      R__b << fCaloTrigger;
      R__b << fNbClusters;
      R__b << fNbBlocks;
      R__b << fNWave;
      R__b << fLogicType;
      R__b.WriteArray(fDTScalers, 4);
      fScalers->Streamer(R__b);
      fARSWaves->Streamer(R__b);
      fADC->Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloEvent(void *p) {
      return  p ? new(p) ::TCaloEvent : new ::TCaloEvent;
   }
   static void *newArray_TCaloEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloEvent[nElements] : new ::TCaloEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloEvent(void *p) {
      delete (static_cast<::TCaloEvent*>(p));
   }
   static void deleteArray_TCaloEvent(void *p) {
      delete [] (static_cast<::TCaloEvent*>(p));
   }
   static void destruct_TCaloEvent(void *p) {
      typedef ::TCaloEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloEvent(TBuffer &buf, void *obj) {
      ((::TCaloEvent*)obj)->::TCaloEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloEvent

namespace {
  void TriggerDictionaryInitialization_TCaloEventDict_Impl() {
    static const char* headers[] = {
"TCaloEvent.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloEvent.h")))  TCaloEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloEventDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloEventDict() {
  TriggerDictionaryInitialization_TCaloEventDict_Impl();
}
