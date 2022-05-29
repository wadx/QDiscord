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

#pragma once

#include "models/QDiscordChannel.h"
#include "models/QDiscordMember.h"
#include "models/QDiscordMessage.h"
#include "models/QDiscordUser.h"
#include "qdiscordabstractstate.h"


class QDiscordJsonDecoder : QObject
{
	Q_OBJECT
public:
	QDiscordJsonDecoder(QObject* parent = nullptr);
	QDiscordAbstractState* state() const { return _state; }
	void setState(QDiscordAbstractState* state) { _state = state; }
	void input(const QJsonObject& d, const QString& t);

private:
	void readyReceived(const QJsonObject& object);
	void resumedReceived(const QJsonObject& object);
	void applicationCommandPermissionsUpdateReceived(const QJsonObject& object);
	void embeddedActivityUpdateReceived(const QJsonObject& object);
	void channelCreateReceived(const QJsonObject& object);
	void channelUpdateReceived(const QJsonObject& object);
	void channelDeleteReceived(const QJsonObject& object);
	void channelPinsUpdateReceived(const QJsonObject& object);
	void guildCreateReceived(const QJsonObject& object);
	void guildUpdateReceived(const QJsonObject& object);
	void guildDeleteReceived(const QJsonObject& object);
	void guildBanAddReceived(const QJsonObject& object);
	void guildBanRemoveReceived(const QJsonObject& object);
	void guildEmojisUpdateReceived(const QJsonObject& object);
	void guildIntegrationsUpdateReceived(const QJsonObject& object);
	void guildMemberAddReceived(const QJsonObject& object);
	void guildMemberRemoveReceived(const QJsonObject& object);
	void guildMemberUpdateReceived(const QJsonObject& object);
	void guildMembersChunkReceived(const QJsonObject& object);
	void guildRoleCreateReceived(const QJsonObject& object);
	void guildRoleUpdateReceived(const QJsonObject& object);
	void guildRoleDeleteReceived(const QJsonObject& object);
	void guildStickersUpdateReceived(const QJsonObject& object);
	void guildApplicationCommandCountsUpdateReceived(const QJsonObject& object);
	void guildScheduledEventCreateReceived(const QJsonObject& object);
	void guildScheduledEventUpdateReceived(const QJsonObject& object);
	void guildScheduledEventDeleteReceived(const QJsonObject& object);
	void guildScheduledEventUserUserAddReceived(const QJsonObject& object);
	void guildScheduledEventUserUserRemoveReceived(const QJsonObject& object);
	void guildJoinRequestDeleteReceived(const QJsonObject& object);
	void guildJoinRequestUpdateReceived(const QJsonObject& object);
	void inviteCreateReceived(const QJsonObject& object);
	void inviteDeleteReceived(const QJsonObject& object);
	void interactionCreateReceived(const QJsonObject& object);
	void integrationUpdateReceived(const QJsonObject& object);
	void integrationDeleteReceived(const QJsonObject& object);
	void messageCreateReceived(const QJsonObject& object);
	void messageUpdateReceived(const QJsonObject& object);
	void messageDeleteReceived(const QJsonObject& object);
	void messageDeleteBulkReceived(const QJsonObject& object);
	void messageReactionAddReceived(const QJsonObject& object);
	void messageReactionRemoveReceived(const QJsonObject& object);
	void messageReactionRemoveAllReceived(const QJsonObject& object);
	void messageReactionRemoveEmojiReceived(const QJsonObject& object);
	void presenceUpdateReceived(const QJsonObject& object);
	void stageInstanceCreateReceived(const QJsonObject& object);
	void stageInstanceUpdateReceived(const QJsonObject& object);
	void stageInstanceDeleteReceived(const QJsonObject& object);
	void threadCreateReceived(const QJsonObject& object);
	void threadUpdateReceived(const QJsonObject& object);
	void threadDeleteReceived(const QJsonObject& object);
	void threadListSyncReceived(const QJsonObject& object);
	void threadMemberUpdateReceived(const QJsonObject& object);
	void threadMembersUpdateReceived(const QJsonObject& object);
	void typingStartReceived(const QJsonObject& object);
	void userUpdateReceived(const QJsonObject& object);
	void voiceStateUpdateReceived(const QJsonObject& object);
	void voiceServerUpdateReceived(const QJsonObject& object);
	void webhooksUpdateReceived(const QJsonObject& object);

	static const QMap<QString, void (QDiscordJsonDecoder::*)(const QJsonObject&)> _dispatchTable;
	QDiscordAbstractState* _state = nullptr;
};


