# CS463 Homework 2: Diagnosing Performance Differences

## Preliminaries: The Scientific Process

What we are doing in this class as a whole may be better described as engineering than science. After all, we are only studying the effective and efficient use of man-made artifacts. That said, the computer is sufficiently complex that the scientific process provides a good workflow. For your reference, here is a brief review of the scientific method as applied to system performance.

- **Observation / Question Formulation**  
  We may observe that two apparently similar programs perform differently, depending on whether a variable is allocated on the stack or on the heap. We may question why.

- **Falsifiable Hypothesis**  
  We may come up with one or more explanations for our observations, or hypotheses. For example, "Stack memory accesses are faster than heap memory accesses." The hypothesis doesn't have to be good, but it must be falsifiable: the hypothesis must produce predictions, that can be shown through repeatable experiment to be true or false.

  Thus, "variables with names starting with the letter q are quicker," is a valid, falsifiable hypothesis. It predicts that the access time of a variable named "qVar" will on average be lower than a variable named "sVar".

- **Experiment to Validate / Falsify Hypothesis**  

  A carefully designed experiment can then be used to test this prediction. If the experiments do not confirm the predictions, we have either falsified the hypothesis, or performed an inaccurate experiment.

Note that depending on the experiment, it can be quite difficult to convince yourself that the experiment itself is accurate. A combination of careful experimental design, and using multiple predictions and tests to validate the same hypothesis can both help build confidence in a hypothesis.

Generally, proving a hypothesis to be true is virtually impossible. However, if the hypothesis produces accurate, and falsifiable, predictions then it is a good hypothesis. At some point, you might even start calling it a theory.

## Introduction

In this homework, we study pairs of simple programs, which exhibit very different performance despite performing the same function, executing essentially the same algorithm, and overall looking very similar at first glance. We form hypotheses explaining the performance difference, make predictions based on the hypotheses, then test them through experiment.

## Prerequisites

You will need the tools from HW1 to do this homework. In addition, you will find `objdump -d`, `gcc -S`, or `disass` in `gdb` useful for inspecting the produced executable.

## Assignment

Your job is to explain, for each pair of programs, the fundamental cause of the performance difference. We'll use the scientific process outlined in the course notes for this. For each pair of programs, the observation is that the execution time differs. Thus, for each pair of programs:

- Present a brief, falsifiable hypothesis explaining the discrepancy.
- Describe a falsifiable prediction that the hypothesis makes about the pair of programs.
- Present experimental results that validate the prediction.

You can use any tool you want to investigate the program, but be careful about the order of hypothesis, prediction, and experiment. If you did your experiments before you came up with the final hypothesis, you've violated the principle, and are more likely to end up with an invalid hypothesis.

Clone the HW2 template from [https://github.com/uicperformance/fastandslow.git](https://github.com/uicperformance/fastandslow.git).

### one vs. one_opt

`one` runs almost 1000× slower than `one_opt`. Formulate a hypothesis explaining why, use the hypothesis to produce a prediction about compiler behaviors, and test it. *Hint: what happens if you try to print out the value of count after the loop?*

### two_opt vs. two

`two_opt` runs much faster than `two`, despite modifying a global variable. This is somehow different from the previous case.

*Hint: Also, what happens if you change `count++;` to `count*=8; count/=3;`?*

### three_opt vs. two_opt

`three_opt` is a lot slower than `two_opt`. What does the keyword `volatile` do? You can probably google your way to a great hypothesis, but let's see a good prediction and test. *Hint: what happens if you change `count++;` to `count=i;`?*

### array packed vs. 64-byte spread

Use the `cachestress` program, to run these two commands:

- `cachestress -s 1048576 -i 1`
- `cachestress -s 1048676 -i 64`

The 64-byte interval version significantly slower than the 1 byte version, even though they perform the same number of operations. Describe your hypothesis and what it is based on, make falsifiable predictions, and report how you tested these predictions. *Hint: what happens when you change the size? Performance counters can make a direct measurement, but can you validate your hypothesis with just timing measurements?*

### larger spreads are slower, then faster again!

Now try this little bash script on the command line:

`for((i=1;i<1000000;i*=2)); do ./cachestress -s 1048576 -i $i; done`


It runs cachestress for a range of steps, where the execution time grows substantially up to some step size (4096 on my machines), then shrinks again eventually reaching the same speed as step size 1.

For this part, propose two falsifiable hypotheses. One hypothesis explaining why cachestress slows down as the step size increases. And a second hypothesis explaining how it speeds up again for even larger step sizes. For both hypotheses, describe an experiment and show an outcome that matches the prediction.

### optional, open question: 128-byte steps are faster than 64

On pages, with the 1M size above, 128-byte intervals are consistently faster than both 64-byte and 256-byte intervals. Form a falsifiable hypothesis explaining this phenomenon, and demonstrate its predictive value by experiment.

### Turn-in instructions

Similar to the previous homework, turn-in is by email to `jakob@uic.edu`. Please include the following for each part above (in bulleted, easily readable form please!):

- Your hypothesis explaining the observed performance difference.
- Your falsifiable prediction based on the hypothesis.
- Your experiment, meant to validate the prediction.
- The outcome of the experiment.

If you went through several rounds of the process before deciding on the hypothesis you turned in, feel free to include any prior hypotheses as well. As a reminder, the course grade is in no way impacted by your assignment turn-in. Use this turn-in as an opportunity to get feedback on your hypotheses, predictions, and experiments. Turning in something not based on your own work, or something not arrived at through the scientific process outlined above, would be pointless. Don't waste your time and mine.
