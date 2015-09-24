Some notes on the Super Mario Maker '.cdt' level format, collected through
reverse-engineering of the version 1.01 game executable.

Not guaranteed to be correct, a lot of these field purposes are just
educated guesses.

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
| 6D | u8 | Unknown |
| 6E | u8 | Unknown |
| 6F | u8 | Unknown |
| 70 | u16 | Time limit |
| 72 | u8 | Unknown |
| 73 | u8 | Unknown |
| 74 | u32 | Unknown |
| 78 | u8[0x60] | Unknown |
| D8 | u32 | Unknown |
| DC | u32 | Unknown |
| E0 | *padding* | 0xC unused bytes |
| EC | u32 | Object count |
| F0 | obj_t[2600] | Objects *(note that the full size is reserved even if the course has less than 2600 objects)* |
| 145F0 | unk_t[300] | Unknown structures, documented below |
| 14F50 | *padding* | 0xB0 unused bytes |

## Object Structure
| Offset | Type | Description |
|--------|------|-------------|
| 00 | u32 | X position (* 10) |
| 04 | u32 | Z position (* 10) |
| 08 | u16 | Y position (* 10) |
| 0A | u8 | Width (in blocks) |
| 0B | u8 | Height (in blocks) |
| 0C | u32 | Unknown |
| 10 | u32 | Unknown |
| 14 | u32 | Unknown |
| 18 | u8 | Object type |
| 19 | u8 | Unknown |
| 1A | u16 | Unknown |
| 1C | u16 | Unknown |
| 1E | u8 | Unknown |
| 1F | u8 | Unknown |

## Unknown Structure
| Offset | Type | Description |
|--------|------|-------------|
| 00 | u8 | Unknown |
| 01 | u8 | Unknown |
| 02 | u8 | Unknown |
| 03 | u8 | Unknown |
| 04 | u8 | Unknown |
| 05 | *padding* | 3 unused bytes |

## Actor Names
| Internal ID | .cdt ID | Name | SubName |
|-------------|---------|------|---------|
| 0 | *none* | TenCoin |  |
| 1 | *none* | Lift |  |
| 2 | *none* | Lift |  |
| 3 | *none* | MapObjLiftRideOnPlayer |  |
| 4 | *none* | FallLift |  |
| 5 | *none* | YouganLift |  |
| 6 | *none* | GoalPole |  |
| 7 | *none* | Mario3Goal |  |
| 8 | *none* | MariowGoal |  |
| 9 | *none* | CastleGoal |  |
| 10 | *none* | HardBlock |  |
| 11 | *none* | IceBlock |  |
| 12 | *none* | KumoBlock |  |
| 13 | *none* | FireBar |  |
| 14 | *none* | Burner |  |
| 15 | *none* | HalfHitWall |  |
| 16 | *none* | MapObjBlockHitActor |  |
| 17 | *none* | ChikuwaBlock |  |
| 18 | *none* | ChikeiFromBlock |  |
| 19 | *none* | HatenaBlock |  |
| 20 | *none* | RengaBlock |  |
| 21 | *none* | ClearBlock |  |
| 22 | *none* | MapObjBlockBreak |  |
| 23 | *none* | OnpuBlock |  |
| 24 | *none* | Ivy |  |
| 25 | *none* | JumpStep |  |
| 26 | *none* | JumpStepSide |  |
| 27 | *none* | PSwitch |  |
| 28 | *none* | PowBlock |  |
| 29 | *none* | Coin |  |
| 30 | *none* | Met | Met |
| 31 | *none* | Met | MetBig |
| 32 | *none* | Dossun | Dossun |
| 33 | *none* | Dossun | DossunBig |
| 34 | *none* | KillerHoudai | KillerHoudai |
| 35 | *none* | SenkanHoudai | SenkanHoudai |
| 36 | *none* | SenkanHoudai | SenkanHoudaiBig |
| 37 | *none* | Togemet | Togemet |
| 38 | *none* | Togemet | TogemetBig |
| 39 | *none* | Togemet | TogemetYellow |
| 40 | *none* | Togemet | TogemetYellowBig |
| 41 | *none* | Poo | Poo |
| 42 | *none* | Poo | PooBig |
| 43 | *none* | BlackPakkun | BlackPakkun |
| 44 | *none* | BlackPakkun | BlackPakkunBig |
| 45 | *none* | WanwanPile | WanwanPile |
| 46 | *none* | KoopaClown | KoopaClown |
| 47 | *none* | Yoshi |  |
| 48 | *none* | Player |  |
| 49 | *none* | PlayerFire |  |
| 50 | *none* | KutsuKuribo | KutsuKuribo |
| 51 | *none* | KutsuKuribo | KutsuKuriboBig |
| 52 | *none* | KutsuKuriboHeels | KutsuKuriboHeels |
| 53 | *none* | KutsuKuriboHeels | KutsuKuriboHeelsBig |
| 54 | *none* | Kuribo | Kuribo |
| 55 | *none* | Kuribo | KuriboBig |
| 56 | *none* | Kuribo | Kuribon |
| 57 | *none* | Kuribo | KuribonBig |
| 58 | *none* | Nokonoko | NokonokoGreen |
| 59 | *none* | Nokonoko | NokonokoGreenBig |
| 60 | *none* | NokonokoNaked | NokonokoWorldGreen |
| 61 | *none* | NokonokoNaked | NokonokoWorldGreenBig |
| 62 | *none* | NokonokoRed | NokonokoRed |
| 63 | *none* | NokonokoRed | NokonokoRedBig |
| 64 | *none* | NokonokoNakedRed | NokonokoWorldRed |
| 65 | *none* | NokonokoNakedRed | NokonokoWorldRedBig |
| 66 | *none* | Pakkun | Pakkun |
| 67 | *none* | Pakkun | PakkunBig |
| 68 | *none* | Pakkun | PPakkun |
| 69 | *none* | Pakkun | PPakkunBig |
| 70 | *none* | FirePakkun | FirePakkun |
| 71 | *none* | FirePakkun | FirePakkunBig |
| 72 | *none* | EnemyWaki |  |
| 73 | *none* | Bros | Bros1st |
| 74 | *none* | Bros | BrosU |
| 75 | *none* | MegaBros | MegaBros |
| 76 | *none* | Choropoo | Choropoo |
| 77 | *none* | Choropoo | ChoropooBig |
| 78 | *none* | Bombhei | Bombhei |
| 79 | *none* | Bombhei | BombheiBig |
| 80 | *none* | Togezo | Togezo |
| 81 | *none* | Togezo | TogezoBig |
| 82 | *none* | Jugem | Jugem |
| 83 | *none* | Killer | Killer |
| 84 | *none* | KillerSearch | KillerSearch |
| 85 | *none* | Kameck | Kameck |
| 86 | *none* | Kameck | KameckBig |
| 87 | *none* | Teresa | Teresa |
| 88 | *none* | Teresa | TeresaBig |
| 89 | *none* | Teresa | TeresaSpread |
| 90 | *none* | Teresa | TeresaSpreadBig |
| 91 | *none* | Necchi | Necchi |
| 92 | *none* | Karon | Karon |
| 93 | *none* | Karon | KaronBig |
| 94 | *none* | Gesso | Gesso |
| 95 | *none* | Gesso | GessoBig |
| 96 | *none* | Hanachan | Hanachan |
| 97 | *none* | Hanachan | HanachanBig |
| 98 | *none* | Pukupuku | Pukupuku |
| 99 | *none* | Pukupuku | PukupukuBig |
| 100 | *none* | PukupukuRed | PukupukuRed |
| 101 | *none* | PukupukuRed | PukupukuRedBig |
| 102 | *none* | Bubble | Bubble |
| 103 | *none* | Bubble | BubbleBig |
| 104 | *none* | Wanwan | Wanwan |
| 105 | *none* | Wanwan | WanwanBig |
| 106 | *none* | Koopa | KoopaM1 |
| 107 | *none* | Koopa | KoopaM1Big |
| 108 | *none* | Koopa | KoopaM3 |
| 109 | *none* | Koopa | KoopaM3Big |
| 110 | *none* | Koopa | KoopaMW |
| 111 | *none* | Koopa | KoopaMWBig |
| 112 | *none* | Koopa | KoopaWU |
| 113 | *none* | Koopa | KoopaWUBig |
| 114 | *none* | KoopaJr | KoopaJr |
| 115 | *none* | KoopaJr | KoopaJrBig |
| 116 | *none* | FishBone | FishBone |
| 117 | *none* | FishBone | FishBoneBig |
| 118 | *none* | Saw |  |
| 119 | *none* | SuperKinoko |  |
| 120 | *none* | FireFlower |  |
| 121 | *none* | SuperStar |  |
| 122 | *none* | 1upKinoko |  |
| 123 | *none* | Leave |  |
| 124 | *none* | Feather |  |
| 125 | *none* | Propeller |  |
| 126 | *none* | Shoes |  |
| 127 | *none* | HatenaKinoko |  |
| 128 | *none* | BigKinoko |  |
| 129 | *none* | CharaMario |  |
| 130 | *none* | Door |  |
| 131 | *none* | YoshiEgg |  |
| 132 | *none* | Hammer |  |
| 133 | *none* | EnmyFire |  |
| 134 | *none* | YoshiFire |  |
| 135 | *none* | BulletYoshiBone |  |
| 136 | *none* | BulletToge |  |
| 137 | *none* | KameckMagic |  |
| 138 | *none* | BulletBone |  |
| 139 | *none* | BulletSenkanBall |  |
| 140 | *none* | BulletSpanner |  |
| 141 | *none* | BulletKoopaFire |  |
| 142 | *none* | BulletKoopaFireFall |  |
| 143 | *none* | ShoesAttack |  |
| 144 | *none* | JugemCloud | JugemCloud |
| 145 | *none* | EnemyTowerManager |  |
| 146 | *none* | KoopaFireEmitter |  |
| 147 | *none* | MapObjCoinDemoJump |  |
| 148 | *none* | MapObjCoinHopJump |  |
| 149 | *none* | MapObjCoinYoshiEat |  |
| 150 | *none* | StartSignBoard |  |
| 151 | *none* | CastleBridge |  |
| 152 | *none* | AirSignBoard |  |
| 153 | *none* | DemoPlayer |  |
| 154 | *none* | DemoPeach |  |
| 155 | 69 | EditPlayer |  |
| 156 | 7 | EditGround | EditGround |
| 157 | 9 | EditDokan | EditDokan |
| 158 | 14 | EditGroundMushroom | EditGroundMushRoom |
| 159 | 16 | EditGroundBox | EditGroundBox |
| 160 | 17 | EditBridge | EditBridge |
| 161 | 53 | EditBeltConveyor | EditBeltConveyor |
| 162 | 64 | EditTsuta | EditTsuta |
| 163 | 59 | EditRail | EditRail |
| 164 | 31 | EditJugemCloud | EditJugemCloud |
| 165 | 42 | EditKoopaClown | EditKoopaClown |
| 166 | 0 | EditKuribo | EditKuribo |
| 167 | 45 | EditKutsuKuribo | EditKutsuKuribo |
| 168 | 1 | EditNokonoko | EditNokonoko |
| 169 | 2 | EditPakkun | EditPakkun |
| 170 | 57 | EditBlackPakkun | EditBlackPakkun |
| 171 | 3 | EditHammerBros | EditHammerBros |
| 172 | 12 | EditDossun | EditDossun |
| 173 | 13 | EditKillerHoudai | EditKillerHoudai |
| 174 | 58 | EditPoo | EditPoo |
| 175 | 15 | EditBombhei | EditBombhei |
| 176 | 25 | EditTogezo | EditTogezo |
| 177 | 28 | EditMet | EditMet |
| 178 | 30 | EditJugem | EditJugem |
| 179 | 39 | EditKameck | EditKameck |
| 180 | 40 | EditTogemet | EditTogemet |
| 181 | 41 | EditTeresa | EditTeresa |
| 182 | 46 | EditKaron | EditKaron |
| 183 | 48 | EditGesso | EditGesso |
| 184 | 47 | EditSenkanHoudai | EditSenkanHoudai |
| 185 | 52 | EditHanachan | EditHanachan |
| 186 | 56 | EditPukupuku | EditPukupuku |
| 187 | 60 | EditBubble | EditBubble |
| 188 | 61 | EditWanwan | EditWanwan |
| 189 | 62 | EditKoopa | EditKoopa |
| 190 | *none* | EditKoopaJr | EditKoopaJr |
| 191 | 4 | EditRengaBlock | EditRengaBlock |
| 192 | 5 | EditHatenaBlock | EditHatenaBlock |
| 193 | 43 | EditToge | EditToge |
| 194 | 6 | EditHardBlock | EditHardBlock |
| 195 | 63 | EditIceBlock | EditIceBlock |
| 196 | 26 | EditGroundGoal |  |
| 197 | 37 | EditGroundStart |  |
| 198 | 49 | EditCastleBridge | EditCastleBridge |
| 199 | 55 | EditDoor | EditDoor |
| 200 | 27 | EditGoalPole |  |
| 201 | *none* | EditWing | EditWing |
| 202 | 10 | EditJumpStep | EditJumpStep |
| 203 | 11 | EditLift | EditLift |
| 204 | 36 | EditYouganLift | EditYouganLift |
| 205 | 18 | EditPSwitch | EditPSwitch |
| 206 | 19 | EditPowBlock | EditPowBlock |
| 207 | 20 | EditSuperKinoko | EditSuperKinoko |
| 208 | 44 | EditKinokoFunny | EditKinokoFunny |
| 209 | 33 | Edit1upKinoko | Edit1upKinoko |
| 210 | 34 | EditFireFlower | EditFireFlower |
| 211 | 35 | EditSuperStar | EditSuperStar |
| 212 | 50 | EditCharaKinoko | EditCharaKinoko |
| 213 | 51 | EditDekaKinoko | EditDekaKinoko |
| 214 | 65 | EditCharaMario | EditCharaMario |
| 215 | 21 | EditChikuwaBlock | EditChikuwaBlock |
| 216 | 22 | EditKumoBlock | EditKumoBlock |
| 217 | 23 | EditOnpuBlock | EditOnpuBlock |
| 218 | 29 | EditClearBlock | EditClearBlock |
| 219 | 32 | EditTsutaBlock | EditTsutaBlock |
| 220 | 8 | EditCoin | EditCoin |
| 221 | 24 | EditFireBar | EditFireBar |
| 222 | 54 | EditBurner | EditBurner |
| 223 | 38 | EditStartSignBoard |  |
| 224 | 66 | EditAirSignBoard | EditAirSignBoard |
| 225 | 67 | EditHalfHitWall | EditHalfHitWall |
| 226 | 68 | EditSaw | EditSaw |
| 227 | *none* | FlyWorker |  |
| 228 | *none* | FlyCourier |  |
| 229 | *none* | FlyChild |  |
| 230 | *none* | FlyBoss |  |
| 231 | *none* | FlyBomb |  |
| 232 | *none* | SampleActor |  |
| 233 | *none* | EnemySample | Sample |

