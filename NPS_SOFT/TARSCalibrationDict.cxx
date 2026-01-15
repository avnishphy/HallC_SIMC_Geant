// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TARSCalibrationDict
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
#include "TARSCalibration.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TARSCalibration(void *p = nullptr);
   static void *newArray_TARSCalibration(Long_t size, void *p);
   static void delete_TARSCalibration(void *p);
   static void deleteArray_TARSCalibration(void *p);
   static void destruct_TARSCalibration(void *p);
   static void streamer_TARSCalibration(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TARSCalibration*)
   {
      ::TARSCalibration *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TARSCalibration >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TARSCalibration", ::TARSCalibration::Class_Version(), "TARSCalibration.h", 15,
                  typeid(::TARSCalibration), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TARSCalibration::Dictionary, isa_proxy, 16,
                  sizeof(::TARSCalibration) );
      instance.SetNew(&new_TARSCalibration);
      instance.SetNewArray(&newArray_TARSCalibration);
      instance.SetDelete(&delete_TARSCalibration);
      instance.SetDeleteArray(&deleteArray_TARSCalibration);
      instance.SetDestructor(&destruct_TARSCalibration);
      instance.SetStreamerFunc(&streamer_TARSCalibration);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TARSCalibration*)
   {
      return GenerateInitInstanceLocal(static_cast<::TARSCalibration*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TARSCalibration*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TARSCalibration::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TARSCalibration::Class_Name()
{
   return "TARSCalibration";
}

//______________________________________________________________________________
const char *TARSCalibration::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSCalibration*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TARSCalibration::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSCalibration*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TARSCalibration::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSCalibration*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TARSCalibration::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSCalibration*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TARSCalibration::Streamer(TBuffer &R__b)
{
   // Stream an object of class TARSCalibration.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fTimeOffset;
      R__b >> fEConst;
      R__b.CheckByteCount(R__s, R__c, TARSCalibration::IsA());
   } else {
      R__c = R__b.WriteVersion(TARSCalibration::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fTimeOffset;
      R__b << fEConst;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TARSCalibration(void *p) {
      return  p ? new(p) ::TARSCalibration : new ::TARSCalibration;
   }
   static void *newArray_TARSCalibration(Long_t nElements, void *p) {
      return p ? new(p) ::TARSCalibration[nElements] : new ::TARSCalibration[nElements];
   }
   // Wrapper around operator delete
   static void delete_TARSCalibration(void *p) {
      delete (static_cast<::TARSCalibration*>(p));
   }
   static void deleteArray_TARSCalibration(void *p) {
      delete [] (static_cast<::TARSCalibration*>(p));
   }
   static void destruct_TARSCalibration(void *p) {
      typedef ::TARSCalibration current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TARSCalibration(TBuffer &buf, void *obj) {
      ((::TARSCalibration*)obj)->::TARSCalibration::Streamer(buf);
   }
} // end of namespace ROOT for class ::TARSCalibration

namespace {
  void TriggerDictionaryInitialization_TARSCalibrationDict_Impl() {
    static const char* headers[] = {
"TARSCalibration.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TARSCalibrationDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TARSCalibration.h")))  TARSCalibration;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TARSCalibrationDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TARSCalibration.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TARSCalibration", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TARSCalibrationDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TARSCalibrationDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TARSCalibrationDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TARSCalibrationDict() {
  TriggerDictionaryInitialization_TARSCalibrationDict_Impl();
}
