// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloCalibrationDict
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
#include "TCaloCalibration.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloCalibration(void *p = nullptr);
   static void *newArray_TCaloCalibration(Long_t size, void *p);
   static void delete_TCaloCalibration(void *p);
   static void deleteArray_TCaloCalibration(void *p);
   static void destruct_TCaloCalibration(void *p);
   static void streamer_TCaloCalibration(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloCalibration*)
   {
      ::TCaloCalibration *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloCalibration >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloCalibration", ::TCaloCalibration::Class_Version(), "TCaloCalibration.h", 22,
                  typeid(::TCaloCalibration), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloCalibration::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloCalibration) );
      instance.SetNew(&new_TCaloCalibration);
      instance.SetNewArray(&newArray_TCaloCalibration);
      instance.SetDelete(&delete_TCaloCalibration);
      instance.SetDeleteArray(&deleteArray_TCaloCalibration);
      instance.SetDestructor(&destruct_TCaloCalibration);
      instance.SetStreamerFunc(&streamer_TCaloCalibration);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloCalibration*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloCalibration*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloCalibration*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloCalibration::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloCalibration::Class_Name()
{
   return "TCaloCalibration";
}

//______________________________________________________________________________
const char *TCaloCalibration::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloCalibration*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloCalibration::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloCalibration*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloCalibration::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloCalibration*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloCalibration::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloCalibration*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloCalibration::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloCalibration.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TCaloCalibration::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloCalibration::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloCalibration(void *p) {
      return  p ? new(p) ::TCaloCalibration : new ::TCaloCalibration;
   }
   static void *newArray_TCaloCalibration(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloCalibration[nElements] : new ::TCaloCalibration[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloCalibration(void *p) {
      delete (static_cast<::TCaloCalibration*>(p));
   }
   static void deleteArray_TCaloCalibration(void *p) {
      delete [] (static_cast<::TCaloCalibration*>(p));
   }
   static void destruct_TCaloCalibration(void *p) {
      typedef ::TCaloCalibration current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloCalibration(TBuffer &buf, void *obj) {
      ((::TCaloCalibration*)obj)->::TCaloCalibration::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloCalibration

namespace {
  void TriggerDictionaryInitialization_TCaloCalibrationDict_Impl() {
    static const char* headers[] = {
"TCaloCalibration.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloCalibrationDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloCalibration.h")))  TCaloCalibration;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloCalibrationDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloCalibration.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloCalibration", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloCalibrationDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloCalibrationDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloCalibrationDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloCalibrationDict() {
  TriggerDictionaryInitialization_TCaloCalibrationDict_Impl();
}
