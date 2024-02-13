## Notes:

### Chapter 1

The model for stock price evolution is 

$dS_t = \mu S_tdt$ + $\sigma S_t dW_t$ (1.1)

and a riskless bond, B, grows at a continuously compounding rate r. The Black-Scholes pricing theory then tells us that the price of a vanilla option, with expiry T and pay-off f, is equal to 

$e^{-rT} \mathbb{E}(f(S_T))$, 

where the expectation is taken under the associated risk-neutral process,

$dS_t = r S_tdt$ + $\sigma S_t dW_t$ (1.2)

We can solve equation (1.2) by passing to the log and using Ito's lemma

$d$ log $S_t = (r - \frac{1}{2} \sigma^2)dt + \sigma dW_t$ (1.3)

Since this process is constant-coefficient, it has the solution

log $S_t = $ log $S_0 + (r - \frac{1}{2} \sigma^2)t + \sigma W_t$ (1.4)

$W_t$ is a Brownian motion, therefore $W_t$ is distributed as a Gaussian with mean 0 and variance T, so we can write

$W_t = \sqrt{T}N(0,1)$ (1.5)

$\therefore$

log $S_t = $ log $S_0 + (r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)$ (1.6)
 
which after raising the logs is equivalent to:

$S_T = S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)}$ (1.7)

Which finally leads us to the price of a vanilla option

$e^{-rT} \mathbb{E}(f(S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)}))$

The objective of our Monte Carlo simulation is to approximate this expectation by using the law of large numbers, which tells us that if $Y_j$ are a sequence of identically distributed independent random variables, then with probability 1 the sequence $\frac{1}{N}\sum_{j=1}^{n} Y_j$ converges to $\mathbb{E}(Y_1)$

We now have an outline for an algorithm to price a call option by Monte Carlo. We can draw a random variable, x, from N(0,1) distribution and compute

$f(S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}x})$ where $f(S) = (S - K)_+$. We do this many times and then take the average. We then multiply this average by $e^{-rt}$ and we are done. 