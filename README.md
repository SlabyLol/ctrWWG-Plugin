# ctrWWG-Plugin

**CTRPluginFramework 3GX Plugin for WarioWare Gold** (Nintendo 3DS)

A modern Luma3DS plugin based on CTRPluginFramework for *WarioWare Gold*.  
Title ID: `00040000001D1C00` (EUR / commonly shared)

## Features

- Action Replay support (import codes from file or create your own)
- Memory Searcher + Hex Editor
- Built-in cheats menu:
  - 99999 Coins
  - Infinite Lives (toggle)
  - 99 Wario Kard Points
  - Quick note about unlocking everything (use AR codes or search)
- Clean English interface
- Automatic GitHub Actions builds

## Installation

1. Download the latest `ctrWWG.3gx` from the [Actions](https://github.com/SlabyLol/ctrWWG-Plugin/actions) tab (Artifacts) or Releases.
2. Place it here on your SD card:
   ```
   sd:/luma/plugins/00040000001D1C00/ctrWWG.3gx
   ```
3. Optional: put AR codes in
   ```
   sd:/luma/plugins/00040000001D1C00.txt
   ```
4. Enable the Plugin Loader in Rosalina menu (L + Down + Select).
5. Start the game → press **Select** to open the menu.

## Building locally

Requirements:
- devkitPro + libctrpf (ThePixellizerOSS)
- 3gxtool

```bash
make
```

Output: `ctrWWG.3gx`

## Known working AR codes (v1.0 / early versions)

```
[99999 Coins]
0091E39C 0001869F

[99 Wario Kard Points]
00465440 E3A00063

[Infinite Lives ON]
2072A0A4 00000000

[Infinite Lives OFF]
2072A0A4 00000001
```

**Note:** Addresses can differ between game versions / regions. Use the built-in Searcher if a code does not work.

## Credits

- CTRPluginFramework by Nanquitas / PabloMK7 / ThePixellizerOSS
- Original NTR cheats by dsrules (GBAtemp)
- Template based on PabloMK7's BlankTemplate

## License

Feel free to use, modify and share.
