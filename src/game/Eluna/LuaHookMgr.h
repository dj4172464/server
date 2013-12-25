/**
 * mangos-zero is a full featured server for World of Warcraft in its vanilla
 * version, supporting clients for patch 1.12.x.
 *
 * Eluna provides an alternative Lua based scripting which allows your to
 * easily customize game content without the need for compilers or any
 * other development tools.
 *
 * Copyright (C) 2010-2013  Eluna Lua Engine <http://emudevs.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef LUAHOOKS_H
#define LUAHOOKS_H

struct AreaTriggerEntry;
struct SpellEntry;

class Aura;
class Channel;
class Creature;
class CreatureAI;
class GameObject;
class GameObjectAI;
class Guild;
class InstanceData;
class Item;
class Map;
class Object;
class Player;
class Quest;
class Spell;
class SpellCastTargets;
class Transport;
class Unit;
class WorldObject;

/**
 * @brief
 *
 */
enum RegisterTypes
{
    REGTYPE_SERVER,
    REGTYPE_PLAYER,
    REGTYPE_GUILD,
    REGTYPE_GROUP,
    REGTYPE_CREATURE,
    REGTYPE_CREATURE_GOSSIP,
    REGTYPE_GAMEOBJECT,
    REGTYPE_GAMEOBJECT_GOSSIP,
    REGTYPE_ITEM,
    REGTYPE_ITEM_GOSSIP,
    REGTYPE_PLAYER_GOSSIP,
    REGTYPE_COUNT
};

/**
 * @brief RegisterServerEvent(EventId, function)
 *
 */
enum ServerEvents
{
    // Server
    SERVER_EVENT_ON_NETWORK_START           =     1,       // Not Implemented
    SERVER_EVENT_ON_NETWORK_STOP            =     2,       // Not Implemented
    SERVER_EVENT_ON_SOCKET_OPEN             =     3,       // Not Implemented
    SERVER_EVENT_ON_SOCKET_CLOSE            =     4,       // Not Implemented
    SERVER_EVENT_ON_PACKET_RECEIVE          =     5,       // Not Implemented
    SERVER_EVENT_ON_PACKET_RECEIVE_UNKNOWN  =     6,       // Not Implemented
    SERVER_EVENT_ON_PACKET_SEND             =     7,       // Not Implemented

    // World
    WORLD_EVENT_ON_OPEN_STATE_CHANGE        =     8,       // (event, open)
    WORLD_EVENT_ON_CONFIG_LOAD              =     9,       // (event, reload)
    WORLD_EVENT_ON_MOTD_CHANGE              =     10,      // (event, newMOTD)
    WORLD_EVENT_ON_SHUTDOWN_INIT            =     11,      // (event, code, mask)
    WORLD_EVENT_ON_SHUTDOWN_CANCEL          =     12,      // (event)
    WORLD_EVENT_ON_UPDATE                   =     13,      // (event, diff)
    WORLD_EVENT_ON_STARTUP                  =     14,      // (event)
    WORLD_EVENT_ON_SHUTDOWN                 =     15,      // (event)

    // Eluna
    ELUNA_EVENT_ON_RESTART                  =     16,      // (event)

    // Map
    MAP_EVENT_ON_CREATE                     =     17,      // Not Implemented
    MAP_EVENT_ON_DESTROY                    =     18,      // Not Implemented
    MAP_EVENT_ON_LOAD                       =     19,      // Not Implemented
    MAP_EVENT_ON_UNLOAD                     =     20,      // Not Implemented
    MAP_EVENT_ON_PLAYER_ENTER               =     21,      // Not Implemented
    MAP_EVENT_ON_PLAYER_LEAVE               =     22,      // Not Implemented
    MAP_EVENT_ON_UPDATE                     =     23,      // Not Implemented

    // Area trigger
    TRIGGER_EVENT_ON_TRIGGER                =     24,      // (event, player, triggerId)

    // Weather
    WEATHER_EVENT_ON_CHANGE                 =     25,      // (event, weather, state, grade)

    // Auction house
    AUCTION_EVENT_ON_ADD                    =     26,      // Not Implemented
    AUCTION_EVENT_ON_REMOVE                 =     27,      // Not Implemented
    AUCTION_EVENT_ON_SUCCESFUL              =     28,      // Not Implemented
    AUCTION_EVENT_ON_EXPIRE                 =     29,      // Not Implemented

    SERVER_EVENT_COUNT
};

/**
 * @brief RegisterPlayerEvent(eventId, function)
 *
 */
enum PlayerEvents
{
    PLAYER_EVENT_ON_CHARACTER_CREATE        =     1,       // (event, player)
    PLAYER_EVENT_ON_CHARACTER_DELETE        =     2,       // (event, guid)
    PLAYER_EVENT_ON_LOGIN                   =     3,       // (event, player)
    PLAYER_EVENT_ON_LOGOUT                  =     4,       // (event, player)
    PLAYER_EVENT_ON_SPELL_CAST              =     5,       // (event, player, spell, skipCheck)
    PLAYER_EVENT_ON_KILL_PLAYER             =     6,       // (event, killer, killed)
    PLAYER_EVENT_ON_KILL_CREATURE           =     7,       // (event, killer, killed)
    PLAYER_EVENT_ON_KILLED_BY_CREATURE      =     8,       // (event, killer, killed)
    PLAYER_EVENT_ON_DUEL_REQUEST            =     9,       // (event, target, challenger)
    PLAYER_EVENT_ON_DUEL_START              =     10,      // (event, player1, player2)
    PLAYER_EVENT_ON_DUEL_END                =     11,      // (event, winner, loser, type)
    PLAYER_EVENT_ON_GIVE_XP                 =     12,      // (event, player, amount, victim)
    PLAYER_EVENT_ON_LEVEL_CHANGE            =     13,      // (event, player, oldLevel)
    PLAYER_EVENT_ON_MONEY_CHANGE            =     14,      // (event, player, amount)
    PLAYER_EVENT_ON_REPUTATION_CHANGE       =     15,      // (event, player, factionId, standing, incremental)
    PLAYER_EVENT_ON_TALENTS_CHANGE          =     16,      // (event, player, points)
    PLAYER_EVENT_ON_TALENTS_RESET           =     17,      // (event, player, noCost)
    PLAYER_EVENT_ON_CHAT                    =     18,      // (event, player, msg, Type, lang) - Can return false
    PLAYER_EVENT_ON_WHISPER                 =     19,      // (event, player, msg, Type, lang, receiver)
    PLAYER_EVENT_ON_GROUP_CHAT              =     20,      // (event, player, msg, Type, lang, group) - Can return false
    PLAYER_EVENT_ON_GUILD_CHAT              =     21,      // (event, player, msg, Type, lang, guild) - Can return false
    PLAYER_EVENT_ON_CHANNEL_CHAT            =     22,      // (event, player, msg, Type, lang, channel) - Can return false
    PLAYER_EVENT_ON_EMOTE                   =     23,      // (event, player, emote) - Not triggered on any known emote
    PLAYER_EVENT_ON_TEXT_EMOTE              =     24,      // (event, player, textEmote, emoteNum, guid)
    PLAYER_EVENT_ON_SAVE                    =     25,      // (event, player)
    PLAYER_EVENT_ON_BIND_TO_INSTANCE        =     26,      // (event, player, difficulty, mapid, permanent)
    PLAYER_EVENT_ON_UPDATE_ZONE             =     27,      // (event, player, newZone, newArea)
    PLAYER_EVENT_ON_MAP_CHANGE              =     28,      // (event, player)
    // Custom
    PLAYER_EVENT_ON_EQUIP                   =     29,      // (event, player, item, bag, slot)
    PLAYER_EVENT_ON_FIRST_LOGIN             =     30,      // (event, player)
    PLAYER_EVENT_ON_CAN_USE_ITEM            =     31,      // (event, player, itemEntry)
    PLAYER_EVENT_ON_LOOT_ITEM               =     32,      // (event, player, item, count)
    PLAYER_EVENT_ON_ENTER_COMBAT            =     33,      // (event, player, enemy)
    PLAYER_EVENT_ON_LEAVE_COMBAT            =     34,      // (event, player)
    PLAYER_EVENT_ON_REPOP                   =     35,      // (event, player)
    PLAYER_EVENT_ON_RESURRECT               =     36,      // (event, player)

    PLAYER_EVENT_COUNT
};

/**
 * @brief RegisterGuildEvent(eventId, function)
 *
 */
enum GuildEventTypes
{
    // Guild
    GUILD_EVENT_ON_ADD_MEMBER               =     1,       // (event, guild, player, rank)
    GUILD_EVENT_ON_REMOVE_MEMBER            =     2,       // (event, guild, isDisbanding, isKicked)
    GUILD_EVENT_ON_MOTD_CHANGE              =     3,       // (event, guild, newMotd)
    GUILD_EVENT_ON_INFO_CHANGE              =     4,       // (event, guild, newInfo)
    GUILD_EVENT_ON_CREATE                   =     5,       // (event, guild, leader, name)
    GUILD_EVENT_ON_DISBAND                  =     6,       // (event, guild)
    GUILD_EVENT_ON_MONEY_WITHDRAW           =     7,       // (event, guild, player, amount, isRepair)
    GUILD_EVENT_ON_MONEY_DEPOSIT            =     8,       // (event, guild, player, amount)
    GUILD_EVENT_ON_ITEM_MOVE                =     9,       // (event, guild, player, item, isSrcBank, srcContainer, srcSlotId, isDestBank, destContainer, destSlotId)
    GUILD_EVENT_ON_EVENT                    =     10,      // (event, guild, eventType, plrGUIDLow1, plrGUIDLow2, newRank)
    GUILD_EVENT_ON_BANK_EVENT               =     11,      // (event, guild, eventType, tabId, playerGUIDLow, itemOrMoney, itemStackCount, destTabId)

    GUILD_EVENT_COUNT
};

/**
 * @brief RegisterGroupEvent(eventId, function)
 *
 */
enum GroupEvents
{
    // Group
    GROUP_EVENT_ON_MEMBER_ADD               =     1,       // (event, group, guid)
    GROUP_EVENT_ON_MEMBER_INVITE            =     2,       // (event, group, guid)
    GROUP_EVENT_ON_MEMBER_REMOVE            =     3,       // (event, group, guid, method, kicker, reason)
    GROUP_EVENT_ON_LEADER_CHANGE            =     4,       // (event, group, newLeaderGuid, oldLeaderGuid)
    GROUP_EVENT_ON_DISBAND                  =     5,       // (event, group)
    GROUP_EVENT_ON_CREATE                   =     6,       // (event, group, leaderGuid, groupType)

    GROUP_EVENT_COUNT
};

/**
 * @brief RegisterCreatureEvent(entry, EventId, function)
 *
 */
enum CreatureEvents
{
    CREATURE_EVENT_ON_ENTER_COMBAT                    = 1,  // (event, creature, target)
    CREATURE_EVENT_ON_LEAVE_COMBAT                    = 2,  // (event, creature)
    CREATURE_EVENT_ON_TARGET_DIED                     = 3,  // (event, creature, victim)
    CREATURE_EVENT_ON_DIED                            = 4,  // (event, creature, killer)
    CREATURE_EVENT_ON_SPAWN                           = 5,  // (event, creature)
    CREATURE_EVENT_ON_REACH_WP                        = 6,  // (event, creature, type, id)
    CREATURE_EVENT_ON_AIUPDATE                        = 7,  // (event, creature, diff)
    CREATURE_EVENT_ON_RECEIVE_EMOTE                   = 8,  // (event, creature, player, emoteid)
    CREATURE_EVENT_ON_DAMAGE_TAKEN                    = 9,  // (event, creature, attacker, damage)
    CREATURE_EVENT_ON_PRE_COMBAT                      = 10, // (event, creature, target)
    CREATURE_EVENT_ON_ATTACKED_AT                     = 11, // (event, creature, attacker)
    CREATURE_EVENT_ON_OWNER_ATTACKED                  = 12, // (event, creature, target)
    CREATURE_EVENT_ON_OWNER_ATTACKED_AT               = 13, // (event, creature, attacker)
    CREATURE_EVENT_ON_HIT_BY_SPELL                    = 14, // (event, creature, caster, spellid)
    CREATURE_EVENT_ON_SPELL_HIT_TARGET                = 15, // (event, creature, target, spellid)
    CREATURE_EVENT_ON_SPELL_CLICK                     = 16, // (event, creature, clicker)
    CREATURE_EVENT_ON_CHARMED                         = 17, // (event, creature, apply)
    CREATURE_EVENT_ON_POSSESS                         = 18, // (event, creature, apply)
    CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE          = 19, // (event, creature, summon)
    CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN       = 20, // (event, creature, summon)
    CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED          = 21, // (event, creature, summon, killer)
    CREATURE_EVENT_ON_SUMMONED                        = 22, // (event, creature, summoner)
    CREATURE_EVENT_ON_RESET                           = 23, // (event, creature)
    CREATURE_EVENT_ON_REACH_HOME                      = 24, // (event, creature)
    CREATURE_EVENT_ON_CAN_RESPAWN                     = 25, // (event, creature)
    CREATURE_EVENT_ON_CORPSE_REMOVED                  = 26, // (event, creature, respawndelay)
    CREATURE_EVENT_ON_MOVE_IN_LOS                     = 27, // (event, creature, unit)
    CREATURE_EVENT_ON_VISIBLE_MOVE_IN_LOS             = 28, // (event, creature, unit)
    CREATURE_EVENT_ON_PASSANGER_BOARDED               = 29, // (event, creature, passanger, seatid, apply)
    CREATURE_EVENT_ON_DUMMY_EFFECT                    = 30, // (event, caster, spellid, effindex, creature)
    CREATURE_EVENT_ON_QUEST_ACCEPT                    = 31, // (event, player, creature, quest)
    CREATURE_EVENT_ON_QUEST_SELECT                    = 32, // (event, player, creature, quest)
    CREATURE_EVENT_ON_QUEST_COMPLETE                  = 33, // (event, player, creature, quest)
    CREATURE_EVENT_ON_QUEST_REWARD                    = 34, // (event, player, creature, quest, opt)
    CREATURE_EVENT_ON_DIALOG_STATUS                   = 35, // (event, player, creature)
    CREATURE_EVENT_COUNT
};

/**
 * @brief RegisterGameObjectEvent(entry, EventId, function)
 *
 */
enum GameObjectEvents
{
    GAMEOBJECT_EVENT_ON_AIUPDATE                    = 1,    // (event, go, diff)
    GAMEOBJECT_EVENT_ON_RESET                       = 2,    // (event, go)
    GAMEOBJECT_EVENT_ON_DUMMY_EFFECT                = 3,    // (event, caster, spellid, effindex, go)
    GAMEOBJECT_EVENT_ON_QUEST_ACCEPT                = 4,    // (event, player, go, quest)
    GAMEOBJECT_EVENT_ON_QUEST_REWARD                = 5,    // (event, player, go, quest, opt)
    GAMEOBJECT_EVENT_ON_DIALOG_STATUS               = 6,    // (event, player, go)
    GAMEOBJECT_EVENT_ON_DESTROYED                   = 7,    // (event, go, player)          // TODO
    GAMEOBJECT_EVENT_ON_DAMAGED                     = 8,    // (event, go, player)          // TODO
    GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE           = 9,    // (event, go, state, unit)     // TODO
    GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED            = 10,   // (event, go, state)           // TODO
    GAMEOBJECT_EVENT_ON_QUEST_COMPLETE              = 11,   // (event, player, go, quest)
    GAMEOBJECT_EVENT_COUNT
};

/**
 * @brief RegisterItemEvent(entry, EventId, function)
 *
 */
enum ItemEvents
{
    ITEM_EVENT_ON_DUMMY_EFFECT                      = 1,    // (event, caster, spellid, effindex, item)
    ITEM_EVENT_ON_USE                               = 2,    // (event, player, item, target)
    ITEM_EVENT_ON_QUEST_ACCEPT                      = 3,    // (event, player, item, quest)
    ITEM_EVENT_ON_EXPIRE                            = 4,    // (event, player, itemid)
    ITEM_EVENT_COUNT
};

// RegisterCreatureGossipEvent(entry, EventId, function)
// RegisterGameObjectGossipEvent(entry, EventId, function)
// RegisterItemGossipEvent(entry, EventId, function)
// RegisterPlayerGossipEvent(menu_id, EventId, function)
/**
 * @brief
 *
 */
enum GossipEvents
{
    GOSSIP_EVENT_ON_HELLO                           = 1,    // (event, player, object) - Object is the Creature/GameObject/Item
    GOSSIP_EVENT_ON_SELECT                          = 2,    // (event, player, object, sender, intid, code, menu_id) - Object is the Creature/GameObject/Item/Player, menu_id is only for player gossip
    GOSSIP_EVENT_COUNT
};

/**
 * @brief
 *
 */
struct HookMgr
{
    struct ElunaCreatureAI;
    struct ElunaGameObjectAI;
    /**
     * @brief
     *
     * @param creature
     * @return CreatureAI
     */
    CreatureAI* GetAI(Creature* creature);
    /**
     * @brief
     *
     * @param gameObject
     * @return GameObjectAI
     */
    GameObjectAI* GetAI(GameObject* gameObject);

    /* Misc */
    /**
     * @brief
     *
     * @param diff
     */
    void OnWorldUpdate(uint32 diff);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pItem
     * @param count
     * @param guid
     */
    void OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnFirstLogin(Player* pPlayer);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pItem
     * @param bag
     * @param slot
     */
    void OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnRepop(Player* pPlayer);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnResurrect(Player* pPlayer);
    /**
     * @brief
     *
     * @param pPlayer
     * @param itemEntry
     * @return InventoryResult
     */
    InventoryResult OnCanUseItem(const Player* pPlayer, uint32 itemEntry);
    /**
     * @brief
     *
     */
    void OnEngineRestart();
    /* Item */
    /**
     * @brief
     *
     * @param pCaster
     * @param spellId
     * @param effIndex
     * @param pTarget
     * @return bool
     */
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Item* pTarget);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pItem
     * @param pQuest
     * @return bool
     */
    bool OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pItem
     * @param targets
     * @return bool
     */
    bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pProto
     * @return bool
     */
    bool OnExpire(Player* pPlayer, ItemPrototype const* pProto);
    /**
     * @brief
     *
     * @param pPlayer
     * @param item
     * @param sender
     * @param action
     * @param code
     */
    void HandleGossipSelectOption(Player* pPlayer, Item* item, uint32 sender, uint32 action, std::string code);
    /* Creature */
    /**
     * @brief
     *
     * @param pCaster
     * @param spellId
     * @param effIndex
     * @param pTarget
     * @return bool
     */
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pTarget);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @return bool
     */
    bool OnGossipHello(Player* pPlayer, Creature* pCreature);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @param sender
     * @param action
     * @return bool
     */
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @param sender
     * @param action
     * @param code
     * @return bool
     */
    bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @param pQuest
     * @return bool
     */
    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @param pQuest
     * @return bool
     */
    bool OnQuestSelect(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @param pQuest
     * @return bool
     */
    bool OnQuestComplete(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @param pQuest
     * @return bool
     */
    bool OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pCreature
     * @return uint32
     */
    uint32 GetDialogStatus(Player* pPlayer, Creature* pCreature);
    /* GameObject */
    /**
     * @brief
     *
     * @param pCaster
     * @param spellId
     * @param effIndex
     * @param pTarget
     * @return bool
     */
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @return bool
     */
    bool OnGossipHello(Player* pPlayer, GameObject* pGameObject);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @param sender
     * @param action
     * @return bool
     */
    bool OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @param sender
     * @param action
     * @param code
     * @return bool
     */
    bool OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @param pQuest
     * @return bool
     */
    bool OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @param pQuest
     * @return bool
     */
    bool OnQuestComplete(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @param pQuest
     * @return bool
     */
    bool OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @return bool
     */
    bool OnGameObjectUse(Player* pPlayer, GameObject* pGameObject) { return false; } // TODO? Not on TC
    /**
     * @brief
     *
     * @param pPlayer
     * @param pGameObject
     * @return uint32
     */
    uint32 GetDialogStatus(Player* pPlayer, GameObject* pGameObject);
    /**
     * @brief
     *
     * @param pGameObject
     * @param pPlayer
     */
    void OnDestroyed(GameObject* pGameObject, Player* pPlayer); // TODO
    /**
     * @brief
     *
     * @param pGameObject
     * @param pPlayer
     */
    void OnDamaged(GameObject* pGameObject, Player* pPlayer); // TODO
    /**
     * @brief
     *
     * @param pGameObject
     * @param state
     * @param pUnit
     */
    void OnLootStateChanged(GameObject* pGameObject, uint32 state, Unit* pUnit); // TODO
    /**
     * @brief
     *
     * @param pGameObject
     * @param state
     */
    void OnGameObjectStateChanged(GameObject* pGameObject, uint32 state); // TODO
    /* Player */
    /**
     * @brief
     *
     * @param pPlayer
     * @param pEnemy
     */
    void OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnPlayerLeaveCombat(Player* pPlayer);
    /**
     * @brief
     *
     * @param pKiller
     * @param pKilled
     */
    void OnPVPKill(Player* pKiller, Player* pKilled);
    /**
     * @brief
     *
     * @param pKiller
     * @param pKilled
     */
    void OnCreatureKill(Player* pKiller, Creature* pKilled);
    /**
     * @brief
     *
     * @param pKiller
     * @param pKilled
     */
    void OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled);
    /**
     * @brief
     *
     * @param pPlayer
     * @param oldLevel
     */
    void OnLevelChanged(Player* pPlayer, uint8 oldLevel);
    /**
     * @brief
     *
     * @param pPlayer
     * @param newPoints
     */
    void OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints);
    /**
     * @brief
     *
     * @param pPlayer
     * @param noCost
     */
    void OnTalentsReset(Player* pPlayer, bool noCost);
    /**
     * @brief
     *
     * @param pPlayer
     * @param amount
     */
    void OnMoneyChanged(Player* pPlayer, int32& amount);
    /**
     * @brief
     *
     * @param pPlayer
     * @param amount
     * @param pVictim
     */
    void OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim);
    /**
     * @brief
     *
     * @param pPlayer
     * @param factionID
     * @param standing
     * @param incremental
     */
    void OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental);
    /**
     * @brief
     *
     * @param pTarget
     * @param pChallenger
     */
    void OnDuelRequest(Player* pTarget, Player* pChallenger);
    /**
     * @brief
     *
     * @param pStarter
     * @param pChallenger
     */
    void OnDuelStart(Player* pStarter, Player* pChallenger);
    /**
     * @brief
     *
     * @param pWinner
     * @param pLoser
     * @param type
     */
    void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type);
    /**
     * @brief
     *
     * @param pPlayer
     * @param type
     * @param lang
     * @param msg
     * @param pReceiver
     */
    void OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver);
    /**
     * @brief
     *
     * @param pPlayer
     * @param type
     * @param lang
     * @param msg
     * @return bool
     */
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg);
    /**
     * @brief
     *
     * @param pPlayer
     * @param type
     * @param lang
     * @param msg
     * @param pGroup
     * @return bool
     */
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup);
    /**
     * @brief
     *
     * @param pPlayer
     * @param type
     * @param lang
     * @param msg
     * @param pGuild
     * @return bool
     */
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild);
    /**
     * @brief
     *
     * @param pPlayer
     * @param type
     * @param lang
     * @param msg
     * @param pChannel
     * @return bool
     */
    bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel);
    /**
     * @brief
     *
     * @param pPlayer
     * @param emote
     */
    void OnEmote(Player* pPlayer, uint32 emote);
    /**
     * @brief
     *
     * @param pPlayer
     * @param textEmote
     * @param emoteNum
     * @param guid
     */
    void OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid);
    /**
     * @brief
     *
     * @param pPlayer
     * @param pSpell
     * @param skipCheck
     */
    void OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnLogin(Player* pPlayer);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnLogout(Player* pPlayer);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnCreate(Player* pPlayer);
    /**
     * @brief
     *
     * @param guid
     */
    void OnDelete(uint32 guid);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnSave(Player* pPlayer);
    /**
     * @brief
     *
     * @param pPlayer
     * @param difficulty
     * @param mapid
     * @param permanent
     */
    void OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent);
    /**
     * @brief
     *
     * @param pPlayer
     * @param newZone
     * @param newArea
     */
    void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea);
    /**
     * @brief
     *
     * @param pPlayer
     */
    void OnMapChanged(Player* pPlayer); // TODO
    /**
     * @brief
     *
     * @param pPlayer
     * @param menuId
     * @param sender
     * @param action
     * @param code
     */
    void HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, std::string code);
    /* AreaTrigger */
    /**
     * @brief
     *
     * @param pPlayer
     * @param pTrigger
     * @return bool
     */
    bool OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger);
    /* Weather */
    /**
     * @brief
     *
     * @param weather
     * @param state
     * @param grade
     */
    void OnChange(Weather* weather, WeatherState state, float grade); // TODO
    // condition
    // bool OnConditionCheck(Condition* condition, ConditionSourceInfo& sourceInfo); // TODO ?
    // transport
    /**
     * @brief
     *
     * @param transport
     * @param player
     */
    void OnAddPassenger(Transport* transport, Player* player); // TODO
    /**
     * @brief
     *
     * @param transport
     * @param creature
     */
    void OnAddCreaturePassenger(Transport* transport, Creature* creature); // TODO
    /**
     * @brief
     *
     * @param transport
     * @param player
     */
    void OnRemovePassenger(Transport* transport, Player* player); // TODO
    /**
     * @brief
     *
     * @param transport
     * @param waypointId
     * @param mapId
     * @param x
     * @param y
     * @param z
     */
    void OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z); // TODO
    /* Guild */
    /**
     * @brief
     *
     * @param guild
     * @param player
     * @param plRank
     */
    void OnAddMember(Guild* guild, Player* player, uint32 plRank);
    /**
     * @brief
     *
     * @param guild
     * @param player
     * @param isDisbanding
     * @param isKicked
     */
    void OnRemoveMember(Guild* guild, Player* player, bool isDisbanding, bool isKicked); // IsKicked not a part of Mangos, implement?
    /**
     * @brief
     *
     * @param guild
     * @param newMotd
     */
    void OnMOTDChanged(Guild* guild, const std::string& newMotd);
    /**
     * @brief
     *
     * @param guild
     * @param newInfo
     */
    void OnInfoChanged(Guild* guild, const std::string& newInfo);
    /**
     * @brief
     *
     * @param guild
     * @param leader
     * @param name
     */
    void OnCreate(Guild* guild, Player* leader, const std::string& name);
    /**
     * @brief
     *
     * @param guild
     */
    void OnDisband(Guild* guild);
    /**
     * @brief
     *
     * @param guild
     * @param player
     * @param amount
     * @param isRepair
     */
    void OnMemberWitdrawMoney(Guild* guild, Player* player, uint32 &amount, bool isRepair);
    /**
     * @brief
     *
     * @param guild
     * @param player
     * @param amount
     */
    void OnMemberDepositMoney(Guild* guild, Player* player, uint32 &amount);
    /**
     * @brief
     *
     * @param guild
     * @param player
     * @param pItem
     * @param isSrcBank
     * @param srcContainer
     * @param srcSlotId
     * @param isDestBank
     * @param destContainer
     * @param destSlotId
     */
    void OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId, bool isDestBank, uint8 destContainer, uint8 destSlotId); // TODO: Implement
    /**
     * @brief
     *
     * @param guild
     * @param eventType
     * @param playerGuid1
     * @param playerGuid2
     * @param newRank
     */
    void OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank); // TODO: Implement
    /**
     * @brief
     *
     * @param guild
     * @param eventType
     * @param tabId
     * @param playerGuid
     * @param itemOrMoney
     * @param itemStackCount
     * @param destTabId
     */
    void OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId);
    /* Group */
    /**
     * @brief
     *
     * @param group
     * @param guid
     */
    void OnAddMember(Group* group, uint64 guid);
    /**
     * @brief
     *
     * @param group
     * @param guid
     */
    void OnInviteMember(Group* group, uint64 guid);
    /**
     * @brief
     *
     * @param group
     * @param guid
     * @param method
     * @param kicker
     * @param reason
     */
    void OnRemoveMember(Group* group, uint64 guid, uint8 method, uint64 kicker, const char* reason); // Kicker and Reason not a part of Mangos, implement?
    /**
     * @brief
     *
     * @param group
     * @param newLeaderGuid
     * @param oldLeaderGuid
     */
    void OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid);
    /**
     * @brief
     *
     * @param group
     */
    void OnDisband(Group* group);
    /**
     * @brief
     *
     * @param group
     * @param leaderGuid
     * @param groupType
     */
    void OnCreate(Group* group, uint64 leaderGuid, GroupType groupType);
};
#define sHookMgr MaNGOS::Singleton<HookMgr>::Instance()

#endif
