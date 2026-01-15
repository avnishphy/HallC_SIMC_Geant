// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME THCaloDict
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
#include "THCalo.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_THCalo(void *p = nullptr);
   static void *newArray_THCalo(Long_t size, void *p);
   static void delete_THCalo(void *p);
   static void deleteArray_THCalo(void *p);
   static void destruct_THCalo(void *p);
   static void streamer_THCalo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::THCalo*)
   {
      ::THCalo *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::THCalo >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("THCalo", ::THCalo::Class_Version(), "THCalo.h", 41,
                  typeid(::THCalo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::THCalo::Dictionary, isa_proxy, 16,
                  sizeof(::THCalo) );
      instance.SetNew(&new_THCalo);
      instance.SetNewArray(&newArray_THCalo);
      instance.SetDelete(&delete_THCalo);
      instance.SetDeleteArray(&deleteArray_THCalo);
      instance.SetDestructor(&destruct_THCalo);
      instance.SetStreamerFunc(&streamer_THCalo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::THCalo*)
   {
      return GenerateInitInstanceLocal(static_cast<::THCalo*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::THCalo*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr THCalo::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *THCalo::Class_Name()
{
   return "THCalo";
}

//______________________________________________________________________________
const char *THCalo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::THCalo*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int THCalo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::THCalo*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *THCalo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::THCalo*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *THCalo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::THCalo*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void THCalo::Streamer(TBuffer &R__b)
{
   // Stream an object of class THCalo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TCaloBase::Streamer(R__b);
      R__b >> fMin;
      R__b.CheckByteCount(R__s, R__c, THCalo::IsA());
   } else {
      R__c = R__b.WriteVersion(THCalo::IsA(), kTRUE);
      TCaloBase::Streamer(R__b);
      R__b << fMin;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_THCalo(void *p) {
      return  p ? new(p) ::THCalo : new ::THCalo;
   }
   static void *newArray_THCalo(Long_t nElements, void *p) {
      return p ? new(p) ::THCalo[nElements] : new ::THCalo[nElements];
   }
   // Wrapper around operator delete
   static void delete_THCalo(void *p) {
      delete (static_cast<::THCalo*>(p));
   }
   static void deleteArray_THCalo(void *p) {
      delete [] (static_cast<::THCalo*>(p));
   }
   static void destruct_THCalo(void *p) {
      typedef ::THCalo current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_THCalo(TBuffer &buf, void *obj) {
      ((::THCalo*)obj)->::THCalo::Streamer(buf);
   }
} // end of namespace ROOT for class ::THCalo

namespace {
  void TriggerDictionaryInitialization_THCaloDict_Impl() {
    static const char* headers[] = {
"THCalo.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "THCaloDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$THCalo.h")))  THCalo;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "THCaloDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "THCalo.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"THCalo", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("THCaloDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_THCaloDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_THCaloDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_THCaloDict() {
  TriggerDictionaryInitialization_THCaloDict_Impl();
}
