// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TShortDict
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
#include "TShort.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TShort(void *p = nullptr);
   static void *newArray_TShort(Long_t size, void *p);
   static void delete_TShort(void *p);
   static void deleteArray_TShort(void *p);
   static void destruct_TShort(void *p);
   static void streamer_TShort(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TShort*)
   {
      ::TShort *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TShort >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TShort", ::TShort::Class_Version(), "TShort.h", 25,
                  typeid(::TShort), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TShort::Dictionary, isa_proxy, 16,
                  sizeof(::TShort) );
      instance.SetNew(&new_TShort);
      instance.SetNewArray(&newArray_TShort);
      instance.SetDelete(&delete_TShort);
      instance.SetDeleteArray(&deleteArray_TShort);
      instance.SetDestructor(&destruct_TShort);
      instance.SetStreamerFunc(&streamer_TShort);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TShort*)
   {
      return GenerateInitInstanceLocal(static_cast<::TShort*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TShort*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TShort::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TShort::Class_Name()
{
   return "TShort";
}

//______________________________________________________________________________
const char *TShort::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TShort*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TShort::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TShort*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TShort::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TShort*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TShort::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TShort*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TShort::Streamer(TBuffer &R__b)
{
   // Stream an object of class TShort.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fValue;
      R__b.CheckByteCount(R__s, R__c, TShort::IsA());
   } else {
      R__c = R__b.WriteVersion(TShort::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fValue;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TShort(void *p) {
      return  p ? new(p) ::TShort : new ::TShort;
   }
   static void *newArray_TShort(Long_t nElements, void *p) {
      return p ? new(p) ::TShort[nElements] : new ::TShort[nElements];
   }
   // Wrapper around operator delete
   static void delete_TShort(void *p) {
      delete (static_cast<::TShort*>(p));
   }
   static void deleteArray_TShort(void *p) {
      delete [] (static_cast<::TShort*>(p));
   }
   static void destruct_TShort(void *p) {
      typedef ::TShort current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TShort(TBuffer &buf, void *obj) {
      ((::TShort*)obj)->::TShort::Streamer(buf);
   }
} // end of namespace ROOT for class ::TShort

namespace {
  void TriggerDictionaryInitialization_TShortDict_Impl() {
    static const char* headers[] = {
"TShort.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TShortDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TShort.h")))  TShort;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TShortDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TShort.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TShort", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TShortDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TShortDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TShortDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TShortDict() {
  TriggerDictionaryInitialization_TShortDict_Impl();
}
