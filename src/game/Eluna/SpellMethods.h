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

#ifndef SPELLMETHODS_H
#define SPELLMETHODS_H

namespace LuaSpell
{
    int GetCaster(lua_State* L, Spell* spell)
    {
        sEluna.Push(L, spell->GetCaster());
        return 1;
    }

    int GetCastTime(lua_State* L, Spell* spell)
    {
        sEluna.Push(L, spell->GetCastTime());
        return 1;
    }

    int GetId(lua_State* L, Spell* spell)
    {
        sEluna.Push(L, spell->m_spellInfo->Id);
        return 1;
    }

    int GetPowerCost(lua_State* L, Spell* spell)
    {
        sEluna.Push(L, spell->GetPowerCost());
        return 1;
    }

    int GetDuration(lua_State* L, Spell* spell)
    {
        sEluna.Push(L, GetSpellDuration(spell->m_spellInfo));
        return 1;
    }

    int Cast(lua_State* L, Spell* spell)
    {
        bool skipCheck = lua_toboolean(L, 1);
        spell->cast(skipCheck);
        return 0;
    }

    int IsAutoRepeat(lua_State* L, Spell* spell)
    {
        sEluna.Push(L, spell->IsAutoRepeat());
        return 1;
    }

    int SetAutoRepeat(lua_State* L, Spell* spell)
    {
        bool repeat = luaL_checkbool(L, 1);
        spell->SetAutoRepeat(repeat);
        return 0;
    }

    int cancel(lua_State* L, Spell* spell)
    {
        spell->cancel();
        return 0;
    }

    // Finish()
    int Finish(lua_State* L, Spell* spell)
    {
        spell->finish();
        return 0;
    }

    int GetTargetDest(lua_State* L, Spell* spell)
    {
        if (!(spell->m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION))
            return 0;
        float x, y, z;
        spell->m_targets.getDestination(x, y, z);
        sEluna.Push(L, x);
        sEluna.Push(L, y);
        sEluna.Push(L, z);
        return 3;
    }
};
#endif
