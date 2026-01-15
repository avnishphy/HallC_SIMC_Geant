// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TARSBaseDict
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
#include "TARSBase.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TARSBase(void *p = nullptr);
   static void *newArray_TARSBase(Long_t size, void *p);
   static void delete_TARSBase(void *p);
   static void deleteArray_TARSBase(void *p);
   static void destruct_TARSBase(void *p);
   static void streamer_TARSBase(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TARSBase*)
   {
      ::TARSBase *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TARSBase >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TARSBase", ::TARSBase::Class_Version(), "TARSBase.h", 24,
                  typeid(::TARSBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TARSBase::Dictionary, isa_proxy, 16,
                  sizeof(::TARSBase) );
      instance.SetNew(&new_TARSBase);
      instance.SetNewArray(&newArray_TARSBase);
      instance.SetDelete(&delete_TARSBase);
      instance.SetDeleteArray(&deleteArray_TARSBase);
      instance.SetDestructor(&destruct_TARSBase);
      instance.SetStreamerFunc(&streamer_TARSBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TARSBase*)
   {
      return GenerateInitInstanceLocal(static_cast<::TARSBase*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TARSBase*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TARSBase::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TARSBase::Class_Name()
{
   return "TARSBase";
}

//______________________________________________________________________________
const char *TARSBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSBase*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TARSBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSBase*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TARSBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSBase*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TARSBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSBase*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TARSBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TARSBase.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TARSBase::IsA());
   } else {
      R__c = R__b.WriteVersion(TARSBase::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TARSBase(void *p) {
      return  p ? new(p) ::TARSBase : new ::TARSBase;
   }
   static void *newArray_TARSBase(Long_t nElements, void *p) {
      return p ? new(p) ::TARSBase[nElements] : new ::TARSBase[nElements];
   }
   // Wrapper around operator delete
   static void delete_TARSBase(void *p) {
      delete (static_cast<::TARSBase*>(p));
   }
   static void deleteArray_TARSBase(void *p) {
      delete [] (static_cast<::TARSBase*>(p));
   }
   static void destruct_TARSBase(void *p) {
      typedef ::TARSBase current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TARSBase(TBuffer &buf, void *obj) {
      ((::TARSBase*)obj)->::TARSBase::Streamer(buf);
   }
} // end of namespace ROOT for class ::TARSBase

namespace {
  void TriggerDictionaryInitialization_TARSBaseDict_Impl() {
    static const char* headers[] = {
"TARSBase.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TARSBaseDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TARSBase.h")))  TARSBase;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TARSBaseDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TARSBase.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TARSBase", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TARSBaseDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TARSBaseDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TARSBaseDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TARSBaseDict() {
  TriggerDictionaryInitialization_TARSBaseDict_Impl();
}
