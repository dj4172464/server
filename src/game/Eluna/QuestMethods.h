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

#ifndef QUESTMETHODS_H
#define QUESTMETHODS_H

namespace LuaQuest
{
    int GetId(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetQuestId());
        return 1;
    }

    int GetLevel(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetQuestLevel());
        return 1;
    }

    int GetMaxLevel(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetMaxLevel());
        return 1;
    }

    int GetMinLevel(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetMinLevel());
        return 1;
    }

    int GetNextQuestId(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetNextQuestId());
        return 1;
    }

    int GetPrevQuestId(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetPrevQuestId());
        return 1;
    }

    int GetNextQuestInChain(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetNextQuestInChain());
        return 1;
    }

    int GetFlags(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetQuestFlags());
        return 1;
    }

    int GetType(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->GetType());
        return 1;
    }

    int HasFlag(lua_State* L, Quest* quest)
    {
        uint32 flag = luaL_checkunsigned(L, 1);
        sEluna.Push(L, quest->HasQuestFlag((QuestFlags)flag));
        return 1;
    }

    int IsDaily(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->IsDaily());
        return 1;
    }

    int IsRepeatable(lua_State* L, Quest* quest)
    {
        sEluna.Push(L, quest->IsRepeatable());
        return 1;
    }

    int SetFlag(lua_State* L, Quest* quest)
    {
        uint32 flag = luaL_checkunsigned(L, 1);
        quest->SetSpecialFlag((QuestSpecialFlags)flag);
        return 0;
    }
};
#endif
