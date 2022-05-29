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
#include "models/QDiscordInteraction.h"
#include "models/QDiscordApplication.h"
#include "models/QDiscordPresence.h"


class QDiscordAbstractState : public QObject
{
	Q_OBJECT
public:
	explicit QDiscordAbstractState(QObject* parent = nullptr);
	virtual ~QDiscordAbstractState() = default;
	virtual void readyReceived(int protocolVersion, QSharedPointer<QDiscordApplication> application, QSharedPointer<QDiscordUser> user) = 0;
	virtual void channelCreateReceived(QSharedPointer<QDiscordChannel> channel) = 0;
	virtual void channelUpdateReceived(QSharedPointer<QDiscordChannel> channel) = 0;
	virtual void channelDeleteReceived(QSharedPointer<QDiscordChannel> channel) = 0;
	virtual void guildCreateReceived(QSharedPointer<QDiscordGuild> guild) = 0;
	virtual void guildUpdateReceived(QSharedPointer<QDiscordGuild> guild) = 0;
	virtual void guildDeleteReceived(QSharedPointer<QDiscordGuild> guild) = 0;
	virtual void guildBanAddReceived(const QJsonObject& object) = 0;
	virtual void guildBanRemoveReceived(const QJsonObject& object) = 0;
	virtual void guildEmojisUpdateReceived(const QJsonObject& object) = 0;
	virtual void guildIntegrationsUpdateReceived(const QJsonObject& object) = 0;
	virtual void guildMemberAddReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId) = 0;
	virtual void guildMemberRemoveReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId) = 0;
	virtual void guildMemberUpdateReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId) = 0;
	virtual void guildMembersChunkReceived(const QJsonObject& object) = 0;
	virtual void guildRoleCreateReceived(QSharedPointer<QDiscordRole> role, QDiscordID guildId) = 0;
	virtual void guildRoleUpdateReceived(QSharedPointer<QDiscordRole> role, QDiscordID guildId) = 0;
	virtual void guildRoleDeleteReceived(QDiscordID roleId, QDiscordID guildId) = 0;
	virtual void interactionCreateReceived(QSharedPointer<QDiscordInteraction> interaction) = 0;
	virtual void messageCreateReceived(QSharedPointer<QDiscordMessage> message) = 0;
	virtual void messageUpdateReceived(QSharedPointer<QDiscordMessage> message) = 0;
	virtual void messageDeleteReceived(QSharedPointer<QDiscordMessage> message) = 0;
	virtual void messageDeleteBulkReceived(const QJsonObject& object) = 0;
	virtual void presenceUpdateReceived(const QJsonObject& object) = 0;
	virtual void typingStartReceived(const QJsonObject& object) = 0;
	virtual void userUpdateReceived(QSharedPointer<QDiscordUser> user) = 0;
	virtual void applicationCommandPermissionsUpdateReceived(QSharedPointer<QDiscordGuildApplicationCommandPermissions> permissions) = 0;
	virtual void voiceStateUpdateReceived(const QJsonObject& object) = 0;
	virtual void voiceServerUpdateReceived(const QJsonObject& object) = 0;
	virtual void reset() = 0;
signals:
	void selfCreated(QSharedPointer<QDiscordApplication> application, QSharedPointer<QDiscordUser> user);
	void channelCreated(QSharedPointer<QDiscordChannel> channel);
	void channelUpdated(QSharedPointer<QDiscordChannel> channel);
	void channelDeleted(QSharedPointer<QDiscordChannel> channel);
	void guildCreated(QSharedPointer<QDiscordGuild> guild);
	void guildAvailable(QSharedPointer<QDiscordGuild> guild);
	void guildUpdated(QSharedPointer<QDiscordGuild> guild);
	void guildDeleted(QSharedPointer<QDiscordGuild> guild);
	void guildUnavailable(QSharedPointer<QDiscordGuild> guild);
	void guildBanAdded(QSharedPointer<QDiscordGuild> guild, QDiscordUser user);
	void guildBanRemoved(QSharedPointer<QDiscordGuild> guild, QDiscordUser user);
	void guildEmojisUpdated(/* TODO: Fill this in */);
	void guildIntegrationsUpdated(QSharedPointer<QDiscordGuild> guild);
	void guildMemberAdded(QSharedPointer<QDiscordMember> member);
	void guildMemberRemoved(QSharedPointer<QDiscordMember> member);
	void guildMemberUpdated(QSharedPointer<QDiscordMember> member);
	void guildMembersChunk(QSharedPointer<QDiscordGuild> guild, QList<QSharedPointer<QDiscordMember>> members);
	void guildRoleCreated(QSharedPointer<QDiscordRole> role);
	void guildRoleUpdated(QSharedPointer<QDiscordRole> role);
	void guildRoleDeleted(QSharedPointer<QDiscordRole> role);
	void interactionReceived(QSharedPointer<QDiscordInteraction> interaction);
	void messageCreated(QSharedPointer<QDiscordMessage> message);
	void messageUpdated(QSharedPointer<QDiscordMessage> message);
	void messageDeleted(QSharedPointer<QDiscordMessage> message);
	void messagesDeleted(QList<QDiscordMessage> messages);
	void presenceUpdated(/* TODO: Fill this in */);
	void typingStarted(QSharedPointer<QDiscordChannel> channel, QSharedPointer<QDiscordUser> user, QDateTime timestamp);
	void selfUpdated(QSharedPointer<QDiscordUser> user);
	void voiceStateUpdated(/* TODO: Fill this in */);
	void voiceServerUpdated(QString token, QSharedPointer<QDiscordGuild> guild, QString endpoint);
	void guildsNumberChanged(int guildsNumber);

private:
};

