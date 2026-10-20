# ENUBET: energy deposit in a scintillator pad

**Field:** beam instrumentation · **Used in:** project case

**Question.** What is the fraction of events with two particles crossing the pad, and what is the detector resolution?

**Source.** Inspired by Figure 4 of “Status of the ENUBET project”, J. Phys.: Conf. Ser. 1056 (2018) 012047.

| File | Content |
|---|---|
| `data/enubet_histo.dat` | 95 bins of the energy deposit (first bin centre 0.025, width 0.01; 5334 entries); two columns: bin centre, counts |

## Project brief

- **Lab 1/2:** composite non-extended model. One-particle deposit: Landau (mean in [0, 0.4], sigma in [0.005, 0.05]); two-particle deposit: the Landau convolved with itself; both smeared by a Gaussian resolution (sigma in [0.005, 0.08]). See `course/optional/convolution_resolution.ipynb`.
- **Lab 3:** the resolution and the Landau parameters as nuisance parameters; effect on the 2-particle fraction.
- **Lab 4:** binned model with HistFactory; showcase.
- *Caveat to watch:* correlation between the resolution and the Landau width.

Milestones are in `course/project/README.md`. The original exercise text is `exercise-original.md` (draft extraction). Solutions are published at the end of the course.
