# ctrWWG-Plugin

CTRPluginFramework 3GX Plugin for **WarioWare Gold** (3DS)  
Title ID: `00040000001D1C00`

## Important: Cheats may not work out of the box

Public Action Replay addresses from 2018 are **version/region specific**.  
If Coins / Lives / Kard Points do nothing on your game, the addresses are wrong for your dump.

### How to make working cheats (Memory Searcher)

1. Start the game and open the plugin (**Select**)
2. Go to **Tools → Search**
3. Example for Coins:
   - Note your current coin count
   - Search exact value
   - Spend or earn coins in-game
   - Search again (Increased / Decreased / Changed)
   - Repeat until 1–2 addresses remain
   - Edit the value to `99999`
4. Save the address as an **Action Replay** code inside the plugin

Same method for Lives and Wario Kard Points.

### Built-in menu

- 99999 Coins (tries known addresses)
- Infinite Lives (toggle – only if address matches)
- Refill Lives
- 99 Wario Kard Points
- Force Win / Defeat Boss → guide only (no stable public address)
- Unlock All → only existed in the old 2018 NTR `.plg` by dsrules

### Installation

```
sd:/luma/plugins/00040000001D1C00/ctrWWG-Plugin.3gx
```

Enable Plugin Loader in Rosalina (L + Down + Select).

### Build / Release

Version is in `version.txt`. Every push to `master` builds and auto-releases.

```bash
make
```

### Credits

- CTRPluginFramework – Nanquitas / PabloMK7
- Original NTR cheats – dsrules (GBAtemp)
