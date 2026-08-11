#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    // Cheats
    void    Coins99999(MenuEntry *entry);
    void    InfiniteLives(MenuEntry *entry);
    void    KardPoints99(MenuEntry *entry);
}
#endif
