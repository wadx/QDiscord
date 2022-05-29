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
#include "QDiscordId.h"
#include "moc_QDiscordId.cpp"


QDiscordID::QDiscordID()
{
	_id = 0;
}


QDiscordID::QDiscordID(quint64 id)
{
	_id = id;
}


QDiscordID::QDiscordID(const char* id)
{
	bool ok;
	_id = QString(id).toULongLong(&ok);
	if (!ok)
	{
		_id = 0;
	}
}


QDiscordID::QDiscordID(const QString& id)
{
	bool ok;
	_id = id.toULongLong(&ok);
	if (!ok)
	{
		_id = 0;
	}
}


QString QDiscordID::toString() const
{
	return QString::number(_id);
}


quint64 QDiscordID::value() const
{
	return _id;
}


void QDiscordID::setValue(const quint64 value)
{
	_id = value;
}


QDateTime QDiscordID::createdAt() const
{
	return QDateTime::fromSecsSinceEpoch(((_id >> 22) + QDiscordUtilities::discordEpoch) / 1000);
}


QDiscordID QDiscordID::generate()
{
	quint64 ms = QDateTime::currentMSecsSinceEpoch() - QDiscordUtilities::discordEpoch;
	static quint64 workerId = QRandomGenerator::global()->generate64();
	static quint64 processId = QRandomGenerator::global()->generate64();
	static quint64 inc = 1;
	quint64 id = ms << 22 | workerId << 17 | processId << 12 | inc++;
	return QDiscordID(id);
}


bool QDiscordID::isNull() const
{
	return _id == 0;
}


bool QDiscordID::operator!() const
{
	return _id == 0;
}


QDiscordID::operator bool() const
{
	return _id != 0;
}


bool QDiscordID::operator==(const QDiscordID& other) const
{
	if (isNull() || other.isNull())
	{
		return false;
	}
	return _id == other._id;
}


bool QDiscordID::operator!=(const QDiscordID& other) const
{
	return !operator==(other);
}


bool QDiscordID::operator>(const QDiscordID& other) const
{
	return _id > other._id;
}


bool QDiscordID::operator<(const QDiscordID& other) const
{
	return _id < other._id;
}


bool QDiscordID::operator<=(const QDiscordID& other) const
{
	return _id <= other._id;
}


bool QDiscordID::operator>=(const QDiscordID& other) const
{
	return _id >= other._id;
}


bool QDiscordID::operator==(quint64 other) const
{
	return _id == other;
}


bool QDiscordID::operator!=(quint64 other) const
{
	return _id != other;
}


bool QDiscordID::operator>(quint64 other) const
{
	return _id > other;
}


bool QDiscordID::operator<(quint64 other) const
{
	return _id < other;
}


bool QDiscordID::operator<=(quint64 other) const
{
	return _id <= other;
}


bool QDiscordID::operator>=(quint64 other) const
{
	return _id >= other;
}


namespace QDiscordModel
{


template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordID& value, const QString& name)
{
	value = action.data()[name].toString();
}


template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordID& value, const QString& name)
{
	action.data().insert(name, value.toString());
}


template<>
void field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordID>& value, const QString& name)
{
	value.clear();
	for (const QJsonValue& i : action.data()[name].toArray())
	{
		QDiscordID item(i.toString());
		value.append(item);
	}
}


template<>
void field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordID>& value, const QString& name)
{
	QJsonArray output;
	for (const QDiscordID& i : value)
	{
		output.append(i.toString());
	}
	action.data().insert(name, output);
}


template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDiscordID>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		value = action.data()[name].toString();
	}
}


template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDiscordID>& value, const QString& name)
{
	if (value.has_value())
	{
		action.data().insert(name, value.value().toString());
	}
}


} // namespace QDiscordModel

