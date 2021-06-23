import ROOT
from particle import Particle

nevents = 1000
ptcut = 0.6 

# goal - make a histogram of
# as a function of reco track pT

f = ROOT.TFile.Open("infiles/v0.1/SUEP_2018_mMed-400_mDark-2_temp-2_decay-darkPhoHad_13TeV-pythia8_AnalysisTree.root")
tree = f.Get("TreeMaker2/PreSelection")

class particle:
    def __init__(self,pt,eta,phi,mass=0.13957):
        self.pt  = pt 
        self.eta = eta
        self.phi = phi
        self.m  = 0.13957 
        self.vec = self.vec()
        self.match = 0

    def vec(self):
        p4 = ROOT.TLorentzVector.TLorentzVector()
        p4.SetPtEtaPhiM(self.pt,self.eta,self.phi,self.m)
        return p4


def isCharged(pdgId):
    part = Particle.from_pdgid(pdgId)
    if part.charge !=0 : return 1
    else : return 0
#
# define hists
#
h_minDR = ROOT.TH1F("h_minDR",";min dR(reco,track)",100,0,0.3) 
h_allDR = ROOT.TH1F("h_allDR",";all dR(reco,track)",100,0,0.3) 

# efficiency = gen matched signal 
h_truth_ptS = ROOT.TH1F("h_truth_ptS","",100,0,10) 
h_truth_ptL = ROOT.TH1F("h_truth_ptL","",100,0,1000) 
h_truth_eta = ROOT.TH1F("h_truth_eta","",100,-3.5,3.5) 
h_truth_phi = ROOT.TH1F("h_truth_phi","",100,-3.5,3.5) 
h_truth_recod_ptS = ROOT.TH1F("h_truth_recod_ptS","",100,0,10) 
h_truth_recod_ptL = ROOT.TH1F("h_truth_recod_ptL","",100,0,1000) 
h_truth_recod_eta = ROOT.TH1F("h_truth_recod_eta","",100,-3.5,3.5) 
h_truth_recod_phi = ROOT.TH1F("h_truth_recod_phi","",100,-3.5,3.5) 

# fake rate = not gen matched signal
h_reco_ptS = ROOT.TH1F("h_reco_ptS","",100,0,10) 
h_reco_ptL = ROOT.TH1F("h_reco_ptL","",100,0,1000) 
h_reco_eta = ROOT.TH1F("h_reco_eta","",100,-3.5,3.5) 
h_reco_phi = ROOT.TH1F("h_reco_phi","",100,-3.5,3.5) 
h_reco_fake_ptS = ROOT.TH1F("h_reco_fake_ptS","",100,0,10) 
h_reco_fake_ptL = ROOT.TH1F("h_reco_fake_ptL","",100,0,1000) 
h_reco_fake_eta = ROOT.TH1F("h_reco_fake_eta","",100,-3.5,3.5) 
h_reco_fake_phi = ROOT.TH1F("h_reco_fake_phi","",100,-3.5,3.5) 

h_truth_ptS.Sumw2()
h_truth_ptL.Sumw2()
h_truth_eta.Sumw2() 
h_truth_phi.Sumw2() 
h_truth_recod_ptS.Sumw2()
h_truth_recod_ptL.Sumw2()
h_truth_recod_eta.Sumw2() 
h_truth_recod_phi.Sumw2() 

# fake rate = not gen matched signal
h_reco_ptS.Sumw2() 
h_reco_ptL.Sumw2()
h_reco_eta.Sumw2() 
h_reco_phi.Sumw2() 
h_reco_fake_ptS.Sumw2()
h_reco_fake_ptL.Sumw2()
h_reco_fake_eta.Sumw2() 
h_reco_fake_phi.Sumw2() 

nentries = tree.GetEntries()
for entry in range(0,nentries): 
    tree.GetEntry(entry)
    if entry%(nevents/10) == 0 : print(entry)
    
    # Pack up truth particles    
    particles = []
    for i in range(0,len(tree.GenParticles)):

        if tree.GenParticles[i].Pt() < ptcut : continue 
        if abs(tree.GenParticles[i].Eta()) > 2.5 : continue
        if tree.GenParticles_Status[i] != 1: continue
        if isCharged( tree.GenParticles_PdgId[i] ) == 0 : continue
        #print(i)
        
        particles.append(  particle(tree.GenParticles[i].Pt(), 
                            tree.GenParticles[i].Eta(), 
                            tree.GenParticles[i].Phi(),
                            tree.GenParticles[i].M() ) )

    # Pack up reco particles
    tracks = []
    for i in range(0,len(tree.Tracks)):
        if tree.Tracks[i].Rho() < ptcut : continue 
        if abs(tree.Tracks[i].Eta()) > 2.5 : continue
        if tree.Tracks_fromPV0[i] < 2: continue
        if tree.Tracks_matchedToPFCandidate[i] == 0 : continue
        #print(i)
        
        tracks.append(  particle(tree.Tracks[i].Rho(), 
                            tree.Tracks[i].Eta(), 
                            tree.Tracks[i].Phi() ) )

    matched_truth = []
    unmatched_truth = []
    matched_reco = []
    unmatched_reco = []
    for truth in particles: 
        minDR = 9999
        # Fill all truth histos
        h_truth_ptS.Fill(truth.vec.Pt())
        h_truth_ptL.Fill(truth.vec.Pt())
        h_truth_eta.Fill(truth.vec.Eta()) 
        h_truth_phi.Fill(truth.vec.Phi()) 
        for reco in tracks: 
            dR = reco.vec.DeltaR(truth.vec)
            h_allDR.Fill(dR)
            if dR < minDR :  minDR = dR
        h_minDR.Fill(minDR)

        # Fill truth - reco matched histos 
        if minDR < 0.015:
            h_truth_recod_ptS.Fill(truth.vec.Pt())
            h_truth_recod_ptL.Fill(truth.vec.Pt())
            h_truth_recod_eta.Fill(truth.vec.Eta()) 
            h_truth_recod_phi.Fill(truth.vec.Phi()) 
    
    for reco in tracks: 
        minDR = 9999 
        # Fill all reco histos
        h_reco_ptS.Fill(reco.vec.Pt())
        h_reco_ptL.Fill(reco.vec.Pt())
        h_reco_eta.Fill(reco.vec.Eta()) 
        h_reco_phi.Fill(reco.vec.Phi()) 
        for truth in particles:
            dR = reco.vec.DeltaR(truth.vec)
            if dR < minDR :  minDR = dR

        if minDR > 0.015:
        # Fill reco - fake histos
            h_reco_fake_ptS.Fill(reco.vec.Pt())
            h_reco_fake_ptL.Fill(reco.vec.Pt())
            h_reco_fake_eta.Fill(reco.vec.Eta()) 
            h_reco_fake_phi.Fill(reco.vec.Phi()) 
    if entry > nevents: break


output = ROOT.TFile("output/track_matching.root","RECREATE")
output.cd()
h_minDR.Write()
h_allDR.Write()

h_truth_ptS.Write()
h_truth_ptL.Write()
h_truth_eta.Write() 
h_truth_phi.Write() 
h_truth_recod_ptS.Write()
h_truth_recod_ptL.Write()
h_truth_recod_eta.Write() 
h_truth_recod_phi.Write() 

h_reco_ptS.Write()
h_reco_ptL.Write()
h_reco_eta.Write() 
h_reco_phi.Write() 
h_reco_fake_ptS.Write()
h_reco_fake_ptL.Write()
h_reco_fake_eta.Write() 
h_reco_fake_phi.Write() 
