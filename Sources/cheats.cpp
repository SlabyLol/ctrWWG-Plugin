#include "cheats.hpp"

namespace CTRPluginFramework
{
    // 99999 Coins - common address from community codes
    void    Coins99999(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            Process::Write32(0x0091E39C, 0x0001869F);
            OSD::Notify("Coins set to 99999", Color::Lime);
        }
    }

    // Infinite Lives toggle (Story Mode style)
    void    InfiniteLives(MenuEntry *entry)
    {
        static bool enabled = false;

        if (entry->WasJustActivated())
        {
            enabled = !enabled;
            if (enabled)
            {
                Process::Write32(0x2072A0A4, 0x00000000);
                OSD::Notify("Infinite Lives: ON", Color::Lime);
            }
            else
            {
                Process::Write32(0x2072A0A4, 0x00000001);
                OSD::Notify("Infinite Lives: OFF", Color::Orange);
            }
        }
    }

    // 99 Wario Kard Points
    void    KardPoints99(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            Process::Write32(0x00465440, 0xE3A00063); // MOV R0, #0x63
            OSD::Notify("Wario Kard Points set to 99", Color::Lime);
        }
    }
}
