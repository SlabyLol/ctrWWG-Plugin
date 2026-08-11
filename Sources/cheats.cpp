#include "cheats.hpp"

namespace CTRPluginFramework
{
    // Confirmed by user Search:
    // Coins  @ 0x0091E39C
    // Lives  @ 0x086ACF38  (heap)
    // Level  @ 0x086C4F80  (heap)

    void    Coins99999(MenuEntry *entry)
    {
        if (entry->IsActivated())
            Process::Write32(0x0091E39C, 99999);

        if (entry->WasJustActivated())
            OSD::Notify("Coins FREEZE 99999 ON", Color::Lime);
    }

    void    CoinsSetOnce(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            if (Process::Write32(0x0091E39C, 99999))
                OSD::Notify("Coins set to 99999", Color::Lime);
            else
                OSD::Notify("Write failed", Color::Red);
        }
    }

    void    InfiniteLives(MenuEntry *entry)
    {
        if (entry->IsActivated())
            Process::Write32(0x086ACF38, 9);

        if (entry->WasJustActivated())
            OSD::Notify("Infinite Lives FREEZE ON (9)", Color::Lime);
    }

    void    RefillLives(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            if (Process::Write32(0x086ACF38, 9))
                OSD::Notify("Lives set to 9", Color::Lime);
            else
                OSD::Notify("Write failed – address may have moved", Color::Red);
        }
    }

    // Level editor – set specific level / freeze
    static u32 g_levelValue = 1;

    void    LevelSet(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            // Keyboard to enter level number
            Keyboard kb("Enter level number (decimal):");
            kb.IsHexadecimal(false);
            u32 val = g_levelValue;
            if (kb.Open(val) != -1)
            {
                g_levelValue = val;
                if (Process::Write32(0x086C4F80, val))
                    OSD::Notify(Utils::Format("Level set to %u", val), Color::Lime);
                else
                    OSD::Notify("Write failed – addr may have moved", Color::Red);
            }
        }
    }

    void    LevelFreeze(MenuEntry *entry)
    {
        if (entry->IsActivated())
            Process::Write32(0x086C4F80, g_levelValue);

        if (entry->WasJustActivated())
            OSD::Notify(Utils::Format("Level FREEZE %u ON", g_levelValue), Color::Lime);
    }

    void    LevelPlus1(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            u32 cur = 0;
            Process::Read32(0x086C4F80, cur);
            cur += 1;
            Process::Write32(0x086C4F80, cur);
            g_levelValue = cur;
            OSD::Notify(Utils::Format("Level -> %u", cur), Color::Lime);
        }
    }

    void    KardPoints99(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            OSD::Notify("Find Kard address with Search first!", Color::Orange);
    }

    void    ForceWin(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            OSD::Notify("Find win-flag with Search during microgame", Color::Orange);
    }

    void    DefeatBoss(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            OSD::Notify("Find win-flag with Search during boss", Color::Orange);
    }

    void    UnlockInfo(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            MessageBox("Addresses", 
                "Coins: 0x0091E39C (stable)\n"
                "Lives: 0x086ACF38 (heap)\n"
                "Level: 0x086C4F80 (heap)\n\n"
                "Heap addresses can change after\n"
                "reboot. Re-Search if broken.")();
        }
    }
}
