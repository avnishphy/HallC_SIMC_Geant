// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TDVCSGlobalDict
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
#include "TDVCSGlobal.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *TDVCSGlobal_Dictionary();
   static void TDVCSGlobal_TClassManip(TClass*);
   static void delete_TDVCSGlobal(void *p);
   static void deleteArray_TDVCSGlobal(void *p);
   static void destruct_TDVCSGlobal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDVCSGlobal*)
   {
      ::TDVCSGlobal *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TDVCSGlobal));
      static ::ROOT::TGenericClassInfo 
         instance("TDVCSGlobal", "TDVCSGlobal.h", 14,
                  typeid(::TDVCSGlobal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TDVCSGlobal_Dictionary, isa_proxy, 0,
                  sizeof(::TDVCSGlobal) );
      instance.SetDelete(&delete_TDVCSGlobal);
      instance.SetDeleteArray(&deleteArray_TDVCSGlobal);
      instance.SetDestructor(&destruct_TDVCSGlobal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDVCSGlobal*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDVCSGlobal*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDVCSGlobal*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TDVCSGlobal_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::TDVCSGlobal*>(nullptr))->GetClass();
      TDVCSGlobal_TClassManip(theClass);
   return theClass;
   }

   static void TDVCSGlobal_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TDVCSGlobal(void *p) {
      delete (static_cast<::TDVCSGlobal*>(p));
   }
   static void deleteArray_TDVCSGlobal(void *p) {
      delete [] (static_cast<::TDVCSGlobal*>(p));
   }
   static void destruct_TDVCSGlobal(void *p) {
      typedef ::TDVCSGlobal current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TDVCSGlobal

namespace {
  void TriggerDictionaryInitialization_TDVCSGlobalDict_Impl() {
    static const char* headers[] = {
"TDVCSGlobal.h",
nullptr
    };
    static const char* includePaths[] = {
"/u/group/halla/apps/ROOT/6.30-04/el9/RelWithDebInfo/include/",
"/w/hallc-scshelf2102/nps/singhav/geant4_simc/NPS_SOFT/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TDVCSGlobalDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$TDVCSGlobal.h")))  TDVCSGlobal;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TDVCSGlobalDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TDVCSGlobal.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDVCSGlobal", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TDVCSGlobalDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TDVCSGlobalDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TDVCSGlobalDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TDVCSGlobalDict() {
  TriggerDictionaryInitialization_TDVCSGlobalDict_Impl();
}
