// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TShortArrayDict
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
#include "TShortArray.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TShortArray(void *p = nullptr);
   static void *newArray_TShortArray(Long_t size, void *p);
   static void delete_TShortArray(void *p);
   static void deleteArray_TShortArray(void *p);
   static void destruct_TShortArray(void *p);
   static void streamer_TShortArray(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TShortArray*)
   {
      ::TShortArray *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TShortArray >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TShortArray", ::TShortArray::Class_Version(), "TShortArray.h", 33,
                  typeid(::TShortArray), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TShortArray::Dictionary, isa_proxy, 16,
                  sizeof(::TShortArray) );
      instance.SetNew(&new_TShortArray);
      instance.SetNewArray(&newArray_TShortArray);
      instance.SetDelete(&delete_TShortArray);
      instance.SetDeleteArray(&deleteArray_TShortArray);
      instance.SetDestructor(&destruct_TShortArray);
      instance.SetStreamerFunc(&streamer_TShortArray);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TShortArray*)
   {
      return GenerateInitInstanceLocal(static_cast<::TShortArray*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TShortArray*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TShortArray::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TShortArray::Class_Name()
{
   return "TShortArray";
}

//______________________________________________________________________________
const char *TShortArray::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TShortArray*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TShortArray::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TShortArray*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TShortArray::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TShortArray*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TShortArray::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TShortArray*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TShortArray::Streamer(TBuffer &R__b)
{
   // Stream an object of class TShortArray.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      fData->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TShortArray::IsA());
   } else {
      R__c = R__b.WriteVersion(TShortArray::IsA(), kTRUE);
      TObject::Streamer(R__b);
      fData->Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TShortArray(void *p) {
      return  p ? new(p) ::TShortArray : new ::TShortArray;
   }
   static void *newArray_TShortArray(Long_t nElements, void *p) {
      return p ? new(p) ::TShortArray[nElements] : new ::TShortArray[nElements];
   }
   // Wrapper around operator delete
   static void delete_TShortArray(void *p) {
      delete (static_cast<::TShortArray*>(p));
   }
   static void deleteArray_TShortArray(void *p) {
      delete [] (static_cast<::TShortArray*>(p));
   }
   static void destruct_TShortArray(void *p) {
      typedef ::TShortArray current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TShortArray(TBuffer &buf, void *obj) {
      ((::TShortArray*)obj)->::TShortArray::Streamer(buf);
   }
} // end of namespace ROOT for class ::TShortArray

namespace {
  void TriggerDictionaryInitialization_TShortArrayDict_Impl() {
    static const char* headers[] = {
"TShortArray.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TShortArrayDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TShortArray.h")))  TShortArray;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TShortArrayDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TShortArray.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TShortArray", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TShortArrayDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TShortArrayDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TShortArrayDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TShortArrayDict() {
  TriggerDictionaryInitialization_TShortArrayDict_Impl();
}
