# Lab 2 — Speaker Script

*Companion of lab2.md (23 slides).*

## How to use this script

- Read the lines after **SAY**. **IT** = riassunto in italiano, solo per te. **\[PAUSE\]** = respira. **\[DO\]** = azione.
- Se ti perdi, riparti dalla frase in **grassetto** della slide.
- Il Lab 2 è il più “teorico” dei primi due: tieni il ritmo con le domande alla classe.
- Numeri di slide = quelli di lab2.md, divisori inclusi.

## New phrases for today

| Situation | Say | IT |
| --- | --- | --- |
| Recap | Please discuss in pairs for two minutes. | Parlatene in coppie per due minuti |
| Poll | Raise your hand if you think the answer is yes. | Alzi la mano chi pensa di sì |
| Wrong answer | Almost. Let's think about it together. | Quasi, ragioniamoci |
| Right answer | Exactly. Well done. | Esatto, bravi |
| Show | Let me show you on the plot. | Ve lo mostro sul grafico |
| Check | What do you see in the output? | Cosa vedete nell'output? |
| Stuck | Which cell fails? Please read me the error. | Quale cella fallisce? Leggetemi l'errore |
| Time left | You have five more minutes. | Cinque minuti ancora |
| Open lab | Tell me which notebook you are working on. | Dite su quale notebook state lavorando |

## Pronunciation help

| Word | Say it like |
| --- | --- |
| MIGRAD | MY-grad |
| HESSE | HESS-eh |
| MINOS | MY-nos |
| Wilks | VILKS |
| covariance | co-VAIR-ee-ans |
| correlation | co-re-LAY-shun |
| profile | PRO-file |
| coverage | KUV-er-ij |
| pull | pool |
| toy | TOY |
| boundary | BOWN-da-ree |
| nuisance | NYOO-sans |
| parabola | pa-RAB-o-la |
| asymmetric | ay-si-MET-rik |
| converge | con-VERJ |

---

## 0:00 — Recap (slides 1–3, 10 min)

**SAY (slide 1):** Good morning, and welcome back. This is Lab 2: likelihood and fit quality. In Lab 1 we built models and we fitted them. Today we open the box. We want to understand what the fit really does, how much we can trust the errors, and how to test a fit. \[PAUSE\] Then we validate it with toys.

*IT: bentornati, oggi apriamo la scatola nera del fit.*

**\[DO\] slide 2 — Recap**

**SAY:** First, a short recap. Four questions. Please discuss in pairs, for two minutes. \[PAUSE\] Question one: in the marked Poisson model, which factor is the rate, and which is the shape? Question two: extended fit, or fit with fractions. What information do we lose with fractions? Question three: why is a binned likelihood not a chi-square fit? Question four: which two notebooks of Lab 1 did you submit, and which cell was the hardest?

**After two minutes, SAY:** Let's compare. Question one? \[PAUSE\]

**Expected answers:**

1. Rate = Poisson term for n. Shape = product of the densities.
2. With fractions we lose the total yield: the rate.
3. The binned likelihood is Poisson in each bin: exact also with few or zero counts. Chi-square assumes Gaussian errors.
4. Collect two or three answers. Note the hardest cells on the board: they tell you what to repeat today. Remind them of the rule: two notebooks out of three.

*IT: 4 domande, risposte attese sopra. Segna alla lavagna le celle più difficili del Lab 1.*

**\[DO\] slide 3 — Schedule**

**SAY:** This is our plan. Three talks, three hands-on parts, two breaks. At the end, thirty minutes of open lab, to finish a notebook with me. \[PAUSE\] Please do not skip it: it is the most useful time for you.

---

## 0:10 — Talk A: What happens in fitTo (slides 4–8, 20 min)

**\[DO\] slide 5 — From pdf to number**

**SAY:** When you write fit-to, four things happen. \[PAUSE\] First, RooFit builds the negative log-likelihood. It is a function of the parameters. Second, the minimiser, called MINUIT, finds the minimum. The command is MIGRAD. Third, HESSE computes the covariance matrix from the second derivatives. Fourth, if you ask, MINOS computes asymmetric errors. **Today we call each step ourselves, with a class called RooMinimizer.**

*IT: fitTo = NLL → MIGRAD → HESSE → (MINOS). Oggi li chiamiamo uno a uno.*

**\[DO\] slide 6 — MIGRAD, HESSE, MINOS**

**SAY:** Look at the table. MIGRAD follows the gradient. It stops when the estimated distance to the minimum, the EDM, is very small. HESSE computes the matrix of second derivatives, and inverts it. The inverse is the covariance matrix. This gives symmetric errors and the correlations. \[PAUSE\] MINOS is different. It scans the likelihood. For each parameter, it looks for the points where the negative log-likelihood rises by zero point five. This gives asymmetric errors. **HESSE assumes the likelihood is a parabola. MINOS does not.** If they disagree, the likelihood is not a parabola, and we trust MINOS.

*IT: HESSE = parabola, simmetrico. MINOS = scansione, asimmetrico. Se discordano, fidati di MINOS.*

**Ask the class:** Why would the two be different? **Answer:** the likelihood is not a parabola: low statistics, a boundary, a non-linear parameter.

**\[DO\] slide 7 — Is my fit healthy?**

**SAY:** Before we use a result, we check the fit. Status must be zero. The covariance quality must be three. This means a full, accurate covariance matrix. The EDM must be tiny. No parameter should sit at its limit. And no correlation should be close to one. \[PAUSE\] **A parameter at its limit is a warning. It is not a result.**

*IT: checklist: status 0, covQual 3, EDM piccolo, nessun parametro al limite, nessuna correlazione ±1.*

**\[DO\] slide 8 — When fits go wrong**

**SAY:** Fits fail. This is normal. Look at the table. If the fit does not converge, the start values are often bad. Choose start values near the data, and bound the ranges. If you see huge errors and a correlation close to one, two parameters are doing the same job. Fix one, or change the parametrisation. If a parameter is at a limit, look at the model. \[PAUSE\] A small trick: instead of tau, fit the logarithm of tau. Or use fractions between zero and one. **When a fit works on some toys only, we have a low-statistics problem. We study it at the end of the morning.**

*IT: tabella dei sintomi. Riparametrizzare aiuta.*

---

## 0:30 — Hands-on A: Anatomy of a fit (slides 9–10, 45 min)

**\[DO\] slide 10 — Exercise A**

**SAY:** Now it is your turn. We use the same data and the same model as in Lab 1, exercise C. \[PAUSE\] Step one. Build the negative log-likelihood. Run MIGRAD and HESSE with RooMinimizer. Read the status, the EDM and the covariance quality. Step two. Run MINOS on the signal yield. Are the errors symmetric? Do they agree with HESSE? Step three. Print the correlation matrix. Which two parameters are most correlated? Step four. Plot the likelihood scan, the profile, and the HESSE parabola together. Step five. Draw the one-sigma and two-sigma contours of signal against background. \[PAUSE\] Open ex A in the lab 2 folder. You have forty-five minutes.

*IT: 5 passi. Leggili lentamente. Poi circola.*

**While walking around:**

- Did the first cell run? Did you set your student number?
- What does the check say?
- Compare the red curve and the dashed curve. Where do they separate?
- Why is the correlation negative?

**At the end (SAY):** Let's stop. Who can tell me the HESSE error and the MINOS errors? \[PAUSE\] **Notice: the MINOS interval is not symmetric. The likelihood is steeper at low signal, because the signal cannot be negative.** And the signal and the background are anti-correlated: they compete for the same events under the peak.

---

## 1:15 — BREAK (15 min)

**SAY:** Let's take a break. We restart at 10:30.

---

## 1:30 — Talk B: Intervals and nuisance parameters (slides 11–14, 20 min)

**\[DO\] slide 12 — Likelihood-ratio intervals**

**SAY:** Welcome back. Now the main idea of the day: likelihood-ratio intervals. For a single parameter, in the large-sample limit, minus two times the log of the likelihood ratio follows a chi-square distribution with one degree of freedom. This is Wilks theorem. \[PAUSE\] Practically: for a sixty-eight percent interval, we look where the negative log-likelihood rises by zero point five. For ninety-five percent, by one point nine two. **The interval is where the curve is below the minimum plus one half. It does not need to be symmetric.** This is the MINOS interval.

*IT: Wilks; 0.5 per il 68%, 1.92 per il 95%; intervallo = dove la curva sta sotto min + 0.5.*

**\[DO\] slide 13 — Nuisance parameters**

**SAY:** A real model has parameters of interest, and nuisance parameters. A nuisance parameter is something we need in the model, but we do not care about. For example, the background rate, the resolution, or an efficiency. \[PAUSE\] There are two ways to draw the likelihood. The slice: we fix the nuisance parameters at their best-fit value. This is too optimistic, because it ignores what we do not know. The profile: for each value of the parameter of interest, we fit the nuisance parameters again. **The profile is wider than the slice. The difference is the cost of the nuisance parameter.**

*IT: slice (parametri fissi, ottimista) vs profile (rifit dei nuisance). Profile più largo.*

**\[DO\] slide 14 — The on/off problem**

**SAY:** Here is a classical example. We count events in the signal region: n on. We count events in a control region: n off. The control region measures the background. The expected counts are s plus b in the signal region, and tau times b in the control region. Tau is the ratio of the sizes of the two regions. \[PAUSE\] The best fit is simple. b hat is n off divided by tau. And s hat is n on minus b hat. **The uncertainty on the background is not an input. It comes from the control region.** When you read a result like background three point eight plus or minus zero point six, this is the model behind it. In Lab 3 we add constraint terms.

*IT: on/off: due Poisson. b = n\_off/tau; s = n\_on − b. L'incertezza su b viene dalla regione di controllo.*

**Ask the class:** If tau is small, what happens to the uncertainty on b? **Answer:** it gets larger: the control region is small.

---

## 1:50 — Hands-on B: the on/off problem (slides 15–16, 45 min)

**\[DO\] slide 16 — Exercise B**

**SAY:** Exercise B uses the top-quark numbers. Seventeen events observed in the signal region. Forty in the control region. Tau equal to ten point five three. \[PAUSE\] Step one. Build the model with two Poisson distributions. Fit, and read s hat and b hat. Step two. Compute the sixty-eight percent interval on s in two ways: scan the profile, and use MINOS. Compare them. Step three. Compare with the slice. Step four. Repeat with a poorer control region: n off equal to four, tau equal to one point zero five three. The best-fit background is the same. What changes? \[PAUSE\] Forty-five minutes. Please start with the model.

*IT: B1 modello, B2 profile vs MINOS, B3 slice, B4 controllo povero.*

**While walking around:**

- What is the observable here? And the parameters?
- Is tau constant in your code?
- Check: b hat should be about three point eight.
- Is the profile the same as MINOS? It should be.

**At the end (SAY):** Let's compare. With tau equal to ten, profile and slice are almost the same. \[PAUSE\] With the poor control region, the profile is wider. **This is exactly the cost of not knowing the background.** \[PAUSE\] Question: in the notebooks you are working on, where is the control region, and what does it tell you about the background?

---

## 2:35 — BREAK (10 min)

**SAY:** Let's take a short break. Ten minutes. We restart at 11:45.

---

## 2:45 — Talk C: Validate with toys (slides 17–19, 15 min)

**\[DO\] slide 18 — Why toys?**

**SAY:** One last question. How do we know that the errors are correct? HESSE and MINOS are approximations. We can test them with toys. \[PAUSE\] The recipe has three steps. One: generate a dataset with known true parameters. Two: fit it. Three: save the result. Repeat three hundred times, or more. \[PAUSE\] We define the pull. It is the fitted value, minus the true value, divided by the estimated error. **If everything is fine, the pull has mean zero and RMS one.** The mean tells us about bias. The RMS tells us if the errors have the right size. And about sixty-eight percent of the toys should have a pull between minus one and plus one. This is the coverage.

*IT: toy → fit → pull. Media 0 = nessun bias, RMS 1 = errori giusti, copertura \~68%.*

**\[DO\] slide 19 — Low statistics**

**SAY:** What happens with few events? The likelihood is no longer a parabola. Parameters hit boundaries, for example the signal yield cannot be negative. The pulls are not Gaussian. \[PAUSE\] The remedy: report profile or MINOS intervals. Or use a full toy construction, which we see in Lab 3. And please count the failed fits. **A toy that fails is not a missing result. It is information about your model.**

*IT: bassa statistica: parametri al bordo, pull non gaussiani; riportare intervalli MINOS/profile; contare i fit falliti.*

---

## 3:00 — Hands-on C: pulls, bias, coverage (slides 20–21, 25 min)

**\[DO\] slide 21 — Exercise C**

**SAY:** Exercise C is short. We use the LHCb model again. \[PAUSE\] Step one. Write the toy loop: generate, fit, compute the pull. Use thirty-three signal events. Fill a histogram. Compute the mean, the RMS and the coverage. Step two. Repeat with five signal events. What happens to the pulls? How many fits sit at the boundary? \[PAUSE\] The loop takes about a minute. While it runs, please read the questions in the notebook. If you finish early, step C3 is optional: the same loop written in C++. Compare the time.

*IT: loop toy; N\_s=33 poi N\_s=5. Il loop impiega circa un minuto.*

**While walking around:**

- Did you reset the parameters before each toy?
- Is the dataset extended?
- How many toys failed?
- What is the shape of the pull for five events?

**At the end (SAY):** Look at the result for thirty-three events. \[PAUSE\] Mean close to zero. RMS close to one. **The errors are reliable.** Now five events. The distribution is distorted, and many fits sit at zero. **Here a symmetric error is wrong. We need another tool.** We will build it in Lab 3.

---

## 3:25 — Open lab (slide 22, 30 min)

**SAY:** Now thirty minutes of open lab. \[PAUSE\] Work on the notebook you have not finished. If you have finished, look at the third one: the solutions come later. All the notebooks of today are independent, so you can start from any. Run it from the top, and check that every check says PASS. \[PAUSE\] I walk around. Please call me early.

*IT: 30 minuti di lab aperto. Gira tra i banchi. Chiedi: su quale notebook sei? Converge? HESSE e MINOS cosa dicono?*

**Questions to ask each student:**

- Which notebook are you on? Which two will you submit?
- Does the fit converge? What does the status say?
- HESSE or MINOS: which error do you trust here, and why?
- What would break this fit?

---

## 3:55 — Wrap-up (slide 23, 5 min)

**SAY:** Let's finish. \[PAUSE\] Today you learned three things. First, what the fit does: the likelihood, MIGRAD, HESSE, MINOS. Second, the profile likelihood, and why nuisance parameters make intervals wider. Third, toys: pulls, bias and coverage. \[PAUSE\] For the next lab, in two weeks: submit two of the three notebooks, the ones you prefer, on Virtuale. The solutions of all three appear after the deadline. And please read the first two sections of the paper by Cowan, Cranmer, Gross and Vitells. The reference is on the slide. \[PAUSE\] **In Lab 3 we model systematic uncertainties, we use RooStats, and we study a real problem with correlated uncertainties.** Thank you very much. See you in two weeks.

*IT: 3 cose imparate; compiti: consegnare 2 notebook su 3 su Virtuale, leggere Cowan et al. (sez. 1-2). Anteprima Lab 3.*

---

## Emergency notes

- **Running late?** Shorten slide 8 (when fits go wrong) and skip the contour in A5. Do not skip the toys: it is the bridge to Lab 3.
- **Toy loop too slow?** Say: Please use two hundred toys instead of three hundred.
- **A student asks about Bayesian intervals?** Say: Good question. We see the frequentist and Bayesian tools in Lab 3, with RooStats.
- **Confusion between slice and profile?** Draw two curves on the board: the narrow one is the slice, the wide one is the profile.

---

## Setup reminders (ROOT on the student laptops)

**SAY (first minutes, after the recap):** One practical point. Who still has a problem with ROOT on the laptop? Please raise your hand. \[PAUSE\] If ROOT does not work, please use GitHub Codespaces in your browser. You need a free GitHub account. Please come to me in the first break, and we fix it together.

*IT: chi ha ancora problemi? Codespaces come piano B; risolvi in pausa.*

**Notes for you:**

- Ask who used Codespaces in Lab 1 and whether the quota is enough. Remind them to stop the codespace when they finish.
- The toy loop of Exercise C takes about a minute. On a slow laptop or a 2-core codespace it can take longer: suggest 200 toys instead of 300.
- If a student works in Codespaces, they download the notebooks and upload them on Virtuale.

| Situation | Say | IT |
| --- | --- | --- |
| Problem | Does the check setup say PASS? | check\_setup dice PASS? |
| Fallback | Please use Codespaces in your browser. | Usate Codespaces |
| Slow | Please use fewer toys. | Usate meno toy |
