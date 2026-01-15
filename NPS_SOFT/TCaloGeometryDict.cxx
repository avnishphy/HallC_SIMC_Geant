// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TCaloGeometryDict
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
#include "TCaloGeometry.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_TCaloGeometry(void *p = nullptr);
   static void *newArray_TCaloGeometry(Long_t size, void *p);
   static void delete_TCaloGeometry(void *p);
   static void deleteArray_TCaloGeometry(void *p);
   static void destruct_TCaloGeometry(void *p);
   static void streamer_TCaloGeometry(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCaloGeometry*)
   {
      ::TCaloGeometry *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TCaloGeometry >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TCaloGeometry", ::TCaloGeometry::Class_Version(), "TCaloGeometry.h", 27,
                  typeid(::TCaloGeometry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TCaloGeometry::Dictionary, isa_proxy, 16,
                  sizeof(::TCaloGeometry) );
      instance.SetNew(&new_TCaloGeometry);
      instance.SetNewArray(&newArray_TCaloGeometry);
      instance.SetDelete(&delete_TCaloGeometry);
      instance.SetDeleteArray(&deleteArray_TCaloGeometry);
      instance.SetDestructor(&destruct_TCaloGeometry);
      instance.SetStreamerFunc(&streamer_TCaloGeometry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCaloGeometry*)
   {
      return GenerateInitInstanceLocal(static_cast<::TCaloGeometry*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TCaloGeometry*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TCaloGeometry::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TCaloGeometry::Class_Name()
{
   return "TCaloGeometry";
}

//______________________________________________________________________________
const char *TCaloGeometry::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloGeometry*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TCaloGeometry::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TCaloGeometry*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TCaloGeometry::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloGeometry*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TCaloGeometry::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TCaloGeometry*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TCaloGeometry::Streamer(TBuffer &R__b)
{
   // Stream an object of class TCaloGeometry.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TCaloGeometry::IsA());
   } else {
      R__c = R__b.WriteVersion(TCaloGeometry::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCaloGeometry(void *p) {
      return  p ? new(p) ::TCaloGeometry : new ::TCaloGeometry;
   }
   static void *newArray_TCaloGeometry(Long_t nElements, void *p) {
      return p ? new(p) ::TCaloGeometry[nElements] : new ::TCaloGeometry[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCaloGeometry(void *p) {
      delete (static_cast<::TCaloGeometry*>(p));
   }
   static void deleteArray_TCaloGeometry(void *p) {
      delete [] (static_cast<::TCaloGeometry*>(p));
   }
   static void destruct_TCaloGeometry(void *p) {
      typedef ::TCaloGeometry current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TCaloGeometry(TBuffer &buf, void *obj) {
      ((::TCaloGeometry*)obj)->::TCaloGeometry::Streamer(buf);
   }
} // end of namespace ROOT for class ::TCaloGeometry

namespace {
  void TriggerDictionaryInitialization_TCaloGeometryDict_Impl() {
    static const char* headers[] = {
"TCaloGeometry.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TCaloGeometryDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TCaloGeometry.h")))  TCaloGeometry;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TCaloGeometryDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TCaloGeometry.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TCaloGeometry", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TCaloGeometryDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TCaloGeometryDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TCaloGeometryDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TCaloGeometryDict() {
  TriggerDictionaryInitialization_TCaloGeometryDict_Impl();
}
