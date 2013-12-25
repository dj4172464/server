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

#ifndef WORLDPACKETMETHODS_H
#define WORLDPACKETMETHODS_H

namespace LuaPacket
{
    /**
     * @brief GetOpcode()
     *
     * @param L
     * @param packet
     * @return int
     */
    int GetOpcode(lua_State* L, WorldPacket* packet)
    {
        sEluna.Push(L, packet->GetOpcode());
        return 1;
    }

    /**
     * @brief GetSize()
     *
     * @param L
     * @param packet
     * @return int
     */
    int GetSize(lua_State* L, WorldPacket* packet)
    {
        sEluna.Push(L, packet->size());
        return 1;
    }

    /**
     * @brief SetOpcode(opcode)
     *
     * @param L
     * @param packet
     * @return int
     */
    int SetOpcode(lua_State* L, WorldPacket* packet)
    {
        uint16 opcode = luaL_checkunsigned(L, 1);
        if (opcode >= NUM_MSG_TYPES)
            luaL_error(L, "Invalid opcode type (%d)", opcode);
        else
            packet->SetOpcode((Opcodes)opcode);
        return 0;
    }

    /**
     * @brief ReadByte()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadByte(lua_State* L, WorldPacket* packet)
    {
        int8 byte;
        (*packet) >> byte;
        sEluna.Push(L, byte);
        return 1;
    }

    /**
     * @brief ReadUByte()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadUByte(lua_State* L, WorldPacket* packet)
    {
        uint8 byte;
        (*packet) >> byte;
        sEluna.Push(L, byte);
        return 1;
    }

    /**
     * @brief ReadShort()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadShort(lua_State* L, WorldPacket* packet)
    {
        int16 _short;
        (*packet) >> _short;
        sEluna.Push(L, _short);
        return 1;
    }

    /**
     * @brief ReadUShort()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadUShort(lua_State* L, WorldPacket* packet)
    {
        uint16 _ushort;
        (*packet) >> _ushort;
        sEluna.Push(L, _ushort);
        return 1;
    }

    /**
     * @brief ReadLong()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadLong(lua_State* L, WorldPacket* packet)
    {
        int32 _long;
        (*packet) >> _long;
        sEluna.Push(L, _long);
        return 1;
    }

    /**
     * @brief ReadULong()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadULong(lua_State* L, WorldPacket* packet)
    {
        uint32 _ulong;
        (*packet) >> _ulong;
        sEluna.Push(L, _ulong);
        return 1;
    }

    /**
     * @brief ReadFloat()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadFloat(lua_State* L, WorldPacket* packet)
    {
        float _val;
        (*packet) >> _val;
        sEluna.Push(L, _val);
        return 1;
    }

    /**
     * @brief ReadDouble()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadDouble(lua_State* L, WorldPacket* packet)
    {
        double _val;
        (*packet) >> _val;
        sEluna.Push(L, _val);
        return 1;
    }

    /**
     * @brief ReadGUID()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadGUID(lua_State* L, WorldPacket* packet)
    {
        uint64 guid;
        (*packet) >> guid;
        sEluna.Push(L, guid);
        return 1;
    }

    /**
     * @brief ReadString()
     *
     * @param L
     * @param packet
     * @return int
     */
    int ReadString(lua_State* L, WorldPacket* packet)
    {
        std::string _val;
        (*packet) >> _val;
        sEluna.Push(L, _val);
        return 1;
    }

    /**
     * @brief WriteGUID(guid)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteGUID(lua_State* L, WorldPacket* packet)
    {
        uint64 guid = sEluna.CHECK_ULONG(L, 1);
        (*packet) << guid;
        return 0;
    }

    /**
     * @brief WriteString(string)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteString(lua_State* L, WorldPacket* packet)
    {
        std::string _val = std::string(luaL_checkstring(L, 1));
        (*packet) << _val;
        return 0;
    }

    /**
     * @brief WriteBye(byte)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteByte(lua_State* L, WorldPacket* packet)
    {
        int8 byte = luaL_checkinteger(L, 1);
        (*packet) << byte;
        return 0;
    }

    /**
     * @brief WriteUByte(byte)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteUByte(lua_State* L, WorldPacket* packet)
    {
        uint8 byte = luaL_checkunsigned(L, 1);
        (*packet) << byte;
        return 0;
    }

    /**
     * @brief WriteUShort(short)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteUShort(lua_State* L, WorldPacket* packet)
    {
        uint16 _ushort = luaL_checkunsigned(L, 1);
        (*packet) << _ushort;
        return 0;
    }

    /**
     * @brief WriteShort(short)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteShort(lua_State* L, WorldPacket* packet)
    {
        int16 _short = luaL_checkinteger(L, 1);
        (*packet) << _short;
        return 0;
    }

    /**
     * @brief WriteLong(long)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteLong(lua_State* L, WorldPacket* packet)
    {
        int32 _long = luaL_checkinteger(L, 1);
        (*packet) << _long;
        return 0;
    }

    /**
     * @brief WriteULong(long)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteULong(lua_State* L, WorldPacket* packet)
    {
        uint32 _ulong = luaL_checkunsigned(L, 1);
        (*packet) << _ulong;
        return 0;
    }

    /**
     * @brief WriteFloat(float)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteFloat(lua_State* L, WorldPacket* packet)
    {
        float _val = luaL_checknumber(L, 1);
        (*packet) << _val;
        return 0;
    }

    /**
     * @brief WriteDouble(double)
     *
     * @param L
     * @param packet
     * @return int
     */
    int WriteDouble(lua_State* L, WorldPacket* packet)
    {
        double _val = luaL_checknumber(L, 1);
        (*packet) << _val;
        return 0;
    }
};

#endif
