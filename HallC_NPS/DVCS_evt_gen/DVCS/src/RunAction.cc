#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RunAction::RunAction(HistoManager* histo, G4String fileName, G4int n, long i, long j)
  : G4UserRunAction(),
    fHistoManager(histo),
    fFileName(fileName),
    fSumEAbs(0.), fSum2EAbs(0.),
    fSumEGap(0.), fSum2EGap(0.),
    fSumLAbs(0.), fSum2LAbs(0.),
    fSumLGap(0.), fSum2LGap(0.),
    fIndex(n), fIndex2(n),
    fSeed1(i), fSeed2(j), fSeed3(i)
{
  // Initialize arrays safely
  for (int idx = 0; idx < 1080; ++idx) {
      fEdep[idx] = 0.0;
      fPID[idx] = 0;
      fOP_sc[idx] = 0;
      fOP_ce[idx] = 0;
      fOP_cover[idx] = 0;
      fOP_frontcover[idx] = 0;
      fOP_pmtcover[idx] = 0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4int index = fIndex2;
  long seeds[2];
  seeds[0] = fSeed3;
  seeds[1] = fSeed2;
  G4Random::setTheSeeds(seeds, index);
  G4Random::showEngineStatus();

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  // initialize cumulative quantities
  fSumEAbs = fSum2EAbs = fSumEGap = fSum2EGap = 0.;
  fSumLAbs = fSum2LAbs = fSumLGap = fSum2LGap = 0.;

  // NOTE: in main() the HistoManager::Book(...) is already invoked before creating
  // RunAction. To avoid reopening the output file here, do not call Book() again.
  // If you wish RunAction to handle booking, call Book only here and remove earlier call.
  // fHistoManager->Book(fFileName);  // <<--- intentionally omitted to avoid double-open
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::fillPerEvent(G4double EAbs, G4double EGap,
                                  G4double LAbs, G4double LGap)
{
  // accumulate statistic
  fSumEAbs += EAbs;  fSum2EAbs += EAbs*EAbs;
  fSumEGap += EGap;  fSum2EGap += EGap*EGap;

  fSumLAbs += LAbs;  fSum2LAbs += LAbs*LAbs;
  fSumLGap += LGap;  fSum2LGap += LGap*LGap;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........

void RunAction::AddEdepPerEvent(G4int id, G4int pid, G4double edep, G4int sc, G4int ce, G4int opc, G4int opfc, G4int oppc)
{
  // Add edep per each crystal for whole run (all the events)
  if (id >= 0 && id < 1080) {
      fEdep[id] += edep;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;

  // compute statistics: mean and rms
  fSumEAbs /= NbOfEvents; fSum2EAbs /= NbOfEvents;
  G4double rmsEAbs = fSum2EAbs - fSumEAbs*fSumEAbs;
  if (rmsEAbs > 0.) rmsEAbs = std::sqrt(rmsEAbs); else rmsEAbs = 0.;

  fSumEGap /= NbOfEvents; fSum2EGap /= NbOfEvents;
  G4double rmsEGap = fSum2EGap - fSumEGap*fSumEGap;
  if (rmsEGap > 0.) rmsEGap = std::sqrt(rmsEGap); else rmsEGap = 0.;

  fSumLAbs /= NbOfEvents; fSum2LAbs /= NbOfEvents;
  G4double rmsLAbs = fSum2LAbs - fSumLAbs*fSumLAbs;
  if (rmsLAbs > 0.) rmsLAbs = std::sqrt(rmsLAbs); else rmsLAbs = 0.;

  fSumLGap /= NbOfEvents; fSum2LGap /= NbOfEvents;
  G4double rmsLGap = fSum2LGap - fSumLGap*fSumLGap;
  if (rmsLGap > 0.) rmsLGap = std::sqrt(rmsLGap); else rmsLGap = 0.;

  // save histograms
  if (fHistoManager) fHistoManager->Save();
}
