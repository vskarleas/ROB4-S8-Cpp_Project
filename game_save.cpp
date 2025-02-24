// #############################################################################
// # File game_save.cpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <SDL.h>

#include "game_save.hpp"

/* SAVE_FILENAME and KEY are acceesible only in this specific source file
    where the namespace is included for security purposes*/
namespace
{
    const unsigned char KEY = 0x83;
    const char *SAVE_FILENAME = "game_pong-save_849374.txt"; // we always save the gam'es state on this prticular file
    const char *HIGHSCCORE_FILENAME = "game_pong-highscore_849216.txt";

    /* Encrypting a byte (unsigned 8 bits) - Inspired from https://www.101computing.net/xor-encryption-algorithm/
       It allows fusing the same operation to retrieve the encrypted data */
    unsigned char codec_byte(unsigned char byte)
    {
        return byte ^ KEY; // XOR operation
    }

    void codec_float(float &value)
    {
        unsigned char *bytes = reinterpret_cast<unsigned char *>(&value); // casting to return a float value to byte representation (interprentation)
        for (size_t i = 0; i < sizeof(float); ++i)
        {
            bytes[i] = codec_byte(bytes[i]);
        }
    }

    void codec_int(int &value) // same approche as seen for float values above
    {
        unsigned char *bytes = reinterpret_cast<unsigned char *>(&value);
        for (size_t i = 0; i < sizeof(int); ++i)
        {
            bytes[i] = codec_byte(bytes[i]);
        }
    }

    void codec_string(char* str, size_t length) {
        for (size_t i = 0; i < length; ++i) {
            str[i] = codec_byte(str[i]);
        }
    }
}

/* Deleting the save file */
void Saving::delete_save()
{
    std::remove(SAVE_FILENAME);
}

void Saving::delete_highscore()
{
    std::remove(HIGHSCCORE_FILENAME);
}

bool Saving::save_highscore(const HighScore &score)
{
    std::ofstream file(HIGHSCCORE_FILENAME, std::ios::binary | std::ios::app); // open the file in binary mode and append mode

    if (!file)
    {
        return false;
    }

    // Create a copy of the score to encode
    HighScore encode_score = score;

    // Encrypting the ints and floats of the HighScore structure
    codec_int(encode_score.score);
    codec_string(encode_score.name, 20);

    // Creating the file
    file.write(reinterpret_cast<const char *>(&encode_score), sizeof(HighScore));

    return file.good();
}

/* Creates or rewrites a save file with encrypted informations using the XOR algorithm */
bool Saving::save_game(const SaveState &state)
{
    std::ofstream file(SAVE_FILENAME, std::ios::binary);

    if (!file)
    {
        return false;
    }

    // Create a copy of the state to encode. The state can be
    SaveState encode_state = state;

    // Encrypting the ints and floats of the SaveState structure
    codec_int(encode_state.score1);
    codec_int(encode_state.score2);
    codec_float(encode_state.paddle1_y);
    codec_float(encode_state.paddle2_y);
    codec_float(encode_state.ball_x);
    codec_float(encode_state.ball_y);
    codec_float(encode_state.ball_vel_x);
    codec_float(encode_state.ball_vel_y);
    codec_int(encode_state.ball_type);
    codec_string(encode_state.player1_name, 20);
    codec_string(encode_state.player2_name, 20);

    // Creating the file
    file.write(reinterpret_cast<const char *>(&encode_state), sizeof(SaveState));

    return file.good(); // returns true if write operation was successful
}

bool Saving::load_game(SaveState &state)
{
    std::ifstream file(SAVE_FILENAME, std::ios::binary); // opening the file in binary mode

    // TEST 1 (file existence)
    if (!file) // if the file does not exist returns false
    {
        return false;
    }
    else
    {
        // Read encrypted content
        SaveState encode_state;
        file.read(reinterpret_cast<char *>(&encode_state), sizeof(SaveState));

        // TEST 2 (file reading rights)
        if (!file.good())
        {
            return false; // if the file is not readable returns false
        }

        // Decode all values
        codec_int(encode_state.score1);
        codec_int(encode_state.score2);
        codec_float(encode_state.paddle1_y);
        codec_float(encode_state.paddle2_y);
        codec_float(encode_state.ball_x);
        codec_float(encode_state.ball_y);
        codec_float(encode_state.ball_vel_x);
        codec_float(encode_state.ball_vel_y);
        codec_int(encode_state.ball_type);
        codec_string(encode_state.player1_name, 20);
        codec_string(encode_state.player2_name, 20);

        
        state = encode_state; // Copy decoded state back

        return true;
    }
}

bool Saving::load_highscore(HighScore &score)
{
    std::ifstream file(HIGHSCCORE_FILENAME, std::ios::binary);

    if (!file)
    {
        return false;
    }

    // Read the latest high score (at the end of file)
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    if (fileSize < sizeof(HighScore))
    {
        return false;
    }
    // Move to the last record
    file.seekg(-static_cast<int>(sizeof(HighScore)), std::ios::end);

    HighScore encode_score;
    file.read(reinterpret_cast<char *>(&encode_score), sizeof(HighScore));

    if (!file.good())
    {
        return false;
    }

    codec_int(encode_score.score);
    codec_string(encode_score.name, 20);

    score = encode_score;
    
    SDL_Log("Loaded high score - Name: %s, Score: %d", score.name, score.score);
    return true;
}

/* Check if a save file exists or not (the idea is that it has been generated previously) */
bool Saving::save_exists()
{
    std::ifstream file(SAVE_FILENAME);
    return file.good();
}

bool Saving::highscore_exists()
{
    std::ifstream file(HIGHSCCORE_FILENAME);
    return file.good();
}