//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 16 14:22:03 2020 by ROOT version 6.14/09
// from TTree PreSelection/PreSelection
// found on file: root://cmseos.fnal.gov//store/user/kdipetri/SUEP/Production_v0.2/2018/NTUP/PrivateSamples.SUEP_2018_mMed-1000_mDark-2_temp-2_decay-darkPhoHad_13TeV-pythia8_n-100_0_RA2AnalysisTree.root
//////////////////////////////////////////////////////////
//
#ifndef doHistos_h
#define doHistos_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TMatrixDSym.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include "Math/GenVector/Cartesian3D.h" 
#include "Math/GenVector/PositionVector3D.h" 
#include "Math/GenVector/DisplacementVector3D.h" 
#include "SUEP_Analysis/PlotHelper.h"
#include "SUEP_Analysis/PhysicsObjects.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
// not included in cmssw - needs extra setup
//#include "fastjet/contrib/VariableRPlugin.hh"
#include "Math/GenVector/PtEtaPhiE4D.h"

// Setup plotter
PlotHelper plotter("");//set up the plotter
TCanvas *c1 = new TCanvas("c1","c1",800,800);

// Helpful variables
TLorentzVector scalar;
int npfs=0;
int npfs_09=0;
int npfs_08=0;
int npfs_07=0;
int npfs_2=0;
int njets=0;
float ht=0;
float lead_jet_pt=0;


class doHistos {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
// may need to increase these
// set to accomodate 1 TeV darkPhoHad signal 10k events
   static constexpr Int_t kMaxElectrons = 20;
   static constexpr Int_t kMaxGenJets = 80;
   static constexpr Int_t kMaxGenJetsAK8 = 20;
   static constexpr Int_t kMaxGenParticles = 7000;
   static constexpr Int_t kMaxGenVertices = 300;
   static constexpr Int_t kMaxJets = 100;
   static constexpr Int_t kMaxJetsAK8 = 20;
   static constexpr Int_t kMaxJetsAK8_subjets = 20;
   static constexpr Int_t kMaxMuons = 20;
   static constexpr Int_t kMaxPrimaryVertices = 150;
   static constexpr Int_t kMaxTracks = 2500;
   static constexpr Int_t kMaxTracks_referencePoint = 2500;

   // Declaration of leaf types
   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   ULong64_t       EvtNum;
   Bool_t          BadChargedCandidateFilter;
   Bool_t          BadPFMuonFilter;
   Int_t           BTags;
   Int_t           BTagsDeepCSV;
   Double_t        CaloMET;
   Double_t        CaloMETPhi;
   Double_t        CrossSection;
   Int_t           CSCTightHaloFilter;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi3;
   Double_t        DeltaPhi4;
   Int_t           ecalBadCalibFilter;
   Bool_t          ecalBadCalibReducedExtraFilter;
   Bool_t          ecalBadCalibReducedFilter;
   Int_t           EcalDeadCellBoundaryEnergyFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   Int_t           Electrons_;
   Double_t        Electrons_fCoordinates_fPt[kMaxElectrons];   //[Electrons_]
   Double_t        Electrons_fCoordinates_fEta[kMaxElectrons];   //[Electrons_]
   Double_t        Electrons_fCoordinates_fPhi[kMaxElectrons];   //[Electrons_]
   Double_t        Electrons_fCoordinates_fE[kMaxElectrons];   //[Electrons_]
   vector<int>     *Electrons_charge;
   vector<bool>    *Electrons_passIso;
   Double_t        fixedGridRhoFastjetAll;
   Double_t        GenHT;
   Int_t           GenJets_;
   Double_t        GenJets_fCoordinates_fPt[kMaxGenJets];   //[GenJets_]
   Double_t        GenJets_fCoordinates_fEta[kMaxGenJets];   //[GenJets_]
   Double_t        GenJets_fCoordinates_fPhi[kMaxGenJets];   //[GenJets_]
   Double_t        GenJets_fCoordinates_fE[kMaxGenJets];   //[GenJets_]
   Int_t           GenJetsAK8_;
   Double_t        GenJetsAK8_fCoordinates_fPt[kMaxGenJetsAK8];   //[GenJetsAK8_]
   Double_t        GenJetsAK8_fCoordinates_fEta[kMaxGenJetsAK8];   //[GenJetsAK8_]
   Double_t        GenJetsAK8_fCoordinates_fPhi[kMaxGenJetsAK8];   //[GenJetsAK8_]
   Double_t        GenJetsAK8_fCoordinates_fE[kMaxGenJetsAK8];   //[GenJetsAK8_]
   vector<int>     *GenJetsAK8_multiplicity;
   vector<double>  *GenJetsAK8_softDropMass;
   Double_t        GenMET;
   Double_t        GenMETPhi;
   Double_t        GenMHT;
   Double_t        GenMHTPhi;
   Int_t           GenParticles_;
   Double_t        GenParticles_fCoordinates_fPt[kMaxGenParticles];   //[GenParticles_]
   Double_t        GenParticles_fCoordinates_fEta[kMaxGenParticles];   //[GenParticles_]
   Double_t        GenParticles_fCoordinates_fPhi[kMaxGenParticles];   //[GenParticles_]
   Double_t        GenParticles_fCoordinates_fE[kMaxGenParticles];   //[GenParticles_]
   vector<int>     *GenParticles_Charge;
   vector<int>     *GenParticles_ParentId;
   vector<int>     *GenParticles_ParentIdx;
   vector<int>     *GenParticles_PdgId;
   vector<int>     *GenParticles_Status;
   vector<bool>    *GenParticles_TTFlag;
   vector<int>     *GenParticles_vertexIdx;
   Int_t           GenVertices_;
   Double_t        GenVertices_fCoordinates_fX[kMaxGenVertices];   //[GenVertices_]
   Double_t        GenVertices_fCoordinates_fY[kMaxGenVertices];   //[GenVertices_]
   Double_t        GenVertices_fCoordinates_fZ[kMaxGenVertices];   //[GenVertices_]
   Int_t           globalSuperTightHalo2016Filter;
   Int_t           globalTightHalo2016Filter;
   Int_t           HBHEIsoNoiseFilter;
   Int_t           HBHENoiseFilter;
   Double_t        HT;
   Double_t        HT5;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Bool_t          JetID;
   Bool_t          JetIDAK8;
   Int_t           Jets_;
   Double_t        Jets_fCoordinates_fPt[kMaxJets];   //[Jets_]
   Double_t        Jets_fCoordinates_fEta[kMaxJets];   //[Jets_]
   Double_t        Jets_fCoordinates_fPhi[kMaxJets];   //[Jets_]
   Double_t        Jets_fCoordinates_fE[kMaxJets];   //[Jets_]
   vector<double>  *Jets_axismajor;
   vector<double>  *Jets_axisminor;
   vector<double>  *Jets_bDiscriminatorCSV;
   vector<double>  *Jets_bJetTagDeepCSVBvsAll;
   vector<double>  *Jets_chargedEmEnergyFraction;
   vector<double>  *Jets_chargedHadronEnergyFraction;
   vector<int>     *Jets_chargedHadronMultiplicity;
   vector<int>     *Jets_chargedMultiplicity;
   vector<double>  *Jets_electronEnergyFraction;
   vector<int>     *Jets_electronMultiplicity;
   vector<int>     *Jets_hadronFlavor;
   vector<double>  *Jets_hfEMEnergyFraction;
   vector<double>  *Jets_hfHadronEnergyFraction;
   vector<bool>    *Jets_HTMask;
   vector<bool>    *Jets_ID;
   vector<double>  *Jets_jecFactor;
   vector<double>  *Jets_jerFactor;
   vector<bool>    *Jets_LeptonMask;
   vector<bool>    *Jets_MHTMask;
   vector<int>     *Jets_multiplicity;
   vector<double>  *Jets_muonEnergyFraction;
   vector<int>     *Jets_muonMultiplicity;
   vector<double>  *Jets_neutralEmEnergyFraction;
   vector<double>  *Jets_neutralHadronEnergyFraction;
   vector<int>     *Jets_neutralHadronMultiplicity;
   vector<int>     *Jets_neutralMultiplicity;
   vector<int>     *Jets_partonFlavor;
   vector<double>  *Jets_photonEnergyFraction;
   vector<int>     *Jets_photonMultiplicity;
   vector<double>  *Jets_ptD;
   vector<double>  *Jets_qgLikelihood;
   Int_t           JetsAK8_;
   Double_t        JetsAK8_fCoordinates_fPt[kMaxJetsAK8];   //[JetsAK8_]
   Double_t        JetsAK8_fCoordinates_fEta[kMaxJetsAK8];   //[JetsAK8_]
   Double_t        JetsAK8_fCoordinates_fPhi[kMaxJetsAK8];   //[JetsAK8_]
   Double_t        JetsAK8_fCoordinates_fE[kMaxJetsAK8];   //[JetsAK8_]
   vector<double>  *JetsAK8_chargedEmEnergyFraction;
   vector<double>  *JetsAK8_chargedHadronEnergyFraction;
   vector<int>     *JetsAK8_chargedHadronMultiplicity;
   vector<int>     *JetsAK8_chargedMultiplicity;
   vector<double>  *JetsAK8_DeepMassDecorrelTagbbvsLight;
   vector<double>  *JetsAK8_DeepMassDecorrelTagHbbvsQCD;
   vector<double>  *JetsAK8_DeepMassDecorrelTagTvsQCD;
   vector<double>  *JetsAK8_DeepMassDecorrelTagWvsQCD;
   vector<double>  *JetsAK8_DeepMassDecorrelTagZbbvsQCD;
   vector<double>  *JetsAK8_DeepMassDecorrelTagZHbbvsQCD;
   vector<double>  *JetsAK8_DeepMassDecorrelTagZvsQCD;
   vector<double>  *JetsAK8_DeepTagHbbvsQCD;
   vector<double>  *JetsAK8_DeepTagTvsQCD;
   vector<double>  *JetsAK8_DeepTagWvsQCD;
   vector<double>  *JetsAK8_DeepTagZbbvsQCD;
   vector<double>  *JetsAK8_DeepTagZvsQCD;
   vector<double>  *JetsAK8_doubleBDiscriminator;
   vector<double>  *JetsAK8_ecfN2b1;
   vector<double>  *JetsAK8_ecfN2b2;
   vector<double>  *JetsAK8_ecfN3b1;
   vector<double>  *JetsAK8_ecfN3b2;
   vector<double>  *JetsAK8_electronEnergyFraction;
   vector<int>     *JetsAK8_electronMultiplicity;
   vector<double>  *JetsAK8_hfEMEnergyFraction;
   vector<double>  *JetsAK8_hfHadronEnergyFraction;
   vector<bool>    *JetsAK8_ID;
   vector<double>  *JetsAK8_jecFactor;
   vector<double>  *JetsAK8_jerFactor;
   vector<double>  *JetsAK8_muonEnergyFraction;
   vector<int>     *JetsAK8_muonMultiplicity;
   vector<double>  *JetsAK8_neutralEmEnergyFraction;
   vector<double>  *JetsAK8_neutralHadronEnergyFraction;
   vector<double>  *JetsAK8_neutralHadronMultiplicity;
   vector<double>  *JetsAK8_neutralMultiplicity;
   vector<double>  *JetsAK8_NsubjettinessTau1;
   vector<double>  *JetsAK8_NsubjettinessTau2;
   vector<double>  *JetsAK8_NsubjettinessTau3;
   vector<int>     *JetsAK8_NumBhadrons;
   vector<int>     *JetsAK8_NumChadrons;
   vector<double>  *JetsAK8_pfMassIndependentDeepDoubleBvLJetTagsProbHbb;
   vector<double>  *JetsAK8_photonEnergyFraction;
   vector<double>  *JetsAK8_photonMultiplicity;
   vector<double>  *JetsAK8_softDropMass;
   Int_t           JetsAK8_subjets_;
   Double_t        JetsAK8_subjets_fCoordinates_fPt[kMaxJetsAK8_subjets];   //[JetsAK8_subjets_]
   Double_t        JetsAK8_subjets_fCoordinates_fEta[kMaxJetsAK8_subjets];   //[JetsAK8_subjets_]
   Double_t        JetsAK8_subjets_fCoordinates_fPhi[kMaxJetsAK8_subjets];   //[JetsAK8_subjets_]
   Double_t        JetsAK8_subjets_fCoordinates_fE[kMaxJetsAK8_subjets];   //[JetsAK8_subjets_]
   vector<int>     *JetsAK8_subjetsCounts;
   vector<double>  *JetsAK8_subjets_axismajor;
   vector<double>  *JetsAK8_subjets_axisminor;
   vector<double>  *JetsAK8_subjets_bDiscriminatorCSV;
   vector<double>  *JetsAK8_subjets_jecFactor;
   vector<int>     *JetsAK8_subjets_multiplicity;
   vector<double>  *JetsAK8_subjets_ptD;
   Double_t        madHT;
   Double_t        MET;
   vector<double>  *METDown;
   Double_t        METPhi;
   vector<double>  *METPhiDown;
   vector<double>  *METPhiUp;
   Double_t        METSignificance;
   vector<double>  *METUp;
   Double_t        MHT;
   Double_t        MHTPhi;
   Int_t           Muons_;
   Double_t        Muons_fCoordinates_fPt[kMaxMuons];   //[Muons_]
   Double_t        Muons_fCoordinates_fEta[kMaxMuons];   //[Muons_]
   Double_t        Muons_fCoordinates_fPhi[kMaxMuons];   //[Muons_]
   Double_t        Muons_fCoordinates_fE[kMaxMuons];   //[Muons_]
   vector<int>     *Muons_charge;
   vector<bool>    *Muons_passIso;
   Int_t           nAllVertices;
   Int_t           NElectrons;
   Int_t           NJets;
   Int_t           NJetsISR;
   Int_t           NMuons;
   Double_t        NumEvents;
   Int_t           NumInteractions;
   Int_t           NVtx;
   vector<float>   *PDFweights;
   Double_t        PFCaloMETRatio;
   Int_t           PrimaryVertexFilter;
   Int_t           PrimaryVertices_;
   Double_t        PrimaryVertices_fCoordinates_fX[kMaxPrimaryVertices];   //[PrimaryVertices_]
   Double_t        PrimaryVertices_fCoordinates_fY[kMaxPrimaryVertices];   //[PrimaryVertices_]
   Double_t        PrimaryVertices_fCoordinates_fZ[kMaxPrimaryVertices];   //[PrimaryVertices_]
   vector<double>  *PrimaryVertices_chi2;
   vector<bool>    *PrimaryVertices_isFake;
   vector<bool>    *PrimaryVertices_isGood;
   vector<bool>    *PrimaryVertices_isValid;
   vector<double>  *PrimaryVertices_ndof;
   vector<int>     *PrimaryVertices_nTracks;
   vector<double>  *PrimaryVertices_sumTrackPt2;
   vector<double>  *PrimaryVertices_tError;
   vector<double>  *PrimaryVertices_time;
   vector<double>  *PrimaryVertices_xError;
   vector<double>  *PrimaryVertices_yError;
   vector<double>  *PrimaryVertices_zError;
   vector<float>   *PSweights;
   Double_t        puSysDown;
   Double_t        puSysUp;
   Double_t        puWeight;
   vector<float>   *ScaleWeights;
   vector<double>  *SignalParameters;
   Int_t           Tracks_;
   Double_t        Tracks_fCoordinates_fX[kMaxTracks];   //[Tracks_]
   Double_t        Tracks_fCoordinates_fY[kMaxTracks];   //[Tracks_]
   Double_t        Tracks_fCoordinates_fZ[kMaxTracks];   //[Tracks_]
   vector<int>     *Tracks_charge;
   vector<double>  *Tracks_dxyErrorPV0;
   vector<double>  *Tracks_dxyPV0;
   vector<double>  *Tracks_dzAssociatedPV;
   vector<double>  *Tracks_dzErrorPV0;
   vector<double>  *Tracks_dzPV0;
   vector<double>  *Tracks_etaError;
   vector<int>     *Tracks_firstHit;
   vector<int>     *Tracks_foundHits;
   vector<int>     *Tracks_fromPV0;
   vector<int>     *Tracks_hitPattern;
   vector<int>     *Tracks_hitPatternCounts;
   vector<double>  *Tracks_IP2DPV0;
   vector<double>  *Tracks_IP2dSigPV0;
   vector<double>  *Tracks_IP3DPV0;
   vector<double>  *Tracks_IP3DSigPV0;
   vector<int>     *Tracks_lostHits;
   vector<bool>    *Tracks_matchedToPFCandidate;
   vector<double>  *Tracks_normalizedChi2;
   vector<int>     *Tracks_numberOfHits;
   vector<int>     *Tracks_numberOfPixelHits;
   vector<double>  *Tracks_phiError;
   vector<double>  *Tracks_ptError;
   vector<int>     *Tracks_pvAssociationQuality;
   vector<double>  *Tracks_qoverpError;
   vector<int>     *Tracks_quality;
   Int_t           Tracks_referencePoint_;
   Double_t        Tracks_referencePoint_fCoordinates_fX[kMaxTracks_referencePoint];   //[Tracks_referencePoint_]
   Double_t        Tracks_referencePoint_fCoordinates_fY[kMaxTracks_referencePoint];   //[Tracks_referencePoint_]
   Double_t        Tracks_referencePoint_fCoordinates_fZ[kMaxTracks_referencePoint];   //[Tracks_referencePoint_]
   vector<int>     *Tracks_vertexIdx;
   vector<int>     *TriggerPass;
   vector<int>     *TriggerPrescales;
   vector<int>     *TriggerVersion;
   Double_t        TrueNumInteractions;
   Double_t        Weight;

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_BadChargedCandidateFilter;   //!
   TBranch        *b_BadPFMuonFilter;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_BTagsDeepCSV;   //!
   TBranch        *b_CaloMET;   //!
   TBranch        *b_CaloMETPhi;   //!
   TBranch        *b_CrossSection;   //!
   TBranch        *b_CSCTightHaloFilter;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_DeltaPhi4;   //!
   TBranch        *b_ecalBadCalibFilter;   //!
   TBranch        *b_ecalBadCalibReducedExtraFilter;   //!
   TBranch        *b_ecalBadCalibReducedFilter;   //!
   TBranch        *b_EcalDeadCellBoundaryEnergyFilter;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_eeBadScFilter;   //!
   TBranch        *b_Electrons_;   //!
   TBranch        *b_Electrons_fCoordinates_fPt;   //!
   TBranch        *b_Electrons_fCoordinates_fEta;   //!
   TBranch        *b_Electrons_fCoordinates_fPhi;   //!
   TBranch        *b_Electrons_fCoordinates_fE;   //!
   TBranch        *b_Electrons_charge;   //!
   TBranch        *b_Electrons_passIso;   //!
   TBranch        *b_fixedGridRhoFastjetAll;   //!
   TBranch        *b_GenHT;   //!
   TBranch        *b_GenJets_;   //!
   TBranch        *b_GenJets_fCoordinates_fPt;   //!
   TBranch        *b_GenJets_fCoordinates_fEta;   //!
   TBranch        *b_GenJets_fCoordinates_fPhi;   //!
   TBranch        *b_GenJets_fCoordinates_fE;   //!
   TBranch        *b_GenJetsAK8_;   //!
   TBranch        *b_GenJetsAK8_fCoordinates_fPt;   //!
   TBranch        *b_GenJetsAK8_fCoordinates_fEta;   //!
   TBranch        *b_GenJetsAK8_fCoordinates_fPhi;   //!
   TBranch        *b_GenJetsAK8_fCoordinates_fE;   //!
   TBranch        *b_GenJetsAK8_multiplicity;   //!
   TBranch        *b_GenJetsAK8_softDropMass;   //!
   TBranch        *b_GenMET;   //!
   TBranch        *b_GenMETPhi;   //!
   TBranch        *b_GenMHT;   //!
   TBranch        *b_GenMHTPhi;   //!
   TBranch        *b_GenParticles_;   //!
   TBranch        *b_GenParticles_fCoordinates_fPt;   //!
   TBranch        *b_GenParticles_fCoordinates_fEta;   //!
   TBranch        *b_GenParticles_fCoordinates_fPhi;   //!
   TBranch        *b_GenParticles_fCoordinates_fE;   //!
   TBranch        *b_GenParticles_Charge;   //!
   TBranch        *b_GenParticles_ParentId;   //!
   TBranch        *b_GenParticles_ParentIdx;   //!
   TBranch        *b_GenParticles_PdgId;   //!
   TBranch        *b_GenParticles_Status;   //!
   TBranch        *b_GenParticles_TTFlag;   //!
   TBranch        *b_GenParticles_vertexIdx;   //!
   TBranch        *b_GenVertices_;   //!
   TBranch        *b_GenVertices_fCoordinates_fX;   //!
   TBranch        *b_GenVertices_fCoordinates_fY;   //!
   TBranch        *b_GenVertices_fCoordinates_fZ;   //!
   TBranch        *b_globalSuperTightHalo2016Filter;   //!
   TBranch        *b_globalTightHalo2016Filter;   //!
   TBranch        *b_HBHEIsoNoiseFilter;   //!
   TBranch        *b_HBHENoiseFilter;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_HT5;   //!
   TBranch        *b_isoElectronTracks;   //!
   TBranch        *b_isoMuonTracks;   //!
   TBranch        *b_isoPionTracks;   //!
   TBranch        *b_JetID;   //!
   TBranch        *b_JetIDAK8;   //!
   TBranch        *b_Jets_;   //!
   TBranch        *b_Jets_fCoordinates_fPt;   //!
   TBranch        *b_Jets_fCoordinates_fEta;   //!
   TBranch        *b_Jets_fCoordinates_fPhi;   //!
   TBranch        *b_Jets_fCoordinates_fE;   //!
   TBranch        *b_Jets_axismajor;   //!
   TBranch        *b_Jets_axisminor;   //!
   TBranch        *b_Jets_bDiscriminatorCSV;   //!
   TBranch        *b_Jets_bJetTagDeepCSVBvsAll;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity;   //!
   TBranch        *b_Jets_chargedMultiplicity;   //!
   TBranch        *b_Jets_electronEnergyFraction;   //!
   TBranch        *b_Jets_electronMultiplicity;   //!
   TBranch        *b_Jets_hadronFlavor;   //!
   TBranch        *b_Jets_hfEMEnergyFraction;   //!
   TBranch        *b_Jets_hfHadronEnergyFraction;   //!
   TBranch        *b_Jets_HTMask;   //!
   TBranch        *b_Jets_ID;   //!
   TBranch        *b_Jets_jecFactor;   //!
   TBranch        *b_Jets_jerFactor;   //!
   TBranch        *b_Jets_LeptonMask;   //!
   TBranch        *b_Jets_MHTMask;   //!
   TBranch        *b_Jets_multiplicity;   //!
   TBranch        *b_Jets_muonEnergyFraction;   //!
   TBranch        *b_Jets_muonMultiplicity;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity;   //!
   TBranch        *b_Jets_neutralMultiplicity;   //!
   TBranch        *b_Jets_partonFlavor;   //!
   TBranch        *b_Jets_photonEnergyFraction;   //!
   TBranch        *b_Jets_photonMultiplicity;   //!
   TBranch        *b_Jets_ptD;   //!
   TBranch        *b_Jets_qgLikelihood;   //!
   TBranch        *b_JetsAK8_;   //!
   TBranch        *b_JetsAK8_fCoordinates_fPt;   //!
   TBranch        *b_JetsAK8_fCoordinates_fEta;   //!
   TBranch        *b_JetsAK8_fCoordinates_fPhi;   //!
   TBranch        *b_JetsAK8_fCoordinates_fE;   //!
   TBranch        *b_JetsAK8_chargedEmEnergyFraction;   //!
   TBranch        *b_JetsAK8_chargedHadronEnergyFraction;   //!
   TBranch        *b_JetsAK8_chargedHadronMultiplicity;   //!
   TBranch        *b_JetsAK8_chargedMultiplicity;   //!
   TBranch        *b_JetsAK8_DeepMassDecorrelTagbbvsLight;   //!
   TBranch        *b_JetsAK8_DeepMassDecorrelTagHbbvsQCD;   //!
   TBranch        *b_JetsAK8_DeepMassDecorrelTagTvsQCD;   //!
   TBranch        *b_JetsAK8_DeepMassDecorrelTagWvsQCD;   //!
   TBranch        *b_JetsAK8_DeepMassDecorrelTagZbbvsQCD;   //!
   TBranch        *b_JetsAK8_DeepMassDecorrelTagZHbbvsQCD;   //!
   TBranch        *b_JetsAK8_DeepMassDecorrelTagZvsQCD;   //!
   TBranch        *b_JetsAK8_DeepTagHbbvsQCD;   //!
   TBranch        *b_JetsAK8_DeepTagTvsQCD;   //!
   TBranch        *b_JetsAK8_DeepTagWvsQCD;   //!
   TBranch        *b_JetsAK8_DeepTagZbbvsQCD;   //!
   TBranch        *b_JetsAK8_DeepTagZvsQCD;   //!
   TBranch        *b_JetsAK8_doubleBDiscriminator;   //!
   TBranch        *b_JetsAK8_ecfN2b1;   //!
   TBranch        *b_JetsAK8_ecfN2b2;   //!
   TBranch        *b_JetsAK8_ecfN3b1;   //!
   TBranch        *b_JetsAK8_ecfN3b2;   //!
   TBranch        *b_JetsAK8_electronEnergyFraction;   //!
   TBranch        *b_JetsAK8_electronMultiplicity;   //!
   TBranch        *b_JetsAK8_hfEMEnergyFraction;   //!
   TBranch        *b_JetsAK8_hfHadronEnergyFraction;   //!
   TBranch        *b_JetsAK8_ID;   //!
   TBranch        *b_JetsAK8_jecFactor;   //!
   TBranch        *b_JetsAK8_jerFactor;   //!
   TBranch        *b_JetsAK8_muonEnergyFraction;   //!
   TBranch        *b_JetsAK8_muonMultiplicity;   //!
   TBranch        *b_JetsAK8_neutralEmEnergyFraction;   //!
   TBranch        *b_JetsAK8_neutralHadronEnergyFraction;   //!
   TBranch        *b_JetsAK8_neutralHadronMultiplicity;   //!
   TBranch        *b_JetsAK8_neutralMultiplicity;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau1;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau2;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau3;   //!
   TBranch        *b_JetsAK8_NumBhadrons;   //!
   TBranch        *b_JetsAK8_NumChadrons;   //!
   TBranch        *b_JetsAK8_pfMassIndependentDeepDoubleBvLJetTagsProbHbb;   //!
   TBranch        *b_JetsAK8_photonEnergyFraction;   //!
   TBranch        *b_JetsAK8_photonMultiplicity;   //!
   TBranch        *b_JetsAK8_softDropMass;   //!
   TBranch        *b_JetsAK8_subjets_;   //!
   TBranch        *b_JetsAK8_subjets_fCoordinates_fPt;   //!
   TBranch        *b_JetsAK8_subjets_fCoordinates_fEta;   //!
   TBranch        *b_JetsAK8_subjets_fCoordinates_fPhi;   //!
   TBranch        *b_JetsAK8_subjets_fCoordinates_fE;   //!
   TBranch        *b_JetsAK8_subjetsCounts;   //!
   TBranch        *b_JetsAK8_subjets_axismajor;   //!
   TBranch        *b_JetsAK8_subjets_axisminor;   //!
   TBranch        *b_JetsAK8_subjets_bDiscriminatorCSV;   //!
   TBranch        *b_JetsAK8_subjets_jecFactor;   //!
   TBranch        *b_JetsAK8_subjets_multiplicity;   //!
   TBranch        *b_JetsAK8_subjets_ptD;   //!
   TBranch        *b_madHT;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METDown;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_METPhiDown;   //!
   TBranch        *b_METPhiUp;   //!
   TBranch        *b_METSignificance;   //!
   TBranch        *b_METUp;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MHTPhi;   //!
   TBranch        *b_Muons_;   //!
   TBranch        *b_Muons_fCoordinates_fPt;   //!
   TBranch        *b_Muons_fCoordinates_fEta;   //!
   TBranch        *b_Muons_fCoordinates_fPhi;   //!
   TBranch        *b_Muons_fCoordinates_fE;   //!
   TBranch        *b_Muons_charge;   //!
   TBranch        *b_Muons_passIso;   //!
   TBranch        *b_nAllVertices;   //!
   TBranch        *b_NElectrons;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_NJetsISR;   //!
   TBranch        *b_NMuons;   //!
   TBranch        *b_NumEvents;   //!
   TBranch        *b_NumInteractions;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_PDFweights;   //!
   TBranch        *b_PFCaloMETRatio;   //!
   TBranch        *b_PrimaryVertexFilter;   //!
   TBranch        *b_PrimaryVertices_;   //!
   TBranch        *b_PrimaryVertices_fCoordinates_fX;   //!
   TBranch        *b_PrimaryVertices_fCoordinates_fY;   //!
   TBranch        *b_PrimaryVertices_fCoordinates_fZ;   //!
   TBranch        *b_PrimaryVertices_chi2;   //!
   TBranch        *b_PrimaryVertices_isFake;   //!
   TBranch        *b_PrimaryVertices_isGood;   //!
   TBranch        *b_PrimaryVertices_isValid;   //!
   TBranch        *b_PrimaryVertices_ndof;   //!
   TBranch        *b_PrimaryVertices_nTracks;   //!
   TBranch        *b_PrimaryVertices_sumTrackPt2;   //!
   TBranch        *b_PrimaryVertices_tError;   //!
   TBranch        *b_PrimaryVertices_time;   //!
   TBranch        *b_PrimaryVertices_xError;   //!
   TBranch        *b_PrimaryVertices_yError;   //!
   TBranch        *b_PrimaryVertices_zError;   //!
   TBranch        *b_PSweights;   //!
   TBranch        *b_puSysDown;   //!
   TBranch        *b_puSysUp;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_ScaleWeights;   //!
   TBranch        *b_SignalParameters;   //!
   TBranch        *b_Tracks_;   //!
   TBranch        *b_Tracks_fCoordinates_fX;   //!
   TBranch        *b_Tracks_fCoordinates_fY;   //!
   TBranch        *b_Tracks_fCoordinates_fZ;   //!
   TBranch        *b_Tracks_charge;   //!
   TBranch        *b_Tracks_dxyErrorPV0;   //!
   TBranch        *b_Tracks_dxyPV0;   //!
   TBranch        *b_Tracks_dzAssociatedPV;   //!
   TBranch        *b_Tracks_dzErrorPV0;   //!
   TBranch        *b_Tracks_dzPV0;   //!
   TBranch        *b_Tracks_etaError;   //!
   TBranch        *b_Tracks_firstHit;   //!
   TBranch        *b_Tracks_foundHits;   //!
   TBranch        *b_Tracks_fromPV0;   //!
   TBranch        *b_Tracks_hitPattern;   //!
   TBranch        *b_Tracks_hitPatternCounts;   //!
   TBranch        *b_Tracks_IP2DPV0;   //!
   TBranch        *b_Tracks_IP2dSigPV0;   //!
   TBranch        *b_Tracks_IP3DPV0;   //!
   TBranch        *b_Tracks_IP3DSigPV0;   //!
   TBranch        *b_Tracks_lostHits;   //!
   TBranch        *b_Tracks_matchedToPFCandidate;   //!
   TBranch        *b_Tracks_normalizedChi2;   //!
   TBranch        *b_Tracks_numberOfHits;   //!
   TBranch        *b_Tracks_numberOfPixelHits;   //!
   TBranch        *b_Tracks_phiError;   //!
   TBranch        *b_Tracks_ptError;   //!
   TBranch        *b_Tracks_pvAssociationQuality;   //!
   TBranch        *b_Tracks_qoverpError;   //!
   TBranch        *b_Tracks_quality;   //!
   TBranch        *b_Tracks_referencePoint_;   //!
   TBranch        *b_Tracks_referencePoint_fCoordinates_fX;   //!
   TBranch        *b_Tracks_referencePoint_fCoordinates_fY;   //!
   TBranch        *b_Tracks_referencePoint_fCoordinates_fZ;   //!
   TBranch        *b_Tracks_vertexIdx;   //!
   TBranch        *b_TriggerPass;   //!
   TBranch        *b_TriggerPrescales;   //!
   TBranch        *b_TriggerVersion;   //!
   TBranch        *b_TrueNumInteractions;   //!
   TBranch        *b_Weight;   //!

   doHistos(TTree *tree=0,bool isMC=0);
   virtual ~doHistos();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(std::string s_sample,bool isMC);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef doHistos_cxx
doHistos::doHistos(TTree *tree, bool isMC) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://cmseos.fnal.gov//store/user/kdipetri/SUEP/Production_v0.2/2018/NTUP/PrivateSamples.SUEP_2018_mMed-1000_mDark-2_temp-2_decay-darkPhoHad_13TeV-pythia8_n-100_0_RA2AnalysisTree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://cmseos.fnal.gov//store/user/kdipetri/SUEP/Production_v0.2/2018/NTUP/PrivateSamples.SUEP_2018_mMed-1000_mDark-2_temp-2_decay-darkPhoHad_13TeV-pythia8_n-100_0_RA2AnalysisTree.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("root://cmseos.fnal.gov//store/user/kdipetri/SUEP/Production_v0.2/2018/NTUP/PrivateSamples.SUEP_2018_mMed-1000_mDark-2_temp-2_decay-darkPhoHad_13TeV-pythia8_n-100_0_RA2AnalysisTree.root:/TreeMaker2");
      dir->GetObject("PreSelection",tree);

   }
   Init(tree);
}

doHistos::~doHistos()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t doHistos::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t doHistos::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void doHistos::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Electrons_charge = 0;
   Electrons_passIso = 0;
   GenJetsAK8_multiplicity = 0;
   GenJetsAK8_softDropMass = 0;
   GenParticles_Charge = 0;
   GenParticles_ParentId = 0;
   GenParticles_ParentIdx = 0;
   GenParticles_PdgId = 0;
   GenParticles_Status = 0;
   GenParticles_TTFlag = 0;
   GenParticles_vertexIdx = 0;
   Jets_axismajor = 0;
   Jets_axisminor = 0;
   Jets_bDiscriminatorCSV = 0;
   Jets_bJetTagDeepCSVBvsAll = 0;
   Jets_chargedEmEnergyFraction = 0;
   Jets_chargedHadronEnergyFraction = 0;
   Jets_chargedHadronMultiplicity = 0;
   Jets_chargedMultiplicity = 0;
   Jets_electronEnergyFraction = 0;
   Jets_electronMultiplicity = 0;
   Jets_hadronFlavor = 0;
   Jets_hfEMEnergyFraction = 0;
   Jets_hfHadronEnergyFraction = 0;
   Jets_HTMask = 0;
   Jets_ID = 0;
   Jets_jecFactor = 0;
   Jets_jerFactor = 0;
   Jets_LeptonMask = 0;
   Jets_MHTMask = 0;
   Jets_multiplicity = 0;
   Jets_muonEnergyFraction = 0;
   Jets_muonMultiplicity = 0;
   Jets_neutralEmEnergyFraction = 0;
   Jets_neutralHadronEnergyFraction = 0;
   Jets_neutralHadronMultiplicity = 0;
   Jets_neutralMultiplicity = 0;
   Jets_partonFlavor = 0;
   Jets_photonEnergyFraction = 0;
   Jets_photonMultiplicity = 0;
   Jets_ptD = 0;
   Jets_qgLikelihood = 0;
   JetsAK8_chargedEmEnergyFraction = 0;
   JetsAK8_chargedHadronEnergyFraction = 0;
   JetsAK8_chargedHadronMultiplicity = 0;
   JetsAK8_chargedMultiplicity = 0;
   JetsAK8_DeepMassDecorrelTagbbvsLight = 0;
   JetsAK8_DeepMassDecorrelTagHbbvsQCD = 0;
   JetsAK8_DeepMassDecorrelTagTvsQCD = 0;
   JetsAK8_DeepMassDecorrelTagWvsQCD = 0;
   JetsAK8_DeepMassDecorrelTagZbbvsQCD = 0;
   JetsAK8_DeepMassDecorrelTagZHbbvsQCD = 0;
   JetsAK8_DeepMassDecorrelTagZvsQCD = 0;
   JetsAK8_DeepTagHbbvsQCD = 0;
   JetsAK8_DeepTagTvsQCD = 0;
   JetsAK8_DeepTagWvsQCD = 0;
   JetsAK8_DeepTagZbbvsQCD = 0;
   JetsAK8_DeepTagZvsQCD = 0;
   JetsAK8_doubleBDiscriminator = 0;
   JetsAK8_ecfN2b1 = 0;
   JetsAK8_ecfN2b2 = 0;
   JetsAK8_ecfN3b1 = 0;
   JetsAK8_ecfN3b2 = 0;
   JetsAK8_electronEnergyFraction = 0;
   JetsAK8_electronMultiplicity = 0;
   JetsAK8_hfEMEnergyFraction = 0;
   JetsAK8_hfHadronEnergyFraction = 0;
   JetsAK8_ID = 0;
   JetsAK8_jecFactor = 0;
   JetsAK8_jerFactor = 0;
   JetsAK8_muonEnergyFraction = 0;
   JetsAK8_muonMultiplicity = 0;
   JetsAK8_neutralEmEnergyFraction = 0;
   JetsAK8_neutralHadronEnergyFraction = 0;
   JetsAK8_neutralHadronMultiplicity = 0;
   JetsAK8_neutralMultiplicity = 0;
   JetsAK8_NsubjettinessTau1 = 0;
   JetsAK8_NsubjettinessTau2 = 0;
   JetsAK8_NsubjettinessTau3 = 0;
   JetsAK8_NumBhadrons = 0;
   JetsAK8_NumChadrons = 0;
   JetsAK8_pfMassIndependentDeepDoubleBvLJetTagsProbHbb = 0;
   JetsAK8_photonEnergyFraction = 0;
   JetsAK8_photonMultiplicity = 0;
   JetsAK8_softDropMass = 0;
   JetsAK8_subjetsCounts = 0;
   JetsAK8_subjets_axismajor = 0;
   JetsAK8_subjets_axisminor = 0;
   JetsAK8_subjets_bDiscriminatorCSV = 0;
   JetsAK8_subjets_jecFactor = 0;
   JetsAK8_subjets_multiplicity = 0;
   JetsAK8_subjets_ptD = 0;
   METDown = 0;
   METPhiDown = 0;
   METPhiUp = 0;
   METUp = 0;
   Muons_charge = 0;
   Muons_passIso = 0;
   PDFweights = 0;
   PrimaryVertices_chi2 = 0;
   PrimaryVertices_isFake = 0;
   PrimaryVertices_isGood = 0;
   PrimaryVertices_isValid = 0;
   PrimaryVertices_ndof = 0;
   PrimaryVertices_nTracks = 0;
   PrimaryVertices_sumTrackPt2 = 0;
   PrimaryVertices_tError = 0;
   PrimaryVertices_time = 0;
   PrimaryVertices_xError = 0;
   PrimaryVertices_yError = 0;
   PrimaryVertices_zError = 0;
   PSweights = 0;
   ScaleWeights = 0;
   SignalParameters = 0;
   Tracks_charge = 0;
   Tracks_dxyErrorPV0 = 0;
   Tracks_dxyPV0 = 0;
   Tracks_dzAssociatedPV = 0;
   Tracks_dzErrorPV0 = 0;
   Tracks_dzPV0 = 0;
   Tracks_etaError = 0;
   Tracks_firstHit = 0;
   Tracks_foundHits = 0;
   Tracks_fromPV0 = 0;
   Tracks_hitPattern = 0;
   Tracks_hitPatternCounts = 0;
   Tracks_IP2DPV0 = 0;
   Tracks_IP2dSigPV0 = 0;
   Tracks_IP3DPV0 = 0;
   Tracks_IP3DSigPV0 = 0;
   Tracks_lostHits = 0;
   Tracks_matchedToPFCandidate = 0;
   Tracks_normalizedChi2 = 0;
   Tracks_numberOfHits = 0;
   Tracks_numberOfPixelHits = 0;
   Tracks_phiError = 0;
   Tracks_ptError = 0;
   Tracks_pvAssociationQuality = 0;
   Tracks_qoverpError = 0;
   Tracks_quality = 0;
   Tracks_vertexIdx = 0;
   TriggerPass = 0;
   TriggerPrescales = 0;
   TriggerVersion = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
   fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("BTagsDeepCSV", &BTagsDeepCSV, &b_BTagsDeepCSV);
   fChain->SetBranchAddress("CaloMET", &CaloMET, &b_CaloMET);
   fChain->SetBranchAddress("CaloMETPhi", &CaloMETPhi, &b_CaloMETPhi);
   fChain->SetBranchAddress("CrossSection", &CrossSection, &b_CrossSection);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
   fChain->SetBranchAddress("ecalBadCalibFilter", &ecalBadCalibFilter, &b_ecalBadCalibFilter);
   fChain->SetBranchAddress("ecalBadCalibReducedExtraFilter", &ecalBadCalibReducedExtraFilter, &b_ecalBadCalibReducedExtraFilter);
   fChain->SetBranchAddress("ecalBadCalibReducedFilter", &ecalBadCalibReducedFilter, &b_ecalBadCalibReducedFilter);
   fChain->SetBranchAddress("EcalDeadCellBoundaryEnergyFilter", &EcalDeadCellBoundaryEnergyFilter, &b_EcalDeadCellBoundaryEnergyFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("Electrons", &Electrons_, &b_Electrons_);
   fChain->SetBranchAddress("Electrons.fCoordinates.fPt", Electrons_fCoordinates_fPt, &b_Electrons_fCoordinates_fPt);
   fChain->SetBranchAddress("Electrons.fCoordinates.fEta", Electrons_fCoordinates_fEta, &b_Electrons_fCoordinates_fEta);
   fChain->SetBranchAddress("Electrons.fCoordinates.fPhi", Electrons_fCoordinates_fPhi, &b_Electrons_fCoordinates_fPhi);
   fChain->SetBranchAddress("Electrons.fCoordinates.fE", Electrons_fCoordinates_fE, &b_Electrons_fCoordinates_fE);
   fChain->SetBranchAddress("Electrons_charge", &Electrons_charge, &b_Electrons_charge);
   fChain->SetBranchAddress("Electrons_passIso", &Electrons_passIso, &b_Electrons_passIso);
   fChain->SetBranchAddress("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll, &b_fixedGridRhoFastjetAll);
   fChain->SetBranchAddress("GenHT", &GenHT, &b_GenHT);
   fChain->SetBranchAddress("GenJets", &GenJets_, &b_GenJets_);
   fChain->SetBranchAddress("GenJets.fCoordinates.fPt", GenJets_fCoordinates_fPt, &b_GenJets_fCoordinates_fPt);
   fChain->SetBranchAddress("GenJets.fCoordinates.fEta", GenJets_fCoordinates_fEta, &b_GenJets_fCoordinates_fEta);
   fChain->SetBranchAddress("GenJets.fCoordinates.fPhi", GenJets_fCoordinates_fPhi, &b_GenJets_fCoordinates_fPhi);
   fChain->SetBranchAddress("GenJets.fCoordinates.fE", GenJets_fCoordinates_fE, &b_GenJets_fCoordinates_fE);
   fChain->SetBranchAddress("GenJetsAK8", &GenJetsAK8_, &b_GenJetsAK8_);
   fChain->SetBranchAddress("GenJetsAK8.fCoordinates.fPt", GenJetsAK8_fCoordinates_fPt, &b_GenJetsAK8_fCoordinates_fPt);
   fChain->SetBranchAddress("GenJetsAK8.fCoordinates.fEta", GenJetsAK8_fCoordinates_fEta, &b_GenJetsAK8_fCoordinates_fEta);
   fChain->SetBranchAddress("GenJetsAK8.fCoordinates.fPhi", GenJetsAK8_fCoordinates_fPhi, &b_GenJetsAK8_fCoordinates_fPhi);
   fChain->SetBranchAddress("GenJetsAK8.fCoordinates.fE", GenJetsAK8_fCoordinates_fE, &b_GenJetsAK8_fCoordinates_fE);
   fChain->SetBranchAddress("GenJetsAK8_multiplicity", &GenJetsAK8_multiplicity, &b_GenJetsAK8_multiplicity);
   fChain->SetBranchAddress("GenJetsAK8_softDropMass", &GenJetsAK8_softDropMass, &b_GenJetsAK8_softDropMass);
   fChain->SetBranchAddress("GenMET", &GenMET, &b_GenMET);
   fChain->SetBranchAddress("GenMETPhi", &GenMETPhi, &b_GenMETPhi);
   fChain->SetBranchAddress("GenMHT", &GenMHT, &b_GenMHT);
   fChain->SetBranchAddress("GenMHTPhi", &GenMHTPhi, &b_GenMHTPhi);
   fChain->SetBranchAddress("GenParticles", &GenParticles_, &b_GenParticles_);
   fChain->SetBranchAddress("GenParticles.fCoordinates.fPt", GenParticles_fCoordinates_fPt, &b_GenParticles_fCoordinates_fPt);
   fChain->SetBranchAddress("GenParticles.fCoordinates.fEta", GenParticles_fCoordinates_fEta, &b_GenParticles_fCoordinates_fEta);
   fChain->SetBranchAddress("GenParticles.fCoordinates.fPhi", GenParticles_fCoordinates_fPhi, &b_GenParticles_fCoordinates_fPhi);
   fChain->SetBranchAddress("GenParticles.fCoordinates.fE", GenParticles_fCoordinates_fE, &b_GenParticles_fCoordinates_fE);
   fChain->SetBranchAddress("GenParticles_Charge", &GenParticles_Charge, &b_GenParticles_Charge);
   fChain->SetBranchAddress("GenParticles_ParentId", &GenParticles_ParentId, &b_GenParticles_ParentId);
   fChain->SetBranchAddress("GenParticles_ParentIdx", &GenParticles_ParentIdx, &b_GenParticles_ParentIdx);
   fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
   fChain->SetBranchAddress("GenParticles_Status", &GenParticles_Status, &b_GenParticles_Status);
   fChain->SetBranchAddress("GenParticles_TTFlag", &GenParticles_TTFlag, &b_GenParticles_TTFlag);
   fChain->SetBranchAddress("GenParticles_vertexIdx", &GenParticles_vertexIdx, &b_GenParticles_vertexIdx);
   fChain->SetBranchAddress("GenVertices", &GenVertices_, &b_GenVertices_);
   fChain->SetBranchAddress("GenVertices.fCoordinates.fX", GenVertices_fCoordinates_fX, &b_GenVertices_fCoordinates_fX);
   fChain->SetBranchAddress("GenVertices.fCoordinates.fY", GenVertices_fCoordinates_fY, &b_GenVertices_fCoordinates_fY);
   fChain->SetBranchAddress("GenVertices.fCoordinates.fZ", GenVertices_fCoordinates_fZ, &b_GenVertices_fCoordinates_fZ);
   fChain->SetBranchAddress("globalSuperTightHalo2016Filter", &globalSuperTightHalo2016Filter, &b_globalSuperTightHalo2016Filter);
   fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
   fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("HT5", &HT5, &b_HT5);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("JetIDAK8", &JetIDAK8, &b_JetIDAK8);
   fChain->SetBranchAddress("Jets", &Jets_, &b_Jets_);
   fChain->SetBranchAddress("Jets.fCoordinates.fPt", Jets_fCoordinates_fPt, &b_Jets_fCoordinates_fPt);
   fChain->SetBranchAddress("Jets.fCoordinates.fEta", Jets_fCoordinates_fEta, &b_Jets_fCoordinates_fEta);
   fChain->SetBranchAddress("Jets.fCoordinates.fPhi", Jets_fCoordinates_fPhi, &b_Jets_fCoordinates_fPhi);
   fChain->SetBranchAddress("Jets.fCoordinates.fE", Jets_fCoordinates_fE, &b_Jets_fCoordinates_fE);
   fChain->SetBranchAddress("Jets_axismajor", &Jets_axismajor, &b_Jets_axismajor);
   fChain->SetBranchAddress("Jets_axisminor", &Jets_axisminor, &b_Jets_axisminor);
   fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVBvsAll", &Jets_bJetTagDeepCSVBvsAll, &b_Jets_bJetTagDeepCSVBvsAll);
   fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
   fChain->SetBranchAddress("Jets_chargedMultiplicity", &Jets_chargedMultiplicity, &b_Jets_chargedMultiplicity);
   fChain->SetBranchAddress("Jets_electronEnergyFraction", &Jets_electronEnergyFraction, &b_Jets_electronEnergyFraction);
   fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
   fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
   fChain->SetBranchAddress("Jets_hfEMEnergyFraction", &Jets_hfEMEnergyFraction, &b_Jets_hfEMEnergyFraction);
   fChain->SetBranchAddress("Jets_hfHadronEnergyFraction", &Jets_hfHadronEnergyFraction, &b_Jets_hfHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);
   fChain->SetBranchAddress("Jets_ID", &Jets_ID, &b_Jets_ID);
   fChain->SetBranchAddress("Jets_jecFactor", &Jets_jecFactor, &b_Jets_jecFactor);
   fChain->SetBranchAddress("Jets_jerFactor", &Jets_jerFactor, &b_Jets_jerFactor);
   fChain->SetBranchAddress("Jets_LeptonMask", &Jets_LeptonMask, &b_Jets_LeptonMask);
   fChain->SetBranchAddress("Jets_MHTMask", &Jets_MHTMask, &b_Jets_MHTMask);
   fChain->SetBranchAddress("Jets_multiplicity", &Jets_multiplicity, &b_Jets_multiplicity);
   fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
   fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
   fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronEnergyFraction", &Jets_neutralHadronEnergyFraction, &b_Jets_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
   fChain->SetBranchAddress("Jets_neutralMultiplicity", &Jets_neutralMultiplicity, &b_Jets_neutralMultiplicity);
   fChain->SetBranchAddress("Jets_partonFlavor", &Jets_partonFlavor, &b_Jets_partonFlavor);
   fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
   fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
   fChain->SetBranchAddress("Jets_ptD", &Jets_ptD, &b_Jets_ptD);
   fChain->SetBranchAddress("Jets_qgLikelihood", &Jets_qgLikelihood, &b_Jets_qgLikelihood);
   fChain->SetBranchAddress("JetsAK8", &JetsAK8_, &b_JetsAK8_);
   fChain->SetBranchAddress("JetsAK8.fCoordinates.fPt", JetsAK8_fCoordinates_fPt, &b_JetsAK8_fCoordinates_fPt);
   fChain->SetBranchAddress("JetsAK8.fCoordinates.fEta", JetsAK8_fCoordinates_fEta, &b_JetsAK8_fCoordinates_fEta);
   fChain->SetBranchAddress("JetsAK8.fCoordinates.fPhi", JetsAK8_fCoordinates_fPhi, &b_JetsAK8_fCoordinates_fPhi);
   fChain->SetBranchAddress("JetsAK8.fCoordinates.fE", JetsAK8_fCoordinates_fE, &b_JetsAK8_fCoordinates_fE);
   fChain->SetBranchAddress("JetsAK8_chargedEmEnergyFraction", &JetsAK8_chargedEmEnergyFraction, &b_JetsAK8_chargedEmEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_chargedHadronEnergyFraction", &JetsAK8_chargedHadronEnergyFraction, &b_JetsAK8_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_chargedHadronMultiplicity", &JetsAK8_chargedHadronMultiplicity, &b_JetsAK8_chargedHadronMultiplicity);
   fChain->SetBranchAddress("JetsAK8_chargedMultiplicity", &JetsAK8_chargedMultiplicity, &b_JetsAK8_chargedMultiplicity);
   fChain->SetBranchAddress("JetsAK8_DeepMassDecorrelTagbbvsLight", &JetsAK8_DeepMassDecorrelTagbbvsLight, &b_JetsAK8_DeepMassDecorrelTagbbvsLight);
   fChain->SetBranchAddress("JetsAK8_DeepMassDecorrelTagHbbvsQCD", &JetsAK8_DeepMassDecorrelTagHbbvsQCD, &b_JetsAK8_DeepMassDecorrelTagHbbvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepMassDecorrelTagTvsQCD", &JetsAK8_DeepMassDecorrelTagTvsQCD, &b_JetsAK8_DeepMassDecorrelTagTvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepMassDecorrelTagWvsQCD", &JetsAK8_DeepMassDecorrelTagWvsQCD, &b_JetsAK8_DeepMassDecorrelTagWvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepMassDecorrelTagZbbvsQCD", &JetsAK8_DeepMassDecorrelTagZbbvsQCD, &b_JetsAK8_DeepMassDecorrelTagZbbvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepMassDecorrelTagZHbbvsQCD", &JetsAK8_DeepMassDecorrelTagZHbbvsQCD, &b_JetsAK8_DeepMassDecorrelTagZHbbvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepMassDecorrelTagZvsQCD", &JetsAK8_DeepMassDecorrelTagZvsQCD, &b_JetsAK8_DeepMassDecorrelTagZvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepTagHbbvsQCD", &JetsAK8_DeepTagHbbvsQCD, &b_JetsAK8_DeepTagHbbvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepTagTvsQCD", &JetsAK8_DeepTagTvsQCD, &b_JetsAK8_DeepTagTvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepTagWvsQCD", &JetsAK8_DeepTagWvsQCD, &b_JetsAK8_DeepTagWvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepTagZbbvsQCD", &JetsAK8_DeepTagZbbvsQCD, &b_JetsAK8_DeepTagZbbvsQCD);
   fChain->SetBranchAddress("JetsAK8_DeepTagZvsQCD", &JetsAK8_DeepTagZvsQCD, &b_JetsAK8_DeepTagZvsQCD);
   fChain->SetBranchAddress("JetsAK8_doubleBDiscriminator", &JetsAK8_doubleBDiscriminator, &b_JetsAK8_doubleBDiscriminator);
   fChain->SetBranchAddress("JetsAK8_ecfN2b1", &JetsAK8_ecfN2b1, &b_JetsAK8_ecfN2b1);
   fChain->SetBranchAddress("JetsAK8_ecfN2b2", &JetsAK8_ecfN2b2, &b_JetsAK8_ecfN2b2);
   fChain->SetBranchAddress("JetsAK8_ecfN3b1", &JetsAK8_ecfN3b1, &b_JetsAK8_ecfN3b1);
   fChain->SetBranchAddress("JetsAK8_ecfN3b2", &JetsAK8_ecfN3b2, &b_JetsAK8_ecfN3b2);
   fChain->SetBranchAddress("JetsAK8_electronEnergyFraction", &JetsAK8_electronEnergyFraction, &b_JetsAK8_electronEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_electronMultiplicity", &JetsAK8_electronMultiplicity, &b_JetsAK8_electronMultiplicity);
   fChain->SetBranchAddress("JetsAK8_hfEMEnergyFraction", &JetsAK8_hfEMEnergyFraction, &b_JetsAK8_hfEMEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_hfHadronEnergyFraction", &JetsAK8_hfHadronEnergyFraction, &b_JetsAK8_hfHadronEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_ID", &JetsAK8_ID, &b_JetsAK8_ID);
   fChain->SetBranchAddress("JetsAK8_jecFactor", &JetsAK8_jecFactor, &b_JetsAK8_jecFactor);
   fChain->SetBranchAddress("JetsAK8_jerFactor", &JetsAK8_jerFactor, &b_JetsAK8_jerFactor);
   fChain->SetBranchAddress("JetsAK8_muonEnergyFraction", &JetsAK8_muonEnergyFraction, &b_JetsAK8_muonEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_muonMultiplicity", &JetsAK8_muonMultiplicity, &b_JetsAK8_muonMultiplicity);
   fChain->SetBranchAddress("JetsAK8_neutralEmEnergyFraction", &JetsAK8_neutralEmEnergyFraction, &b_JetsAK8_neutralEmEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_neutralHadronEnergyFraction", &JetsAK8_neutralHadronEnergyFraction, &b_JetsAK8_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_neutralHadronMultiplicity", &JetsAK8_neutralHadronMultiplicity, &b_JetsAK8_neutralHadronMultiplicity);
   fChain->SetBranchAddress("JetsAK8_neutralMultiplicity", &JetsAK8_neutralMultiplicity, &b_JetsAK8_neutralMultiplicity);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau1", &JetsAK8_NsubjettinessTau1, &b_JetsAK8_NsubjettinessTau1);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau2", &JetsAK8_NsubjettinessTau2, &b_JetsAK8_NsubjettinessTau2);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau3", &JetsAK8_NsubjettinessTau3, &b_JetsAK8_NsubjettinessTau3);
   fChain->SetBranchAddress("JetsAK8_NumBhadrons", &JetsAK8_NumBhadrons, &b_JetsAK8_NumBhadrons);
   fChain->SetBranchAddress("JetsAK8_NumChadrons", &JetsAK8_NumChadrons, &b_JetsAK8_NumChadrons);
   fChain->SetBranchAddress("JetsAK8_pfMassIndependentDeepDoubleBvLJetTagsProbHbb", &JetsAK8_pfMassIndependentDeepDoubleBvLJetTagsProbHbb, &b_JetsAK8_pfMassIndependentDeepDoubleBvLJetTagsProbHbb);
   fChain->SetBranchAddress("JetsAK8_photonEnergyFraction", &JetsAK8_photonEnergyFraction, &b_JetsAK8_photonEnergyFraction);
   fChain->SetBranchAddress("JetsAK8_photonMultiplicity", &JetsAK8_photonMultiplicity, &b_JetsAK8_photonMultiplicity);
   fChain->SetBranchAddress("JetsAK8_softDropMass", &JetsAK8_softDropMass, &b_JetsAK8_softDropMass);
   fChain->SetBranchAddress("JetsAK8_subjets", &JetsAK8_subjets_, &b_JetsAK8_subjets_);
   fChain->SetBranchAddress("JetsAK8_subjets.fCoordinates.fPt", JetsAK8_subjets_fCoordinates_fPt, &b_JetsAK8_subjets_fCoordinates_fPt);
   fChain->SetBranchAddress("JetsAK8_subjets.fCoordinates.fEta", JetsAK8_subjets_fCoordinates_fEta, &b_JetsAK8_subjets_fCoordinates_fEta);
   fChain->SetBranchAddress("JetsAK8_subjets.fCoordinates.fPhi", JetsAK8_subjets_fCoordinates_fPhi, &b_JetsAK8_subjets_fCoordinates_fPhi);
   fChain->SetBranchAddress("JetsAK8_subjets.fCoordinates.fE", JetsAK8_subjets_fCoordinates_fE, &b_JetsAK8_subjets_fCoordinates_fE);
   fChain->SetBranchAddress("JetsAK8_subjetsCounts", &JetsAK8_subjetsCounts, &b_JetsAK8_subjetsCounts);
   fChain->SetBranchAddress("JetsAK8_subjets_axismajor", &JetsAK8_subjets_axismajor, &b_JetsAK8_subjets_axismajor);
   fChain->SetBranchAddress("JetsAK8_subjets_axisminor", &JetsAK8_subjets_axisminor, &b_JetsAK8_subjets_axisminor);
   fChain->SetBranchAddress("JetsAK8_subjets_bDiscriminatorCSV", &JetsAK8_subjets_bDiscriminatorCSV, &b_JetsAK8_subjets_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsAK8_subjets_jecFactor", &JetsAK8_subjets_jecFactor, &b_JetsAK8_subjets_jecFactor);
   fChain->SetBranchAddress("JetsAK8_subjets_multiplicity", &JetsAK8_subjets_multiplicity, &b_JetsAK8_subjets_multiplicity);
   fChain->SetBranchAddress("JetsAK8_subjets_ptD", &JetsAK8_subjets_ptD, &b_JetsAK8_subjets_ptD);
   fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METDown", &METDown, &b_METDown);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("METPhiDown", &METPhiDown, &b_METPhiDown);
   fChain->SetBranchAddress("METPhiUp", &METPhiUp, &b_METPhiUp);
   fChain->SetBranchAddress("METSignificance", &METSignificance, &b_METSignificance);
   fChain->SetBranchAddress("METUp", &METUp, &b_METUp);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
   fChain->SetBranchAddress("Muons", &Muons_, &b_Muons_);
   fChain->SetBranchAddress("Muons.fCoordinates.fPt", Muons_fCoordinates_fPt, &b_Muons_fCoordinates_fPt);
   fChain->SetBranchAddress("Muons.fCoordinates.fEta", Muons_fCoordinates_fEta, &b_Muons_fCoordinates_fEta);
   fChain->SetBranchAddress("Muons.fCoordinates.fPhi", Muons_fCoordinates_fPhi, &b_Muons_fCoordinates_fPhi);
   fChain->SetBranchAddress("Muons.fCoordinates.fE", Muons_fCoordinates_fE, &b_Muons_fCoordinates_fE);
   fChain->SetBranchAddress("Muons_charge", &Muons_charge, &b_Muons_charge);
   fChain->SetBranchAddress("Muons_passIso", &Muons_passIso, &b_Muons_passIso);
   fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
   fChain->SetBranchAddress("NElectrons", &NElectrons, &b_NElectrons);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NJetsISR", &NJetsISR, &b_NJetsISR);
   fChain->SetBranchAddress("NMuons", &NMuons, &b_NMuons);
   fChain->SetBranchAddress("NumEvents", &NumEvents, &b_NumEvents);
   fChain->SetBranchAddress("NumInteractions", &NumInteractions, &b_NumInteractions);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("PDFweights", &PDFweights, &b_PDFweights);
   fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);
   fChain->SetBranchAddress("PrimaryVertexFilter", &PrimaryVertexFilter, &b_PrimaryVertexFilter);
   fChain->SetBranchAddress("PrimaryVertices", &PrimaryVertices_, &b_PrimaryVertices_);
   fChain->SetBranchAddress("PrimaryVertices.fCoordinates.fX", PrimaryVertices_fCoordinates_fX, &b_PrimaryVertices_fCoordinates_fX);
   fChain->SetBranchAddress("PrimaryVertices.fCoordinates.fY", PrimaryVertices_fCoordinates_fY, &b_PrimaryVertices_fCoordinates_fY);
   fChain->SetBranchAddress("PrimaryVertices.fCoordinates.fZ", PrimaryVertices_fCoordinates_fZ, &b_PrimaryVertices_fCoordinates_fZ);
   fChain->SetBranchAddress("PrimaryVertices_chi2", &PrimaryVertices_chi2, &b_PrimaryVertices_chi2);
   fChain->SetBranchAddress("PrimaryVertices_isFake", &PrimaryVertices_isFake, &b_PrimaryVertices_isFake);
   fChain->SetBranchAddress("PrimaryVertices_isGood", &PrimaryVertices_isGood, &b_PrimaryVertices_isGood);
   fChain->SetBranchAddress("PrimaryVertices_isValid", &PrimaryVertices_isValid, &b_PrimaryVertices_isValid);
   fChain->SetBranchAddress("PrimaryVertices_ndof", &PrimaryVertices_ndof, &b_PrimaryVertices_ndof);
   fChain->SetBranchAddress("PrimaryVertices_nTracks", &PrimaryVertices_nTracks, &b_PrimaryVertices_nTracks);
   fChain->SetBranchAddress("PrimaryVertices_sumTrackPt2", &PrimaryVertices_sumTrackPt2, &b_PrimaryVertices_sumTrackPt2);
   fChain->SetBranchAddress("PrimaryVertices_tError", &PrimaryVertices_tError, &b_PrimaryVertices_tError);
   fChain->SetBranchAddress("PrimaryVertices_time", &PrimaryVertices_time, &b_PrimaryVertices_time);
   fChain->SetBranchAddress("PrimaryVertices_xError", &PrimaryVertices_xError, &b_PrimaryVertices_xError);
   fChain->SetBranchAddress("PrimaryVertices_yError", &PrimaryVertices_yError, &b_PrimaryVertices_yError);
   fChain->SetBranchAddress("PrimaryVertices_zError", &PrimaryVertices_zError, &b_PrimaryVertices_zError);
   fChain->SetBranchAddress("PSweights", &PSweights, &b_PSweights);
   fChain->SetBranchAddress("puSysDown", &puSysDown, &b_puSysDown);
   fChain->SetBranchAddress("puSysUp", &puSysUp, &b_puSysUp);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
   fChain->SetBranchAddress("SignalParameters", &SignalParameters, &b_SignalParameters);
   fChain->SetBranchAddress("Tracks", &Tracks_, &b_Tracks_);
   fChain->SetBranchAddress("Tracks.fCoordinates.fX", Tracks_fCoordinates_fX, &b_Tracks_fCoordinates_fX);
   fChain->SetBranchAddress("Tracks.fCoordinates.fY", Tracks_fCoordinates_fY, &b_Tracks_fCoordinates_fY);
   fChain->SetBranchAddress("Tracks.fCoordinates.fZ", Tracks_fCoordinates_fZ, &b_Tracks_fCoordinates_fZ);
   fChain->SetBranchAddress("Tracks_charge", &Tracks_charge, &b_Tracks_charge);
   fChain->SetBranchAddress("Tracks_dxyErrorPV0", &Tracks_dxyErrorPV0, &b_Tracks_dxyErrorPV0);
   fChain->SetBranchAddress("Tracks_dxyPV0", &Tracks_dxyPV0, &b_Tracks_dxyPV0);
   fChain->SetBranchAddress("Tracks_dzAssociatedPV", &Tracks_dzAssociatedPV, &b_Tracks_dzAssociatedPV);
   fChain->SetBranchAddress("Tracks_dzErrorPV0", &Tracks_dzErrorPV0, &b_Tracks_dzErrorPV0);
   fChain->SetBranchAddress("Tracks_dzPV0", &Tracks_dzPV0, &b_Tracks_dzPV0);
   fChain->SetBranchAddress("Tracks_etaError", &Tracks_etaError, &b_Tracks_etaError);
   fChain->SetBranchAddress("Tracks_firstHit", &Tracks_firstHit, &b_Tracks_firstHit);
   fChain->SetBranchAddress("Tracks_foundHits", &Tracks_foundHits, &b_Tracks_foundHits);
   fChain->SetBranchAddress("Tracks_fromPV0", &Tracks_fromPV0, &b_Tracks_fromPV0);
   fChain->SetBranchAddress("Tracks_hitPattern", &Tracks_hitPattern, &b_Tracks_hitPattern);
   fChain->SetBranchAddress("Tracks_hitPatternCounts", &Tracks_hitPatternCounts, &b_Tracks_hitPatternCounts);
   fChain->SetBranchAddress("Tracks_IP2DPV0", &Tracks_IP2DPV0, &b_Tracks_IP2DPV0);
   fChain->SetBranchAddress("Tracks_IP2dSigPV0", &Tracks_IP2dSigPV0, &b_Tracks_IP2dSigPV0);
   fChain->SetBranchAddress("Tracks_IP3DPV0", &Tracks_IP3DPV0, &b_Tracks_IP3DPV0);
   fChain->SetBranchAddress("Tracks_IP3DSigPV0", &Tracks_IP3DSigPV0, &b_Tracks_IP3DSigPV0);
   fChain->SetBranchAddress("Tracks_lostHits", &Tracks_lostHits, &b_Tracks_lostHits);
   fChain->SetBranchAddress("Tracks_matchedToPFCandidate", &Tracks_matchedToPFCandidate, &b_Tracks_matchedToPFCandidate);
   fChain->SetBranchAddress("Tracks_normalizedChi2", &Tracks_normalizedChi2, &b_Tracks_normalizedChi2);
   fChain->SetBranchAddress("Tracks_numberOfHits", &Tracks_numberOfHits, &b_Tracks_numberOfHits);
   fChain->SetBranchAddress("Tracks_numberOfPixelHits", &Tracks_numberOfPixelHits, &b_Tracks_numberOfPixelHits);
   fChain->SetBranchAddress("Tracks_phiError", &Tracks_phiError, &b_Tracks_phiError);
   fChain->SetBranchAddress("Tracks_ptError", &Tracks_ptError, &b_Tracks_ptError);
   fChain->SetBranchAddress("Tracks_pvAssociationQuality", &Tracks_pvAssociationQuality, &b_Tracks_pvAssociationQuality);
   fChain->SetBranchAddress("Tracks_qoverpError", &Tracks_qoverpError, &b_Tracks_qoverpError);
   fChain->SetBranchAddress("Tracks_quality", &Tracks_quality, &b_Tracks_quality);
   fChain->SetBranchAddress("Tracks_referencePoint", &Tracks_referencePoint_, &b_Tracks_referencePoint_);
   fChain->SetBranchAddress("Tracks_referencePoint.fCoordinates.fX", Tracks_referencePoint_fCoordinates_fX, &b_Tracks_referencePoint_fCoordinates_fX);
   fChain->SetBranchAddress("Tracks_referencePoint.fCoordinates.fY", Tracks_referencePoint_fCoordinates_fY, &b_Tracks_referencePoint_fCoordinates_fY);
   fChain->SetBranchAddress("Tracks_referencePoint.fCoordinates.fZ", Tracks_referencePoint_fCoordinates_fZ, &b_Tracks_referencePoint_fCoordinates_fZ);
   fChain->SetBranchAddress("Tracks_vertexIdx", &Tracks_vertexIdx, &b_Tracks_vertexIdx);
   fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
   fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
   fChain->SetBranchAddress("TriggerVersion", &TriggerVersion, &b_TriggerVersion);
   fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   Notify();
}

Bool_t doHistos::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void doHistos::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t doHistos::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef doHistos_cxx
