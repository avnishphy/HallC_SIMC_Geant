// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloParametersDict
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
#include "TCaloParameters.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloParameters(void *p = nullptr);
   static void *newArray_TCaloParameters(Long_t size, void *p);
   static void delete_TCaloParameters(void *p);
   static void deleteArray_TCaloParameters(void *p);
   static void destruct_TCaloParameters(void *p);
   static void streamer_TCaloParameters(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloParameters*)
   {
      ::TCaloParameters *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloParameters >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloParameters", ::TCaloParameters::Class_Version(), "TCaloParameters.h", 22,
                  typeid(::TCaloParameters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloParameters::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloParameters) );
      instance.SetNew(&new_TCaloParameters);
      instance.SetNewArray(&newArray_TCaloParameters);
      instance.SetDelete(&delete_TCaloParameters);
      instance.SetDeleteArray(&deleteArray_TCaloParameters);
      instance.SetDestructor(&destruct_TCaloParameters);
      instance.SetStreamerFunc(&streamer_TCaloParameters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloParameters*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloParameters*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloParameters*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloParameters::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloParameters::Class_Name()
{
   return "TCaloParameters";
}

//______________________________________________________________________________
const char *TCaloParameters::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloParameters*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloParameters::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloParameters*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloParameters::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloParameters*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloParameters::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloParameters*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloParameters::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloParameters.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TCaloParameters::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloParameters::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloParameters(void *p) {
      return  p ? new(p) ::TCaloParameters : new ::TCaloParameters;
   }
   static void *newArray_TCaloParameters(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloParameters[nElements] : new ::TCaloParameters[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloParameters(void *p) {
      delete (static_cast<::TCaloParameters*>(p));
   }
   static void deleteArray_TCaloParameters(void *p) {
      delete [] (static_cast<::TCaloParameters*>(p));
   }
   static void destruct_TCaloParameters(void *p) {
      typedef ::TCaloParameters current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloParameters(TBuffer &buf, void *obj) {
      ((::TCaloParameters*)obj)->::TCaloParameters::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloParameters

namespace {
  void TriggerDictionaryInitialization_TCaloParametersDict_Impl() {
    static const char* headers[] = {
"TCaloParameters.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloParametersDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloParameters.h")))  TCaloParameters;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloParametersDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloParameters.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloParameters", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloParametersDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloParametersDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloParametersDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloParametersDict() {
  TriggerDictionaryInitialization_TCaloParametersDict_Impl();
}
