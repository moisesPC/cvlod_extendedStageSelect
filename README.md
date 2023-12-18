# Castlevania: Legacy of Darkness - Extended Stage Select Mod

This repository contains source code for an extended stage select mod for Castlevania: Legacy of Darkness.

This mod replaces that with a newly-created stage selection with the ability to select all maps, plus some other options.

Press L + R + Z at any time during gameplay to go to the stage select.

Controls:
* DPad Up and Down: Select maps
* A: Warp to map
* L: Change character
* R: Change alt costume
* DPad Left and Right: Select cutscenes
* CRight and Left: Select spawns

([A version of this mod for Castlevania 64 is available here](https://github.com/moisesPC/cv64_extendedStageSelect))

## Building (Ubuntu)
### Prerequisites
* [IDO 7.1](https://github.com/decompals/ido-static-recomp/releases) (place `cc` and all the other files in `tools/ido71`)
* [nOVL](https://github.com/Bsquo/nOVL/releases) (place `novl` in `tools/nOVL`)
* `mips64-ld`

### Build
* Place a Castlevania: Legacy of Darkness (USA) ROM (`sha1: 879EAD98F197FD05EDDA867655DA5B1CE25AA5B8`) in the root of the project and rename it to `cvlod.z64`. Then, run `make`. Said ROM will then be patched with the mod.

* Once the ROM is patched, recalculate its CRC by using a tool such as [rn64crc](https://www.smwcentral.net/?p=section&a=details&id=8799): `rn64crc -u cvlod.z64`

## Credits:
* ZZT32, ariahiro64, z64me, sauraen: For [nOVL](https://github.com/z64tools/nOVL), which this repository uses to convert textures from PNG to raw data.
* CrookedPoe, z64me: For [z64ovl](https://github.com/CrookedPoe/z64ovl). Although intended for the Zelda 64 games, they provide examples for rebuilding overlays.
* [OoT Decomp](https://github.com/zeldaret/oot): For the Ultra 64 headers.

## More information:
* [Castlevania: Legacy of Darkness - Research Spreadsheets](https://docs.google.com/spreadsheets/d/1lOO1ppSLE1xEmJF2g5O_c2bdmHmL9Y0541WuwihK9q0/edit#gid=733572789)
* [CV64&LoD Speedruns Discord.](https://discord.gg/eKht382) Discord server for the CV64 / LoD community. Go to the #tech-talk channel for reverse engineering discussion.