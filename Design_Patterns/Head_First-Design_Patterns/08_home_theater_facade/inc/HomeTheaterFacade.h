#ifndef HOMETHEATERFACADE_H
#define HOMETHEATERFACADE_H

#include "Amplifier.h"
#include "DvdPlayer.h"
#include "Projector.h"
#include "Screen.h"
#include "TheaterLights.h"
#include "PopcornPopper.h"
#include "Tuner.h"
#include "CdPlayer.h"
#include <iostream>
#include <string>

/**
 * @brief Facade - Simplifies Home Theater Subsystem
 *
 * The HomeTheaterFacade provides a simplified interface to the complex
 * home theater subsystem. Instead of requiring the client to interact
 * with 8 different components and remember the correct sequence of
 * 15+ method calls, the facade provides simple methods like watchMovie()
 * and endMovie().
 *
 * Key benefits:
 * - Simplifies client code
 * - Hides subsystem complexity
 * - Provides convenient methods for common tasks
 * - Follows Principle of Least Knowledge
 * - Decouples client from subsystem
 *
 * Note: Facade doesn't prevent access to subsystem - clients can still
 * use subsystem components directly if they need fine-grained control.
 */
class HomeTheaterFacade {
private:
    // Subsystem components (composition)
    Amplifier* amp;
    Tuner* tuner;
    DvdPlayer* dvd;
    CdPlayer* cd;
    Projector* projector;
    Screen* screen;
    TheaterLights* lights;
    PopcornPopper* popper;

public:
    /**
     * @brief Constructor - Facade is passed references to all subsystem components
     *
     * The facade doesn't own these components - they're managed by the client.
     * This allows flexibility in subsystem component creation and lifecycle.
     *
     * @param amplifier Amplifier component
     * @param tunerComponent Tuner component
     * @param dvdPlayer DVD player component
     * @param cdPlayer CD player component
     * @param projectorDevice Projector component
     * @param theaterScreen Screen component
     * @param theaterLights Lights component
     * @param popcornPopper Popcorn popper component
     */
    HomeTheaterFacade(Amplifier* amplifier,
                     Tuner* tunerComponent,
                     DvdPlayer* dvdPlayer,
                     CdPlayer* cdPlayer,
                     Projector* projectorDevice,
                     Screen* theaterScreen,
                     TheaterLights* theaterLights,
                     PopcornPopper* popcornPopper)
        : amp(amplifier),
          tuner(tunerComponent),
          dvd(dvdPlayer),
          cd(cdPlayer),
          projector(projectorDevice),
          screen(theaterScreen),
          lights(theaterLights),
          popper(popcornPopper) {}

    /**
     * @brief Simplified method to watch a movie
     *
     * Encapsulates the complex sequence of operations needed to watch a movie:
     * 1. Turn on popcorn popper and pop popcorn
     * 2. Dim the lights
     * 3. Lower the screen
     * 4. Turn on projector and set widescreen mode
     * 5. Turn on amplifier, set to DVD, surround sound, and volume
     * 6. Turn on DVD player and play movie
     *
     * Without facade: Client must remember and execute 15+ method calls
     * With facade: Client calls one method
     *
     * @param movie Name of the movie to watch
     */
    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie..." << std::endl;

        // Delegate to subsystem components
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

    /**
     * @brief Simplified method to end a movie
     *
     * Encapsulates the shutdown sequence:
     * 1. Turn off popcorn popper
     * 2. Turn on lights
     * 3. Raise the screen
     * 4. Turn off projector
     * 5. Turn off amplifier
     * 6. Stop and eject DVD, then turn off player
     *
     * Again, without facade this would require remembering many
     * method calls in the correct sequence.
     */
    void endMovie() {
        std::cout << "Shutting movie theater down..." << std::endl;

        popper->off();
        lights->on();
        screen->up();
        projector->off();
        amp->off();
        dvd->stop();
        dvd->eject();
        dvd->off();
    }

    /**
     * @brief Simplified method to listen to CD
     *
     * Demonstrates that facades can provide multiple simplified interfaces
     * to the same subsystem for different use cases.
     *
     * @param cdTitle Title of the CD to play
     */
    void listenToCd(const std::string& cdTitle) {
        std::cout << "Get ready for an audio experience..." << std::endl;

        lights->on();
        amp->on();
        amp->setCd(cd);
        amp->setStereoSound();
        amp->setVolume(11);
        cd->on();
        cd->play(cdTitle);
    }

    /**
     * @brief Simplified method to end CD playback
     */
    void endCd() {
        std::cout << "Shutting down CD..." << std::endl;

        amp->off();
        cd->eject();
        cd->off();
    }

    /**
     * @brief Simplified method to listen to radio
     *
     * @param frequency Radio frequency
     */
    void listenToRadio(double frequency) {
        std::cout << "Tuning in the airwaves..." << std::endl;

        tuner->on();
        tuner->setFrequency(frequency);
        amp->on();
        amp->setTuner(tuner);
        amp->setStereoSound();
        amp->setVolume(5);
    }

    /**
     * @brief Simplified method to end radio listening
     */
    void endRadio() {
        std::cout << "Shutting down the tuner..." << std::endl;

        tuner->off();
        amp->off();
    }
};

#endif // HOMETHEATERFACADE_H
