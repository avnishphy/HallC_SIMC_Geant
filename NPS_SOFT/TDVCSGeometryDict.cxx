// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDVCSGeometryDict
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
#include "TDVCSGeometry.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TDVCSGeometry(void *p = nullptr);
   static void *newArray_TDVCSGeometry(Long_t size, void *p);
   static void delete_TDVCSGeometry(void *p);
   static void deleteArray_TDVCSGeometry(void *p);
   static void destruct_TDVCSGeometry(void *p);
   static void streamer_TDVCSGeometry(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDVCSGeometry*)
   {
      ::TDVCSGeometry *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDVCSGeometry >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDVCSGeometry", ::TDVCSGeometry::Class_Version(), "TDVCSGeometry.h", 29,
                  typeid(::TDVCSGeometry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDVCSGeometry::Dictionary, isa_proxy, 16,
                  sizeof(::TDVCSGeometry) );
      instance.SetNew(&new_TDVCSGeometry);
      instance.SetNewArray(&newArray_TDVCSGeometry);
      instance.SetDelete(&delete_TDVCSGeometry);
      instance.SetDeleteArray(&deleteArray_TDVCSGeometry);
      instance.SetDestructor(&destruct_TDVCSGeometry);
      instance.SetStreamerFunc(&streamer_TDVCSGeometry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDVCSGeometry*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDVCSGeometry*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDVCSGeometry*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDVCSGeometry::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDVCSGeometry::Class_Name()
{
   return "TDVCSGeometry";
}

//______________________________________________________________________________
const char *TDVCSGeometry::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSGeometry*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDVCSGeometry::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSGeometry*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDVCSGeometry::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSGeometry*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDVCSGeometry::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSGeometry*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDVCSGeometry::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDVCSGeometry.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TDVCSGeometry::IsA());
   } else {
      R__c = R__b.WriteVersion(TDVCSGeometry::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TDVCSGeometry(void *p) {
      return  p ? new(p) ::TDVCSGeometry : new ::TDVCSGeometry;
   }
   static void *newArray_TDVCSGeometry(Long_t nElements, void *p) {
      return p ? new(p) ::TDVCSGeometry[nElements] : new ::TDVCSGeometry[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDVCSGeometry(void *p) {
      delete (static_cast<::TDVCSGeometry*>(p));
   }
   static void deleteArray_TDVCSGeometry(void *p) {
      delete [] (static_cast<::TDVCSGeometry*>(p));
   }
   static void destruct_TDVCSGeometry(void *p) {
      typedef ::TDVCSGeometry current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDVCSGeometry(TBuffer &buf, void *obj) {
      ((::TDVCSGeometry*)obj)->::TDVCSGeometry::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDVCSGeometry

namespace {
  void TriggerDictionaryInitialization_TDVCSGeometryDict_Impl() {
    static const char* headers[] = {
"TDVCSGeometry.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDVCSGeometryDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDVCSGeometry.h")))  TDVCSGeometry;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDVCSGeometryDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDVCSGeometry.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDVCSGeometry", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDVCSGeometryDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDVCSGeometryDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDVCSGeometryDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDVCSGeometryDict() {
  TriggerDictionaryInitialization_TDVCSGeometryDict_Impl();
}
