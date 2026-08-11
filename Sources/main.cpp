#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>

#include <vector>
#include "cheats.hpp"

namespace CTRPluginFramework
{
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    void    InitMenu(PluginMenu &menu)
    {
        // === Cheats folder ===
        MenuFolder *cheats = new MenuFolder("Cheats");

        *cheats += new MenuEntry("99999 Coins", nullptr, Coins99999,
            "Sets coin count to 99999.");

        *cheats += new MenuEntry("Infinite Lives (Toggle)", nullptr, InfiniteLives,
            "Toggle infinite lives.\nPress again to turn OFF.");

        *cheats += new MenuEntry("Refill Lives", nullptr, RefillLives,
            "Refill / protect lives (Story Mode).\n"
            "Best used together with Infinite Lives.");

        *cheats += new MenuEntry("99 Wario Kard Points", nullptr, KardPoints99,
            "Sets Wario Kard points to 99.");

        menu += cheats;

        // === Gameplay folder ===
        MenuFolder *gameplay = new MenuFolder("Gameplay");

        *gameplay += new MenuEntry("Force Win (Microgame)", nullptr, ForceWin,
            "Attempt to force-clear the current\n"
            "microgame. Use during play.\n"
            "If nothing happens, search for the\n"
            "win flag with the Memory Searcher.");

        *gameplay += new MenuEntry("Defeat Boss", nullptr, DefeatBoss,
            "Best-effort boss clear.\n"
            "Activate while a Boss Microgame\n"
            "is running. Combine with Force Win.\n"
            "Exact address is version-dependent.");

        menu += gameplay;

        // === Unlock folder ===
        MenuFolder *unlock = new MenuFolder("Unlock");

        *unlock += new MenuEntry("Unlock All – Info", nullptr, UnlockInfo,
            "Explains how to unlock everything\n"
            "(minigames, characters, challenges,\n"
            "Arcade, Missions, cards…).\n"
            "Full codes were in the old NTR plugin.");

        menu += unlock;

        // About
        menu += new MenuEntry("About", nullptr, [](MenuEntry *entry)
        {
            MessageBox("ctrWWG-Plugin v1.1", 
                "WarioWare Gold 3GX Plugin\n"
                "by DarkFox / SlabyLol\n\n"
                "Title ID: 00040000001D1C00\n\n"
                "Working:\n"
                "• 99999 Coins\n"
                "• Infinite / Refill Lives\n"
                "• 99 Kard Points\n\n"
                "Force Win / Defeat Boss =\n"
                "best-effort (use Searcher if needed)\n\n"
                "Full Unlock All = use old NTR plugin\n"
                "or Memory Searcher + AR.\n\n"
                "Credits: Nanquitas, PabloMK7,\n"
                "dsrules (original NTR cheats)")();
        });
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("ctrWWG-Plugin", 1, 1, 0,
            "WarioWare Gold Plugin\n"
            "Coins • Lives • Kard • Force Win\n"
            "+ Action Replay & tools");

        menu->SynchronizeWithFrame(true);
        InitMenu(*menu);
        menu->Run();
        delete menu;
        return (0);
    }
}
