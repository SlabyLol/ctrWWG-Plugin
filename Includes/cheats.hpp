#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    // Basic
    void    Coins99999(MenuEntry *entry);
    void    InfiniteLives(MenuEntry *entry);
    void    RefillLives(MenuEntry *entry);
    void    KardPoints99(MenuEntry *entry);

    // Gameplay
    void    ForceWin(MenuEntry *entry);
    void    DefeatBoss(MenuEntry *entry);

    // Unlock helpers (notes + partial)
    void    UnlockInfo(MenuEntry *entry);
}
#endif
