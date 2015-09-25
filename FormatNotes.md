Some notes on the Super Mario Maker '.cdt' level format, collected through
reverse-engineering of the version 1.01 game executable and careful
examination of level files. Thanks to RoadrunnerWMC for additional work
investigating files.

Not guaranteed to be correct, a lot of these field purposes are just
educated guesses.

Some u32 values may actually be signed; I haven't done any work to figure out
which ones are signed or not.

## File Layout
| Offset | Type | Description |
|--------|------|-------------|
| 00 | u64 | Assumed to be a version number. Always 0xB (11) right now |
| 08 | u32 | Checksum. Standard CRC32 of the entire file from offset 0x10 onwards. |
| 0C | *padding* | 4 unused bytes |
| 10 | u16 | Creation year |
| 12 | u8  | Creation month |
| 13 | u8  | Creation day |
| 14 | u8  | Creation hour |
| 15 | u8  | Creation minute |
| 16 | u8  | Unknown |
| 17 | u8  | Unknown |
| 18 | u64 | Unknown |
| 20 | u8  | Unknown |
| 21 | *padding* | 7 unused bytes |
| 28 | u16[0x21] | UCS-2 course name - 32 characters long plus zero terminator |
| 6A | char[2] | Game mode ('M1', 'M3', 'MW', 'WU') |
| 6C | u8 | Unknown |
| 6D | u8 | Course theme (0 = overworld, 1 = underground, 2 = castle, 3 = airship, 4 = water, 5 = ghost house) |
| 6E | u8 | Unknown |
| 6F | u8 | Unknown |
| 70 | u16 | Time limit |
| 72 | u8 | Autoscroll (0 = none, 1 = slow, 2 = medium, 3 = fast) |
| 73 | u8 | Unknown |
| 74 | u32 | Unknown |
| 78 | u8[0x60] | Unknown |
| D8 | u32 | Unknown |
| DC | u32 | Unknown |
| E0 | *padding* | 0xC unused bytes |
| EC | u32 | Object count |
| F0 | obj_t[2600] | Objects *(note that the full size is reserved even if the course has less than 2600 objects)* |
| 145F0 | effect_t[300] | Sound effects |
| 14F50 | *padding* | 0xB0 unused bytes |

## Object Structure
| Offset | Type | Description |
|--------|------|-------------|
| 00 | u32 | X position (* 10) |
| 04 | u32 | Z position (* 10) |
| 08 | s16 | Y position (* 10) |
| 0A | s8 | Width (in blocks) |
| 0B | s8 | Height (in blocks) |
| 0C | u32 | Object flags |
| 10 | u32 | Child object flags |
| 14 | u32 | Extended object data (used by Firebar and perhaps others) |
| 18 | s8 | Object type |
| 19 | s8 | Child object type |
| 1A | s16 | Link ID (assigned to pipes and rails) |
| 1C | s16 | Effect Index (-1 if none) |
| 1E | s8 | Unknown *(Always -1 in sample courses - could be object's transformation ID?)* |
| 1F | s8 | Child object's transformation ID (used by EditKinokoFunny) |

## Sound/Visual Effect Structure *(referenced by object field 1C)*
| Offset | Type | Description |
|--------|------|-------------|
| 00 | u8 | Unknown |
| 01 | u8 | Unknown |
| 02 | u8 | Unknown |
| 03 | u8 | Unknown |
| 04 | u8 | Unknown |
| 05 | *padding* | 3 unused bytes |

## Actor Names
| Internal ID | .cdt ID | Name | SubName | Description |
|-------------|---------|------|---------|-------------|
| 0 | *none* | TenCoin |  | |
| 1 | *none* | Lift |  | |
| 2 | *none* | Lift |  | |
| 3 | *none* | MapObjLiftRideOnPlayer |  | |
| 4 | *none* | FallLift |  | |
| 5 | *none* | YouganLift |  | |
| 6 | *none* | GoalPole |  | |
| 7 | *none* | Mario3Goal |  | |
| 8 | *none* | MariowGoal |  | |
| 9 | *none* | CastleGoal |  | |
| 10 | *none* | HardBlock |  | |
| 11 | *none* | IceBlock |  | |
| 12 | *none* | KumoBlock |  | |
| 13 | *none* | FireBar |  | |
| 14 | *none* | Burner |  | |
| 15 | *none* | HalfHitWall |  | |
| 16 | *none* | MapObjBlockHitActor |  | |
| 17 | *none* | ChikuwaBlock |  | |
| 18 | *none* | ChikeiFromBlock |  | |
| 19 | *none* | HatenaBlock |  | |
| 20 | *none* | RengaBlock |  | |
| 21 | *none* | ClearBlock |  | |
| 22 | *none* | MapObjBlockBreak |  | |
| 23 | *none* | OnpuBlock |  | |
| 24 | *none* | Ivy |  | |
| 25 | *none* | JumpStep |  | |
| 26 | *none* | JumpStepSide |  | |
| 27 | *none* | PSwitch |  | |
| 28 | *none* | PowBlock |  | |
| 29 | *none* | Coin |  | |
| 30 | *none* | Met | Met | |
| 31 | *none* | Met | MetBig | |
| 32 | *none* | Dossun | Dossun | |
| 33 | *none* | Dossun | DossunBig | |
| 34 | *none* | KillerHoudai | KillerHoudai | |
| 35 | *none* | SenkanHoudai | SenkanHoudai | |
| 36 | *none* | SenkanHoudai | SenkanHoudaiBig | |
| 37 | *none* | Togemet | Togemet | |
| 38 | *none* | Togemet | TogemetBig | |
| 39 | *none* | Togemet | TogemetYellow | |
| 40 | *none* | Togemet | TogemetYellowBig | |
| 41 | *none* | Poo | Poo | |
| 42 | *none* | Poo | PooBig | |
| 43 | *none* | BlackPakkun | BlackPakkun | |
| 44 | *none* | BlackPakkun | BlackPakkunBig | |
| 45 | *none* | WanwanPile | WanwanPile | |
| 46 | *none* | KoopaClown | KoopaClown | |
| 47 | *none* | Yoshi |  | |
| 48 | *none* | Player |  | |
| 49 | *none* | PlayerFire |  | |
| 50 | *none* | KutsuKuribo | KutsuKuribo | |
| 51 | *none* | KutsuKuribo | KutsuKuriboBig | |
| 52 | *none* | KutsuKuriboHeels | KutsuKuriboHeels | |
| 53 | *none* | KutsuKuriboHeels | KutsuKuriboHeelsBig | |
| 54 | *none* | Kuribo | Kuribo | |
| 55 | *none* | Kuribo | KuriboBig | |
| 56 | *none* | Kuribo | Kuribon | |
| 57 | *none* | Kuribo | KuribonBig | |
| 58 | *none* | Nokonoko | NokonokoGreen | |
| 59 | *none* | Nokonoko | NokonokoGreenBig | |
| 60 | *none* | NokonokoNaked | NokonokoWorldGreen | |
| 61 | *none* | NokonokoNaked | NokonokoWorldGreenBig | |
| 62 | *none* | NokonokoRed | NokonokoRed | |
| 63 | *none* | NokonokoRed | NokonokoRedBig | |
| 64 | *none* | NokonokoNakedRed | NokonokoWorldRed | |
| 65 | *none* | NokonokoNakedRed | NokonokoWorldRedBig | |
| 66 | *none* | Pakkun | Pakkun | |
| 67 | *none* | Pakkun | PakkunBig | |
| 68 | *none* | Pakkun | PPakkun | |
| 69 | *none* | Pakkun | PPakkunBig | |
| 70 | *none* | FirePakkun | FirePakkun | |
| 71 | *none* | FirePakkun | FirePakkunBig | |
| 72 | *none* | EnemyWaki |  | |
| 73 | *none* | Bros | Bros1st | |
| 74 | *none* | Bros | BrosU | |
| 75 | *none* | MegaBros | MegaBros | |
| 76 | *none* | Choropoo | Choropoo | |
| 77 | *none* | Choropoo | ChoropooBig | |
| 78 | *none* | Bombhei | Bombhei | |
| 79 | *none* | Bombhei | BombheiBig | |
| 80 | *none* | Togezo | Togezo | |
| 81 | *none* | Togezo | TogezoBig | |
| 82 | *none* | Jugem | Jugem | |
| 83 | *none* | Killer | Killer | |
| 84 | *none* | KillerSearch | KillerSearch | |
| 85 | *none* | Kameck | Kameck | |
| 86 | *none* | Kameck | KameckBig | |
| 87 | *none* | Teresa | Teresa | |
| 88 | *none* | Teresa | TeresaBig | |
| 89 | *none* | Teresa | TeresaSpread | |
| 90 | *none* | Teresa | TeresaSpreadBig | |
| 91 | *none* | Necchi | Necchi | |
| 92 | *none* | Karon | Karon | |
| 93 | *none* | Karon | KaronBig | |
| 94 | *none* | Gesso | Gesso | |
| 95 | *none* | Gesso | GessoBig | |
| 96 | *none* | Hanachan | Hanachan | |
| 97 | *none* | Hanachan | HanachanBig | |
| 98 | *none* | Pukupuku | Pukupuku | |
| 99 | *none* | Pukupuku | PukupukuBig | |
| 100 | *none* | PukupukuRed | PukupukuRed | |
| 101 | *none* | PukupukuRed | PukupukuRedBig | |
| 102 | *none* | Bubble | Bubble | |
| 103 | *none* | Bubble | BubbleBig | |
| 104 | *none* | Wanwan | Wanwan | |
| 105 | *none* | Wanwan | WanwanBig | |
| 106 | *none* | Koopa | KoopaM1 | |
| 107 | *none* | Koopa | KoopaM1Big | |
| 108 | *none* | Koopa | KoopaM3 | |
| 109 | *none* | Koopa | KoopaM3Big | |
| 110 | *none* | Koopa | KoopaMW | |
| 111 | *none* | Koopa | KoopaMWBig | |
| 112 | *none* | Koopa | KoopaWU | |
| 113 | *none* | Koopa | KoopaWUBig | |
| 114 | *none* | KoopaJr | KoopaJr | |
| 115 | *none* | KoopaJr | KoopaJrBig | |
| 116 | *none* | FishBone | FishBone | |
| 117 | *none* | FishBone | FishBoneBig | |
| 118 | *none* | Saw |  | |
| 119 | *none* | SuperKinoko |  | |
| 120 | *none* | FireFlower |  | |
| 121 | *none* | SuperStar |  | |
| 122 | *none* | 1upKinoko |  | |
| 123 | *none* | Leave |  | |
| 124 | *none* | Feather |  | |
| 125 | *none* | Propeller |  | |
| 126 | *none* | Shoes |  | |
| 127 | *none* | HatenaKinoko |  | |
| 128 | *none* | BigKinoko |  | |
| 129 | *none* | CharaMario |  | |
| 130 | *none* | Door |  | |
| 131 | *none* | YoshiEgg |  | |
| 132 | *none* | Hammer |  | |
| 133 | *none* | EnmyFire |  | |
| 134 | *none* | YoshiFire |  | |
| 135 | *none* | BulletYoshiBone |  | |
| 136 | *none* | BulletToge |  | |
| 137 | *none* | KameckMagic |  | |
| 138 | *none* | BulletBone |  | |
| 139 | *none* | BulletSenkanBall |  | |
| 140 | *none* | BulletSpanner |  | |
| 141 | *none* | BulletKoopaFire |  | |
| 142 | *none* | BulletKoopaFireFall |  | |
| 143 | *none* | ShoesAttack |  | |
| 144 | *none* | JugemCloud | JugemCloud | |
| 145 | *none* | EnemyTowerManager |  | |
| 146 | *none* | KoopaFireEmitter |  | |
| 147 | *none* | MapObjCoinDemoJump |  | |
| 148 | *none* | MapObjCoinHopJump |  | |
| 149 | *none* | MapObjCoinYoshiEat |  | |
| 150 | *none* | StartSignBoard |  | |
| 151 | *none* | CastleBridge |  | |
| 152 | *none* | AirSignBoard |  | |
| 153 | *none* | DemoPlayer |  | |
| 154 | *none* | DemoPeach |  | |
| 155 | 69 | EditPlayer |  | |
| 156 | 7 | EditGround | EditGround | Terrain |
| 157 | 9 | EditDokan | EditDokan | Pipe |
| 158 | 14 | EditGroundMushroom | EditGroundMushRoom | Terrain: Mushroom (looks are game specific) |
| 159 | 16 | EditGroundBox | EditGroundBox | Terrain: Box (looks are game specific) |
| 160 | 17 | EditBridge | EditBridge | |
| 161 | 53 | EditBeltConveyor | EditBeltConveyor | |
| 162 | 64 | EditTsuta | EditTsuta | Vine |
| 163 | 59 | EditRail | EditRail | |
| 164 | 31 | EditJugemCloud | EditJugemCloud | Lakitu's Cloud |
| 165 | 42 | EditKoopaClown | EditKoopaClown | |
| 166 | 0 | EditKuribo | EditKuribo | Goomba |
| 167 | 45 | EditKutsuKuribo | EditKutsuKuribo | Shoed Goomba (Yoshi Egg in SMW/NSMBU) |
| 168 | 1 | EditNokonoko | EditNokonoko | Koopa Troopa |
| 169 | 2 | EditPakkun | EditPakkun | Piranha Plant |
| 170 | 57 | EditBlackPakkun | EditBlackPakkun | Muncher |
| 171 | 3 | EditHammerBros | EditHammerBros | |
| 172 | 12 | EditDossun | EditDossun | Thwomp |
| 173 | 13 | EditKillerHoudai | EditKillerHoudai | Bullet Bill Cannon |
| 174 | 58 | EditPoo | EditPoo | Rocky Wrench |
| 175 | 15 | EditBombhei | EditBombhei | Bob-Omb |
| 176 | 25 | EditTogezo | EditTogezo | Spiny |
| 177 | 28 | EditMet | EditMet | Buzzy Beetle |
| 178 | 30 | EditJugem | EditJugem | Lakitu |
| 179 | 39 | EditKameck | EditKameck | Kamek |
| 180 | 40 | EditTogemet | EditTogemet | Spike Top |
| 181 | 41 | EditTeresa | EditTeresa | Boo |
| 182 | 46 | EditKaron | EditKaron | Dry Bones |
| 183 | 48 | EditGesso | EditGesso | Blooper |
| 184 | 47 | EditSenkanHoudai | EditSenkanHoudai | Cannon |
| 185 | 52 | EditHanachan | EditHanachan | Wiggler |
| 186 | 56 | EditPukupuku | EditPukupuku | Cheep |
| 187 | 60 | EditBubble | EditBubble | Podoboo |
| 188 | 61 | EditWanwan | EditWanwan | Chain Chomp |
| 189 | 62 | EditKoopa | EditKoopa | Bowser |
| 190 | *none* | EditKoopaJr | EditKoopaJr | |
| 191 | 4 | EditRengaBlock | EditRengaBlock | Brick Block |
| 192 | 5 | EditHatenaBlock | EditHatenaBlock | '?' Block |
| 193 | 43 | EditToge | EditToge | Spiny Thing |
| 194 | 6 | EditHardBlock | EditHardBlock | Wooden Block |
| 195 | 63 | EditIceBlock | EditIceBlock | |
| 196 | 26 | EditGroundGoal |  | |
| 197 | 37 | EditGroundStart |  | |
| 198 | 49 | EditCastleBridge | EditCastleBridge | |
| 199 | 55 | EditDoor | EditDoor | |
| 200 | 27 | EditGoalPole |  | |
| 201 | *none* | EditWing | EditWing | |
| 202 | 10 | EditJumpStep | EditJumpStep | Springboard |
| 203 | 11 | EditLift | EditLift | Moving Platform |
| 204 | 36 | EditYouganLift | EditYouganLift | |
| 205 | 18 | EditPSwitch | EditPSwitch | |
| 206 | 19 | EditPowBlock | EditPowBlock | |
| 207 | 20 | EditSuperKinoko | EditSuperKinoko | |
| 208 | 44 | EditKinokoFunny | EditKinokoFunny | |
| 209 | 33 | Edit1upKinoko | Edit1upKinoko | |
| 210 | 34 | EditFireFlower | EditFireFlower | |
| 211 | 35 | EditSuperStar | EditSuperStar | |
| 212 | 50 | EditCharaKinoko | EditCharaKinoko | |
| 213 | 51 | EditDekaKinoko | EditDekaKinoko | |
| 214 | 65 | EditCharaMario | EditCharaMario | |
| 215 | 21 | EditChikuwaBlock | EditChikuwaBlock | Donut Lift |
| 216 | 22 | EditKumoBlock | EditKumoBlock | Cloud Block |
| 217 | 23 | EditOnpuBlock | EditOnpuBlock | Note Block |
| 218 | 29 | EditClearBlock | EditClearBlock | |
| 219 | 32 | EditTsutaBlock | EditTsutaBlock | Vine Block? |
| 220 | 8 | EditCoin | EditCoin | |
| 221 | 24 | EditFireBar | EditFireBar | |
| 222 | 54 | EditBurner | EditBurner | Flamethrower |
| 223 | 38 | EditStartSignBoard |  | Sign at beginning of level |
| 224 | 66 | EditAirSignBoard | EditAirSignBoard | |
| 225 | 67 | EditHalfHitWall | EditHalfHitWall | One-way Gate |
| 226 | 68 | EditSaw | EditSaw | Grinder |
| 227 | *none* | FlyWorker |  | |
| 228 | *none* | FlyCourier |  | |
| 229 | *none* | FlyChild |  | |
| 230 | *none* | FlyBoss |  | |
| 231 | *none* | FlyBomb |  | |
| 232 | *none* | SampleActor |  | |
| 233 | *none* | EnemySample | Sample | |

## Transformation IDs

| ID | Name |
|----|------|
| 0 | Mario |
| 1 | Peach |
| 2 | Luigi |
| 3 | Koopa |
| 4 | Kuribo |
| 5 | Block |
| 6 | Kinopio |
| 7 | MarioSilver |
| 8 | MarioGold |
| 9 | Trampoline |
| 10 | Wario |
| 11 | SideStepper |
| 12 | MarioOriginal |
| 13 | Heiho |
| 14 | Rosalina |
| 15 | Yoshi |
| 16 | KoopaJr |
| 17 | DrMario |
| 18 | MarioKart |
| 19 | WoolYoshiAqua |
| 20 | WoolYoshiGreen |
| 21 | WoolYoshiPink |
| 22 | WoolYoshiBig |
| 23 | Kirby |
| 24 | Dedede |
| 25 | MetaKnight |
| 26 | Pit |
| 27 | Palutena |
| 28 | DarkPit |
| 29 | MegaMan |
| 30 | Samus |
| 31 | ZeroSams |
| 32 | Robot |
| 33 | Marth |
| 34 | Ike |
| 35 | Lucina |
| 36 | Robin |
| 37 | Pikachu |
| 38 | Lucario |
| 39 | Charizard |
| 40 | Greninja |
| 41 | Pudding |
| 42 | Mewtwo |
| 43 | Orima |
| 44 | Pikmin |
| 45 | Link |
| 46 | Zelda |
| 47 | Ganon |
| 48 | Sheik |
| 49 | Tincle |
| 50 | ThunLink |
| 51 | Shulk |
| 52 | Ness |
| 53 | Lucas |
| 54 | SplaIka |
| 55 | SplaBoy |
| 56 | SplaGirl |
| 57 | Fit |
| 58 | ChibiRobo |
| 59 | Murabito |
| 60 | Tanuki |
| 61 | Sizue |
| 62 | Kento |
| 63 | Kaizo |
| 64 | Lisa |
| 65 | Kinuyo |
| 66 | Totakeke |
| 67 | SizueWinter |
| 68 | Fuko |
| 69 | Futa |
| 70 | ResetSan |
| 71 | Shunk |
| 72 | TsubuMame |
| 73 | Kappei |
| 74 | MishiNeko |
| 75 | Takumi |
| 76 | Falcon |
| 77 | GameWatch |
| 78 | Sonic |
| 79 | DonkeyKong |
| 80 | DiddyKong |
| 81 | DuckHunt |
| 82 | PackMan |
| 83 | Blackey |
| 84 | Fox |
| 85 | LittleMac |
| 86 | Falco |
| 87 | Slippy |
| 88 | Peppy |
| 89 | Arwing |
| 90 | DiyMario |
| 91 | DonkeyKongJr |
| 92 | Shellcreeper |
| 93 | Waluigi |
| 94 | Wiibo |
| 95 | MahjongTile |
| 96 | MrHakari |
| 97 | Ashley |
| 98 | Nikki |

## Level Notes

Objects seem to default to: objFlags = 06000840, childFlags = 06000840, _14 = 00000000,
childType = -1, linkID = -1, _1C = -1, _1E = 255, _1F = 255

Object flag 2 seems to make an object winged.

Object flag 4 affects objects in the following ways (ref function at 0x20A2AF0 and others):

| Object | When Clear | When Set |
|--------|------------|----------|
| Koopa Troopa | Green | Red |
| Cheep Cheep | Green | Red |
| Piranha Plant | Normal | Fire |
| Rocky Wrench | 'Poo' | 'Choropoo' |
| Hammer Bros | Normal | Mega |
| Bowser | Normal | Jr |
| Shoed Goomba | Shoe | Heels |
| Boo | Single | Group |
| Spike Top | Normal | Yellow |
| Springboard | Normal | Sideways |
| Platform | Normal | Falling |
| Bullet Bill Cannon | Normal | Missile |

There's bound to be more, these are just the ones I've found out.

Object flag 0x100 turns Teresa (Boo) into a 'Necchi' (not sure what that is).

If `(((objFlags & 0x6000) >> 13) == 2)`, an object will be converted into its large version.


For blocks (EditHatenaBlock, EditRengaBlock, etc), childType defines the
.cdt ID of the object contained within that block, or -1 for the default coin.
e.g.: 64 = EditTsuta (vine), 15 = EditBombhei (bob-omb), 41 = EditTeresa (Boo).

For Firebars, extData seems to control the initial rotation of the bar (and possibly other things).

For EditKinokoFunny, field 1F specifies what form the mushroom will transform
you into - e.g.: 1 = Peach, 2 = Luigi, 3 = Koopa, 4 = Goomba, 5 = ? block, ...
(see 'Transformation IDs' section above)

In every sample level, this field exists on a block which contains an
EditKinokoFunny. I speculate that field 1E may do the same thing for the
outer/parent object, which means that it could work when applied to a
standalone '?' mushroom - but I cannot confirm this as none of the sample
levels contain these.

Pipes, Rails and Clown Cars have an incrementing 'Link ID' stored in field 1A.
Objects like Piranha Plants (EditPakkun) which can go inside a pipe will have
a matching Link ID with their paired pipe. The same occurs for objects which
can be attached to a rail, like the Chain Chomps in NWC-02.


