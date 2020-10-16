#define variableJets_cxx

using namespace fastjet;
using namespace contrib;

// a declaration of a function that pretty prints a list of jets


void print_jets (const fastjet::ClusterSequence &, 
                 const vector<fastjet::PseudoJet> &);

void makeVRDisplay(const vector<fastjet::PseudoJet> jets, std::string sample, int size, Long64_t ievent){

	std::vector<TGraph*> graphs;
	//std::vector<TGraph2D> graphs;
	for (unsigned i = 0; i < jets.size(); i++){

		TGraph *graph = new TGraph();
		graph->SetTitle(Form("g_%s_%lli_VR%i",sample.c_str(), ievent, size));
		//TGraph2D *graph = new TGraph2D();

		std::vector<PseudoJet> constituents = jets[i].constituents();
		for (unsigned j = 0; j < constituents.size(); j++) {
      		graph->SetPoint(j,constituents[j].eta(),constituents[j].phi_std());
      		//graph->SetPoint(j,constituents[j].eta(),constituents[j].phi_std(),constituents[j].pt());
   		}
   		graph->SetMarkerColor(color.at(i));
   		graph->SetMarkerStyle(21);

		graphs.push_back(graph);
	}
	TMultiGraph *mg = new TMultiGraph();
	mg->SetTitle(";#eta; #phi");
	for (auto gr: graphs){
	//for (TGraph2D gr: graphs){
		mg->Add(gr);		
	}

	c1->cd();
	mg->Draw("ap");
	c1->Print(Form("plots/variable_jet_evt_displays/%s_%lli_VR%i.png", sample.c_str(), ievent, size));
}

void VRjet_plots(std::string sample, std::string sel, std::vector<Track> tracks, SUEP_Jet truth_suep_jet, Long64_t ievent, double rho=1000.){

	// Get the particles ready
	std::vector<PseudoJet> particles;
	// an event with  particles: px py pz E
	for (auto track : tracks){
		particles.push_back( PseudoJet( track.p4.Px(), track.p4.Py(), track.p4.Pz(), track.p4.E()) );
	}

  	// defining parameters
  	//double rho = 1000.0;
  	double min_r = 0.0;
  	double max_r = 2.0;
  	double ptmin = 5.0;
	
  	VariableRPlugin lvjet_pluginAKT(rho, min_r, max_r, VariableRPlugin::AKTLIKE);
  	fastjet::JetDefinition jet_defAKT(&lvjet_pluginAKT);
  	fastjet::ClusterSequence clust_seqAKT(particles, jet_defAKT);
	
  	// tell the user what was done
  	//std::cout << "# Ran " << jet_defAKT.description() << std::endl;
	
  	// extract the inclusive jets with pt > 5 GeV
  	vector<fastjet::PseudoJet> jets = clust_seqAKT.inclusive_jets(ptmin);
	
  	// print them out
  	//std::cout << "Printing inclusive jets with pt > "<< ptmin <<" GeV\n";
  	//std::cout << "---------------------------------------\n";
  	//print_jets(clust_seqAKT, inclusive_jetsAKT);
  	//std::cout << std::endl;
	//
	//
	//std::cout << "Truth jet " << std::endl;
	//std::cout << truth_suep_jet.p4.Eta() <<  " " << truth_suep_jet.p4.Phi() << " " << truth_suep_jet.p4.Pt() << " " << truth_suep_jet.p4.M() << " " << truth_suep_jet.p4.E() << " " << truth_suep_jet.nTruthTracks << std::endl;
	//std::cout << std::endl;



	// *
	// Make some nice plots...
	// *
	int cone = int(rho);
	int n_fatjets=0;
	float dR = 6.0;
	PseudoJet suep_jet;
	int max_nconsit=0;

	if (ievent < 200) makeVRDisplay(jets, sample, cone, ievent);

	for (unsigned i = 0; i < jets.size(); i++) {

		// basic cleaning cuts 
		if ( jets[i].pt() < 30 ) continue; // need some min jet cut
		// some min # tracks cut ? > 1 

		n_fatjets+=1;

		//std::cout << jets[i].area() << std::endl;

		// the basics...
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_pt" , sample.c_str(),sel.c_str(),cone),";jet pt" , jets[i].pt()      , 100, 0, 1000 );
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_eta", sample.c_str(),sel.c_str(),cone),";jet eta", jets[i].eta()     , 100, -3.5, 3.5 );
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_phi", sample.c_str(),sel.c_str(),cone),";jet phi", jets[i].phi_std() , 100, -3.5, 3.5 );
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_m"  , sample.c_str(),sel.c_str(),cone),";jet m"  , jets[i].m() 		, 100, 0, 2000 );

		// add plots of other variables here
		TLorentzVector jet_p4;
		jet_p4.SetPtEtaPhiM(jets[i].pt(),jets[i].eta(),jets[i].phi_std(),jets[i].m());
		float dR_tmp= jet_p4.DeltaR(scalar);
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_dRscalar"  , sample.c_str(),sel.c_str(),cone),";jet,scalar dR"  , dR_tmp		, 50, 0, 6.0 );

		//plotter.Plot2D(Form("%s_evt%lli_event_display_jetsAK%i",sample_name.c_str(),ievent,cone),";eta;phi;pt", jets[i].eta(), jets[i].phi_std(), 100, 3.5,3.5,100,3.5,3.5 , jets[i].perp());

		// Constituent based plots
		vector<PseudoJet> constituents = jets[i].constituents();
		float num =0;
		float den =0;
		for (unsigned j = 0; j < constituents.size(); j++) {
			TLorentzVector trk_p4;
			trk_p4.SetPtEtaPhiM(constituents[j].pt(),constituents[j].eta(),constituents[j].phi_std(),constituents[j].m());

			num += trk_p4.DeltaR(jet_p4)*trk_p4.Pt();
			den += trk_p4.Pt();

			plotter.Plot1D(Form( "%s_%s_jetsVR%i_constit_pt", sample.c_str(),sel.c_str(),cone),";constit pt", constituents[j].pt(), 100, 0, 100 );

		}
		float width = num/den;
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_nconstit", sample.c_str(),sel.c_str(),cone),";n constit.", constituents.size(), 100, 0, 500 );
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_width"   , sample.c_str(),sel.c_str(),cone),";jet width" , width, 100, 0, 3.0 );
		
		if (constituents.size() > max_nconsit) {
			max_nconsit = constituents.size();
			suep_jet = jets[i];
		}
	}
	plotter.Plot1D(Form("%s_%s_jetsVR%i_njets", sample.c_str(),sel.c_str(),cone),";njets", n_fatjets, 20, -0.5, 19.5 );

	// * 
	// Now make suep jet plots
	// * 
	if (max_nconsit > 0){// then we found a suep jet
		// the basics...
		plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_pt" , sample.c_str(),sel.c_str(),cone),";jet pt" , suep_jet.pt()      , 100, 0, 2000 );
		
		if ( suep_jet.pt() > 150 ) {

			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_eta", sample.c_str(),sel.c_str(),cone),";jet eta", suep_jet.eta()     , 100, -3.5, 3.5 );
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_phi", sample.c_str(),sel.c_str(),cone),";jet phi", suep_jet.phi_std() , 100, -3.5, 3.5 );
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_m"  , sample.c_str(),sel.c_str(),cone),";jet m"  , suep_jet.m() 		, 100, 0, 2000 );
		
			// add plots of other variables here
			TLorentzVector suep_p4;
			suep_p4.SetPtEtaPhiM(suep_jet.pt(),suep_jet.eta(),suep_jet.phi_std(),suep_jet.m());
			float dR_tmp= suep_p4.DeltaR(scalar);
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_dRscalar"  , sample.c_str(),sel.c_str(),cone),";jet,scalar dR"  , dR_tmp		, 50, 0, 6.0 );
		
			//plotter.Plot2D(Form("%s_evt%lli_event_display_jetsAK%i",sample_name.c_str(),ievent,cone),";eta;phi;pt", jets[i].eta(), jets[i].phi_std(), 100, 3.5,3.5,100,3.5,3.5 , jets[i].perp());
		
			// Constituent based plots
			vector<PseudoJet> constituents = suep_jet.constituents();
			float num =0;
			float den =0;
			for (unsigned j = 0; j < constituents.size(); j++) {
				TLorentzVector trk_p4;
				trk_p4.SetPtEtaPhiM(constituents[j].pt(),constituents[j].eta(),constituents[j].phi_std(),constituents[j].m());
		
				num += trk_p4.DeltaR(suep_p4)*trk_p4.Pt();
				den += trk_p4.Pt();
		
				plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_constit_pt", sample.c_str(),sel.c_str(),cone),";constit pt", constituents[j].pt(), 100, 0, 100 );
		
			}
			float width = num/den;
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_nconstit", sample.c_str(),sel.c_str(),cone),";n constit.", constituents.size(), 100, 0, 500 );
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_width"   , sample.c_str(),sel.c_str(),cone),";jet width" , width, 100, 0, 3.0 );		
	
			
			//
			// COMPARISON WITH TRUTH SUEP "jet"
			//
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_dRtruth", sample.c_str(),sel.c_str(),cone),";dR", truth_suep_jet.p4.DeltaR(suep_p4) , 100, 0, 5.0 );
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_truth_ratio_mass"    , sample.c_str(),sel.c_str(),cone),";reco/truth m "		, suep_jet.m()		 /truth_suep_jet.p4.M() 		, 100, 0, 2 );
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_truth_ratio_pt"      , sample.c_str(),sel.c_str(),cone),";reco/truth pt"		, suep_jet.pt()		 /truth_suep_jet.p4.Pt() 		, 100, 0, 2 );
			plotter.Plot1D(Form( "%s_%s_jetsVR%i_suep_truth_ratio_nconstit", sample.c_str(),sel.c_str(),cone),";reco/truth nconst"	, (float)constituents.size()/(float)truth_suep_jet.nTruthTracks 	, 100, 0, 2 );
	
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_dRtruth_rationtrack" , sample.c_str(),sel.c_str(),cone),";dR; reco/truth nconst", truth_suep_jet.p4.DeltaR(suep_p4) , (float)constituents.size()/(float)truth_suep_jet.nTruthTracks , 100, 0, 5.0, 100, 0, 2 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_dRtruth_ntrack" , sample.c_str(),sel.c_str(),cone),";dR; reco/truth nconst", truth_suep_jet.p4.DeltaR(suep_p4) , truth_suep_jet.nTruthTracks , 100, 0, 5.0, 100, 0, 500 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_scalar_Tmass"   , sample.c_str(),sel.c_str(),cone),";scalar m; truth m"  		, scalar.M()					, truth_suep_jet.p4.M() 	, 100, 0, 2000, 100, 0, 2000 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_scalar_Rmass"   , sample.c_str(),sel.c_str(),cone),";scalar m; reco m"  		, scalar.M()					, suep_jet.m()	, 100, 0, 2000, 100, 0, 2000 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_scalar_Tpt"   , sample.c_str(),sel.c_str(),cone),";scalar pt; truth pt"  		, scalar.Pt()					, truth_suep_jet.p4.Pt() 	, 100, 0, 2000, 100, 0, 2000 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_scalar_Rpt"   , sample.c_str(),sel.c_str(),cone),";scalar pt; reco pt"  		, scalar.Pt()					, suep_jet.pt()	, 100, 0, 2000, 100, 0, 2000 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_truth_mass"    , sample.c_str(),sel.c_str(),cone),";truth m;reco m "			, truth_suep_jet.p4.M() 		, suep_jet.m()	, 100, 0, 2000, 100, 0, 2000 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_truth_pt"      , sample.c_str(),sel.c_str(),cone),";truth pt;reco pt"			, truth_suep_jet.p4.Pt() 		, suep_jet.pt()	, 100, 0, 2000, 100, 0, 2000 );
			plotter.Plot2D(Form( "%s_%s_jetsVR%i_suep_truth_nconstit", sample.c_str(),sel.c_str(),cone),";truth nconst;reco nconst"	, truth_suep_jet.nTruthTracks 	, constituents.size()	, 100, 0,  500, 100, 0,  500 );				
			


		}



	}


	return;
}
//----------------------------------------------------------------------
/// a function that pretty prints a list of jets
void print_jets (const fastjet::ClusterSequence & clust_seq,
                 const vector<fastjet::PseudoJet> & jets) {
  
  // sort jets into increasing pt
  vector<fastjet::PseudoJet> sorted_jets = sorted_by_pt(jets);
  
  // label the columns
  printf("%5s %10s %10s %10s %10s %10s %10s\n","jet #", "rapidity",
         "phi", "pt","m","e", "n constituents");
  
  // print out the details for each jet
  for (unsigned int i = 0; i < sorted_jets.size(); i++) {
    int n_constituents = clust_seq.constituents(sorted_jets[i]).size();
    printf("%5u %10.3f %10.3f %10.3f %10.3f %10.3f %8u\n",
           i, sorted_jets[i].rap(), sorted_jets[i].phi_std(),
           sorted_jets[i].perp(),sorted_jets[i].m(),sorted_jets[i].e(), n_constituents);
  }
}
