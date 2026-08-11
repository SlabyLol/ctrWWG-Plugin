#include "cheats.hpp"

namespace CTRPluginFramework
{
    /*
     * IMPORTANT:
     * The public AR addresses from 2018 often do NOT work on all
     * game revisions / regions. If a cheat does nothing:
     * 1. Open the plugin menu -> Tools -> Search
     * 2. Search for your current coin count (or lives)
     * 3. Change the value in-game, search again ("changed")
     * 4. When you have 1-2 results, write the new value there
     * 5. Note the address and update these functions or use Action Replay
     */

    // -------------------------------------------------------
    // 99999 Coins – one-shot write
    // Default address from community codes (may be wrong for your version)
    // -------------------------------------------------------
    void    Coins99999(MenuEntry *entry)
    {
        static const u32 candidates[] = {
            0x0091E39C,  // common community address
            0x091E39C,
            0x001E39C
        };

        if (entry->WasJustActivated())
        {
            bool wrote = false;
            for (u32 addr : candidates)
            {
                if (Process::Write32(addr, 99999))
                {
                    OSD::Notify(Utils::Format("Coins -> 99999 @ %08X", addr), Color::Lime);
                    wrote = true;
                    break;
                }
            }
            if (!wrote)
                OSD::Notify("Coins write failed – use Memory Searcher", Color::Red);
        }
    }

    // -------------------------------------------------------
    // Infinite Lives – runs every frame while enabled
    // -------------------------------------------------------
    void    InfiniteLives(MenuEntry *entry)
    {
        // Known community address (often version-specific)
        static const u32 lifeAddr = 0x2072A0A4;

        if (entry->IsActivated())
        {
            // Try keep lives high every frame
            Process::Write32(lifeAddr, 0);
            // Also try writing a high life count to common patterns
            // (user should replace with found address)
        }

        if (entry->WasJustActivated())
            OSD::Notify("Infinite Lives ON (if address correct)", Color::Lime);
        if (entry->WasJustDeactivated())
            OSD::Notify("Infinite Lives OFF", Color::Orange);
    }

    // -------------------------------------------------------
    // Refill Lives – one shot
    // -------------------------------------------------------
    void    RefillLives(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            // Same limitation: address must match your game version
            if (Process::Write32(0x2072A0A4, 0))
                OSD::Notify("Lives write sent – check in-game", Color::Lime);
            else
                OSD::Notify("Write failed – find address with Searcher", Color::Red);
        }
    }

    // -------------------------------------------------------
    // 99 Wario Kard Points
    // Original code was an instruction patch (MOV R0, #99)
    // Data write may not work; try both styles
    // -------------------------------------------------------
    void    KardPoints99(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            // Try data value 99
            Process::Write32(0x00465440, 99);
            // Original AR was instruction: E3A00063 = MOV R0, #0x63
            Process::Write32(0x00465440, 0xE3A00063);
            OSD::Notify("Kard Points write sent", Color::Lime);
            OSD::Notify("If no effect: Search for current points", Color::White);
        }
    }

    // -------------------------------------------------------
    // Force Win – needs real win-flag address (game specific)
    // -------------------------------------------------------
    void    ForceWin(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            OSD::Notify("Force Win: no stable public address", Color::Orange);
            OSD::Notify("Use Searcher during a microgame", Color::White);
            OSD::Notify("Search 0 then win -> search changed", Color::White);
        }
    }

    // -------------------------------------------------------
    // Defeat Boss – same limitation
    // -------------------------------------------------------
    void    DefeatBoss(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            OSD::Notify("Defeat Boss: needs your game addresses", Color::Orange);
            OSD::Notify("Find win flag with Memory Searcher", Color::White);
        }
    }

    // -------------------------------------------------------
    // Unlock info
    // -------------------------------------------------------
    void    UnlockInfo(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            MessageBox("Why cheats may not work", 
                "Public AR codes from 2018 are often\n"
                "invalid on other revisions/regions.\n\n"
                "How to get WORKING cheats:\n\n"
                "1. Open plugin -> Tools -> Search\n"
                "2. Type your current Coins value\n"
                "3. Search -> Unknown / Exact\n"
                "4. Spend/earn coins in game\n"
                "5. Search again (Increased/Decreased)\n"
                "6. When 1 address left: edit it to 99999\n"
                "7. Save as Action Replay code\n\n"
                "Same method for Lives and Kard Points.\n\n"
                "Full Unlock All only existed in the\n"
                "old NTR .plg by dsrules (2018).")();
        }
    }
}
