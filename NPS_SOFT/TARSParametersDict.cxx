// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TARSParametersDict
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
#include "TARSParameters.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TARSParameters(void *p = nullptr);
   static void *newArray_TARSParameters(Long_t size, void *p);
   static void delete_TARSParameters(void *p);
   static void deleteArray_TARSParameters(void *p);
   static void destruct_TARSParameters(void *p);
   static void streamer_TARSParameters(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TARSParameters*)
   {
      ::TARSParameters *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TARSParameters >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TARSParameters", ::TARSParameters::Class_Version(), "TARSParameters.h", 28,
                  typeid(::TARSParameters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TARSParameters::Dictionary, isa_proxy, 16,
                  sizeof(::TARSParameters) );
      instance.SetNew(&new_TARSParameters);
      instance.SetNewArray(&newArray_TARSParameters);
      instance.SetDelete(&delete_TARSParameters);
      instance.SetDeleteArray(&deleteArray_TARSParameters);
      instance.SetDestructor(&destruct_TARSParameters);
      instance.SetStreamerFunc(&streamer_TARSParameters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TARSParameters*)
   {
      return GenerateInitInstanceLocal(static_cast<::TARSParameters*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TARSParameters*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TARSParameters::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TARSParameters::Class_Name()
{
   return "TARSParameters";
}

//______________________________________________________________________________
const char *TARSParameters::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSParameters*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TARSParameters::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSParameters*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TARSParameters::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSParameters*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TARSParameters::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSParameters*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TARSParameters::Streamer(TBuffer &R__b)
{
   // Stream an object of class TARSParameters.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fSize;
      fMatrix1->Streamer(R__b);
      fMatrix2->Streamer(R__b);
      R__b >> fBase;
      R__b >> fShape;
      R__b >> fSum;
      R__b >> fShape2;
      R__b.CheckByteCount(R__s, R__c, TARSParameters::IsA());
   } else {
      R__c = R__b.WriteVersion(TARSParameters::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fSize;
      fMatrix1->Streamer(R__b);
      fMatrix2->Streamer(R__b);
      R__b << fBase;
      R__b << fShape;
      R__b << fSum;
      R__b << fShape2;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TARSParameters(void *p) {
      return  p ? new(p) ::TARSParameters : new ::TARSParameters;
   }
   static void *newArray_TARSParameters(Long_t nElements, void *p) {
      return p ? new(p) ::TARSParameters[nElements] : new ::TARSParameters[nElements];
   }
   // Wrapper around operator delete
   static void delete_TARSParameters(void *p) {
      delete (static_cast<::TARSParameters*>(p));
   }
   static void deleteArray_TARSParameters(void *p) {
      delete [] (static_cast<::TARSParameters*>(p));
   }
   static void destruct_TARSParameters(void *p) {
      typedef ::TARSParameters current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TARSParameters(TBuffer &buf, void *obj) {
      ((::TARSParameters*)obj)->::TARSParameters::Streamer(buf);
   }
} // end of namespace ROOT for class ::TARSParameters

namespace {
  void TriggerDictionaryInitialization_TARSParametersDict_Impl() {
    static const char* headers[] = {
"TARSParameters.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TARSParametersDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TARSParameters.h")))  TARSParameters;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TARSParametersDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TARSParameters.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TARSParameters", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TARSParametersDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TARSParametersDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TARSParametersDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TARSParametersDict() {
  TriggerDictionaryInitialization_TARSParametersDict_Impl();
}
