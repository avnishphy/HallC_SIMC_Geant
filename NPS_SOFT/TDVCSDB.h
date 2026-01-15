//
// TDVCSDB.h, v1.0, Thu Mar  25 14:42:50
// Author: C. Munoz Camacho
//

#ifndef __TDVCSDB__
#define __TDVCSDB__

#ifndef ROOT_TObject
#include "TObject.h"
#endif

#ifndef ROOT_TSystem
#include "TSystem.h"
#endif

#ifndef ROOT_TString
#include "TString.h"
#endif

#ifndef ROOT_TSQLServer
#include "TSQLServer.h"
#endif

#ifndef ROOT_TSQLResult
#include "TSQLResult.h"
#endif

#ifndef ROOT_TSQLRow
#include "TSQLRow.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////
//
// TDVCSDB.h
//
// DVCS database class
// 
////////////////////////////////////////////////////////////////////////////////

class TDVCSDB : public TObject
{
  
  private :

    TSQLServer *fServer;
    TString fUser;
  
    void UpdateLatest(const char* name, const char*  username, const char*  date, const char*  shift, const char*  job);
    void ClearLatest(const char*  date, const char*  shift, const char*  job);

  public :

    TDVCSDB(const char*  db, const char*  host ,Int_t port, const char*  user);
    TDVCSDB(const char*  db, const char*  host, Int_t port, const char*  user, const char*  passwd);
    TDVCSDB(const char*  host ,Int_t port, const char*  user);
    TDVCSDB(const TDVCSDB&);
    virtual ~TDVCSDB();

    Int_t GetLastValueId(const char* nametable, Int_t run);
    Int_t CreateTable(const char*  nametable, const char*  type, Int_t number);

    //20190410(start)
    Int_t DeleteTable(const char*  nametable);
    //20190410(finish)
    
    Int_t AddEntry(const char* tablename, Int_t runmin, Int_t runmax, Int_t col, Double_t val, const char* comment=""); 
    Int_t AddEntry(const char* tablename, Int_t run, Int_t runmin, Int_t runmax, Int_t col, Double_t val, const char* comment=""); 
    Int_t AddEntry(const char* tablename, Int_t runmin, Int_t runmax, const char*  filename, const char* comment="");
    void AddEntry_f(const char* tablename, Int_t runmin, Int_t runmax, Float_t* val, const char* comment="");
    void AddEntry_d(const char* tablename, Int_t runmin, Int_t runmax, Double_t* val, const char* comment="");
    void AddEntry_i(const char* tablename, Int_t runmin, Int_t runmax, Int_t* val, const char* comment="");
    void AddEntry_s(const char* tablename, Int_t runmin, Int_t runmax, const char** val, const char* comment);
    Int_t AddOneEntry(const char* tablename, Int_t runmin, Int_t runmax, Double_t val, const char* comment="");
    Int_t CopyEntry(const char* tablename, Int_t run, Int_t runmin, Int_t runmax, const char* comment="");

    void AddShift(const char*  name, char * username, const char*  date, const char*  shift, const char*  job);
    void AddNewShift(const char*  date, const char*  shift, const char*  job);
    void ClearShift(const char*  date, const char*  shift, const char*  job);
    
    Double_t* GetEntry_d(const char* tablename, Int_t run);
    Float_t* GetEntry_f(const char* tablename, Int_t run);
    Int_t* GetEntry_i(const char* tablename, Int_t run);
    const char** GetEntry_s(const char* tablename, Int_t run);
    
    Double_t GetEntry_d(const char* tablename, Int_t run, Int_t col);
    Float_t GetEntry_f(const char* tablename, Int_t run, Int_t col);
    Int_t GetEntry_i(const char* tablename, Int_t run, Int_t col);
    TString GetEntry_c(const char* tablename, Int_t run, Int_t col);
    
    void GetEntry(const char* tablename, Int_t run, const char* filename);
    
    TSQLServer* GetServer(void) { return fServer ; }
    
    ClassDef(TDVCSDB,1) // DVCS DataBase Class
      
      }; // End of TDVCSDB class definition

#endif
      





