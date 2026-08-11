# ctrWWG-Plugin

**CTRPluginFramework 3GX Plugin for WarioWare Gold** (Nintendo 3DS)

Title ID: `00040000001D1C00`

## Features

### Working Cheats
- **99999 Coins**
- **Infinite Lives** (toggle)
- **Refill Lives**
- **99 Wario Kard Points**

### Gameplay
- **Force Win** – attempt to auto-clear the current microgame
- **Defeat Boss** – best-effort boss clear (activate during boss)

### Unlock
- Info entry explaining how to get full unlocks (all minigames, characters, challenges, Arcade, Missions, cards…)

The complete “Unlock Everything” codes only existed in the old 2018 NTR `.plg` by dsrules and were never published as simple AR addresses. Use the built-in **Memory Searcher** or the original NTR plugin if you need 100 % unlock.

## Installation

1. Download `ctrWWG.3gx` from [Actions → Artifacts](https://github.com/SlabyLol/ctrWWG-Plugin/actions)
2. Put it here:
   ```
   sd:/luma/plugins/00040000001D1C00/ctrWWG.3gx
   ```
3. Optional AR file:
   ```
   sd:/luma/plugins/00040000001D1C00.txt
   ```
4. Rosalina → Plugin Loader → Enable
5. Start game → press **Select**

## Building

```bash
make
```

Requires devkitPro + libctrpf + 3gxtool.

## Credits

- CTRPluginFramework – Nanquitas / PabloMK7 / ThePixellizerOSS
- Original NTR cheats – dsrules (GBAtemp)
- Template – PabloMK7 BlankTemplate

## Notes

Addresses can differ between game versions/regions.  
If a cheat does nothing, open the **Memory Searcher** inside the plugin and find the correct value yourself.
