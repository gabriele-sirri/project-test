# Lab 1 — Speaker Script

*Companion of lab1.md (the slides).*

## How to use this script

- Read the lines after **SAY**. The sentences are short and simple on purpose.
- **IT** = riassunto in italiano, solo per te. Non va letto.
- **\[PAUSE\]** = respira, guarda la classe, aspetta due secondi.
- **\[DO\]** = azione da fare (cambiare slide, aprire il notebook).
- Se ti perdi, riparti dalla frase in **grassetto**: è il messaggio chiave della slide.
- Parla piano. Dieci secondi di silenzio dopo una domanda sono normali.

## Survival phrases

| Situation | Say | IT |
| --- | --- | --- |
| Start | Good morning everyone. Let's start. | Buongiorno, iniziamo |
| Slow down | Let me say that again, more slowly. | Lo ripeto più piano |
| Check | Is this clear? Any questions? | È chiaro? Domande? |
| Did not understand | Sorry, could you repeat the question? | Puoi ripetere la domanda? |
| Not sure | Good question. I will check and answer next time. | Controllo e rispondo la prossima volta |
| Later | We will see this in Lab 2. | Lo vediamo nel Lab 2 |
| Teams | Please work in pairs, or in teams of three. | Lavorate in coppie o terne |
| Time | You have fifteen minutes. | Avete quindici minuti |
| Help | Raise your hand and I will come to you. | Alzate la mano e vengo |
| Look | Please look at the screen. | Guardate lo schermo |
| Open | Open the notebook called ex A. | Aprite il notebook ex A |
| Error | Do not worry, this error is normal. Let's read the message together. | Leggiamo l'errore insieme |
| Break | Let's take a break. We restart at 10:35. | Pausa, si riparte alle 10:35 |
| End | That's all for today. See you in two weeks. | Ci vediamo tra due settimane |

## Pronunciation help (approximate)

| Word | Say it like |
| --- | --- |
| likelihood | LIKE-li-hood |
| Poisson | pwa-SON |
| Gaussian | GOW-si-an (GOW as in cow) |
| Breit–Wigner | BRITE VIG-ner |
| nuisance | NYOO-sans |
| parameter | pa-RAM-i-ter |
| extended | ex-TEN-did |
| background | BACK-ground |
| RooFit | ROO-fit |
| RooStats | ROO-stats |
| MINUIT | MIN-you-it (or: mee-NWEE) |
| MIGRAD | MY-grad |
| HESSE | HESS-eh |
| sigma | SIG-ma |
| tau | TOW (as in cow) |
| histogram | HIS-to-gram |
| unbinned | un-BINND |
| tutorial | tu-TOR-ee-al |
| workspace | WORK-space |

---

## 0:00 — Opening (slides 1–3, 5 min)

**SAY (slide 1):** Good morning everyone, and welcome. My name is Gabriele Sirri. This is the practical part of the course, Module 3 of Statistical Data Analysis. In four mornings we will build a complete analysis, step by step. Today is Lab 1: data modelling, and the basics of RooFit. \[PAUSE\] Please keep your laptops open. This is a hands-on course. You will write code in every hour.

*IT: benvenuto, cosa faremo in 4 mattine, oggi Lab 1, portatili aperti.*

**\[DO\] slide 2 — Roadmap**

**SAY:** Here is the plan. We have four labs, one every two weeks. Between the labs you do a short tutorial at home. And there is one project, in teams. \[PAUSE\] I announce the project today, because I want you to think about it for two weeks. In Lab 1 we learn to build a model. In Lab 2 we study the likelihood and the MINUIT minimiser. In Lab 3 we study systematic uncertainties, RooStats, and a real problem with correlated uncertainties. In Lab 4 we use HistFactory, and every team shows its work. **Every lab has the same rhythm: a short talk, then hands-on work. Three times, with two breaks.**

*IT: 4 lab, uno ogni 2 settimane, tutorial a casa, progetto annunciato oggi, contenuti dei 4 lab, ritmo talk + hands-on.*

**\[DO\] slide 3 — Today's schedule**

**SAY:** This is our schedule for today. We start at nine. The first break is at about twenty past ten. The second break is at ten to twelve. We finish at one o'clock. If you are late for a break, please do not worry. The notebooks are in the repository.

---

## 0:05 — Setup check (slide 4, 5 min)

**SAY:** First, a quick check. Please use your own laptop, with ROOT installed as in the guides. If ROOT does not work on your laptop, open the repository in GitHub Codespaces, in the browser of the lab computer. For this you need a free GitHub account. The notebooks are the same everywhere. \[PAUSE\] Now run this small cell. It prints the ROOT version and creates a RooFit workspace. You should see the RooFit banner. **If you see an error, tell me now, not at twelve o'clock.**

*IT: verifica ambiente. Chi ha problemi lo dice subito. Cammina tra i banchi per 3 minuti.*

**Useful during the check:**

- Who has a problem? Please raise your hand.
- Please try to open a new terminal.
- Let's install it together after the break.

---

## 0:10 — Talk A: From data to a model (slides 5–9, 20 min)

**\[DO\] slide 6 — The inference chain**

**SAY:** Let me start with the big picture. We have data. We build a model. From the model we write the likelihood. And from the likelihood we do inference: estimates, intervals, tests, limits. \[PAUSE\] In this course, each lab adds one block. **Today we work on the model.**

*IT: catena data → model → likelihood → inference. Oggi il modello.*

**Ask the class:** What is the difference between a function and a probability density? **Expected answer:** a density is normalised: the integral is one. **If nobody answers, SAY:** A probability density has area equal to one. A generic function does not. This is why RooFit normalises the pdf for us.

**\[DO\] slide 7 — The marked Poisson model**

**SAY:** Now the main formula of the morning. An experiment records n events. Each event has some measured features, for example a mass or an energy. We call these features the marks. \[PAUSE\] The probability of the whole experiment has two parts. The first part is a Poisson distribution for the number of events n. The second part is a product, over all events, of the density of the marks. **The first part is the rate. The second part is the shape.**

*IT: Poisson per il numero di eventi (rate) × prodotto delle densità (shape). Se rate-only è un conteggio.*

**SAY (to close):** If we only have the rate, we have a counting experiment. If we only care about the shape, we can ignore the number of events. Most real analyses use both. For the details, please read Cranmer, Practical Statistics for the LHC. The link is on the slide.

**\[DO\] slide 8 — Channels and processes**

**SAY:** In a real measurement, several processes contribute to the same channel. For example, signal and background. The total expected number of events is the sum of the contributions. And the total shape is the weighted sum of the shapes. \[PAUSE\] Look at the table. LHCb, CUORE, IceCube, MAGIC. Different fields, different detectors. **But the mathematical structure is the same: signal plus background, in a mass, an energy, or an angle.** This is why one toolkit is enough for all of us.

*IT: processi nello stesso canale; esempi dalla tabella; stessa struttura in ogni campo.*

**\[DO\] slide 9 — Why RooFit?**

**SAY:** Why do we use RooFit? RooFit is a toolkit to build, combine, fit and share probability models. The models are objects. You can combine them, and you do not need to rewrite the likelihood by hand. The model is stored in a workspace, and the workspace goes directly into RooStats and HistFactory. \[PAUSE\] I want to be honest. There are alternatives. iminuit and scipy are good for simple fits. zfit and pyhf are modern Python tools. **We use RooFit because it is the tool used in the experiments, and it covers the full chain, from the model to the final statistical result.**

*IT: motivazione onesta per RooFit; citare alternative; punto forte = catena completa + uso in collaborazione.*

---

## 0:30 — Hands-on A: Gaussian, toys, fit (slides 10–12, 50 min)

**\[DO\] slide 11 — The minimal RooFit program (live coding)**

**SAY while typing:** Now we write a complete RooFit program. It is short. \[PAUSE\]

- First, we import ROOT.
- We create the variable x, from minus ten to ten. This is the observable.
- We create the mean, with start value zero. The two numbers after are the limits.
- We create sigma, with start value three.
- Now we create the Gaussian pdf. It knows x, mean and sigma. **The pdf holds references to the variables: they are shared objects.**
- We generate ten thousand events. These are toy data.
- We fit the pdf to the data. Save equals True keeps the fit result.
- Finally we make a frame, we plot the data, we plot the pdf, and we draw.

*IT: narra ogni riga mentre scrivi. Messaggio chiave: le variabili sono oggetti condivisi.*

**SAY (after the plot):** The fit gives a mean close to zero and a sigma close to three. \[PAUSE\] Is this a surprise? No, because we generated the data with these values. This is a toy: **we know the truth, so we can test our method.**

**\[DO\] slide 12 — Exercise A**

**SAY:** Now it is your turn. You have about fifty minutes. Exercise A1: create a Gaussian with mean zero and sigma one. Plot it. Then change sigma to three. Generate ten thousand unbinned events, fit, and plot. Exercise A2: create an exponential, with tau equal to four point five. Generate binned data, one thousand events, bin width zero point five. Fit and plot. \[PAUSE\] Please also answer the three questions in your notebook. First: are the fitted values compatible with the true ones? Second: what changes if you use only one hundred events? Third: why is the error on sigma different from the error on the mean? Work in pairs if you like. Raise your hand if you are stuck.

*IT: leggi le consegne; poi circola. Dopo 25 min chiedi: chi ha finito A1? Alla fine chiedi a un volontario di mostrare il grafico.*

**While walking around:**

- Did you run the first cell?
- What does the error message say?
- Look at the range of the variable. Is the value inside the range?
- Very good. Now try with fewer events.

**At the end (SAY):** Time is up. Let's compare. Who can show me the result of A2? \[PAUSE\] Thank you. **Notice: with fewer events, the errors are larger. The error scales roughly as one over the square root of N.**

---

## 1:15 — BREAK (15 min)

**SAY:** Let's take a break. We restart at 10:35. If you have a technical problem, come to me now.

---

## 1:30 — Talk B: RooFit building blocks (slides 13–15, 20 min)

**\[DO\] slide 14 — Four objects to know**

**SAY:** Welcome back. Now let me organise what you have just used. In RooFit there are four objects to know. \[PAUSE\] The first is RooRealVar. It is a variable or a parameter, with a range. The second is the pdf, the normalised density. For example the Gaussian, the exponential. The third is the dataset. It can be unbinned, a RooDataSet, or binned, a RooDataHist. The fourth is RooPlot, the frame where we draw data and model. \[PAUSE\] Three rules of thumb. Observables have a range. Parameters have a range and a start value. **And the pdf is normalised over the observable automatically.**

*IT: 4 oggetti, 3 regole. La normalizzazione automatica è il punto chiave.*

**\[DO\] slide 15 — Unbinned vs binned**

**SAY:** Now, two kinds of likelihood. In the unbinned case we use every event. The minus log likelihood is the sum, over events, of the minus log of the density. In the binned case, we have a histogram. In each bin the number of events is Poisson, with an expected value that depends on the parameters. \[PAUSE\] A very important point. **A binned likelihood is not a chi-square fit.** It is exact for low counts, and it works also with empty bins. Binned fits lose information if the bins are wide. Unbinned fits are slow if you have very many events. In RooFit the pdf and the code are the same. Only the dataset type changes.

*IT: binned ≠ chi-quadro. Stesso codice, cambia il dataset.*

**Ask the class:** When would you prefer a binned fit? **Possible answers:** very large data samples; templates from simulation; combining many channels (this is what HistFactory does, Lab 4).

---

## 1:50 — Hands-on B: LHCb mass and CLT (slide 16, 55 min)

**\[DO\] slide 16 — Exercise B**

**SAY:** Exercise B1 uses a simplified dataset, modelled on an LHCb analysis. The file is called b0 invariant mass dot root. Please import the histogram as a RooDataHist. Fit a Breit–Wigner. Then add a Gaussian resolution and compare your mass with the value from the Particle Data Group. \[PAUSE\] Exercise B2 is about the central limit theorem. Generate the sum of N uniform variables. Fit a Gaussian. Then look at the tails, for N equal to two, five, ten, twenty. **Where does the Gaussian stop being a good model? The answer is in the tails.** Fifty minutes. Please start.

*IT: B1 = dati reali LHCb; B2 = CLT con code. Se qualcuno è lento, B2 si può finire a casa.*

**While walking around:**

- How do you import a histogram into RooFit? Look at RooDataHist.
- What is the width of the Breit–Wigner? Is it larger than the resolution?
- Please plot the pulls. Do you see a pattern?

**At the end (SAY):** Let's stop here. \[PAUSE\] Quick question: for N equal to ten, does the Gaussian look good in the centre? Yes. And in the tails? Not exactly. **This is the message: a five sigma claim needs an explicit calculation. We cannot only say the Gaussian is a good approximation.** We will use this idea in Lab 3.

---

## 2:45 — BREAK (10 min)

**SAY:** Let's take a short break. Ten minutes. We restart at 12:00.

---

## 2:55 — Talk C: Composite models (slides 17–19, 15 min)

**\[DO\] slide 18 — Adding pdfs**

**SAY:** Now the last topic: signal plus background. We add two pdfs. There are two ways. \[PAUSE\] The first is shape-only. We use a fraction. The total number of events is fixed by the data. The second is extended. We use the yields, N signal and N background. In the extended case, the number of events is Poisson, and the yield is a parameter of the fit. **This is exactly the marked Poisson model from the beginning of the morning, written in code.** \[PAUSE\] In RooFit we use RooAddPdf. We give two lists: the pdfs, and the yields. And to plot only the background, we use Components equals bkg.

*IT: frazioni vs yield; extended = marked Poisson; RooAddPdf; Components per plottare il fondo.*

**\[DO\] slide 19 — RDataFrame in one slide**

**SAY:** One short remark about data. In real analyses, data are in ROOT files, in trees. RDataFrame is the modern way to read them. You select events with Filter. You create new columns with Define. And you make histograms. \[PAUSE\] RDataFrame is lazy: nothing runs until you ask for a result. And it makes one loop over the events for all your results. With one line, you can use many cores. **We will study RDataFrame again in Lab 4.** For now, remember: Filter, Define, Histo1D. One more thing: the expression in a Define can be a C++ function, compiled just in time. You will try it in exercise C, step four.

*IT: RDF in 1 minuto. Non approfondire.*

---

## 3:10 — Hands-on C and project (slides 20–22, 40 min)

**\[DO\] slide 21 — Exercise C**

**SAY:** Exercise C1 uses the LHCb rare decay, B zero to proton anti-proton. The file is in the data folder. Please fit a Gaussian for the signal, plus an exponential for the background. Use an extended fit. Report the number of signal events and the number of background events, with errors. Plot the components and the pulls. \[PAUSE\] Exercise C2: do the same with fractions, shape-only. What happened to the information on the total yield? **Think about this: the rate is gone.** You have about twenty minutes. If you finish early, step C4 is optional: count the events in a mass window with a C++ function, compiled just in time.

*IT: C1 estesa, C2 con frazioni, domanda sul rate perso.*

**\[DO\] slide 22 — Project menu (at 12:30)**

**SAY:** Now the project. \[PAUSE\] You will work in teams of two or three. Please look at the table. We have five cases, from different fields: nuclear physics, neutrinos, astroparticle physics, and beam instrumentation. You can also propose your own case, with a one-page proposal by Lab 2. Each case has its own data. In Lab 4, each team presents one figure, one number, and one caveat, in three to five minutes. \[PAUSE\] A caveat is a limitation: something your result does not tell us. **We do not need slides. A good plot and a clear explanation are enough.** Between now and Lab 2, please choose your team and your case. Write your names in the file teams dot md.

*IT: annuncio progetto, 6 casi, team di 2-3, presentazione 3-5 min (figura, numero, caveat), scegliere entro il Lab 2.*

**If students ask:**

- Is it graded? — It is part of your work in the course. You will also discuss it at the exam.
- Can I work alone? — Yes, but teams are better. Talk to me.
- Can we propose our own case? — Yes, if you have data. Please talk to me first.

---

## 3:50 — Wrap-up (slide 23, 10 min)

**SAY:** Let's finish. \[PAUSE\] Today you learned three things. First, the marked Poisson model: rate times shape. Second, the RooFit objects: variable, pdf, dataset, frame. Third, unbinned and binned likelihoods, and extended fits. \[PAUSE\] For the next lab, in two weeks, please do four things. One: finish the exercises in the notebooks. The solutions will appear after the deadline. Two: choose your project case and your team. Three: read the sections on likelihood and nuisance parameters in Cranmer's paper. Four: open your Codespace once, to check that it still works. \[PAUSE\] **In Lab 2 we open the box: what really happens when we call fitTo.** We will study MINUIT, the likelihood scan, and the nuisance parameters. Thank you very much. See you in two weeks.

*IT: 3 cose imparate, 4 compiti, anteprima Lab 2. Saluti.*

---

## Emergency notes

- **Running late?** Skip B2 (do at home) and shorten the RDataFrame slide. Never skip the project announcement.
- **Codespaces not working?** Say: Please use SWAN, or the shared notebook link. We fix your installation after class.
- **A student asks something very hard?** Say: That is an excellent question. It goes beyond today. Let's discuss it after class, or in Lab 2.
- **Silence after a question?** Wait ten seconds. Then rephrase: Let me ask in a different way.

---

## Setup policy: ROOT on the student laptops (read before Lab 1)

**Rule for the students:** bring a laptop with a working ROOT. If it does not work, use GitHub Codespaces in a browser on a lab computer. A free GitHub account is needed.

### Message to send one week before Lab 1

Dear students, for the labs please bring a laptop with a working ROOT installation. Follow the guides in the docs folder of the course repository: Windows, WSL, Binder, Colab. For a local installation, use the course environment file. Then run python course/tools/check\_setup.py. Every line must say PASS. If you see a FAIL, please send me the output before the first lab. If ROOT does not work on your laptop, you can use GitHub Codespaces in the browser of the lab computers. For this, please create a free GitHub account before the lab. Binder and Colab are only fallback options: the session is temporary.

*IT: messaggio da inviare una settimana prima. Chiedi l'output di check\_setup in caso di FAIL.*

### First minutes of Lab 1

**SAY:** Raise your hand if check setup says PASS on your laptop. \[PAUSE\] Thank you. Everybody else, please open Codespaces. Go to the repository page. Click the green button Code. Then the tab Codespaces. Then Create codespace. It takes about one minute. \[PAUSE\] If you do not have a GitHub account, please create one now. It is free.

### Useful phrases

| Situation | Say | IT |
| --- | --- | --- |
| Poll | Who has a working ROOT? | Chi ha ROOT funzionante? |
| Fallback | Please use Codespaces in your browser. | Usate Codespaces nel browser |
| Account | You need a free GitHub account. | Serve un account GitHub gratuito |
| Stop | Please stop the codespace when you finish. | Fermate il codespace a fine lavoro |
| Hand-in | Please download your notebook before you leave. | Scaricate il notebook |

### Notes for you

- Before the course, open a Codespace yourself from a lab computer. Check that the browser and the network work.
- A Codespace consumes the free monthly quota of the student while it is running. Remind them to stop it. The free plan gives 120 core-hours per month: 60 hours on a 2-core codespace. Closing the browser does not stop the codespace: it runs until the idle timeout, 30 minutes by default. Ask them to stop it from the Codespaces page.
- In Codespaces the files stay in the student's codespace. To hand in, they download the notebook.
