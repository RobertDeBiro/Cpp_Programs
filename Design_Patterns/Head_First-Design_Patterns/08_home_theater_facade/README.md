# Facade Pattern - Home Theater System

## Overview

Demonstration of the **Facade Pattern** using a home theater system example. Shows how to provide a simplified interface to a complex subsystem, making it easier to use while still allowing direct access when needed.

## Key Concepts

- **Simplification:** Provide a unified, simple interface to a complex subsystem
- **Decoupling:** Client depends only on facade, not subsystem components
- **Principle of Least Knowledge:** Client interacts with fewer objects (only facade)
- **Convenience:** Common tasks wrapped in simple methods
- **Flexibility:** Facade doesn't prevent direct subsystem access if needed

## Project Structure

```text
08_home_theater_facade/
├── CMakeLists.txt              # Build configuration
├── main.cpp                    # Main program entry point
├── inc/                        # Header files
│   ├── HomeTheaterFacade.h     # Facade (simplified interface)
│   ├── Amplifier.h             # Subsystem component
│   ├── DvdPlayer.h             # Subsystem component
│   ├── CdPlayer.h              # Subsystem component
│   ├── Projector.h             # Subsystem component
│   ├── Screen.h                # Subsystem component
│   ├── TheaterLights.h         # Subsystem component
│   ├── PopcornPopper.h         # Subsystem component
│   └── Tuner.h                 # Subsystem component
├── src/                        # Source files (empty for header-only implementation)
├── out/
│   └── build/                  # Build output directory
├── scripts/                    # Build and run scripts
│   ├── conf.sh                 # Configure CMake
│   ├── build.sh                # Build project
│   ├── run.sh                  # Run executable
│   └── all.sh                  # Run all steps (configure + build + run)
├── UML/                        # UML diagrams
│   └── diagram.puml            # PlantUML class diagram
├── Facade_Pattern.md         # Comprehensive pattern analysis
└── README.md
```

## Building and Running

### Option 1: Using the all-in-one script (Recommended)

```bash
cd scripts
./all.sh
```

This will configure, build, and run the project in one step.

### Option 2: Step-by-step

```bash
cd scripts
./conf.sh   # Configure CMake
./build.sh  # Build project
./run.sh    # Run executable
```

### Option 3: Manual CMake

```bash
cmake -S . -B out/build
cd out/build
make
./home_theater_facade
```

## Expected Output

```text
=== Facade Pattern - Home Theater System ===

--- WITHOUT Facade (Complex Client Code) ---
Get ready to watch a movie...
Popcorn Popper on
Popcorn Popper popping popcorn!
Theater Ceiling Lights dimming to 10%
Theater Screen going down
Top-O-Line Projector on
Top-O-Line Projector in widescreen mode (16x9 aspect ratio)
Top-O-Line Amplifier on
Top-O-Line Amplifier setting DVD player to Top-O-Line DVD Player
Top-O-Line Amplifier surround sound on (5 speakers, 1 subwoofer)
Top-O-Line Amplifier setting volume to 5
Top-O-Line DVD Player on
Top-O-Line DVD Player playing "Raiders of the Lost Ark"

... movie is now playing ...

Shutting movie theater down...
Popcorn Popper off
Theater Ceiling Lights on
Theater Screen going up
Top-O-Line Projector off
Top-O-Line Amplifier off
Top-O-Line DVD Player stopped "Raiders of the Lost Ark"
Top-O-Line DVD Player eject
Top-O-Line DVD Player off

========================================

--- WITH Facade (Simplified Client Code) ---
Get ready to watch a movie...
[...same sequence as above...]

--- Additional Facade Features ---

** Listen to CD:
Get ready for an audio experience...
Theater Ceiling Lights on
Top-O-Line Amplifier on
Top-O-Line Amplifier setting CD player
Top-O-Line Amplifier stereo mode on
Top-O-Line Amplifier setting volume to 11
Top-O-Line CD Player on
Top-O-Line CD Player playing "Dark Side of the Moon"

** Listen to Radio:
Tuning in the airwaves...
Top-O-Line Tuner on
Top-O-Line Tuner setting frequency to 101.5
Top-O-Line Amplifier on
Top-O-Line Amplifier setting tuner
Top-O-Line Amplifier stereo mode on
Top-O-Line Amplifier setting volume to 5

=== Demonstration Complete ===

Key Observations:
1. WITHOUT Facade: Client must call 15+ methods on 6 objects
2. WITH Facade: Client calls 1 method (watchMovie)
3. Facade simplifies but doesn't hide - can still access subsystem
4. Facade follows Principle of Least Knowledge
5. Facade decouples client from subsystem complexity
6. Adding new facade methods doesn't modify subsystem
```

## Files

### Facade (in `inc/`)

- `HomeTheaterFacade.h` - Provides simplified interface to home theater subsystem

### Subsystem Components (in `inc/`)

- `Amplifier.h` - Audio amplifier with multiple input sources
- `DvdPlayer.h` - DVD player with playback controls
- `CdPlayer.h` - CD player with playback controls
- `Projector.h` - Video projector with display modes
- `Screen.h` - Motorized projection screen
- `TheaterLights.h` - Dimmable lighting system
- `PopcornPopper.h` - Popcorn maker (because every theater needs one!)
- `Tuner.h` - Radio tuner for AM/FM reception

### Client

- `main.cpp` - Demonstration program showing facade usage and comparison

## Design Highlights

### Modern C++ Features Used

- **Smart Pointers** (`std::unique_ptr`) - Automatic memory management
- **C++11 Attributes** (`[[maybe_unused]]`) - Suppress unused parameter warnings
- **Explicit Constructors** - Prevent implicit conversions
- **Const Correctness** - Methods marked appropriately
- **Default Parameters** - Convenient construction
- **String Literals** - Modern string handling

### The Problem: Complex Subsystem

Without facade, client code to watch a movie looks like this:

```cpp
// Client must know about and interact with 8 different components!
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
dvd->play("Raiders of the Lost Ark");

// ... watch movie ...

// Then must remember to shut everything down in reverse order
popper->off();
lights->on();
screen->up();
projector->off();
amp->off();
dvd->stop();
dvd->eject();
dvd->off();
```

**Problems:**
- Client must know about 8 subsystem components
- Client must call 15+ methods in correct sequence
- Easy to forget steps or get order wrong
- Tight coupling between client and subsystem
- Violates Principle of Least Knowledge
- Difficult to maintain and test

### The Solution: Facade Pattern

With facade, the same operation becomes:

```cpp
// Client only needs to know about the facade
homeTheater->watchMovie("Raiders of the Lost Ark");

// ... watch movie ...

// Shutdown is equally simple
homeTheater->endMovie();
```

**Benefits:**
- Client calls 1 method instead of 15+
- Client only knows about 1 class (facade) instead of 8
- Correct sequence guaranteed by facade
- Easy to use, hard to misuse
- Loose coupling
- Follows Principle of Least Knowledge
- Much easier to maintain and test

### Facade Implementation

```cpp
class HomeTheaterFacade {
private:
    // Facade composes subsystem components
    Amplifier* amp;
    Tuner* tuner;
    DvdPlayer* dvd;
    CdPlayer* cd;
    Projector* projector;
    Screen* screen;
    TheaterLights* lights;
    PopcornPopper* popper;

public:
    // Constructor takes references to subsystem components
    HomeTheaterFacade(Amplifier* amplifier, Tuner* tunerComponent,
                     DvdPlayer* dvdPlayer, CdPlayer* cdPlayer,
                     Projector* projectorDevice, Screen* theaterScreen,
                     TheaterLights* theaterLights, PopcornPopper* popcornPopper)
        : amp(amplifier), tuner(tunerComponent), dvd(dvdPlayer),
          cd(cdPlayer), projector(projectorDevice), screen(theaterScreen),
          lights(theaterLights), popper(popcornPopper) {}

    // Simplified method encapsulates complex sequence
    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie..." << std::endl;

        // Facade delegates to subsystem components
        // in the correct sequence
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
        std::cout << "Shutting movie theater down..." << std::endl;

        // Proper shutdown sequence
        popper->off();
        lights->on();
        screen->up();
        projector->off();
        amp->off();
        dvd->stop();
        dvd->eject();
        dvd->off();
    }

    // Additional simplified methods for other use cases
    void listenToCd(const std::string& cdTitle) { /* ... */ }
    void endCd() { /* ... */ }
    void listenToRadio(double frequency) { /* ... */ }
    void endRadio() { /* ... */ }
};
```

### Key Facade Pattern Characteristics

1. **Simplification, Not Hiding:** Facade provides a simple interface but doesn't prevent direct access to subsystem components if needed for advanced usage

2. **Composition:** Facade doesn't own subsystem components - they're passed in. This allows flexibility in component lifecycle management

3. **Task-Oriented Methods:** Facade methods represent common tasks (watchMovie, listenToCd) rather than low-level operations

4. **Multiple Facades:** Can create multiple facades for the same subsystem for different use cases

5. **No Modification:** Subsystem components remain unchanged - facade is an additional layer

## Principle of Least Knowledge (Law of Demeter)

The Facade Pattern embodies the **Principle of Least Knowledge**, which states:

> "Talk only to your immediate friends"

### Without Facade:

```cpp
void clientCode() {
    // Client "knows" about 8 classes
    Amplifier amp;
    Tuner tuner;
    DvdPlayer dvd;
    CdPlayer cd;
    Projector projector;
    Screen screen;
    TheaterLights lights;
    PopcornPopper popper;

    // Client must interact with all of them
    popper.on();
    lights.dim(10);
    // ... etc
}
```

Client has 8 dependencies - violates Principle of Least Knowledge.

### With Facade:

```cpp
void clientCode() {
    // Client only "knows" about 1 class
    HomeTheaterFacade homeTheater(...);

    // Client interacts only with facade
    homeTheater.watchMovie("Movie");
}
```

Client has 1 dependency - follows Principle of Least Knowledge.

### Benefits of Least Knowledge

- **Reduced Coupling:** Fewer dependencies = easier to change
- **Easier Testing:** Mock only facade, not entire subsystem
- **Better Encapsulation:** Subsystem details hidden
- **Clearer Intent:** Client code reads like high-level operations

## Pattern Benefits Demonstrated

1. **Dramatic Simplification:** 15+ method calls reduced to 1
2. **Loose Coupling:** Client depends only on facade
3. **Encapsulation:** Subsystem complexity hidden
4. **Maintainability:** Changes to subsystem don't affect client
5. **Readability:** Client code expresses intent clearly
6. **Testability:** Easy to mock facade for testing
7. **Flexibility:** Facade doesn't prevent direct subsystem access

## Architecture

```text
┌────────────┐
│   Client   │ ← Uses only facade (1 dependency)
│  main()    │
└──────┬─────┘
       │ uses
       ↓
┌──────────────────┐
│ HomeTheaterFacade│ ← Facade (simplifies interface)
├──────────────────┤
│ - amp*           │
│ - tuner*         │
│ - dvd*           │
│ - cd*            │
│ - projector*     │
│ - screen*        │
│ - lights*        │
│ - popper*        │
│ + watchMovie()   │
│ + endMovie()     │
│ + listenToCd()   │
│ + listenToRadio()│
└────────┬─────────┘
         │ delegates to
         ↓
┌─────────────────────────────────────┐
│      Complex Subsystem              │
│ ┌──────────┐  ┌───────────┐        │
│ │Amplifier │  │ DvdPlayer │        │
│ └──────────┘  └───────────┘        │
│ ┌──────────┐  ┌───────────┐        │
│ │CdPlayer  │  │ Projector │        │
│ └──────────┘  └───────────┘        │
│ ┌──────────┐  ┌───────────┐        │
│ │  Screen  │  │TheaterLights│      │
│ └──────────┘  └───────────┘        │
│ ┌──────────┐  ┌───────────┐        │
│ │PopcornPopper│ │   Tuner  │       │
│ └──────────┘  └───────────┘        │
│                                     │
│ 8 classes, 37 methods               │
└─────────────────────────────────────┘
```

## Comparison: Before vs After

| Aspect | Without Facade | With Facade |
|--------|----------------|-------------|
| **Dependencies** | Client knows 8 classes | Client knows 1 class |
| **Method Calls** | 15+ method calls | 1 method call |
| **Complexity** | High (must remember sequence) | Low (facade handles it) |
| **Coupling** | Tight (client → subsystem) | Loose (client → facade) |
| **Error Prone** | Easy to forget steps | Correct sequence guaranteed |
| **Readability** | Low (scattered operations) | High (intent clear) |
| **Maintenance** | Difficult (changes ripple) | Easy (changes isolated) |
| **Testing** | Difficult (mock 8 classes) | Easy (mock 1 facade) |

## Real-World Applications

### Software Libraries

```cpp
// Without facade - complex database API
Connection* conn = database.createConnection();
conn->open("host", "port", "user", "password");
Statement* stmt = conn->createStatement();
stmt->setQuery("SELECT * FROM users");
ResultSet* rs = stmt->execute();
while (rs->next()) {
    // Process results
}
rs->close();
stmt->close();
conn->close();

// With facade - simplified API
DatabaseFacade db("host", "port", "user", "password");
auto users = db.query("SELECT * FROM users");
for (const auto& user : users) {
    // Process results
}
// Resources automatically managed
```

### Embedded Systems

```cpp
// Complex sensor subsystem
class SensorFacade {
private:
    TemperatureSensor* tempSensor;
    PressureSensor* pressureSensor;
    HumiditySensor* humiditySensor;
    DataLogger* logger;
    Calibrator* calibrator;

public:
    // Simplified method for common task
    EnvironmentalData readEnvironment() {
        // Facade handles complex sequence:
        // 1. Calibrate sensors
        // 2. Read all sensors
        // 3. Validate readings
        // 4. Log data
        // 5. Return consolidated results
        calibrator->calibrateAll();
        float temp = tempSensor->read();
        float pressure = pressureSensor->read();
        float humidity = humiditySensor->read();
        logger->log(temp, pressure, humidity);
        return EnvironmentalData{temp, pressure, humidity};
    }
};

// Client code is simple
SensorFacade sensors;
auto data = sensors.readEnvironment();  // Simple!
```

### Compiler Front-Ends

```cpp
// Compiler facade simplifies complex compilation process
class CompilerFacade {
private:
    Lexer* lexer;
    Parser* parser;
    SemanticAnalyzer* analyzer;
    Optimizer* optimizer;
    CodeGenerator* codegen;

public:
    bool compile(const std::string& sourceFile,
                const std::string& outputFile) {
        // Facade orchestrates entire compilation pipeline
        auto tokens = lexer->tokenize(sourceFile);
        auto ast = parser->parse(tokens);
        analyzer->analyze(ast);
        optimizer->optimize(ast);
        codegen->generate(ast, outputFile);
        return true;
    }
};

// Client just wants to compile
CompilerFacade compiler;
compiler.compile("program.cpp", "program.o");  // That's it!
```

### Game Engines

```cpp
// Complex game subsystems
class GameFacade {
private:
    RenderEngine* renderer;
    PhysicsEngine* physics;
    AudioEngine* audio;
    InputManager* input;
    SceneManager* scene;

public:
    void startLevel(const std::string& levelName) {
        // Facade handles complex initialization sequence
        scene->load(levelName);
        renderer->setActiveCamera(scene->getCamera());
        physics->setGravity(scene->getGravity());
        audio->playBackgroundMusic(scene->getMusic());
        input->enableControls();
    }
};
```

## Pattern Relationships

### Facade vs Adapter

- **Facade:** Simplifies interface (many-to-one, same functionality)
- **Adapter:** Changes interface (one-to-one, different interface)
- **Example:** Facade provides `watchMovie()` that calls subsystem. Adapter makes `Turkey` compatible with `Duck` interface.

### Facade vs Decorator

- **Facade:** Simplifies (hides complexity)
- **Decorator:** Enhances (adds behavior, same interface)
- **Example:** Facade wraps subsystem for simplicity. Decorator wraps component to add functionality.

### Facade vs Mediator

- **Facade:** Unidirectional (client → facade → subsystem)
- **Mediator:** Bidirectional (components communicate via mediator)
- **Example:** Facade client calls facade, which calls subsystem. Mediator has components calling mediator, which calls other components.

### Facade vs Proxy

- **Facade:** Different interface (simpler)
- **Proxy:** Same interface (controls access)
- **Example:** Facade provides `watchMovie()` for complex operations. Proxy provides same interface but adds access control/lazy loading.

## When to Use Facade Pattern

Use Facade when:

- You want a simple interface to a complex subsystem
- There are many dependencies between clients and subsystem
- You want to layer your subsystem (facade as entry point)
- You want to decouple client from subsystem implementation
- You want to wrap a poorly designed API with a better one
- Common tasks require many steps across multiple classes

Don't use Facade when:

- Subsystem is already simple
- Client needs fine-grained control over subsystem
- Creating facade adds unnecessary layer
- Subsystem has only one or two classes

## Key Takeaways

1. **Facade provides simplified interface** to complex subsystem without hiding it
2. **Reduces dependencies** - client talks to facade, not subsystem
3. **Follows Principle of Least Knowledge** - client knows fewer classes
4. **Encapsulates complexity** - client doesn't need to know details
5. **Doesn't prevent direct access** - can still use subsystem if needed
6. **Makes subsystem easier to use** - task-oriented methods
7. **Decouples client from subsystem** - easier to maintain and change

## Further Reading

See [Facade_Pattern.md](Facade_Pattern.md) for detailed architectural analysis, including:

- Problem analysis (subsystem complexity, tight coupling, knowledge dependencies)
- Real-world examples and use cases
- Design principles explained (Principle of Least Knowledge, Dependency Inversion)
- Benefits, trade-offs, and when to use Facade Pattern
- C++ specific considerations (smart pointers, composition, RAII)
- Pattern relationships (Adapter, Decorator, Mediator, Proxy)
- Multiple facades and subsystem layering

## Summary

The Facade Pattern enables:

- **Simplification:** Complex subsystem hidden behind simple interface
- **Decoupling:** Client depends only on facade, not subsystem
- **Maintainability:** Changes to subsystem don't affect client
- **Readability:** Client code expresses high-level intent
- **Flexibility:** Doesn't prevent direct subsystem access
- **Testability:** Easy to mock facade for unit tests

**When to use:** You have a complex subsystem with many classes and methods, clients need to perform common tasks that involve multiple subsystem operations, and you want to provide a simple, easy-to-use interface while still allowing direct access when needed.

**Key Insight:** Don't force clients to understand and manage complex subsystems - provide a facade that handles the complexity and presents a simple interface. This makes the subsystem much easier to use while maintaining full functionality for advanced users.
