#ifndef EgammaTools_ConversionFinder_h
#define EgammaTools_ConversionFinder_h
/** \class reco::ConversionFinder ConversionFinder.h RecoEgamma/EgammaTools/interface/ConversionFinder.h
  *  
  * Conversion finding and rejection code 
  * Uses simple geometric methods to determine whether or not the 
  * electron did indeed come from a conversion
  * \author Puneeth Kalavase, University Of California, Santa Barbara
  *
  * \version $Id: ConversionFinder.h,v 1.7 2010/04/13 19:32:13 kalavase Exp $
  *
  */

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Math/VectorUtil.h"
#include "ConversionInfo.h"



/* 
   Class Looks for oppositely charged track in the 
   track collection with the minimum delta cot(theta) between the track
   and the electron's CTF track (if it doesn't exist, we use the electron's
   GSF track). Calculate the dist, dcot, point of conversion and the 
   radius of conversion for this pair and fill the ConversionInfo
*/

class ConversionFinder {    
 public:
  ConversionFinder();
  ~ConversionFinder();
  //bField has to be supplied in Tesla
  ConversionInfo getConversionInfo(const reco::GsfElectron& gsfElectron, 
				   const edm::Handle<reco::TrackCollection>& ctftracks_h, 
				   const edm::Handle<reco::GsfTrackCollection>& gsftracks_h,
				   const double bFieldAtOrigin,
				   const double minFracSharedHits = 0.45);
  
  ConversionInfo getConversionInfo(const reco::Track *el_track, 
				   const reco::Track *candPartnerTk,
				   const double bFieldAtOrigin);	

  const reco::Track* getElectronTrack(const reco::GsfElectron& electron, const float minFracSharedHits = 0.45);

  
  //takes in a vector of candidate conversion partners
  //and arbitrates between them returning the one with the 
  //smallest R=sqrt(dist*dist + dcot*dcot)
  ConversionInfo arbitrateConversionPartners(const std::vector<ConversionInfo>& v_convCandidates);
  //function below is only for backwards compatibility 
  static std::pair<double, double> getConversionInfo(math::XYZTLorentzVector trk1_p4, 
						     int trk1_q, float trk1_d0, 
						     math::XYZTLorentzVector trk2_p4,
						     int trk2_q, float trk2_d0,
						     float bFieldAtOrigin);

  //for backwards compatibility. Does not use the GSF track collection. This function will be 
  //deprecated soon
  ConversionInfo getConversionInfo(const reco::GsfElectron& gsfElectron,
				   const edm::Handle<reco::TrackCollection>& track_h, 
				   const double bFieldAtOrigin,
				   const double minFracSharedHits = 0.45);


 private:
  ConversionInfo convInfo_;
};
#endif
