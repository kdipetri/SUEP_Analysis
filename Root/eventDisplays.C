#define eventDisplays_cxx


void eventdisplays_tracks(std::string sample_name,Long64_t ievent, std::vector<Track> tracks){

    for (auto track : tracks){
    	plotter.Plot2D(Form("%s_evt%lli_event_display_tracks",sample_name.c_str(),ievent),";eta;phi;pt", track.p4.Eta(), track.p4.Phi(), 100, 3.5,3.5,100,3.5,3.5 , track.p4.Pt());
    }
}

void eventdisplays_jets(std::string sample_name, Long64_t ievent, std::vector<Jet> jets){

    for (auto jet : jets){
    	plotter.Plot2D(Form("%s_evt%lli_event_display_jets",sample_name.c_str(),ievent),";eta;phi;pt", jet.p4.Eta(), jet.p4.Phi(), 100, 3.5,3.5,100,3.5,3.5 , jet.p4.Pt());
    }
}

void eventdisplays_jetAK8s(std::string sample_name, Long64_t ievent, std::vector<JetAK8> jets){

    for (auto jet : jets){
    	plotter.Plot2D(Form("%s_evt%lli_event_display_jetsAK8",sample_name.c_str(),ievent),";eta;phi;pt", jet.p4.Eta(), jet.p4.Phi(), 100, 3.5,3.5,100,3.5,3.5 , jet.p4.Pt());
    }
}

