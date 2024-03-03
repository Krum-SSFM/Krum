// Krum - Krum mcpe 0.14-1.1 server software.
//
// Copyright (C) 2024  Krum-SSFM.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <cstdint>

namespace Krum::network::protocol
{ 
    static constexpr std::uint8_t OLDV_PACKET_HEADER_BYTE = 0x8e;

    enum class PacketIdentifiers : std::uint8_t
    {
        NONE,
        LOGIN,
        PLAY_STATUS,
        DISCONNECT,
        BATCH,
        TEXT,
        SET_TIME,
        START_GAME,
        ADD_PLAYER,
        REMOVE_PLAYER,
        ADD_ENTITY,
        REMOVE_ENTITY,
        ADD_ITEM_ENTITY,
        TAKE_ITEM_ENTITY,
        MOVE_ENTITY,
        MOVE_PLAYER,
        REMOVE_BLOCK,
        UPDATE_BLOCK,
        ADD_PAINTING,
        EXPLODE,
        LEVEL_EVENT,
        BLOCK_EVENT,
        ENTITY_EVENT,
        MOB_EFFECT,
        UPDATE_ATTRIBUTES,
        MOB_EQUIPMENT,
        MOB_ARMOR_EQUIPMENT,
        INTERACT,
        USE_ITEM,
        PLAYER_ACTION,
        HURT_ARMOR,
        SET_ENTITY_DATA,
        SET_ENTITY_MOTION,
        SET_ENTITY_LINK,
        SET_HEALTH,
        SET_SPAWN_POSITION,
        ANIMATE,
        RESPAWN,
        DROP_ITEM,
        CONTAINER_OPEN,
        CONTAINER_CLOSE,
        CONTAINER_SET_SLOT,
        CONTAINER_SET_DATA,
        CONTAINER_SET_CONTENT,
        CRAFTING_DATA,
        CRAFTING_EVENT,
        ADVENTURE_SETTINGS,
        BLOCK_ENTITY_DATA,
        PLAYER_INPUT,
        FULL_CHUNK_DATA,
        SET_DIFFICULITY,
        CHANGE_DIMENSION,
        SET_PLAYER_GAME_TYPE,
        PLAYER_LIST,
        TELEMETRY_EVENT,
        SPAWN_EXPERIENCE_ORB,
        CLIENT_BOUND_MAP_ITEM_DATA,
        MAP_INFO_REQUEST,
        REQUEST_CHUNK_RADIUS,
        CHUNK_RADIUS_UPDATED,
        ITEM_FRAME_DROP_ITEM,
        REPLACE_SELECTED_ITEM
    };

    using packet_identifier_t = PacketIdentifiers;
}
