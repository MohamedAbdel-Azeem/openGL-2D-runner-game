#include "SoundPlayer.h"
#include <iostream>
#include "fmod.hpp"

FMOD_RESULT result;
FMOD::System* pSystem = nullptr;
FMOD::Channel* backgroundChannel = nullptr;
FMOD::Channel* pChannel = nullptr;

void Soundplayer_init() {
    // First, create the FMOD system
    result = FMOD::System_Create(&pSystem); // Create the system object
    if (result != FMOD_OK) {
        std::cout << "FMOD System creation failed" << std::endl;
        return;
    }

    // Then initialize the system
    result = pSystem->init(32, FMOD_INIT_NORMAL, nullptr); // Initialize FMOD system with 32 channels
    if (result != FMOD_OK) {
        std::cout << "FMOD System initialization failed" << std::endl;
    }
}

void Soundplayer_playBackgroundMusic() {
    FMOD::Sound* pSound = nullptr;
    backgroundChannel->stop();
    pChannel->stop();
    // Ensure the sound path is correctly formatted
    result = pSystem->createSound(Background_Sound, FMOD_DEFAULT, nullptr, &pSound);

    if (result != FMOD_OK) {
        std::cout << "Error creating sound" << std::endl;
        return;
    }

    result = pSystem->playSound(pSound, nullptr, false, &backgroundChannel);

    if (result != FMOD_OK) {
        std::cout << "Error playing sound" << std::endl;
    }
    else {
        std::cout << "Sound played successfully" << std::endl;
    }
}


void SoundPlayer_playSoundEffect(const char* soundPath) {
	FMOD::Sound* pSound = nullptr;


	// Ensure the sound path is correctly formatted
	result = pSystem->createSound(soundPath, FMOD_DEFAULT, nullptr, &pSound);

	if (result != FMOD_OK) {
		std::cout << "Error creating sound" << std::endl;
		return;
	}

	result = pSystem->playSound(pSound, nullptr, false, &pChannel);

	if (result != FMOD_OK) {
		std::cout << "Error playing sound" << std::endl;
	}
	else {
		std::cout << "Sound played successfully" << std::endl;
	}

}

void SoundPlayer_playObstacleSound() {
	SoundPlayer_playSoundEffect(Obstacle_Sound);
}


void SoundPlayer_playCollectibleSound() {
	SoundPlayer_playSoundEffect(Collectible_Sound);
}


void SoundPlayer_playPowerupSound() {
    SoundPlayer_playSoundEffect(Powerup_Sound);
}

void SoundPlayer_PostGameSound(bool isGameOver) {
    backgroundChannel->stop();
    if (isGameOver) {
        
		SoundPlayer_playSoundEffect(GameOver_Sound);
	}
    else {
		SoundPlayer_playSoundEffect(GameEnd_Sound);
	}
}