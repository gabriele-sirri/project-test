void tmva_train()
{
  // DataLoader Example
  // ------------------

  // Declare Factory

  auto outputFile = TFile::Open("TMVAOutputCV.root", "RECREATE");

  TMVA::Factory factory("TMVAClassification", outputFile,
                        "!V:ROC:!Correlations:!Silent:Color:"
                        "!DrawProgressBar:AnalysisType=Classification");

  // Declare DataLoader(s)

  TMVA::DataLoader loader("dataset");

  loader.AddVariable("Length");
  loader.AddVariable("Width");
  loader.AddVariable("Size");
  loader.AddVariable("Conc");
  loader.AddVariable("Conc1");
  loader.AddVariable("Asym");
  loader.AddVariable("M3Long");
  loader.AddVariable("M3Trans");
  loader.AddVariable("Alpha");
  loader.AddVariable("Dist");
  // loader.AddVariable("class");

  // Setup Dataset(s)
  // see TMVA User Guide, Code Example 9: Registration of signal and background
  // text files used for training

  double sigWeight = 1.0;  // overall weight for all signal events
  double bkgWeight = 1.0;  // overall weight for all background events
  loader.SetInputTrees("magic04_signal.data", "magic04_backgr.data", sigWeight, bkgWeight);
  //

  // Apply additional cuts on the signal and background samples (can be
  // different)
  TCut mycuts = "";  // ex: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  TCut mycutb = "";  // ex: TCut mycutb = "abs(var1)<0.5";

  // Tell the dataloader how to use the training and testing events
  //
  // If no numbers of events are given, half of the events in the tree are used
  // for training, and the other half for testing:
  //
  //    dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
  //
  // To also specify the number of testing events, use:
  //
  //    dataloader->PrepareTrainingAndTestTree( mycut,
  //         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V"
  //         );


  loader.PrepareTrainingAndTestTree(mycuts, mycutb, "SplitMode=random:!V");

  // Booking Methods
  // ---------------

  // First dataset

  // Boosted Decision Trees
  factory.BookMethod(
      &loader, TMVA::Types::kBDT, "BDT",
      "!V:NTrees=200:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:"
      "AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType="
      "GiniIndex:nCuts=20");

  // Multi-Layer Perceptron (Neural Network)
  factory.BookMethod(&loader, TMVA::Types::kMLP, "MLP",
                     "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=100:"
                     "HiddenLayers=N+5:TestRate=5:!UseRegulator");

  // Cut optimisation
  factory.BookMethod(
      &loader, TMVA::Types::kCuts, "Cuts",
      "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");

  // Fisher discriminant (same as LD)
  factory.BookMethod(
      &loader, TMVA::Types::kFisher, "Fisher",
      "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:"
      "NbinsMVAPdf=50:NsmoothMVAPdf=10");

  // Train Methods

  factory.TrainAllMethods();

  // Test and Evaluate Methods

  factory.TestAllMethods();
  factory.EvaluateAllMethods();

  // Plot ROC Curve

  // auto c1 = factory.GetROCCurve(&loader);
  // c1->Draw();
}
