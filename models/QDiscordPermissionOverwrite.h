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

#include "QDiscordId.h"
#include "QDiscordPermissions.h"

// Based on https://github.com/Rapptz/discord.py


class QDiscordPermissionOverwrite
{
	Q_GADGET

	Q_PROPERTY(QDiscordPermissions allow READ allow STORED false)
	Q_PROPERTY(QDiscordPermissions deny READ deny STORED false)

	Q_PROPERTY(std::optional<bool> createInstantInvite READ createInstantInvite WRITE setCreateInstantInvite STORED false)
	Q_PROPERTY(std::optional<bool> kickMembers READ kickMembers WRITE setKickMembers STORED false)
	Q_PROPERTY(std::optional<bool> banMembers READ banMembers WRITE setBanMembers STORED false)
	Q_PROPERTY(std::optional<bool> administrator READ administrator WRITE setAdministrator STORED false)
	Q_PROPERTY(std::optional<bool> manageChannels READ manageChannels WRITE setManageChannels STORED false)
	Q_PROPERTY(std::optional<bool> manageServer READ manageServer WRITE setManageServer STORED false)
	Q_PROPERTY(std::optional<bool> addReactions READ addReactions WRITE setAddReactions STORED false)
	Q_PROPERTY(std::optional<bool> viewAuditLogs READ viewAuditLogs WRITE setViewAuditLogs STORED false)
	Q_PROPERTY(std::optional<bool> readMessages READ readMessages WRITE setReadMessages STORED false)
	Q_PROPERTY(std::optional<bool> sendMessages READ sendMessages WRITE setSendMessages STORED false)
	Q_PROPERTY(std::optional<bool> sendTtsMessages READ sendTtsMessages WRITE setSendTtsMessages STORED false)
	Q_PROPERTY(std::optional<bool> manageMessages READ manageMessages WRITE setManageMessages STORED false)
	Q_PROPERTY(std::optional<bool> embedLinks READ embedLinks WRITE setEmbedLinks STORED false)
	Q_PROPERTY(std::optional<bool> attachFiles READ attachFiles WRITE setAttachFiles STORED false)
	Q_PROPERTY(std::optional<bool> readMessageHistory READ readMessageHistory WRITE setReadMessageHistory STORED false)
	Q_PROPERTY(std::optional<bool> mentionEveryone READ mentionEveryone WRITE setMentionEveryone STORED false)
	Q_PROPERTY(std::optional<bool> externalEmojis READ externalEmojis WRITE setExternalEmojis STORED false)
	Q_PROPERTY(std::optional<bool> connect READ connect WRITE setConnect STORED false)
	Q_PROPERTY(std::optional<bool> speak READ speak WRITE setSpeak STORED false)
	Q_PROPERTY(std::optional<bool> muteMembers READ muteMembers WRITE setMuteMembers STORED false)
	Q_PROPERTY(std::optional<bool> deafenMembers READ deafenMembers WRITE setDeafenMembers STORED false)
	Q_PROPERTY(std::optional<bool> moveMembers READ moveMembers WRITE setMoveMembers STORED false)
	Q_PROPERTY(std::optional<bool> useVoiceActivation READ useVoiceActivation WRITE setUseVoiceActivation STORED false)
	Q_PROPERTY(std::optional<bool> changeNickname READ changeNickname WRITE setChangeNickname STORED false)
	Q_PROPERTY(std::optional<bool> manageNicknames READ manageNicknames WRITE setManageNicknames STORED false)
	Q_PROPERTY(std::optional<bool> manageRoles READ manageRoles WRITE setManageRoles STORED false)
	Q_PROPERTY(std::optional<bool> manageWebhooks READ manageWebhooks WRITE setManageWebhooks STORED false)
	Q_PROPERTY(std::optional<bool> manageEmojis READ manageEmojis WRITE setManageEmojis STORED false)

public:
	enum class Type : qint8
	{
		ROLE    = 0,
		MEMBER  = 1,
		Unknown = -1
	};
	Q_ENUM(Type)

	QDiscordPermissionOverwrite() = default;
	QDiscordPermissionOverwrite(const QDiscordID& id, Type type, QDiscordPermissions allow, QDiscordPermissions deny);

	std::optional<bool> createInstantInvite() const;
	void setCreateInstantInvite(const std::optional<bool>& value);
	std::optional<bool> kickMembers() const;
	void setKickMembers(const std::optional<bool>& value);
	std::optional<bool> banMembers() const;
	void setBanMembers(const std::optional<bool>& value);
	std::optional<bool> administrator() const;
	void setAdministrator(const std::optional<bool>& value);
	std::optional<bool> manageChannels() const;
	void setManageChannels(const std::optional<bool>& value);
	std::optional<bool> manageServer() const;
	void setManageServer(const std::optional<bool>& value);
	std::optional<bool> addReactions() const;
	void setAddReactions(const std::optional<bool>& value);
	std::optional<bool> viewAuditLogs() const;
	void setViewAuditLogs(const std::optional<bool>& value);
	std::optional<bool> readMessages() const;
	void setReadMessages(const std::optional<bool>& value);
	std::optional<bool> sendMessages() const;
	void setSendMessages(const std::optional<bool>& value);
	std::optional<bool> sendTtsMessages() const;
	void setSendTtsMessages(const std::optional<bool>& value);
	std::optional<bool> manageMessages() const;
	void setManageMessages(const std::optional<bool>& value);
	std::optional<bool> embedLinks() const;
	void setEmbedLinks(const std::optional<bool>& value);
	std::optional<bool> attachFiles() const;
	void setAttachFiles(const std::optional<bool>& value);
	std::optional<bool> readMessageHistory() const;
	void setReadMessageHistory(const std::optional<bool>& value);
	std::optional<bool> mentionEveryone() const;
	void setMentionEveryone(const std::optional<bool>& value);
	std::optional<bool> externalEmojis() const;
	void setExternalEmojis(const std::optional<bool>& value);
	std::optional<bool> connect() const;
	void setConnect(const std::optional<bool>& value);
	std::optional<bool> speak() const;
	void setSpeak(const std::optional<bool>& value);
	std::optional<bool> muteMembers() const;
	void setMuteMembers(const std::optional<bool>& value);
	std::optional<bool> deafenMembers() const;
	void setDeafenMembers(const std::optional<bool>& value);
	std::optional<bool> moveMembers() const;
	void setMoveMembers(const std::optional<bool>& value);
	std::optional<bool> useVoiceActivation() const;
	void setUseVoiceActivation(const std::optional<bool>& value);
	std::optional<bool> changeNickname() const;
	void setChangeNickname(const std::optional<bool>& value);
	std::optional<bool> manageNicknames() const;
	void setManageNicknames(const std::optional<bool>& value);
	std::optional<bool> manageRoles() const;
	void setManageRoles(const std::optional<bool>& value);
	std::optional<bool> manageWebhooks() const;
	void setManageWebhooks(const std::optional<bool>& value);
	std::optional<bool> manageEmojis() const;
	void setManageEmojis(const std::optional<bool>& value);

	QDiscordPermissions allow() const;
	QDiscordPermissions deny() const;

	QPair<QDiscordPermissions, QDiscordPermissions> pair() const;
	bool isEmpty() const;

	QDiscordID id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	Type type() const { return _type; }
	void setType(const Type type) { _type = type; }

private:
	std::optional<bool> bit(const quint8 index) const;
	void set(const quint8 index, const std::optional<bool>& value);

	QDiscordID                                                _id; // role or user id
	Type                                                      _type = Type::Unknown;
	std::array<std::optional<bool>, QDiscordPermissions::bits> _value;
};
Q_DECLARE_METATYPE(QDiscordPermissionOverwrite)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordPermissionOverwrite>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordPermissionOverwrite>& value, const QString& name);
} // namespace QDiscordModel


