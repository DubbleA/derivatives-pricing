## Notes:

### Chapter 1

The model for stock price evolution is 

$dS_t = \mu S_tdt + \sigma S_t dW_t$ (1.1)

- Here, \(dS_t\) represents the infinitesimal change in stock price at time \(t\). 
- \(\mu\) is the expected return rate of the stock, representing the average rate at which the stock price is expected to grow over time. 
- \(\sigma\) is the volatility of the stock, a measure of how much the stock price is expected to fluctuate. 
- \(dW_t\) is a term representing Brownian motion, capturing the random movement of the stock price.
- The equation as a whole models how stock prices evolve over time, accounting for both predictable growth and random fluctuations.

and a riskless bond, B, grows at a continuously compounding rate \(r\). The Black-Scholes pricing theory then tells us that the price of a vanilla option, with expiry \(T\) and pay-off \(f\), is equal to 

$e^{-rT} \mathbb{E}(f(S_T))$, 

where the expectation is taken under the associated risk-neutral process,

$dS_t = r S_tdt + \sigma S_t dW_t$ (1.2)

- This formula shifts the expected growth rate of the stock from \(\mu\) to the risk-free rate \(r\), aligning with the risk-neutral valuation principle. This adjustment is crucial for option pricing, as it simplifies the calculation by assuming investors are indifferent to risk.

We can solve equation (1.2) by passing to the log and using Ito's lemma

$d \text{log} S_t = (r - \frac{1}{2} \sigma^2)dt + \sigma dW_t$ (1.3)

- Ito's lemma is a key mathematical tool in financial engineering, allowing us to work with the logarithm of stock prices for easier manipulation and solution finding.
- This step simplifies the stochastic differential equation by focusing on the log of the stock price, which has more tractable mathematical properties.

Since this process is constant-coefficient, it has the solution

log \(S_t = \) log \(S_0 + (r - \frac{1}{2} \sigma^2)t + \sigma W_t\) (1.4)

- \(S_0\) is the initial stock price.
- This equation provides a formula for calculating the log of the stock price at any time \(t\), which will be utilized in option pricing.

\(W_t\) is a Brownian motion, therefore \(W_t\) is distributed as a Gaussian with mean 0 and variance \(T\), so we can write

$W_t = \sqrt{T}N(0,1)$ (1.5)

- This reflects the normal distribution of stock price movements over time, grounded in the theory of Brownian motion.

\(\therefore\)

log \(S_t = \) log \(S_0 + (r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)\) (1.6)
 
which after raising the logs is equivalent to:

$S_T = S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)}$ (1.7)

- This is the final formula used for simulating stock prices at time \(T\), crucial for option pricing.

Which finally leads us to the price of a vanilla option

$e^{-rT} \mathbb{E}(f(S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)}))$

- This formula calculates the present value of the expected payoff of the option, using the risk-neutral process.

The objective of our Monte Carlo simulation is to approximate this expectation by using the law of large numbers, which tells us that if \(Y_j\) are a sequence of identically distributed independent random variables, then with probability 1 the sequence \(\frac{1}{N}\sum_{j=1}^{n} Y_j\) converges to \(\mathbb{E}(Y_1)\)

- Monte Carlo simulation is a computational technique that uses random sampling to estimate mathematical functions and simulate the behavior of complex systems.

We now have an outline for an algorithm to price a call option by Monte Carlo. We can draw a random variable, \(x\), from \(N(0,1)\) distribution and compute

$f(S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}x})$ where \(f(S) = (S - K)_+\). We do this many times and then take the average. We then multiply this average by \(e^{-rT}\) and we are done. 

- Here, \(K\) is the strike price of the option. 
- \((S - K)_+\) represents the payoff of a call option, which is the maximum of \(S - K\) and 0. This formula is used to simulate the payoff of the option across a large number of scenarios, and the average of these simulations gives us an approximation of the option's price.
