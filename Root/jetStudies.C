#define jetStudies_cxx


using namespace fastjet;


void fatjet_plots(std::string sample, std::string sel, std::vector<Track> tracks, Long64_t ievent, float R=0.8){

	// Get the particles ready
	std::vector<PseudoJet> particles;
	// an event with  particles: px py pz E
	for (auto track : tracks){
		particles.push_back( PseudoJet( track.p4.Px(), track.p4.Py(), track.p4.Pz(), track.p4.E()) );
	}
	
	// choose a jet definition
	int cone = R*10;
	JetDefinition jet_def(antikt_algorithm, R);

	// run the clustering, extract the jets
	ClusterSequence cs(particles, jet_def);
	std::vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

	// *
	// Make some nice plots...
	// *
	int n_fatjets=0;
	float dR = 6.0;
	for (unsigned i = 0; i < jets.size(); i++) {

		// basic cleaning cuts 
		if ( jets[i].pt() < 30 ) continue; // need some min jet cut
		// some min # tracks cut ? > 1 

		n_fatjets+=1;

		// the basics...
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_pt" , sample.c_str(),sel.c_str(),cone),";jet pt" , jets[i].pt()      , 100, 0, 1000 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_eta", sample.c_str(),sel.c_str(),cone),";jet eta", jets[i].eta()     , 100, -3.5, 3.5 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_phi", sample.c_str(),sel.c_str(),cone),";jet phi", jets[i].phi_std() , 100, -3.5, 3.5 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_m"  , sample.c_str(),sel.c_str(),cone),";jet m"  , jets[i].m() 		, 100, 0, 2000 );

		// add plots of other variables here
		TLorentzVector jet_p4;
		jet_p4.SetPtEtaPhiM(jets[i].pt(),jets[i].eta(),jets[i].phi_std(),jets[i].m());
		float dR_tmp= jet_p4.DeltaR(scalar);
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_dRscalar"  , sample.c_str(),sel.c_str(),cone),";jet,scalar dR"  , dR_tmp		, 50, 0, 6.0 );

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

			plotter.Plot1D(Form( "%s_%s_jetsAK%i_constit_pt", sample.c_str(),sel.c_str(),cone),";constit pt", constituents[j].pt(), 100, 0, 100 );

		}
		float width = num/den;
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_nconstit", sample.c_str(),sel.c_str(),cone),";n constit.", constituents.size(), 100, 0, 500 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_width"   , sample.c_str(),sel.c_str(),cone),";jet width" , width, 100, 0, 3.0 );
		
	}
	plotter.Plot1D(Form("%s_%s_jetsAK%i_njets", sample.c_str(),sel.c_str(),cone),";njets", n_fatjets, 20, -0.5, 19.5 );

	return;
}
