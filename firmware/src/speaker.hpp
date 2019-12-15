#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include "queue.hpp"

namespace gb7
{
    class speaker
    {
        enum class Tone
        {
            None, C, D, E, F, G, A, B, C
        };
        static constexpr int frequencties[] = {0, }; // TODO

        struct Note
        {
            Tone tone;
            int length;
        };

        static queue<Note> notes;
        Tone m_tone = Tone::None;

        static inline bool enqueue_note(Tone tone, int length)
        {
            return notes.push({ tone, length });
        }

        static inline void on_timer_interrupt()
        {
            
        }
    };
}

#endif // SPEAKER_HPP
