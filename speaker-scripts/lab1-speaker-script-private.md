# Lab 1 — Speaker Script

*Companion of lab1.md (the slides).*

*How to use this script, survival phrases and pronunciation help are in `lab1-guide-and-phrases-private.md` and `lab1-pronunciation-private.md`.*

---

## 0:00 — Opening (slides 1–3, 5 min)

**SAY (slide 1):** Good morning everyone, and welcome. My name is Gabriele Sirri. This is the practical part of the course, Module 3 of Statistical Data Analysis. In four mornings we will build a complete analysis, step by step. Today is Lab 1: data modelling, and the basics of RooFit. \[PAUSE\] Please keep your laptops open. This is a hands-on course. You will write code in every hour.

*IT: benvenuto, cosa faremo in 4 mattine, oggi Lab 1, portatili aperti.*

**\[DO\] slide 2 — Roadmap**

**SAY:** Here is the plan. We have four labs, one every two weeks. Between the labs you finish your notebooks at home, and you submit them. \[PAUSE\] The rule is simple: in each of Labs 1, 2 and 3 there are three notebooks, A, B and C. You submit two of them, the ones you prefer. In Lab 4 there are two notebooks, and you hand in both. We work on all of them in class, and I publish all the solutions. So you will not miss anything. In Lab 1 we learn to build a model. In Lab 2 we study the likelihood and the MINUIT minimiser. In Lab 3 we study systematic uncertainties, RooStats, and a real problem with correlated uncertainties. In Lab 4 we use HistFactory and RDataFrame, and we finish with a demo of TMVA. **Every lab has the same rhythm: a short talk, then hands-on work. Three times, with two breaks.**

*IT: 4 lab, uno ogni 2 settimane; consegna di 2 notebook su 3 nei Lab 1-3 e di entrambi nel Lab 4; si lavora su tutti in aula, soluzioni per tutti; contenuti dei 4 lab, ritmo talk + hands-on.*

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

## 0:10 — Talk A: From data to a model (slides 5–12, 20 min)

*Timing: the three notation slides (8–10) take about 6 minutes. Keep slides 11 and 12 short (about 2 minutes each).*

**\[DO\] slide 6 — The inference chain**

**SAY:** Let me start with the big picture. We have data. We build a model. From the model we write the likelihood. And from the likelihood we do inference: estimates, intervals, tests, limits. \[PAUSE\] In this course, each lab adds one block. **Today we work on the model.**

*IT: catena data → model → likelihood → inference. Oggi il modello.*

**Ask the class:** What is the difference between a function and a probability density? **Expected answer:** a density is normalised: the integral is one. **If nobody answers, SAY:** A probability density has area equal to one. A generic function does not. This is why RooFit normalises the pdf for us.

**\[DO\] slide 7 — The marked Poisson model**

**SAY:** Now the main formula of the morning. An experiment records n events. Each event has some measured features, for example a mass or an energy. We call these features the marks. \[PAUSE\] The probability of the whole experiment has two parts. The first part is a Poisson distribution for the number of events n. The second part is a product, over all events, of the density of the marks. **The first part is the rate. The second part is the shape.**

*IT: Poisson per il numero di eventi (rate) × prodotto delle densità (shape). Se rate-only è un conteggio.*

**SAY (to close):** If we only have the rate, we have a counting experiment. If we only care about the shape, we can ignore the number of events. Most real analyses use both. For the details, please read Kyle Cranmer, Practical Statistics for the LHC. The link is on the slide.

**\[DO\] slide 8 — Notation: observables and parameters**

**SAY:** Before we go on, a few words about notation. It looks like a detail, but it avoids many mistakes. \[PAUSE\] **Roman letters are observables, the data: x, m, E, n.** **Greek letters are parameters, the unknown constants of the model: mu, sigma, tau, nu, theta.** Look at the first two: n is the number of events we observe. Nu is the number of events we expect. They are not the same. \[PAUSE\] A hat means an estimate from the data: theta hat is the best-fit value. A subscript zero is a fixed reference value, for example the true value. From Lab 2 you will also hear parameter of interest and nuisance parameters. **One warning: the same letter can mean two things. Mu is the mean of a Gaussian, but also the signal strength. Always tell me what each symbol is, in the exercises and at the exam.**

*IT: lettere romane = osservabili/dati; greche = parametri; n osservati, nu attesi; cappello = stima; pedice 0 = valore di riferimento; attenzione allo stesso simbolo con due significati.*

**Ask the class:** In a Gaussian, which symbols are observables and which are parameters? **Expected answer:** x is the observable; mean and sigma are the parameters. **If nobody answers, SAY:** x is what we measure, event by event. Mean and sigma are what we want to find.

**\[DO\] slide 9 — A range for every variable, but not the same range**

**SAY:** Now an important point, and RooFit forces us to think about it. Every variable needs a range. But the range does not mean the same thing. \[PAUSE\] For an observable, the range is the domain of the pdf. The pdf is normalised on this range: the integral is one. Events outside the range are not in the fit. So the range is part of the model. **If you change the range of an observable, you change the model.** In an extended fit, even the yields change, because the yield is the number of events in the range. \[PAUSE\] For a parameter, we give a starting value and an allowed interval. The interval is only a bound for the minimiser. It does not change the function. But the fit still depends on it, especially if the best value is near a limit. **The range of an observable defines the model. The range of a parameter steers the search.**

*IT: osservabile: range = dominio dove la pdf è normalizzata; eventi fuori non entrano; nei fit estesi cambiano le rese. Parametro: valore iniziale + intervallo = limiti per il minimizzatore; non cambia la funzione ma il fit ne dipende.*

**Ask the class:** In an extended fit, I make the mass range smaller. Does N signal change? Why? **Expected answer:** yes, N is the number of events inside the range. **If nobody answers, SAY:** The yield is defined inside the range of the observable. A smaller range, fewer events.

**\[DO\] slide 10 — Parameter limits: what can go wrong**

**SAY:** Let me give you the typical problems. If the interval is too narrow, the best value sits on the boundary. You see it in the printout. And the errors are not reliable there, neither HESSE nor MINOS. \[PAUSE\] If the interval is too wide, the fit is slow, or it fails. Or it goes to a region without physics, for example a negative sigma, or negative yields. Start near the value you expect. The starting value is not the range. \[PAUSE\] And one more question: is your limit physical or numerical? A limit like mu greater than zero is physics. In Lab 3 you will see that it can change the inference. A loose limit that helps MIGRAD is only numerics. **Say which one it is.** If you do not want to fit a parameter, fix it with set constant.

*IT: troppo stretto = best fit sul bordo, errori non affidabili; troppo largo = convergenza lenta o regioni non fisiche; partire vicino al valore atteso; limite fisico (mu ≥ 0) vs numerico; setConstant per fissare.*

**\[DO\] slide 11 — Channels and processes**

**SAY:** In a real measurement, several processes contribute to the same channel. For example, signal and background. The total expected number of events is the sum of the contributions. And the total shape is the weighted sum of the shapes. \[PAUSE\] Look at the table, and look at the physics. In LHCb, the signal is the decay of the B zero into a proton and an antiproton. The background is random proton–antiproton pairs. In CUORE, the signal is the neutrinoless double-beta decay of tellurium one-thirty, and the background is the natural radioactivity of the materials. In IceCube, the signal is the oscillation of the muon neutrinos, and the background is atmospheric muons and other neutrino flavours. In MAGIC, the signal is gamma rays, and the background is hadrons, from cosmic-ray showers. \[PAUSE\] Different fields, different detectors. **But the mathematical structure is the same: signal plus background, in a mass, an energy, or an angle.** This is why one toolkit is enough for all of us.

*IT: processi nello stesso canale; per ogni esempio nomina il processo fisico (segnale e fondo); stessa struttura in ogni campo. Per IceCube il fondo è da confermare.*

**\[DO\] slide 12 — Why RooFit?**

**SAY:** Why do we use RooFit? First, what it is. RooFit is a part of ROOT, the same ROOT that you know for histograms and trees. Together with RooStats and HistFactory, it is the statistical toolkit of ROOT. The links are on the slide. \[PAUSE\] RooFit builds, combines, fits and shares probability models. The models are objects. You can combine them, and you do not need to rewrite the likelihood by hand. **And there is one very important thing: the normalisation comes for free. RooFit normalises the pdf for you, and it takes everything into account: the limits of the range, the projections, the composite models. This saves a lot of work, and a lot of mistakes.** \[PAUSE\] The model is stored in a workspace, and the workspace goes directly into RooStats and HistFactory. The major LHC collaborations use RooFit. Mostly in an indirect way, inside bigger frameworks. \[PAUSE\] I want to be honest. There are alternatives. iminuit and scipy are good for simple fits. zfit and pyhf are modern Python tools. **We use RooFit because it is the tool behind the experiments, and it covers the full chain, from the model to the final statistical result.**

*IT: RooFit è un componente di ROOT (con RooStats e HistFactory, link in slide); normalizzazione gratis = punto chiave (range, proiezioni, modelli compositi); usato dalle collaborazioni LHC in modo indiretto; alternative onestamente; punto forte = catena completa.*

---

## 0:30 — Hands-on A: Gaussian, toys, fit (slides 13–15, 50 min)

**\[DO\] slide 14 — The minimal RooFit program (live coding)**

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

**\[DO\] Live demo (3 min), right after the live coding of slide 14: ranges in practice.** Set sigma range to 0.1 and 2, and refit. The true value is 3. **Expected:** sigma stops very close to 2, at the boundary. Do not trust its error. Then restore the range, set the sub-range of x, minus 5 to 5, and fit with Range equal to "fit". **Expected:** results close to the first fit, but the errors get larger, because there are fewer events. Ask: why?

**\[DO\] slide 15 — Exercise A**

**SAY:** Now it is your turn. You have about fifty minutes. Exercise A1: create a Gaussian with mean zero and sigma one. Plot it. Then change sigma to three. Generate ten thousand unbinned events, fit, and plot. Exercise A2: create an exponential, with tau equal to four point five. Generate binned data, one thousand events, bin width zero point five. Fit and plot. \[PAUSE\] Please also answer the three questions in your notebook. First: are the fitted values compatible with the true ones? Second: what changes if you use only one hundred events? Third: why is the error on sigma different from the error on the mean? Work in pairs if you like. Raise your hand if you are stuck. The references are on the slide: the ROOT tutorials rf101, rf201 and rf202.

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

## 1:30 — Talk B: RooFit building blocks (slides 16–18, 20 min)

**\[DO\] slide 17 — Four objects to know**

**SAY:** Welcome back. Now let me organise what you have just used. In RooFit there are four objects to know. \[PAUSE\] The first is RooRealVar. It is a variable or a parameter, with a range. The second is the pdf, the normalised density. In practice we use concrete classes, for example RooGaussian and RooExponential. They all derive from one abstract class, RooAbsPdf, and this is why they all behave in the same way: you can fit them, generate from them, and plot them. We will meet other classes in the notebooks, when we need them. The third is the dataset. It can be unbinned, a RooDataSet, or binned, a RooDataHist. The fourth is RooPlot, the frame where we draw data and model. \[PAUSE\] Three rules of thumb. Observables have a range. Parameters have a range and a start value. **And the pdf is normalised over the observable automatically.**

*IT: 4 oggetti, 3 regole. La normalizzazione automatica è il punto chiave.*

**\[DO\] slide 18 — Unbinned vs binned**

**SAY:** Now, two kinds of likelihood. In the unbinned case we use every event. The minus log likelihood is the sum, over events, of the minus log of the density. In the binned case, we have a histogram. In each bin the number of events is Poisson, with an expected value that depends on the parameters. \[PAUSE\] A very important point. **A binned likelihood is not a chi-square fit.** It is exact for low counts, and it works also with empty bins. Binned fits lose information if the bins are wide. Unbinned fits are slow if you have very many events. In RooFit the pdf and the code are the same. Only the dataset type changes.

*IT: binned ≠ chi-quadro. Stesso codice, cambia il dataset.*

**Ask the class:** When would you prefer a binned fit? **Possible answers:** very large data samples; templates from simulation; combining many channels (this is what HistFactory does, Lab 4).

---

## 1:50 — Hands-on B: LHCb mass and CLT (slide 19, 55 min)

**\[DO\] slide 19 — Exercise B**

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

## 2:55 — Talk C: Composite models (slides 20–22, 15 min)

**\[DO\] slide 21 — Adding pdfs**

**SAY:** Now the last topic: signal plus background. We add two pdfs. There are two ways. \[PAUSE\] The first is shape-only. We use a fraction. The total number of events is fixed by the data. The second is extended. We use the yields, N signal and N background. In the extended case, the number of events is Poisson, and the yield is a parameter of the fit. **This is exactly the marked Poisson model from the beginning of the morning, written in code.** \[PAUSE\] In RooFit we use RooAddPdf. We give two lists: the pdfs, and the yields. And to plot only the background, we use Components equals bkg.

*IT: frazioni vs yield; extended = marked Poisson; RooAddPdf; Components per plottare il fondo.*

**\[DO\] slide 22 — RDataFrame in one slide**

**SAY:** One short remark about data. In real analyses, data are in ROOT files, in trees. RDataFrame is the modern way to read them. You select events with Filter. You create new columns with Define. And you make histograms. \[PAUSE\] RDataFrame is lazy: nothing runs until you ask for a result. And it makes one loop over the events for all your results. With one line, you can use many cores. **We will study RDataFrame again in Lab 4.** For now, remember: Filter, Define, Histo1D. One more thing: the expression in a Define can be a C++ function, compiled just in time. You will try it in exercise C, step four.

*IT: RDF in 1 minuto. Non approfondire.*

---

## 3:10 — Hands-on C (slides 23–24, 40 min)

**\[DO\] slide 24 — Exercise C**

**SAY:** Exercise C1 uses the LHCb rare decay, B zero to proton anti-proton. The file is in the data folder. Please fit a Gaussian for the signal, plus an exponential for the background. Use an extended fit. Report the number of signal events and the number of background events, with errors. Plot the components and the pulls. \[PAUSE\] Exercise C2: do the same with fractions, shape-only. What happened to the information on the total yield? **Think about this: the rate is gone.** You have about thirty minutes. If you finish early, step C4 is optional: count the events in a mass window with a C++ function, compiled just in time.

*IT: C1 estesa, C2 con frazioni, domanda sul rate perso.*

**If students ask:**

- Which two notebooks should I choose? — Your choice. I suggest the ones where you felt less sure, because that is where you learn most. The solutions of the third one are there too.
- Can I submit all three? — Yes, I read them with pleasure, but two are enough.
- Is it graded? — No grade: the outcome is "work done", and it gives access to the written exam.
- A check says FAIL. What do I do? — A FAIL means the notebook stops. Fix the cell, or come to my office hours before the deadline.

---

## 3:50 — Wrap-up (slide 25, 10 min)

**SAY:** Let's finish. \[PAUSE\] Today you learned three things. First, the marked Poisson model: rate times shape. Second, the RooFit objects: variable, pdf, dataset, frame. Third, unbinned and binned likelihoods, and extended fits. \[PAUSE\] For the next lab, in two weeks, please do four things. One: finish your two notebooks, the ones you choose, and check that every check says PASS. Two: upload them on Virtuale before the deadline. The solutions of all three notebooks will appear after the deadline. Three: read the sections on likelihood and nuisance parameters in Cranmer's paper. Four: open your Codespace once, to check that it still works. \[PAUSE\] **In Lab 2 we open the box: what really happens when we call fitTo.** We will study MINUIT, the likelihood scan, and the nuisance parameters. Thank you very much. See you in two weeks.

*IT: 3 cose imparate, 4 compiti (finire 2 notebook, caricarli su Virtuale, lettura, aprire il Codespace), anteprima Lab 2. Saluti.*

---

## Emergency notes

- **Running late?** Skip the ranges live demo (after slide 14) and B2 (do at home), and shorten the RDataFrame slide. Never skip the explanation of the submission rule (2 notebooks out of 3).
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
| Upload | Please download your notebook and upload it on Virtuale. | Scaricate il notebook e caricatelo su Virtuale |

### Notes for you

- Before the course, open a Codespace yourself from a lab computer. Check that the browser and the network work.
- A Codespace consumes the free monthly quota of the student while it is running. Remind them to stop it. The free plan gives 120 core-hours per month: 60 hours on a 2-core codespace. Closing the browser does not stop the codespace: it runs until the idle timeout, 30 minutes by default. Ask them to stop it from the Codespaces page.
- In Codespaces the files stay in the student's codespace. To submit, they download the notebook and upload it on Virtuale.
