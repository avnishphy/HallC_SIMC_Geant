// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDVCSELossDict
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
#include "TDVCSELoss.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TDVCSELoss(void *p = nullptr);
   static void *newArray_TDVCSELoss(Long_t size, void *p);
   static void delete_TDVCSELoss(void *p);
   static void deleteArray_TDVCSELoss(void *p);
   static void destruct_TDVCSELoss(void *p);
   static void streamer_TDVCSELoss(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDVCSELoss*)
   {
      ::TDVCSELoss *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDVCSELoss >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDVCSELoss", ::TDVCSELoss::Class_Version(), "TDVCSELoss.h", 8,
                  typeid(::TDVCSELoss), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDVCSELoss::Dictionary, isa_proxy, 16,
                  sizeof(::TDVCSELoss) );
      instance.SetNew(&new_TDVCSELoss);
      instance.SetNewArray(&newArray_TDVCSELoss);
      instance.SetDelete(&delete_TDVCSELoss);
      instance.SetDeleteArray(&deleteArray_TDVCSELoss);
      instance.SetDestructor(&destruct_TDVCSELoss);
      instance.SetStreamerFunc(&streamer_TDVCSELoss);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDVCSELoss*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDVCSELoss*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDVCSELoss*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDVCSELoss::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDVCSELoss::Class_Name()
{
   return "TDVCSELoss";
}

//______________________________________________________________________________
const char *TDVCSELoss::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSELoss*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDVCSELoss::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSELoss*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDVCSELoss::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSELoss*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDVCSELoss::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSELoss*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDVCSELoss::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDVCSELoss.

   ::Error("TDVCSELoss::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TDVCSELoss(void *p) {
      return  p ? new(p) ::TDVCSELoss : new ::TDVCSELoss;
   }
   static void *newArray_TDVCSELoss(Long_t nElements, void *p) {
      return p ? new(p) ::TDVCSELoss[nElements] : new ::TDVCSELoss[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDVCSELoss(void *p) {
      delete (static_cast<::TDVCSELoss*>(p));
   }
   static void deleteArray_TDVCSELoss(void *p) {
      delete [] (static_cast<::TDVCSELoss*>(p));
   }
   static void destruct_TDVCSELoss(void *p) {
      typedef ::TDVCSELoss current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDVCSELoss(TBuffer &buf, void *obj) {
      ((::TDVCSELoss*)obj)->::TDVCSELoss::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDVCSELoss

namespace {
  void TriggerDictionaryInitialization_TDVCSELossDict_Impl() {
    static const char* headers[] = {
"TDVCSELoss.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDVCSELossDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDVCSELoss.h")))  TDVCSELoss;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDVCSELossDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDVCSELoss.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDVCSELoss", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDVCSELossDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDVCSELossDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDVCSELossDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDVCSELossDict() {
  TriggerDictionaryInitialization_TDVCSELossDict_Impl();
}
