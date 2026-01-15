// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME THRSDict
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
#include "THRS.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_THRS(void *p = nullptr);
   static void *newArray_THRS(Long_t size, void *p);
   static void delete_THRS(void *p);
   static void deleteArray_THRS(void *p);
   static void destruct_THRS(void *p);
   static void streamer_THRS(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::THRS*)
   {
      ::THRS *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::THRS >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("THRS", ::THRS::Class_Version(), "THRS.h", 28,
                  typeid(::THRS), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::THRS::Dictionary, isa_proxy, 16,
                  sizeof(::THRS) );
      instance.SetNew(&new_THRS);
      instance.SetNewArray(&newArray_THRS);
      instance.SetDelete(&delete_THRS);
      instance.SetDeleteArray(&deleteArray_THRS);
      instance.SetDestructor(&destruct_THRS);
      instance.SetStreamerFunc(&streamer_THRS);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::THRS*)
   {
      return GenerateInitInstanceLocal(static_cast<::THRS*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::THRS*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr THRS::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *THRS::Class_Name()
{
   return "THRS";
}

//______________________________________________________________________________
const char *THRS::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::THRS*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int THRS::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::THRS*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *THRS::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::THRS*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *THRS::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::THRS*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void THRS::Streamer(TBuffer &R__b)
{
   // Stream an object of class THRS.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fScattered;
      R__b >> fScattered_c;
      R__b >> fP;
      R__b >> fTheta;
      R__b >> fPhi;
      R__b.CheckByteCount(R__s, R__c, THRS::IsA());
   } else {
      R__c = R__b.WriteVersion(THRS::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fScattered;
      R__b << fScattered_c;
      R__b << fP;
      R__b << fTheta;
      R__b << fPhi;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_THRS(void *p) {
      return  p ? new(p) ::THRS : new ::THRS;
   }
   static void *newArray_THRS(Long_t nElements, void *p) {
      return p ? new(p) ::THRS[nElements] : new ::THRS[nElements];
   }
   // Wrapper around operator delete
   static void delete_THRS(void *p) {
      delete (static_cast<::THRS*>(p));
   }
   static void deleteArray_THRS(void *p) {
      delete [] (static_cast<::THRS*>(p));
   }
   static void destruct_THRS(void *p) {
      typedef ::THRS current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_THRS(TBuffer &buf, void *obj) {
      ((::THRS*)obj)->::THRS::Streamer(buf);
   }
} // end of namespace ROOT for class ::THRS

namespace {
  void TriggerDictionaryInitialization_THRSDict_Impl() {
    static const char* headers[] = {
"THRS.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "THRSDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$THRS.h")))  THRS;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "THRSDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "THRS.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"THRS", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("THRSDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_THRSDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_THRSDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_THRSDict() {
  TriggerDictionaryInitialization_THRSDict_Impl();
}
