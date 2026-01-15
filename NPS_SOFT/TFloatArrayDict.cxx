// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TFloatArrayDict
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
#include "TFloatArray.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TFloatArray(void *p = nullptr);
   static void *newArray_TFloatArray(Long_t size, void *p);
   static void delete_TFloatArray(void *p);
   static void deleteArray_TFloatArray(void *p);
   static void destruct_TFloatArray(void *p);
   static void streamer_TFloatArray(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFloatArray*)
   {
      ::TFloatArray *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFloatArray >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TFloatArray", ::TFloatArray::Class_Version(), "TFloatArray.h", 33,
                  typeid(::TFloatArray), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFloatArray::Dictionary, isa_proxy, 16,
                  sizeof(::TFloatArray) );
      instance.SetNew(&new_TFloatArray);
      instance.SetNewArray(&newArray_TFloatArray);
      instance.SetDelete(&delete_TFloatArray);
      instance.SetDeleteArray(&deleteArray_TFloatArray);
      instance.SetDestructor(&destruct_TFloatArray);
      instance.SetStreamerFunc(&streamer_TFloatArray);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFloatArray*)
   {
      return GenerateInitInstanceLocal(static_cast<::TFloatArray*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TFloatArray*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TFloatArray::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TFloatArray::Class_Name()
{
   return "TFloatArray";
}

//______________________________________________________________________________
const char *TFloatArray::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFloatArray*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TFloatArray::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFloatArray*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFloatArray::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFloatArray*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFloatArray::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFloatArray*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TFloatArray::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFloatArray.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      fData->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TFloatArray::IsA());
   } else {
      R__c = R__b.WriteVersion(TFloatArray::IsA(), kTRUE);
      TObject::Streamer(R__b);
      fData->Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFloatArray(void *p) {
      return  p ? new(p) ::TFloatArray : new ::TFloatArray;
   }
   static void *newArray_TFloatArray(Long_t nElements, void *p) {
      return p ? new(p) ::TFloatArray[nElements] : new ::TFloatArray[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFloatArray(void *p) {
      delete (static_cast<::TFloatArray*>(p));
   }
   static void deleteArray_TFloatArray(void *p) {
      delete [] (static_cast<::TFloatArray*>(p));
   }
   static void destruct_TFloatArray(void *p) {
      typedef ::TFloatArray current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TFloatArray(TBuffer &buf, void *obj) {
      ((::TFloatArray*)obj)->::TFloatArray::Streamer(buf);
   }
} // end of namespace ROOT for class ::TFloatArray

namespace {
  void TriggerDictionaryInitialization_TFloatArrayDict_Impl() {
    static const char* headers[] = {
"TFloatArray.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TFloatArrayDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TFloatArray.h")))  TFloatArray;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TFloatArrayDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TFloatArray.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TFloatArray", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TFloatArrayDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TFloatArrayDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TFloatArrayDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TFloatArrayDict() {
  TriggerDictionaryInitialization_TFloatArrayDict_Impl();
}
