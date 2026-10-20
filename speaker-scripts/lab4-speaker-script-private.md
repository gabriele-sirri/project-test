# Lab 4 — Speaker Script

*Companion of lab4.md (18 slides).*

## How to use this script

- **SAY** = read aloud. **IT** = riassunto per te. **\[PAUSE\]** = respira. **\[DO\]** = azione. In grassetto il messaggio chiave.
- Numeri di slide = quelli di lab4.md, divisori inclusi.
- Oggi: 1 ora e mezza di lezione/hands-on e **75 minuti di showcase**. La parte difficile è gestire il tempo dei team: scrivi sul foglio l'ordine e il cronometro.
- Prima del lab: sorteggia l'ordine dei team e preparalo; prova che il tuo portatile mostri un notebook da Codespaces.

## New phrases for today

| Situation | Say | IT |
| --- | --- | --- |
| Draw | We draw the order by lottery. | Ordine per sorteggio |
| Start | Team one, please start. You have five minutes. | Team uno, iniziate |
| One minute | You have one minute left. | Resta un minuto |
| Stop | Thank you. Please, we need to stop here. | Dobbiamo fermarci |
| Who | Who did what in your team? | Chi ha fatto cosa? |
| Question | Does anyone have a question for this team? | Domande per questo team? |
| Speak up | Please speak to the class, not to the screen. | Parlate alla classe |
| Thanks | Thank you very much. Let's give them a round of applause. | Applauso |
| Next | Next team, please get ready. | Prossimo team |
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
| showcase | SHOW-case |
| caveat | KAV-ee-at |
| lambda | LAM-duh |
| just-in-time | just in TIME (JIT = jit) |
| multithreaded | MUL-ti-THRED-id |
| anonymous | uh-NON-i-mus |

---

## 0:00 — Recap (slides 1–3, 5 min)

**SAY (slide 1):** Good morning, and welcome to the last lab. This is Lab 4: HistFactory, and your analysis. Today we have two parts. In the first hour and a half, we build a binned model with HistFactory. Then, you present your work. \[PAUSE\] I am looking forward to seeing what you did in these weeks.

*IT: ultimo lab; 1.5 ore di HistFactory poi showcase dei team.*

**\[DO\] slide 2 — Recap**

**SAY:** Three short questions. Please answer in pairs. One: constraint term, or auxiliary measurement. Which one do you use, and when? Two: one source of systematic uncertainty moves three channels. How many nuisance parameters do you need? Three: which tool for a discovery, which for an upper limit?

**Expected answers:**

1. Measurement if you have the control data; constraint if you only have its result.
2. One: a fully correlated source needs one nuisance parameter. In general, the rank of the covariance matrix.
3. Discovery: hypothesis test, q zero. Upper limit: CLs with the hypothesis test inverter.

**\[DO\] slide 3 — Schedule**

**SAY:** This is our plan. Two talks and two hands-on parts. At eleven fifteen, you have twenty minutes to finish your project. At eleven thirty-five, the showcases start. Every team has three to five minutes. I will use a timer. \[PAUSE\] The order is by lottery. Let me draw it now. \[DO\] Draw the order and write it on the board.

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

**SAY:** Exercise B. Step one: build the measurement. Two channels, four samples. The signal has the NormFactor mu. The ZZ has the NormFactor k ZZ, and it is the same name in both channels. Step two: fit. Then compare with a fit without the control region. Step three: the interval on mu and the significance. Step four: add a five percent luminosity uncertainty. \[PAUSE\] **Attention: five percent is an illustrative size, not the CMS value. In your project, use a number you can justify.** Step five: slice and profile of mu, and the correlation between mu and k ZZ. Thirty-five minutes.

*IT: B1 Measurement, B2 con/senza CR, B3 interval/Z, lumi 5% (illustrativo!), B4 anatomia. Attesi: μ≈0.98, kZZ≈0.90, Z≈3.5, \[0.62,1.43\]; senza CR μ≈0.92, Z≈3.3.*

**While walking around:**

- Is the NormFactor named exactly the same in the two channels?
- Did you set the histograms to be owned by HistFactory?
- What does the check say?
- Why is the correlation between mu and k ZZ small?

**At the end (SAY):** Let's look at the results. The control region says that k ZZ is about zero point nine. \[PAUSE\] The simulation overestimates the ZZ background by about ten percent. With less background, the same data need more signal: mu goes from zero point nine two to zero point nine eight. And the significance increases from three point three to three point five. **This is the value of a control region.** And three point five sigma is evidence, not a discovery.

---

## 2:05 — BREAK (10 min)

**SAY:** Let's take a short break. We restart at 11:15 for the project.

---

## 2:15 — Project: the last twenty minutes (20 min)

**SAY:** You have twenty minutes to finish. Please do three things. One: choose your figure. Only one. Two: write your number, with its uncertainty. Three: write your caveat, the most important limitation. \[PAUSE\] Decide who speaks about what. **Every team member speaks.** I will ask: who did what? I walk around. Please call me if the notebook does not run.

*IT: 20 minuti: una figura, un numero, un caveat; decidere chi parla; ognuno parla.*

**Questions to ask each team:**

- What is your figure?
- What is your number, with its uncertainty?
- What is your caveat?
- Who will present what?

---

## 2:35 — Showcases (slide 17, 75 min)

**\[DO\] slide 17 — Showcase rules**

**SAY:** Now the showcases. \[PAUSE\] The rules are on the slide. Three to five minutes per team. One figure, one number, one caveat. Every member speaks. At the end, one question from another team. \[PAUSE\] I will say: one minute left. Please finish when I say stop. I know it is difficult to speak about a project in five minutes. It is a good exercise.

*IT: regole; cronometro; un minuto di preavviso; una domanda per team.*

**For each team (use this sequence):**

1. SAY: Team \[number\], please start. You have five minutes.
2. At four minutes: You have one minute left.
3. At five minutes: Thank you. Please, we need to stop here.
4. SAY: Who did what in your team? (If it was not said.)
5. SAY: Does anyone have a question for this team?
6. SAY: Thank you very much. Let's give them a round of applause. Next team, please get ready.

**Questions you can ask if the room is silent:**

- What would break your fit?
- What did you assume, that you could not check?
- Which systematic uncertainty is the biggest?
- If you had one more week, what would you do?
- Is your result a measurement, a limit, or a discovery?

**If you run out of time:** keep three minutes per team, no questions. Use the last ten minutes for the written feedback.

---

## 3:50 — Wrap-up and feedback (slide 18, 10 min)

**SAY:** Let's finish the course. \[PAUSE\] You can now do four things. You can write the complete model: the marked Poisson, the nuisance parameters, the constraints, the control regions. You can fit it and validate it with toys. You can make statements with RooStats: a significance, an interval, a limit. And you can read a HistFactory workspace, the same as in a published paper. \[PAUSE\] Before you leave. Please upload your final notebook and your one-page report to the course portal. The solutions of all the labs are in the solutions folder, after the deadline. The optional material is in the optional folder: the TMVA demo, the speed test, the convolution, and the upper limits. And please fill the short anonymous feedback form. It has five questions. **Your feedback decides what I change next year.** \[PAUSE\] Thank you very much. It was a pleasure.

*IT: 4 competenze; consegna sul portale; soluzioni dopo la scadenza; materiale opzionale; modulo anonimo di feedback (5 domande).*

---

## Emergency notes

- **Few teams or a short showcase?** Use the extra time for questions and for the optional TMVA demo (30 minutes, slides optional\_tmva).
- **A team did not finish?** Say: It is fine. Show what you have: the figure and the caveat. The caveat is the most important part.
- **Many teams?** Three minutes each, no questions. Group questions at the end.
- **A notebook does not run live?** Say: Please show the figure you saved before. We do not debug live.
- **A student asks about the exam?** Say: In the exam there is a question about your lab work. I may ask about your own result.

---

## Setup reminders and the showcase (laptops and Codespaces)

**SAY (at the start):** A practical point for today. In the showcase, you present from your own laptop, or from Codespaces in the browser of the lab computer. Please open your notebook before your turn, and run it once. \[PAUSE\] Please keep a saved figure ready: we do not debug live. If you work in Codespaces, please download your notebook and your report before you leave. Before the end of the lab, stop your codespace.

*IT: showcase da portatile o da Codespaces; notebook già aperto ed eseguito; figura salvata; scaricare notebook e report; fermare il codespace.*

**Notes for you:**

- Before the showcase, check how the projector connects: HDMI or USB-C. Students with a laptop may need an adapter. Prepare one lab computer as a backup: it can show a Codespace in a browser.
- The ROOT Team macros of Exercise A are in C++ and need the compiler: they work in the Codespace. On a laptop, ask if the check setup shows the compiler PASS.
- Remind them that the final notebook and the report go to the course portal.

| Situation | Say | IT |
| --- | --- | --- |
| Prepare | Please open your notebook before your turn. | Aprite il notebook prima del turno |
| Backup | Please show the figure you saved before. | Mostrate la figura salvata |
| Laptop | Please connect your laptop to the projector. | Collegate il portatile al proiettore |
| Hand-in | Please download your files before you leave. | Scaricate i file |
