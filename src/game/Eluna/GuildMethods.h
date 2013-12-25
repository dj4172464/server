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

#ifndef GUILDMETHODS_H
#define GUILDMETHODS_H

namespace LuaGuild
{
    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetMembers(lua_State* L, Guild* guild)
    {
        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        SessionMap const& sessions = sWorld.GetAllSessions();
        for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
        {
            if (Player* player = it->second->GetPlayer())
            {
                if (player->GetSession() && (player->GetGuildId() == guild->GetId()))
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
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetMemberCount(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, guild->GetMemberSize());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetLeader(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, sObjectMgr.GetPlayer(guild->GetLeaderGuid()));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int SetLeader(lua_State* L, Guild* guild)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        if (!player)
            return 0;

        guild->SetLeader(player->GetObjectGuid());
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetLeaderGUID(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, guild->GetLeaderGuid());
        return 1;
    }

    /**
     * @brief SendPacketToGuild(packet)
     *
     * @param L
     * @param guild
     * @return int
     */
    int SendPacket(lua_State* L, Guild* guild)
    {
        WorldPacket* data = sEluna.CHECK_PACKET(L, 1);

        if (data)
            guild->BroadcastPacket(data);
        return 0;
    }

    /**
     * @brief SendPacketToRankedInGuild(packet, rankId)
     *
     * @param L
     * @param guild
     * @return int
     */
    int SendPacketToRanked(lua_State* L, Guild* guild)
    {
        WorldPacket* data = sEluna.CHECK_PACKET(L, 1);
        uint8 ranked = luaL_checkunsigned(L, 2);

        if (data)
            guild->BroadcastPacketToRank(data, ranked);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int Disband(lua_State* L, Guild* guild)
    {
        guild->Disband();
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetId(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, guild->GetId());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetName(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, guild->GetName());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetMOTD(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, guild->GetMOTD());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetInfo(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, guild->GetGINFO());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int AddMember(lua_State* L, Guild* guild)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        uint8 rankId = luaL_optint(L, 2, GUILD_RANK_NONE);

        if (player)
            guild->AddMember(player->GetObjectGuid(), rankId);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int DeleteMember(lua_State* L, Guild* guild)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        bool isDisbanding = luaL_optbool(L, 2, false);

        if (player)
            guild->DelMember(player->GetObjectGuid(), isDisbanding);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int ChangeMemberRank(lua_State* L, Guild* guild)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        uint8 newRank = luaL_checkunsigned(L, 2);

        if (player)
            guild->ChangeMemberRank(player->GetObjectGuid(), newRank);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int SetBankTabText(lua_State* L, Guild* guild)
    {
        uint8 tabId = luaL_checkunsigned(L, 1);
        const char* text = luaL_checkstring(L, 2);
        guild->SetGuildBankTabText(tabId, text);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int GetBankMoney(lua_State* L, Guild* guild)
    {
        sEluna.Push(L, guild->GetGuildBankMoney());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int WithdrawBankMoney(lua_State* L, Guild* guild)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        uint32 money = luaL_checknumber(L, 2);

        if (!player || (guild->GetGuildBankMoney() - money) < 0)
            return 0;

        player->SetMoney(player->GetMoney() + money);
        guild->SetBankMoney(guild->GetGuildBankMoney() - money);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param guild
     * @return int
     */
    int DepositBankMoney(lua_State* L, Guild* guild)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        uint32 money = luaL_checknumber(L, 2);

        if (!player || (player->GetMoney() - money) < 0)
            return 0;

        player->SetMoney(player->GetMoney() - money);
        guild->SetBankMoney(guild->GetGuildBankMoney() + money);
        return 0;
    }
};
#endif
