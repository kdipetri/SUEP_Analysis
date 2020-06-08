#define jetStudies_cxx

#include "fastjet/ClusterSequence.hh"

using namespace fastjet;

void makeJets(std::string sample_name, Long64_t ievent, std::vector<Track> tracks){

	vector<PseudoJet> particles;
	// an event with  particles: px py pz E
	for (auto track : tracks){
		particles.push_back( PseudoJet( track.p4.Px(), track.p4.Py(), track.p4.Pz(), track.p4.E()) );
	}
	
	// choose a jet definition
	double R = 0.8;
	int cone = R*10;
	JetDefinition jet_def(antikt_algorithm, R);

	// run the clustering, extract the jets
	ClusterSequence cs(particles, jet_def);
	vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

	// print out some info about reco method
	//std::cout << "Clustered with " << jet_def.description() << std::endl;

	// print the jets
	for (unsigned i = 0; i < jets.size(); i++) {
		//std::cout << "jet " << i << ": "<< jets[i].perp() << " "
		//	<< jets[i].rap() << " " << jets[i].phi() << std::endl;

		plotter.Plot1D(Form( "%s_jetsAK%i", sample_name.c_str(),cone),";jet pt" , jets[i].perp(), 100, 0, 1000 );
		plotter.Plot1D(Form( "%s_jetsAK%i", sample_name.c_str(),cone),";jet eta", jets[i].rap() , 100, -3.5, 3.5 );
		plotter.Plot1D(Form( "%s_jetsAK%i", sample_name.c_str(),cone),";jet phi", jets[i].phi() , 100, -3.5, 3.5 );


		plotter.Plot2D(Form("%s_evt%lli_event_display_jetsAK%i",sample_name.c_str(),ievent,cone),";eta;phi;pt", jets[i].rap(), jets[i].phi(), 100, 3.5,3.5,100,3.5,3.5 , jets[i].perp());

		vector<PseudoJet> constituents = jets[i].constituents();
		for (unsigned j = 0; j < constituents.size(); j++) {

			plotter.Plot1D(Form( "%s_jetsAK%i_constit_pt", sample_name.c_str(),cone),";constit pt", constituents[j].perp(), 100, 0, 1000 );

		}
		plotter.Plot1D(Form( "%s_jetsAK%i_nconstit", sample_name.c_str(),cone),";n constit.", constituents.size(), 100, 0, 500 );

	}
	plotter.Plot1D(Form( "%s_jetsAK%i_njets", sample_name.c_str(),cone),";njets", jets.size(), 100, 0, 500 );



	
	// event displays to debug
	    for (auto track : tracks){
    	plotter.Plot2D(Form("%s_evt%lli_event_display_tracks",sample_name.c_str(),ievent),";eta;phi;pt", track.p4.Eta(), track.p4.Phi(), 100, 3.5,3.5,100,3.5,3.5 , track.p4.Pt());
    }


}
