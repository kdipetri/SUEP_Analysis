#define kinematics_cxx


void scalar_plots(std::string sample, std::string sel){
	plotter.Plot1D(Form("%s_%s_scalar_pt"  ,sample.c_str(), sel.c_str()),";scalar pT"  , scalar.Pt() , 100,0,1000);
    plotter.Plot1D(Form("%s_%s_scalar_eta" ,sample.c_str(), sel.c_str()),";scalar eta" , scalar.Eta(), 100,-3.5,3.5);
    plotter.Plot1D(Form("%s_%s_scalar_phi" ,sample.c_str(), sel.c_str()),";scalar phi" , scalar.Phi(), 100,-3.5,3.5);
    plotter.Plot1D(Form("%s_%s_scalar_m"   ,sample.c_str(), sel.c_str()),";scalar mass", scalar.M()  , 100,0,1000);
}
void track_plots(std::string sample, std::string sel){
    plotter.Plot1D(Form("%s_%s_nchpfs"    ,sample.c_str(),sel.c_str()),";n_{tracks}", npfs   , 100,0,1000);
    plotter.Plot1D(Form("%s_%s_nchpfs_07" ,sample.c_str(),sel.c_str()),";n_{tracks}", npfs_07, 100,0,1000);
    plotter.Plot1D(Form("%s_%s_nchpfs_08" ,sample.c_str(),sel.c_str()),";n_{tracks}", npfs_08, 100,0,1000);
    plotter.Plot1D(Form("%s_%s_nchpfs_09" ,sample.c_str(),sel.c_str()),";n_{tracks}", npfs_09, 100,0,1000);      
    plotter.Plot1D(Form("%s_%s_nchpfs_2"  ,sample.c_str(),sel.c_str()),";n_{tracks}", npfs_2 , 100,0,1000);  
}
void jet_plots(std::string sample, std::string sel){
      plotter.Plot1D(Form("%s_%s_ht"   		,sample.c_str(),sel.c_str()),";H_{T} [GeV]"  , ht         , 20,0,2000 );
      plotter.Plot1D(Form("%s_%s_njets"     ,sample.c_str(),sel.c_str()),";n_{jets}"     , njets      , 20,-0.5,19.5 );
      plotter.Plot1D(Form("%s_%s_leadjetpt" ,sample.c_str(),sel.c_str()),"jet1 pT [GeV]" , lead_jet_pt, 20,0, 1000);
}
void combined_plots(std::string sample, std::string sel){
	plotter.Plot2D(Form("%s_%s_nchpfs_v_ht"   , sample.c_str(),sel.c_str()), ";H_{T} [GeV];n_{tracks}", ht, npfs, 20,0,2000   , 100,0,1000);
	plotter.Plot2D(Form("%s_%s_nchpfs_v_njets", sample.c_str(),sel.c_str()), ";n_{jets};n_{tracks}"   , ht, npfs, 20,-0.5,19.5, 100,0,1000);
}
void basic_kinematics(std::string sample, std::string sel){
	jet_plots(sample,sel);
	track_plots(sample,sel);
	scalar_plots(sample,sel);
	combined_plots(sample,sel);
}