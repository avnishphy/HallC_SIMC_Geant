// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TARSArrayDict
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
#include "TARSArray.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TARSArray(void *p = nullptr);
   static void *newArray_TARSArray(Long_t size, void *p);
   static void delete_TARSArray(void *p);
   static void deleteArray_TARSArray(void *p);
   static void destruct_TARSArray(void *p);
   static void streamer_TARSArray(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TARSArray*)
   {
      ::TARSArray *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TARSArray >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TARSArray", ::TARSArray::Class_Version(), "TARSArray.h", 29,
                  typeid(::TARSArray), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TARSArray::Dictionary, isa_proxy, 16,
                  sizeof(::TARSArray) );
      instance.SetNew(&new_TARSArray);
      instance.SetNewArray(&newArray_TARSArray);
      instance.SetDelete(&delete_TARSArray);
      instance.SetDeleteArray(&deleteArray_TARSArray);
      instance.SetDestructor(&destruct_TARSArray);
      instance.SetStreamerFunc(&streamer_TARSArray);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TARSArray*)
   {
      return GenerateInitInstanceLocal(static_cast<::TARSArray*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TARSArray*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TARSArray::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TARSArray::Class_Name()
{
   return "TARSArray";
}

//______________________________________________________________________________
const char *TARSArray::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSArray*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TARSArray::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSArray*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TARSArray::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSArray*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TARSArray::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSArray*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TARSArray::Streamer(TBuffer &R__b)
{
   // Stream an object of class TARSArray.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      fWave->Streamer(R__b);
      R__b >> fNbWaves;
      R__b.CheckByteCount(R__s, R__c, TARSArray::IsA());
   } else {
      R__c = R__b.WriteVersion(TARSArray::IsA(), kTRUE);
      TObject::Streamer(R__b);
      fWave->Streamer(R__b);
      R__b << fNbWaves;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TARSArray(void *p) {
      return  p ? new(p) ::TARSArray : new ::TARSArray;
   }
   static void *newArray_TARSArray(Long_t nElements, void *p) {
      return p ? new(p) ::TARSArray[nElements] : new ::TARSArray[nElements];
   }
   // Wrapper around operator delete
   static void delete_TARSArray(void *p) {
      delete (static_cast<::TARSArray*>(p));
   }
   static void deleteArray_TARSArray(void *p) {
      delete [] (static_cast<::TARSArray*>(p));
   }
   static void destruct_TARSArray(void *p) {
      typedef ::TARSArray current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TARSArray(TBuffer &buf, void *obj) {
      ((::TARSArray*)obj)->::TARSArray::Streamer(buf);
   }
} // end of namespace ROOT for class ::TARSArray

namespace {
  void TriggerDictionaryInitialization_TARSArrayDict_Impl() {
    static const char* headers[] = {
"TARSArray.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TARSArrayDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TARSArray.h")))  TARSArray;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TARSArrayDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TARSArray.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TARSArray", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TARSArrayDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TARSArrayDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TARSArrayDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TARSArrayDict() {
  TriggerDictionaryInitialization_TARSArrayDict_Impl();
}
