#define doHistos_cxx
#include "SUEP_Analysis/doHistos.h"
#include "SUEP_Analysis/PlotHelper.h"
#include "Root/jetStudies.C"
#include "Root/eventDisplays.C"
#include "Root/eventShapes.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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


      // TODO 
      float ht=0;
      float lead_jet_pt=0;
      float njets=0;
      TLorentzVector jet_p4;
      std::vector<Jet> jets; jets.clear();
      for (unsigned int i = 0; i <Jets_ID->size(); i++)
      {
      	if ( Jets->at(i).Pt() < 30 ) continue;
      	if ( abs(Jets->at(i).Eta() ) > 2.0 ) continue;
      		
      	 
      	njets+=1;
      	ht += Jets->at(i).Pt();

      	Jet jet;

      	jet_p4 = Jets->at(i);
      	jet.p4 = jet_p4;

      	if (jet_p4.Pt() > lead_jet_pt ) lead_jet_pt = jet_p4.Pt() ;

      	jets.push_back(jet);
      }
      plotter.Plot1D(Form("%s_testHT",s_sample.c_str()),";H_{T} [GeV]", ht, 20,0,2000 );
      plotter.Plot1D(Form("%s_HT"    ,s_sample.c_str()),";H_{T} [GeV]", HT, 20,0,2000 );
      plotter.Plot1D(Form("%s_njets" ,s_sample.c_str()),";n_{jets}", njets, 20,-0.5,19.5 );

      /*
      Fat jets
      */
      TLorentzVector jetAK8_p4;
      std::vector<JetAK8> jetsAK8; jetsAK8.clear();
      for (unsigned int i = 0; i <JetsAK8_ID->size(); i++)
      {
      	if ( JetsAK8->at(i).Pt() < 30 ) continue;
      	if ( abs(JetsAK8->at(i).Eta() ) > 2.0 ) continue;
      		

      	JetAK8 jetAK8;

      	jetAK8_p4 = JetsAK8->at(i);
      	jetAK8.p4 = jetAK8_p4;

      	jetsAK8.push_back(jetAK8);
      }
      

      /*
      Packing Inner Detector Tracks 
      */
      int npfs=0;
      int npfs_09=0;
      int npfs_08=0;
      int npfs_07=0;
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


      	Track track;

      	trk_p4.SetPtEtaPhiM(Tracks->at(i).Rho(), Tracks->at(i).Eta(), Tracks->at(i).Phi(), 0.13957);
      	track.p4 = trk_p4; 
      	
      	tracks.push_back(track);
      	npfs+=1;
        plotter.Plot1D(Form("%s_chpfs_pt" ,s_sample.c_str()),";chPFs pT", track.p4.Pt(), 100,0,10);
      }      
      plotter.Plot1D(Form("%s_nchpfs" ,s_sample.c_str()),";n_{chpfs}", npfs, 100,0,1000);

      // * 
      // Find the higgs
      // * 
      TLorentzVector scalar;
      for (unsigned int i=0; i < GenParticles_PdgId->size(); i++)
      {
        if (GenParticles_PdgId->at(i)==25) scalar = GenParticles->at(i);
      }
      plotter.Plot1D(Form("%s_scalar_pt"  ,s_sample.c_str()),";scalar pT"  , scalar.Pt() , 100,0,1000);
      plotter.Plot1D(Form("%s_scalar_eta" ,s_sample.c_str()),";scalar eta" , scalar.Eta(), 100,-3.5,3.5);
      plotter.Plot1D(Form("%s_scalar_phi" ,s_sample.c_str()),";scalar phi" , scalar.Phi(), 100,-3.5,3.5);
      plotter.Plot1D(Form("%s_scalar_m"   ,s_sample.c_str()),";scalar mass", scalar.M()  , 100,0,1000);

      // * 
      // Pass HT or jet triggers 
      // * 
      if (ht < 500) continue;
      //if (ht < 1200 && lead_jet_pt < 500) continue;

      // Post trigger higgs plots
      plotter.Plot1D(Form("%s_trig_scalar_pt"  ,s_sample.c_str()),";scalar pT"  , scalar.Pt() , 100,0,1000);
      plotter.Plot1D(Form("%s_trig_scalar_eta" ,s_sample.c_str()),";scalar eta" , scalar.Eta(), 100,-3.5,3.5);
      plotter.Plot1D(Form("%s_trig_scalar_phi" ,s_sample.c_str()),";scalar phi" , scalar.Phi(), 100,-3.5,3.5);
      plotter.Plot1D(Form("%s_trig_scalar_m"   ,s_sample.c_str()),";scalar mass", scalar.M()  , 100,0,1000);

      // Post trigger jet plots
      plotter.Plot1D(Form("%s_trig_testHT",s_sample.c_str()),";H_{T} [GeV]", ht, 20,0,2000 );
      plotter.Plot1D(Form("%s_trig_HT"    ,s_sample.c_str()),";H_{T} [GeV]", HT, 20,0,2000 );
      plotter.Plot1D(Form("%s_trig_njets" ,s_sample.c_str()),";n_{jets}", njets, 20,-0.5,19.5 );
      
      // Post trigger track plots
      plotter.Plot1D(Form("%s_trig_nchpfs"    ,s_sample.c_str()),";n_{chpfs}", npfs, 100,0,1000);
      plotter.Plot1D(Form("%s_trig_nchpfs_07" ,s_sample.c_str()),";n_{chpfs}", npfs_07, 100,0,1000);
      plotter.Plot1D(Form("%s_trig_nchpfs_08" ,s_sample.c_str()),";n_{chpfs}", npfs_08, 100,0,1000);
      plotter.Plot1D(Form("%s_trig_nchpfs_09" ,s_sample.c_str()),";n_{chpfs}", npfs_09, 100,0,1000);

      // Event shapes
      plotEventShapes(s_sample, tracks);
      // Event displays with jets that come out of the box
      //eventdisplays_tracks(s_sample,ientry,tracks);
      //eventdisplays_jets(s_sample,ientry,jets);
      //eventdisplays_jetAK8s(s_sample,ientry,jetsAK8);


      // Trying different jet cone sizes and algorithms here...
      //makeJets(s_sample, ientry, tracks, 0.8);
      //makeJets(s_sample, ientry, tracks, 1.5);
      //makeJets(s_sample, ientry, tracks, 2.0);



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
    if (argc > 1){
        sample_name = argv[1];
        output_name = argv[1];
        file_name = Form("infiles/SUEP_2018_%s_13TeV-pythia8_AnalysisTree.root",sample_name.c_str());
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
