C***********************************************************************
C*                                                                     *
C*  ZEBRA POINTER TRACKING COMMON BLOCK                                *
C*                                                                     *
C*  This file contains the FORTRAN common block and initialization     *
C*  routine for tracking ZebraPointer objects used by the C++          *
C*  ZebraPointer class. The common block provides a registry where     *
C*  all Zebra links referenced by ZebraPointer instances are stored    *
C*  and properly declared to the Zebra memory management system.       *
C*                                                                     *
C*  The ZebraPointer C++ class stores only an index into this          *
C*  registry rather than the actual Zebra link, reducing memory        *
C*  overhead and ensuring proper Zebra link management.                *
C*                                                                     *
C*  Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>                   *
C*  Date: October 2025                                                 *
C*                                                                     *
C***********************************************************************

        SUBROUTINE ZEBPTRINI
C
C  Purpose: Initialize the ZebraPointer tracking system
C
C  This subroutine initializes the ZEBRA link area that tracks all
C  Zebra pointers referenced by C++ ZebraPointer objects. The link
C  area is declared to Zebra using MZLINK to ensure proper memory
C  management and garbage collection.
C
C  The common block /ZEBLLL/ contains:
C    LZEBPTR - Array of Zebra links tracked by ZebraPointer instances
C    MXZEBPTR - Maximum number of trackable ZebraPointer links
C
C  This initialization must be called before using any ZebraPointer
C  objects to ensure the Zebra system properly tracks the links.
C
        IMPLICIT NONE
        
C  Maximum number of ZebraPointer links that can be tracked
        INTEGER MXZEBPTR
        PARAMETER ( MXZEBPTR = 1000)
        
C  Array to store Zebra links referenced by ZebraPointer objects
        INTEGER LZEBPTR
        
C***********************************************************************
C*  COMMON BLOCK /ZEBLLL/ - ZebraPointer Link Registry                 *
C*                                                                     *
C*  This common block serves as a centralized registry for all Zebra   *
C*  links that are referenced by C++ ZebraPointer instances. By        *
C*  declaring this area to Zebra using MZLINK, we ensure that:         *
C*                                                                     *
C*  1. All tracked links are properly known to the Zebra system        *
C*  2. Zebra's garbage collection will not accidentally free           *
C*     referenced memory                                               *
C*  3. The ZebraPointer registry remains consistent with Zebra's       *
C*     internal memory management                                      *
C*                                                                     *
C*  The C++ ZebraPointer class accesses this common block through      *
C*  extern "C" declarations to maintain the registry.                  *
C***********************************************************************
        COMMON/ZEBLLL/LZEBPTR(MXZEBPTR)
        
C  Declare the link area to Zebra memory management system
C  This ensures Zebra knows about all links stored in LZEBPTR
        CALL MZLINK(0,'/ZEBLLL/',LZEBPTR,LZEBPTR,LZEBPTR(MXZEBPTR))
        
        END