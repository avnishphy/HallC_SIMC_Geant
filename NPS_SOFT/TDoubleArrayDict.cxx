// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDoubleArrayDict
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
#include "TDoubleArray.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TDoubleArray(void *p = nullptr);
   static void *newArray_TDoubleArray(Long_t size, void *p);
   static void delete_TDoubleArray(void *p);
   static void deleteArray_TDoubleArray(void *p);
   static void destruct_TDoubleArray(void *p);
   static void streamer_TDoubleArray(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDoubleArray*)
   {
      ::TDoubleArray *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDoubleArray >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDoubleArray", ::TDoubleArray::Class_Version(), "TDoubleArray.h", 17,
                  typeid(::TDoubleArray), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDoubleArray::Dictionary, isa_proxy, 16,
                  sizeof(::TDoubleArray) );
      instance.SetNew(&new_TDoubleArray);
      instance.SetNewArray(&newArray_TDoubleArray);
      instance.SetDelete(&delete_TDoubleArray);
      instance.SetDeleteArray(&deleteArray_TDoubleArray);
      instance.SetDestructor(&destruct_TDoubleArray);
      instance.SetStreamerFunc(&streamer_TDoubleArray);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDoubleArray*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDoubleArray*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDoubleArray*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDoubleArray::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDoubleArray::Class_Name()
{
   return "TDoubleArray";
}

//______________________________________________________________________________
const char *TDoubleArray::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDoubleArray*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDoubleArray::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDoubleArray*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDoubleArray::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDoubleArray*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDoubleArray::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDoubleArray*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDoubleArray::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDoubleArray.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fSz;
      R__b >> fN;
      delete [] fDarray;
      fDarray = new Double_t[fN];
      R__b.ReadFastArray(fDarray,fN);
      R__b.CheckByteCount(R__s, R__c, TDoubleArray::IsA());
   } else {
      R__c = R__b.WriteVersion(TDoubleArray::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fSz;
      R__b << fN;
      R__b.WriteFastArray(fDarray,fN);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TDoubleArray(void *p) {
      return  p ? new(p) ::TDoubleArray : new ::TDoubleArray;
   }
   static void *newArray_TDoubleArray(Long_t nElements, void *p) {
      return p ? new(p) ::TDoubleArray[nElements] : new ::TDoubleArray[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDoubleArray(void *p) {
      delete (static_cast<::TDoubleArray*>(p));
   }
   static void deleteArray_TDoubleArray(void *p) {
      delete [] (static_cast<::TDoubleArray*>(p));
   }
   static void destruct_TDoubleArray(void *p) {
      typedef ::TDoubleArray current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDoubleArray(TBuffer &buf, void *obj) {
      ((::TDoubleArray*)obj)->::TDoubleArray::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDoubleArray

namespace {
  void TriggerDictionaryInitialization_TDoubleArrayDict_Impl() {
    static const char* headers[] = {
"TDoubleArray.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDoubleArrayDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDoubleArray.h")))  TDoubleArray;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDoubleArrayDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDoubleArray.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDoubleArray", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDoubleArrayDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDoubleArrayDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDoubleArrayDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDoubleArrayDict() {
  TriggerDictionaryInitialization_TDoubleArrayDict_Impl();
}
