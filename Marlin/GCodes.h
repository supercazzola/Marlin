/**
 * GCodes.h - Contains codes for Gcodes.
 * Author: Dan Thompson (danthompson41@gmail.com)
 * Date: 4/8/2016
 * Used as the home for Gcodes, to decouple them from Marlin_main.
 * Note on the weirdness of having the definitions in an h file: This is to
 * facilitate the inline functions. Inline is only file specific, so doesn't
 * work if you count on the linker (ex, using the normal .cpp with an h file
 * interface). Directly including the code in an H file is the easiest way to
 * do this.
 * Adapted from Dan Thompson's work at Voxel8
 */

#ifndef G_CODES_H_
#define G_CODES_H_

#include "Marlin.h"
#include "GCodeUtility.h"
#include "planner.h"

//===========================================================================
//================================ GCode List ===============================
//===========================================================================

/**
 * Look here for descriptions of G-codes:
 *  - http://linuxcnc.org/handbook/gcode/g-code.html
 *  - http://objects.reprap.org/wiki/Mendel_User_Manual:_RepRapGCodes
 *
 *
 * -----------------
 * Implemented Codes
 * -----------------
 *
 * "M" Codes
 *
 * M248 - Queries the thermistor of the heated bed to see if it is connected.
 *        Protects from homing when bed is not attached, useful for protecting
 *        the printer from starting a print job without the bed attached.
*/

//===========================================================================
//============================= Public Functions ============================
//===========================================================================

/*
* M248 - Enable / Disable Protections
*   S - 1       1 = Heated Bed Check
*   E - 0 - 1   1 = Enable, 0 = Disable
*/
inline void gcode_M248() {
  // Used to see if we've been given arguments, and to warn you through the
  // serial port if they're not seen.
  bool hasS;
  bool hasE;

  if (hasS = code_seen('S')) {
    switch(int(code_value())) {
      case 1:
      // Heated Bed Check
        if (hasE = code_seen('E')) {
          switch(int(code_value())) {
            case 0:
              HeatedBed__SetPresentCheck(false);
              break;
            case 1:
              HeatedBed__SetPresentCheck(true);
              break;
            default:
              SERIAL_PROTOCOLLNPGM("(E1) or (E0) not given");
              return;
          }
        }
        break;

      default:
        SERIAL_PROTOCOLLNPGM(
            "Invalid S argument: S1 = HeatedBed");
        return;
    }
  }

  if (!hasS) {
    SERIAL_PROTOCOLLNPGM(
        "No S argument given: S1 = HeatedBed);
    }
    if (!hasE) {
      SERIAL_PROTOCOLLNPGM("(E1) or (E0) not given");
    }
}

#endif  // G_CODES_H_