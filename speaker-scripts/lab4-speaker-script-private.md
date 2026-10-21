# Lab 4 — Speaker Script

*Companion of lab4.md (17 slides) and lab4_tmva.md (Talk C).*

## How to use this script

- **SAY** = read aloud. **IT** = riassunto per te. **\[PAUSE\]** = respira. **\[DO\]** = azione. In grassetto il messaggio chiave.
- Numeri di slide = quelli di lab4.md, divisori inclusi.
- Oggi: HistFactory (Talk A, B e hands-on A, B), poi **Talk C + demo guidata TMVA** (non da consegnare) e **35 minuti di lab aperto**. Nessun progetto, nessuno showcase.
- Consegna: nel Lab 4 si consegnano **entrambi** i notebook (A e B) su Virtuale. In totale: 2 su 3 nei Lab 1–3, più A e B del Lab 4.
- Prima del lab: prova che la demo TMVA giri (serve ROOT con TMVA, e il compilatore per gli esempi del ROOT Team); controlla che il tuo portatile mostri un notebook da Codespaces.

## New phrases for today

| Situation | Say | IT |
| --- | --- | --- |
| Run | Please run the notebook from the top. | Eseguite il notebook dall'inizio |
| Compare | Compare your number with the check cell. | Confrontate col numero della cella check |
| Cut | Which cut would you choose, and why? | Quale taglio scegliereste? |
| Move | Change the yields. Does the optimal cut move? | Cambiate le rese: il taglio ottimale si sposta? |
| Hand-in | Please upload both notebooks on Virtuale. | Caricate i due notebook su Virtuale |
| Feedback | Please fill the short form before you leave. | Compilate il modulo prima di uscire |

## Pronunciation help

| Word | Say it like |
| --- | --- |
| HistFactory | HIS-to-FAK-tuh-ree |
| modifier | MOD-i-fy-er |
| template | TEM-plet |
| interpolation | in-TUR-puh-LAY-shun |
| overall | OH-ver-all |
| luminosity | loo-mi-NOS-i-tee |
| efficiency | ih-FISH-un-see |
| purity | PYOOR-ih-tee |
| Asimov | AZ-ih-mov |
| boosted | BOO-stid |
| lambda | LAM-duh |
| just-in-time | just in TIME (JIT = jit) |
| multithreaded | MUL-ti-THRED-id |
| anonymous | uh-NON-i-mus |

---

## 0:00 — Recap (slides 1–3, 5 min)

**SAY (slide 1):** Good morning, and welcome to the last lab. This is Lab 4: HistFactory, and event selection. Today we have three parts. In the first two hours, we build a binned model with HistFactory, and we use RDataFrame. Then, a short talk and a demo on TMVA, to select events. At the end, an open lab, to finish your notebooks. \[PAUSE\] Today you hand in both notebooks, A and B.

*IT: ultimo lab; HistFactory, poi TMVA (demo), poi lab aperto; oggi si consegnano A e B.*

**\[DO\] slide 2 — Recap**

**SAY:** Three short questions. Please answer in pairs. One: constraint term, or auxiliary measurement. Which one do you use, and when? Two: one source of systematic uncertainty moves three channels. How many nuisance parameters do you need? Three: which tool for a discovery, which for an upper limit?

**Expected answers:**

1. Measurement if you have the control data; constraint if you only have its result.
2. One: a fully correlated source needs one nuisance parameter. In general, the rank of the covariance matrix.
3. Discovery: hypothesis test, q zero. Upper limit: CLs with the hypothesis test inverter.

**\[DO\] slide 3 — Schedule**

**SAY:** This is our plan. Two talks and two hands-on parts on HistFactory. At eleven fifteen, a third talk, on TMVA, and a guided demo. At ten past twelve, the open lab: you finish the notebooks, and you ask me everything. At a quarter to one, the wrap-up and the feedback form.

---

## 0:05 — Talk A: From histograms to a likelihood (slides 4–8, 20 min)

**\[DO\] slide 5 — The binned model**

**SAY:** We start from a histogram. We have bins. In each bin, the observed number of events, n b, is a Poisson variable. The expected number, nu b, depends on the parameters. The likelihood is the product over all bins, times the constraint terms. \[PAUSE\] The expected number is a sum over samples. Each sample is a template histogram, multiplied by modifiers. A modifier says how a parameter changes the template. **This is the extended marked Poisson model of Lab 1: the shape is a histogram, and the nuisance parameters are the modifiers.** HistFactory is the recipe that builds this likelihood from histograms.

*IT: verosimiglianza binnata = prodotto di Poisson per bin × vincoli; ν = template × modificatori.*

**\[DO\] slide 6 — Building blocks**

**SAY:** Four levels. The measurement: the whole analysis. The channel: a region with its own data, for example a signal region and a control region. The sample: one process, with a template. And the modifiers. \[PAUSE\] The output is a workspace with a ModelConfig. **It is exactly the same object that you used in Lab 3.** So everything you know from RooStats works now.

*IT: Measurement > Channel > Sample > modifiers. Output = workspace + ModelConfig.*

**\[DO\] slide 7 — Modifiers**

**SAY:** Look at the table. Four modifiers. NormFactor: a free scale factor, without constraint. We use it for the signal strength mu. And also for a background that is normalised by a control region. OverallSys: scales the sample by one plus or minus epsilon, with a Gaussian constraint. For luminosity, for example. HistoSys: two histograms, up and down. The shape morphs between them. For energy scale. StatError: one nuisance parameter for each bin, for the finite statistics of the simulation. \[PAUSE\] **A NormFactor with the same name in two channels is shared. It is a control-region measurement. The same idea as the on/off problem, with histograms.**

*IT: 4 modificatori; NormFactor condiviso tra canali = regione di controllo.*

**\[DO\] slide 8 — Same likelihood, different file format**

**SAY:** One remark. In ROOT, we build the model with the C++ or Python API, or with hist2workspace. In pyhf, the same model is written in JSON, in pure Python. The two implement the same likelihood, and the LHC experiments cross-check them. **What you learn today is what ATLAS and CMS use to publish their models.**

---

## 0:25 — Hands-on A: One toy, three ways (slides 9–10, 40 min)

**\[DO\] slide 10 — Exercise A**

**SAY:** Exercise A uses the course of the ROOT Team. It is in the folder third party. The files are theirs, with their licence, and the notebook explains it. \[PAUSE\] There is one toy simulator, one dataset, and three fits of the same data. Step one: run the five macros. They are written in C++ and compiled just in time, but we run them from the notebook. Step two: read the file physics dot h. Where do mu and theta act? Is the simulation run again? Step three: compare the fits. Step four: from the nuisance parameter alpha, compute theta, and compare with the true value, one point three. Step five: slice and profile of mu, as in Lab 2. \[PAUSE\] Forty minutes. If a macro fails, tell me immediately.

*IT: eseguire le 5 macro dal notebook; domande su physics.h; theta^ = 1 + α·0.4 vs 1.3; slice vs profile.*

**While walking around:**

- Did all the macros run? Which one failed?
- Where is the weight of the event computed?
- Why is the simulation never run again for a different theta?
- What is the correlation between mu and alpha?

**At the end (SAY):** Let's stop. \[PAUSE\] Key message: **in this toy, the physics parameters act only through weights. We simulate once, and we reweight.** This is very common in real analyses, for example for scale factors. And the nuisance parameter widens the uncertainty on mu: the profile is wider than the slice.

---

## 1:05 — BREAK (10 min)

**SAY:** Let's take a break. We restart at 10:15.

---

## 1:15 — Talk B: RDataFrame Vary and modern C++ (slides 11–13, 15 min)

**\[DO\] slide 12 — Systematic variations in one event loop**

**SAY:** Where do the up and down histograms come from? From RDataFrame, with a function called Vary. \[PAUSE\] Look at the code. We define a column, here the weight. And we say: for the variations theta up and theta down, the column has these other values. Then we ask for a histogram. RDataFrame gives us the nominal histogram, and a map with the varied histograms. **All in one event loop.** The cost is almost the same as a single loop, not one loop for each variation. And the varied histograms are exactly the inputs of the HistoSys modifier.

*IT: Vary: istogrammi nominale + varianti in un solo loop. Sono gli input dei HistoSys.*

**\[DO\] slide 13 — Why modern C++**

**SAY:** Why do I insist on modern C++? \[PAUSE\] Look at this code. We declare a C++ function from Python. The interpreter compiles it just in time. Then we use it in a Define. We have the speed of C++, from the comfort of Python. And a Python loop over events does not scale. RDataFrame does. \[PAUSE\] Also: the code of the experiments is C++. If you want to work in a collaboration, you must be able to read it. **Python is the glue. C++ is the engine.** There is an optional notebook that measures the speed: Python loop, RDataFrame, and multithreaded RDataFrame.

*IT: JIT, lambda, RVec; un loop Python non scala; il codice degli esperimenti è C++. Notebook opzionale per i tempi.*

---

## 1:30 — Hands-on B: HistFactory on CMS H to 4 leptons (slides 14–16, 35 min)

**\[DO\] slide 15 — The case**

**SAY:** The case: CMS Open Data, Higgs to four leptons. Real data. Look at the table. The signal region: thirty-seven bins from seventy to one hundred eighty-one GeV. Data: one hundred two events. And the control region: one single bin, with everything above one hundred eighty-one GeV. Data: one hundred seventy-six events. \[PAUSE\] **The signal is a parameter, mu. The ZZ background has a free normalisation, shared by the two channels. The control region measures it.**

*IT: dati reali CMS; SR 37 bin, 102 eventi; CR 1 bin, 176 eventi; kZZ condiviso.*

**\[DO\] slide 16 — Exercise B**

**SAY:** Exercise B. Step one: build the measurement. Two channels, four samples. The signal has the NormFactor mu. The ZZ has the NormFactor k ZZ, and it is the same name in both channels. Step two: fit. Then compare with a fit without the control region. Step three: the interval on mu and the significance. Step four: add a five percent luminosity uncertainty. \[PAUSE\] **Attention: five percent is an illustrative size, not the CMS value. In a real analysis, use a number you can justify.** Step five: slice and profile of mu, and the correlation between mu and k ZZ. Thirty-five minutes.

*IT: B1 Measurement, B2 con/senza CR, B3 interval/Z, lumi 5% (illustrativo!), B4 anatomia. Attesi: μ≈0.98, kZZ≈0.90, Z≈3.5, \[0.62,1.43\]; senza CR μ≈0.92, Z≈3.3.*

**While walking around:**

- Is the NormFactor named exactly the same in the two channels?
- Did you set the histograms to be owned by HistFactory?
- What does the check say?
- Why is the correlation between mu and k ZZ small?

**At the end (SAY):** Let's look at the results. The control region says that k ZZ is about zero point nine. \[PAUSE\] The simulation overestimates the ZZ background by about ten percent. With less background, the same data need more signal: mu goes from zero point nine two to zero point nine eight. And the significance increases from three point three to three point five. **This is the value of a control region.** And three point five sigma is evidence, not a discovery.

---

## 2:05 — BREAK (10 min)

**SAY:** Let's take a short break. We restart at 11:15 with a new topic: how to select events.

---

## 2:15 — Talk C: Selecting events with TMVA (lab4\_tmva.md, 20 min)

*Slides: lab4\_tmva.md. This is a different file: open it before the break.*

**\[DO\] slide 2 — The problem**

**SAY:** Until now, we had the events already selected. Today, a short look at how to select them. The data are from the MAGIC telescope: gamma rays are the signal, hadrons are the background. Ten image parameters for each event. \[PAUSE\] A cut on one variable is not enough, so we combine them. Rectangular cuts are simple and transparent. Fisher is a linear combination. And the BDT, the boosted decision tree, is the workhorse of high-energy physics. TMVA trains, tests, and compares them, and makes the plots for us.

*IT: problema gamma/adroni, 10 variabili, tagli rettangolari, Fisher, BDT; TMVA fa training, test e grafici.*

**\[DO\] slide 3 — Vocabulary**

**SAY:** Machine-learning people use different words. Recall is the signal efficiency. False-positive rate is the background efficiency. One minus it is the background rejection. Precision is the purity. And accuracy, we do not use it. \[PAUSE\] **The efficiencies do not depend on the signal-to-background ratio. The purity does.** That is why in physics we quote the two efficiencies, and the expected yields, separately.

*IT: tabella ML ↔ fisica; efficienze indipendenti da S/B, purezza no.*

**\[DO\] slides 4–5 — ROC and the naive figure of merit**

**SAY:** The ROC curve plots the background rejection against the signal efficiency. Every point is a cut on the classifier response. So, different cuts are different working points of the same classifier. Which is the best? **It depends on what you want to measure.** Choose the cut by optimising the final significance, not the accuracy. \[PAUSE\] The naive figure of merit is s over square root of b. It is valid for s much smaller than b, and large b. But when the background goes to zero, it explodes. Example: three signal events, background of zero point one. s over square root of b is about nine and a half, from three events. It is pathological.

*IT: ROC, working point; s/sqrt(b) patologico a basso fondo (3 eventi, b=0.1 → 9.5).*

**\[DO\] slide 6 — The Asimov significance**

**SAY:** The Asimov significance comes from the profile-likelihood ratio, with b known. It is the paper of Cowan, Cranmer, Gross and Vitells, the same one I asked you to read. It is always smaller than or equal to s over square root of b. It behaves well for small b, and for s much smaller than b it is the same as the naive formula. \[PAUSE\] One limit: it ignores the uncertainty on b. In Lab 3 you know how to include it, as a nuisance parameter.

*IT: Z_A da profile likelihood, sempre ≤ s/sqrt(b); limite: ignora l'incertezza su b (Lab 3).*

**\[DO\] slides 7–8 — What the notebook does, take-home messages**

**SAY:** Now the notebook. It converts the data to ROOT trees, it trains a BDT and a Fisher with TMVA, it reads the test tree, and it scans the cut: efficiencies, purity, the two significances. Then it finds the optimal cut for two different sets of expected yields. **The optimal cut moves.** \[PAUSE\] Three messages to remember. Translate the words: recall is efficiency, precision is purity. Optimise the physics figure of merit, with the expected yields. And the efficiency is a systematic: model it as a nuisance parameter.

*IT: cosa fa il notebook; 3 messaggi: tradurre il vocabolario, ottimizzare la figura di merito fisica, efficienza = sistematica.*

---

## 2:35 — Guided demo C: TMVA on MAGIC (35 min)

**SAY:** Please open demo C, tmva magic demo, in the lab four folder. We go step by step. It is not handed in: the questions at the end are for discussion. \[PAUSE\] Run the cells with me. The training takes a short time. While it runs, look at the TMVA plots: the ROC curve, and the response of signal and background.

*IT: demo guidata, non da consegnare; eseguire insieme; mentre il training gira, guardare i grafici TMVA.*

**Milestones to follow in the room:**

- Data converted, two ROOT files created: signal and background.
- BDT and Fisher trained: the file TMVA magic dot root exists.
- The scan runs: the optimal cut is printed for s over square root of b and for Z A.
- The check cells say PASS.

**Questions for the discussion at the end (from the notebook):**

- Why does s over square root of b push the cut to extreme values when the background efficiency goes to zero, and what does Z A do instead?
- Change the illustrative yields. How do the optimal cut and the two significances move?
- The cut was optimised on the test sample, then used on data. What bias does it introduce, and how do you avoid it?
- Which systematic uncertainty would you add to the model, and as which kind of nuisance parameter?

---

## 3:10 — Open lab (35 min)

**SAY:** Now thirty-five minutes of open lab. Finish Exercise A and Exercise B. Today you hand in both. \[PAUSE\] Run each notebook from the top, and check that every check says PASS. If a check fails, call me. If you have finished, try the questions at the end of the TMVA demo, or look at the optional notebooks. I walk around.

*IT: 35 minuti di lab aperto: finire A e B (da consegnare entrambi), check PASS; se hanno finito, domande TMVA o notebook opzionali.*

**Questions to ask each student:**

- Does your Exercise A run to the end? Which step was the hardest?
- In Exercise B, what happens to mu when you remove the control region?
- What is the meaning of the parameter k ZZ?
- Which of the two significances would you quote, and why?

---

## 3:45 — Wrap-up and feedback (slide 17, 10 min)

**SAY:** Let's finish the course. \[PAUSE\] You can now do four things. You can write the complete model: the marked Poisson, the nuisance parameters, the constraints, the control regions. You can fit it and validate it with toys. You can make statements with RooStats: a significance, an interval, a limit. And you can read a HistFactory workspace, the same as in a published paper. \[PAUSE\] Before you leave. Please upload both notebooks of Lab 4, A and B, on Virtuale. In total you hand in two notebooks out of three for each of the first three labs, and both of Lab 4. The solutions of all the labs appear after the deadline. The optional material is in the optional folder: the speed test, the convolution, and the upper limits. And please fill the short anonymous feedback form. It has five questions. **Your feedback decides what I change next year.** \[PAUSE\] Thank you very much. It was a pleasure.

*IT: 4 competenze; consegna A e B del Lab 4 su Virtuale; riepilogo regola 2/3 + 2/2; soluzioni dopo la scadenza; materiale opzionale; modulo anonimo di feedback (5 domande).*

---

## Emergency notes

- **Running late?** Shorten Talk C to slides 2, 3 and 6, and run the demo in 25 minutes. Never skip the hand-in rule at the end.
- **TMVA does not run on a laptop?** Say: Please use the Codespace, or follow on my screen. The training is the same.
- **Exercise A macros fail to compile?** They need the C++ compiler. Say: Please use the Codespace. We fix your laptop after class.
- **A notebook does not run?** Say: Please call me. Do not lose time: check the cell that fails, and read me the error.
- **A student asks about the exam?** Say: When the required notebooks are in, your lab work counts as done and you can take the written exam. Details are in the course page.
- **A student asks about RooUnfold or more TMVA?** Say: Good question. It goes beyond the four labs. Ask me after class.

---

## Setup reminders (laptops and Codespaces)

**SAY (at the start):** A practical point for today. Exercise A runs C++ macros, so it needs the compiler. If it does not work on your laptop, please use Codespaces in the browser. \[PAUSE\] When you finish, download your two notebooks, and upload them on Virtuale. Then stop your codespace.

*IT: Exercise A usa macro C++ (compilatore); piano B Codespaces; scaricare i notebook, caricarli su Virtuale, fermare il codespace.*

**Notes for you:**

- The ROOT Team macros of Exercise A are in C++ and need the compiler: they work in the Codespace. On a laptop, ask if the check setup shows the compiler PASS.
- The TMVA demo writes files in the working folder: TMVA magic dot root and the dataset magic folder. In a Codespace the quota is not an issue; on a laptop, make sure there is a writable folder.
- Remind them that both notebooks of Lab 4 go on Virtuale.

| Situation | Say | IT |
| --- | --- | --- |
| Prepare | Please run the notebook from the top. | Eseguite il notebook dall'inizio |
| Compiler | Does the check setup say PASS for the compiler? | check\_setup dice PASS per il compilatore? |
| Hand-in | Please upload both notebooks on Virtuale. | Caricate i due notebook su Virtuale |
| Stop | Please stop your codespace. | Fermate il codespace |
