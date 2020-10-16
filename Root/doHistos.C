#define doHistos_cxx
#include "SUEP_Analysis/doHistos.h"
#include "SUEP_Analysis/PlotHelper.h"
#include "Root/jetStudies.C"
// doesn't work in cmssw
//#include "Root/variableJets.C"
#include "Root/eventDisplays.C"
#include "Root/eventShapes.C"
#include "Root/kinematics.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <vector>
#include <string>
using namespace std;

int get_charge(int pdgId){
  if (abs(pdgId) == 11) return 1;
  if (abs(pdgId) == 13) return 1;
  if (abs(pdgId) == 211) return 1;
  return 0;
}

void doHistos::Loop(std::string s_sample,bool isMC)
{
	//////////////////////////////////////////////////////
    // Loops over the input ntuple from a given sample  //
    //////////////////////////////////////////////////////

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << " Analyzing Tree : " << s_sample << " with " << nentries << " entries" << std::endl;

   //disable all branches
   fChain->SetBranchStatus("*",0);
   //only activate branches that are used (faster)
   vector<string> branches_used{
      //"Jets",
      "Jets.fCoordinates.fPt",  
      "Jets.fCoordinates.fEta", 
      "Jets.fCoordinates.fPhi", 
      "Jets.fCoordinates.fE",   
      "Jets_ID",
      "Jets_multiplicity",
      "Jets_chargedMultiplicity",
      //"JetsAK8",
      "JetsAK8.fCoordinates.fPt",  
      "JetsAK8.fCoordinates.fEta", 
      "JetsAK8.fCoordinates.fPhi", 
      "JetsAK8.fCoordinates.fE",   
      "JetsAK8_ID",
      //"Tracks",
      "Tracks_fromPV0",
      "Tracks.fCoordinates.fX",
      "Tracks.fCoordinates.fY",
      "Tracks.fCoordinates.fZ",
      "Tracks_matchedToPFCandidate",
      "GenParticles.fCoordinates.fPt", 
      "GenParticles.fCoordinates.fEta", 
      "GenParticles.fCoordinates.fPhi", 
      "GenParticles.fCoordinates.fE",   
      "GenParticles_Charge",
      "GenParticles_ParentId",
      "GenParticles_PdgId",
      "GenParticles_Status",
   };
   for(const auto& branch : branches_used) fChain->SetBranchStatus(branch.c_str(),1);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if (ientry%1000==0) std::cout << "Processed " << ientry << " events!" << std::endl;

      // Find the scalar, and pack up truth information
      SUEP_Jet suep_jet_all; // all status 1 particles
      SUEP_Jet suep_jet_charge; // add charge
      SUEP_Jet suep_jet_eta2p5; // add eta 2.5 
      SUEP_Jet suep_jet; // add pt 1 geV
      TLorentzVector suep_particle_p4;
      std::vector<SUEP_particle> suep_particles; suep_particles.clear();
      int ntruth=0;

      for (unsigned int i=0; i < GenParticles_PdgId->size(); i++)
      {
        if (GenParticles_PdgId->at(i)==25) {
          scalar.SetPtEtaPhiE(GenParticles_fCoordinates_fPt[i],GenParticles_fCoordinates_fEta[i],GenParticles_fCoordinates_fPhi[i],GenParticles_fCoordinates_fE[i]);
        }

        // pack up suep final state particles
        // Only works for dark pho (had) samples - electrons muons hadrons
        // std::cout << GenParticles_ParentId->at(i) << " " << GenParticles_Status->at(i) << std::endl;
        if (GenParticles_ParentId->at(i)==999998 && GenParticles_Status->at(i)==1) {
          SUEP_particle suep_particle;

          ntruth+=1;
          suep_particle_p4.SetPtEtaPhiE(GenParticles_fCoordinates_fPt[i],GenParticles_fCoordinates_fEta[i],GenParticles_fCoordinates_fPhi[i],GenParticles_fCoordinates_fE[i]);

          suep_particle.p4 = suep_particle_p4; 
          //suep_particle.p4 = GenParticles->at(i); 
          suep_particle.pdgId = GenParticles_PdgId->at(i);
          suep_particle.pt1GeV = ( suep_particle_p4.Pt() > 1 );
          suep_particle.eta2p5 = ( abs(suep_particle_p4.Eta()) < 2.5 );
          suep_particle.isReco = 0;//set to zero for now
          suep_particle.charge = GenParticles_Charge->at(i); 
          //suep_particle.charge = get_charge(GenParticles_PdgId->at(i));
          suep_particles.push_back(suep_particle);

          // for acceptance studies
          suep_jet_all.p4+=suep_particle.p4; 
          suep_jet_all.nTruthTracks+=1;
          if (suep_particle.charge==1) {
            suep_jet_charge.p4+=suep_particle.p4; 
            suep_jet_charge.nTruthTracks+=1;
            if (suep_particle.eta2p5){
              suep_jet_eta2p5.p4+=suep_particle.p4; 
              suep_jet_eta2p5.nTruthTracks+=1;
              if (suep_particle.pt1GeV){
                suep_jet.p4+=suep_particle.p4; 
                suep_jet.nTruthTracks+=1;               
              }
            }
          }

        } // decay products
      } // truth particle loop
        
      // Truth acceptance study
      //plotter.Plot1D(Form("%s_truthstudy_scalar_mass"   , s_sample.c_str()), ";mass [GeV]" , scalar.M()      , 100, 0, 2000);
      //plotter.Plot1D(Form("%s_truthstudy_scalar_ntracks", s_sample.c_str()), ";n_tracks"   , -1              , 100, 0, 1000);
      //plotter.Plot1D(Form("%s_truthstudy_scalar_pt"     , s_sample.c_str()), ";p_{T} [GeV]", scalar.Pt()     , 100, 0, 2000);

      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_charge_mass"   , s_sample.c_str()), ";mass [GeV]" , suep_jet_all.p4.M()      , 100, 0, 2000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_charge_ntracks", s_sample.c_str()), ";n_tracks"   , suep_jet_all.nTruthTracks, 100, 0, 1000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_charge_pt"     , s_sample.c_str()), ";p_{T} [GeV]", suep_jet_all.p4.Pt()     , 100, 0, 2000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_eta2p5_mass"   , s_sample.c_str()), ";mass [GeV]" , suep_jet_eta2p5.p4.M()      , 100, 0, 2000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_eta2p5_ntracks", s_sample.c_str()), ";n_tracks"   , suep_jet_eta2p5.nTruthTracks, 100, 0, 1000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_eta2p5_pt"     , s_sample.c_str()), ";p_{T} [GeV]", suep_jet_eta2p5.p4.Pt()     , 100, 0, 2000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_mass"          , s_sample.c_str()), ";mass [GeV]" , suep_jet.p4.M()      , 100, 0, 2000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_ntracks"       , s_sample.c_str()), ";n_tracks"   , suep_jet.nTruthTracks, 100, 0, 1000);
      //plotter.Plot1D(Form("%s_truthstudy_suep_jet_pt"            , s_sample.c_str()), ";p_{T} [GeV]", suep_jet.p4.Pt()     , 100, 0, 2000);
  
      //plotter.Plot2D(Form("%s_truthstudy_suep_jet_eta2p5_ntracks_scalar_eta"   , s_sample.c_str()), "" , scalar.Eta(), suep_jet_eta2p5.nTruthTracks  , 50, -5, 5, 50, 0, 1000);

      //plotter.Plot2D(Form("%s_truthstudy_suep_jet_charge_scalar_mass"   , s_sample.c_str()), "" , scalar.M(), suep_jet_all.p4.M()     , 50, 0, 2000, 50, 0, 2000);
      //plotter.Plot2D(Form("%s_truthstudy_suep_jet_eta2p5_scalar_mass"   , s_sample.c_str()), "" , scalar.M(), suep_jet_eta2p5.p4.M()  , 50, 0, 2000, 50, 0, 2000);
      //plotter.Plot2D(Form("%s_truthstudy_suep_jet_scalar_mass"          , s_sample.c_str()), "" , scalar.M(), suep_jet.p4.M()         , 100, 0, 2000, 100, 0, 1000);
  
      //plotter.Plot2D(Form("%s_truthstudy_suep_jet_charge_scalar_pt"   , s_sample.c_str()), "" , scalar.Pt(), suep_jet_all.p4.Pt()     , 50, 0, 2000, 50, 0, 2000);
      //plotter.Plot2D(Form("%s_truthstudy_suep_jet_eta2p5_scalar_pt"   , s_sample.c_str()), "" , scalar.Pt(), suep_jet_eta2p5.p4.Pt()  , 50, 0, 2000, 50, 0, 2000);
      //plotter.Plot2D(Form("%s_truthstudy_suep_jet_scalar_pt"          , s_sample.c_str()), "" , scalar.Pt(), suep_jet.p4.Pt()         , 50, 0, 2000, 50, 0, 2000);

      //plotter.Plot1D(Form("%s_ntruth_final_state" ,s_sample.c_str()),";ntruth", ntruth, 100,0,500);
        

      // *
      // Packing up inner detector tracks
      // * 
      npfs=0; // number of charged pflow candidates with pT > 1 GeV
      npfs_09=0; // 0.9 GeV
      npfs_08=0; // 0.8 GeV
      npfs_07=0; // 0.7 GeV
      npfs_2=0; // for Phase 2 question
      TLorentzVector trk_p4;
      std::vector<Track> tracks; tracks.clear();
      for (unsigned int i = 0; i <Tracks_fromPV0->size(); i++)
      {

        // Make 4 vector bc ppl be cray
        trk_p4.SetXYZM(Tracks_fCoordinates_fX[i],Tracks_fCoordinates_fY[i],Tracks_fCoordinates_fY[i], 0.13957);
        //trk_p4.SetPtEtaPhiM(Tracks->at(i).Rho(), Tracks->at(i).Eta(), Tracks->at(i).Phi(), 0.13957);

        if (abs(trk_p4.Eta()) > 2.5) continue;
        if (Tracks_fromPV0->at(i) < 2) continue;
        if (Tracks_matchedToPFCandidate->at(i) == 0) continue;
        if (trk_p4.Pt() > 0.7) npfs_07 +=1;
        if (trk_p4.Pt() > 0.8) npfs_08 +=1;
        if (trk_p4.Pt() > 0.9) npfs_09 +=1;
        if (trk_p4.Pt() < 1.0) continue; // pT cut 1 GeV, to be optimized
        if (trk_p4.Pt() > 2.0) npfs_2 +=1;
        Track track;

        track.p4 = trk_p4; 
        track.isSuep = false;
        
        tracks.push_back(track);
        npfs+=1;
        plotter.Plot1D(Form("%s_chpfs_pt" ,s_sample.c_str()),";chPFs pT", track.p4.Pt(), 100,0,10);
      }
      
      // *
      // Anti-kt R=0.4 jets - use these to calculate HT
      // *
      unsigned int index=0;
      ht=0;
      njets=0;
      lead_jet_pt=0;
      TLorentzVector jet_p4;
      std::vector<Jet> jets; jets.clear();
      for (unsigned int i = 0; i <Jets_ID->size(); i++)
      {

        jet_p4.SetPtEtaPhiE(Jets_fCoordinates_fPt[i],Jets_fCoordinates_fEta[i],Jets_fCoordinates_fPhi[i],Jets_fCoordinates_fE[i]);
        //jet_p4 = Jets->at(i);

        if ( jet_p4.Pt() < 30 ) continue;
        if ( abs(jet_p4.Eta() ) > 2.0 ) continue;
          
        njets+=1;
        ht += jet_p4.Pt();

        Jet jet;
        jet.index = index;

        jet.p4 = jet_p4;

        jet.multiplicity = Jets_multiplicity->at(i);
        jet.chargedMultiplicity = Jets_chargedMultiplicity->at(i);

        if (jet_p4.Pt() > lead_jet_pt ) lead_jet_pt = jet_p4.Pt() ;

        //TLorentzVector num; 
        //for (auto track : tracks){
        //   if (jet.p4.DeltaR(track.p4) > 1.0 ) continue;
        //   if (jet.p4.DeltaR(track.p4) < 0.4 ) continue;
        //   num += track.p4;
        //}
        //
        //jet.isolation = (num.Pt())/jet.p4.Pt(); // test 

        jet.scalar_dPhi = abs(jet.p4.DeltaPhi(scalar));
        jet.scalar_dR   = jet.p4.DeltaR(scalar);

        //float min_dR = 6.0; 
        //for (auto jet2 : jets){
        //  if ( jet.index==jet2.index) continue;
        //  float tmp_dR   = jet.p4.DeltaR(jet2.p4);
        //  if (tmp_dR   < min_dR  ) min_dR = tmp_dR;
        //}
        //jet.min_dR = min_dR;
        
        // Save jet
        jets.push_back(jet);
    
        index+=1;
      }

      //*
      // Anti-kt R=0.8 fat jets - not validated
      //*
      TLorentzVector jetAK8_p4;
      std::vector<JetAK8> jetsAK8; jetsAK8.clear();
      for (unsigned int i = 0; i <JetsAK8_ID->size(); i++)
      {

        jetAK8_p4.SetPtEtaPhiE(JetsAK8_fCoordinates_fPt[i],JetsAK8_fCoordinates_fEta[i],JetsAK8_fCoordinates_fPhi[i],JetsAK8_fCoordinates_fE[i]);
      	//jetAK8_p4 = JetsAK8->at(i);
      	
      	if ( jetAK8_p4.Pt() < 30 ) continue;
      	if ( abs(jetAK8_p4.Eta() ) > 2.0 ) continue;
      		

      	JetAK8 jetAK8;

      	jetAK8.p4 = jetAK8_p4;

      	jetsAK8.push_back(jetAK8);
      }


      // * 
      // Make plots here
      // *
      

      // *
      // Pre-trigger kinematic plots
      // *
      basic_kinematics(s_sample,"all"); // no trigger requirement
      
      // * 
      // Pass scouting or online trigger 
      // * 
      if (ht < 500) continue;

      basic_kinematics(s_sample,"scouting");

      plotEventShapes(s_sample, "scouting", tracks);

      // * 
      // Pass Offline HT or jet triggers 
      // * 
      if (ht < 1200 && lead_jet_pt < 500) continue;

      basic_kinematics(s_sample,"offline"); 

      plotEventShapes(s_sample, "offline", tracks);

      // Fat jet containment 
      //fatjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 2.0);
      //fatjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 1.8);
      //fatjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 1.5);
      //fatjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 1.3);
      //fatjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 1.0);

      // doesn't work in cmssw
      // Variable radius jet studies
      //VRjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 2000); // param = rho
      //VRjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 1000); // param = rho
      //VRjet_plots(s_sample, "offline" ,tracks, suep_jet, ientry, 500); // param = rho
      
      // * 
      // Dummy event displays 
      // * 
      //if (ientry < 100) {//scouting
      //    eventdisplays_tracks(s_sample,ientry,tracks);
      //    eventdisplays_jets(s_sample,ientry,jets);     
      //}
             
      // * 
      // Pile-up distributions - post offline trigger
      // *
      plotter.Plot1D(Form("%s_trueNint" ,s_sample.c_str()),";True Nint" , TrueNumInteractions  , 20,0,100 );
      plotter.Plot1D(Form("%s_Nint"     ,s_sample.c_str()),";Nint"      , NumInteractions       , 20,0,100 );
      plotter.Plot1D(Form("%s_NPV"      ,s_sample.c_str()),";NPV"       , NVtx                  , 20,0,100 );
             
   }
}

int main(int argc, char* argv[]){

    // defaults 
    std::string tree_name = "TreeMaker2/PreSelection";
    std::string file_name = "root://cmseos.fnal.gov//store/user/kdipetri/SUEP/Production_v0.0/2018/merged_NTUP/SUEP_2018_mMed-750_mDark-2_temp-2_decay-darkPho_13TeV-pythia8_AnalysisTree.root";
    std::string sample_name = "mMed-750_mDark-2_temp-2_decay-generic";
    std::string output_name = "mMed-750_mDark-2_temp-2_decay-generic";

    // Pick file
    // ./doHistos sample_name
    if (argc > 1){
        sample_name = argv[1];
        output_name = argv[1];
        file_name = argv[2];
    }

    std::cout << "Starting SUEP Studies!" << std::endl;

    gROOT->SetBatch();
    gStyle->SetOptStat(0);
    PlotHelper::setPlotStyle();

    TFile *file = TFile::Open(file_name.c_str());
    TTree *tree = (TTree*)file->Get(tree_name.c_str());

	// Figure out if is MC
    bool isMC = 1;
    if (sample_name=="data") isMC = 0;

    // Do analysis
    doHistos analysis(tree,isMC);
    analysis.Loop(sample_name,isMC);

    // Save histograms here
    TFile *output_file = TFile::Open(Form("output/%s.root",output_name.c_str()),"RECREATE");
    c1->SetTickx(true);
    c1->SetTicky(true);
    plotter.DrawAll1D(c1);
    plotter.DrawAll2D(c1, "colz");

}
