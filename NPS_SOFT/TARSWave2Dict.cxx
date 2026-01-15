// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TARSWave2Dict
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
#include "TARSWave2.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TARSWave2(void *p = nullptr);
   static void *newArray_TARSWave2(Long_t size, void *p);
   static void delete_TARSWave2(void *p);
   static void deleteArray_TARSWave2(void *p);
   static void destruct_TARSWave2(void *p);
   static void streamer_TARSWave2(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TARSWave2*)
   {
      ::TARSWave2 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TARSWave2 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TARSWave2", ::TARSWave2::Class_Version(), "TARSWave2.h", 14,
                  typeid(::TARSWave2), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TARSWave2::Dictionary, isa_proxy, 16,
                  sizeof(::TARSWave2) );
      instance.SetNew(&new_TARSWave2);
      instance.SetNewArray(&newArray_TARSWave2);
      instance.SetDelete(&delete_TARSWave2);
      instance.SetDeleteArray(&deleteArray_TARSWave2);
      instance.SetDestructor(&destruct_TARSWave2);
      instance.SetStreamerFunc(&streamer_TARSWave2);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TARSWave2*)
   {
      return GenerateInitInstanceLocal(static_cast<::TARSWave2*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TARSWave2*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TARSWave2::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TARSWave2::Class_Name()
{
   return "TARSWave2";
}

//______________________________________________________________________________
const char *TARSWave2::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSWave2*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TARSWave2::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TARSWave2*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TARSWave2::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSWave2*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TARSWave2::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TARSWave2*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TARSWave2::Streamer(TBuffer &R__b)
{
   // Stream an object of class TARSWave2.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      delete [] refshape;
      refshape = new Double_t[128];
      R__b.ReadFastArray(refshape,128);
      delete [] shape;
      shape = new Double_t[128];
      R__b.ReadFastArray(shape,128);
      R__b >> fb;
      R__b >> fa1;
      R__b >> fa2;
      R__b >> ft1;
      R__b >> ft1n;
      R__b >> ft2;
      R__b >> ft2n;
      R__b >> fChan;
      R__b >> fRun;
      R__b.CheckByteCount(R__s, R__c, TARSWave2::IsA());
   } else {
      R__c = R__b.WriteVersion(TARSWave2::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.WriteFastArray(refshape,128);
      R__b.WriteFastArray(shape,128);
      R__b << fb;
      R__b << fa1;
      R__b << fa2;
      R__b << ft1;
      R__b << ft1n;
      R__b << ft2;
      R__b << ft2n;
      R__b << fChan;
      R__b << fRun;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TARSWave2(void *p) {
      return  p ? new(p) ::TARSWave2 : new ::TARSWave2;
   }
   static void *newArray_TARSWave2(Long_t nElements, void *p) {
      return p ? new(p) ::TARSWave2[nElements] : new ::TARSWave2[nElements];
   }
   // Wrapper around operator delete
   static void delete_TARSWave2(void *p) {
      delete (static_cast<::TARSWave2*>(p));
   }
   static void deleteArray_TARSWave2(void *p) {
      delete [] (static_cast<::TARSWave2*>(p));
   }
   static void destruct_TARSWave2(void *p) {
      typedef ::TARSWave2 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TARSWave2(TBuffer &buf, void *obj) {
      ((::TARSWave2*)obj)->::TARSWave2::Streamer(buf);
   }
} // end of namespace ROOT for class ::TARSWave2

namespace {
  void TriggerDictionaryInitialization_TARSWave2Dict_Impl() {
    static const char* headers[] = {
"TARSWave2.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TARSWave2Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TARSWave2.h")))  TARSWave2;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TARSWave2Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TARSWave2.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TARSWave2", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TARSWave2Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TARSWave2Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TARSWave2Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TARSWave2Dict() {
  TriggerDictionaryInitialization_TARSWave2Dict_Impl();
}
