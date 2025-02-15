#include "game_save.hpp"
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace {
    const unsigned char KEY = 0x83;
    const char* SAVE_FILENAME = "game_pong-save_849374.txt";

    unsigned char CodecByte(unsigned char byte) {
        return byte ^ KEY;
    }

    void CodecFloat(float& value) {
        unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
        for (size_t i = 0; i < sizeof(float); ++i) {
            bytes[i] = CodecByte(bytes[i]);
        }
    }

    void CodecInt(int& value) {
        unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
        for (size_t i = 0; i < sizeof(int); ++i) {
            bytes[i] = CodecByte(bytes[i]);
        }
    }
}

void GameSave::DeleteSave() {
    std::remove(SAVE_FILENAME);
}

bool GameSave::SaveGame(const SaveState& state, const std::string& /*filename*/) {
    std::ofstream file(SAVE_FILENAME, std::ios::binary);
    
    if (!file) {
        return false;
    }

    // Create a copy of the state to encode
    SaveState encodedState = state;

    // Encode all values
    CodecInt(encodedState.score1);
    CodecInt(encodedState.score2);
    CodecFloat(encodedState.paddle1Y);
    CodecFloat(encodedState.paddle2Y);
    CodecFloat(encodedState.ballX);
    CodecFloat(encodedState.ballY);
    CodecFloat(encodedState.ballVelX);
    CodecFloat(encodedState.ballVelY);
    CodecInt(encodedState.ballType);

    // Write encoded state to file
    file.write(reinterpret_cast<const char*>(&encodedState), sizeof(SaveState));
    
    return file.good();
}

bool GameSave::LoadGame(SaveState& state, const std::string& /*filename*/) {
    std::ifstream file(SAVE_FILENAME, std::ios::binary);
    
    if (!file) {
        return false;
    }

    // Read encoded state from file
    SaveState encodedState;
    file.read(reinterpret_cast<char*>(&encodedState), sizeof(SaveState));
    
    if (!file.good()) {
        return false;
    }

    // Decode all values
    CodecInt(encodedState.score1);
    CodecInt(encodedState.score2);
    CodecFloat(encodedState.paddle1Y);
    CodecFloat(encodedState.paddle2Y);
    CodecFloat(encodedState.ballX);
    CodecFloat(encodedState.ballY);
    CodecFloat(encodedState.ballVelX);
    CodecFloat(encodedState.ballVelY);
    CodecInt(encodedState.ballType);

    // Copy decoded state back
    state = encodedState;
    
    return true;
}

bool GameSave::SaveExists() {
    std::ifstream file(SAVE_FILENAME);
    return file.good();
}