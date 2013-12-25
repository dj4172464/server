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

#ifndef GLOBALMETHODS_H
#define GLOBALMETHODS_H

extern void StartEluna(bool restart);

namespace LuaGlobalFunctions
{
    /**
     * @brief RegisterServerEvent(event, function)
     *
     * @param L
     * @return int
     */
    int RegisterServerEvent(lua_State* L)
    {
        lua_settop(L, 2);
        uint32 ev = luaL_checkunsigned(L, 1);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_SERVER, 0, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterPlayerEvent(event, function)
     *
     * @param L
     * @return int
     */
    int RegisterPlayerEvent(lua_State* L)
    {
        lua_settop(L, 2);
        uint32 ev = luaL_checkunsigned(L, 1);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_PLAYER, 0, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterGuildEvent(event, function)
     *
     * @param L
     * @return int
     */
    int RegisterGuildEvent(lua_State* L)
    {
        lua_settop(L, 2);
        uint32 ev = luaL_checkunsigned(L, 1);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_GUILD, 0, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterGroupEvent(event, function)
     *
     * @param L
     * @return int
     */
    int RegisterGroupEvent(lua_State* L)
    {
        lua_settop(L, 2);
        uint32 ev = luaL_checkunsigned(L, 1);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_GROUP, 0, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterCreatureGossipEvent(entry, event, function)
     *
     * @param L
     * @return int
     */
    int RegisterCreatureGossipEvent(lua_State* L)
    {
        lua_settop(L, 3);
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 ev = luaL_checkunsigned(L, 2);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_CREATURE_GOSSIP, entry, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterGameObjectGossipEvent(entry, event, function)
     *
     * @param L
     * @return int
     */
    int RegisterGameObjectGossipEvent(lua_State* L)
    {
        lua_settop(L, 3);
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 ev = luaL_checkunsigned(L, 2);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_GAMEOBJECT_GOSSIP, entry, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterItemEvent(entry, event, function)
     *
     * @param L
     * @return int
     */
    int RegisterItemEvent(lua_State* L)
    {
        lua_settop(L, 3);
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 ev = luaL_checkunsigned(L, 2);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_ITEM, entry, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterItemGossipEvent(entry, event, function)
     *
     * @param L
     * @return int
     */
    int RegisterItemGossipEvent(lua_State* L)
    {
        lua_settop(L, 3);
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 ev = luaL_checkunsigned(L, 2);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_ITEM_GOSSIP, entry, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterPlayerGossipEvent(menu_id, event, function)
     *
     * @param L
     * @return int
     */
    int RegisterPlayerGossipEvent(lua_State* L)
    {
        lua_settop(L, 3);
        uint32 menu_id = luaL_checkunsigned(L, 1);
        uint32 ev = luaL_checkunsigned(L, 2);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_PLAYER_GOSSIP, menu_id, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterCreatureEvent(entry, event, function)
     *
     * @param L
     * @return int
     */
    int RegisterCreatureEvent(lua_State* L)
    {
        lua_settop(L, 3);
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 ev = luaL_checkunsigned(L, 2);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_CREATURE, entry, ev, functionRef);
        return 0;
    }

    /**
     * @brief RegisterGameObjectEvent(entry, event, function)
     *
     * @param L
     * @return int
     */
    int RegisterGameObjectEvent(lua_State* L)
    {
        lua_settop(L, 3);
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 ev = luaL_checkunsigned(L, 2);
        if (ev == 0)
        {
            luaL_error(L, "0 is not a valid event");
            return 0;
        }
        luaL_checktype(L, lua_gettop(L), LUA_TFUNCTION);

        int functionRef  = lua_ref(L, true);
        if (functionRef > 0)
            sEluna.Register(REGTYPE_GAMEOBJECT, entry, ev, functionRef);
        return 0;
    }

    /**
     * @brief GetLuaEngine() - Gets lua engine name
     *
     * @param L
     * @return int
     */
    int GetLuaEngine(lua_State* L)
    {
        sEluna.Push(L, "ElunaEngine");
        return 1;
    }

    /**
     * @brief GetCoreVersion() - Gets core version as a string
     *
     * @param L
     * @return int
     */
    int GetCoreVersion(lua_State* L)
    {
        sEluna.Push(L, REVISION_NR);
        return 1;
    }

    /**
     * @brief GetQuest(questId)
     *
     * @param L
     * @return int
     */
    int GetQuest(lua_State* L)
    {
        uint32 questId = luaL_checkunsigned(L, 1);
        if (!questId)
            return 0;

        sEluna.Push(L, sObjectMgr.GetQuestTemplate(questId));
        return 1;
    }

    /**
     * @brief ReloadEluna() - Reloads eluna
     *
     * @param L
     * @return int
     */
    int ReloadEluna(lua_State* L)
    {
        StartEluna(true);
        return 0;
    }

    /**
     * @brief GetPlayerByGUID(guid) - Gets Player object by its guid
     *
     * @param L
     * @return int
     */
    int GetPlayerByGUID(lua_State* L)
    {
        uint64 guid = sEluna.CHECK_ULONG(L, 1);
        sEluna.Push(L, sObjectAccessor.FindPlayer((ObjectGuid)guid));
        return 1;
    }

    /**
     * @brief GetPlayerByName("name") - Gets player object by name
     *
     * @param L
     * @return int
     */
    int GetPlayerByName(lua_State* L)
    {
        const char* message = luaL_checkstring(L, 1);
        sEluna.Push(L, sObjectAccessor.FindPlayerByName(message));
        return 1;
    }

    /**
     * @brief GetGameTime() - Gets ingame time as seconds (server time?)
     *
     * @param L
     * @return int
     */
    int GetGameTime(lua_State* L)
    {
        sEluna.Push(L, sWorld.GetGameTime());
        return 1;
    }

    /**
     * @brief SendWorldMessage("msg") - Sends a broadcast message to everyone
     *
     * @param L
     * @return int
     */
    int SendWorldMessage(lua_State* L)
    {
        const char* message = luaL_checkstring(L, 1);
        sWorld.SendServerMessage(SERVER_MSG_CUSTOM, message);
        return 0;
    }

    /**
     * @brief GetPlayersInWorld([team, onlyGM]) - Gets a table with players in world. Team can be 0 for ally, 1 for horde and 2 for both.
     *
     * @param L
     * @return int
     */
    int GetPlayersInWorld(lua_State* L)
    {
        uint32 team = luaL_optunsigned(L, 1, TEAM_NEUTRAL);
        bool onlyGM = luaL_optbool(L, 2, false);

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        SessionMap const& sessions = sWorld.GetAllSessions();
        for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
        {
            if (Player* player = it->second->GetPlayer())
            {
                if (player->GetSession() && ((team >= TEAM_NEUTRAL || player->GetTeamId() == team) && (!onlyGM || player->isGameMaster())))
                {
                    ++i;
                    sEluna.Push(L, i);
                    sEluna.Push(L, player);
                    lua_settable(L, tbl);
                }
            }
        }

        lua_settop(L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * @brief GetPlayersInMap(mapid[, instanceid, team]) - Gets a table with players in the map. Instanceid optional (0 for normal map). Team can be 0 for ally, 1 for horde and 2 for both
     *
     * @param L
     * @return int
     */
    int GetPlayersInMap(lua_State* L)
    {
        uint32 mapID = luaL_checkunsigned(L, 1);
        uint32 instanceID = luaL_optunsigned(L, 2, 0);
        uint32 team = luaL_optunsigned(L, 3, TEAM_BOTH_ALLOWED);

        Map* map = sMapMgr.FindMap(mapID, instanceID);
        if (!map)
            return 0;

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        Map::PlayerList const& players = map->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            Player* player = itr->getSource();
            if (!player)
                continue;
            if (player->GetSession() && (team >= TEAM_BOTH_ALLOWED || player->GetTeam() == team))
            {
                ++i;
                sEluna.Push(L, i);
                sEluna.Push(L, player);
                lua_settable(L, tbl);
            }
        }

        lua_settop(L, tbl);
        return 1;
    }

    /**
     * @brief WorldDBQuery("sql") - Executes SQL to world database and returns the query Result or nil (instant)
     *
     * @param L
     * @return int
     */
    int WorldDBQuery(lua_State* L)
    {
        const char* query = luaL_checkstring(L, 1);
        if (!query)
            return 0;

        QueryResult* Result = WorldDatabase.Query(query);
        if (!Result)
            return 0;

        sEluna.Push(L, Result);
        return 1;
    }

    /**
     * @brief WorldDBExecute("sql") - Executes SQL to world database (not instant)
     *
     * @param L
     * @return int
     */
    int WorldDBExecute(lua_State* L)
    {
        const char* query = luaL_checkstring(L, 1);
        if (!query)
            return 0;

        WorldDatabase.Execute(query);
        return 0;
    }

    /**
     * @brief CharDBQuery("sql") - Executes SQL to characters database and returns the query Result or nil (instant)
     *
     * @param L
     * @return int
     */
    int CharDBQuery(lua_State* L)
    {
        const char* query = luaL_checkstring(L, 1);
        if (!query)
            return 0;

        QueryResult* Result = CharacterDatabase.Query(query);
        if (!Result)
            return 0;

        sEluna.Push(L, Result);
        return 1;
    }

    /**
     * @brief CharDBExecute("sql") - Executes SQL to characters database (not instant)
     *
     * @param L
     * @return int
     */
    int CharDBExecute(lua_State* L)
    {
        const char* query = luaL_checkstring(L, 1);
        if (!query)
            return 0;

        CharacterDatabase.Execute(query);
        return 0;
    }

    /**
     * @brief AuthDBQuery("sql") - Executes SQL to auth database and returns the query Result or nil (instant)
     *
     * @param L
     * @return int
     */
    int AuthDBQuery(lua_State* L)
    {
        const char* query = luaL_checkstring(L, 1);
        if (!query)
            return 0;

        QueryResult* Result = LoginDatabase.Query(query);
        if (!Result)
            return 0;

        sEluna.Push(L, Result);
        return 1;
    }

    /**
     * @brief AuthDBExecute("sql") - Executes SQL to auth database (not instant)
     *
     * @param L
     * @return int
     */
    int AuthDBExecute(lua_State* L)
    {
        const char* query = luaL_checkstring(L, 1);
        if (!query)
            return 0;

        LoginDatabase.Execute(query);
        return 0;
    }

    /**
     * @brief GetGuildByName("name") - Gets guild object
     *
     * @param L
     * @return int
     */
    int GetGuildByName(lua_State* L)
    {
        const char* name = luaL_checkstring(L, 1);
        sEluna.Push(L, sGuildMgr.GetGuildByName(name));
        return 1;
    }

    /**
     * @brief GetMapById()
     *
     * @param L
     * @return int
     */
    int GetMapById(lua_State* L)
    {
        uint32 mapid = luaL_checkunsigned(L, 1);
        if (!sMapStore.LookupEntry(mapid))
            return 0;

        sEluna.Push(L, sMapMgr.FindMap(mapid));
        return 1;
    }

    /**
     * @brief GetGuildByLeaderGUID(leaderGUID) - Gets guild object
     *
     * @param L
     * @return int
     */
    int GetGuildByLeaderGUID(lua_State* L)
    {
        Object* obj = sEluna.CHECK_OBJECT(L, 1);

        sEluna.Push(L, sGuildMgr.GetGuildByLeader((ObjectGuid)obj->GetObjectGuid()));
        return 1;
    }

    /**
     * @brief GetPlayerCount() - Gets server player count
     *
     * @param L
     * @return int
     */
    int GetPlayerCount(lua_State* L)
    {
        sEluna.Push(L, sWorld.GetActiveSessionCount());
        return 1;
    }

    // FindUnit(guid)
    /*int FindUnit(lua_State* L)
    {
        uint64 guid = sEluna.CHECK_ULONG(L, 1);
        sEluna.Push(L, sObjectAccessor.FindUnit(guid));
        return 1;
    }*/

    /**
     * @brief GetPlayerGUID(lowguid)
     *
     * @param L
     * @return int
     */
    int GetPlayerGUID(lua_State* L)
    {
        uint32 lowguid = luaL_checkunsigned(L, 1);
        sEluna.Push(L, ObjectGuid(HIGHGUID_PLAYER, lowguid));
        return 1;
    }

    /**
     * @brief GetItemGUID(lowguid)
     *
     * @param L
     * @return int
     */
    int GetItemGUID(lua_State* L)
    {
        uint32 lowguid = luaL_checkunsigned(L, 1);
        sEluna.Push(L, ObjectGuid(HIGHGUID_ITEM, lowguid));
        return 1;
    }

    /**
     * @brief GetObjectGUID(lowguid, entry)
     *
     * @param L
     * @return int
     */
    int GetObjectGUID(lua_State* L)
    {
        uint32 lowguid = luaL_checkunsigned(L, 1);
        uint32 entry = luaL_checkunsigned(L, 2);
        sEluna.Push(L, ObjectGuid(HIGHGUID_GAMEOBJECT, lowguid, entry));
        return 1;
    }

    /**
     * @brief GetUnitGUID(lowguid, entry)
     *
     * @param L
     * @return int
     */
    int GetUnitGUID(lua_State* L)
    {
        uint32 lowguid = luaL_checkunsigned(L, 1);
        uint32 entry = luaL_checkunsigned(L, 2);
        sEluna.Push(L, ObjectGuid(HIGHGUID_UNIT, lowguid, entry));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int CreateLuaEvent(lua_State* L)
    {
        luaL_checktype(L, 1, LUA_TFUNCTION);
        uint32 delay = luaL_checkunsigned(L, 2);
        uint32 repeats = luaL_checkunsigned(L, 3);

        lua_settop(L, 1);
        int functionRef = lua_ref(L, true);
        sEluna.Push(L, sEluna.EventMgr.AddEvent(&sEluna.EventMgr.GlobalEvents, functionRef, delay, repeats));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int RemoveEventById(lua_State* L)
    {
        int eventId = luaL_checkinteger(L, 1);
        bool all_Events = luaL_optbool(L, 1, false);

        if (all_Events)
            sEluna.EventMgr.RemoveEvent(eventId);
        else
            sEluna.EventMgr.RemoveEvent(&sEluna.EventMgr.GlobalEvents, eventId);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int RemoveEvents(lua_State* L)
    {
        bool all_Events = luaL_optbool(L, 1, false);

        if (all_Events)
            sEluna.EventMgr.RemoveEvents();
        else
            sEluna.EventMgr.RemoveEvents(&sEluna.EventMgr.GlobalEvents);
        return 0;
    }

    /**
     * @brief PerformIngameSpawn(spawntype, entry, mapid, instanceid, x, y, z, o[, save, DurOrResptime, phase])
     *
     * spawntype: 1 Creature, 2 Object. DurOrResptime is respawntime for gameobjects and despawntime for creatures if creature is not saved
     *
     * @param L
     * @return int
     */
    int PerformIngameSpawn(lua_State* L)
    {
        int spawntype = luaL_checkinteger(L, 1);
        uint32 entry = luaL_checkunsigned(L, 2);
        uint32 mapID = luaL_checkunsigned(L, 3);
        uint32 instanceID = luaL_checkunsigned(L, 4);
        float x = luaL_checknumber(L, 5);
        float y = luaL_checknumber(L, 6);
        float z = luaL_checknumber(L, 7);
        float o = luaL_checknumber(L, 8);
        bool save = luaL_optbool(L, 9, false);
        uint32 durorresptime = luaL_optunsigned(L, 10, 0);
        /*uint32 phase = luaL_optunsigned(L, 11, PHASEMASK_NORMAL);
        if (!phase)
            return 0;*/

        Map* map = sMapMgr.FindMap(mapID, instanceID);
        if (!map)
            return 0;

        if (spawntype == 1) // spawn creature
        {
            if (save)
            {
                CreatureInfo const* cinfo = ObjectMgr::GetCreatureTemplate(entry);
                if (!cinfo)
                    return 0;

                CreatureCreatePos pos(map, x, y, z, o/*, phase*/);
                Creature* pCreature = new Creature;
                // used guids from specially reserved range (can be 0 if no free values)
                uint32 lowguid = sObjectMgr.GenerateStaticCreatureLowGuid();
                if (!lowguid)
                    return 0;

                if (!pCreature->Create(lowguid, pos, cinfo))
                {
                    delete pCreature;
                    return 0;
                }

                pCreature->SaveToDB(map->GetId(), (1 << map->GetSpawnMode())/*, phase*/);

                uint32 db_guid = pCreature->GetGUIDLow();

                // To call _LoadGoods(); _LoadQuests(); CreateTrainerSpells();
                pCreature->LoadFromDB(db_guid, map);

                map->Add(pCreature);
                sObjectMgr.AddCreatureToGrid(db_guid, sObjectMgr.GetCreatureData(db_guid));
                if (durorresptime)
                    pCreature->ForcedDespawn(durorresptime);

                sEluna.Push(L, pCreature);
            }
            else
            {
                CreatureInfo const* cinfo = ObjectMgr::GetCreatureTemplate(entry);
                if (!cinfo)
                    return 0;

                TemporarySummon* pCreature = new TemporarySummon(ObjectGuid(uint64(0)));
                CreatureCreatePos pos(map, x, y, z, o/*, phase*/);

                if (!pCreature->Create(map->GenerateLocalLowGuid(cinfo->GetHighGuid()), pos, cinfo, TEAM_NONE))
                {
                    delete pCreature;
                    return NULL;
                }

                pCreature->SetRespawnCoord(pos);

                // Active state set before added to map
                pCreature->SetActiveObjectState(false);

                // Also initializes the AI and MMGen
                pCreature->Summon(durorresptime ? TEMPSUMMON_TIMED_OR_DEAD_DESPAWN : TEMPSUMMON_MANUAL_DESPAWN, durorresptime);

                // Creature Linking, Initial load is handled like respawn
                if (pCreature->IsLinkingEventTrigger())
                    map->GetCreatureLinkingHolder()->DoCreatureLinkingEvent(LINKING_EVENT_RESPAWN, pCreature);

                sEluna.Push(L, pCreature);
            }

            return 1;
        }

        if (spawntype == 2) // Spawn object
        {
            if (save)
            {
                const GameObjectInfo* gInfo = ObjectMgr::GetGameObjectInfo(entry);
                if (!gInfo)
                    return 0;

                // used guids from specially reserved range (can be 0 if no free values)
                uint32 db_lowGUID = sObjectMgr.GenerateStaticGameObjectLowGuid();
                if (!db_lowGUID)
                    return 0;

                GameObject* pGameObj = new GameObject;
                if (!pGameObj->Create(db_lowGUID, gInfo->id, map, /*phase,*/ x, y, z, o))
                {
                    delete pGameObj;
                    return 0;
                }

                if (durorresptime)
                    pGameObj->SetRespawnTime(durorresptime);

                // fill the gameobject data and save to the db
                pGameObj->SaveToDB(map->GetId(), (1 << map->GetSpawnMode())/*, phase*/);

                // this will generate a new guid if the object is in an instance
                if (!pGameObj->LoadFromDB(db_lowGUID, map))
                {
                    delete pGameObj;
                    return false;
                }

                // DEBUG_LOG(GetMangosString(LANG_GAMEOBJECT_CURRENT), gInfo->name, db_lowGUID, x, y, z, o);

                map->Add(pGameObj);

                sObjectMgr.AddGameobjectToGrid(db_lowGUID, sObjectMgr.GetGOData(db_lowGUID));

                sEluna.Push(L, pGameObj);
            }
            else
            {
                GameObject* pGameObj = new GameObject;

                if (!pGameObj->Create(map->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), entry, map, /*phase,*/ x, y, z, o))
                {
                    delete pGameObj;
                    return NULL;
                }

                pGameObj->SetRespawnTime(durorresptime/IN_MILLISECONDS);

                map->Add(pGameObj);

                sEluna.Push(L, pGameObj);
            }
            return 1;
        }

        return 0;
    }

    /**
     * @brief CreatePacket(opcode, size)
     *
     * @param L
     * @return int
     */
    int CreatePacket(lua_State* L)
    {
        uint16 opcode = luaL_checkunsigned(L, 1);
        size_t size = luaL_checkunsigned(L, 2);

        if (opcode >= NUM_MSG_TYPES)
            luaL_error(L, "Invalid opcode type (%d)", opcode);
        else
        {
            WorldPacket* _packet = new WorldPacket((Opcodes)opcode, size);
            sEluna.Push(L, _packet);
            return 1;
        }
        return 0;
    }

    /**
     * @brief AddVendorItem(entry, itemId, maxcount, incrtime, extendedcost[, persist(bool)])
     *
     * @param L
     * @return int
     */
    int AddVendorItem(lua_State* L)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 item = luaL_checkunsigned(L, 2);
        int maxcount = luaL_checkinteger(L, 3);
        uint32 incrtime = luaL_checkunsigned(L, 4);
        uint32 extendedcost = luaL_checkunsigned(L, 5);
        // bool persist = luaL_optbool(L, 6, true);
        if (!sObjectMgr.GetCreatureTemplate(entry))
        {
            luaL_error(L, "Couldn't find a creature with (ID: %d)!", entry);
            return 0;
        }

        if (!sObjectMgr.IsVendorItemValid(false, "npc_vendor", entry, item, maxcount, incrtime, extendedcost, 0))
            return 0;
        sObjectMgr.AddVendorItem(entry, item, maxcount, incrtime, extendedcost/*, persist*/); // MaNGOS does not support persist
        return 0;
    }

    /**
     * @brief VendorRemoveItem(entry, item[, persist(bool)])
     *
     * @param L
     * @return int
     */
    int VendorRemoveItem(lua_State* L)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 item = luaL_checkunsigned(L, 2);
        bool persist = luaL_optbool(L, 3, true);
        if (!sObjectMgr.GetCreatureTemplate(entry))
        {
            luaL_error(L, "Couldn't find a creature with (ID: %d)!", entry);
            return 0;
        }

        sObjectMgr.RemoveVendorItem(entry, item/*, persist*/); // MaNGOS does not support persist
        return 0;
    }

    /**
     * @brief VendorRemoveAllItems(entry, persist(bool))
     *
     * @param L
     * @return int
     */
    int VendorRemoveAllItems(lua_State* L)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        bool persist = luaL_optbool(L, 2, true);

        VendorItemData const* items = sObjectMgr.GetNpcVendorItemList(entry);
        if (!items || items->Empty())
            return 0;

        VendorItemList const itemlist = items->m_items;
        for (VendorItemList::const_iterator itr = itemlist.begin(); itr != itemlist.end(); ++itr)
            sObjectMgr.RemoveVendorItem(entry, (*itr)->item/*, persist*/); // MaNGOS does not support persist
        return 0;
    }

    /**
     * @brief Kick(player)
     *
     * @param L
     * @return int
     */
    int Kick(lua_State* L)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        if (!player)
            return 0;
        player->GetSession()->KickPlayer();
        return 0;
    }

    /**
     * @brief Ban(banMode(integer), nameOrIP(string), duration(string), reason(string), player(whoBanned))
     *
     * @param L
     * @return int
     */
    int Ban(lua_State* L)
    {
        int banMode = luaL_checkint(L, 1);
        std::string nameOrIP = luaL_checkstring(L, 2);
        uint32 duration = luaL_checkunsigned(L, 3);
        const char* reason = luaL_checkstring(L, 4);
        Player* whoBanned = sEluna.CHECK_PLAYER(L, 5);
        if (!whoBanned)
            return 0;

        switch (banMode)
        {
            case BAN_ACCOUNT:
                if (!AccountMgr::normalizeString(nameOrIP))
                    return 0;
                break;
            case BAN_CHARACTER:
                if (!normalizePlayerName(nameOrIP))
                    return 0;
                break;
            case BAN_IP:
                if (!IsIPAddress(nameOrIP.c_str()))
                    return 0;
                break;
            default:
                return 0;
        }

        switch (sWorld.BanAccount((BanMode)banMode, nameOrIP, duration, reason, whoBanned->GetSession() ? whoBanned->GetName() : ""))
        {
            case BAN_SUCCESS:
                if (duration > 0)
                    ChatHandler(whoBanned->GetSession()).PSendSysMessage(LANG_BAN_YOUBANNED, nameOrIP.c_str(), secsToTimeString(duration, true).c_str(), reason);
                else
                    ChatHandler(whoBanned->GetSession()).PSendSysMessage(LANG_BAN_YOUPERMBANNED, nameOrIP.c_str(), reason);
                break;
            case BAN_SYNTAX_ERROR:
                return 0;
            case BAN_NOTFOUND:
                return 0;
        }
        return 0;
    }

    /**
     * @brief SaveAllPlayers()
     *
     * @param L
     * @return int
     */
    int SaveAllPlayers(lua_State* L)
    {
        sObjectAccessor.SaveAllPlayers();
        return 0;
    }

    /**
     * @brief GetGUIDLow(guid)
     *
     * @param L
     * @return int
     */
    int GetGUIDLow(lua_State* L)
    {
        uint64 guid = sEluna.CHECK_ULONG(L, 1);

        sEluna.Push(L, ObjectGuid(guid).GetCounter());
        return 1;
    }

    /**
     * @brief SendMail(subject, text, receiverLowGUID[, sender, stationary, delay, itemEntry, itemAmount, itemEntry2, itemAmount2...])
     *
     * @param L
     * @return int
     */
    int SendMail(lua_State* L)
    {
        uint8 i = 0;
        std::string subject = luaL_checkstring(L, ++i);
        std::string text = luaL_checkstring(L, ++i);
        uint32 receiverGUIDLow = luaL_checkunsigned(L, ++i);
        Player* senderPlayer = sEluna.CHECK_PLAYER(L, ++i);
        uint32 stationary = luaL_optunsigned(L, ++i, MAIL_STATIONERY_DEFAULT);
        uint32 delay = luaL_optunsigned(L, ++i, 0);
        int32 argAmount = lua_gettop(L);

        MailDraft draft;

        // fill draft
        draft.SetSubjectAndBody(subject, text);

        uint8 addedItems = 0;
        while (addedItems <= MAX_MAIL_ITEMS && i+2 <= argAmount)
        {
            uint32 entry = luaL_checkunsigned(L, ++i);
            uint32 amount = luaL_checkunsigned(L, ++i);

            ItemPrototype const* item_proto = ObjectMgr::GetItemPrototype(entry);
            if (!item_proto)
            {
                luaL_error(L, "Item entry %d does not exist", entry);
                continue;
            }
            if (amount < 1 || (item_proto->MaxCount > 0 && amount > uint32(item_proto->MaxCount)))
            {
                luaL_error(L, "Item entry %d has invalid amount %d", entry, amount);
                continue;
            }
            if (Item* item = Item::CreateItem(entry, amount, senderPlayer))
            {
                item->SaveToDB();
                draft.AddItem(item);
                ++addedItems;
            }
        }

        // from console show nonexistent sender
        MailSender sender(MAIL_NORMAL, senderPlayer ? senderPlayer->GetObjectGuid().GetCounter() : 0, MailStationery(stationary));

        draft.SendMailTo(MailReceiver(ObjectGuid(HIGHGUID_PLAYER, receiverGUIDLow)), sender);
        return 0;
    }

    /**
     * @brief bit_and(a, b)
     *
     * @param L
     * @return int
     */
    int bit_and(lua_State* L)
    {
        uint32 a = luaL_checkunsigned(L, 1);
        uint32 b = luaL_checkunsigned(L, 2);
        sEluna.Push(L, a & b);
        return 1;
    }

    /**
     * @brief bit_or(a, b)
     *
     * @param L
     * @return int
     */
    int bit_or(lua_State* L)
    {
        uint32 a = luaL_checkunsigned(L, 1);
        uint32 b = luaL_checkunsigned(L, 2);
        sEluna.Push(L, a | b);
        return 1;
    }

    /**
     * @brief bit_lshift(a, b)
     *
     * @param L
     * @return int
     */
    int bit_lshift(lua_State* L)
    {
        uint32 a = luaL_checkunsigned(L, 1);
        uint32 b = luaL_checkunsigned(L, 2);
        sEluna.Push(L, a << b);
        return 1;
    }

    /**
     * @brief bit_rshift(a, b)
     *
     * @param L
     * @return int
     */
    int bit_rshift(lua_State* L)
    {
        uint32 a = luaL_checkunsigned(L, 1);
        uint32 b = luaL_checkunsigned(L, 2);
        sEluna.Push(L, a >> b);
        return 1;
    }

    /**
     * @brief bit_xor(a, b)
     *
     * @param L
     * @return int
     */
    int bit_xor(lua_State* L)
    {
        uint32 a = luaL_checkunsigned(L, 1);
        uint32 b = luaL_checkunsigned(L, 2);
        sEluna.Push(L, a ^ b);
        return 1;
    }

    /**
     * @brief bit_not(a)
     *
     * @param L
     * @return int
     */
    int bit_not(lua_State* L)
    {
        uint32 a = luaL_checkunsigned(L, 1);
        sEluna.Push(L, ~ a);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int GetGUIDType(lua_State* L)
    {
        uint64 guid = sEluna.CHECK_ULONG(L, 1);
        sEluna.Push(L, ObjectGuid(guid).GetHigh());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int GetGUIDEntry(lua_State* L)
    {
        uint64 guid = sEluna.CHECK_ULONG(L, 1);
        sEluna.Push(L, ObjectGuid(guid).GetEntry());
        return 1;
    }

    /**
     * @brief AddTaxiPath(pathTable, mountA, mountH[, price, pathId])
     *
     * @param L
     * @return int
     */
    int AddTaxiPath(lua_State* L)
    {
        luaL_checktype(L, 1, LUA_TTABLE);
        uint32 mountA = luaL_checkunsigned(L, 2);
        uint32 mountH = luaL_checkunsigned(L, 3);
        uint32 price = luaL_optunsigned(L, 4, 0);
        uint32 pathId = luaL_optunsigned(L, 5, 0);
        lua_settop(L, 1);

        std::list<TaxiPathNodeEntry> nodes;

        int start = lua_gettop(L);
        int end = start;

        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            luaL_checktype(L, -1, LUA_TTABLE);
            lua_pushnil(L);
            while (lua_next(L, -2) != 0)
            {
                lua_insert(L, end++);
            }
            if (start == end)
                continue;
            if (end - start < 4) // no mandatory args, dont add
            {
                while (end != start)
                    lua_remove(L, --end);
                continue;
            }

            while (end - start < 8) // fill optional args with 0
            {
                lua_pushunsigned(L, 0);
                lua_insert(L, end++);
            }
            TaxiPathNodeEntry* entry = new TaxiPathNodeEntry();
            // mandatory
            entry->mapid = luaL_checkunsigned(L, start);
            entry->x = luaL_checknumber(L, start + 1);
            entry->y = luaL_checknumber(L, start + 2);
            entry->z = luaL_checknumber(L, start + 3);
            // optional
            entry->actionFlag = luaL_checkunsigned(L, start + 4);
            entry->delay = luaL_checkunsigned(L, start + 5);
            entry->arrivalEventID = luaL_checkunsigned(L, start + 6);
            entry->departureEventID = luaL_checkunsigned(L, start + 7);

            nodes.push_back(*entry);

            while (end != start) // remove args
                lua_remove(L, --end);

            lua_pop(L, 1);
        }

        sEluna.Push(L, LuaTaxiMgr::AddPath(nodes, mountA, mountH, price, pathId));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int GetItemLink(lua_State* L)
    {
        /*
        LOCALE_enUS = 0,
        LOCALE_koKR = 1,
        LOCALE_frFR = 2,
        LOCALE_deDE = 3,
        LOCALE_zhCN = 4,
        LOCALE_zhTW = 5,
        LOCALE_esES = 6,
        LOCALE_esMX = 7,
        LOCALE_ruRU = 8
        */
        uint32 entry = luaL_checkunsigned(L, 1);
        int loc_idx = luaL_optint(L, 2, DEFAULT_LOCALE);
        if (loc_idx < 0 || loc_idx >= MAX_LOCALE)
        {
            luaL_error(L, "Invalid locale index (%d)", loc_idx);
            return 0;
        }

        const ItemPrototype* temp = sObjectMgr.GetItemPrototype(entry);
        if (!temp)
        {
            luaL_error(L, "Invalid item entry (%d)", entry);
            return 0;
        }

        std::string name = temp->Name1;
        if (ItemLocale const* il = sObjectMgr.GetItemLocale(entry))
            ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

        std::ostringstream oss;
        oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
            "|Hitem:" << entry << ":0:0:0:0:0:0:0:0:0|h[" << name << "]|h|r";

        sEluna.Push(L, oss.str());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int AddCorpse(lua_State* L)
    {
        Corpse* corpse = sEluna.CHECK_CORPSE(L, 1);
        if (!corpse)
            return 0;

        sObjectAccessor.AddCorpse(corpse);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int RemoveCorpse(lua_State* L)
    {
        Corpse* corpse = sEluna.CHECK_CORPSE(L, 1);
        sObjectAccessor.RemoveCorpse(corpse);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int ConvertCorpseForPlayer(lua_State* L)
    {
        uint64 guid = sEluna.CHECK_ULONG(L, 1);
        bool insignia = luaL_optbool(L, 2, false);

        sEluna.Push(L, sObjectAccessor.ConvertCorpseForPlayer((ObjectGuid)guid, insignia));
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int RemoveOldCorpses(lua_State* L)
    {
        sObjectAccessor.RemoveOldCorpses();
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int FindWeather(lua_State* L)
    {
        uint32 zoneId = luaL_checkunsigned(L, 1);
        Weather* weather = sWorld.FindWeather(zoneId);
        sEluna.Push(L, weather);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int AddWeather(lua_State* L)
    {
        uint32 zoneId = luaL_checkunsigned(L, 1);
        Weather* weather = sWorld.AddWeather(zoneId);
        sEluna.Push(L, weather);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int RemoveWeather(lua_State* L)
    {
        uint32 zoneId = luaL_checkunsigned(L, 1);

        sWorld.RemoveWeather(zoneId);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @return int
     */
    int SendFineWeatherToPlayer(lua_State* L)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        if (!player)
            return 0;

        Weather::SendFineWeatherUpdateToPlayer(player);
        return 0;
    }
}
#endif
