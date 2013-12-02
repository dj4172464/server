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

class LuaCorpse
{
        /*
        public:
            // GetOwnerGUID() [CORPSE_FIELD_OWNER]
            static int GetOwnerGUID(lua_State* L, Corpse* corpse)
            {
                if (!corpse)
                    return 0;
                sEluna->PushULong(L, corpse->GetOwnerGUID());
                return 1;
            }

            // GetGhostTime()
            static int GetGhostTime(lua_State* L, Corpse* corpse)
            {
                if (!corpse)
                    return 0;
                sEluna->PushUnsigned(L, corpse->GetGhostTime());
                return 1;
            }

            // GetType()
            static int GetType(lua_State* L, Corpse* corpse)
            {
                if (!corpse)
                    return 0;
                sEluna->PushUnsigned(L, corpse->GetType());
                return 1;
            }

            // Create(map)
            static int Create(lua_State* L, Corpse* corpse)
            {
                Player* player = sEluna->CHECK_PLAYER(L, 1);
                if (!player || !corpse)
                    return 0;
                if (corpse->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_CORPSE), player))
                    return 0;
                return 0;
            }

            // ResetGhostTime()
            static int ResetGhostTime(lua_State* L, Corpse* corpse)
            {
                if (!corpse)
                    return 0;
                corpse->ResetGhostTime();
                return 0;
            }

            // SaveToDB()
            static int SaveToDB(lua_State* L, Corpse* corpse)
            {
                if (!corpse)
                    return 0;
                corpse->SaveToDB();
                return 0;
            }

            // DeleteBonesFromWorld()
            static int DeleteBonesFromWorld(lua_State* L, Corpse* corpse)
            {
                if (!corpse)
                    return 0;
                corpse->DeleteBonesFromWorld();
                return 0;
            }
        */
};

#endif
