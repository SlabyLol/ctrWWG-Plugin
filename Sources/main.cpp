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

        // GameFunc (2nd arg) = runs every frame when activated
        *cheats += new MenuEntry("Coins FREEZE 99999", Coins99999,
            "Confirmed address 0x0091E39C\n"
            "Keeps coins at 99999 every frame.");

        *cheats += new MenuEntry("Coins set once 99999", nullptr, CoinsSetOnce,
            "Writes 99999 once to 0x0091E39C");

        *cheats += new MenuEntry("Infinite Lives", InfiniteLives,
            "Writes lives address every frame.\n"
            "Find real address with Search if needed.");

        *cheats += new MenuEntry("Refill Lives", nullptr, RefillLives);

        *cheats += new MenuEntry("99 Wario Kard Points", nullptr, KardPoints99);

        menu += cheats;

        MenuFolder *gameplay = new MenuFolder("Gameplay");
        *gameplay += new MenuEntry("Force Win (how-to)", nullptr, ForceWin);
        *gameplay += new MenuEntry("Defeat Boss (how-to)", nullptr, DefeatBoss);
        menu += gameplay;

        MenuFolder *unlock = new MenuFolder("Unlock");
        *unlock += new MenuEntry("Info", nullptr, UnlockInfo);
        menu += unlock;
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("ctrWWG-Plugin", 1, 2, 1,
            "WarioWare Gold\nCoins @ 0x0091E39C confirmed");

        menu->SynchronizeWithFrame(true);
        InitMenu(*menu);
        menu->Run();
        delete menu;
        return (0);
    }
}
