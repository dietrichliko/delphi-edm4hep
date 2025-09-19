#pragma once

namespace skelana
{
/*+KEEP,PSCRNQ.              Run Quality file information
*
*     Fill characteristics from the RQ files :
*
*     NRQFIL         - Total   number of fills
*     MRQFIL         - Maximum number of fills
*     IRQFIL(MRQFIL) - LEP number of the fills
*     ERQFIL(MRQFIL) - LEP energy of the fills
*
*     DELPHI detector/trigger status summary :
*
*     NRQDET         - Number of detectors in the RQ files
*     NRQTRG         - Number of triggers  in the RQ files
*     NRQT9X         - Number of triggers  after  1990
*     NRQT90         - Number of triggers  during 1990
*     IRQDMN(NRQDET) - Minimum status level for the detectors (1-31)
*     IRQDMX(NRQDET) - Maximum status level for the detectors (1-31)
*     IRQTMN(NRQTRG) - Minimum status level for the triggers  (1-23)
*     IRQTMX(NRQTRG) - Maximum status level for the triggers  (1-23)
*
*     IRQDET( 1)     - MVX_A   detector run quality
*     IRQDET( 2)     - MVX_C   detector run quality
*     IRQDET( 3)     - ID_JET  detector run quality
*     IRQDET( 4)     - ID_TRIG detector run quality
*     IRQDET( 5)     - TPC_0   detector run quality
*     IRQDET( 6)     - TPC_1   detector run quality
*     IRQDET( 7)     - BRICH_L detector run quality
*     IRQDET( 8)     - BRICH_G detector run quality
*     IRQDET( 9)     - OD_B    detector run quality
*     IRQDET(10)     - OD_D    detector run quality
*     IRQDET(11)     - HPC_0   detector run quality
*     IRQDET(12)     - HPC_1   detector run quality
*     IRQDET(13)     - HCAB_A  detector run quality
*     IRQDET(14)     - HCAB_C  detector run quality
*     IRQDET(15)     - MUB_B   detector run quality
*     IRQDET(16)     - MUB_B   detector run quality
*     IRQDET(17)     - FCA_A   detector run quality
*     IRQDET(18)     - FCA_C   detector run quality
*     IRQDET(19)     - RIF_A   detector run quality
*     IRQDET(20)     - RIF_C   detector run quality
*     IRQDET(21)     - FCB_A   detector run quality
*     IRQDET(22)     - FCB_C   detector run quality
*     IRQDET(23)     - EMF_A   detector run quality
*     IRQDET(24)     - EMF_C   detector run quality
*     IRQDET(25)     - HCAF_A  detector run quality
*     IRQDET(26)     - HCAF_C  detector run quality
*     IRQDET(27)     - MUF_A   detector run quality
*     IRQDET(28)     - MUF_C   detector run quality
*     IRQDET(29)     - SAT_CAL detector run quality
*     IRQDET(30)     - SAT_TRA detector run quality
*     IRQDET(31)     - VSAT    detector run quality
*
*                                      after 1990 :
*     IRQTRG( 1)     - TRIG_T1 trigger  run quality
*     IRQTRG( 2)     - TRIG_T2 trigger  run quality
*     IRQTRG( 3)     - B1_OR   trigger  run quality
*     IRQTRG( 4)     - B1_FW   trigger  run quality
*     IRQTRG( 5)     - PYT_SA  trigger  run quality
*     IRQTRG( 6)     - PYT_BM2 trigger  run quality
*     IRQTRG( 7)     - PYT_FM2 trigger  run quality
*     IRQTRG( 8)     - PYT_BMJ trigger  run quality
*     IRQTRG( 9)     - PYT_FMJ trigger  run quality
*     IRQTRG(10)     - SAT     trigger  run quality
*     IRQTRG(11)     - VSAT    trigger  run quality
*
*                                     during 1990 :
*     IRQTRG(12)     - ID      trigger  run quality
*     IRQTRG(13)     - OD      trigger  run quality
*     IRQTRG(14)     - HPC     trigger  run quality
*     IRQTRG(15)     - TOF     trigger  run quality
*     IRQTRG(16)     - FCA_A   trigger  run quality
*     IRQTRG(17)     - FCA_C   trigger  run quality
*     IRQTRG(18)     - FCB_A   trigger  run quality
*     IRQTRG(19)     - FCB_C   trigger  run quality
*     IRQTRG(20)     - EMF_A   trigger  run quality
*     IRQTRG(21)     - EMF_C   trigger  run quality
*     IRQTRG(22)     - HOF     trigger  run quality
*     IRQTRG(23)     - SAT     trigger  run quality
*
*     List of selected (rejected) run sets
*
*     NSRUNS         - Total   number of selected run sets
*     MSRUNS         - Maximum number of selected run sets
*     IFRUNS(MSRUNS) - First run of the selected  run sets
*     ILRUNS(MSRUNS) - Last  run of the selected  run sets
*     IFFILE(MSRUNS) - File number of the IFRUNS
*     ILFILE(MSRUNS) - File number of the ILRUNS
*/
    inline const int MRQFIL = 5000;
    inline const int NRQDET = 38;
    inline const int NRQTRG = 23;
    inline const int MSRUNS = 3000;
    extern "C" struct
    {
        int nrqfil;
        int irqfil[MRQFIL];
        float erqfil[MRQFIL];
        int irqdmn[NRQDET];
        int irqdmx[NRQDET];
        int irqtmn[NRQTRG];
        int irqtmx[NRQTRG];
        int irqdet[NRQDET];
        int irqtrg[NRQDET];
        int nsruns;
        int ifruns[MSRUNS];
        int ilruns[MSRUNS];
        int iffile[MSRUNS];
        int ilfile[MSRUNS];
    } pscrnq_;

    inline const int MEVBAD = 50000;
    extern "C" struct
    {
        int nevbad;
        int irnbad[MEVBAD];
        int ievbad[MEVBAD];
    } pscbhp_;

    inline int &NRQFIL = pscrnq_.nrqfil;
    inline int &IRQFIL(int i) { return pscrnq_.irqfil[i - 1]; }
    inline float &ERQFIL(int i) { return pscrnq_.erqfil[i - 1]; }
    inline int &IRQDMN(int i) { return pscrnq_.irqdmn[i - 1]; }
    inline int &IRQDMX(int i) { return pscrnq_.irqdmx[i - 1]; }
    inline int &IRQTMN(int i) { return pscrnq_.irqtmn[i - 1]; }
    inline int &IRQTMX(int i) { return pscrnq_.irqtmx[i - 1]; }
    inline int &IRQDET(int i) { return pscrnq_.irqdet[i - 1]; }
    inline int &IRQTRG(int i) { return pscrnq_.irqtrg[i - 1]; }
    inline int &NSRUNS = pscrnq_.nsruns;
    inline int &IFRUNS(int i) { return pscrnq_.ifruns[i - 1]; }
    inline int &ILRUNS(int i) { return pscrnq_.ilruns[i - 1]; }
    inline int &IFFILE(int i) { return pscrnq_.iffile[i - 1]; }
    inline int &ILFILE(int i) { return pscrnq_.ilfile[i - 1]; }

    inline int &NEVBAD = pscbhp_.nevbad;
    inline int &IRNBAD(int i) { return pscbhp_.irnbad[i - 1]; }
    inline int &IEVBAD(int i) { return pscbhp_.ievbad[i - 1]; }

} // namespace skelana   