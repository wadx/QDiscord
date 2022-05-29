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
#include "QDiscordPermissionOverwrite.h"


QDiscordPermissionOverwrite::QDiscordPermissionOverwrite(const QDiscordID& id, Type type, QDiscordPermissions allow, QDiscordPermissions deny)
{
	_id = id;
	_type = type;
	for (quint8 i = 0; i < QDiscordPermissions::bits; i++)
	{
		if (allow.bit(i))
		{
			_value.at(i) = true;
		}
		if (deny.bit(i))
		{
			_value.at(i) = false;
		}
	}
}


std::optional<bool> QDiscordPermissionOverwrite::createInstantInvite() const
{
	return bit(0);
}


void QDiscordPermissionOverwrite::setCreateInstantInvite(const std::optional<bool>& value)
{
	set(0, value);
}


std::optional<bool> QDiscordPermissionOverwrite::kickMembers() const
{
	return bit(1);
}


void QDiscordPermissionOverwrite::setKickMembers(const std::optional<bool>& value)
{
	set(1, value);
}


std::optional<bool> QDiscordPermissionOverwrite::banMembers() const
{
	return bit(2);
}


void QDiscordPermissionOverwrite::setBanMembers(const std::optional<bool>& value)
{
	set(2, value);
}


std::optional<bool> QDiscordPermissionOverwrite::administrator() const
{
	return bit(3);
}


void QDiscordPermissionOverwrite::setAdministrator(const std::optional<bool>& value)
{
	set(3, value);
}


std::optional<bool> QDiscordPermissionOverwrite::manageChannels() const
{
	return bit(4);
}


void QDiscordPermissionOverwrite::setManageChannels(const std::optional<bool>& value)
{
	set(4, value);
}


std::optional<bool> QDiscordPermissionOverwrite::manageServer() const
{
	return bit(5);
}


void QDiscordPermissionOverwrite::setManageServer(const std::optional<bool>& value)
{
	set(5, value);
}


std::optional<bool> QDiscordPermissionOverwrite::addReactions() const
{
	return bit(6);
}


void QDiscordPermissionOverwrite::setAddReactions(const std::optional<bool>& value)
{
	set(6, value);
}


std::optional<bool> QDiscordPermissionOverwrite::viewAuditLogs() const
{
	return bit(7);
}


void QDiscordPermissionOverwrite::setViewAuditLogs(const std::optional<bool>& value)
{
	set(7, value);
}


std::optional<bool> QDiscordPermissionOverwrite::readMessages() const
{
	return bit(10);
}


void QDiscordPermissionOverwrite::setReadMessages(const std::optional<bool>& value)
{
	set(10, value);
}


std::optional<bool> QDiscordPermissionOverwrite::sendMessages() const
{
	return bit(11);
}


void QDiscordPermissionOverwrite::setSendMessages(const std::optional<bool>& value)
{
	set(11, value);
}


std::optional<bool> QDiscordPermissionOverwrite::sendTtsMessages() const
{
	return bit(12);
}


void QDiscordPermissionOverwrite::setSendTtsMessages(const std::optional<bool>& value)
{
	set(12, value);
}


std::optional<bool> QDiscordPermissionOverwrite::manageMessages() const
{
	return bit(13);
}


void QDiscordPermissionOverwrite::setManageMessages(const std::optional<bool>& value)
{
	set(13, value);
}


std::optional<bool> QDiscordPermissionOverwrite::embedLinks() const
{
	return bit(14);
}


void QDiscordPermissionOverwrite::setEmbedLinks(const std::optional<bool>& value)
{
	set(14, value);
}


std::optional<bool> QDiscordPermissionOverwrite::attachFiles() const
{
	return bit(15);
}


void QDiscordPermissionOverwrite::setAttachFiles(const std::optional<bool>& value)
{
	set(15, value);
}


std::optional<bool> QDiscordPermissionOverwrite::readMessageHistory() const
{
	return bit(16);
}


void QDiscordPermissionOverwrite::setReadMessageHistory(const std::optional<bool>& value)
{
	set(16, value);
}


std::optional<bool> QDiscordPermissionOverwrite::mentionEveryone() const
{
	return bit(17);
}


void QDiscordPermissionOverwrite::setMentionEveryone(const std::optional<bool>& value)
{
	set(17, value);
}


std::optional<bool> QDiscordPermissionOverwrite::externalEmojis() const
{
	return bit(18);
}


void QDiscordPermissionOverwrite::setExternalEmojis(const std::optional<bool>& value)
{
	set(18, value);
}


std::optional<bool> QDiscordPermissionOverwrite::connect() const
{
	return bit(20);
}


void QDiscordPermissionOverwrite::setConnect(const std::optional<bool>& value)
{
	set(20, value);
}


std::optional<bool> QDiscordPermissionOverwrite::speak() const
{
	return bit(21);
}


void QDiscordPermissionOverwrite::setSpeak(const std::optional<bool>& value)
{
	set(21, value);
}


std::optional<bool> QDiscordPermissionOverwrite::muteMembers() const
{
	return bit(22);
}


void QDiscordPermissionOverwrite::setMuteMembers(const std::optional<bool>& value)
{
	set(22, value);
}


std::optional<bool> QDiscordPermissionOverwrite::deafenMembers() const
{
	return bit(23);
}


void QDiscordPermissionOverwrite::setDeafenMembers(const std::optional<bool>& value)
{
	set(23, value);
}


std::optional<bool> QDiscordPermissionOverwrite::moveMembers() const
{
	return bit(24);
}


void QDiscordPermissionOverwrite::setMoveMembers(const std::optional<bool>& value)
{
	set(24, value);
}


std::optional<bool> QDiscordPermissionOverwrite::useVoiceActivation() const
{
	return bit(25);
}


void QDiscordPermissionOverwrite::setUseVoiceActivation(const std::optional<bool>& value)
{
	set(25, value);
}


std::optional<bool> QDiscordPermissionOverwrite::changeNickname() const
{
	return bit(26);
}


void QDiscordPermissionOverwrite::setChangeNickname(const std::optional<bool>& value)
{
	set(26, value);
}


std::optional<bool> QDiscordPermissionOverwrite::manageNicknames() const
{
	return bit(27);
}


void QDiscordPermissionOverwrite::setManageNicknames(const std::optional<bool>& value)
{
	set(27, value);
}


std::optional<bool> QDiscordPermissionOverwrite::manageRoles() const
{
	return bit(28);
}


void QDiscordPermissionOverwrite::setManageRoles(const std::optional<bool>& value)
{
	set(28, value);
}


std::optional<bool> QDiscordPermissionOverwrite::manageWebhooks() const
{
	return bit(29);
}


void QDiscordPermissionOverwrite::setManageWebhooks(const std::optional<bool>& value)
{
	set(29, value);
}


std::optional<bool> QDiscordPermissionOverwrite::manageEmojis() const
{
	return bit(30);
}


void QDiscordPermissionOverwrite::setManageEmojis(const std::optional<bool>& value)
{
	set(30, value);
}


QDiscordPermissions QDiscordPermissionOverwrite::allow() const
{
	return pair().first;
}


QDiscordPermissions QDiscordPermissionOverwrite::deny() const
{
	return pair().second;
}


QPair<QDiscordPermissions, QDiscordPermissions> QDiscordPermissionOverwrite::pair() const
{
	QDiscordPermissions allow;
	QDiscordPermissions deny;
	for (quint8 i = 0; i < QDiscordPermissions::bits; i++)
	{
		if (_value.at(i).has_value())
		{
			if (_value.at(i).value())
			{
				allow.set(i, true);
			}
			else
			{
				deny.set(i, true);
			}
		}
	}
	return { allow, deny };
}


bool QDiscordPermissionOverwrite::isEmpty() const
{
	for (const std::optional<bool>& value : _value)
	{
		if (value.has_value())
		{
			return false;
		}
	}

	return true;
}


std::optional<bool> QDiscordPermissionOverwrite::bit(const quint8 index) const
{
	return _value.at(index);
}


void QDiscordPermissionOverwrite::set(const quint8 index, const std::optional<bool>& value)
{
	_value.at(index) = value;
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordPermissionOverwrite>& value, const QString& name)
{
	value.clear();
	for (const QJsonValue& i : action.data()[name].toArray())
	{
		QJsonObject obj = i.toObject();
		QDiscordID id = QDiscordID(obj["id"].toString());
		QDiscordPermissionOverwrite::Type type = static_cast<QDiscordPermissionOverwrite::Type>(obj["type"].toInt());
		QDiscordPermissions allow = QDiscordPermissions(obj["allow"].toVariant().toULongLong());
		QDiscordPermissions deny = QDiscordPermissions(obj["deny"].toVariant().toULongLong());
		value.append(QDiscordPermissionOverwrite(id, type, allow, deny));
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordPermissionOverwrite>& value, const QString& name)
{
	QJsonArray output;
	for (const QDiscordPermissionOverwrite& i : value)
	{
		QJsonObject obj;
		obj["id"] = i.id().toString();
		obj["type"] = static_cast<int>(i.type());
		obj["allow"] = QString::number(i.allow().value());
		obj["deny"] = QString::number(i.deny().value());
		output.append(obj);
	}
	action.data().insert(name, output);
}


