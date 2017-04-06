//
// cOrbit.h
//
// This is the header file for the class cOrbit. This class accepts a
// single satellite's NORAD two-line element set and provides information 
// regarding the satellite's orbit such as period, axis length,
// ECI coordinates/velocity, etc., using the SGP4/SDP4 orbital models.
// 
// Copyright (c) 2002-2009 Michael F. Henry
//
// mfh 01/02/2009
//
#pragma once

#include "cTle.h"
#include "cJulian.h"
#include "cNoradBase.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////////////

class cVector;
class cGeoCoord;
class cEci;

//////////////////////////////////////////////////////////////////////////////
class cOrbit  
{
public:
   cOrbit(const cTle &tle);
   virtual ~cOrbit();

   // Return satellite ECI data at given minutes since element's epoch.
   bool getPosition(double tsince, cEci *pEci) const;
   
   double Inclination()  const { return radGet(cTle::FLD_I);                 }
   double Eccentricity() const { return m_tle.getField(cTle::FLD_E);         }
   double RAAN()         const { return radGet(cTle::FLD_RAAN);              }
   double ArgPerigee()   const { return radGet(cTle::FLD_ARGPER);            }
   double BStar()        const { return m_tle.getField(cTle::FLD_BSTAR) / AE;}
   double Drag()         const { return m_tle.getField(cTle::FLD_MMOTIONDT); }
   double mnMotion()     const { return m_tle.getField(cTle::FLD_MMOTION);   }
   double mnAnomaly()    const { return radGet(cTle::FLD_M);                 }
   double mnAnomaly(cJulian t) const;  // mean anomaly (in radians) at time t

   cJulian Epoch() const { return m_jdEpoch; }

   double TPlusEpoch(const cJulian &t) const;    // time span [t - epoch] in secs

   std::string SatName(bool fAppendId = false) const;
   std::string SatId() const;

   
   // "Recovered" from the input elements
   double SemiMajor()  const { return m_aeAxisSemiMajorRec; }
   double SemiMinor()  const { return m_aeAxisSemiMinorRec; }
   double MeanMotion() const { return m_rmMeanMotionRec;    }  // mean motion, rads/min
   double Major()      const { return 2.0 * SemiMajor();    }  // major axis in AE
   double Minor()      const { return 2.0 * SemiMinor();    }  // minor axis in AE
   double Perigee()    const { return m_kmPerigeeRec;       }  // perigee in km
   double Apogee()     const { return m_kmApogeeRec;        }  // apogee in km
   double Period()     const;                                  // period in seconds

protected:
   double radGet(cTle::eField fld) const
      { return m_tle.getField(fld, cTle::U_RAD); }

   double degGet(cTle::eField fld) const
      { return m_tle.getField(fld, cTle::U_DEG); }

private:
   cTle        m_tle;
   cJulian     m_jdEpoch;
   cNoradBase *m_pNoradModel;

   // Caching variables; note units are not necessarily the same as tle units
   mutable double m_secPeriod;

   // Caching variables recovered from the input TLE elements
   double m_aeAxisSemiMajorRec;  // semimajor axis, in AE units
   double m_aeAxisSemiMinorRec;  // semiminor axis, in AE units
   double m_rmMeanMotionRec;     // radians per minute
   double m_kmPerigeeRec;        // perigee, in km
   double m_kmApogeeRec;         // apogee, in km
};

