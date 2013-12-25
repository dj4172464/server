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

#ifndef CORPSEMETHODS_H
#define CORPSEMETHODS_H

namespace LuaCorpse
{
    /**
     * @brief GetOwnerGUID
     *
     * @param L
     * @param corpse
     * @return int
     */
    int GetOwnerGUID(lua_State* L, Corpse* corpse)
    {
        sEluna.Push(L, corpse->GetOwnerGuid());
        return 1;
    }

    /**
     * @brief GetGhostTime
     *
     * @param L
     * @param corpse
     * @return int
     */
    int GetGhostTime(lua_State* L, Corpse* corpse)
    {
        sEluna.Push(L, corpse->GetGhostTime());
        return 1;
    }

    /**
     * @brief GetType
     *
     * @param L
     * @param corpse
     * @return int
     */
    int GetType(lua_State* L, Corpse* corpse)
    {
        sEluna.Push(L, corpse->GetType());
        return 1;
    }

    /**
     * @brief ResetGhostTime
     *
     * @param L
     * @param corpse
     * @return int
     */
    int ResetGhostTime(lua_State* L, Corpse* corpse)
    {
        corpse->ResetGhostTime();
        return 0;
    }

    /**
     * @brief SaveToDB
     *
     * @param L
     * @param corpse
     * @return int
     */
    int SaveToDB(lua_State* L, Corpse* corpse)
    {
        corpse->SaveToDB();
        return 0;
    }

    /**
     * @brief DeleteBonesFromWorld
     *
     * @param L
     * @param corpse
     * @return int
     */
    int DeleteBonesFromWorld(lua_State* L, Corpse* corpse)
    {
        corpse->DeleteBonesFromWorld();
        return 0;
    }
};
#endif
