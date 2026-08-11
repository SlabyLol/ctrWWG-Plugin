#include "cheats.hpp"

namespace CTRPluginFramework
{
    // ONLY confirmed address from user Search:
    // Coins @ 0x0091E39C

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

    // Lives: NO write until user finds real address via Search
    void    InfiniteLives(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            OSD::Notify("Find Lives address with Search first!", Color::Orange);
    }

    void    RefillLives(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            OSD::Notify("Find Lives address with Search first!", Color::Orange);
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
            MessageBox("Safe mode", 
                "Only Coins (0x0091E39C) writes memory.\n\n"
                "Lives / Kard / Force Win / Boss\n"
                "are disabled until YOU find the\n"
                "addresses with Search.\n\n"
                "Wrong addresses = crash.")();
        }
    }
}
