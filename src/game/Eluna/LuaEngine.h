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

#ifndef __ELUNA__H
#define __ELUNA__H

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "LuaIncludes.h"

/**
 * @brief
 *
 */
typedef std::set<std::string> LoadedScripts;

/**
 * @brief
 *
 * @return const char
 */
template<typename T> const char* GetTName();

template<class T>
/**
 * @brief
 *
 */
struct ElunaRegister
{
    const char* name; /**< TODO */
    /**
     * @brief
     *
     * @param
     * @param
     * @return int
     */
    int(*mfunc)(lua_State*, T*);
};

template<typename T>
/**
 * @brief
 *
 * @param L
 * @param methodTable
 */
void SetMethods(lua_State* L, ElunaRegister<T>* methodTable)
{
    if (!methodTable)
        return;
    if (!lua_istable(L, 1))
        return;
    lua_pushstring(L, "GetObjectType");
    lua_pushcclosure(L, ElunaTemplate<T>::type, 0);
    lua_settable(L, 1);
    for (; methodTable->name; ++methodTable)
    {
        lua_pushstring(L, methodTable->name);
        lua_pushlightuserdata(L, (void*)methodTable);
        lua_pushcclosure(L, ElunaTemplate<T>::thunk, 1);
        lua_settable(L, 1);
    }
}

template<typename T>
/**
 * @brief
 *
 */
class ElunaTemplate
{
    public:
        /**
         * @brief
         *
         * @param L
         * @return int
         */
        static int type(lua_State* L)
        {
            lua_pushstring(L, GetTName<T>());
            return 1;
        }

        /**
         * @brief
         *
         * @param L
         */
        static void Register(lua_State* L)
        {
            lua_settop(L, 0); // clean stack

            lua_newtable(L);
            int methods = lua_gettop(L);

            luaL_newmetatable(L, GetTName<T>());
            int metatable = lua_gettop(L);

            // store method table in globals so that
            // scripts can add functions in Lua
            lua_pushvalue(L, methods);
            lua_setglobal(L, GetTName<T>());

            // hide metatable
            lua_pushvalue(L, methods);
            lua_setfield(L, metatable, "__metatable");

            lua_pushvalue(L, methods);
            lua_setfield(L, metatable, "__index");

            lua_pushcfunction(L, tostringT);
            lua_setfield(L, metatable, "__tostring");

            lua_pushcfunction(L, gcT);
            lua_setfield(L, metatable, "__gc");

            lua_newtable(L);
            lua_setmetatable(L, methods);
        }

        /**
         * @brief
         *
         * @param L
         * @param obj
         * @param gc
         * @return int
         */
        static int push(lua_State* L, T const* obj, bool gc = false)
        {
            if (!obj)
            {
                lua_pushnil(L);
                return lua_gettop(L);
            }
            luaL_getmetatable(L, GetTName<T>());
            if (lua_isnil(L, -1))
                luaL_error(L, "%s missing metatable", GetTName<T>());
            int idxMt = lua_gettop(L);
            T const** ptrHold = (T const**)lua_newuserdata(L, sizeof(T**));
            int ud = lua_gettop(L);
            if (ptrHold)
            {
                *ptrHold = obj;
                lua_pushvalue(L, idxMt);
                lua_setmetatable(L, -2);
                char name[32];
                tostring(name, obj);
                lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
                if (lua_isnil(L, -1))
                {
                    luaL_newmetatable(L, "DO NOT TRASH");
                    lua_pop(L, 1);
                }
                lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
                if (gc == false)
                {
                    lua_pushboolean(L, 1);
                    lua_setfield(L, -2, name);
                }
                lua_pop(L, 1);
            }
            lua_settop(L, ud);
            lua_replace(L, idxMt);
            lua_settop(L, idxMt);
            return idxMt;
        }

        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return T
         */
        static T* check(lua_State* L, int narg)
        {
            T** ptrHold = static_cast<T**>(lua_touserdata(L, narg));
            if (!ptrHold)
                return NULL;
            return *ptrHold;
        }

        /**
         * @brief
         *
         * @param L
         * @return int
         */
        static int thunk(lua_State* L)
        {
            T* obj = check(L, 1); // get self
            lua_remove(L, 1); // remove self
            ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
            if (!obj)
                return 0;
            return l->mfunc(L, obj);
        }

        /**
         * @brief
         *
         * @param L
         * @return int
         */
        static int gcT(lua_State* L)
        {
            T* obj = check(L, 1);
            if (!obj)
                return 0;
            lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
            if (lua_istable(L, -1))
            {
                char name[32];
                tostring(name, obj);
                lua_getfield(L, -1, std::string(name).c_str());
                if (lua_isnil(L, -1))
                {
                    delete obj;
                    obj = NULL;
                }
            }
            return 1;
        }

        /**
         * @brief
         *
         * @param L
         * @return int
         */
        static int tostringT(lua_State* L)
        {
            char buff[32];
            T** ptrHold = (T**)lua_touserdata(L, 1);
            T* obj = *ptrHold;
            sprintf(buff, "%p", obj);
            lua_pushfstring(L, "%s (%s)", GetTName<T>(), buff);
            return 1;
        }

        /**
         * @brief
         *
         * @param buff
         * @param obj
         */
        inline static void tostring(char* buff, void const* obj)
        {
            sprintf(buff, "%p", obj);
        }

        /**
         * @brief
         *
         * @param L
         * @return int
         */
        static int index(lua_State* L)
        {
            lua_getglobal(L, GetTName<T>());
            const char* key = lua_tostring(L, 2);
            if (lua_istable(L, - 1))
            {
                lua_pushvalue(L, 2);
                lua_rawget(L, -2);
                if (lua_isnil(L, -1))
                {
                    lua_getmetatable(L, -2);
                    if (lua_istable(L, -1))
                    {
                        lua_getfield(L, -1, "__index");
                        if (lua_isfunction(L, -1))
                        {
                            lua_pushvalue(L, 1);
                            lua_pushvalue(L, 2);
                            lua_pcall(L, 2, 1, 0);
                        }
                        else if (lua_istable(L, -1))
                            lua_getfield(L, -1, key);
                        else
                            lua_pushnil(L);
                    }
                    else
                        lua_pushnil(L);
                }
                else if (lua_istable(L, -1))
                {
                    lua_pushvalue(L, 2);
                    lua_rawget(L, -2);
                }
            }
            else
                lua_pushnil(L);
            lua_insert(L, 1);
            lua_settop(L, 1);
            return 1;
        }
};

/**
 * @brief
 *
 */
struct EventMgr
{
    struct LuaEvent;

    /**
     * @brief
     *
     */
    typedef std::set<LuaEvent*> EventSet;
    /**
     * @brief
     *
     */
    typedef std::map<EventProcessor*, EventSet> EventMap;
    /**
     * @brief
     *
     */
    typedef UNORDERED_MAP<uint64, EventProcessor> ProcessorMap;

    EventMap LuaEvents; // LuaEvents[events] = {LuaEvents} /**< TODO */
    ProcessorMap Processors; // Processors[guid] = processor /**< TODO */
    EventProcessor GlobalEvents; /**< TODO */

    /**
     * @brief
     *
     */
    struct LuaEvent : public BasicEvent
    {
        /**
         * @brief
         *
         * @param _events
         * @param _funcRef
         * @param _delay
         * @param _calls
         * @param _obj
         */
        LuaEvent(EventProcessor* _events, int _funcRef, uint32 _delay, uint32 _calls, Object* _obj);

        /**
         * @brief
         *
         */
        ~LuaEvent();

        /**
         * @brief Should never execute on dead events
         *
         * @param time
         * @param diff
         * @return bool
         */
        bool Execute(uint64 time, uint32 diff);

        bool hasObject; // Dont call event if object no longer exists /**< TODO */
        Object* obj;    // Object to push /**< TODO */
        int funcRef;    // Lua function reference ID, also used as event ID /**< TODO */
        uint32 delay;   // Delay between event calls /**< TODO */
        uint32 calls;   // Amount of calls to make, 0 for infinite /**< TODO */
        EventProcessor* events; // Pointer to events (holds the timed event) /**< TODO */
    };

    /**
     * @brief Updates all processors stored in the manager
     *
     * Should be run on world tick
     *
     * @param diff
     */
    void Update(uint32 diff)
    {
        GlobalEvents.Update(diff);
        for (ProcessorMap::iterator it = Processors.begin(); it != Processors.end(); ++it)
            it->second.Update(diff);
    }

    /*
    // Updates processor stored for guid || remove from Update()
    // Should be run on gameobject tick
    static void Update(uint64 guid, uint32 diff)
    {
        if (Processors.find(guid) == Processors.end())
            return;
        Processors[guid].Update(diff);
    }
    */

    /**
     * @brief Aborts all lua events
     *
     * @param events
     */
    void KillAllEvents(EventProcessor* events)
    {
        if (!events)
            return;
        EventMap::const_iterator it = LuaEvents.find(events); // Get event set
        if (it == LuaEvents.end())
            return;
        for (EventSet::const_iterator itr = it->second.begin(); itr != it->second.end(); ++itr) // Loop events
            (*itr)->to_Abort = true; // Abort event
    }

    /**
     * @brief Remove all timed events
     *
     */
    void RemoveEvents()
    {
        for (ProcessorMap::iterator it = Processors.begin(); it != Processors.end(); ++it)
            it->second.KillAllEvents(true);
        Processors.clear();
        for (EventMap::const_iterator it = LuaEvents.begin(); it != LuaEvents.end(); ++it) // loop processors
            KillAllEvents(it->first);
        LuaEvents.clear(); // remove pointer sets
    }

    /**
     * @brief Remove timed events from processor
     *
     * @param events
     */
    void RemoveEvents(EventProcessor* events)
    {
        if (!events)
            return;
        KillAllEvents(events);
        LuaEvents.erase(events); // remove pointer set
    }

    /**
     * @brief Remove timed events from guid
     *
     * @param guid
     */
    void RemoveEvents(uint64 guid)
    {
        if (Processors.find(guid) == Processors.end())
            return;
        Processors[guid].KillAllEvents(true); // remove events
        Processors.erase(guid); // remove processor
    }

    /**
     * @brief Adds a new event to the processor and returns the eventID or 0 (Never negative)
     *
     * @param events
     * @param funcRef
     * @param delay
     * @param calls
     * @param obj
     * @return int
     */
    int AddEvent(EventProcessor* events, int funcRef, uint32 delay, uint32 calls, Object* obj = NULL)
    {
        if (!events || funcRef <= 0) // If funcRef <= 0, function reference failed
            return 0; // on fail always return 0. funcRef can be negative.
        events->AddEvent(new LuaEvent(events, funcRef, delay, calls, obj), events->CalculateTime(delay));
        return funcRef; // return the event ID
    }

    /**
     * @brief Creates a processor for the guid if needed and adds the event to it
     *
     * @param guid
     * @param funcRef
     * @param delay
     * @param calls
     * @param obj
     * @return int
     */
    int AddEvent(uint64 guid, int funcRef, uint32 delay, uint32 calls, Object* obj = NULL)
    {
        if (!guid) // 0 should be unused
            return 0;
        return AddEvent(&Processors[guid], funcRef, delay, calls, obj);
    }

    /**
     * @brief Finds the event that has the ID from events
     *
     * @param events
     * @param eventId
     * @return LuaEvent
     */
    LuaEvent* GetEvent(EventProcessor* events, int eventId)
    {
        if (!events || !eventId)
            return NULL;
        EventMap::const_iterator it = LuaEvents.find(events); // Get event set
        if (it == LuaEvents.end())
            return NULL;
        for (EventSet::const_iterator itr = it->second.begin(); itr != it->second.end(); ++itr) // Loop events
            if ((*itr) && (*itr)->funcRef == eventId) // Check if the event has our ID
                return *itr; // Return the event if found
        return NULL;
    }

    /**
     * @brief Remove the event with the eventId from processor
     *
     * @param events
     * @param eventId
     * @return bool Returns true if event is removed
     */
    bool RemoveEvent(EventProcessor* events, int eventId) // eventId = funcRef
    {
        if (!events || !eventId)
            return false;
        LuaEvent* luaEvent = GetEvent(events, eventId);
        if (!luaEvent)
            return false;
        luaEvent->to_Abort = true; // Set to remove on next call
        // LuaEvents[events].erase(luaEvent); // Remove pointer
        return true;
    }

    /**
     * @brief Remove event by ID from processor stored for guid
     *
     * @param guid
     * @param eventId
     * @return bool
     */
    bool RemoveEvent(uint64 guid, int eventId)
    {
        if (!guid || Processors.find(guid) == Processors.end())
            return false;
        return RemoveEvent(&Processors[guid], eventId);
    }

    /**
     * @brief Removes the eventId from all events
     *
     * @param eventId
     */
    void RemoveEvent(int eventId)
    {
        if (!eventId)
            return;
        for (EventMap::const_iterator it = LuaEvents.begin(); it != LuaEvents.end(); ++it) // loop processors
            if (RemoveEvent(it->first, eventId))
                break; // succesfully remove the event, stop loop.
    }
};

/**
 * @brief
 *
 */
class Eluna
{
    public:
        friend class ScriptMgr;
        lua_State* L; /**< TODO */
        EventMgr EventMgr; /**< TODO */

        /**
         * @brief
         *
         */
        typedef std::map<int, int> ElunaBindingMap;
        /**
         * @brief
         *
         */
        typedef UNORDERED_MAP<uint32, ElunaBindingMap> ElunaEntryMap;
        struct ElunaBind;
        std::map<int, std::vector<int> > ServerEventBindings; /**< TODO */
        std::map<int, std::vector<int> > PlayerEventBindings; /**< TODO */
        std::map<int, std::vector<int> > GuildEventBindings; /**< TODO */
        std::map<int, std::vector<int> > GroupEventBindings; /**< TODO */
        ElunaBind* CreatureEventBindings; /**< TODO */
        ElunaBind* CreatureGossipBindings; /**< TODO */
        ElunaBind* GameObjectEventBindings; /**< TODO */
        ElunaBind* GameObjectGossipBindings; /**< TODO */
        ElunaBind* ItemEventBindings; /**< TODO */
        ElunaBind* ItemGossipBindings; /**< TODO */
        ElunaBind* playerGossipBindings; /**< TODO */

        /**
         * @brief
         *
         */
        void Initialize();
        /**
         * @brief
         *
         * @param
         */
        static void report(lua_State*);
        /**
         * @brief
         *
         * @param reg
         * @param id
         * @param evt
         * @param func
         */
        void Register(uint8 reg, uint32 id, uint32 evt, int func);
        /**
         * @brief
         *
         * @param fReference
         */
        void BeginCall(int fReference);
        /**
         * @brief
         *
         * @param params
         * @param res
         * @return bool
         */
        bool ExecuteCall(uint8 params, uint8 res);
        /**
         * @brief
         *
         * @param res
         */
        void EndCall(uint8 res);
        /**
         * @brief
         *
         * @param directory
         * @param scr
         */
        void LoadDirectory(char* directory, LoadedScripts* scr);
        // Pushes
        /**
         * @brief
         *
         * @param
         */
        void Push(lua_State*); // nil
        /**
         * @brief
         *
         * @param
         * @param uint64
         */
        void Push(lua_State*, uint64);
        /**
         * @brief
         *
         * @param
         * @param int64
         */
        void Push(lua_State*, int64);
        /**
         * @brief
         *
         * @param
         * @param uint32
         */
        void Push(lua_State*, uint32);
        /**
         * @brief
         *
         * @param
         * @param int32
         */
        void Push(lua_State*, int32);
        /**
         * @brief
         *
         * @param
         * @param bool
         */
        void Push(lua_State*, bool);
        /**
         * @brief
         *
         * @param
         * @param float
         */
        void Push(lua_State*, float);
        /**
         * @brief
         *
         * @param
         * @param double
         */
        void Push(lua_State*, double);
        /**
         * @brief
         *
         * @param
         * @param
         */
        void Push(lua_State*, const char*);
        /**
         * @brief
         *
         * @param
         * @param std::string
         */
        void Push(lua_State*, std::string);
        /**
         * @brief
         *
         * @param L
         * @param ptr
         */
        template<typename T> void Push(lua_State* L, T const* ptr)
        {
            ElunaTemplate<T>::push(L, ptr);
        }
        /**
         * @brief
         *
         * @param L
         * @param pet
         */
        template<> void Eluna::Push<Pet>(lua_State* L, Pet const* pet)
        {
            Push(L, pet->ToCreature());
        }
        /**
         * @brief
         *
         * @param L
         * @param summon
         */
        template<> void Eluna::Push<TemporarySummon>(lua_State* L, TemporarySummon const* summon)
        {
            Push(L, summon->ToCreature());
        }
        /**
         * @brief
         *
         * @param L
         * @param unit
         */
        template<> void Eluna::Push<Unit>(lua_State* L, Unit const* unit)
        {
            if (!unit)
            {
                Push(L);
                return;
            }
            switch (unit->GetTypeId())
            {
                case TYPEID_UNIT:
                    Push(L, unit->ToCreature());
                    break;
                case TYPEID_PLAYER:
                    Push(L, unit->ToPlayer());
                    break;
                default:
                    ElunaTemplate<Unit>::push(L, unit);
            }
        }
        /**
         * @brief
         *
         * @param
         * @param obj
         */
        template<> void Eluna::Push<WorldObject>(lua_State*, WorldObject const* obj)
        {
            if (!obj)
            {
                Push(L);
                return;
            }
            switch (obj->GetTypeId())
            {
                case TYPEID_UNIT:
                    Push(L, obj->ToCreature());
                    break;
                case TYPEID_PLAYER:
                    Push(L, obj->ToPlayer());
                    break;
                case TYPEID_GAMEOBJECT:
                    Push(L, obj->ToGameObject());
                    break;
                case TYPEID_CORPSE:
                    Push(L, obj->ToCorpse());
                    break;
                default:
                    ElunaTemplate<WorldObject>::push(L, obj);
            }
        }
        /**
         * @brief
         *
         * @param L
         * @param obj
         */
        template<> void Eluna::Push<Object>(lua_State* L, Object const* obj)
        {
            if (!obj)
            {
                Push(L);
                return;
            }
            switch (obj->GetTypeId())
            {
                case TYPEID_UNIT:
                    Push(L, obj->ToCreature());
                    break;
                case TYPEID_PLAYER:
                    Push(L, obj->ToPlayer());
                    break;
                case TYPEID_GAMEOBJECT:
                    Push(L, obj->ToGameObject());
                    break;
                case TYPEID_CORPSE:
                    Push(L, obj->ToCorpse());
                    break;
                default:
                    ElunaTemplate<Object>::push(L, obj);
            }
        }

        // Checks
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return WorldPacket
         */
        WorldPacket* CHECK_PACKET(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Object
         */
        Object* CHECK_OBJECT(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return WorldObject
         */
        WorldObject* CHECK_WORLDOBJECT(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Unit
         */
        Unit* CHECK_UNIT(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Player
         */
        Player* CHECK_PLAYER(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Creature
         */
        Creature* CHECK_CREATURE(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return GameObject
         */
        GameObject* CHECK_GAMEOBJECT(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Corpse
         */
        Corpse* CHECK_CORPSE(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Quest
         */
        Quest* CHECK_QUEST(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Spell
         */
        Spell* CHECK_SPELL(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return uint64
         */
        uint64 CHECK_ULONG(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return int64
         */
        int64 CHECK_LONG(lua_State* L, int narg);
        /**
         * @brief
         *
         * @param L
         * @param narg
         * @return Item
         */
        Item* CHECK_ITEM(lua_State* L, int narg);

        /**
         * @brief Creates new binding stores
         *
         */
        Eluna()
        {
            L = NULL;

            for (int i = 0; i < SERVER_EVENT_COUNT; ++i)
            {
                std::vector<int> _vector;
                ServerEventBindings.insert(std::pair<int, std::vector<int> >(i, _vector));
            }

            for (int i = 0; i < PLAYER_EVENT_COUNT; ++i)
            {
                std::vector<int> _vector;
                PlayerEventBindings.insert(std::pair<int, std::vector<int> >(i, _vector));
            }

            for (int i = 0; i < GUILD_EVENT_COUNT; ++i)
            {
                std::vector<int> _vector;
                GuildEventBindings.insert(std::pair<int, std::vector<int> >(i, _vector));
            }

            for (int i = 0; i < GROUP_EVENT_COUNT; ++i)
            {
                std::vector<int> _vector;
                GroupEventBindings.insert(std::pair<int, std::vector<int> >(i, _vector));
            }
            CreatureEventBindings = new ElunaBind;
            CreatureGossipBindings = new ElunaBind;
            GameObjectEventBindings = new ElunaBind;
            GameObjectGossipBindings = new ElunaBind;
            ItemEventBindings = new ElunaBind;
            ItemGossipBindings = new ElunaBind;
            playerGossipBindings = new ElunaBind;
        }

        /**
         * @brief
         *
         */
        ~Eluna()
        {
            for (std::map<int, std::vector<int> >::iterator itr = ServerEventBindings.begin(); itr != ServerEventBindings.end(); ++itr)
            {
                for (std::vector<int>::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                    luaL_unref(L, LUA_REGISTRYINDEX, (*it));
                itr->second.clear();
            }

            for (std::map<int, std::vector<int> >::iterator itr = PlayerEventBindings.begin(); itr != PlayerEventBindings.end(); ++itr)
            {
                for (std::vector<int>::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                    luaL_unref(L, LUA_REGISTRYINDEX, (*it));
                itr->second.clear();
            }

            for (std::map<int, std::vector<int> >::iterator itr = GuildEventBindings.begin(); itr != GuildEventBindings.end(); ++itr)
            {
                for (std::vector<int>::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                    luaL_unref(L, LUA_REGISTRYINDEX, (*it));
                itr->second.clear();
            }

            for (std::map<int, std::vector<int> >::iterator itr = GroupEventBindings.begin(); itr != GroupEventBindings.end(); ++itr)
            {
                for (std::vector<int>::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                    luaL_unref(L, LUA_REGISTRYINDEX, (*it));
                itr->second.clear();
            }
            ServerEventBindings.clear();
            PlayerEventBindings.clear();
            GuildEventBindings.clear();
            GroupEventBindings.clear();
            CreatureEventBindings->Clear();
            CreatureGossipBindings->Clear();
            GameObjectEventBindings->Clear();
            GameObjectGossipBindings->Clear();
            ItemEventBindings->Clear();
            ItemGossipBindings->Clear();
            playerGossipBindings->Clear();

            lua_close(L); // Closing
        }

        /**
         * @brief
         *
         */
        struct ElunaBind
        {
            /**
             * @brief unregisters all registered functions and clears all registered events from the bind std::maps (reset)
             *
             */
            void Clear();
            /**
             * @brief Inserts a new registered event
             *
             * @param entryId
             * @param eventId
             * @param funcRef
             */
            void Insert(uint32 entryId, uint32 eventId, int funcRef);

            /**
             * @brief Gets the function ref of an entry for an event
             *
             * @param entryId
             * @param eventId
             * @return int
             */
            int GetBind(uint32 entryId, uint32 eventId)
            {
                ElunaEntryMap::iterator itr = Bindings.find(entryId);
                if (itr == Bindings.end())
                    return 0;

                return itr->second[eventId];
            }

            /**
             * @brief Gets the binding std::map containing all registered events with the function refs for the entry
             *
             * @param entryId
             * @return ElunaBindingMap
             */
            ElunaBindingMap* GetBindMap(uint32 entryId)
            {
                ElunaEntryMap::iterator itr = Bindings.find(entryId);
                if (itr == Bindings.end())
                    return NULL;

                return &itr->second;
            }

            ElunaEntryMap Bindings; // Binding store Bindings[entryId][eventId] = funcRef; /**< TODO */
        };

        /**
         * @brief
         *
         */
        struct ObjectGUIDCheck
        {
            /**
             * @brief
             *
             * @param GUID
             */
            ObjectGUIDCheck(ObjectGuid GUID) : _GUID(GUID) { }
            /**
             * @brief
             *
             * @param object
             * @return bool operator
             */
            bool operator()(WorldObject* object)
            {
                return object->GetObjectGuid() == _GUID;
            }

            ObjectGuid _GUID; /**< TODO */
        };

        /**
         * @brief Binary predicate to sort WorldObjects based on the distance to a reference WorldObject
         *
         */
        struct ObjectDistanceOrderPred
        {
            /**
             * @brief
             *
             * @param pRefObj
             * @param ascending
             */
            ObjectDistanceOrderPred(WorldObject const* pRefObj, bool ascending = true) : m_refObj(pRefObj), m_ascending(ascending) { }
            /**
             * @brief
             *
             * @param pLeft
             * @param pRight
             * @return bool operator
             */
            bool operator()(WorldObject const* pLeft, WorldObject const* pRight) const
            {
                return m_ascending ? m_refObj->GetDistanceOrder(pLeft, pRight) : !m_refObj->GetDistanceOrder(pLeft, pRight);
            }

            WorldObject const* m_refObj; /**< TODO */
            const bool m_ascending; /**< TODO */
        };

        /**
         * @brief Doesn't get self
         *
         */
        struct WorldObjectInRangeCheck
        {
            /**
             * @brief
             *
             * @param nearest
             * @param obj
             * @param range
             * @param typeId
             * @param entry
             */
            WorldObjectInRangeCheck(bool nearest, WorldObject const* obj, float range,
                                    TypeID typeId = TYPEID_OBJECT, uint32 entry = 0) : i_nearest(nearest),
                i_obj(obj), i_range(range), i_typeId(typeId), i_entry(entry) {}
            /**
             * @brief
             *
             * @return const WorldObject
             */
            WorldObject const& GetFocusObject() const { return *i_obj; }
            /**
             * @brief
             *
             * @param u
             * @return bool operator
             */
            bool operator()(WorldObject* u)
            {
                if (i_typeId && u->GetTypeId() != i_typeId)
                    return false;
                if (i_entry && u->GetEntry() != i_entry)
                    return false;
                if (i_obj->GetObjectGuid() == u->GetObjectGuid())
                    return false;
                if (!i_obj->IsWithinDistInMap(u, i_range))
                    return false;
                if (Unit* unit = u->ToUnit())
                    if (!unit->isAlive())
                        return false;
                if (i_nearest)
                    i_range = i_obj->GetDistance(u);
                return true;
            }

            WorldObject const* i_obj; /**< TODO */
            float i_range; /**< TODO */
            TypeID i_typeId; /**< TODO */
            uint32 i_entry; /**< TODO */
            bool i_nearest; /**< TODO */

            /**
             * @brief
             *
             * @param
             */
            WorldObjectInRangeCheck(WorldObjectInRangeCheck const&);
        };
};
#define sEluna MaNGOS::Singleton<Eluna>::Instance()

/**
 * @brief
 *
 */
class LuaTaxiMgr
{
    private:
        static uint32 nodeId; /**< TODO */
    public:
        /**
         * @brief
         *
         * @param player
         * @param pathid
         */
        static void StartTaxi(Player* player, uint32 pathid);
        /**
         * @brief
         *
         * @param nodes
         * @param mountA
         * @param mountH
         * @param price
         * @param pathId
         * @return uint32
         */
        static uint32 AddPath(std::list<TaxiPathNodeEntry> nodes, uint32 mountA, uint32 mountH, uint32 price = 0, uint32 pathId = 0);
};
#endif
