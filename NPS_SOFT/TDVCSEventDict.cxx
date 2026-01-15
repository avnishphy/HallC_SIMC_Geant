// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDVCSEventDict
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
#include "TDVCSEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TDVCSEvent(void *p = nullptr);
   static void *newArray_TDVCSEvent(Long_t size, void *p);
   static void delete_TDVCSEvent(void *p);
   static void deleteArray_TDVCSEvent(void *p);
   static void destruct_TDVCSEvent(void *p);
   static void streamer_TDVCSEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDVCSEvent*)
   {
      ::TDVCSEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDVCSEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDVCSEvent", ::TDVCSEvent::Class_Version(), "TDVCSEvent.h", 33,
                  typeid(::TDVCSEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDVCSEvent::Dictionary, isa_proxy, 16,
                  sizeof(::TDVCSEvent) );
      instance.SetNew(&new_TDVCSEvent);
      instance.SetNewArray(&newArray_TDVCSEvent);
      instance.SetDelete(&delete_TDVCSEvent);
      instance.SetDeleteArray(&deleteArray_TDVCSEvent);
      instance.SetDestructor(&destruct_TDVCSEvent);
      instance.SetStreamerFunc(&streamer_TDVCSEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDVCSEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDVCSEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDVCSEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDVCSEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDVCSEvent::Class_Name()
{
   return "TDVCSEvent";
}

//______________________________________________________________________________
const char *TDVCSEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDVCSEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDVCSEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDVCSEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDVCSEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDVCSEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TDVCSBase::Streamer(R__b);
      R__b >> fCaloEvent;
      fVertex.Streamer(R__b);
      fElectron.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TDVCSEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(TDVCSEvent::IsA(), kTRUE);
      TDVCSBase::Streamer(R__b);
      R__b << fCaloEvent;
      fVertex.Streamer(R__b);
      fElectron.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TDVCSEvent(void *p) {
      return  p ? new(p) ::TDVCSEvent : new ::TDVCSEvent;
   }
   static void *newArray_TDVCSEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TDVCSEvent[nElements] : new ::TDVCSEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDVCSEvent(void *p) {
      delete (static_cast<::TDVCSEvent*>(p));
   }
   static void deleteArray_TDVCSEvent(void *p) {
      delete [] (static_cast<::TDVCSEvent*>(p));
   }
   static void destruct_TDVCSEvent(void *p) {
      typedef ::TDVCSEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDVCSEvent(TBuffer &buf, void *obj) {
      ((::TDVCSEvent*)obj)->::TDVCSEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDVCSEvent

namespace {
  void TriggerDictionaryInitialization_TDVCSEventDict_Impl() {
    static const char* headers[] = {
"TDVCSEvent.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDVCSEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDVCSEvent.h")))  TDVCSEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDVCSEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDVCSEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDVCSEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDVCSEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDVCSEventDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDVCSEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDVCSEventDict() {
  TriggerDictionaryInitialization_TDVCSEventDict_Impl();
}
