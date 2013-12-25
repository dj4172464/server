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

#ifndef MAPMETHODS_H
#define MAPMETHODS_H

namespace LuaMap
{
    /**
     * @brief GetName()
     *
     * @param L
     * @param map
     * @return int
     */
    int GetName(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->GetMapName());
        return 1;
    }

    /**
     * @brief GetHeight(x, y[, phase])
     *
     * @param L
     * @param map
     * @return int
     */
    int GetHeight(lua_State* L, Map* map)
    {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        uint32 phasemask = luaL_optunsigned(L, 3, 1);

        float z = map->GetHeight(/*phasemask,*/x, y, MAX_HEIGHT);
        if (z == INVALID_HEIGHT)
            return 0;
        sEluna.Push(L, z);
        return 1;
    }

    /**
     * @brief GetDifficulty()
     *
     * @param L
     * @param map
     * @return int
     */
    int GetDifficulty(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->GetDifficulty());
        return 1;
    }

    /**
     * @brief GetInstanceId()
     *
     * @param L
     * @param map
     * @return int
     */
    int GetInstanceId(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->GetInstanceId());
        return 1;
    }

    /**
     * @brief GetPlayerCount()
     *
     * @param L
     * @param map
     * @return int
     */
    int GetPlayerCount(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->GetPlayersCountExceptGMs());
        return 1;
    }

    /**
     * @brief GetMapId()
     *
     * @param L
     * @param map
     * @return int
     */
    int GetMapId(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->GetId());
        return 1;
    }

    /**
     * @brief GetAreaId(x, y, z)
     *
     * @param L
     * @param map
     * @return int
     */
    int GetAreaId(lua_State* L, Map* map)
    {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 3);

        sEluna.Push(L, map->GetTerrain()->GetAreaId(x, y, z));
        return 1;
    }

    /**
     * @brief IsArena()
     *
     * @param L
     * @param map
     * @return int
     */
    int IsArena(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->IsBattleArena());
        return 1;
    }

    /**
     * @brief IsBattleground()
     *
     * @param L
     * @param map
     * @return int
     */
    int IsBattleground(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->IsBattleGround());
        return 1;
    }

    /**
     * @brief IsDungeon()
     *
     * @param L
     * @param map
     * @return int
     */
    int IsDungeon(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->IsDungeon());
        return 1;
    }

    /**
     * @brief IsEmpty()
     *
     * @param L
     * @param map
     * @return int
     */
    int IsEmpty(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->isEmpty());
        return 1;
    }

    /**
     * @brief IsHeroic()
     *
     * @param L
     * @param map
     * @return int
     */
    int IsHeroic(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->IsHeroic());
        return 1;
    }

    /**
     * @brief IsRaid()
     *
     * @param L
     * @param map
     * @return int
     */
    int IsRaid(lua_State* L, Map* map)
    {
        sEluna.Push(L, map->IsRaid());
        return 1;
    }
};
#endif
