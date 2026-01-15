// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME THaEpicsStackDict
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
#include "THaEpicsStack.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_THaEpicsStack(void *p = nullptr);
   static void *newArray_THaEpicsStack(Long_t size, void *p);
   static void delete_THaEpicsStack(void *p);
   static void deleteArray_THaEpicsStack(void *p);
   static void destruct_THaEpicsStack(void *p);
   static void streamer_THaEpicsStack(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::THaEpicsStack*)
   {
      ::THaEpicsStack *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::THaEpicsStack >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("THaEpicsStack", ::THaEpicsStack::Class_Version(), "THaEpicsStack.h", 27,
                  typeid(::THaEpicsStack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::THaEpicsStack::Dictionary, isa_proxy, 16,
                  sizeof(::THaEpicsStack) );
      instance.SetNew(&new_THaEpicsStack);
      instance.SetNewArray(&newArray_THaEpicsStack);
      instance.SetDelete(&delete_THaEpicsStack);
      instance.SetDeleteArray(&deleteArray_THaEpicsStack);
      instance.SetDestructor(&destruct_THaEpicsStack);
      instance.SetStreamerFunc(&streamer_THaEpicsStack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::THaEpicsStack*)
   {
      return GenerateInitInstanceLocal(static_cast<::THaEpicsStack*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::THaEpicsStack*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr THaEpicsStack::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *THaEpicsStack::Class_Name()
{
   return "THaEpicsStack";
}

//______________________________________________________________________________
const char *THaEpicsStack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::THaEpicsStack*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int THaEpicsStack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::THaEpicsStack*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *THaEpicsStack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::THaEpicsStack*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *THaEpicsStack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::THaEpicsStack*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void THaEpicsStack::Streamer(TBuffer &R__b)
{
   // Stream an object of class THaEpicsStack.

   ::Error("THaEpicsStack::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_THaEpicsStack(void *p) {
      return  p ? new(p) ::THaEpicsStack : new ::THaEpicsStack;
   }
   static void *newArray_THaEpicsStack(Long_t nElements, void *p) {
      return p ? new(p) ::THaEpicsStack[nElements] : new ::THaEpicsStack[nElements];
   }
   // Wrapper around operator delete
   static void delete_THaEpicsStack(void *p) {
      delete (static_cast<::THaEpicsStack*>(p));
   }
   static void deleteArray_THaEpicsStack(void *p) {
      delete [] (static_cast<::THaEpicsStack*>(p));
   }
   static void destruct_THaEpicsStack(void *p) {
      typedef ::THaEpicsStack current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_THaEpicsStack(TBuffer &buf, void *obj) {
      ((::THaEpicsStack*)obj)->::THaEpicsStack::Streamer(buf);
   }
} // end of namespace ROOT for class ::THaEpicsStack

namespace {
  void TriggerDictionaryInitialization_THaEpicsStackDict_Impl() {
    static const char* headers[] = {
"THaEpicsStack.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "THaEpicsStackDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$THaEpicsStack.h")))  THaEpicsStack;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "THaEpicsStackDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "THaEpicsStack.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"THaEpicsStack", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("THaEpicsStackDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_THaEpicsStackDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_THaEpicsStackDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_THaEpicsStackDict() {
  TriggerDictionaryInitialization_THaEpicsStackDict_Impl();
}
