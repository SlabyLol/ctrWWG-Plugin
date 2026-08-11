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

        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if (R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
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
        MenuFolder *cheats = new MenuFolder("Cheats");

        // Hotkey optional – user can set in menu
        *cheats += new MenuEntry("99999 Coins", nullptr, Coins99999,
            "Writes 99999 to known coin addresses.\n"
            "If nothing changes: use Tools -> Search\n"
            "to find YOUR coin address.");

        // Infinite lives = toggle entry (IsActivated runs every frame)
        *cheats += new MenuEntry("Infinite Lives", InfiniteLives, "",
            "Keeps writing the lives address every frame.\n"
            "Only works if the address matches your version.\n"
            "Find the correct address with Searcher.");

        *cheats += new MenuEntry("Refill Lives", nullptr, RefillLives,
            "One-shot lives write.");

        *cheats += new MenuEntry("99 Wario Kard Points", nullptr, KardPoints99,
            "Attempts Kard points write / patch.\n"
            "Often needs a version-specific address.");

        menu += cheats;

        MenuFolder *gameplay = new MenuFolder("Gameplay");

        *gameplay += new MenuEntry("Force Win (how-to)", nullptr, ForceWin,
            "No stable public address.\n"
            "Use Memory Searcher during a microgame.");

        *gameplay += new MenuEntry("Defeat Boss (how-to)", nullptr, DefeatBoss,
            "No stable public address.\n"
            "Use Memory Searcher during a boss.");

        menu += gameplay;

        MenuFolder *unlock = new MenuFolder("Unlock");

        *unlock += new MenuEntry("Why cheats fail / How to fix", nullptr, UnlockInfo,
            "Explains version mismatch and how to\n"
            "find working addresses yourself.");

        menu += unlock;

        menu += new MenuEntry("About", nullptr, [](MenuEntry *entry)
        {
            MessageBox("ctrWWG-Plugin", 
                "WarioWare Gold 3GX Plugin\n\n"
                "Built-in addresses are from 2018\n"
                "community codes and often do NOT\n"
                "work on every game revision.\n\n"
                "Use Tools -> Search to find\n"
                "Coins / Lives on YOUR dump,\n"
                "then save them as AR codes.\n\n"
                "Title ID: 00040000001D1C00")();
        });
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("ctrWWG-Plugin", 1, 2, 0,
            "WarioWare Gold\n"
            "Find addresses with Search if cheats fail");

        menu->SynchronizeWithFrame(true);
        InitMenu(*menu);
        menu->Run();
        delete menu;
        return (0);
    }
}
