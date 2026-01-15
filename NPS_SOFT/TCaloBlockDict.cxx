// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloBlockDict
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
#include "TCaloBlock.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloBlock(void *p = nullptr);
   static void *newArray_TCaloBlock(Long_t size, void *p);
   static void delete_TCaloBlock(void *p);
   static void deleteArray_TCaloBlock(void *p);
   static void destruct_TCaloBlock(void *p);
   static void streamer_TCaloBlock(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloBlock*)
   {
      ::TCaloBlock *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloBlock >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloBlock", ::TCaloBlock::Class_Version(), "TCaloBlock.h", 33,
                  typeid(::TCaloBlock), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloBlock::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloBlock) );
      instance.SetNew(&new_TCaloBlock);
      instance.SetNewArray(&newArray_TCaloBlock);
      instance.SetDelete(&delete_TCaloBlock);
      instance.SetDeleteArray(&deleteArray_TCaloBlock);
      instance.SetDestructor(&destruct_TCaloBlock);
      instance.SetStreamerFunc(&streamer_TCaloBlock);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloBlock*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloBlock*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloBlock*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloBlock::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloBlock::Class_Name()
{
   return "TCaloBlock";
}

//______________________________________________________________________________
const char *TCaloBlock::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloBlock*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloBlock::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloBlock*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloBlock::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloBlock*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloBlock::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloBlock*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloBlock::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloBlock.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TCaloBase::Streamer(R__b);
      R__b >> fBlockNb;
      R__b >> fNPulse;
      fEnergy->Streamer(R__b);
      fTime->Streamer(R__b);
      fChi2->Streamer(R__b);
      R__b >> fBase;
      R__b >> fAnalyzed;
      R__b.CheckByteCount(R__s, R__c, TCaloBlock::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloBlock::IsA(), kTRUE);
      TCaloBase::Streamer(R__b);
      R__b << fBlockNb;
      R__b << fNPulse;
      fEnergy->Streamer(R__b);
      fTime->Streamer(R__b);
      fChi2->Streamer(R__b);
      R__b << fBase;
      R__b << fAnalyzed;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloBlock(void *p) {
      return  p ? new(p) ::TCaloBlock : new ::TCaloBlock;
   }
   static void *newArray_TCaloBlock(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloBlock[nElements] : new ::TCaloBlock[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloBlock(void *p) {
      delete (static_cast<::TCaloBlock*>(p));
   }
   static void deleteArray_TCaloBlock(void *p) {
      delete [] (static_cast<::TCaloBlock*>(p));
   }
   static void destruct_TCaloBlock(void *p) {
      typedef ::TCaloBlock current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloBlock(TBuffer &buf, void *obj) {
      ((::TCaloBlock*)obj)->::TCaloBlock::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloBlock

namespace {
  void TriggerDictionaryInitialization_TCaloBlockDict_Impl() {
    static const char* headers[] = {
"TCaloBlock.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloBlockDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloBlock.h")))  TCaloBlock;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloBlockDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloBlock.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloBlock", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloBlockDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloBlockDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloBlockDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloBlockDict() {
  TriggerDictionaryInitialization_TCaloBlockDict_Impl();
}
