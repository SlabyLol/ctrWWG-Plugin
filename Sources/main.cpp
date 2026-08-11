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

        *cheats += new MenuEntry("Coins FREEZE 99999", Coins99999,
            "Address 0x0091E39C (confirmed)");
        *cheats += new MenuEntry("Coins set once 99999", nullptr, CoinsSetOnce);

        *cheats += new MenuEntry("Infinite Lives FREEZE", InfiniteLives,
            "Address 0x086ACF38 – freeze at 9");
        *cheats += new MenuEntry("Refill Lives (9)", nullptr, RefillLives);

        menu += cheats;

        MenuFolder *level = new MenuFolder("Level");

        *level += new MenuEntry("Set Level (keyboard)", nullptr, LevelSet,
            "Enter level number, writes to 0x086C4F80");
        *level += new MenuEntry("Level FREEZE", LevelFreeze,
            "Keeps last set level every frame");
        *level += new MenuEntry("Level +1", nullptr, LevelPlus1,
            "Increase current level by 1");

        menu += level;

        MenuFolder *gameplay = new MenuFolder("Gameplay");
        *gameplay += new MenuEntry("Force Win (how-to)", nullptr, ForceWin);
        *gameplay += new MenuEntry("Defeat Boss (how-to)", nullptr, DefeatBoss);
        *gameplay += new MenuEntry("99 Wario Kard Points", nullptr, KardPoints99);
        menu += gameplay;

        MenuFolder *unlock = new MenuFolder("Unlock");
        *unlock += new MenuEntry("Info", nullptr, UnlockInfo);
        menu += unlock;
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("ctrWWG-Plugin", 1, 2, 4,
            "Coins / Lives / Level editor");

        menu->SynchronizeWithFrame(true);
        InitMenu(*menu);
        menu->Run();
        delete menu;
        return (0);
    }
}
