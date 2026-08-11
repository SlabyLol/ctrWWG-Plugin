#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>

#include <vector>
#include "cheats.hpp"

namespace CTRPluginFramework
{
    // This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
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

    // This function is called before main and before the game starts
    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    // This function is called when the process exits
    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    void    InitMenu(PluginMenu &menu)
    {
        MenuFolder *cheats = new MenuFolder("Cheats");

        *cheats += new MenuEntry("99999 Coins", nullptr, Coins99999,
            "Sets your coin count to 99999.\n"
            "Address may vary by version/region.");

        *cheats += new MenuEntry("Infinite Lives (Toggle)", nullptr, InfiniteLives,
            "Toggle infinite lives for Story Mode.\n"
            "Press again to turn OFF.");

        *cheats += new MenuEntry("99 Wario Kard Points", nullptr, KardPoints99,
            "Sets Wario Kard points to 99.");

        menu += cheats;

        // Info entry
        menu += new MenuEntry("About / Notes", nullptr, [](MenuEntry *entry)
        {
            MessageBox("ctrWWG-Plugin", 
                "WarioWare Gold 3GX Plugin\n"
                "by DarkFox / SlabyLol\n\n"
                "Title ID: 00040000001D1C00\n\n"
                "If a cheat does not work, use the\n"
                "built-in Memory Searcher or\n"
                "Action Replay to find the correct\n"
                "addresses for your version.\n\n"
                "Original NTR codes by dsrules.\n"
                "Framework by Nanquitas / PabloMK7.")();
        });
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("ctrWWG-Plugin", 1, 0, 0,
            "WarioWare Gold Plugin\n"
            "Coins | Lives | Kard Points\n"
            "+ full Action Replay & tools");

        // Synchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        // Init our menu entries & folders
        InitMenu(*menu);

        // Launch menu and mainloop
        menu->Run();

        delete menu;

        // Exit plugin
        return (0);
    }
}
