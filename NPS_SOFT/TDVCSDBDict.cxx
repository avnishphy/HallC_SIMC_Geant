// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDVCSDBDict
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
#include "TDVCSDB.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void delete_TDVCSDB(void *p);
   static void deleteArray_TDVCSDB(void *p);
   static void destruct_TDVCSDB(void *p);
   static void streamer_TDVCSDB(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDVCSDB*)
   {
      ::TDVCSDB *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDVCSDB >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDVCSDB", ::TDVCSDB::Class_Version(), "TDVCSDB.h", 45,
                  typeid(::TDVCSDB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDVCSDB::Dictionary, isa_proxy, 16,
                  sizeof(::TDVCSDB) );
      instance.SetDelete(&delete_TDVCSDB);
      instance.SetDeleteArray(&deleteArray_TDVCSDB);
      instance.SetDestructor(&destruct_TDVCSDB);
      instance.SetStreamerFunc(&streamer_TDVCSDB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDVCSDB*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDVCSDB*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDVCSDB*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDVCSDB::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDVCSDB::Class_Name()
{
   return "TDVCSDB";
}

//______________________________________________________________________________
const char *TDVCSDB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSDB*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDVCSDB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDVCSDB*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDVCSDB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSDB*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDVCSDB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDVCSDB*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDVCSDB::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDVCSDB.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fServer;
      fUser.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TDVCSDB::IsA());
   } else {
      R__c = R__b.WriteVersion(TDVCSDB::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fServer;
      fUser.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TDVCSDB(void *p) {
      delete (static_cast<::TDVCSDB*>(p));
   }
   static void deleteArray_TDVCSDB(void *p) {
      delete [] (static_cast<::TDVCSDB*>(p));
   }
   static void destruct_TDVCSDB(void *p) {
      typedef ::TDVCSDB current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDVCSDB(TBuffer &buf, void *obj) {
      ((::TDVCSDB*)obj)->::TDVCSDB::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDVCSDB

namespace {
  void TriggerDictionaryInitialization_TDVCSDBDict_Impl() {
    static const char* headers[] = {
"TDVCSDB.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDVCSDBDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDVCSDB.h")))  TDVCSDB;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDVCSDBDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDVCSDB.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDVCSDB", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDVCSDBDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDVCSDBDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDVCSDBDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDVCSDBDict() {
  TriggerDictionaryInitialization_TDVCSDBDict_Impl();
}
