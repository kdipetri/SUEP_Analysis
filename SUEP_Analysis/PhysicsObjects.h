#ifndef physicsObjects_h
#define physicsObjects_h

// Structures for physics objects that don't require doHistos class 
// Useful for packing up n-tuple variables for a single muon
// Can loop through muons more easily to figure 

struct Jet {
  unsigned int index;
  TLorentzVector p4;
  bool id;
  int multiplicity;
  int chargedMultiplicity;
  float isolation;
  float scalar_dPhi;
  float scalar_dR;
  float min_dR;
};

struct JetAK8 {
  unsigned int index;
  TLorentzVector p4;
  bool id;
  int multiplicity;
  int chargedMultiplicity;
};

struct Track {
  unsigned int index;
  TLorentzVector p4;
  bool fromPV;
  bool highPurity;
  bool isPFcand;
};

#endif