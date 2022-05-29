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
#include "QDiscordMember.h"
#include "QDiscordGuild.h"
#include "updateIfValue.h"


QSharedPointer<QDiscordMember> QDiscordMember::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordMember> member(new QDiscordMember());
	member->deserialize(object);
	return member;
}


QDiscordMember::QDiscordMember(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordMember::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordMember::serialize() const
{
	return serializeJson();
}


void QDiscordMember::update(const QDiscordMember& other)
{
	_user->update(other.user());
	updateIfValue(_nick, other._nick);
	updateIfValue(_avatar, other._avatar);
	_roles = other._roles;
	updateIfValue(_joinedAt, other._joinedAt);
	_premium_since = other._premium_since;
	updateIfValue(_deaf, other._deaf);
	updateIfValue(_mute, other._mute);
	updateIfValue(_pending, other._pending);
	_communication_disabled_until = other._communication_disabled_until;
	_permissions = other._permissions;
	updateIfValue(_flags, other._flags);
	updateIfValue(_pending, other._pending);
	updateIfValue(_guild_id, other._guild_id);
	updateIfValue(_hoisted_role, other._hoisted_role);
}


QString QDiscordMember::mentionUsername() const
{
	return _user ? _user->mention() : "";
}


QString QDiscordMember::mentionNickname() const
{
	return QString("<@!%1>").arg(_user->id() ? _user->id().toString() : "invalid ID");
}


bool QDiscordMember::operator==(const QDiscordMember& other) const
{
	QSharedPointer<QDiscordGuild> strongGuild = _guild.toStrongRef();
	if (!strongGuild)
	{
		return false;
	}
	if (!other.guild())
	{
		return false;
	}
	return _user == other._user && strongGuild->id() == other.guild()->id();
}


bool QDiscordMember::operator!=(const QDiscordMember& other) const
{
	return !operator==(other);
}
