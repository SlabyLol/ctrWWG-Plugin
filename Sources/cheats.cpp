#include "cheats.hpp"

namespace CTRPluginFramework
{
    // Confirmed by user search: Coins @ 0x0091E39C
    // (matches 2018 community AR code)

    void    Coins99999(MenuEntry *entry)
    {
        // Freeze coins every frame while enabled
        if (entry->IsActivated())
        {
            Process::Write32(0x0091E39C, 99999);
        }

        if (entry->WasJustActivated())
            OSD::Notify("Coins FREEZE 99999 ON", Color::Lime);
        if (entry->WasJustDeactivated())
            OSD::Notify("Coins FREEZE OFF", Color::Orange);
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
        static const u32 lifeAddr = 0x2072A0A4;

        if (entry->IsActivated())
            Process::Write32(lifeAddr, 0);

        if (entry->WasJustActivated())
            OSD::Notify("Infinite Lives ON (try Search if no effect)", Color::Lime);
        if (entry->WasJustDeactivated())
            OSD::Notify("Infinite Lives OFF", Color::Orange);
    }

    void    RefillLives(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            Process::Write32(0x2072A0A4, 0);
            OSD::Notify("Lives write sent – verify with Searcher", Color::Lime);
        }
    }

    void    KardPoints99(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            Process::Write32(0x00465440, 0xE3A00063);
            OSD::Notify("Kard patch sent – use Searcher if needed", Color::Lime);
        }
    }

    void    ForceWin(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            OSD::Notify("Use Searcher during microgame", Color::Orange);
        }
    }

    void    DefeatBoss(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            OSD::Notify("Use Searcher during boss", Color::Orange);
        }
    }

    void    UnlockInfo(MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            MessageBox("Coins address confirmed", 
                "Coins: 0x0091E39C (your search)\n\n"
                "Enable 'Coins FREEZE 99999' to\n"
                "keep coins locked every frame.\n\n"
                "For Lives: same Search method.\n"
                "Unlock All = old NTR plugin only.")();
        }
    }
}
