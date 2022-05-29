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
#include "QDiscordPermissions.h"


QDiscordPermissions QDiscordPermissions::none()
{
	return {};
}


QDiscordPermissions QDiscordPermissions::all()
{
	return { 0x7ff7fcff };
}


QDiscordPermissions QDiscordPermissions::allChannel()
{
	return { 0x33f7fc51 };
}


QDiscordPermissions QDiscordPermissions::general()
{
	return { 0x7c0000bf };
}


QDiscordPermissions QDiscordPermissions::text()
{
	return { 0x7fc40 };
}


QDiscordPermissions QDiscordPermissions::voice()
{
	return { 0x3f00000 };
}


QDiscordPermissions::QDiscordPermissions(quint64 value)
	: _value(value)
{
}


bool QDiscordPermissions::isSubset(const QDiscordPermissions& other) const
{
	return (_value & other._value) == _value;
}


bool QDiscordPermissions::isSuperset(const QDiscordPermissions& other) const
{
	return (_value | other._value) == _value;
}


bool QDiscordPermissions::isStrictSubset(const QDiscordPermissions& other) const
{
	return isSubset(other) && operator!=(other);
}


bool QDiscordPermissions::isStrictSuperset(const QDiscordPermissions& other) const
{
	return isSuperset(other) && operator!=(other);
}


void QDiscordPermissions::handleOverwrite(quint64 allow, quint64 deny)
{
	_value = (_value & ~deny) | allow;
}


void QDiscordPermissions::handleOverwrite(const QDiscordPermissions& allow, const QDiscordPermissions& deny)
{
	handleOverwrite(allow._value, deny._value);
}


bool QDiscordPermissions::createInstantInvite() const
{
	return bit(0);
}


void QDiscordPermissions::setCreateInstantInvite(bool value)
{
	set(0, value);
}


bool QDiscordPermissions::kickMembers() const
{
	return bit(1);
}


void QDiscordPermissions::setKickMembers(bool value)
{
	set(1, value);
}


bool QDiscordPermissions::banMembers() const
{
	return bit(2);
}


void QDiscordPermissions::setBanMembers(bool value)
{
	set(2, value);
}


bool QDiscordPermissions::administrator() const
{
	return bit(3);
}


void QDiscordPermissions::setAdministrator(bool value)
{
	set(3, value);
}


bool QDiscordPermissions::manageChannels() const
{
	return bit(4);
}


void QDiscordPermissions::setManageChannels(bool value)
{
	set(4, value);
}


bool QDiscordPermissions::manageServer() const
{
	return bit(5);
}


void QDiscordPermissions::setManageServer(bool value)
{
	set(5, value);
}


bool QDiscordPermissions::addReactions() const
{
	return bit(6);
}


void QDiscordPermissions::setAddReactions(bool value)
{
	set(6, value);
}


bool QDiscordPermissions::viewAuditLogs() const
{
	return bit(7);
}


void QDiscordPermissions::setViewAuditLogs(bool value)
{
	set(7, value);
}


bool QDiscordPermissions::readMessages() const
{
	return bit(10);
}


void QDiscordPermissions::setReadMessages(bool value)
{
	set(10, value);
}


bool QDiscordPermissions::sendMessages() const
{
	return bit(11);
}


void QDiscordPermissions::setSendMessages(bool value)
{
	set(11, value);
}


bool QDiscordPermissions::sendTtsMessages() const
{
	return bit(12);
}


void QDiscordPermissions::setSendTtsMessages(bool value)
{
	set(12, value);
}


bool QDiscordPermissions::manageMessages() const
{
	return bit(13);
}


void QDiscordPermissions::setManageMessages(bool value)
{
	set(13, value);
}


bool QDiscordPermissions::embedLinks() const
{
	return bit(14);
}


void QDiscordPermissions::setEmbedLinks(bool value)
{
	set(14, value);
}


bool QDiscordPermissions::attachFiles() const
{
	return bit(15);
}


void QDiscordPermissions::setAttachFiles(bool value)
{
	set(15, value);
}


bool QDiscordPermissions::readMessageHistory() const
{
	return bit(16);
}


void QDiscordPermissions::setReadMessageHistory(bool value)
{
	set(16, value);
}


bool QDiscordPermissions::mentionEveryone() const
{
	return bit(17);
}


void QDiscordPermissions::setMentionEveryone(bool value)
{
	set(17, value);
}


bool QDiscordPermissions::externalEmojis() const
{
	return bit(18);
}


void QDiscordPermissions::setExternalEmojis(bool value)
{
	set(18, value);
}


bool QDiscordPermissions::connect() const
{
	return bit(20);
}


void QDiscordPermissions::setConnect(bool value)
{
	set(20, value);
}


bool QDiscordPermissions::speak() const
{
	return bit(21);
}


void QDiscordPermissions::setSpeak(bool value)
{
	set(21, value);
}


bool QDiscordPermissions::muteMembers() const
{
	return bit(22);
}


void QDiscordPermissions::setMuteMembers(bool value)
{
	set(22, value);
}


bool QDiscordPermissions::deafenMembers() const
{
	return bit(23);
}


void QDiscordPermissions::setDeafenMembers(bool value)
{
	set(23, value);
}


bool QDiscordPermissions::moveMembers() const
{
	return bit(24);
}


void QDiscordPermissions::setMoveMembers(bool value)
{
	set(24, value);
}


bool QDiscordPermissions::useVoiceActivation() const
{
	return bit(25);
}


void QDiscordPermissions::setUseVoiceActivation(bool value)
{
	set(25, value);
}


bool QDiscordPermissions::changeNickname() const
{
	return bit(26);
}


void QDiscordPermissions::setChangeNickname(bool value)
{
	set(26, value);
}


bool QDiscordPermissions::manageNicknames() const
{
	return bit(27);
}


void QDiscordPermissions::setManageNicknames(bool value)
{
	set(27, value);
}


bool QDiscordPermissions::manageRoles() const
{
	return bit(28);
}


void QDiscordPermissions::setManageRoles(bool value)
{
	set(28, value);
}


bool QDiscordPermissions::manageWebhooks() const
{
	return bit(29);
}


void QDiscordPermissions::setManageWebhooks(bool value)
{
	set(29, value);
}


bool QDiscordPermissions::manageEmojis() const
{
	return bit(30);
}


void QDiscordPermissions::setManageEmojis(bool value)
{
	set(30, value);
}


quint64 QDiscordPermissions::value() const
{
	return _value;
}


void QDiscordPermissions::setValue(const quint64 value)
{
	_value = value;
}


bool QDiscordPermissions::operator==(const QDiscordPermissions& other) const
{
	return _value == other._value;
}


bool QDiscordPermissions::operator!=(const QDiscordPermissions& other) const
{
	return !operator==(other);
}


bool QDiscordPermissions::operator>(const QDiscordPermissions& other) const
{
	return isStrictSuperset(other);
}


bool QDiscordPermissions::operator<(const QDiscordPermissions& other) const
{
	return isStrictSubset(other);
}


bool QDiscordPermissions::operator>=(const QDiscordPermissions& other) const
{
	return isSuperset(other);
}


bool QDiscordPermissions::operator<=(const QDiscordPermissions& other) const
{
	return isSubset(other);
}


bool QDiscordPermissions::bit(quint8 index) const
{
	return (_value >> index) & 1;
}


void QDiscordPermissions::set(quint8 index, bool value)
{
	if (value)
	{
		_value |= ((quint64)1 << index);
	}
	else
	{
		_value &= ~((quint64)1 << index);
	}
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordPermissions& value, const QString& name)
{
	value = QDiscordPermissions(action.data()[name].toVariant().toULongLong());
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordPermissions& value, const QString& name)
{
	action.data().insert(name, QString::number(value.value()));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDiscordPermissions>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		value = QDiscordPermissions(action.data()[name].toVariant().toULongLong());
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDiscordPermissions>& value, const QString& name)
{
	if (value.has_value())
	{
		action.data().insert(name, QString::number(value.value().value()));
	}
}


