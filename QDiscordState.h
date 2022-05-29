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

#include "QDiscordAbstractState.h"


class QDiscordRest;


class QDiscordState : public QDiscordAbstractState
{
	Q_OBJECT

	Q_PROPERTY(int protocolVersion READ protocolVersion)
	Q_PROPERTY(QSharedPointer<QDiscordUser> user READ user WRITE setUser)
	Q_PROPERTY(QList<QSharedPointer<QDiscordChannel>> dmChannels READ dmChannels STORED false)
	Q_PROPERTY(QList<QSharedPointer<QDiscordGuild>> guilds READ guilds STORED false)

public:
	explicit QDiscordState(QObject* parent = nullptr);
	virtual ~QDiscordState() = default;
	void readyReceived(int protocolVersion, QSharedPointer<QDiscordApplication> application, QSharedPointer<QDiscordUser> user) override;
	void channelCreateReceived(QSharedPointer<QDiscordChannel> channel) override;
	void channelUpdateReceived(QSharedPointer<QDiscordChannel> channel) override;
	void channelDeleteReceived(QSharedPointer<QDiscordChannel> channel) override;
	void guildCreateReceived(QSharedPointer<QDiscordGuild> guild) override;
	void guildUpdateReceived(QSharedPointer<QDiscordGuild> guild) override;
	void guildDeleteReceived(QSharedPointer<QDiscordGuild> guild) override;
	void guildBanAddReceived(const QJsonObject& object) override;
	void guildBanRemoveReceived(const QJsonObject& object) override;
	void guildEmojisUpdateReceived(const QJsonObject& object) override;
	void guildIntegrationsUpdateReceived(const QJsonObject& object) override;
	void guildMemberAddReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId) override;
	void guildMemberRemoveReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId) override;
	void guildMemberUpdateReceived(QSharedPointer<QDiscordMember> member, QDiscordID guildId) override;
	void guildMembersChunkReceived(const QJsonObject& object) override;
	void guildRoleCreateReceived(QSharedPointer<QDiscordRole> role, QDiscordID guildId) override;
	void guildRoleUpdateReceived(QSharedPointer<QDiscordRole> role, QDiscordID guildId) override;
	void guildRoleDeleteReceived(QDiscordID roleId, QDiscordID guildId) override;
	void interactionCreateReceived(QSharedPointer<QDiscordInteraction> interaction) override;
	void messageCreateReceived(QSharedPointer<QDiscordMessage> message) override;
	void messageUpdateReceived(QSharedPointer<QDiscordMessage> message) override;
	void messageDeleteReceived(QSharedPointer<QDiscordMessage> message) override;
	void messageDeleteBulkReceived(const QJsonObject& object) override;
	void presenceUpdateReceived(const QJsonObject& object) override;
	void typingStartReceived(const QJsonObject& object) override;
	void userUpdateReceived(QSharedPointer<QDiscordUser> user) override;
	void applicationCommandPermissionsUpdateReceived(QSharedPointer<QDiscordGuildApplicationCommandPermissions> permissions) override;
	void voiceStateUpdateReceived(const QJsonObject& object) override;
	void voiceServerUpdateReceived(const QJsonObject& object) override;
	void reset() override;

	int protocolVersion() const { return _protocolVersion; }
	QSharedPointer<QDiscordUser> user() const { return _user; }
	void setUser(QSharedPointer<QDiscordUser> user) { _user = user; }
	Q_INVOKABLE QSharedPointer<QDiscordChannel> dmChannel(const QDiscordID& id) const { return _dmChannels.value(id); }
	QList<QSharedPointer<QDiscordChannel>> dmChannels() const { return _dmChannels.values(); }
	QMap<QDiscordID, QSharedPointer<QDiscordChannel>> dmChannelsMap() const { return _dmChannels; }
	Q_INVOKABLE QSharedPointer<QDiscordChannel> channel(const QDiscordID& id) const;
	Q_INVOKABLE QSharedPointer<QDiscordGuild> guild(const QDiscordID& id) const { return _guilds.value(id); }
	QList<QSharedPointer<QDiscordGuild>> guilds() const { return _guilds.values(); }
	QMap<QDiscordID, QSharedPointer<QDiscordGuild>> guildsMap() const { return _guilds; }
	QSharedPointer<QDiscordApplication> application() const { return _application; }

private:
	int                                               _protocolVersion = -1;
	QSharedPointer<QDiscordApplication>               _application;
	QSharedPointer<QDiscordUser>                      _user;
	QMap<QDiscordID, QSharedPointer<QDiscordChannel>> _dmChannels;
	QMap<QDiscordID, QSharedPointer<QDiscordGuild>>   _guilds;
};

