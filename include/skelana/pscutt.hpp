#pragma once

namespace skelana
{
/* +KEEP,PSCUTT.                  Track selection cuts
*
***********charged :
*     TRKMOM  -  min Track momentum in GeV
*     TRKMAX  -  max momentum in GeV
*     TRKERR  -  max dp/p 
*     TRKRPH  -  max Rphi impact parameter
*     TRKZET  -  max Z    impact parameter
*     TRKLEN  -  min Track length in cm.
*     TRCCOS  -  max COS (theta)  for charged tracks
*     VDONLY  -  reject VDONLY tracks
*             -  1- reject VD only without measued Z tracks
*             -  2- reject all VD only tracks
*
*     IDVDWZ  -  if >0, reject IDVD without Z tracks
*
*     IHADRJ - Hadron calorimeter noise rejection level 0-2
*                0 - Inactive
*                1 - reject most noisy clusters (tight tag)
*                2 - reject noisy clusters (loose or tight)
*
*     ISTOEL - Off momentum electrons rejection in STIC 0
*                0 - Inactive
*                1 - Active
*   
************recovery :
*                recover rejected charged tracks with
*     RECCAL  -  calorimeter deposits (GeV)
************neutral :
*                neutral cluster cuts :
*     EHPC    -  HPC   energy for neutral tracks  
*     EFEMC   -  FEMC  energy for neutral tracks
*     EHAC    -  EHAC  energy for neutral tracks
*     ESTIC   -  ESTIC energy for neutral tracks
*     TRNCOS  -  COS (theta)  for neutral tracks
*/
    inline const int NCUT = 3;
    extern "C" struct
    {
        float trkmom[NCUT];
        float trklen[NCUT];
        float trkrph[NCUT];
        float trkzet[NCUT];
        float trccos[NCUT];
        float trncos[NCUT];
        float trkmax[NCUT];
        float trkerr[NCUT];
        float reccal[NCUT];
        float ehpc[NCUT];
        float efemc[NCUT];
        float ehac[NCUT];
        float estic[NCUT];
        int vdonly[NCUT];
        int idvdwz[NCUT];
        int ihadrj[NCUT];
        int istoel[NCUT];
    } pscutt_;

    inline float &TRKMOM(int i) { return pscutt_.trkmom[i - 1]; }
    inline float &TRKLEN(int i) { return pscutt_.trklen[i - 1]; }
    inline float &TRKRPH(int i) { return pscutt_.trkrph[i - 1]; }
    inline float &TRKZET(int i) { return pscutt_.trkzet[i - 1]; }
    inline float &TRCCOS(int i) { return pscutt_.trccos[i - 1]; }
    inline float &TRNCOS(int i) { return pscutt_.trncos[i - 1]; }
    inline float &TRKMAX(int i) { return pscutt_.trkmax[i - 1]; }
    inline float &TRKERR(int i) { return pscutt_.trkerr[i - 1]; }
    inline float &RECCAL(int i) { return pscutt_.reccal[i - 1]; }
    inline float &EHPC(int i) { return pscutt_.ehpc[i - 1]; }
    inline float &EFEMC(int i) { return pscutt_.efemc[i - 1]; }
    inline float &EHAC(int i) { return pscutt_.ehac[i - 1]; }
    inline float &ESTIC(int i) { return pscutt_.estic[i - 1]; }
    inline int &VDONLY(int i) { return pscutt_.vdonly[i - 1]; }
    inline int &IDVDWZ(int i) { return pscutt_.idvdwz[i - 1]; }
    inline int &IHADRJ(int i) { return pscutt_.ihadrj[i - 1]; }
    inline int &ISTOEL(int i) { return pscutt_.istoel[i - 1]; }

} 
