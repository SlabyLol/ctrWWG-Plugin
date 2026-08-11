#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void    Coins99999(MenuEntry *entry);
    void    CoinsSetOnce(MenuEntry *entry);
    void    InfiniteLives(MenuEntry *entry);
    void    RefillLives(MenuEntry *entry);
    void    KardPoints99(MenuEntry *entry);
    void    ForceWin(MenuEntry *entry);
    void    DefeatBoss(MenuEntry *entry);
    void    UnlockInfo(MenuEntry *entry);
}
#endif
