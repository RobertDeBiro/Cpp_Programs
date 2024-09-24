/*

This sample code uses the SFML library to create music objects for each song and load the songs. It then plays the songs one by one and waits for the song to finish before playing the next one.

Please note that in order to use the SFML library, you will have to install it first. You can find the installation instructions on the SFML website: https://www.sfml-dev.org/tutorials/2.6/start-vc.php

This is just a basic example of music player using C++, it can be further expanded to have more functionality like adding volume control, adding playlists, adding pause and stop functionality, etc.

*/

#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> songs = {"song1.ogg", "song2.ogg", "song3.ogg"};
    std::vector<sf::Music> musics;

    // Create music objects for each song and load the songs
    for (const auto &song : songs) {
        sf::Music music;
        if (!music.openFromFile(song)) {
            std::cout << "Error loading " << song<< std::endl;
            return -1;
        }
        musics.push_back(music);
    }

    // Play the songs
    for (auto &music : musics) {
        music.play();
        while (music.getStatus() == sf::SoundSource::Playing) {
            // Wait for the song to finish
        }
    }

    return 0;
}
