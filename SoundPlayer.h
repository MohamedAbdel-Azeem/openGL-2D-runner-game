#pragma once

#define Obstacle_Sound R"(C:\Users\moham\Downloads\Minecraft Uh Hit Sound Effect [TubeRipper.com].mp3)"
#define Collectible_Sound R"(C:\Users\moham\Downloads\Retro Game Coin Sound Effect [TubeRipper.com].mp3)"
#define Powerup_Sound R"(C:\Users\moham\Downloads\Woo Hoo Sound Effect [TubeRipper.com].mp3)"
#define GameOver_Sound R"(C:\Users\moham\Downloads\Brawl Stars OST - Lose [TubeRipper.com].mp3)"
#define GameEnd_Sound R"(C:\Users\moham\Downloads\One Piece OST The Very Very Very Strongest EPIC VERSION [TubeRipper.com].mp3)"
#define Background_Sound R"(C:\Users\moham\Downloads\The Amazing World of Gumball Im On My Way Cartoon Network [TubeRipper.com].mp3)"


void Soundplayer_init();
void Soundplayer_playBackgroundMusic();
void SoundPlayer_playObstacleSound();
void SoundPlayer_playCollectibleSound();
void SoundPlayer_playPowerupSound();

void SoundPlayer_PostGameSound(bool isGameOver);