// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TIntDict
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
#include "TInt.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TInt(void *p = nullptr);
   static void *newArray_TInt(Long_t size, void *p);
   static void delete_TInt(void *p);
   static void deleteArray_TInt(void *p);
   static void destruct_TInt(void *p);
   static void streamer_TInt(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TInt*)
   {
      ::TInt *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TInt >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TInt", ::TInt::Class_Version(), "TInt.h", 25,
                  typeid(::TInt), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TInt::Dictionary, isa_proxy, 16,
                  sizeof(::TInt) );
      instance.SetNew(&new_TInt);
      instance.SetNewArray(&newArray_TInt);
      instance.SetDelete(&delete_TInt);
      instance.SetDeleteArray(&deleteArray_TInt);
      instance.SetDestructor(&destruct_TInt);
      instance.SetStreamerFunc(&streamer_TInt);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TInt*)
   {
      return GenerateInitInstanceLocal(static_cast<::TInt*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TInt*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TInt::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TInt::Class_Name()
{
   return "TInt";
}

//______________________________________________________________________________
const char *TInt::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TInt*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TInt::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TInt*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TInt::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TInt*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TInt::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TInt*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TInt::Streamer(TBuffer &R__b)
{
   // Stream an object of class TInt.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fValue;
      R__b.CheckByteCount(R__s, R__c, TInt::IsA());
   } else {
      R__c = R__b.WriteVersion(TInt::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fValue;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TInt(void *p) {
      return  p ? new(p) ::TInt : new ::TInt;
   }
   static void *newArray_TInt(Long_t nElements, void *p) {
      return p ? new(p) ::TInt[nElements] : new ::TInt[nElements];
   }
   // Wrapper around operator delete
   static void delete_TInt(void *p) {
      delete (static_cast<::TInt*>(p));
   }
   static void deleteArray_TInt(void *p) {
      delete [] (static_cast<::TInt*>(p));
   }
   static void destruct_TInt(void *p) {
      typedef ::TInt current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TInt(TBuffer &buf, void *obj) {
      ((::TInt*)obj)->::TInt::Streamer(buf);
   }
} // end of namespace ROOT for class ::TInt

namespace {
  void TriggerDictionaryInitialization_TIntDict_Impl() {
    static const char* headers[] = {
"TInt.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TIntDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TInt.h")))  TInt;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TIntDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TInt.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TInt", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TIntDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TIntDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TIntDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TIntDict() {
  TriggerDictionaryInitialization_TIntDict_Impl();
}
