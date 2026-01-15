#include "dvcsGlobals.hh"

// ---- Run info ----
int    dvcsGlobals::run_number = 0;

// ---- Beam & spectrometer ----
double dvcsGlobals::Ebeam         = 0.0;  // GeV
double dvcsGlobals::HMS_angle     = 0.0;  // radians
double dvcsGlobals::HMS_momentum  = 0.0;  // GeV

// ---- Calorimeter ----
double dvcsGlobals::Calo_distance = 0.0;  // cm or m (match geometry)
double dvcsGlobals::Calo_angle    = 0.0;  // radians

// ---- Target ----
int    dvcsGlobals::target_type           = 0;
int    dvcsGlobals::target_gen_proc_type  = 0;
double dvcsGlobals::target_density        = 0.0;
double dvcsGlobals::target_offset         = 0.0;
double dvcsGlobals::target_length         = 0.0;

// ---- Flags ----
bool   dvcsGlobals::hit_HMS_CALO_flag = false;

// ---- Sweeping magnet ----
bool   dvcsGlobals::SM_field_flag = false;
double dvcsGlobals::SM_field_str  = 0.0;
double dvcsGlobals::SM_angle      = 0.0;
