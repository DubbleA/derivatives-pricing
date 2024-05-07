# Notes:

The model for stock price evolution is 

$dS_t = \mu S_tdt + \sigma S_t dW_t$ (1.1)

- Here, $dS_t$ represents the infinitesimal change in stock price at time $t$. 
- $\mu$ is the expected return rate of the stock, representing the average rate at which the stock price is expected to grow over time. 
- $\sigma$ is the volatility of the stock, a measure of how much the stock price is expected to fluctuate. 
- $dW_t$ is a term representing Brownian motion, capturing the random movement of the stock price.
- The equation as a whole models how stock prices evolve over time, accounting for both predictable growth and random fluctuations.

and a riskless bond, B, grows at a continuously compounding rate $r$. The Black-Scholes pricing theory then tells us that the price of a vanilla option, with expiry $T$ and pay-off $f$, is equal to 

$e^{-rT} \mathbb{E}(f(S_T))$, 

where the expectation is taken under the associated risk-neutral process,

$dS_t = r S_tdt + \sigma S_t dW_t$ (1.2)

- This formula shifts the expected growth rate of the stock from $\mu$ to the risk-free rate $r$, aligning with the risk-neutral valuation principle. This adjustment is crucial for option pricing, as it simplifies the calculation by assuming investors are indifferent to risk.

We can solve equation (1.2) by passing to the log and using Ito's lemma

$d \text{log} S_t = (r - \frac{1}{2} \sigma^2)dt + \sigma dW_t$ (1.3)

- Ito's lemma is a key mathematical tool in financial engineering, allowing us to work with the logarithm of stock prices for easier manipulation and solution finding.
- This step simplifies the stochastic differential equation by focusing on the log of the stock price, which has more tractable mathematical properties.

Since this process is constant-coefficient, it has the solution

log $S_t = $ log $S_0 + (r - \frac{1}{2} \sigma^2)t + \sigma W_t$ (1.4)

- $S_0$ is the initial stock price.
- This equation provides a formula for calculating the log of the stock price at any time $t$, which will be utilized in option pricing.

$W_t$ is a Brownian motion, therefore $W_t$ is distributed as a Gaussian with mean 0 and variance $T$, so we can write

$W_t = \sqrt{T}N(0,1)$ (1.5)

- This reflects the normal distribution of stock price movements over time, grounded in the theory of Brownian motion.

$\therefore$

log $S_t = $ log $S_0 + (r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)$ (1.6)
 
which after raising the logs is equivalent to:

$S_T = S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)}$ (1.7)

- This is the final formula used for simulating stock prices at time $T$, crucial for option pricing.

Which finally leads us to the price of a vanilla option

$e^{-rT} \mathbb{E}(f(S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}N(0,1)}))$

- This formula calculates the present value of the expected payoff of the option, using the risk-neutral process.

The objective of our Monte Carlo simulation is to approximate this expectation by using the law of large numbers, which tells us that if $Y_j$ are a sequence of identically distributed independent random variables, then with probability 1 the sequence $\frac{1}{N}\sum_{j=1}^{n} Y_j$ converges to $\mathbb{E}(Y_1)$

- Monte Carlo simulation is a computational technique that uses random sampling to estimate mathematical functions and simulate the behavior of complex systems.

We now have an outline for an algorithm to price a call option by Monte Carlo. We can draw a random variable, $x$, from $N(0,1)$ distribution and compute

$f(S_0e^{(r - \frac{1}{2} \sigma^2)T + \sigma \sqrt{T}x})$ where $f(S) = (S - K)_+$. We do this many times and then take the average. We then multiply this average by $e^{-rT}$ and we are done. 

- Here, $K$ is the strike price of the option. 
- $(S - K)_+$ represents the payoff of a call option, which is the maximum of $S - K$ and 0. This formula is used to simulate the payoff of the option across a large number of scenarios, and the average of these simulations gives us an approximation of the option's price.

### Key points
- Options can be priced by risk-neutral expectation
- Monte Carlo uses the Law of Large Numbers to approximate this risk-neutral expectation
- Reuse is as much a social issue as a technical one
- Procedural Programs can be hard to extend and reuse
- Classes allow us to encapsulate concepts which makes reuse and extensibility a lot easier
- Making classes closely model real-world concepts makes them easier to design and to explain
- Classes allow us to separate the design of the interface from the coding of the implementation


## Encapsulation

### Key Points
- Using a pay-off class allows us to add extra forms of pay-offs without modifying our Monte Carlo routine.
- By overloading operator() we can make an object look like a function.
- const enforces extra disclipline by forcing the coder to be aware of which code is allowed to change things and which code cannot. 
- const code can run faster
- The open-closed principline says that code should be open for extension but closed for modification
- Private data helps us to separate interface from implementation

## Inheritance and virtual functions

### Key Points

- Inheritance expresses 'is a' relationships
- A virtual function is bound at run time instead of at compile time
- We cannot have objects from classes with pure virtual functions
- We have to pass inherited class objects by reference if we do not wish to change the virtual functions
- Virtual functions are implemented via a table of function pointers
- If a class has a pure virtual function then it should have a virtual destructor

## Bridging with a virtual constructor

4.6 Beware of new. Everytime we copy a bridged object, we are implicitly using the new command. So if our code involves a lot of 
passing around objects, its important to not copy unnecessarily (we can avoid this by using move semantics or pass by reference).

When we create variables normally, (not using new), the compiler gets them an area of memory known as the stack. The important thing is that these
variables are always destroyed in reverse order from their creation (which is why its called the stack). Each variable as declared is added to top of the stack and deleted when it is removed from the top. If we want to destroy variables in a different order (what happens when we use new), we would have to scan the stack down to the point where the variable was stored then move all the variables further up the stack down a bit to cover up the gap caused by the release of memory. 

The compiler therefore does not use the stack for new but instead uses a different area of memory known as a heap. For this area of memory, the code keeps track of which pieces are in use and which pieces are not. Everytime new is called, the compiler has to find an empty piece of memory which is large enough and mark the memory as being in use. When delete is called, the code marks the memory as being free again.

### Key Points

- Cloning gives us a method of implementing a virtual copy constructor
- The rule of three says that if we need any one of a copy constructor, destructor, and assignment operator then we need all three
- We can use a wrapper class to hide all the memory handling, allowing us to treat a polymorphic object just like any other object
- the bridge pattern allows us to separate interface and implementation, enabling us to vary the two indepently
- the new command is slow
- We have to be careful to ensure the self-assignment does not cause crashes


## 5 Strategies, Decoration, and Statistics

Standard design pattern: the decorator pattern. We added functionality to a class without changing the interface. This process is called decoration. The most important part is that, since the decorated class has the same interface as the undecorated class, any decoration which can be applied to the original class can also be applied to the decorated class. We can therefore decorate as many times as we wish, but it might not be useful.

In this chapter we have seen that we can allow the user to specify aspects of how an algorithm works by making part of the algorithm be carried out in an inputed class. We have also examined the techniques of decoration and templatization. 

### Key Points
- Routines can be made more flexible by using the strategy pattern
- Making part of an algorithm be implemented by an inputted class is called the strategy pattern
- For code that is very similar accross many different classes, we can use tempates to save time in rewriting
- If we want containers of polymorphic objects, we must use wrappers or pointers
- Decoration is the technique of adding functionality by placing a class around a class which has the same interface; i.e. the outer class is inherited from the same base class
- A class can be decorated several times