# HallC_NPS

Hall_C NPS Geant4 Simulation 

For Hall C DVCS (DVCS_evt_gen/), see https://wiki.jlab.org/cuawiki/images/f/fa/User_Guide.pdf for a short description on how to run on JLab/ifarm

Visualization macro workflow (all maintained variants):
- `vis_setup.mac`: setup only
- `vis_single.mac`: setup + one event
- `vis_sequential.mac`: setup + one-by-one stepping guidance
- `vis.mac`: backward-compatible alias to `vis_setup.mac`
