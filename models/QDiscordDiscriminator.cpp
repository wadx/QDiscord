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
#include "QDiscordDiscriminator.h"
#include "moc_QDiscordDiscriminator.cpp"


QDiscordDiscriminator::QDiscordDiscriminator()
{
	_discriminator = -1;
}


QDiscordDiscriminator::QDiscordDiscriminator(qint16 discriminator)
{
	_discriminator = discriminator;
}


QDiscordDiscriminator::QDiscordDiscriminator(const QString& discriminator)
{
	bool ok;
	_discriminator = discriminator.toShort(&ok);
	if (!ok)
	{
		_discriminator = -1;
	}
}


QString QDiscordDiscriminator::toString() const
{
	return QString::number(_discriminator);
}


qint16 QDiscordDiscriminator::value() const
{
	return _discriminator;
}


void QDiscordDiscriminator::setValue(const qint16 value)
{
	_discriminator = value;
}


bool QDiscordDiscriminator::isNull() const
{
	return _discriminator == -1;
}


bool QDiscordDiscriminator::operator!() const
{
	return _discriminator == -1;
}


QDiscordDiscriminator::operator bool() const
{
	return _discriminator != -1;
}


bool QDiscordDiscriminator::operator==(const QDiscordDiscriminator& other) const
{
	if (isNull() || other.isNull())
	{
		return false;
	}
	return _discriminator == other._discriminator;
}


bool QDiscordDiscriminator::operator!=(const QDiscordDiscriminator& other) const
{
	return !operator==(other);
}


bool QDiscordDiscriminator::operator>(const QDiscordDiscriminator& other) const
{
	return _discriminator > other._discriminator;
}


bool QDiscordDiscriminator::operator<(const QDiscordDiscriminator& other) const
{
	return _discriminator < other._discriminator;
}


bool QDiscordDiscriminator::operator<=(const QDiscordDiscriminator& other) const
{
	return _discriminator <= other._discriminator;
}


bool QDiscordDiscriminator::operator>=(const QDiscordDiscriminator& other) const
{
	return _discriminator >= other._discriminator;
}


bool QDiscordDiscriminator::operator==(qint16 other) const
{
	return _discriminator == other;
}


bool QDiscordDiscriminator::operator!=(qint16 other) const
{
	return _discriminator != other;
}


bool QDiscordDiscriminator::operator>(qint16 other) const
{
	return _discriminator > other;
}


bool QDiscordDiscriminator::operator<(qint16 other) const
{
	return _discriminator < other;
}


bool QDiscordDiscriminator::operator<=(qint16 other) const
{
	return _discriminator <= other;
}


bool QDiscordDiscriminator::operator>=(qint16 other) const
{
	return _discriminator >= other;
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordDiscriminator& value, const QString& name)
{
	value = QDiscordDiscriminator(action.data()[name].toString());
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordDiscriminator& value, const QString& name)
{
	action.data().insert(name, value.toString());
}

