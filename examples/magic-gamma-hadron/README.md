# MAGIC: gamma / hadron separation

**Field:** astroparticle physics · **Used in:** project case

**Question.** How well can ten image parameters separate gamma showers from hadronic ones, and what significance follows from a given selection?

**Source.** MAGIC gamma telescope dataset (UCI repository, see `data/magic04.names`): simulated Cherenkov telescope events.

| File | Content |
|---|---|
| `data/magic04.data` | 19 020 events: 10 image parameters and the class `g` (gamma) or `h` (hadron) |
| `data/magic04.names` | description of the columns |

## Project brief

- **Lab 2:** study one discriminating variable: fit its distribution for gammas and hadrons.
- **Lab 3:** efficiency and rejection of a selection (cuts or a classifier), expected yields, significance with the Asimov formula and with RooStats; the selection efficiency as a systematic. TMVA is optional: `course/optional/tmva_magic_demo.ipynb`.
- **Lab 4:** binned model of the classifier output; showcase.
- *Caveat to watch:* the class balance of the file is not the real one: efficiencies transfer, purity does not.

Milestones are in `course/project/README.md`. The original exercise text is `exercise-original.md` (draft extraction). Solutions are published at the end of the course.
