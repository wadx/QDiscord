/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 george99g
 * Copyright(c) 2022 by wad(wad@inbox.lv)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"
#include "QDiscordJsonDecoder.h"
#include "moc_QDiscordJsonDecoder.cpp"


const QMap<QString, void (QDiscordJsonDecoder::*)(const QJsonObject&)>
QDiscordJsonDecoder::_dispatchTable =
{
	{ "READY",                                   &QDiscordJsonDecoder::readyReceived },
	{ "RESUMED",                                 &QDiscordJsonDecoder::resumedReceived },
	{ "APPLICATION_COMMAND_PERMISSIONS_UPDATE",  &QDiscordJsonDecoder::applicationCommandPermissionsUpdateReceived },
	{ "EMBEDDED_ACTIVITY_UPDATE",                &QDiscordJsonDecoder::embeddedActivityUpdateReceived },
	{ "CHANNEL_CREATE",                          &QDiscordJsonDecoder::channelCreateReceived },
	{ "CHANNEL_UPDATE",                          &QDiscordJsonDecoder::channelUpdateReceived },
	{ "CHANNEL_DELETE",                          &QDiscordJsonDecoder::channelDeleteReceived },
	{ "CHANNEL_PINS_UPDATE",                     &QDiscordJsonDecoder::channelPinsUpdateReceived },
	{ "GUILD_CREATE",                            &QDiscordJsonDecoder::guildCreateReceived },
	{ "GUILD_UPDATE",                            &QDiscordJsonDecoder::guildUpdateReceived },
	{ "GUILD_DELETE",                            &QDiscordJsonDecoder::guildDeleteReceived },
	{ "GUILD_BAN_ADD",                           &QDiscordJsonDecoder::guildBanAddReceived },
	{ "GUILD_BAN_REMOVE",                        &QDiscordJsonDecoder::guildBanRemoveReceived },
	{ "GUILD_EMOJIS_UPDATE",                     &QDiscordJsonDecoder::guildEmojisUpdateReceived },
	{ "GUILD_INTEGRATIONS_UPDATE",               &QDiscordJsonDecoder::guildIntegrationsUpdateReceived },
	{ "GUILD_MEMBER_ADD",                        &QDiscordJsonDecoder::guildMemberAddReceived },
	{ "GUILD_MEMBER_REMOVE",                     &QDiscordJsonDecoder::guildMemberRemoveReceived },
	{ "GUILD_MEMBER_UPDATE",                     &QDiscordJsonDecoder::guildMemberUpdateReceived },
	{ "GUILD_MEMBERS_CHUNK",                     &QDiscordJsonDecoder::guildMembersChunkReceived },
	{ "GUILD_ROLE_CREATE",                       &QDiscordJsonDecoder::guildRoleCreateReceived },
	{ "GUILD_ROLE_UPDATE",                       &QDiscordJsonDecoder::guildRoleUpdateReceived },
	{ "GUILD_ROLE_DELETE",                       &QDiscordJsonDecoder::guildRoleDeleteReceived },
	{ "GUILD_STICKERS_UPDATE",                   &QDiscordJsonDecoder::guildStickersUpdateReceived },
	{ "GUILD_APPLICATION_COMMAND_COUNTS_UPDATE", &QDiscordJsonDecoder::guildApplicationCommandCountsUpdateReceived },
	{ "GUILD_SCHEDULED_EVENT_CREATE",            &QDiscordJsonDecoder::guildScheduledEventCreateReceived },
	{ "GUILD_SCHEDULED_EVENT_UPDATE",            &QDiscordJsonDecoder::guildScheduledEventUpdateReceived },
	{ "GUILD_SCHEDULED_EVENT_DELETE",            &QDiscordJsonDecoder::guildScheduledEventDeleteReceived },
	{ "GUILD_SCHEDULED_EVENT_USER_ADD",          &QDiscordJsonDecoder::guildScheduledEventUserUserAddReceived },
	{ "GUILD_SCHEDULED_EVENT_USER_REMOVE",       &QDiscordJsonDecoder::guildScheduledEventUserUserRemoveReceived },
	{ "GUILD_JOIN_REQUEST_DELETE",               &QDiscordJsonDecoder::guildJoinRequestDeleteReceived },
	{ "GUILD_JOIN_REQUEST_UPDATE",               &QDiscordJsonDecoder::guildJoinRequestUpdateReceived },
	{ "INVITE_CREATE",                           &QDiscordJsonDecoder::inviteCreateReceived },
	{ "INVITE_DELETE",                           &QDiscordJsonDecoder::inviteDeleteReceived },
	{ "INTERACTION_CREATE",                      &QDiscordJsonDecoder::interactionCreateReceived },
	{ "INTEGRATION_UPDATE",                      &QDiscordJsonDecoder::integrationUpdateReceived },
	{ "INTEGRATION_DELETE",                      &QDiscordJsonDecoder::integrationDeleteReceived },
	{ "MESSAGE_CREATE",                          &QDiscordJsonDecoder::messageCreateReceived },
	{ "MESSAGE_UPDATE",                          &QDiscordJsonDecoder::messageUpdateReceived },
	{ "MESSAGE_DELETE",                          &QDiscordJsonDecoder::messageDeleteReceived },
	{ "MESSSAGE_DELETE_BULK",                    &QDiscordJsonDecoder::messageDeleteBulkReceived },
	{ "MESSAGE_REACTION_ADD",                    &QDiscordJsonDecoder::messageReactionAddReceived },
	{ "MESSAGE_REACTION_REMOVE",                 &QDiscordJsonDecoder::messageReactionRemoveReceived },
	{ "MESSAGE_REACTION_REMOVE_ALL",             &QDiscordJsonDecoder::messageReactionRemoveAllReceived },
	{ "MESSAGE_REACTION_REMOVE_EMOJI",           &QDiscordJsonDecoder::messageReactionRemoveEmojiReceived },
	{ "PRESENCE_UPDATE",                         &QDiscordJsonDecoder::presenceUpdateReceived },
	{ "STAGE_INSTANCE_CREATE",                   &QDiscordJsonDecoder::stageInstanceCreateReceived },
	{ "STAGE_INSTANCE_UPDATE",                   &QDiscordJsonDecoder::stageInstanceUpdateReceived },
	{ "STAGE_INSTANCE_DELETE",                   &QDiscordJsonDecoder::stageInstanceDeleteReceived },
	{ "THREAD_CREATE",                           &QDiscordJsonDecoder::threadCreateReceived },
	{ "THREAD_UPDATE",                           &QDiscordJsonDecoder::threadUpdateReceived },
	{ "THREAD_DELETE",                           &QDiscordJsonDecoder::threadDeleteReceived },
	{ "THREAD_LIST_SYNC",                        &QDiscordJsonDecoder::threadListSyncReceived },
	{ "THREAD_MEMBER_UPDATE",                    &QDiscordJsonDecoder::threadMemberUpdateReceived },
	{ "THREAD_MEMBERS_UPDATE",                   &QDiscordJsonDecoder::threadMembersUpdateReceived },
	{ "TYPING_START",                            &QDiscordJsonDecoder::typingStartReceived },
	{ "USER_UPDATE",                             &QDiscordJsonDecoder::userUpdateReceived },
	{ "VOICE_STATE_UPDATE",                      &QDiscordJsonDecoder::voiceStateUpdateReceived },
	{ "VOICE_SERVER_UPDATE",                     &QDiscordJsonDecoder::voiceServerUpdateReceived },
	{ "WEBHOOKS_UPDATE",                         &QDiscordJsonDecoder::webhooksUpdateReceived },
};


QDiscordJsonDecoder::QDiscordJsonDecoder(QObject* parent)
	: QObject(parent)
{
}


void QDiscordJsonDecoder::input(const QJsonObject& d, const QString& t)
{
	if (!_state)
	{
		return;
	}
	if (_dispatchTable.contains(t))
	{
		(this->*_dispatchTable[t])(d);
	}
	else
	{
		qCDebug(STATE, ) << "No dispatch table entry found for " << t;
	}
}


void QDiscordJsonDecoder::readyReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->readyReceived(object["v"].toInt(-1), QDiscordApplication::fromJson(object["application"].toObject()), QDiscordUser::fromJson(object["user"].toObject()));
	}
	for (const QJsonValueRef& item : object["guilds"].toArray())
	{
		guildCreateReceived(item.toObject());
	}
	for (const QJsonValueRef& item : object["private_channels"].toArray())
	{
		channelCreateReceived(item.toObject());
	}
	//"_trace": []
	//"geo_ordered_rtc_regions": []
	//"guild_join_requests": []
	//"presences": []
	//"relationships": []
	//"user_settings": {}
	//shard?	array of two integers (shard_id, num_shards)	the shard information associated with this session, if sent when identifying
}


void QDiscordJsonDecoder::resumedReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::channelCreateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->channelCreateReceived(QDiscordChannel::fromJson(object));
	}
}


void QDiscordJsonDecoder::channelUpdateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->channelUpdateReceived(QDiscordChannel::fromJson(object));
	}
}


void QDiscordJsonDecoder::channelDeleteReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->channelDeleteReceived(QDiscordChannel::fromJson(object));
	}
}


void QDiscordJsonDecoder::guildCreateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildCreateReceived(QDiscordGuild::fromJson(object));
	}
}


void QDiscordJsonDecoder::guildUpdateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildUpdateReceived(QDiscordGuild::fromJson(object));
	}
}


void QDiscordJsonDecoder::guildDeleteReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildDeleteReceived(QDiscordGuild::fromJson(object));
	}
}


void QDiscordJsonDecoder::guildBanAddReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildBanRemoveReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildEmojisUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildIntegrationsUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildMemberAddReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildMemberAddReceived(QDiscordMember::fromJson(object), QDiscordID(object["guild_id"].toString()));
	}
}


void QDiscordJsonDecoder::guildMemberRemoveReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildMemberRemoveReceived(QDiscordMember::fromJson(object), QDiscordID(object["guild_id"].toString()));
	}
}


void QDiscordJsonDecoder::guildMemberUpdateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildMemberUpdateReceived(QDiscordMember::fromJson(object), QDiscordID(object["guild_id"].toString()));
	}
}


void QDiscordJsonDecoder::guildMembersChunkReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildRoleCreateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildRoleCreateReceived(QDiscordRole::fromJson(object), QDiscordID(object["guild_id"].toString()));
	}
}


void QDiscordJsonDecoder::guildRoleUpdateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildRoleUpdateReceived(QDiscordRole::fromJson(object), QDiscordID(object["guild_id"].toString()));
	}
}


void QDiscordJsonDecoder::guildRoleDeleteReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->guildRoleDeleteReceived(QDiscordID(object["role_id"].toString()), QDiscordID(object["guild_id"].toString()));
	}
}


void QDiscordJsonDecoder::interactionCreateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->interactionCreateReceived(QDiscordInteraction::fromJson(object));
	}
}


void QDiscordJsonDecoder::integrationUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::integrationDeleteReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::messageCreateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->messageCreateReceived(QDiscordMessage::fromJson(object));
	}
}


void QDiscordJsonDecoder::messageUpdateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->messageUpdateReceived(QDiscordMessage::fromJson(object));
	}
}


void QDiscordJsonDecoder::messageDeleteReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->messageDeleteReceived(QDiscordMessage::fromJson(object));
	}
}


void QDiscordJsonDecoder::messageDeleteBulkReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::presenceUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this to QDiscordPresence
}


void QDiscordJsonDecoder::applicationCommandPermissionsUpdateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->applicationCommandPermissionsUpdateReceived(QDiscordGuildApplicationCommandPermissions::fromJson(object));
	}
}


void QDiscordJsonDecoder::embeddedActivityUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::channelPinsUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildStickersUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildApplicationCommandCountsUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildScheduledEventCreateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildScheduledEventUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildScheduledEventDeleteReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildScheduledEventUserUserAddReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildScheduledEventUserUserRemoveReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildJoinRequestDeleteReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::guildJoinRequestUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::inviteCreateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::inviteDeleteReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::messageReactionAddReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::messageReactionRemoveReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::messageReactionRemoveAllReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::messageReactionRemoveEmojiReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::stageInstanceCreateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::stageInstanceUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::stageInstanceDeleteReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::threadCreateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::threadUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::threadDeleteReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::threadListSyncReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::threadMemberUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::threadMembersUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::typingStartReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::userUpdateReceived(const QJsonObject& object)
{
	if (_state)
	{
		_state->userUpdateReceived(QDiscordUser::fromJson(object));
	}
}


void QDiscordJsonDecoder::voiceStateUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::voiceServerUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


void QDiscordJsonDecoder::webhooksUpdateReceived(const QJsonObject& object)
{
	Q_UNUSED(object);
	// TODO: Implement this
}


