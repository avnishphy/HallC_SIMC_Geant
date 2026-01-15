// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TBoolDict
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
#include "TBool.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TBool(void *p = nullptr);
   static void *newArray_TBool(Long_t size, void *p);
   static void delete_TBool(void *p);
   static void deleteArray_TBool(void *p);
   static void destruct_TBool(void *p);
   static void streamer_TBool(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TBool*)
   {
      ::TBool *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TBool >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TBool", ::TBool::Class_Version(), "TBool.h", 25,
                  typeid(::TBool), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TBool::Dictionary, isa_proxy, 16,
                  sizeof(::TBool) );
      instance.SetNew(&new_TBool);
      instance.SetNewArray(&newArray_TBool);
      instance.SetDelete(&delete_TBool);
      instance.SetDeleteArray(&deleteArray_TBool);
      instance.SetDestructor(&destruct_TBool);
      instance.SetStreamerFunc(&streamer_TBool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TBool*)
   {
      return GenerateInitInstanceLocal(static_cast<::TBool*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TBool*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TBool::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TBool::Class_Name()
{
   return "TBool";
}

//______________________________________________________________________________
const char *TBool::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TBool*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TBool::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TBool*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TBool::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TBool*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TBool::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TBool*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TBool::Streamer(TBuffer &R__b)
{
   // Stream an object of class TBool.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fValue;
      R__b.CheckByteCount(R__s, R__c, TBool::IsA());
   } else {
      R__c = R__b.WriteVersion(TBool::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fValue;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TBool(void *p) {
      return  p ? new(p) ::TBool : new ::TBool;
   }
   static void *newArray_TBool(Long_t nElements, void *p) {
      return p ? new(p) ::TBool[nElements] : new ::TBool[nElements];
   }
   // Wrapper around operator delete
   static void delete_TBool(void *p) {
      delete (static_cast<::TBool*>(p));
   }
   static void deleteArray_TBool(void *p) {
      delete [] (static_cast<::TBool*>(p));
   }
   static void destruct_TBool(void *p) {
      typedef ::TBool current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TBool(TBuffer &buf, void *obj) {
      ((::TBool*)obj)->::TBool::Streamer(buf);
   }
} // end of namespace ROOT for class ::TBool

namespace {
  void TriggerDictionaryInitialization_TBoolDict_Impl() {
    static const char* headers[] = {
"TBool.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TBoolDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TBool.h")))  TBool;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TBoolDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TBool.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TBool", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TBoolDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TBoolDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TBoolDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TBoolDict() {
  TriggerDictionaryInitialization_TBoolDict_Impl();
}
