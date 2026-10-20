# Lab 3 — Speaker Script

*Companion of lab3.md (23 slides).*

## How to use this script

- **SAY** = read aloud. **IT** = riassunto per te. **\[PAUSE\]** = respira. **\[DO\]** = azione. In grassetto il messaggio chiave.
- Numeri di slide = quelli di lab3.md, divisori inclusi.
- Oggi è il lab più concettuale: tre idee (vincoli, RooStats, correlazioni). Rallenta nelle formule, accelera negli esercizi.
- Il caso OPERA è reale ma la correlazione tra canali è un'ipotesi nostra: dillo chiaramente, non attribuirla alla collaborazione.

## New phrases for today

| Situation | Say | IT |
| --- | --- | --- |
| Concept check | Who can explain this in one sentence? | Chi lo spiega in una frase? |
| Disagree | I see it differently. Let me explain why. | Io la vedo diversamente |
| Link | This is the same idea as in Lab 2. | Stessa idea del Lab 2 |
| Numbers | Please compare your number with the one in the check cell. | Confrontate col numero della cella check |
| Assumption | This is our assumption, not the paper's. | Ipotesi nostra, non del paper |
| Warn | This step takes a minute. Please be patient. | Ci vuole un minuto |

## Pronunciation help

| Word | Say it like |
| --- | --- |
| constraint | con-STRAYNT |
| auxiliary | awg-ZIL-yuh-ree |
| hypothesis | hy-POTH-uh-sis |
| significance | sig-NIF-i-kans |
| Asimov | AZ-i-mov |
| eigenvalue | EYE-gen-val-yoo |
| diagonalise | dy-AG-uh-nuh-lyze |
| covariance | co-VAIR-ee-ans |
| OPERA | OH-pe-ra |
| tau (neutrino) | TOW (as in cow) |
| log-normal | LOG-NOR-mul |
| systematic | sis-tuh-MAT-ik |
| Cowan | KOW-en |
| Cranmer | KRAN-mer |

---

## 0:00 — Recap (slides 1–3, 10 min)

**SAY (slide 1):** Good morning, and welcome back. This is Lab 3: systematics and inference. In Lab 2 we saw the profile likelihood and the on/off problem. Today we ask the real question of every analysis: how do we treat what we do not know? \[PAUSE\] We have three parts. First, how to write a systematic uncertainty. Second, how to make statistical statements with RooStats. Third, a real problem, with correlated uncertainties.

*IT: oggi: come scrivere una sistematica, RooStats, caso reale con correlazioni.*

**\[DO\] slide 2 — Recap**

**SAY:** First a short recap. Please discuss in pairs for two minutes. Question one: slice and profile likelihood. Which is wider, and why? Question two: in the on/off problem, where does the uncertainty on the background come from? Question three: your pull has an RMS of one point three. What does it tell you? Question four: does your project fit converge?

**Expected answers:**

1. Profile is wider: nuisance parameters are re-fitted, so their uncertainty adds.
2. From the control region: it is the Poisson uncertainty of n off, divided by tau.
3. The errors are underestimated by thirty percent: the fit errors are too small.
4. Collect the answers; note which teams have problems.

**\[DO\] slide 3 — Schedule**

**SAY:** Here is today's plan. Three talks, three hands-on parts, two breaks. The last twenty-five minutes are for your project. In the project, you add one systematic uncertainty. So please listen with your own case in mind.

---

## 0:10 — Talk A: Constraints vs auxiliary measurements (slides 4–7, 20 min)

**\[DO\] slide 5 — Two ways to model a systematic**

**SAY:** A nuisance parameter is a quantity that we need in the model, but we know it only with an uncertainty. Where does our knowledge come from? \[PAUSE\] There are two ways to write it. The first: an auxiliary measurement. We write the likelihood of the control data. For example, a Poisson for n off. The second: a constraint term. We write a probability distribution for the result of that measurement. For example, a Gaussian centred on the background estimate, with the quoted uncertainty. \[PAUSE\] Look at the table. With the auxiliary measurement, you need the control data. With the constraint, you need only the summary, for example a paper that says: background three point eight, plus or minus zero point six. **Both enter the likelihood as a factor. The second one is an approximation of the first.**

*IT: misura ausiliaria (likelihood dei dati di controllo) vs vincolo (pdf del risultato). Il vincolo è un'approssimazione.*

**\[DO\] slide 6 — From on/off to a Gaussian constraint**

**SAY:** Let us see when the approximation is good. The control measurement gives b hat equal to n off divided by tau. And the uncertainty is the square root of n off, divided by tau. For a large n off, the Poisson is almost Gaussian. This works for about thirty to fifty counts, or more. \[PAUSE\] For few counts, it fails. The Gaussian is symmetric. It allows negative background. And it makes the significance too high. \[PAUSE\] Two alternatives. If the uncertainty is multiplicative and the quantity is positive, for example an efficiency, use a log-normal. If you know the number of control events, the exact partner of the Poisson is the Gamma distribution. **Rule: use the measurement when you have it. Use a constraint when you have only its result.**

*IT: Gauss ok per n\_off grande; per pochi conteggi sovrastima la significatività; log-normale per efficienze, Gamma come coniugata esatta.*

**Ask the class:** A paper says: background zero point five plus or minus zero point four. Can you use a Gaussian? **Answer:** No: the Gaussian gives weight to negative values. Use a log-normal or a Gamma.

**\[DO\] slide 7 — The full model, and global observables**

**SAY:** Now the full model. It is the one from Lab 1: the extended marked Poisson. A Poisson for the number of events, times the product of the densities. And now, a new factor: the product of all the constraint terms. \[PAUSE\] In a constraint term, a j is the result of the auxiliary measurement. We call it a global observable. Remember this rule. **In the fit, the global observables are constants. In toy experiments, they are thrown again, together with the data.** In RooFit, you tell this to createNLL with the option GlobalObservables. In RooStats, with ModelConfig.

*IT: modello completo = marked Poisson × vincoli. Global observables: costanti nel fit, rigenerate nei toy.*

---

## 0:30 — Hands-on A: On/off with a Gaussian constraint (slides 8–9, 40 min)

**\[DO\] slide 9 — Exercise A**

**SAY:** Exercise A. We use the top-quark numbers: seventeen events, background three point eight plus or minus zero point six. \[PAUSE\] Step one: build the model with a Gaussian constraint. The function build Poisson aux is given, as a reference. You write build Gauss. Step two: compute the significance for both models. You write the function z zero: a free fit, a fit with s equal to zero, and the square root of two delta NLL. The two models should agree. Step three: repeat with a poor control region, four events. Which model is too optimistic? \[PAUSE\] Open ex A in the lab 3 folder. Forty minutes.

*IT: A1 build\_gauss, A2 z0, A3 controllo povero (4 eventi). Attesi: Z≈4.6 per entrambi; con 4 eventi Poisson 3.06 vs Gauss 3.54.*

**While walking around:**

- What is b zero? Is it in the dataset?
- Is s constant when you fit with s equal to zero?
- Do you get the same significance as the check cell?
- Why do we return a dictionary from the function? (To keep the objects alive.)

**At the end (SAY):** Let's compare. With forty control events, both models give four point six. \[PAUSE\] With four control events, the Poisson gives three, the Gaussian gives three and a half. **The Gaussian is too optimistic. It does not know that four events are a very poor measurement.**

---

## 1:15 — BREAK (15 min)

**SAY:** Let's take a break. We restart at 10:25.

---

## 1:25 — Talk B: RooStats (slides 10–13, 20 min)

**\[DO\] slide 11 — Roles in RooStats**

**SAY:** Welcome back. Now RooStats. RooStats needs to know the role of every element of the model. \[PAUSE\] Look at the table. The model: SetPdf. The parameters of interest: for us, the signal strength. The nuisance parameters. The observables, the data. And the global observables. All of these live in an object called ModelConfig. Then the calculators work on a pair: the data, and the ModelConfig. **If you give the right roles, RooStats does the rest.** The calculators we see: the profile likelihood calculator, the asymptotic calculator, the frequentist calculator with toys, and the hypothesis test inverter for limits.

*IT: ModelConfig = ruoli degli elementi. I calcolatori lavorano su (dati, ModelConfig).*

**\[DO\] slide 12 — Hypothesis test and significance**

**SAY:** The hypothesis test. The null hypothesis is: no signal, mu equal to zero. The test statistic, q zero, is minus two times the log of the profile likelihood ratio. The significance Z is the square root of q zero. And the p-value is one minus the Gaussian cumulative of Z. \[PAUSE\] Two numbers to remember. Three sigma, one in about eight hundred: evidence. Five sigma, about three in ten million: discovery. \[PAUSE\] And a useful formula, from the paper of Cowan, Cranmer, Gross and Vitells. When the background is known, the Asimov significance is: square root of two times s plus b, times the log of one plus s over b, minus s. For s much smaller than b it becomes s over square root of b. **But s over root b overestimates the significance when s is not small. Do not use it for a result.**

*IT: q0, Z=sqrt(q0), p; 3σ=1.3e-3, 5σ=2.9e-7; formula di Asimov; s/√b sovrastima.*

**\[DO\] slide 13 — Intervals and limits**

**SAY:** Three questions, three tools. How significant is the excess? The hypothesis test. What is mu, with its uncertainty? The profile likelihood interval, as in Lab 2. Nothing is seen: how large can mu be? The upper limit, with the CLs method. \[PAUSE\] Asymptotic formulae are fast, and good for large samples. With few counts you need toys. **Choose the calculator from the question, not from habit.**

*IT: tre domande, tre strumenti; asintotico vs toy. CLs nel notebook opzionale.*

---

## 1:45 — Hands-on B: ModelConfig and hypothesis test (slides 14–15, 40 min)

**\[DO\] slide 15 — Exercise B**

**SAY:** Exercise B. The same top-quark model, now in a workspace. \[PAUSE\] Step one: import the model and the data, and define the roles in the ModelConfig. Step two: the sixty-eight and ninety-five percent intervals on s, with the profile likelihood calculator. Step three: the significance and the p-value. Step four: compare with s over root b, and with the Asimov formula. Which is closest to RooStats? And why? \[PAUSE\] Forty minutes.

*IT: B1 ModelConfig, B2 intervalli, B3 significatività, B4 confronto formule. Attesi: \[9.4,17.7\] al 68%; Z≈4.6; Z\_A=4.95; s/√b=6.8.*

**While walking around:**

- Which are the global observables in your model?
- Did you set the null parameters before the hypothesis test?
- What does the check cell say?
- Why is the Asimov number higher than the RooStats number?

**At the end (SAY):** Let's look at the three numbers. S over root b: six point eight. Asimov: four point nine five. RooStats: four point six. \[PAUSE\] **Each step adds realism: first the Poisson fluctuations, then the uncertainty on the background.** And each number is a good lesson: a simple formula can overestimate a significance by fifty percent.

---

## 2:25 — BREAK (10 min)

**SAY:** Let's take a short break. We restart at 11:35.

---

## 2:35 — Talk C: Correlated systematics (slides 16–19, 15 min)

**\[DO\] slide 17 — Systematics are correlated**

**SAY:** A systematic uncertainty rarely affects only one number. A source, for example the charm cross section, or the tagging efficiency, or the luminosity, moves several yields together. \[PAUSE\] We write this with a covariance matrix. Sigma i j is the sum, over the sources, of the effect of source k on channel i, times the effect on channel j. If the errors are independent, the matrix is diagonal. If a source is common to two channels, we have off-diagonal terms. **Ignoring them changes the size of the uncertainty on mu. How much? Only a calculation can tell.**

*IT: una sorgente muove più canali; Sigma = somma v v^T; fuori diagonale = correlazioni.*

**\[DO\] slide 18 — Diagonalise**

**SAY:** How do we put a covariance matrix in a likelihood? We diagonalise it. A real symmetric matrix can be written as U Lambda U transpose. Lambda is diagonal, with the eigenvalues. Then we define independent nuisance parameters, z k. Each one is a standard Gaussian. And the correlated parameters are: beta zero, plus U, times square root of Lambda, times z. \[PAUSE\] Two practical results. One: we need one nuisance parameter for each non-zero eigenvalue. This is the rank of the matrix. Four channels, three sources: three nuisance parameters, not four. Two: if the errors are fully correlated, there is only one nuisance parameter. **This is what HistFactory, pyhf, and the experiment combinations do under the hood.**

*IT: Σ=UΛU^T; β=β0+U√Λ z; z indipendenti N(0,1); rango = numero di sorgenti.*

**\[DO\] slide 19 — A real problem: OPERA**

**SAY:** Here is our real problem. The OPERA experiment. It looks for tau neutrinos appearing in a muon-neutrino beam. This is the final analysis, from the 2018 paper. Four channels, which are four decay modes of the tau. Ten candidate events. \[PAUSE\] Look at the table: the backgrounds by source, the expected signal, the observed events. Notice something. All the signal errors are about twenty percent. In the 2015 paper, the sources are listed: the model, ten percent. The oscillation parameters, ten percent. The tagging efficiency, fifteen percent. These are common to all channels. \[PAUSE\] **Our assumption: each source is fully correlated across the channels it affects. This is our modelling choice. It is not the published treatment of the collaboration.** Please remember this, and say it in your report.

*IT: OPERA reale (Tab. III, arXiv:1804.04912). L'ipotesi di correlazione piena è NOSTRA, non della collaborazione: ribadiscilo.*

---

## 2:50 — Hands-on C: OPERA with a covariance matrix (slides 20–21, 40 min)

**\[DO\] slide 21 — Exercise C**

**SAY:** Exercise C is the main one today. \[PAUSE\] Step one: build the covariance matrix of the backgrounds from the three sources, and diagonalise it with numpy. What is the rank? Step two: build the RooFit model. Four Poisson terms. The expected background is beta zero plus A times z. And one Gaussian constraint for each z. Step three: fit, compute the significance and the sixty-eight percent interval on mu. Step four: add the signal uncertainty, twenty percent per channel, with correlation rho. Scan rho equal to zero, zero point five, one. Step five: by how much does the interval change? Does the significance change? \[PAUSE\] This will take about forty minutes. Please ask when you are stuck: the model building is the difficult part.

*IT: C1 factor(), C2 build\_opera (formule lin e lam), C3 scansione rho. Attesi: rango 3; Z≈3.9; larghezza intervallo ≈0.96 (ρ=0), ≈1.06 (ρ=1).*

**While walking around:**

- What is the rank of your matrix? Why not four?
- What is the range of z? Is the background positive at the minimum?
- Why do we use max of the expression and a small number in the Poisson mean?
- Does the fit converge?

**At the end (SAY):** Let's see the result. \[PAUSE\] The interval on mu is about ten percent wider when the signal uncertainty is fully correlated. And the significance of mu equal to zero does not change at all. Why? \[PAUSE\] Because at mu equal to zero the signal is multiplied by zero. **The signal uncertainty cannot matter for the discovery. It matters for the measurement.** And the main message: ten events. The Poisson fluctuation dominates. The systematics change the interval by only ten percent. So improving the systematic estimate would help little here.

---

## 3:30 — Project: add a systematic (slide 22, 25 min)

**SAY:** Now the project. Choose one systematic in your case. Write it as a nuisance parameter. Give it a name, a source, and a size you can justify. \[PAUSE\] Compute your main result with and without it. And answer one question: does it change your conclusion? **That sentence goes into your showcase, as the caveat.** I walk around.

*IT: una sistematica come nuisance, con nome, sorgente, taglia; risultato con e senza.*

**Questions to ask each team:**

- Which systematic did you choose, and why?
- Is it an auxiliary measurement or a constraint?
- How big is the change on your result?

---

## 3:55 — Wrap-up (slide 23, 5 min)

**SAY:** Let's finish. Today you learned three things. First, constraint terms and auxiliary measurements, and the global observables. Second, RooStats: the ModelConfig, the hypothesis test, the profile interval, and the Asimov formula. Third, correlated systematics, covariance, diagonalisation, and rank. \[PAUSE\] For Lab 4: finish the exercises. Bring your project model with your systematic, and the result with and without it. And read the HistFactory section in the ROOT manual. \[PAUSE\] **In Lab 4 we build a binned model with HistFactory, and you present your work.** Thank you. See you in two weeks.

*IT: 3 cose, compiti, anteprima Lab 4 e showcase.*

---

## Emergency notes

- **Late?** Skip B4 (the formula comparison) and shorten the CLs remark. Never skip Exercise C: it is the capstone.
- **build\_opera fails or does not converge?** Say: Please widen the range of z, or start from mu equal to one. Use the solution notebook for the formula lines only.
- **RooStats PLC returns strange numbers?** Check the global observables and the null parameters. Say: This is a role problem, not a physics problem.
- **A student asks about the paper's 6.1 sigma?** Say: The paper uses the kinematic information of each candidate. We use only the counts, so we get less.

---

## Setup reminders (ROOT on the student laptops)

**SAY (at the start, after the recap):** A short reminder. If ROOT is not working on your laptop, please use GitHub Codespaces in your browser. Today the notebooks are heavier: the RooStats calculators and the OPERA model need a minute to run. Please be patient, and please do not close the notebook while a cell is running. \[PAUSE\] When you finish, stop your codespace. It uses your free quota while it is running.

*IT: ricorda Codespaces come piano B; le celle RooStats/OPERA richiedono circa un minuto; fermare il codespace a fine lavoro.*

**Notes for you:**

- Exercise C (OPERA) builds a model with many nuisance parameters. On a 2-core codespace it can take a few minutes: tell the students before they start.
- If a student sees a crash in RooStats on their own laptop, ask for the ROOT version. Compare it with the one in the Codespace, and suggest to continue in the Codespace.
- Students working in Codespaces download the notebooks to hand in.

| Situation | Say | IT |
| --- | --- | --- |
| Slow | This step takes a minute. Please be patient. | Ci vuole un minuto |
| Version | Which ROOT version do you have? | Che versione di ROOT? |
| Fallback | Please continue in Codespaces. | Continuate in Codespaces |
