/**
 * @file main.cpp
 * @brief Facade Pattern - Home Theater System Demonstration
 *
 * Demonstrates the Facade pattern where:
 * - Complex subsystem: Amplifier, DvdPlayer, Projector, Screen, Lights, PopcornPopper, etc.
 * - Facade: HomeTheaterFacade provides simplified interface (watchMovie, endMovie)
 * - Client: main() uses facade instead of directly interacting with subsystem
 *
 * Key Points:
 * - Client code is dramatically simplified (2 method calls vs 15+)
 * - Subsystem complexity is hidden behind facade
 * - Facade doesn't prevent direct subsystem access if needed
 * - Follows Principle of Least Knowledge (Law of Demeter)
 * - Decouples client from subsystem implementation details
 *
 * Comparison:
 * WITHOUT Facade: Client must call 15+ methods on 6 different objects in correct sequence
 * WITH Facade: Client calls 1 method (watchMovie) on facade
 */

#include "HomeTheaterFacade.h"
#include <iostream>
#include <memory>

/**
 * @brief Demonstrates what client code looks like WITHOUT facade
 *
 * This shows the complexity that facade eliminates.
 * Client must know about all subsystem components and the correct
 * sequence of operations.
 */
void demonstrateWithoutFacade(Amplifier* amp, DvdPlayer* dvd, Projector* projector,
                             Screen* screen, TheaterLights* lights, PopcornPopper* popper) {
    std::cout << "--- WITHOUT Facade (Complex Client Code) ---" << std::endl;
    std::cout << "Get ready to watch a movie..." << std::endl;

    // Client must know and call all these methods in correct order
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

    std::cout << std::endl;
    std::cout << "... movie is now playing ..." << std::endl;
    std::cout << std::endl;

    // Shutdown also requires many calls
    std::cout << "Shutting movie theater down..." << std::endl;
    popper->off();
    lights->on();
    screen->up();
    projector->off();
    amp->off();
    dvd->stop();
    dvd->eject();
    dvd->off();

    std::cout << std::endl;
}

/**
 * @brief Demonstrates what client code looks like WITH facade
 *
 * Client code is dramatically simplified - just call facade methods.
 */
void demonstrateWithFacade(HomeTheaterFacade* homeTheater) {
    std::cout << "--- WITH Facade (Simplified Client Code) ---" << std::endl;

    // Client calls one simple method
    homeTheater->watchMovie("Raiders of the Lost Ark");

    std::cout << std::endl;
    std::cout << "... movie is now playing ..." << std::endl;
    std::cout << std::endl;

    // Shutdown also simplified
    homeTheater->endMovie();

    std::cout << std::endl;
}

/**
 * @brief Demonstrates additional facade methods
 */
void demonstrateOtherFeatures(HomeTheaterFacade* homeTheater) {
    std::cout << "--- Additional Facade Features ---" << std::endl;
    std::cout << std::endl;

    // Listen to CD
    std::cout << "** Listen to CD:" << std::endl;
    homeTheater->listenToCd("Dark Side of the Moon");
    std::cout << std::endl;

    homeTheater->endCd();
    std::cout << std::endl;

    // Listen to Radio
    std::cout << "** Listen to Radio:" << std::endl;
    homeTheater->listenToRadio(101.5);
    std::cout << std::endl;

    homeTheater->endRadio();
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Facade Pattern - Home Theater System ===" << std::endl;
    std::cout << std::endl;

    // Create subsystem components
    // Note: In production, these might be created by a factory or dependency injection
    auto amp = std::make_unique<Amplifier>();
    auto tuner = std::make_unique<Tuner>();
    auto dvd = std::make_unique<DvdPlayer>();
    auto cd = std::make_unique<CdPlayer>();
    auto projector = std::make_unique<Projector>();
    auto screen = std::make_unique<Screen>();
    auto lights = std::make_unique<TheaterLights>();
    auto popper = std::make_unique<PopcornPopper>();

    // Demonstrate complexity WITHOUT facade
    demonstrateWithoutFacade(amp.get(), dvd.get(), projector.get(),
                            screen.get(), lights.get(), popper.get());

    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // Create facade
    auto homeTheater = std::make_unique<HomeTheaterFacade>(
        amp.get(), tuner.get(), dvd.get(), cd.get(),
        projector.get(), screen.get(), lights.get(), popper.get()
    );

    // Demonstrate simplicity WITH facade
    demonstrateWithFacade(homeTheater.get());

    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // Demonstrate additional facade features
    demonstrateOtherFeatures(homeTheater.get());

    std::cout << "=== Demonstration Complete ===" << std::endl;
    std::cout << std::endl;

    std::cout << "Key Observations:" << std::endl;
    std::cout << "1. WITHOUT Facade: Client must call 15+ methods on 6 objects" << std::endl;
    std::cout << "2. WITH Facade: Client calls 1 method (watchMovie)" << std::endl;
    std::cout << "3. Facade simplifies but doesn't hide - can still access subsystem" << std::endl;
    std::cout << "4. Facade follows Principle of Least Knowledge" << std::endl;
    std::cout << "5. Facade decouples client from subsystem complexity" << std::endl;
    std::cout << "6. Adding new facade methods doesn't modify subsystem" << std::endl;

    return 0;
}
