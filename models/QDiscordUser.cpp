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
#include "QDiscordUser.h"
#include "QDiscordRest.h"
#include "QDiscordUtilities.h"
#include "moc_QDiscordUser.cpp"
#include "updateIfValue.h"


QSharedPointer<QDiscordUser> QDiscordUser::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordUser> user(new QDiscordUser());
	user->deserialize(object);
	return user;
}


QDiscordUser::QDiscordUser(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordUser::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordUser::serialize() const
{
	return serializeJson();
}


void QDiscordUser::update(QSharedPointer<QDiscordUser> other)
{
	updateIfValue(_id, other->_id);
	updateIfValue(_username, other->_username);
	updateIfValue(_discriminator, other->_discriminator);
	updateIfValue(_avatar, other->_avatar);
	updateIfValue(_bot, other->_bot);
	updateIfValue(_system, other->_system);
	updateIfValue(_mfaEnabled, other->_mfaEnabled);
	updateIfValue(_banner, other->_banner);
	updateIfValue(_accent_color, other->_accent_color);
	updateIfValue(_locale, other->_locale);
	updateIfValue(_verified, other->_verified);
	updateIfValue(_email, other->_email);
	updateIfValue(_flags, other->_flags);
	updateIfValue(_premium_type, other->_premium_type);
	updateIfValue(_public_flags, other->_public_flags);
}


QString QDiscordUser::mention() const
{
	return QString("<@%1>").arg(_id ? _id.toString() : "invalid ID");
}


QDiscordID QDiscordUser::parseMention(const QString& mention)
{
	qsizetype beg = 0;
	beg = mention.indexOf("<@");
	if (beg == -1)
	{
		return QDiscordID();
	}
	else
	{
		beg += 2;
	}
	qsizetype end = mention.indexOf(">");
	QString idStr = mention.mid(beg, end - beg);
	return QDiscordID(idStr);
}


