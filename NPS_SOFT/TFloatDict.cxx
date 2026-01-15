// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TFloatDict
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
#include "TFloat.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TFloat(void *p = nullptr);
   static void *newArray_TFloat(Long_t size, void *p);
   static void delete_TFloat(void *p);
   static void deleteArray_TFloat(void *p);
   static void destruct_TFloat(void *p);
   static void streamer_TFloat(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFloat*)
   {
      ::TFloat *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFloat >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TFloat", ::TFloat::Class_Version(), "TFloat.h", 25,
                  typeid(::TFloat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFloat::Dictionary, isa_proxy, 16,
                  sizeof(::TFloat) );
      instance.SetNew(&new_TFloat);
      instance.SetNewArray(&newArray_TFloat);
      instance.SetDelete(&delete_TFloat);
      instance.SetDeleteArray(&deleteArray_TFloat);
      instance.SetDestructor(&destruct_TFloat);
      instance.SetStreamerFunc(&streamer_TFloat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFloat*)
   {
      return GenerateInitInstanceLocal(static_cast<::TFloat*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TFloat*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TFloat::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TFloat::Class_Name()
{
   return "TFloat";
}

//______________________________________________________________________________
const char *TFloat::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFloat*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TFloat::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFloat*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFloat::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFloat*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFloat::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFloat*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TFloat::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFloat.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fValue;
      R__b.CheckByteCount(R__s, R__c, TFloat::IsA());
   } else {
      R__c = R__b.WriteVersion(TFloat::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fValue;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFloat(void *p) {
      return  p ? new(p) ::TFloat : new ::TFloat;
   }
   static void *newArray_TFloat(Long_t nElements, void *p) {
      return p ? new(p) ::TFloat[nElements] : new ::TFloat[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFloat(void *p) {
      delete (static_cast<::TFloat*>(p));
   }
   static void deleteArray_TFloat(void *p) {
      delete [] (static_cast<::TFloat*>(p));
   }
   static void destruct_TFloat(void *p) {
      typedef ::TFloat current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TFloat(TBuffer &buf, void *obj) {
      ((::TFloat*)obj)->::TFloat::Streamer(buf);
   }
} // end of namespace ROOT for class ::TFloat

namespace {
  void TriggerDictionaryInitialization_TFloatDict_Impl() {
    static const char* headers[] = {
"TFloat.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TFloatDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TFloat.h")))  TFloat;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TFloatDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TFloat.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TFloat", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TFloatDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TFloatDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TFloatDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TFloatDict() {
  TriggerDictionaryInitialization_TFloatDict_Impl();
}
