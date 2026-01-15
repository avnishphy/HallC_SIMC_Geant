// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDoubleDict
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
#include "TDouble.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TDouble(void *p = nullptr);
   static void *newArray_TDouble(Long_t size, void *p);
   static void delete_TDouble(void *p);
   static void deleteArray_TDouble(void *p);
   static void destruct_TDouble(void *p);
   static void streamer_TDouble(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDouble*)
   {
      ::TDouble *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDouble >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDouble", ::TDouble::Class_Version(), "TDouble.h", 25,
                  typeid(::TDouble), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDouble::Dictionary, isa_proxy, 16,
                  sizeof(::TDouble) );
      instance.SetNew(&new_TDouble);
      instance.SetNewArray(&newArray_TDouble);
      instance.SetDelete(&delete_TDouble);
      instance.SetDeleteArray(&deleteArray_TDouble);
      instance.SetDestructor(&destruct_TDouble);
      instance.SetStreamerFunc(&streamer_TDouble);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDouble*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDouble*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDouble*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDouble::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDouble::Class_Name()
{
   return "TDouble";
}

//______________________________________________________________________________
const char *TDouble::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDouble*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDouble::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDouble*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDouble::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDouble*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDouble::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDouble*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDouble::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDouble.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fValue;
      R__b.CheckByteCount(R__s, R__c, TDouble::IsA());
   } else {
      R__c = R__b.WriteVersion(TDouble::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fValue;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TDouble(void *p) {
      return  p ? new(p) ::TDouble : new ::TDouble;
   }
   static void *newArray_TDouble(Long_t nElements, void *p) {
      return p ? new(p) ::TDouble[nElements] : new ::TDouble[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDouble(void *p) {
      delete (static_cast<::TDouble*>(p));
   }
   static void deleteArray_TDouble(void *p) {
      delete [] (static_cast<::TDouble*>(p));
   }
   static void destruct_TDouble(void *p) {
      typedef ::TDouble current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDouble(TBuffer &buf, void *obj) {
      ((::TDouble*)obj)->::TDouble::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDouble

namespace {
  void TriggerDictionaryInitialization_TDoubleDict_Impl() {
    static const char* headers[] = {
"TDouble.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDoubleDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDouble.h")))  TDouble;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDoubleDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDouble.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDouble", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDoubleDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDoubleDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDoubleDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDoubleDict() {
  TriggerDictionaryInitialization_TDoubleDict_Impl();
}
