#define doHistos_cxx
#include "SUEP_Analysis/doHistos.h"
#include "SUEP_Analysis/PlotHelper.h"
#include "Root/jetStudies.C"
#include "Root/eventDisplays.C"
#include "Root/eventShapes.C"
#include "Root/kinematics.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Jet get_ISR_jet(std::vector<Jet> jets){

  Jet isr_jet;

  if ( jets.size()==1 ) return isr_jet;

  float lead_pt = 100;
  for (auto jet : jets)
  {
    if ( jet.isolation < 0.05 && jet.p4.Pt() > lead_pt ) {
      lead_pt = jet.p4.Pt();
      isr_jet = jet;
    }
  }
  return isr_jet;

}
void doHistos::Loop(std::string s_sample,bool isMC)
{
	//////////////////////////////////////////////////////
    // Loops over the input ntuple from a given sample  //
    //////////////////////////////////////////////////////

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << " Analyzing Tree : " << s_sample << " with " << nentries << " entries" << std::endl;


   // disable all branches
   fChain->SetBranchStatus("*",0);
   // only activate branches that are used (faster)
   std::vector<string> branches_used{
      "HT",
      "Jets",
      "Jets_ID",
      "Jets_multiplicity",
      "Jets_chargedMultiplicity",
      "JetsAK8",
      "JetsAK8_ID",
      "Tracks",
      "Tracks_fromPV0",
      "Tracks_matchedToPFCandidate",
      "GenParticles",
      "GenParticles_PdgId",
   };
   for(const auto& branch : branches_used) fChain->SetBranchStatus(branch.c_str(),1);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if (ientry%1000==0) std::cout << "Processed " << ientry << " events!" << std::endl;


      // * 
      // Find the higgs
      // * 
      for (unsigned int i=0; i < GenParticles_PdgId->size(); i++)
      {
        if (GenParticles_PdgId->at(i)==25) scalar = GenParticles->at(i);
      }


      /*
      Packing Inner Detector Tracks 
      */
      unsigned int index=0;
      npfs=0;
      npfs_09=0;
      npfs_08=0;
      npfs_07=0;
      npfs_2=0; // for phase 2 question
      TLorentzVector trk_p4;
      std::vector<Track> tracks; tracks.clear();
      for (unsigned int i = 0; i <Tracks_fromPV0->size(); i++)
      {

      	if (abs(Tracks->at(i).Eta()) > 2.5) continue;
      	if (Tracks_fromPV0->at(i) < 2) continue;
      	if (Tracks_matchedToPFCandidate->at(i) == 0) continue;
        if (Tracks->at(i).Rho() > 0.7) npfs_07 +=1;
        if (Tracks->at(i).Rho() > 0.8) npfs_08 +=1;
        if (Tracks->at(i).Rho() > 0.9) npfs_09 +=1;
        if (Tracks->at(i).Rho() < 1.0) continue; // pT cut 1 GeV, to be optimized
        if (Tracks->at(i).Rho() > 2.0) npfs_2 +=1;
      	Track track;

      	trk_p4.SetPtEtaPhiM(Tracks->at(i).Rho(), Tracks->at(i).Eta(), Tracks->at(i).Phi(), 0.13957);
      	track.p4 = trk_p4; 
      	
      	tracks.push_back(track);
      	npfs+=1;
        plotter.Plot1D(Form("%s_chpfs_pt" ,s_sample.c_str()),";chPFs pT", track.p4.Pt(), 100,0,10);
      }
      // Post track plots
      
    
      
      //
      // Jets
      // * 
      index=0;
      ht=0;
      njets=0;
      lead_jet_pt=0;
      float max_dphi = 0;
      Jet lead_jet; 
      Jet true_isr_jet; // doesn't really work
      TLorentzVector jet_p4;
      std::vector<Jet> jets; jets.clear();
      for (unsigned int i = 0; i <Jets_ID->size(); i++)
      {
        if ( Jets->at(i).Pt() < 30 ) continue;
        if ( abs(Jets->at(i).Eta() ) > 2.0 ) continue;
          
        njets+=1;
        ht += Jets->at(i).Pt();

        Jet jet;
        jet.index = index;

        jet_p4 = Jets->at(i);
        jet.p4 = jet_p4;

        jet.multiplicity = Jets_multiplicity->at(i);
        jet.chargedMultiplicity = Jets_chargedMultiplicity->at(i);

        if (jet_p4.Pt() > lead_jet_pt ) lead_jet_pt = jet_p4.Pt() ;

        TLorentzVector num; 
        for (auto track : tracks){
           if (jet.p4.DeltaR(track.p4) > 1.0 ) continue;
           if (jet.p4.DeltaR(track.p4) < 0.4 ) continue;
           num += track.p4;
        }
        
        jet.isolation = (num.Pt())/jet.p4.Pt(); // fake

        jet.scalar_dPhi = abs(jet.p4.DeltaPhi(scalar));
        jet.scalar_dR   = jet.p4.DeltaR(scalar);

        float min_dR = 6.0; 
        for (auto jet2 : jets){
          if ( jet.index==jet2.index) continue;
          float tmp_dR   = jet.p4.DeltaR(jet2.p4);
          if (tmp_dR   < min_dR  ) min_dR = tmp_dR;
        }
        jet.min_dR = min_dR;
        
        //plotter.Plot1D(Form("%s_trig_jet_scalar_dPhi",s_sample.c_str()),";jet,scalar dR"  , abs(jet.p4.DeltaPhi(scalar)), 50, 0, 6.0 );
        //plotter.Plot1D(Form("%s_trig_jet_scalar_dR"  ,s_sample.c_str()),";jet,scalar dPhi", abs(jet.p4.DeltaR(scalar))  , 50, 0, 6.0 );

        // Leading jet
        if ( jet.p4.Pt() > lead_jet_pt ) {
          lead_jet_pt  = jet.p4.Pt();
          lead_jet     = jet; 
        }
        // ISR jet
        if ( jet.scalar_dPhi > max_dphi ) {
          max_dphi = jet.scalar_dPhi;
          true_isr_jet = jet;
        }

        jets.push_back(jet);
        index+=1;
      }
      Jet isr_jet = get_ISR_jet(jets);

      /*
      Fat jets
      */
      TLorentzVector jetAK8_p4;
      std::vector<JetAK8> jetsAK8; jetsAK8.clear();
      index=0;
      for (unsigned int i = 0; i <JetsAK8_ID->size(); i++)
      {
        if ( JetsAK8->at(i).Pt() < 30 ) continue;
        if ( abs(JetsAK8->at(i).Eta() ) > 2.0 ) continue;
    
        JetAK8 jetAK8;

        jetAK8_p4 = JetsAK8->at(i);
        jetAK8.p4 = jetAK8_p4;

        jetAK8.index = index;

        jetsAK8.push_back(jetAK8);
        index+=1;
      }

      // Make pre-trigger kinematic plots
      basic_kinematics(s_sample,"all"); // no trigger requirement

      // For a little speedup
      if (ht < 500) continue;

      // old
      // Trying different jet cone sizes and algorithms here...
      //makeJets(s_sample, ientry, tracks, 0.8);
      //makeJets(s_sample, ientry, tracks, 1.5);
      //makeJets(s_sample, ientry, tracks, 2.0); // for hemisphere analysis

      // * 
      // Pass scouting or offline triggers
      // * 

      if (ht > 500){// Scouting stream 

        basic_kinematics(s_sample,"scouting");
  
        plotEventShapes(s_sample, "scouting", tracks);

        fatjet_plots(s_sample, "scouting" ,tracks, ientry, 2.0);

      }
      if (ht > 1200 || lead_jet_pt > 500) {

        basic_kinematics(s_sample,"offline");
  
        plotEventShapes(s_sample, "offline", tracks);

        fatjet_plots(s_sample, "offline" ,tracks, ientry, 2.0);

      }
      

      // * 
      // Event displays with jets that come out of the box
      // * 
      if (ientry < 100) {//scouting
        eventdisplays_tracks(s_sample,ientry,tracks);
        eventdisplays_jets(s_sample,ientry,jets);     
        //eventdisplays_jetAK8s(s_sample,ientry,jetsAK8);   
      }

      //


      //
      // Testing ISR jet tagging
      //
      std::string sel = "suep";
      for (auto jet : jets){
        if ( jet.index == true_isr_jet.index ) sel = "isr"; 
        else sel="suep";

        //std::cout << jet.index <<  " (sel,pt,iso,mult) = (" << sel << " , " << jet.p4.Pt() << " , " << jet.isolation << " , " << jet.multiplicity << " ) " << std::endl;
        
        plotter.Plot1D(Form("%s_trig_%sjet_pt"          ,s_sample.c_str(),sel.c_str()),";jet pt"          , jet.p4.Pt()     , 50,0, 1000 );
        plotter.Plot1D(Form("%s_trig_%sjet_scalar_dR"   ,s_sample.c_str(),sel.c_str()),";jet,scalar dR"   , jet.scalar_dR   , 50, 0, 6.0 );
        plotter.Plot1D(Form("%s_trig_%sjet_scalar_dPhi" ,s_sample.c_str(),sel.c_str()),";jet,scalar dPhi" , jet.scalar_dPhi , 50, 0, 6.0 );
        plotter.Plot1D(Form("%s_trig_%sjet_isolation"   ,s_sample.c_str(),sel.c_str()),";jet isolation"   , jet.isolation   , 50, 0, 1.0 );
        plotter.Plot1D(Form("%s_trig_%sjet_multiplicity",s_sample.c_str(),sel.c_str()),";jet multiplicity", jet.multiplicity, 50, 0, 100 );
        plotter.Plot1D(Form("%s_trig_%sjet_min_dR"      ,s_sample.c_str(),sel.c_str()),";jet,jet min dR"  , jet.min_dR      , 50, 0, 6.0 );

      }


      // Try boosting - fails... bad ISR selection
      //std::vector<Track> tracks_boosted; tracks_boosted.clear();
      //if ( isr_jet.p4.Pt() > 100 ) {// if ISR jet, boost tracks
      //
      //  for (auto track : tracks){
      //
      //    // remove tracks in delta R < 0.4 of ISR jet
      //    if (track.p4.DeltaR(isr_jet.p4) < 0.4) continue;
      //
      //    // boost other jets into seup restfroame
      //    Track track_boosted = track; // copy other params
      //    TVector3 threevec = track.p4.Vect() - isr_jet.p4.Vect();
      //    track_boosted.p4.SetPtEtaPhiM(threevec.Pt(),threevec.Eta(),threevec.Phi(),0.13957);
      //    tracks_boosted.push_back(track_boosted);
      //
      //  }
      //
      //}
      //else tracks_boosted=tracks;
      //std::cout << tracks.size() << " " << tracks_boosted.size() << std::endl;
      //plotEventShapes(s_sample, "boosted", tracks_boosted);



      // Pflow candidates
      // Scan pT threshold 
      // Some Pflow cut...


      // Pile-up distributions - post trigger
      plotter.Plot1D(Form("%s_trueNint" ,s_sample.c_str()),";True Nint" , TrueNumInteractions	, 20,0,100 );
      plotter.Plot1D(Form("%s_Nint"    	,s_sample.c_str()),";Nint"		, NumInteractions 		, 20,0,100 );
      plotter.Plot1D(Form("%s_NPV"    	,s_sample.c_str()),";NPV"		, NVtx					, 20,0,100 );

   }
}

int main(int argc, char* argv[]){

    // defaults 
    std::string tree_name = "TreeMaker2/PreSelection";
    std::string file_name = "infiles/SUEP_2018_mMed-750_mDark-2_temp-2_decay-generic_13TeV-pythia8_AnalysisTree.root";
    std::string sample_name = "mMed-750_mDark-2_temp-2_decay-generic";
    std::string output_name = "mMed-750_mDark-2_temp-2_decay-generic";

    // Pick file
    // ./doHistos sample_name
    if (argc > 2){
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
    TFile *output_file;
    output_file = TFile::Open(Form("output/%s.root",output_name.c_str()),"RECREATE");
    c1->SetTickx(true);
    c1->SetTicky(true);
    plotter.DrawAll1D(c1);
    plotter.DrawAll2D(c1, "colz");

}
