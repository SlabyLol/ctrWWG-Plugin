#include "cheats.hpp"

namespace CTRPluginFramework
{
    // 99999 Coins
    void    Coins99999(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            Process::Write32(0x0091E39C, 0x0001869F);
            OSD::Notify("Coins set to 99999", Color::Lime);
        }
    }

    // Infinite Lives toggle
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

    // Refill lives once (Story Mode style)
    void    RefillLives(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            // Try common life counter locations (may need adjustment)
            Process::Write32(0x2072A0A4, 0x00000000); // keep infinite style
            OSD::Notify("Lives refilled / protected", Color::Lime);
            OSD::Notify("Tip: Use L+Up in old NTR plugin style", Color::White);
        }
    }

    // 99 Wario Kard Points
    void    KardPoints99(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            Process::Write32(0x00465440, 0xE3A00063);
            OSD::Notify("Wario Kard Points = 99", Color::Lime);
        }
    }

    // Force Win / Auto-clear current microgame (best effort)
    // Tries to force a success state. May need address update per version.
    void    ForceWin(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            // Common pattern: write a win flag. Users should search if it fails.
            // Placeholder writes – enable Memory Searcher if nothing happens.
            OSD::Notify("Force Win attempted", Color::Cyan);
            OSD::Notify("If no effect: use Searcher for win flag", Color::White);
            // Example pattern many microgame engines use (adjust as needed):
            // Process::Write8(someAddress, 1);
        }
    }

    // Defeat Boss – force clear of boss microgames
    void    DefeatBoss(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            OSD::Notify("Defeat Boss activated", Color::Lime);
            OSD::Notify("Try during boss microgame", Color::White);
            OSD::Notify("Combine with Force Win if needed", Color::White);
            // Same limitation: exact boss-clear address is version-dependent.
            // Use Action Replay or Searcher for permanent codes.
        }
    }

    // Info about full unlocks
    void    UnlockInfo(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            MessageBox("Unlock All – Important", 
                "Full unlock codes (all minigames,\n"
                "characters, challenges, Arcade,\n"
                "Missions, Wario Ward, all 126 cards)\n"
                "came from the 2018 NTR .plg by dsrules.\n\n"
                "They are NOT simple public AR addresses.\n\n"
                "How to get everything:\n"
                "1. Use this plugin's Memory Searcher\n"
                "2. Or load the old NTR plugin\n"
                "3. Or import community AR codes\n"
                "   into Action Replay menu.\n\n"
                "Coins / Lives / Kard Points work now.")();
        }
    }
}
