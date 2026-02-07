void compare() {
    // =============================================================
    // CONFIGURATION SECTION
    // =============================================================
    // List the files you want to compare. 
    // Based on your screenshot, let's compare the "WN" (Negative?) series.
    const char* fileNames[] = {
        "../root/solid_WP.root", 
        "../root/plate_WP.root", 
        "../root/gyroid_WP.root",
        "../root/schwarzD_WP.root" 
    };
    
    // Legend labels corresponding to the files above
    const char* labels[] = {
        "Solid Block (Control)", 
        "Plate (Equal Mass)", 
        "Gyroid", 
        "SchwarzD"
    };
    
    const int nFiles = 4; // Must match the number of files above
    const char* treeName = "Hits"; 
    const char* varName = "fX";
    
    // Plotting Range (based on your screenshot showing -400 to 400)
    int nBins = 100;
    double xMin = -450; 
    double xMax = 450;

    // Colors for the lines
    int colors[] = {kBlack, kRed, kBlue, kGreen+2};
    // =============================================================

    // 1. Setup Canvas
    TCanvas *c1 = new TCanvas("c1", "Geometry Comparison", 1000, 700);
    gStyle->SetOptStat(0); // Turn off the stats box (it gets messy with 4 lines)
    
    // Create a Legend
    TLegend *leg = new TLegend(0.65, 0.7, 0.9, 0.9);
    leg->SetTextSize(0.03);

    // Create a Stack (helps manage the axes automatically)
    THStack *hs = new THStack("hs", "Beam Profile Comparison (Positive Beam); Position X [mm]; Normalized Counts");

    // 2. Loop through files and plot
    for (int i = 0; i < nFiles; i++) {
        TFile *f = TFile::Open(fileNames[i]);
        if (!f || f->IsZombie()) {
            cout << "Cannot open " << fileNames[i] << endl;
            continue;
        }

        TTree *t = (TTree*)f->Get(treeName);
        if (!t) {
            cout << "Tree 'Hits' not found in " << fileNames[i] << endl;
            continue;
        }

        // Create unique name for histogram
        TString hName = Form("h_%d", i);
        TH1F *h = new TH1F(hName, labels[i], nBins, xMin, xMax);
        
        // Project fX into the histogram
        t->Project(hName, varName);

        // --- STYLING ---
        h->SetLineColor(colors[i]);
        h->SetLineWidth(3);
        h->SetFillStyle(0); // Transparent

        // --- NORMALIZATION (Optional) ---
        // If you want to compare SHAPE (defocusing) regardless of total count:
        if (h->Integral() > 0) {
            h->Scale(1.0 / h->Integral());
        }

        // Detach from file so it stays when file closes
        h->SetDirectory(0);
        
        hs->Add(h);
        leg->AddEntry(h, labels[i], "l");
        
        f->Close();
    }

    // 3. Draw
    // "nostack" ensures they are overlaid, not stacked on top of each other
    // "hist" ensures they are drawn as smooth lines, not error bars
    hs->Draw("nostack hist c"); 
    leg->Draw();
    
    c1->SetGrid();
}