#pragma once
#include "LevelState.h"

namespace Rogalique
{
    class Memento {
    private:
        friend class GameStatePlaying;
        LevelState state;
        Memento(const LevelState& levelState) : state(levelState) {}
        LevelState getState() const { return state; }
    public:
        static std::unique_ptr<Memento> Create(const LevelState& levelState) {
            return std::unique_ptr<Memento>(new Memento(levelState));
        }
    };
}