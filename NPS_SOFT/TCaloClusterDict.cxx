// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloClusterDict
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
#include "TCaloCluster.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloCluster(void *p = nullptr);
   static void *newArray_TCaloCluster(Long_t size, void *p);
   static void delete_TCaloCluster(void *p);
   static void deleteArray_TCaloCluster(void *p);
   static void destruct_TCaloCluster(void *p);
   static void streamer_TCaloCluster(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloCluster*)
   {
      ::TCaloCluster *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloCluster >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloCluster", ::TCaloCluster::Class_Version(), "TCaloCluster.h", 42,
                  typeid(::TCaloCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloCluster::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloCluster) );
      instance.SetNew(&new_TCaloCluster);
      instance.SetNewArray(&newArray_TCaloCluster);
      instance.SetDelete(&delete_TCaloCluster);
      instance.SetDeleteArray(&deleteArray_TCaloCluster);
      instance.SetDestructor(&destruct_TCaloCluster);
      instance.SetStreamerFunc(&streamer_TCaloCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloCluster*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloCluster*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloCluster*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloCluster::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloCluster::Class_Name()
{
   return "TCaloCluster";
}

//______________________________________________________________________________
const char *TCaloCluster::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloCluster*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloCluster::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloCluster*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloCluster::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloCluster*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloCluster::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloCluster*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloCluster::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloCluster.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TCaloBase::Streamer(R__b);
      fClusBlock->Streamer(R__b);
      R__b >> fClusSize;
      R__b >> fEnergy;
      R__b >> fX;
      R__b >> fY;
      R__b >> fAnalyzed;
      R__b.CheckByteCount(R__s, R__c, TCaloCluster::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloCluster::IsA(), kTRUE);
      TCaloBase::Streamer(R__b);
      fClusBlock->Streamer(R__b);
      R__b << fClusSize;
      R__b << fEnergy;
      R__b << fX;
      R__b << fY;
      R__b << fAnalyzed;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloCluster(void *p) {
      return  p ? new(p) ::TCaloCluster : new ::TCaloCluster;
   }
   static void *newArray_TCaloCluster(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloCluster[nElements] : new ::TCaloCluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloCluster(void *p) {
      delete (static_cast<::TCaloCluster*>(p));
   }
   static void deleteArray_TCaloCluster(void *p) {
      delete [] (static_cast<::TCaloCluster*>(p));
   }
   static void destruct_TCaloCluster(void *p) {
      typedef ::TCaloCluster current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloCluster(TBuffer &buf, void *obj) {
      ((::TCaloCluster*)obj)->::TCaloCluster::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloCluster

namespace {
  void TriggerDictionaryInitialization_TCaloClusterDict_Impl() {
    static const char* headers[] = {
"TCaloCluster.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloClusterDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloCluster.h")))  TCaloCluster;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloClusterDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloCluster.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloCluster", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloClusterDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloClusterDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloClusterDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloClusterDict() {
  TriggerDictionaryInitialization_TCaloClusterDict_Impl();
}
