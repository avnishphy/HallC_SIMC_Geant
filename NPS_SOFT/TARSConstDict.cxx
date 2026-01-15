// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TARSConstDict
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
#include "TARSConst.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TARSConst(void *p = nullptr);
   static void *newArray_TARSConst(Long_t size, void *p);
   static void delete_TARSConst(void *p);
   static void deleteArray_TARSConst(void *p);
   static void destruct_TARSConst(void *p);
   static void streamer_TARSConst(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TARSConst*)
   {
      ::TARSConst *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TARSConst >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TARSConst", ::TARSConst::Class_Version(), "TARSConst.h", 20,
                  typeid(::TARSConst), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TARSConst::Dictionary, isa_proxy, 16,
                  sizeof(::TARSConst) );
      instance.SetNew(&new_TARSConst);
      instance.SetNewArray(&newArray_TARSConst);
      instance.SetDelete(&delete_TARSConst);
      instance.SetDeleteArray(&deleteArray_TARSConst);
      instance.SetDestructor(&destruct_TARSConst);
      instance.SetStreamerFunc(&streamer_TARSConst);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TARSConst*)
   {
      return GenerateInitInstanceLocal(static_cast<::TARSConst*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TARSConst*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TARSConst::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TARSConst::Class_Name()
{
   return "TARSConst";
}

//______________________________________________________________________________
const char *TARSConst::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSConst*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TARSConst::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSConst*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TARSConst::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSConst*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TARSConst::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSConst*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TARSConst::Streamer(TBuffer &R__b)
{
   // Stream an object of class TARSConst.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.ReadStaticArray((double*)fChi2);
      R__b.ReadStaticArray((double*)fTime);
      R__b.ReadStaticArray((double*)fAmpLim);
      R__b.CheckByteCount(R__s, R__c, TARSConst::IsA());
   } else {
      R__c = R__b.WriteVersion(TARSConst::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.WriteArray(fChi2, 3);
      R__b.WriteArray((double*)fTime, 4);
      R__b.WriteArray(fAmpLim, 2);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TARSConst(void *p) {
      return  p ? new(p) ::TARSConst : new ::TARSConst;
   }
   static void *newArray_TARSConst(Long_t nElements, void *p) {
      return p ? new(p) ::TARSConst[nElements] : new ::TARSConst[nElements];
   }
   // Wrapper around operator delete
   static void delete_TARSConst(void *p) {
      delete (static_cast<::TARSConst*>(p));
   }
   static void deleteArray_TARSConst(void *p) {
      delete [] (static_cast<::TARSConst*>(p));
   }
   static void destruct_TARSConst(void *p) {
      typedef ::TARSConst current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TARSConst(TBuffer &buf, void *obj) {
      ((::TARSConst*)obj)->::TARSConst::Streamer(buf);
   }
} // end of namespace ROOT for class ::TARSConst

namespace {
  void TriggerDictionaryInitialization_TARSConstDict_Impl() {
    static const char* headers[] = {
"TARSConst.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TARSConstDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TARSConst.h")))  TARSConst;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TARSConstDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TARSConst.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TARSConst", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TARSConstDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TARSConstDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TARSConstDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TARSConstDict() {
  TriggerDictionaryInitialization_TARSConstDict_Impl();
}
