// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDVCSParametersDict
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
#include "TDVCSParameters.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TDVCSParameters(void *p = nullptr);
   static void *newArray_TDVCSParameters(Long_t size, void *p);
   static void delete_TDVCSParameters(void *p);
   static void deleteArray_TDVCSParameters(void *p);
   static void destruct_TDVCSParameters(void *p);
   static void streamer_TDVCSParameters(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDVCSParameters*)
   {
      ::TDVCSParameters *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDVCSParameters >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDVCSParameters", ::TDVCSParameters::Class_Version(), "TDVCSParameters.h", 25,
                  typeid(::TDVCSParameters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDVCSParameters::Dictionary, isa_proxy, 16,
                  sizeof(::TDVCSParameters) );
      instance.SetNew(&new_TDVCSParameters);
      instance.SetNewArray(&newArray_TDVCSParameters);
      instance.SetDelete(&delete_TDVCSParameters);
      instance.SetDeleteArray(&deleteArray_TDVCSParameters);
      instance.SetDestructor(&destruct_TDVCSParameters);
      instance.SetStreamerFunc(&streamer_TDVCSParameters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDVCSParameters*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDVCSParameters*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDVCSParameters*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDVCSParameters::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDVCSParameters::Class_Name()
{
   return "TDVCSParameters";
}

//______________________________________________________________________________
const char *TDVCSParameters::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSParameters*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDVCSParameters::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSParameters*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDVCSParameters::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSParameters*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDVCSParameters::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSParameters*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDVCSParameters::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDVCSParameters.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TDVCSParameters::IsA());
   } else {
      R__c = R__b.WriteVersion(TDVCSParameters::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TDVCSParameters(void *p) {
      return  p ? new(p) ::TDVCSParameters : new ::TDVCSParameters;
   }
   static void *newArray_TDVCSParameters(Long_t nElements, void *p) {
      return p ? new(p) ::TDVCSParameters[nElements] : new ::TDVCSParameters[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDVCSParameters(void *p) {
      delete (static_cast<::TDVCSParameters*>(p));
   }
   static void deleteArray_TDVCSParameters(void *p) {
      delete [] (static_cast<::TDVCSParameters*>(p));
   }
   static void destruct_TDVCSParameters(void *p) {
      typedef ::TDVCSParameters current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDVCSParameters(TBuffer &buf, void *obj) {
      ((::TDVCSParameters*)obj)->::TDVCSParameters::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDVCSParameters

namespace {
  void TriggerDictionaryInitialization_TDVCSParametersDict_Impl() {
    static const char* headers[] = {
"TDVCSParameters.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDVCSParametersDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDVCSParameters.h")))  TDVCSParameters;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDVCSParametersDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDVCSParameters.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDVCSParameters", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDVCSParametersDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDVCSParametersDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDVCSParametersDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDVCSParametersDict() {
  TriggerDictionaryInitialization_TDVCSParametersDict_Impl();
}
