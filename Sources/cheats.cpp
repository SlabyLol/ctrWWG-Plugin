#include "cheats.hpp"

namespace CTRPluginFramework
{
    // Confirmed by user Search:
    // Coins  @ 0x0091E39C
    // Lives  @ 0x086ACF38  (heap – may change after reboot)

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
                "Lives: 0x086ACF38 (heap)\n\n"
                "Heap addresses can change after\n"
                "reboot. If Lives stops working,\n"
                "Search again and send new address.")();
        }
    }
}
