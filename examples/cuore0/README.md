# CUORE-0: neutrinoless double-beta decay

**Field:** nuclear physics · **Used in:** project case

**Question.** Is there a peak at the $^{130}$Te $Q$-value (2527.5 keV)? If not, what upper limit on the signal can you set?

**Source.** Simplified problem modelled on the first phase of the CUORE experiment.

| File | Content |
|---|---|
| `data/cuore0.dat` | 233 reconstructed energies in keV (2471–2569) |
| `data/cuore0.root` | the same data in ROOT format |

## Project brief

- **Lab 2:** background (flat or exponential) + the known $^{60}$Co sum peak (about 2506 keV); baseline extended fit; HESSE vs MINOS.
- **Lab 3:** add the possible peak at 2527.5 keV; one systematic (energy scale, resolution or efficiency) as a nuisance parameter; profile interval or upper limit (see `course/optional/upper_limit_cls.ipynb`).
- **Lab 4:** binned version (HistFactory), showcase.
- *Caveat to watch:* very few events, Gaussian approximations of the intervals fail.

Milestones are in `course/project/README.md`. The original exercise text is `exercise-original.md` (draft extraction). Solutions are published at the end of the course.
