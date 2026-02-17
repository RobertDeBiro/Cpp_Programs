# Facade Pattern - Comprehensive Analysis

## Pattern Overview

**Facade Pattern** provides a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use.

**Key Intent:** Simplify a complex subsystem by providing a simplified interface that performs common tasks.

**Also Known As:** Structural Wrapper

**Core Concept:** The Facade doesn't encapsulate the subsystem - clients can still access subsystem classes directly if needed. The Facade just provides a more convenient interface for common operations.

---

## The Problem: Complex Subsystem Interaction

### Bad Architecture Example: Direct Subsystem Manipulation

```cpp
// BAD: Client directly manipulates 8+ subsystem components
void watchMovie() {
    // 1. Setup projector
    Projector projector;
    projector.on();
    projector.setInput("DVD");
    projector.wideScreenMode();

    // 2. Setup amplifier
    Amplifier amp;
    amp.on();
    amp.setDvd(&dvd);
    amp.setSurroundSound();
    amp.setVolume(5);

    // 3. Setup DVD player
    DvdPlayer dvd;
    dvd.on();
    dvd.play("Raiders of the Lost Ark");

    // 4. Setup screen
    Screen screen;
    screen.down();

    // 5. Setup lights
    TheaterLights lights;
    lights.dim(10);

    // 6. Setup popcorn maker
    PopcornPopper popper;
    popper.on();
    popper.pop();

    // Total: 15+ method calls across 6 different classes!
}

// And you have to do it all in REVERSE to stop the movie:
void endMovie() {
    popper.off();
    lights.on();
    screen.up();
    projector.off();
    amp.off();
    dvd.stop();
    dvd.eject();
    dvd.off();
    // 8 more method calls!
}
```

### Pain Points

1. **Tight Coupling to Complex Subsystem**
   - Client must know about ALL subsystem classes
   - Client must understand subsystem component interactions
   - Client must know the correct sequence of operations
   - Changes to subsystem ripple through all clients

2. **High Cognitive Load**
   - Must remember 15+ steps to perform one task
   - Easy to forget steps or get order wrong
   - Each client reimplements the same complex sequence
   - Error-prone: miss one step and system doesn't work

3. **Code Duplication**
   - Every place that needs "watch movie" duplicates the 15 steps
   - Bug fixes must be applied everywhere
   - Maintenance nightmare

4. **Violates Principle of Least Knowledge**
   - Client knows about Projector, Amplifier, DvdPlayer, Screen, Lights, Popcorn
   - Client knows about their dependencies
   - Client knows about interaction patterns
   - Creates fragile coupling

5. **Not Testable**
   - Must mock 8+ classes to test client code
   - Complex setup for every test
   - Tests become brittle (depend on internal subsystem details)

### Example of Cascading Problems

```cpp
// As system grows, complexity explodes:
class HomeTheaterClient {
public:
    void watchDvd() {
        // 15 lines of setup code...
    }

    void watchStreamingMovie() {
        // 18 lines of setup code (slightly different)...
    }

    void playGame() {
        // 20 lines of setup code...
    }

    void listenToRadio() {
        // 12 lines of setup code...
    }
};

// PROBLEMS:
// 1. Each method duplicates similar setup logic
// 2. Adding new component (e.g., streaming device) requires updating ALL methods
// 3. Changing component interface breaks 10+ places
// 4. Cannot reuse setup logic
// 5. 65+ lines of procedural code scattered across class
```

**Result:** System becomes unmaintainable maze of subsystem interactions. Adding features becomes exponentially harder.

### UML Diagram: Bad Design

See `UML/Bad_Direct_Subsystem_Access.puml` for the class diagram showing the client directly controlling all subsystem components (red-highlighted problem class).

---

---

## Design Principles

### 1. Principle of Least Knowledge (Law of Demeter)

**Definition:** Only talk to your immediate friends. Don't talk to strangers.

**Formal Definition:** A method of an object should only call methods of:
- The object itself
- Objects passed as parameters
- Objects it creates
- Component objects (fields)

**NOT:**
- Objects returned by other methods (chaining)
- Global objects

**Before Facade:**

```cpp
// Violates Principle of Least Knowledge
void watchMovie() {
    // Talks to 8 different subsystem objects (strangers)
    projector.on();             // Friend 1
    projector.setInput("DVD");
    amp.on();                   // Friend 2
    amp.setDvd(&dvd);
    dvd.on();                   // Friend 3
    screen.down();              // Friend 4
    lights.dim(10);             // Friend 5
    popper.on();                // Friend 6
    // Knows about internal subsystem structure!
}
```

**After Facade:**

```cpp
// Follows Principle of Least Knowledge
void watchMovie() {
    // Talks only to facade (one friend)
    homeTheater.watchMovie("Raiders of the Lost Ark");
    // Doesn't know about subsystem structure!
}
```

**Why Principle of Least Knowledge Matters:**

```cpp
// Violates: Chaining through multiple objects
customer.getWallet().getCreditCard().getNumber();
// Problem: Client depends on Customer, Wallet, AND CreditCard
// If Wallet implementation changes, client breaks

// Follows: Only talk to immediate friends
customer.getCreditCardNumber();  // Customer handles delegation
// Client only depends on Customer
```

### 2. Single Responsibility Principle

**Separation of Concerns:**

- **Subsystem classes:** Each responsible for specific functionality
- **Facade:** Responsible for coordinating subsystem for common tasks
- **Client:** Responsible for business logic, not subsystem coordination

Each class has ONE reason to change.

**Before Facade:**

```cpp
class UserInterface {
    void onPlayButtonClick() {
        // ❌ Responsible for UI AND subsystem coordination
        projector.on();
        amp.on();
        dvd.on();
        // ... 15 more lines
    }
};
```

**After Facade:**

```cpp
class UserInterface {
    void onPlayButtonClick() {
        // ✅ Only responsible for UI
        homeTheater.watchMovie(selectedMovie);
    }
};
```

### 3. Open/Closed Principle

**Definition:** Classes should be open for extension but closed for modification.

**Before Facade:**

```cpp
// Adding streaming device requires modifying all client code
void watchStreamingMovie() {
    projector.on();
    amp.on();
    streamingDevice.on();  // ← New line added everywhere
    streamingDevice.selectService("Netflix");
    // ... modify 10 different methods in 5 different classes
}
```

**After Facade:**

```cpp
// Facade encapsulates the change
class HomeTheaterFacade {
    void watchStreamingMovie(const std::string& service) {
        // Only facade modified, clients unchanged
        projector.on();
        amp.on();
        streamingDevice.on();
        streamingDevice.selectService(service);
    }
};

// Client code unchanged!
homeTheater.watchStreamingMovie("Netflix");
```

### 4. Dependency Inversion Principle

**Definition:** Depend on abstractions, not concrete classes.

**Before Facade:**

```cpp
// High-level client depends on low-level subsystem classes
class MovieApp {
    Projector* projector;      // Direct dependency
    Amplifier* amp;            // Direct dependency
    DvdPlayer* dvd;            // Direct dependency
    // Depends on 8+ low-level classes
};
```

**After Facade:**

```cpp
// High-level depends on high-level abstraction
class MovieApp {
    HomeTheater* theater;  // Depends on facade abstraction
    // No knowledge of subsystem
};

// Can even use interface for facade
class HomeTheater {  // Abstract interface
public:
    virtual void watchMovie(const std::string& movie) = 0;
    virtual void endMovie() = 0;
};

class AdvancedHomeTheater : public HomeTheater {
    // Different implementation with more components
};
```

---

## The Solution: Facade Pattern

### Structure

```text
┌──────────────────────────────────────────────────────────────┐
│                         Client                               │
│                                                              │
│   void watchMovie() {                                        │
│       homeTheater.watchMovie("Movie");                       │
│   }                                                          │
└───────────────────────────┬──────────────────────────────────┘
                            │ uses simplified interface
                            ↓
        ┌───────────────────────────────────────────┐
        │          Facade                           │
        │    (HomeTheaterFacade)                    │
        ├───────────────────────────────────────────┤
        │ + watchMovie(movie: string)               │
        │ + endMovie()                              │
        │ + listenToRadio()                         │
        │ + watchDvd()                              │
        └───────┬───────────────────────────────────┘
                │ coordinates subsystem
                │
    ┌───────────┴──────────────────┬──────────────┬───────────┐
    ↓                              ↓              ↓           ↓
┌─────────┐   ┌──────────┐   ┌─────────┐   ┌─────────┐   ┌─────────┐
│Projector│   │Amplifier │   │DvdPlayer│   │Screen   │   │Lights   │
├─────────┤   ├──────────┤   ├─────────┤   ├─────────┤   ├─────────┤
│+ on()   │   │+ on()    │   │+ on()   │   │+ up()   │   │+ on()   │
│+ off()  │   │+ off()   │   │+ play() │   │+ down() │   │+ dim()  │
│+ setIn()│   │+ setVol()│   │+ stop() │   └─────────┘   └─────────┘
└─────────┘   └──────────┘   └─────────┘
    ↑              ↑              ↑
    └──────────────┴──────────────┴──────── Complex Subsystem
                                            (Many classes with detailed interfaces)

Key:
- Client: Uses simplified interface (1-2 method calls)
- Facade: Provides unified, high-level interface
- Subsystem: Complex set of classes (client can still access directly if needed)
```

### Key Components

1. **Facade (HomeTheaterFacade)**
   - Provides simple methods for complex tasks
   - Knows which subsystem classes are responsible for a request
   - Delegates client requests to appropriate subsystem objects
   - Does NOT prevent access to subsystem (not encapsulation)

2. **Subsystem Classes (Projector, Amplifier, etc.)**
   - Implement detailed subsystem functionality
   - Handle work assigned by Facade
   - Have no knowledge of Facade
   - Can be used directly by clients if needed

3. **Client (MovieApp)**
   - Uses Facade for common operations
   - Can still access subsystem directly for advanced features
   - Simplified code with less coupling

### How It Works

```cpp
// 1. Client wants to watch movie (simple operation)
homeTheater.watchMovie("Raiders of the Lost Ark");

// 2. Facade coordinates subsystem
void HomeTheaterFacade::watchMovie(const std::string& movie) {
    // Facade knows the entire complex sequence
    std::cout << "Get ready to watch a movie...\n";

    // Step 1: Prepare viewing environment
    popper->on();
    popper->pop();
    lights->dim(10);
    screen->down();

    // Step 2: Setup audio/video equipment
    projector->on();
    projector->wideScreenMode();

    amp->on();
    amp->setDvd(dvd);
    amp->setSurroundSound();
    amp->setVolume(5);

    // Step 3: Play movie
    dvd->on();
    dvd->play(movie);
}

// 3. Client doesn't know about 15 method calls across 6 classes
// Client just knows: "watchMovie" does everything
```

**Critical Insight:** The Facade doesn't hide the subsystem. Clients can still access `Projector`, `Amplifier`, etc. directly for advanced operations. The Facade just provides a convenient interface for common tasks.

### Facade Implementation

```cpp
// Subsystem classes (simplified)
class Amplifier {
public:
    void on() { std::cout << "Amplifier on\n"; }
    void off() { std::cout << "Amplifier off\n"; }
    void setDvd(DvdPlayer* dvd) { std::cout << "Amplifier setting DVD\n"; }
    void setSurroundSound() { std::cout << "Amplifier surround sound on\n"; }
    void setVolume(int level) { std::cout << "Amplifier volume: " << level << "\n"; }
};

class DvdPlayer {
public:
    void on() { std::cout << "DVD Player on\n"; }
    void off() { std::cout << "DVD Player off\n"; }
    void play(const std::string& movie) { std::cout << "Playing: " << movie << "\n"; }
    void stop() { std::cout << "DVD Player stopped\n"; }
    void eject() { std::cout << "DVD Player eject\n"; }
};

class Projector {
public:
    void on() { std::cout << "Projector on\n"; }
    void off() { std::cout << "Projector off\n"; }
    void wideScreenMode() { std::cout << "Projector wide screen mode\n"; }
    void setInput(const std::string& input) { std::cout << "Projector input: " << input << "\n"; }
};

class Screen {
public:
    void up() { std::cout << "Screen up\n"; }
    void down() { std::cout << "Screen down\n"; }
};

class TheaterLights {
public:
    void on() { std::cout << "Lights on\n"; }
    void dim(int level) { std::cout << "Lights dimmed to " << level << "%\n"; }
};

class PopcornPopper {
public:
    void on() { std::cout << "Popcorn Popper on\n"; }
    void off() { std::cout << "Popcorn Popper off\n"; }
    void pop() { std::cout << "Popping corn!\n"; }
};

// FACADE: Simplifies subsystem interaction
class HomeTheaterFacade {
private:
    // Facade holds references to subsystem components
    Amplifier* amp;
    DvdPlayer* dvd;
    Projector* projector;
    Screen* screen;
    TheaterLights* lights;
    PopcornPopper* popper;

public:
    // Facade takes subsystem components
    HomeTheaterFacade(Amplifier* amp, DvdPlayer* dvd, Projector* proj,
                      Screen* screen, TheaterLights* lights, PopcornPopper* popper)
        : amp(amp), dvd(dvd), projector(proj), screen(screen),
          lights(lights), popper(popper) {}

    // Simplified interface: One method for complex operation
    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie...\n";

        // Facade coordinates the entire subsystem
        popper->on();
        popper->pop();
        lights->dim(10);
        screen->down();
        projector->on();
        projector->wideScreenMode();
        amp->on();
        amp->setDvd(dvd);
        amp->setSurroundSound();
        amp->setVolume(5);
        dvd->on();
        dvd->play(movie);
    }

    void endMovie() {
        std::cout << "Shutting movie theater down...\n";

        // Facade handles cleanup in correct order
        popper->off();
        lights->on();
        screen->up();
        projector->off();
        amp->off();
        dvd->stop();
        dvd->eject();
        dvd->off();
    }

    // Additional simplified operations
    void listenToRadio(double frequency) {
        std::cout << "Tuning to radio...\n";
        lights->on();
        amp->on();
        amp->setVolume(5);
        // ... configure for radio
    }
};

// Client usage - DRAMATICALLY SIMPLER
void clientCode() {
    // Setup subsystem (only once)
    Amplifier amp;
    DvdPlayer dvd;
    Projector projector;
    Screen screen;
    TheaterLights lights;
    PopcornPopper popper;

    // Create facade
    HomeTheaterFacade homeTheater(&amp, &dvd, &projector,
                                   &screen, &lights, &popper);

    // BEFORE: 15+ lines of code
    // AFTER: 1 line
    homeTheater.watchMovie("Raiders of the Lost Ark");

    // ... enjoy movie ...

    // BEFORE: 8+ lines of cleanup code
    // AFTER: 1 line
    homeTheater.endMovie();

    // Client can STILL access subsystem directly if needed
    amp.setVolume(11);  // Advanced operation not in facade
}
```

### Real-World Network Stack Facade Implementation

```cpp
// Network subsystem classes (complex low-level details)
class TcpSocket {
public:
    bool connect(const std::string& ip, int port);
    int write(const char* data, size_t len);
    int read(char* buffer, size_t len);
    void close();
    void setTimeout(int ms);
};

class DnsResolver {
public:
    std::string resolve(const std::string& hostname);
    void setNameserver(const std::string& ns);
};

class SslConnection {
public:
    bool handshake();
    bool verifyCertificate(const std::string& hostname);
    int write(const char* data, size_t len);
    int read(char* buffer, size_t len);
    void shutdown();
};

class HttpRequestBuilder {
public:
    void setMethod(const std::string& method);
    void setPath(const std::string& path);
    void addHeader(const std::string& name, const std::string& value);
    void setBody(const std::string& body);
    std::string build();
};

class HttpResponseParser {
public:
    void parse(const char* data, size_t len);
    int getStatusCode();
    std::string getHeader(const std::string& name);
    std::string getBody();
};

// FACADE: Simplified HTTP client
class HttpClient {
private:
    // Facade manages subsystem
    std::unique_ptr<TcpSocket> socket;
    std::unique_ptr<DnsResolver> dns;
    std::unique_ptr<SslConnection> ssl;
    std::unique_ptr<HttpRequestBuilder> requestBuilder;
    std::unique_ptr<HttpResponseParser> responseParser;

    int timeout = 30000;

    void initializeSubsystems() {
        socket = std::make_unique<TcpSocket>();
        dns = std::make_unique<DnsResolver>();
        ssl = std::make_unique<SslConnection>();
        requestBuilder = std::make_unique<HttpRequestBuilder>();
        responseParser = std::make_unique<HttpResponseParser>();
    }

    std::string connect(const std::string& host, int port) {
        // Facade coordinates DNS + TCP connection
        std::string ip = dns->resolve(host);
        socket->setTimeout(timeout);
        if (!socket->connect(ip, port)) {
            throw std::runtime_error("Connection failed");
        }
        return ip;
    }

    void setupSsl(const std::string& host) {
        // Facade coordinates SSL handshake
        if (!ssl->handshake()) {
            throw std::runtime_error("SSL handshake failed");
        }
        if (!ssl->verifyCertificate(host)) {
            throw std::runtime_error("Certificate verification failed");
        }
    }

public:
    HttpClient() {
        initializeSubsystems();
    }

    // SIMPLIFIED INTERFACE: One method for GET request
    std::string get(const std::string& url) {
        // Facade hides 70+ lines of networking code
        UrlParser parser(url);

        // Step 1: Connect (facade handles DNS + TCP)
        connect(parser.host(), parser.port());

        // Step 2: SSL (facade handles handshake + verification)
        if (parser.isHttps()) {
            setupSsl(parser.host());
        }

        // Step 3: Build request (facade handles headers)
        requestBuilder->setMethod("GET");
        requestBuilder->setPath(parser.path());
        requestBuilder->addHeader("Host", parser.host());
        std::string request = requestBuilder->build();

        // Step 4: Send (facade handles writing)
        ssl->write(request.data(), request.size());

        // Step 5: Receive (facade handles reading + parsing)
        char buffer[4096];
        int bytesRead = ssl->read(buffer, sizeof(buffer));
        responseParser->parse(buffer, bytesRead);

        return responseParser->getBody();
    }

    // SIMPLIFIED INTERFACE: One method for POST request
    std::string post(const std::string& url, const std::string& body) {
        // Facade handles complex POST logic
        UrlParser parser(url);
        connect(parser.host(), parser.port());
        setupSsl(parser.host());

        requestBuilder->setMethod("POST");
        requestBuilder->setPath(parser.path());
        requestBuilder->addHeader("Host", parser.host());
        requestBuilder->addHeader("Content-Type", "application/json");
        requestBuilder->setBody(body);

        std::string request = requestBuilder->build();
        ssl->write(request.data(), request.size());

        char buffer[4096];
        int bytesRead = ssl->read(buffer, sizeof(buffer));
        responseParser->parse(buffer, bytesRead);

        return responseParser->getBody();
    }

    void setTimeout(int ms) { timeout = ms; }
};

// CLIENT: Dramatically simplified
void clientCode() {
    HttpClient client;

    // BEFORE: 70+ lines of low-level networking code
    // AFTER: 1 line
    std::string response = client.get("https://api.example.com/users");

    // POST request
    std::string body = R"({"name": "John", "email": "john@example.com"})";
    std::string result = client.post("https://api.example.com/users", body);

    // Client can still access low-level subsystem if needed for advanced features
    // (not shown here, but possible)
}
```

---

## Benefits and Trade-offs

### Benefits

1. **Simplified Interface**
   - Complex operations reduced to single method calls
   - Hides subsystem complexity from clients
   - Makes subsystem easier to use
   - **Example:** 15 lines → 1 line

2. **Decoupling Client from Subsystem**
   - Client depends only on Facade, not subsystem classes
   - Subsystem changes don't affect client (if Facade interface stable)
   - Can replace subsystem implementation without changing clients
   - **Architectural impact:** Loose coupling enables evolution

3. **Principle of Least Knowledge**
   - Client knows only about Facade
   - Doesn't know about subsystem structure
   - Reduces dependencies
   - **Result:** More maintainable system

4. **Better Organization**
   - Groups related operations together
   - Clear entry point for subsystem
   - Easier to understand system structure
   - **Developer experience:** Faster onboarding

5. **Flexibility**
   - Facade doesn't prevent direct subsystem access
   - Advanced users can bypass Facade for fine-grained control
   - Best of both worlds: simplicity + power
   - **Key insight:** Facade is not encapsulation, it's simplification

6. **Promotes Layered Architecture**
   - Clear separation between layers
   - High-level operations in Facade
   - Low-level details in subsystem
   - **Architecture:** Better separation of concerns

### Trade-offs

1. **Additional Layer of Indirection**
   - Extra object in call chain
   - Small performance overhead (usually negligible)
   - **Mitigated by:** Modern compilers optimize, benefits outweigh cost

2. **Facade Can Become God Object**
   - Risk of Facade becoming too large
   - May violate Single Responsibility if not careful
   - **Mitigated by:** Create multiple focused facades for different tasks

3. **May Hide Too Much**
   - Facade might not expose all subsystem functionality
   - Advanced users may need direct access
   - **Mitigated by:** Don't prevent direct subsystem access

4. **Coupling Facade to Subsystem**
   - Facade depends on all subsystem classes
   - Changes to subsystem may require Facade updates
   - **Mitigated by:** Acceptable coupling (Facade's job is to know subsystem)

5. **Potential Duplication**
   - Multiple facades for same subsystem (different use cases)
   - Some overlap in functionality
   - **Mitigated by:** Share common logic through delegation

### When to Use Facade Pattern

- ✅ Want to provide simple interface to complex subsystem
- ✅ Many dependencies between client and subsystem
- ✅ Want to layer your system (decouple layers)
- ✅ Subsystem is complex and difficult to use
- ✅ Want to wrap poorly designed legacy code
- ✅ Need entry point for each subsystem layer
- ❌ Subsystem is already simple (1-2 classes)
- ❌ Need to expose all subsystem functionality (not simplification)
- ❌ Performance-critical path (avoid extra indirection)

### Facade vs God Object (Anti-Pattern)

**God Object (Anti-Pattern):**

```cpp
// BAD: God Object - does everything
class SystemManager {
    // 50 different methods for unrelated tasks
    void watchMovie();
    void orderPizza();
    void checkEmail();
    void playGame();
    void doTaxes();
    // Violates Single Responsibility!
};
```

**Good Facade:**

```cpp
// GOOD: Focused facades for related subsystems
class HomeTheaterFacade {
    // Only movie/entertainment related methods
    void watchMovie();
    void listenToRadio();
    void playGame();
};

class KitchenFacade {
    // Only kitchen related methods
    void makeCoffee();
    void preheatOven();
};
```

---

---

## Pattern Relationships

### Facade vs Adapter

**Similarity:** Both provide different interface to existing code

**Difference:**
- **Facade:** Simplifies complex subsystem (many classes → simple interface)
- **Adapter:** Converts incompatible interface (one class → compatible interface)

**Intent:**
- **Facade:** Make subsystem easier to use
- **Adapter:** Make interface compatible

```cpp
// FACADE: Simplifies many classes
class HomeTheaterFacade {
    void watchMovie() {
        // Coordinates 6+ classes
        projector->on();
        amp->on();
        dvd->play();
        // ...
    }
};

// ADAPTER: Makes one class compatible
class TurkeyAdapter : public Duck {
    Turkey* turkey;
    void quack() override {
        turkey->gobble();  // Converts interface
    }
};
```

### Facade vs Mediator

**Similarity:** Both centralize communication between objects

**Difference:**
- **Facade:** Unidirectional (client → facade → subsystem)
  - Subsystem doesn't know about Facade
  - Simplifies interface
- **Mediator:** Bidirectional (colleagues ↔ mediator ↔ colleagues)
  - Colleagues know about Mediator
  - Reduces direct communication between colleagues

```cpp
// FACADE: One-way communication
class HomeTheaterFacade {
    void watchMovie() {
        amp->on();    // Facade → subsystem
        dvd->play();  // Facade → subsystem
        // Subsystem never calls back to Facade
    }
};

// MEDIATOR: Two-way communication
class ChatMediator {
    void sendMessage(User* from, std::string msg) {
        // Mediator → other users
        for (User* user : users) {
            if (user != from) user->receive(msg);
        }
    }
};

class User {
    ChatMediator* mediator;
    void send(std::string msg) {
        mediator->sendMessage(this, msg);  // User → Mediator
    }
    void receive(std::string msg) {
        // Mediator → User
    }
};
```

### Facade vs Proxy

**Similarity:** Both provide surrogate for another object

**Difference:**
- **Facade:** Wraps multiple objects (complex subsystem)
- **Proxy:** Wraps single object (same interface, adds control)

**Intent:**
- **Facade:** Simplify
- **Proxy:** Control access, add behavior (lazy loading, security, logging)

```cpp
// FACADE: Wraps many objects
class HomeTheaterFacade {
    Amplifier* amp;
    DvdPlayer* dvd;
    Projector* proj;
    // Simplifies 6+ objects
};

// PROXY: Wraps one object
class ImageProxy {
    RealImage* realImage = nullptr;

    void display() {
        if (!realImage) {
            realImage = new RealImage();  // Lazy loading
        }
        realImage->display();
    }
};
```

### Facade vs Abstract Factory

**Common Combination:** Use Abstract Factory to create subsystem for Facade

```cpp
// Abstract Factory creates subsystem components
class TheaterComponentFactory {
public:
    virtual Amplifier* createAmplifier() = 0;
    virtual DvdPlayer* createDvdPlayer() = 0;
};

class BudgetTheaterFactory : public TheaterComponentFactory {
    Amplifier* createAmplifier() override {
        return new BudgetAmplifier();
    }
    DvdPlayer* createDvdPlayer() override {
        return new DvdPlayer();
    }
};

class PremiumTheaterFactory : public TheaterComponentFactory {
    Amplifier* createAmplifier() override {
        return new PremiumAmplifier();
    }
    DvdPlayer* createDvdPlayer() override {
        return new BluRayPlayer();
    }
};

// Facade uses factory to create subsystem
class HomeTheaterFacade {
public:
    HomeTheaterFacade(TheaterComponentFactory* factory) {
        amp = factory->createAmplifier();
        dvd = factory->createDvdPlayer();
        // ...
    }
};

// Client creates facade with desired factory
auto factory = new PremiumTheaterFactory();
auto theater = new HomeTheaterFacade(factory);
theater->watchMovie("Movie");
```

### Multiple Facades for Same Subsystem

Different facades can provide different views of same subsystem:

```cpp
// Subsystem (same for all facades)
class Amplifier { /* ... */ };
class DvdPlayer { /* ... */ };
class Projector { /* ... */ };

// Facade 1: Movie watching operations
class HomeTheaterFacade {
public:
    void watchMovie(const std::string& movie);
    void endMovie();
};

// Facade 2: Gaming operations
class GamingFacade {
public:
    void startGame(const std::string& console);
    void pauseGame();
    void endGame();
};

// Facade 3: Maintenance operations
class MaintenanceFacade {
public:
    void runDiagnostics();
    void calibrateVideo();
    void updateFirmware();
};

// Each facade provides different simplified interface to same subsystem
```

### Layered Architecture with Facades

```text
┌─────────────────────────────────────────┐
│         Presentation Layer              │
│         (UI Controllers)                │
└──────────────┬──────────────────────────┘
               │ uses
               ↓
┌─────────────────────────────────────────┐
│      Application Facade Layer           │
│      (High-level business operations)   │
│  ┌──────────────┐  ┌─────────────────┐  │
│  │ MovieFacade  │  │ UserFacade      │  │
│  └──────────────┘  └─────────────────┘  │
└──────────────┬──────────────────────────┘
               │ coordinates
               ↓
┌─────────────────────────────────────────┐
│        Business Logic Layer             │
│  (Domain services, repositories)        │
└──────────────┬──────────────────────────┘
               │ uses
               ↓
┌─────────────────────────────────────────┐
│      Infrastructure Facade Layer        │
│     (Database, Network, File I/O)       │
│  ┌────────────┐  ┌──────────────────┐   │
│  │ DbFacade   │  │ NetworkFacade    │   │
│  └────────────┘  └──────────────────┘   │
└──────────────┬──────────────────────────┘
               │ coordinates
               ↓
┌─────────────────────────────────────────┐
│   Low-Level Subsystems                  │
│   (JDBC, Sockets, FileSystem)           │
└─────────────────────────────────────────┘

Facades at each layer boundary provide:
- Simplified interface to layer below
- Decoupling between layers
- Clear dependency direction (top-down)
```

---

## Summary: The Power of Facade Pattern

**Before Facade Pattern:**

- Client code cluttered with subsystem details
- 15+ method calls for simple operation
- Tight coupling to complex subsystem
- Violates Principle of Least Knowledge
- Difficult to maintain and test
- Code duplication across clients

**After Facade Pattern:**

- ✅ **Simplified Interface:** Complex operations in 1-2 method calls
- ✅ **Loose Coupling:** Client depends only on Facade
- ✅ **Least Knowledge:** Client doesn't know subsystem structure
- ✅ **Maintainable:** Subsystem changes isolated to Facade
- ✅ **Flexible:** Advanced users can still access subsystem directly
- ✅ **Testable:** Easy to mock Facade for unit tests

**Architectural Thinking:**

When you have a complex subsystem with many classes and intricate interactions, **DON'T** force every client to understand all the details. Instead, **create a Facade** that provides simple, high-level operations for common tasks. This is the essence of **simplifying complex systems** through unified interfaces.

**Real-World Impact:**

In the network stack example, Facade Pattern enables:
- HTTP request in 1 line instead of 70 lines
- Hide DNS, TCP, SSL, HTTP protocol complexity
- Easy to use for 95% of use cases
- Advanced users can still access low-level subsystem for the other 5%
- Maintainable: Network stack changes isolated to HttpClient facade
- Testable: Mock HttpClient instead of 8+ subsystem components

This transforms a complex, expert-level networking API into a simple, approachable interface that any developer can use correctly.

**Key Design Insight:**

Facade is about **reducing complexity through simplification**, not hiding. The subsystem remains accessible - Facade just provides a better way to accomplish common tasks.

---

## References

- **Design Principles:** Principle of Least Knowledge (Law of Demeter), Single Responsibility, Open/Closed, Dependency Inversion
- **C++ Features:** Smart pointers, RAII, move semantics, const correctness, exception safety, Pimpl idiom
- **Related Patterns:** Adapter (interface conversion), Mediator (bidirectional coordination), Proxy (access control), Abstract Factory (subsystem creation)
- **Real-World Applications:** API clients, library wrappers, subsystem integration, layered architectures, legacy system simplification
