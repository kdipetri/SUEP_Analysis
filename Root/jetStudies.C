#define jetStudies_cxx


using namespace fastjet;

double delta_r(PseudoJet jet1, PseudoJet jet2)
{
    double dphi = abs(jet1.phi() - jet2.phi());
    if (dphi > pi) {dphi = twopi - dphi;}
    double deta = jet1.eta() - jet2.eta();
    return (dphi*dphi + deta*deta);
}
/// the return value is 1 for spherical events and 0 for events linear in r-phi. This function
/// needs the delta R , radius and pT of the jet 
/// defines a ring with thickness deltaR
/// inner radius ra = r-deltaR/2
/// outer radius rb = r+deltaR/2
/// around the jet axist, and pT is the transverse momentum of the whole jet
/// The distance of a given particle i from the jet axis can be expressed in terms of the azimuthal angle ϕi and the pseudorapidity ηi as
/// In the current analysis we used a binning of δr=0.05 and restricted ourselves to the fiducial region r < 0.6 to avoid edge effects
// from https://arxiv.org/pdf/2008.08500.pdf
/// should be
double rho(PseudoJet jet, int R=1.0 , const float& dR=0.1) 
{
    // get constituents
    std::vector<PseudoJet> constituents = jet.constituents();
    if (constituents.size() == 0 ) return -1;
    
    // scalar sum of contituent pT if inside our ring
    float pTsum = 0;
    for (PseudoJet constituent : constituents ) 
    {
      if ( delta_r(jet,constituent) > ( R + dR/2.0 ) ) continue; 
      if ( delta_r(jet,constituent) < ( R - dR/2.0 ) ) continue; 
      pTsum += constituent.pt();
    }
    
    float rho = pTsum / jet.pt() / dR;  
    
    return rho;
}
double width(PseudoJet jet)
{
	float num =0;
	float den =0;
    // get constituents
    std::vector<PseudoJet> constituents = jet.constituents();
    if (constituents.size() == 0 ) return -1;
  
    for (PseudoJet constituent: constituents) 
    {
  
  	    num += delta_r(constituent,jet)*constituent.pt();
  	    den += constituent.pt();
  
  
    }
    return num/den; 
}

void makeAKDisplay(const vector<fastjet::PseudoJet> jets, std::string sample, int size, Long64_t ievent){

	std::vector<TGraph*> graphs;
	//std::vector<TGraph2D> graphs;
	for (unsigned i = 0; i < jets.size(); i++){

		TGraph *graph = new TGraph();
		graph->SetTitle(Form("g_%s_%lli_VR%i",sample.c_str(), ievent, size));
		//TGraph2D *graph = new TGraph2D();

		std::vector<PseudoJet> constituents = jets[i].constituents();
		for (unsigned j = 0; j < constituents.size(); j++) {
      		graph->SetPoint(j,constituents[j].eta(),constituents[j].phi_std());
   		}
   		graph->SetMarkerColor(color.at(i));
   		graph->SetMarkerStyle(21);

		graphs.push_back(graph);
	}
	TMultiGraph *
	mg = new TMultiGraph();
	mg->SetTitle(";#eta; #phi");
	for (auto gr: graphs){
	//for (TGraph2D gr: graphs){
		mg->Add(gr);		
	}

	c1->cd();
	mg->Draw("ap");
	c1->Print(Form("plots/variable_jet_evt_displays/%s_%lli_AK%i.png", sample.c_str(), ievent, size));
}

void fatjet_plots(std::string sample, std::string sel, std::vector<Track> tracks, SUEP_Jet truth_suep_jet, Long64_t ievent, float R=0.8){

	// Get the particles ready
	std::vector<PseudoJet> particles;
	// an event with  particles: px py pz E
	for (auto track : tracks){
		particles.push_back( PseudoJet( track.p4.Px(), track.p4.Py(), track.p4.Pz(), track.p4.E()) );
	}
	
	// choose a jet definition
	int cone = R*10;
	JetDefinition jet_def(antikt_algorithm, R);
	double ghost_maxrap = 2.5; // e.g. if particles go up to y=5
	AreaDefinition area_def(passive_area, GhostedAreaSpec(ghost_maxrap));

	// run the clustering, extract the jets
	//ClusterSequence cs(particles, jet_def);
	ClusterSequenceArea cs(particles, jet_def, area_def);
	std::vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

	// *
	// Make some nice plots...
	// *
	int n_fatjets=0;
	float dR = 6.0;
	PseudoJet suep_jet;
	int max_nconsit=0;

	///if (ievent < 200) makeAKDisplay(jets, sample, cone, ievent);

	for (unsigned i = 0; i < jets.size(); i++) {

		// basic cleaning cuts 
		if ( jets[i].pt() < 30 ) continue; // need some min jet cut
		// some min # tracks cut ? > 1 

		n_fatjets+=1;

		//std::cout << jets[i].area() << std::endl;

		// the basics...
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_pt" , sample.c_str(),sel.c_str(),cone),";jet pt" , jets[i].pt()      , 100, 0, 1000 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_eta", sample.c_str(),sel.c_str(),cone),";jet eta", jets[i].eta()     , 100, -3.5, 3.5 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_phi", sample.c_str(),sel.c_str(),cone),";jet phi", jets[i].phi_std() , 100, -3.5, 3.5 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_m"  , sample.c_str(),sel.c_str(),cone),";jet m"  , jets[i].m() 		, 100, 0, 2000 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_moverpt"  , sample.c_str(),sel.c_str(),cone),";jet mass/pt"  , jets[i].m()/jets[i].pt() , 100, 0, 5 );

		// add plots of other variables here
		TLorentzVector jet_p4;
		jet_p4.SetPtEtaPhiM(jets[i].pt(),jets[i].eta(),jets[i].phi_std(),jets[i].m());
		float dR_tmp= jet_p4.DeltaR(scalar);
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_dRscalar"  , sample.c_str(),sel.c_str(),cone),";jet,scalar dR"  , dR_tmp		, 50, 0, 6.0 );

		//plotter.Plot2D(Form("%s_evt%lli_event_display_jetsAK%i",sample_name.c_str(),ievent,cone),";eta;phi;pt", jets[i].eta(), jets[i].phi_std(), 100, 3.5,3.5,100,3.5,3.5 , jets[i].perp());

		// Constituent based plots
		vector<PseudoJet> constituents = jets[i].constituents();
		for (unsigned j = 0; j < constituents.size(); j++) {
			plotter.Plot1D(Form( "%s_%s_jetsAK%i_constit_pt", sample.c_str(),sel.c_str(),cone),";constit pt", constituents[j].pt(), 100, 0, 100 );

		}
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_nconstit", sample.c_str(),sel.c_str(),cone),";n constit.", constituents.size(), 100, 0, 500 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_width"   , sample.c_str(),sel.c_str(),cone),";jet width" , width(jets[i]), 100, 0, 3.0 );
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_rho"     , sample.c_str(),sel.c_str(),cone),";jet rho" , rho(jets[i]), 100, 0, 1.0 );
		
		if (constituents.size() > max_nconsit) {
			max_nconsit = constituents.size();
			suep_jet = jets[i];
		}
	}
	plotter.Plot1D(Form("%s_%s_jetsAK%i_njets", sample.c_str(),sel.c_str(),cone),";njets", n_fatjets, 20, -0.5, 19.5 );

	// * 
	// Now make suep jet plots
	// * 
	if (max_nconsit > 0){// then we found a suep jet
		// the basics...
		plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_pt" , sample.c_str(),sel.c_str(),cone),";jet pt" , suep_jet.pt()      , 100, 0, 2000 );
		
		if ( suep_jet.pt() > 150 ) {

			plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_eta", sample.c_str(),sel.c_str(),cone),";jet eta", suep_jet.eta()     , 100, -3.5, 3.5 );
			plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_phi", sample.c_str(),sel.c_str(),cone),";jet phi", suep_jet.phi_std() , 100, -3.5, 3.5 );
			plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_m"  , sample.c_str(),sel.c_str(),cone),";jet m"  , suep_jet.m() 		, 100, 0, 2000 );
			plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_moverpt" , sample.c_str(),sel.c_str(),cone),";jet mass/pt" , suep_jet.m()/suep_jet.pt(), 100, 0, 5.0 );
			
			// add plots of other variables here
			TLorentzVector suep_p4;
			suep_p4.SetPtEtaPhiM(suep_jet.pt(),suep_jet.eta(),suep_jet.phi_std(),suep_jet.m());
			float dR_tmp= suep_p4.DeltaR(scalar);
			plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_dRscalar"  , sample.c_str(),sel.c_str(),cone),";jet,scalar dR"  , dR_tmp		, 50, 0, 6.0 );
		
			// Constituent based plots
			vector<PseudoJet> constituents = suep_jet.constituents();
            for (PseudoJet constituent : constituents)
            {
  	            plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_constit_pt", sample.c_str(),sel.c_str(),cone),";constit pt", constituent.pt(), 100, 0, 100 );

            }
			plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_nconstit", sample.c_str(),sel.c_str(),cone),";n constit.", constituents.size(), 100, 0, 500 );
			plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_width"   , sample.c_str(),sel.c_str(),cone),";jet width" , width(suep_jet), 100, 0, 3.0 );		
            for (int step=0; step<15; step++){
			    plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_rho"     , sample.c_str(),sel.c_str(),cone),";jet rho" , rho(suep_jet,step/0.1), 100, 0, 3.0 );		
            }
					
	
			if (cone == 15){
			//
			// COMPARISON WITH TRUTH SUEP "jet"
			//
			//plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_dRtruth", sample.c_str(),sel.c_str(),cone),";dR", truth_suep_jet.p4.DeltaR(suep_p4) , 100, 0, 5.0 );
			//plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_truth_ratio_mass"    , sample.c_str(),sel.c_str(),cone),";reco/truth m "		, suep_jet.m()		 /truth_suep_jet.p4.M() 		, 100, 0, 2 );
			//plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_truth_ratio_pt"      , sample.c_str(),sel.c_str(),cone),";reco/truth pt"		, suep_jet.pt()		 /truth_suep_jet.p4.Pt() 		, 100, 0, 2 );
			//plotter.Plot1D(Form( "%s_%s_jetsAK%i_suep_truth_ratio_nconstit", sample.c_str(),sel.c_str(),cone),";reco/truth nconst"	, (float)constituents.size()/(float)truth_suep_jet.nTruthTracks 	, 100, 0, 2 );
	
			//plotter.Plot2D(Form( "%s_%s_jetsAK%i_suep_truth_mass"    , sample.c_str(),sel.c_str(),cone),";truth m;reco m "			, truth_suep_jet.p4.M() 		, suep_jet.m()	, 100, 0, 2000, 100, 0, 2000 );
			//plotter.Plot2D(Form( "%s_%s_jetsAK%i_suep_truth_pt"      , sample.c_str(),sel.c_str(),cone),";truth pt;reco pt"			, truth_suep_jet.p4.Pt() 		, suep_jet.pt()	, 100, 0, 2000, 100, 0, 2000 );
			//plotter.Plot2D(Form( "%s_%s_jetsAK%i_suep_truth_nconstit", sample.c_str(),sel.c_str(),cone),";truth nconst;reco nconst"	, truth_suep_jet.nTruthTracks 	, constituents.size()	, 100, 0,  500, 100, 0,  500 );				
			}


		}



	}


	return;
}
