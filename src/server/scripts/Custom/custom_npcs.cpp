/*
* Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Creature.h"
#include "Chat.h"
#include "Log.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "World.h"
#include "WorldSession.h"

enum eEnums
{
    ACHIEVEMENT_BROKEN_ISLES_PATHFINDER_1   = 11190,
    ACHIEVEMENT_BROKEN_ISLES_PATHFINDER_2   = 11446
};


class npc_change_rates : public CreatureScript
{
public:
    npc_change_rates() : CreatureScript("npc_change_rates") { }

#define MAX_RATE uint32(10)

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        for (uint32 i = 1; i <= MAX_RATE; ++i)
        {
            if (i == player->GetPersonnalXpRate())
                continue;

            if (i == sWorld->getRate(RATE_XP_KILL))
                continue;

            std::ostringstream gossipText;
            gossipText << "Rate x" << i;
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, gossipText.str(), GOSSIP_SENDER_MAIN, i);
        }

        if (player->GetPersonnalXpRate())
        {
            std::ostringstream gossipText;
            gossipText << "Default Rate - x" << sWorld->getRate(RATE_XP_KILL);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, gossipText.str(), GOSSIP_SENDER_MAIN, 0);
        }

        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 uiAction) override
    {
        player->CLOSE_GOSSIP_MENU();
        player->SetPersonnalXpRate(float(std::min(MAX_RATE, uiAction)));
        return true;
    }
};


class npc_pre_register_bonus : public CreatureScript
{
    public:
        npc_pre_register_bonus() : CreatureScript("npc_pre_register_bonus") {}


        bool OnGossipHello(Player* player, Creature* creature) override
        {
            bool getBonusState;

            getBonusState = player->GetBonusUsed(player->GetSession()->GetAccountId());
            if (getBonusState == true)
            {
            
                std::stringstream gossipTextBonus;
                gossipTextBonus << "Give me my Bonus (You can only get this once ever)";
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, gossipTextBonus.str(), GOSSIP_SENDER_MAIN, 0);

                std::stringstream gossipTextItems;
                gossipTextItems << "PlaceHolder";
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, gossipTextBonus.str(), GOSSIP_SENDER_MAIN, 1);

                player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                return true;
            }
            if (getBonusState == false)
            {
                return false;
            }
        }

        bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 uiAction) override
        {
                auto achievementEntryPathfinder1 = sAchievementStore.LookupEntry(ACHIEVEMENT_BROKEN_ISLES_PATHFINDER_1);
                auto achievementEntryPathfinder2 = sAchievementStore.LookupEntry(ACHIEVEMENT_BROKEN_ISLES_PATHFINDER_2);
                int playerClass = player->getClass();
                player->CLOSE_GOSSIP_MENU();
                player->GiveLevel(110);
                player->ModifyMoney(50000000);

                switch (playerClass)
                {
                    //Warrior [DONE]
                case 1:
                {
                    //Head
                    player->AddItem(139684, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134360, 1);
                    //Back
                    player->AddItem(138374, 1);
                    //Chest
                    player->AddItem(139681, 1);
                    //Wrist
                    player->AddItem(139688, 1);
                    //Hands
                    player->AddItem(137429, 1);
                    //Waist
                    player->AddItem(139687, 1);
                    //Legs
                    player->AddItem(139685, 1);
                    //Feet
                    player->AddItem(139682, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Paladin [DONE]
                case 2:
                {
                    //Head
                    player->AddItem(139693, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134360, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139690, 1);
                    //Wrist
                    player->AddItem(139697, 1);
                    //Hands
                    player->AddItem(137429, 1);
                    //Waist
                    player->AddItem(139696, 1);
                    //Legs
                    player->AddItem(139694, 1);
                    //Feet
                    player->AddItem(139691, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Hunter [DONE]
                case 3:
                {
                    //Head
                    player->AddItem(139710, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134479, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139707, 1);
                    //Wrist
                    player->AddItem(139714, 1);
                    //Hands
                    player->AddItem(134468, 1);
                    //Waist
                    player->AddItem(139713, 1);
                    //Legs
                    player->AddItem(139711, 1);
                    //Feet
                    player->AddItem(139708, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Rogue [DONE]
                case 4:
                {
                    //Head
                    player->AddItem(139742, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(137455, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139739, 1);
                    //Wrist
                    player->AddItem(139746, 1);
                    //Hands
                    player->AddItem(134371, 1);
                    //Waist
                    player->AddItem(139745, 1);
                    //Legs
                    player->AddItem(139743, 1);
                    //Feet
                    player->AddItem(139740, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Priest [DONE]
                case 5:
                {
                    //Head
                    player->AddItem(139757, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134430, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139759, 1);
                    //Wrist
                    player->AddItem(139762, 1);
                    //Hands
                    player->AddItem(134393, 1);
                    //Waist
                    player->AddItem(139761, 1);
                    //Legs
                    player->AddItem(139758, 1);
                    //Feet
                    player->AddItem(139755, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Death Knight [DONE]
                case 6:
                {
                    //Head
                    player->AddItem(139676, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134360, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139673, 1);
                    //Wrist
                    player->AddItem(139680, 1);
                    //Hands
                    player->AddItem(137429, 1);
                    //Waist
                    player->AddItem(139679, 1);
                    //Legs
                    player->AddItem(139677, 1);
                    //Feet
                    player->AddItem(139674, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    //Dalaran Homestone
                    player->AddItem(140192, 1);
                    break;
                }
                //Shaman [DONE]
                case 7:
                {
                    //Head
                    player->AddItem(139701, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134479, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139698, 1);
                    //Wrist
                    player->AddItem(139705, 1);
                    //Hands
                    player->AddItem(134468, 1);
                    //Waist
                    player->AddItem(139704, 1);
                    //Legs
                    player->AddItem(139702, 1);
                    //Feet
                    player->AddItem(139699, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Mage [DONE]
                case 8:
                {
                    //Head
                    player->AddItem(139749, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134430, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139751, 1);
                    //Wrist
                    player->AddItem(139754, 1);
                    //Hands
                    player->AddItem(134393, 1);
                    //Waist
                    player->AddItem(139753, 1);
                    //Legs
                    player->AddItem(139750, 1);
                    //Feet
                    player->AddItem(139747, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Warlock [DONE]
                case 9:
                {
                    //Head
                    player->AddItem(139765, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(134430, 1);
                    //Back
                    player->AddItem(138374, 1);
                    //Chest
                    player->AddItem(139767, 1);
                    //Wrist
                    player->AddItem(139770, 1);
                    //Hands
                    player->AddItem(134393, 1);
                    //Waist
                    player->AddItem(139769, 1);
                    //Legs
                    player->AddItem(139766, 1);
                    //Feet
                    player->AddItem(139763, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Monk [DONE]
                case 10:
                {
                    //Head
                    player->AddItem(139734, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(137455, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139731, 1);
                    //Wrist
                    player->AddItem(139738, 1);
                    //Hands
                    player->AddItem(134371, 1);
                    //Waist
                    player->AddItem(139737, 1);
                    //Legs
                    player->AddItem(139735, 1);
                    //Feet
                    player->AddItem(139732, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Druid [DONE]
                case 11:
                {
                    //Head
                    player->AddItem(139726, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(137455, 1);
                    //Back
                    player->AddItem(133639, 1);
                    //Chest
                    player->AddItem(139723, 1);
                    //Wrist
                    player->AddItem(139730, 1);
                    //Hands
                    player->AddItem(134371, 1);
                    //Waist
                    player->AddItem(139729, 1);
                    //Legs
                    player->AddItem(139727, 1);
                    //Feet
                    player->AddItem(139724, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }
                //Demon Hunter [DONE]
                case 12:
                {
                    //Head
                    player->AddItem(139718, 1);
                    //Neck
                    player->AddItem(137487, 1);
                    //Shoulder
                    player->AddItem(137455, 1);
                    //Back
                    player->AddItem(138374, 1);
                    //Chest
                    player->AddItem(139715, 1);
                    //Wrist
                    player->AddItem(138722, 1);
                    //Hands
                    player->AddItem(134371, 1);
                    //Waist
                    player->AddItem(139721, 1);
                    //Legs
                    player->AddItem(139719, 1);
                    //Feet
                    player->AddItem(139716, 1);
                    //Ring 1
                    player->AddItem(151308, 1);
                    //Ring 2
                    player->AddItem(151311, 1);
                    //Trinket 1
                    player->AddItem(137419, 1);
                    //Trinket 2
                    player->AddItem(137459, 1);
                    break;
                }

                }
                player->CompletedAchievement(achievementEntryPathfinder1);
                player->CompletedAchievement(achievementEntryPathfinder2);
                player->TeleportTo(1220, -828.835, 4371.91, 738.636, 1.88158);
                player->SetBonusUsed(player->GetSession()->GetAccountId());
                return true;
            }
};

void AddSC_custom_npcs()
{
    new npc_change_rates();
    new npc_pre_register_bonus();
}
