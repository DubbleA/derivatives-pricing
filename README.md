# C++ Derivatives Pricing Engine

This project is an implementation of a C++ derivatives pricing engine, based on the concepts and techniques covered in Mark Joshi's book "C++ Design Patterns & Derivatives Pricing". The engine utilizes various design patterns and C++ features to create a flexible and extensible framework for pricing financial derivatives.

For my full notes check out [Chapter Notes](notes.md)

For the original project roadmap and goals check out [roadmap.md](roadmap.md)

## Key Concepts and Learnings

### Monte Carlo Simulation
- Monte Carlo simulation is used to price options by approximating the risk-neutral expectation of the option's payoff.
- The Law of Large Numbers is leveraged to approximate the risk-neutral expectation through repeated simulations.
- The Black-Scholes model is used to simulate stock price evolution, accounting for both predictable growth and random fluctuations.

### Object-Oriented Programming (OOP)
- Encapsulation is implemented to create modular and reusable components, such as the `VanillaOption` and `PayOff` classes.
- Inheritance and virtual functions are utilized to create a hierarchy of classes and enable polymorphic behavior.
- The Bridge pattern is employed to separate the interface and implementation, allowing for independent variation of both.

### Design Patterns
- The Strategy pattern is used to make routines more flexible by allowing the user to specify aspects of how an algorithm works through inputted classes.
- Decoration is a technique for adding functionality to a class without changing its interface, by placing a class around another class with the same interface.
- Templates are utilized to avoid code duplication across similar classes.

### Random Number Generation
- A custom random number generator class is implemented for backtesting purposes.
- Anti-thetic sampling is achieved through decoration, enhancing the efficiency of Monte Carlo simulations.

### Exotic Options and Template Pattern
- Components for an exotic options engine are designed, identified, and implemented.
- The Black-Scholes path generation engine is created to simulate asset price paths.

### Trees and Implied Volatilities
- Tree-based methods are implemented to price derivatives.
- Newton-Raphson method and function template arguments are used for solving implied volatilities.
- The pros and cons of templatization are discussed.

### Factory Pattern and Code Refactoring
- The Factory pattern is employed to automate registration and creation of objects.
- The codebase is refactored to improve readability, maintainability, and adherence to design patterns.

## File Structure

- `SimpleMC.h`: Contains the main Monte Carlo simulation function for pricing vanilla options.
- `Parameters.h`: Defines classes for storing and managing parameters such as volatility and interest rates.
- `PayOffBridge.h`: Implements the Bridge pattern to decouple the `VanillaOption` and `PayOff` classes.
- `MCStatistics.h`: Provides a class for gathering and storing statistics from Monte Carlo simulations.
- `Vanilla.h`: Defines the `VanillaOption` class for representing vanilla options.

## Future Enhancements

- Extend the engine to support additional exotic options and pricing models.
- Optimize the performance of the Monte Carlo simulations through parallel computing techniques.
- Integrate with real-time market data feeds for live pricing and risk management.

## References

- Joshi, M. S. (2004). C++ Design Patterns and Derivatives Pricing. Cambridge University Press.

