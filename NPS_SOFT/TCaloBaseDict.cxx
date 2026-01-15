// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloBaseDict
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
#include "TCaloBase.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloBase(void *p = nullptr);
   static void *newArray_TCaloBase(Long_t size, void *p);
   static void delete_TCaloBase(void *p);
   static void deleteArray_TCaloBase(void *p);
   static void destruct_TCaloBase(void *p);
   static void streamer_TCaloBase(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloBase*)
   {
      ::TCaloBase *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloBase >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloBase", ::TCaloBase::Class_Version(), "TCaloBase.h", 22,
                  typeid(::TCaloBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloBase::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloBase) );
      instance.SetNew(&new_TCaloBase);
      instance.SetNewArray(&newArray_TCaloBase);
      instance.SetDelete(&delete_TCaloBase);
      instance.SetDeleteArray(&deleteArray_TCaloBase);
      instance.SetDestructor(&destruct_TCaloBase);
      instance.SetStreamerFunc(&streamer_TCaloBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloBase*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloBase*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloBase*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloBase::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloBase::Class_Name()
{
   return "TCaloBase";
}

//______________________________________________________________________________
const char *TCaloBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloBase*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloBase*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloBase*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloBase*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloBase.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TCaloBase::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloBase::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloBase(void *p) {
      return  p ? new(p) ::TCaloBase : new ::TCaloBase;
   }
   static void *newArray_TCaloBase(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloBase[nElements] : new ::TCaloBase[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloBase(void *p) {
      delete (static_cast<::TCaloBase*>(p));
   }
   static void deleteArray_TCaloBase(void *p) {
      delete [] (static_cast<::TCaloBase*>(p));
   }
   static void destruct_TCaloBase(void *p) {
      typedef ::TCaloBase current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloBase(TBuffer &buf, void *obj) {
      ((::TCaloBase*)obj)->::TCaloBase::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloBase

namespace {
  void TriggerDictionaryInitialization_TCaloBaseDict_Impl() {
    static const char* headers[] = {
"TCaloBase.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloBaseDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloBase.h")))  TCaloBase;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloBaseDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloBase.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloBase", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloBaseDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloBaseDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloBaseDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloBaseDict() {
  TriggerDictionaryInitialization_TCaloBaseDict_Impl();
}
